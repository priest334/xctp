#pragma once

#include <string>
#include <map>
#include <boost/thread.hpp>


class MdHistory {
public:
	MdHistory();
	~MdHistory();

	void Save(const std::string& insid, const std::string& data);
	std::string Get(const std::string& insid);

private:
	std::map<std::string, std::string> history_;
	boost::mutex mutex_;
};

