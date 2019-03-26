#pragma once

#include <string>
using std::string;

class CThostFtdcMdApi;
class MdSpiHandler;

class MdConnector {
	friend class MdSpiHandler;
public:
	MdConnector();
	~MdConnector();

public:
	void Start();
	void Run();
	void Clear();

	void SubscribeMarketData(const string& insid);
	void UnSubscribeMarketData(const string& insid);

private:
	CThostFtdcMdApi* md_user_api_;
	MdSpiHandler* md_spi_handler_;
};

