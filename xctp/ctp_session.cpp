#include "ctp_session.h"
#include "md_user_session_manager.h"

CtpSessionPtr ctp_session;


CtpSession::CtpSession() : md_connector_(new MdConnector()){
}


CtpSession::~CtpSession() {
}


void CtpSession::Start() {
	md_connector_->Start();
}


void CtpSession::StartThread() {
	md_thread_ = boost::shared_ptr<boost::thread>(new boost::thread([this]() {
		Start();
	}));
}


void CtpSession::Join() {
	if (md_thread_) {
		md_thread_->join();
	}
}


void CtpSession::Subscribe(const std::string& name, const std::string& insid) {
	bool already_subscribed = false;
	mutex_.lock();
	auto iter = sub_ins_users_.find(insid);
	if (iter != sub_ins_users_.end()) {
		iter->second.emplace(name);
		already_subscribed = true;
	} else {
		std::set<std::string> user_list;
		user_list.emplace(name);
		sub_ins_users_.emplace(insid, user_list);
	}
	mutex_.unlock();
	if (already_subscribed) {
		std::string data;
		md_history_mutex_.lock();
		data = md_history_.Get(insid);
		md_history_mutex_.unlock();
		if (!data.empty()) {
			md_user_session_manager->Send(name, data);
			return;
		}
	}
	// resubscribe
	md_connector_->SubscribeMarketData(insid);
}


void CtpSession::Subscribe(const std::string& name, const std::set<std::string>& insid_list) {
	for (auto &insid : insid_list) {
		Subscribe(name, insid);
	}
}


void CtpSession::UnSubscribe(const std::string& name, const std::string& insid) {
	bool clear_subscribed = false;
	mutex_.lock();
	auto iter = sub_ins_users_.find(insid);
	if (iter != sub_ins_users_.end()) {
		iter->second.erase(name);
		clear_subscribed = iter->second.empty();
	}
	if (clear_subscribed) {
		sub_ins_users_.erase(iter);
	}
	mutex_.unlock();
	if (clear_subscribed) {
		md_connector_->UnSubscribeMarketData(insid);
	}
}


void CtpSession::UnSubscribe(const std::string& name, const std::set<std::string>& insid_list) {
	for (auto &insid : insid_list) {
		UnSubscribe(name, insid);
	}
}


void CtpSession::PublishMarketData(const std::string& insid, const std::string& data) {
	md_history_mutex_.lock();
	md_history_.Save(insid, data);
	md_history_mutex_.unlock();
	std::set<std::string> user_list;
	mutex_.lock();
	auto iter = sub_ins_users_.find(insid);
	if (iter != sub_ins_users_.end()) {
		user_list = iter->second;
	}
	mutex_.unlock();
	if (!user_list.empty()) {
		md_user_session_manager->Send(user_list, data);
	}
}




