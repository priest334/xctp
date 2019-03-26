#include "io_context_pool.h"
#include <stdexcept>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>


IOContextPool::IOContextPool(std::size_t size) : index_(0) {
	if (size == 0) {
		throw std::runtime_error("io context pool size is 0");
	}
	for (std::size_t i = 0; i < size; i++) {
		IOContextPtr context(new boost::asio::io_context());
		contexts_.push_back(context);
		workers_.push_back(boost::asio::make_work_guard(*context));
	}
}


void IOContextPool::Run() {
	std::size_t i;
	std::vector<boost::shared_ptr<boost::thread> > threads;
	for (i = 0; i < contexts_.size(); i++) {
		boost::shared_ptr<boost::thread> thread(new boost::thread(
			boost::bind(&boost::asio::io_context::run, contexts_[i])));
		threads.push_back(thread);
	}

	for (i = 0; i < threads.size(); i++)
		threads[i]->join();
}

void IOContextPool::Stop() {
	for (std::size_t i = 0; i < contexts_.size(); i++)
		contexts_[i]->stop();
}

boost::asio::io_context& IOContextPool::Get() {
	boost::asio::io_context& context = *contexts_[index_++];
	if (index_ == contexts_.size())
		index_ = 0;
	return context;
}


