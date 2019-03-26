#pragma once

#include "ThostFtdcUserApiStruct.h"
#include "mapper.h"

#define AddMember(cls, name, type) \
	members_[#name]=new ClassMember<cls>(type,offsetof(cls, name))


class Mapper_CThostFtdcDepthMarketDataField :
	public JsonMapper<CThostFtdcDepthMarketDataField>,
	public StaticMapper<Mapper_CThostFtdcDepthMarketDataField> {
public:
	void Resovle() {
		AddMember(CThostFtdcDepthMarketDataField, TradingDay, MapperType::MTARR);
		AddMember(CThostFtdcDepthMarketDataField, InstrumentID, MapperType::MTARR);
		AddMember(CThostFtdcDepthMarketDataField, ExchangeID, MapperType::MTARR);
		AddMember(CThostFtdcDepthMarketDataField, ExchangeInstID, MapperType::MTARR);
		AddMember(CThostFtdcDepthMarketDataField, LastPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, PreSettlementPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, PreClosePrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, PreOpenInterest, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, OpenPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, HighestPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, LowestPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, Volume, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, Turnover, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, OpenInterest, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, ClosePrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, SettlementPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, UpperLimitPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, LowerLimitPrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, PreDelta, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, CurrDelta, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, UpdateTime, MapperType::MTARR);
		AddMember(CThostFtdcDepthMarketDataField, UpdateMillisec, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, BidPrice1, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, BidVolume1, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, AskPrice1, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, AskVolume1, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, BidPrice2, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, BidVolume2, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, AskPrice2, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, AskVolume2, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, BidPrice3, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, BidVolume3, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, AskPrice3, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, AskVolume3, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, BidPrice4, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, BidVolume4, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, AskPrice4, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, AskVolume4, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, BidPrice5, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, BidVolume5, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, AskPrice5, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, AskVolume5, MapperType::MTINT);
		AddMember(CThostFtdcDepthMarketDataField, AveragePrice, MapperType::MTDBL);
		AddMember(CThostFtdcDepthMarketDataField, ActionDay, MapperType::MTARR);
	}
};




