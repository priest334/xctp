#include "websocket_server.h"
#include <boost/make_shared.hpp>
#include "websocket_session.h"
#include "md_user_session_manager.h"

#include <iostream>
using std::cout;
using std::endl;

WebSocketServer::WebSocketServer(size_t count_of_workers)
	: workers_(count_of_workers),
	acceptor_(workers_.Get()),
	manager_(new WsSessionManager()) {
}


WebSocketServer::~WebSocketServer() {
}


void WebSocketServer::Create(const std::string& address, const std::string& port) {
	tcp::resolver resolver(acceptor_.get_executor().context());
	tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	DoAccept();
}


void WebSocketServer::Run() {
	workers_.Run();
}


void WebSocketServer::Stop() {
	acceptor_.close();
	manager_->StopAll();
	workers_.Stop();
}


void WebSocketServer::Start(const std::string& address, const std::string& port) {
	Create(address, port);
	Run();
}


void WebSocketServer::StartThread(const std::string& address, const std::string& port) {
	thread_ = boost::shared_ptr<boost::thread>(new boost::thread([this](const std::string& _address, const std::string& _port) {
		Start(_address, _port);
	}, address, port));
}


void WebSocketServer::Join() {
	if (thread_) {
		thread_->join();
	}
}


void WebSocketServer::OnNewSession(WebSocketSessionPtr session) {
	
}


void WebSocketServer::OnRead(WebSocketSessionPtr session, const std::string& message) {
	cout << message << endl;
	md_user_session_manager->OnMessage(session, message);
}


void WebSocketServer::OnWrite(WebSocketSessionPtr session, size_t length) {

}


void WebSocketServer::OnClose(WebSocketSessionPtr session, const boost::system::error_code& ec) {
	//cout << ec.message() << endl;
	md_user_session_manager->OnClose(session);
}


void WebSocketServer::OnError(WebSocketSessionPtr session, const boost::system::error_code& ec) {
	cout << ec.message() << endl;
}


void WebSocketServer::Close(WebSocketSessionPtr session) {
	manager_->Stop(session);
}


void WebSocketServer::DoAccept() {
	acceptor_.async_accept(workers_.Get(), [this](const boost::system::error_code& ec, tcp::socket socket) {
		if (!ec) {
			session_.reset(new WebSocketSession(shared_from_this(), std::move(socket)));
			manager_->Start(session_);
		}
		DoAccept();
	});
}



