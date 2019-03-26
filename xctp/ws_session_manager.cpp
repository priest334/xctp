#include "ws_session_manager.h"


 WsSessionManager:: WsSessionManager() {
}


 WsSessionManager::~ WsSessionManager() {
}


void  WsSessionManager::Start(WebSocketSessionPtr session) {
	sessions_.insert(session);
	session->Start();
}


void  WsSessionManager::Stop(WebSocketSessionPtr session) {
	if (!session) {
		return;
	}
	sessions_.erase(session);
	session->Close();
}


void  WsSessionManager::StopAll() {
	std::for_each(sessions_.begin(), sessions_.end(), [this](WebSocketSessionPtr session) {
		Stop(session);
	});
	sessions_.clear();
}


