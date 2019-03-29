#include "ws_session_manager.h"


 WsSessionManager:: WsSessionManager() {
}


 WsSessionManager::~ WsSessionManager() {
}


void  WsSessionManager::Start(WebSocketSessionPtr session) {
	sessions_mutex_.lock();
	sessions_.insert(session);
	sessions_mutex_.unlock();
	session->Start();
}


void  WsSessionManager::Stop(WebSocketSessionPtr session) {
	if (!session) {
		return;
	}
	sessions_mutex_.lock();
	sessions_.erase(session);
	sessions_mutex_.unlock();
	session->Close();
}


void  WsSessionManager::StopAll() {
	sessions_mutex_.lock();
	std::for_each(sessions_.begin(), sessions_.end(), [this](WebSocketSessionPtr session) {
		Stop(session);
	});
	sessions_.clear();
	sessions_mutex_.unlock();
}


