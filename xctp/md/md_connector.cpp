#include "md_connector.h"
#include "ThostFtdcMdApi.h"
#include "md_spi_handler.h"
#include "../settings.h"
#include "str_helper.h"

MdConnector::MdConnector() : 
	md_user_api_(nullptr), 
	md_spi_handler_(nullptr) {
}

MdConnector::~MdConnector() {
	Clear();
}

void MdConnector::Start() {
	if (md_user_api_)
		return;

	md_user_api_ = CThostFtdcMdApi::CreateFtdcMdApi("./");
	md_spi_handler_ = new MdSpiHandler(this);
	md_user_api_->RegisterSpi(md_spi_handler_);
	md_user_api_->RegisterFront((char*)settings->ctp.market_front_.c_str());
	md_user_api_->Init();
	Run();
}

void MdConnector::Run() {
	md_user_api_->Join();
}

void MdConnector::Clear() {
	if (md_user_api_) {
		md_user_api_->Release();
		md_user_api_ = nullptr;
		delete md_spi_handler_;
		md_spi_handler_ = nullptr;
	}
}

void MdConnector::SubscribeMarketData(const string& insid) {
	char* ins[1] = { 0 };
	ins[0] = (char*)insid.c_str();
	md_user_api_->SubscribeMarketData(ins, 1);
}

void MdConnector::UnSubscribeMarketData(const string& insid) {
	char* ins[1] = { 0 };
	ins[0] = (char*)insid.c_str();
	md_user_api_->UnSubscribeMarketData(ins, 1);
}


