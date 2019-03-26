#include "md_spi_handler.h"
#include "md_connector.h"
#include <string.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "user_api_struct_mapper.h"
#include "../settings.h"
#include "str_helper.h"
#include "../ctp_session.h"


MdSpiHandler::MdSpiHandler(MdConnector* connector) : 
	connector_(connector)
{
}


MdSpiHandler::~MdSpiHandler()
{
}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void MdSpiHandler::OnFrontConnected() {
	CThostFtdcReqUserLoginField req = { 0 };
	StrSet(req.BrokerID, settings->ctp.broker_id_.c_str());
	StrSet(req.UserID, settings->ctp.user_id_.c_str());
	StrSet(req.Password, settings->ctp.user_password_.c_str());
	int retval = connector_->md_user_api_->ReqUserLogin(&req, 0);
}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void MdSpiHandler::OnFrontDisconnected(int nReason) {
	//cout << "OnFrontDisconnected: "<< nReason << endl;
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void MdSpiHandler::OnHeartBeatWarning(int nTimeLapse) {
	//cout << "OnHeartBeatWarning" << endl;
}

///登录请求响应
void MdSpiHandler::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUserLogin: " << pRspInfo->ErrorMsg << endl;
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	//connector_->md_user_api_->SubscribeMarketData((char**)INS, sizeof(INS) / sizeof(INS[0]));

}

///登出请求响应
void MdSpiHandler::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUserLogout" << endl;
}

///错误应答
void MdSpiHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspError: " << pRspInfo->ErrorMsg << endl;
}

///订阅行情应答
void MdSpiHandler::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspSubMarketData: "<<pSpecificInstrument->InstrumentID << "--[" << pRspInfo->ErrorID << "]" << pRspInfo->ErrorMsg << endl;
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	//connector_->md_user_api_->SubscribeForQuoteRsp((char**)INS, sizeof(INS) / sizeof(INS[0]));
}

///取消订阅行情应答
void MdSpiHandler::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUnSubMarketData" << endl;
}

///订阅询价应答
void MdSpiHandler::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspSubForQuoteRsp: " << pSpecificInstrument->InstrumentID << "--[" << pRspInfo->ErrorID << "]" << pRspInfo->ErrorMsg << endl;
}

///取消订阅询价应答
void MdSpiHandler::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUnSubForQuoteRsp" << endl;
}

///深度行情通知
void MdSpiHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	string message = Mapper_CThostFtdcDepthMarketDataField::JsonStr(*pDepthMarketData);
	std::cout << "OnRtnDepthMarketData: [" << message << "]" << std::endl;
	if (ctp_session) {
		ctp_session->PublishMarketData(pDepthMarketData->InstrumentID, message);
	}
}

///询价通知
void MdSpiHandler::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
	//cout << "OnRtnForQuoteRsp" << endl;
}
