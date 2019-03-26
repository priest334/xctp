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

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void MdSpiHandler::OnFrontConnected() {
	CThostFtdcReqUserLoginField req = { 0 };
	StrSet(req.BrokerID, settings->ctp.broker_id_.c_str());
	StrSet(req.UserID, settings->ctp.user_id_.c_str());
	StrSet(req.Password, settings->ctp.user_password_.c_str());
	int retval = connector_->md_user_api_->ReqUserLogin(&req, 0);
}

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReason ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void MdSpiHandler::OnFrontDisconnected(int nReason) {
	//cout << "OnFrontDisconnected: "<< nReason << endl;
}

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
void MdSpiHandler::OnHeartBeatWarning(int nTimeLapse) {
	//cout << "OnHeartBeatWarning" << endl;
}

///��¼������Ӧ
void MdSpiHandler::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUserLogin: " << pRspInfo->ErrorMsg << endl;
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	//connector_->md_user_api_->SubscribeMarketData((char**)INS, sizeof(INS) / sizeof(INS[0]));

}

///�ǳ�������Ӧ
void MdSpiHandler::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUserLogout" << endl;
}

///����Ӧ��
void MdSpiHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspError: " << pRspInfo->ErrorMsg << endl;
}

///��������Ӧ��
void MdSpiHandler::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspSubMarketData: "<<pSpecificInstrument->InstrumentID << "--[" << pRspInfo->ErrorID << "]" << pRspInfo->ErrorMsg << endl;
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	//connector_->md_user_api_->SubscribeForQuoteRsp((char**)INS, sizeof(INS) / sizeof(INS[0]));
}

///ȡ����������Ӧ��
void MdSpiHandler::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUnSubMarketData" << endl;
}

///����ѯ��Ӧ��
void MdSpiHandler::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspSubForQuoteRsp: " << pSpecificInstrument->InstrumentID << "--[" << pRspInfo->ErrorID << "]" << pRspInfo->ErrorMsg << endl;
}

///ȡ������ѯ��Ӧ��
void MdSpiHandler::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	//cout << "OnRspUnSubForQuoteRsp" << endl;
}

///�������֪ͨ
void MdSpiHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	string message = Mapper_CThostFtdcDepthMarketDataField::JsonStr(*pDepthMarketData);
	std::cout << "OnRtnDepthMarketData: [" << message << "]" << std::endl;
	if (ctp_session) {
		ctp_session->PublishMarketData(pDepthMarketData->InstrumentID, message);
	}
}

///ѯ��֪ͨ
void MdSpiHandler::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
	//cout << "OnRtnForQuoteRsp" << endl;
}
