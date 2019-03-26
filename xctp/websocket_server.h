#pragma once

#include <functional>
#include <string>
#include <queue>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "io_context_pool.h"
#include "ws_session_manager.h"
using boost::asio::ip::tcp;



class WebSocketServer
	: public boost::enable_shared_from_this<WebSocketServer>,
	public boost::noncopyable {
public:
	WebSocketServer(size_t count_of_workers);
	~WebSocketServer();

	void Create(const std::string& address, const std::string& port);
	void Run();
	void Stop();
	void Start(const std::string& address, const std::string& port);
	void StartThread(const std::string& address, const std::string& port);
	void Join();

	virtual void OnNewSession(WebSocketSessionPtr session);
	virtual void OnRead(WebSocketSessionPtr session, const std::string& message);
	virtual void OnWrite(WebSocketSessionPtr session, size_t length);
	virtual void OnClose(WebSocketSessionPtr session, const boost::system::error_code& ec);
	virtual void OnError(WebSocketSessionPtr session, const boost::system::error_code& ec);

	void Close(WebSocketSessionPtr session);

private:
	void DoAccept();

	IOContextPool workers_;
	tcp::acceptor acceptor_;
	WebSocketSessionPtr session_;
	WsSessionManagerPtr manager_;
	boost::shared_ptr<boost::thread> thread_;
};

