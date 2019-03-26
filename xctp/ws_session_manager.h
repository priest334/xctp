#pragma once

#include <set>
#include <boost/shared_ptr.hpp>
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
};


typedef boost::shared_ptr<WsSessionManager>  WsSessionManagerPtr;

