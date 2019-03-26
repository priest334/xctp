#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/chrono.hpp>
#include <boost/asio/steady_timer.hpp>

class WebSocketServer;
typedef boost::shared_ptr<WebSocketServer> WebSocketServerPtr;

using boost::asio::ip::tcp;
namespace beast = boost::beast;
namespace chrono = boost::asio::chrono;

class WebSocketSession
	: public boost::enable_shared_from_this<WebSocketSession> {
public:
	WebSocketSession(WebSocketServerPtr server, tcp::socket socket);
	virtual ~WebSocketSession();

	boost::shared_ptr<WebSocketSession> GetPtr();

	// seconds
	void Start(size_t ready_timeout = 5, size_t keepalive_interval = 60);

	void Write(const std::string& message);
	void Close();

	void SetName(const std::string& name);
	std::string Name() const;
	void SetReady(bool ready = true);
	bool IsReady() const;
	void StartKeepAliveTimer();
	void ResetKeepAliveTimer();
private:
	void DoAccept();
	void DoRead();
	void DoWrite();

	WebSocketServerPtr server_;
	beast::websocket::stream<tcp::socket> websocket_;
	beast::multi_buffer input_buffer_;
	beast::multi_buffer output_buffer_;
	std::string name_;
	bool is_ready_;
	boost::asio::steady_timer timer_for_ready_state_;
	boost::asio::steady_timer timer_for_keepalive_;
	chrono::steady_clock::time_point last_message_in_;
	size_t ready_timeout_;
	size_t keepalive_interval_;
};

typedef boost::shared_ptr<WebSocketSession> WebSocketSessionPtr;


