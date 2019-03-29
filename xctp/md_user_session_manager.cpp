#include "md_user_session_manager.h"
#include "json_wrapper.h"
#include "switch_wrapper.h"
#include "ctp_session.h"
#include "settings.h"

MdUserSessionManagerPtr md_user_session_manager;

MdUserSessionManager::MdUserSessionManager() {
}


MdUserSessionManager::~MdUserSessionManager() {
}


void MdUserSessionManager::Attach(const std::string& name, WebSocketSessionPtr session) {
	session->SetName(name);
	named_sessions_mutex_.lock();
	auto iter = named_sessions_.find(name);
	if (iter != named_sessions_.end()) {
		named_sessions_.erase(iter);
	}
	named_sessions_.emplace(name, session);
	named_sessions_mutex_.unlock();
}


WebSocketSessionPtr MdUserSessionManager::Get(const std::string& name) {
	WebSocketSessionPtr session;
	named_sessions_mutex_.lock();
	auto iter = named_sessions_.find(name);
	if (iter != named_sessions_.end()) {
		session = iter->second;
	}
	named_sessions_mutex_.unlock();
	return session;
}


WebSocketSessionPtr MdUserSessionManager::Remove(const std::string& name) {
	WebSocketSessionPtr session;
	named_sessions_mutex_.lock();
	auto iter = named_sessions_.find(name);
	if (iter != named_sessions_.end()) {
		session = iter->second;
		named_sessions_.erase(iter);
	}
	named_sessions_mutex_.unlock();
	return session;
}


void MdUserSessionManager::Clear() {
	named_sessions_mutex_.lock();
	named_sessions_.clear();
	named_sessions_mutex_.unlock();
}


void MdUserSessionManager::OnMessage(WebSocketSessionPtr session, const std::string& message) {
	JsonWrapper jw;
	if (!jw.Parse(message.c_str())) {
		// parse error
		return;
	}
	
	std::string action;
	jw.Get("action", action);
	if (!session->IsReady() && action != "auth") {
		// refuse
		return;
	}

	bool reset_keepalive_timer = true;

	SwitchWrapper<std::string, std::function<void(void)>>(action)
		.Case("auth", [&]() {
		std::string user, key;
		jw.GetEx("data.user", user);
		jw.GetEx("data.key", key);
		if (!user.empty() && !key.empty()) {
			// TODO
			// check user here
			Attach(user, session);
			session->SetReady();
		}
	})
		.Case("subscribe", [&]() {
		std::set<std::string> insid_list;
		jw.Get("data", insid_list);
		sub_ins_list_mutex_.lock();
		sub_ins_list_.insert(insid_list.begin(), insid_list.end());
		sub_ins_list_mutex_.unlock();
		ctp_session->Subscribe(session->Name(), insid_list);
	})
		.Case("unsubscribe", [&]() {
		std::set<std::string> insid_list;
		jw.Get("data", insid_list);
		sub_ins_list_mutex_.lock();
		sub_ins_list_.erase(insid_list.begin(), insid_list.end());
		sub_ins_list_mutex_.unlock();
		ctp_session->UnSubscribe(session->Name(), insid_list);
	})
		.Case("ping", [&]() {
		session->Write("{\"action\": \"pong\"}");
	})
		.Default([&]() {
		reset_keepalive_timer = false;
	}).Call();

	// normal message raise reset keepalive timer
	if (reset_keepalive_timer) {
		session->ResetKeepAliveTimer();
	}
}


void MdUserSessionManager::OnError(WebSocketSessionPtr session, const std::string& message) {

}


void MdUserSessionManager::OnClose(WebSocketSessionPtr session) {
	std::set<std::string> ins_list;
	sub_ins_list_mutex_.lock();
	ins_list.insert(sub_ins_list_.begin(), sub_ins_list_.end());
	sub_ins_list_mutex_.unlock();
	Remove(session->Name());
	ctp_session->UnSubscribe(session->Name(), ins_list);
}


void MdUserSessionManager::Send(const std::string& name, const std::string& data) {
	WebSocketSessionPtr session = Get(name);
	session->Write(data+settings->protocol.crlf_);
}


void MdUserSessionManager::Send(const std::set<std::string>& names, const std::string& data) {
	for (auto name : names) {
		Send(name, data);
	}
}




