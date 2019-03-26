#include "md_history.h"


MdHistory::MdHistory() {
}


MdHistory::~MdHistory() {
}


void MdHistory::Save(const std::string& insid, const std::string& data) {
	mutex_.lock();
	history_.emplace(insid, data);
	mutex_.unlock();
}


std::string MdHistory::Get(const std::string& insid) {
	std::string str;
	mutex_.lock();
	auto iter = history_.find(insid);
	if (iter != history_.end()) {
		str = iter->second;
	}
	mutex_.unlock();
	return str;
}



