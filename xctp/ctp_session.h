#pragma once

#include <map>
#include <string>
#include <set>
#include <shared_mutex>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "md/md_connector.h"
#include "md/md_history.h"

class CtpSession {
	typedef boost::shared_ptr<MdConnector> MdConnectorPtr;
public:
	CtpSession();
	~CtpSession();

	void Start();
	void StartThread();
	void Join();

	void Subscribe(const std::string& name, const std::string& insid);
	void Subscribe(const std::string& name, const std::set<std::string>& insid_list);
	void UnSubscribe(const std::string& name, const std::string& insid);
	void UnSubscribe(const std::string& name, const std::set<std::string>& insid_list);
	void PublishMarketData(const std::string& insid, const std::string& data);

private:
	std::map<std::string, std::set<std::string>> sub_ins_users_;
	std::shared_mutex mutex_;
	MdConnectorPtr md_connector_;
	boost::shared_ptr<boost::thread> md_thread_;
	MdHistory md_history_;
};


typedef boost::shared_ptr<CtpSession> CtpSessionPtr;
extern CtpSessionPtr ctp_session;


