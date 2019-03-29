#include "websocket_session.h"
#include "websocket_server.h"


WebSocketSession::WebSocketSession(WebSocketServerPtr server, tcp::socket socket)
	: server_(server),
	websocket_(std::move(socket)),
	is_ready_(false),
	timer_for_ready_state_(socket.get_executor().context()),
	timer_for_keepalive_(socket.get_executor().context()),
	ready_timeout_(5),
	keepalive_interval_(60){
}


WebSocketSession::~WebSocketSession() {
	timer_for_keepalive_.cancel();
	timer_for_ready_state_.cancel();
}


boost::shared_ptr<WebSocketSession> WebSocketSession::GetPtr() {
	return shared_from_this();
}


void WebSocketSession::Start(size_t ready_timeout/* = 5*/, size_t keepalive_interval/* = 60*/) {
	ready_timeout_ = ready_timeout;
	keepalive_interval_ = keepalive_interval;
	timer_for_ready_state_.expires_after(chrono::seconds(ready_timeout_));
	timer_for_ready_state_.async_wait([this](const boost::system::error_code& ec) {
		timer_for_ready_state_.cancel();
		if (!IsReady()) {
			Close();
		}
	});
	DoAccept();
}


void WebSocketSession::Write(const std::string& message) {
	//boost::asio::post(websocket_.get_executor(), [&]() {
	//	size_t remain_size = output_buffer_.size();
	//	size_t size = boost::asio::buffer_copy(output_buffer_.prepare(message.length()), boost::asio::buffer(message));
	//	output_buffer_.commit(size);
	//	if (remain_size == 0) {
	//		DoWrite();
	//	}
	//});
	boost::asio::post(websocket_.get_executor(), boost::bind(&WebSocketSession::WriteAsync, this, message));
}


void WebSocketSession::Close() {
	boost::asio::post(websocket_.get_executor(), [this]() {
		if (websocket_.is_open()) {
			websocket_.async_close(boost::beast::websocket::close_reason("force close"), [this](const boost::system::error_code& ec) {
				if (!ec) {
					server_->OnClose(GetPtr(), boost::system::error_code());
				}
				else {
					server_->OnError(GetPtr(), ec);
				}
			});
		}
		else {
			server_->OnClose(GetPtr(), boost::system::error_code());
		}
	});
}


void WebSocketSession::SetName(const std::string& name) {
	name_ = name;
}


std::string WebSocketSession::Name() const {
	return name_;
}


void WebSocketSession::SetReady(bool ready/* = true*/) {
	is_ready_ = ready;
	if (is_ready_) {
		last_message_in_ = chrono::steady_clock::now();
		StartKeepAliveTimer();
	}
}


bool WebSocketSession::IsReady() const {
	return is_ready_;
}


void WebSocketSession::StartKeepAliveTimer() {
	timer_for_keepalive_.expires_after(chrono::seconds(1));
	timer_for_keepalive_.async_wait([this](const boost::system::error_code& ec) {
		if (!ec) {
			StartKeepAliveTimer();
			chrono::steady_clock::time_point now = chrono::steady_clock::now();
			chrono::duration<size_t> du = chrono::duration_cast<chrono::duration<size_t>>(now - last_message_in_);
			size_t d = du.count();
			if (d > keepalive_interval_) {
				timer_for_keepalive_.cancel();
				Close();
			}
		}
	});
}


void WebSocketSession::ResetKeepAliveTimer() {
	last_message_in_ = chrono::steady_clock::now();
}


void WebSocketSession::DoAccept() {
	websocket_.async_accept([this](const boost::system::error_code& ec) {
		if (ec) {
			server_->OnError(GetPtr(), ec);
			Close();
			return;
		}
		server_->OnNewSession(GetPtr());
		DoRead();
	});
}


void WebSocketSession::DoRead() {
	if (!websocket_.is_open()) {
		return;
	}
	websocket_.async_read(input_buffer_, [this](const boost::system::error_code& ec, size_t length) {
		if (ec) {
			server_->OnError(GetPtr(), ec);
			Close();
			return;
		}
		server_->OnRead(GetPtr(), std::move(beast::buffers_to_string(input_buffer_.data())));
		input_buffer_.consume(input_buffer_.size());
		DoRead();
	});
}


void WebSocketSession::DoWrite() {
	if (!websocket_.is_open()) {
		return;
	}
	websocket_.async_write(output_buffer_.data(), [this](const boost::system::error_code& ec, size_t length) {
		if (ec) {
			server_->OnError(GetPtr(), ec);
			Close();
			return;
		}
		output_buffer_.consume(length);
		server_->OnWrite(GetPtr(), length);
		if (output_buffer_.size() > 0) {
			DoWrite();
		}
	});
}


void WebSocketSession::WriteAsync(std::string message) {
	size_t remain_size = output_buffer_.size();
	size_t size = boost::asio::buffer_copy(output_buffer_.prepare(message.length()), boost::asio::buffer(message));
	output_buffer_.commit(size);
	if (remain_size == 0) {
		DoWrite();
	}
}


