#pragma once


#include <list>
#include <vector>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>



class IOContextPool : public boost::noncopyable {
	typedef boost::shared_ptr<boost::asio::io_context> IOContextPtr;
	typedef boost::asio::executor_work_guard<boost::asio::io_context::executor_type> IOWorker;
public:
	explicit IOContextPool(std::size_t size);

	void Run();
	void Stop();

	boost::asio::io_context& Get();

private:
	std::vector<IOContextPtr> contexts_;
	std::list<IOWorker> workers_;
	std::size_t index_;
};

