#pragma once

#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "websocket_session.h"

class  WsSessionManager {
public:
	 WsSessionManager();
	~ WsSessionManager();

	void Start(WebSocketSessionPtr session);
	void Stop(WebSocketSessionPtr session);
	void StopAll();
private:
	std::set<WebSocketSessionPtr> sessions_;
	boost::mutex sessions_mutex_;
};


typedef boost::shared_ptr<WsSessionManager>  WsSessionManagerPtr;

