#pragma once

#include <string>
#include <map>
#include <set>
#include "websocket_session.h"


class MdUserSessionManager {
public:
	MdUserSessionManager();
	~MdUserSessionManager();

	void Attach(const std::string& name, WebSocketSessionPtr session);
	WebSocketSessionPtr Get(const std::string& name);
	WebSocketSessionPtr Remove(const std::string& name);
	void Clear();

	void OnMessage(WebSocketSessionPtr session, const std::string& message);
	void OnError(WebSocketSessionPtr session, const std::string& message);
	void OnClose(WebSocketSessionPtr session);
	void Send(const std::string& name, const std::string& data);
	void Send(const std::set<std::string>& names, const std::string& data);

private:
	std::map<std::string, WebSocketSessionPtr> named_sessions_;
	std::set<std::string> sub_ins_list_;
};

typedef boost::shared_ptr<MdUserSessionManager> MdUserSessionManagerPtr;
extern MdUserSessionManagerPtr md_user_session_manager;


