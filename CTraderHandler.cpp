#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>
#include <json/json.h>
#include <comhelper.h>


/// 构造函数
CTraderHandler::CTraderHandler(Configure * pConfigure) {
    printf("CTraderHandler():被执行...\n");
    // 读取配置数据信息
    this->pConfigure = pConfigure;
    // 创建zmq通讯环境
    pContext = new zmq::context_t(1);
    pSender = new zmq::socket_t(*pContext, ZMQ_PUSH);
    pSender->bind(pConfigure->PushbackPipe);
}

/// 成功连接服务器消息
void CTraderHandler::OnFrontConnected() {
    printf("OnFrontConnected():被执行...\n");
    zmq::socket_t & sendder = *pSender;
    PushbackMessage message;
    message.requestID = "0";
    message.apiName = "OnFrontConnected";
    message.respInfo = "";
    message.send(sendder);
}

char buffer[1024];

/**********************************************************
*                   onRsp开头的方法                         *
***********************************************************/


///请求查询合约响应
void CTraderHandler::OnRspQryInstrument(
    CThostFtdcInstrumentField * pInstrument,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInstrument():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInstrument:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInstrument:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInstrument";

    /// 返回数据结构体转化json格式
    Json::Value json_pInstrument;
    if ( pInstrument != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInstrument["InstrumentID"] = pInstrument->InstrumentID;
        json_pInstrument["ExchangeID"] = pInstrument->ExchangeID;
        json_pInstrument["InstrumentName"] = pInstrument->InstrumentName;
        json_pInstrument["ExchangeInstID"] = pInstrument->ExchangeInstID;
        json_pInstrument["ProductID"] = pInstrument->ProductID;
        json_pInstrument["ProductClass"] = pInstrument->ProductClass;
        json_pInstrument["DeliveryYear"] = pInstrument->DeliveryYear;
        json_pInstrument["DeliveryMonth"] = pInstrument->DeliveryMonth;
        json_pInstrument["MaxMarketOrderVolume"] = pInstrument->MaxMarketOrderVolume;
        json_pInstrument["MinMarketOrderVolume"] = pInstrument->MinMarketOrderVolume;
        json_pInstrument["MaxLimitOrderVolume"] = pInstrument->MaxLimitOrderVolume;
        json_pInstrument["MinLimitOrderVolume"] = pInstrument->MinLimitOrderVolume;
        json_pInstrument["VolumeMultiple"] = pInstrument->VolumeMultiple;
        json_pInstrument["PriceTick"] = pInstrument->PriceTick;
        json_pInstrument["CreateDate"] = pInstrument->CreateDate;
        json_pInstrument["OpenDate"] = pInstrument->OpenDate;
        json_pInstrument["ExpireDate"] = pInstrument->ExpireDate;
        json_pInstrument["StartDelivDate"] = pInstrument->StartDelivDate;
        json_pInstrument["EndDelivDate"] = pInstrument->EndDelivDate;
        json_pInstrument["InstLifePhase"] = pInstrument->InstLifePhase;
        json_pInstrument["IsTrading"] = pInstrument->IsTrading;
        json_pInstrument["PositionType"] = pInstrument->PositionType;
        json_pInstrument["PositionDateType"] = pInstrument->PositionDateType;
        json_pInstrument["LongMarginRatio"] = pInstrument->LongMarginRatio;
        json_pInstrument["ShortMarginRatio"] = pInstrument->ShortMarginRatio;
        json_pInstrument["MaxMarginSideAlgorithm"] = pInstrument->MaxMarginSideAlgorithm;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInstrument;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInstrument";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询投资者结算结果响应
void CTraderHandler::OnRspQrySettlementInfo(
    CThostFtdcSettlementInfoField * pSettlementInfo,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQrySettlementInfo():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQrySettlementInfo:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQrySettlementInfo:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQrySettlementInfo";

    /// 返回数据结构体转化json格式
    Json::Value json_pSettlementInfo;
    if ( pSettlementInfo != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pSettlementInfo["TradingDay"] = pSettlementInfo->TradingDay;
        json_pSettlementInfo["SettlementID"] = pSettlementInfo->SettlementID;
        json_pSettlementInfo["BrokerID"] = pSettlementInfo->BrokerID;
        json_pSettlementInfo["InvestorID"] = pSettlementInfo->InvestorID;
        json_pSettlementInfo["SequenceNo"] = pSettlementInfo->SequenceNo;
        json_pSettlementInfo["Content"] = pSettlementInfo->Content;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pSettlementInfo;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQrySettlementInfo";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///预埋单录入请求响应
void CTraderHandler::OnRspParkedOrderInsert(
    CThostFtdcParkedOrderField * pParkedOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspParkedOrderInsert():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspParkedOrderInsert:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspParkedOrderInsert:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspParkedOrderInsert";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrder;
    if ( pParkedOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pParkedOrder["BrokerID"] = pParkedOrder->BrokerID;
        json_pParkedOrder["InvestorID"] = pParkedOrder->InvestorID;
        json_pParkedOrder["InstrumentID"] = pParkedOrder->InstrumentID;
        json_pParkedOrder["OrderRef"] = pParkedOrder->OrderRef;
        json_pParkedOrder["UserID"] = pParkedOrder->UserID;
        json_pParkedOrder["OrderPriceType"] = pParkedOrder->OrderPriceType;
        json_pParkedOrder["Direction"] = pParkedOrder->Direction;
        json_pParkedOrder["CombOffsetFlag"] = pParkedOrder->CombOffsetFlag;
        json_pParkedOrder["CombHedgeFlag"] = pParkedOrder->CombHedgeFlag;
        json_pParkedOrder["LimitPrice"] = pParkedOrder->LimitPrice;
        json_pParkedOrder["VolumeTotalOriginal"] = pParkedOrder->VolumeTotalOriginal;
        json_pParkedOrder["TimeCondition"] = pParkedOrder->TimeCondition;
        json_pParkedOrder["GTDDate"] = pParkedOrder->GTDDate;
        json_pParkedOrder["VolumeCondition"] = pParkedOrder->VolumeCondition;
        json_pParkedOrder["MinVolume"] = pParkedOrder->MinVolume;
        json_pParkedOrder["ContingentCondition"] = pParkedOrder->ContingentCondition;
        json_pParkedOrder["StopPrice"] = pParkedOrder->StopPrice;
        json_pParkedOrder["ForceCloseReason"] = pParkedOrder->ForceCloseReason;
        json_pParkedOrder["IsAutoSuspend"] = pParkedOrder->IsAutoSuspend;
        json_pParkedOrder["BusinessUnit"] = pParkedOrder->BusinessUnit;
        json_pParkedOrder["RequestID"] = pParkedOrder->RequestID;
        json_pParkedOrder["UserForceClose"] = pParkedOrder->UserForceClose;
        json_pParkedOrder["ExchangeID"] = pParkedOrder->ExchangeID;
        json_pParkedOrder["ParkedOrderID"] = pParkedOrder->ParkedOrderID;
        json_pParkedOrder["UserType"] = pParkedOrder->UserType;
        json_pParkedOrder["Status"] = pParkedOrder->Status;
        json_pParkedOrder["ErrorID"] = pParkedOrder->ErrorID;
        json_pParkedOrder["ErrorMsg"] = pParkedOrder->ErrorMsg;
        json_pParkedOrder["IsSwapOrder"] = pParkedOrder->IsSwapOrder;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pParkedOrder;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspParkedOrderInsert";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询交易所响应
void CTraderHandler::OnRspQryExchange(
    CThostFtdcExchangeField * pExchange,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryExchange():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryExchange:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryExchange:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchange";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchange;
    if ( pExchange != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pExchange["ExchangeID"] = pExchange->ExchangeID;
        json_pExchange["ExchangeName"] = pExchange->ExchangeName;
        json_pExchange["ExchangeProperty"] = pExchange->ExchangeProperty;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pExchange;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchange";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///报单操作请求响应
void CTraderHandler::OnRspOrderAction(
    CThostFtdcInputOrderActionField * pInputOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspOrderAction():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspOrderAction:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspOrderAction:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pInputOrderAction;
    if ( pInputOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInputOrderAction["BrokerID"] = pInputOrderAction->BrokerID;
        json_pInputOrderAction["InvestorID"] = pInputOrderAction->InvestorID;
        json_pInputOrderAction["OrderActionRef"] = pInputOrderAction->OrderActionRef;
        json_pInputOrderAction["OrderRef"] = pInputOrderAction->OrderRef;
        json_pInputOrderAction["RequestID"] = pInputOrderAction->RequestID;
        json_pInputOrderAction["FrontID"] = pInputOrderAction->FrontID;
        json_pInputOrderAction["SessionID"] = pInputOrderAction->SessionID;
        json_pInputOrderAction["ExchangeID"] = pInputOrderAction->ExchangeID;
        json_pInputOrderAction["OrderSysID"] = pInputOrderAction->OrderSysID;
        json_pInputOrderAction["ActionFlag"] = pInputOrderAction->ActionFlag;
        json_pInputOrderAction["LimitPrice"] = pInputOrderAction->LimitPrice;
        json_pInputOrderAction["VolumeChange"] = pInputOrderAction->VolumeChange;
        json_pInputOrderAction["UserID"] = pInputOrderAction->UserID;
        json_pInputOrderAction["InstrumentID"] = pInputOrderAction->InstrumentID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInputOrderAction;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询投资者响应
void CTraderHandler::OnRspQryInvestor(
    CThostFtdcInvestorField * pInvestor,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInvestor():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInvestor:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInvestor:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestor";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestor;
    if ( pInvestor != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInvestor["InvestorID"] = pInvestor->InvestorID;
        json_pInvestor["BrokerID"] = pInvestor->BrokerID;
        json_pInvestor["InvestorGroupID"] = pInvestor->InvestorGroupID;
        json_pInvestor["InvestorName"] = pInvestor->InvestorName;
        json_pInvestor["IdentifiedCardType"] = pInvestor->IdentifiedCardType;
        json_pInvestor["IdentifiedCardNo"] = pInvestor->IdentifiedCardNo;
        json_pInvestor["IsActive"] = pInvestor->IsActive;
        json_pInvestor["Telephone"] = pInvestor->Telephone;
        json_pInvestor["Address"] = pInvestor->Address;
        json_pInvestor["OpenDate"] = pInvestor->OpenDate;
        json_pInvestor["Mobile"] = pInvestor->Mobile;
        json_pInvestor["CommModelID"] = pInvestor->CommModelID;
        json_pInvestor["MarginModelID"] = pInvestor->MarginModelID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInvestor;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestor";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///删除预埋单响应
void CTraderHandler::OnRspRemoveParkedOrder(
    CThostFtdcRemoveParkedOrderField * pRemoveParkedOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspRemoveParkedOrder():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspRemoveParkedOrder:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspRemoveParkedOrder:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspRemoveParkedOrder";

    /// 返回数据结构体转化json格式
    Json::Value json_pRemoveParkedOrder;
    if ( pRemoveParkedOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pRemoveParkedOrder["BrokerID"] = pRemoveParkedOrder->BrokerID;
        json_pRemoveParkedOrder["InvestorID"] = pRemoveParkedOrder->InvestorID;
        json_pRemoveParkedOrder["ParkedOrderID"] = pRemoveParkedOrder->ParkedOrderID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRemoveParkedOrder;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspRemoveParkedOrder";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询投资者品种/跨品种保证金响应
void CTraderHandler::OnRspQryInvestorProductGroupMargin(
    CThostFtdcInvestorProductGroupMarginField * pInvestorProductGroupMargin,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInvestorProductGroupMargin():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInvestorProductGroupMargin:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInvestorProductGroupMargin:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorProductGroupMargin";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorProductGroupMargin;
    if ( pInvestorProductGroupMargin != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInvestorProductGroupMargin["ProductGroupID"] = pInvestorProductGroupMargin->ProductGroupID;
        json_pInvestorProductGroupMargin["BrokerID"] = pInvestorProductGroupMargin->BrokerID;
        json_pInvestorProductGroupMargin["InvestorID"] = pInvestorProductGroupMargin->InvestorID;
        json_pInvestorProductGroupMargin["TradingDay"] = pInvestorProductGroupMargin->TradingDay;
        json_pInvestorProductGroupMargin["SettlementID"] = pInvestorProductGroupMargin->SettlementID;
        json_pInvestorProductGroupMargin["FrozenMargin"] = pInvestorProductGroupMargin->FrozenMargin;
        json_pInvestorProductGroupMargin["LongFrozenMargin"] = pInvestorProductGroupMargin->LongFrozenMargin;
        json_pInvestorProductGroupMargin["ShortFrozenMargin"] = pInvestorProductGroupMargin->ShortFrozenMargin;
        json_pInvestorProductGroupMargin["UseMargin"] = pInvestorProductGroupMargin->UseMargin;
        json_pInvestorProductGroupMargin["LongUseMargin"] = pInvestorProductGroupMargin->LongUseMargin;
        json_pInvestorProductGroupMargin["ShortUseMargin"] = pInvestorProductGroupMargin->ShortUseMargin;
        json_pInvestorProductGroupMargin["ExchMargin"] = pInvestorProductGroupMargin->ExchMargin;
        json_pInvestorProductGroupMargin["LongExchMargin"] = pInvestorProductGroupMargin->LongExchMargin;
        json_pInvestorProductGroupMargin["ShortExchMargin"] = pInvestorProductGroupMargin->ShortExchMargin;
        json_pInvestorProductGroupMargin["CloseProfit"] = pInvestorProductGroupMargin->CloseProfit;
        json_pInvestorProductGroupMargin["FrozenCommission"] = pInvestorProductGroupMargin->FrozenCommission;
        json_pInvestorProductGroupMargin["Commission"] = pInvestorProductGroupMargin->Commission;
        json_pInvestorProductGroupMargin["FrozenCash"] = pInvestorProductGroupMargin->FrozenCash;
        json_pInvestorProductGroupMargin["CashIn"] = pInvestorProductGroupMargin->CashIn;
        json_pInvestorProductGroupMargin["PositionProfit"] = pInvestorProductGroupMargin->PositionProfit;
        json_pInvestorProductGroupMargin["OffsetAmount"] = pInvestorProductGroupMargin->OffsetAmount;
        json_pInvestorProductGroupMargin["LongOffsetAmount"] = pInvestorProductGroupMargin->LongOffsetAmount;
        json_pInvestorProductGroupMargin["ShortOffsetAmount"] = pInvestorProductGroupMargin->ShortOffsetAmount;
        json_pInvestorProductGroupMargin["ExchOffsetAmount"] = pInvestorProductGroupMargin->ExchOffsetAmount;
        json_pInvestorProductGroupMargin["LongExchOffsetAmount"] = pInvestorProductGroupMargin->LongExchOffsetAmount;
        json_pInvestorProductGroupMargin["ShortExchOffsetAmount"] = pInvestorProductGroupMargin->ShortExchOffsetAmount;
        json_pInvestorProductGroupMargin["HedgeFlag"] = pInvestorProductGroupMargin->HedgeFlag;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInvestorProductGroupMargin;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorProductGroupMargin";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询转帐银行响应
void CTraderHandler::OnRspQryTransferBank(
    CThostFtdcTransferBankField * pTransferBank,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryTransferBank():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryTransferBank:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryTransferBank:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTransferBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pTransferBank;
    if ( pTransferBank != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pTransferBank["BankID"] = pTransferBank->BankID;
        json_pTransferBank["BankBrchID"] = pTransferBank->BankBrchID;
        json_pTransferBank["BankName"] = pTransferBank->BankName;
        json_pTransferBank["IsActive"] = pTransferBank->IsActive;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTransferBank;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTransferBank";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询经纪公司交易算法响应
void CTraderHandler::OnRspQryBrokerTradingAlgos(
    CThostFtdcBrokerTradingAlgosField * pBrokerTradingAlgos,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryBrokerTradingAlgos():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryBrokerTradingAlgos:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryBrokerTradingAlgos:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryBrokerTradingAlgos";

    /// 返回数据结构体转化json格式
    Json::Value json_pBrokerTradingAlgos;
    if ( pBrokerTradingAlgos != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pBrokerTradingAlgos["BrokerID"] = pBrokerTradingAlgos->BrokerID;
        json_pBrokerTradingAlgos["ExchangeID"] = pBrokerTradingAlgos->ExchangeID;
        json_pBrokerTradingAlgos["InstrumentID"] = pBrokerTradingAlgos->InstrumentID;
        json_pBrokerTradingAlgos["HandlePositionAlgoID"] = pBrokerTradingAlgos->HandlePositionAlgoID;
        json_pBrokerTradingAlgos["FindMarginRateAlgoID"] = pBrokerTradingAlgos->FindMarginRateAlgoID;
        json_pBrokerTradingAlgos["HandleTradingAccountAlgoID"] = pBrokerTradingAlgos->HandleTradingAccountAlgoID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pBrokerTradingAlgos;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryBrokerTradingAlgos";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询产品响应
void CTraderHandler::OnRspQryProduct(
    CThostFtdcProductField * pProduct,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryProduct():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryProduct:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryProduct:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryProduct";

    /// 返回数据结构体转化json格式
    Json::Value json_pProduct;
    if ( pProduct != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pProduct["ProductID"] = pProduct->ProductID;
        json_pProduct["ProductName"] = pProduct->ProductName;
        json_pProduct["ExchangeID"] = pProduct->ExchangeID;
        json_pProduct["ProductClass"] = pProduct->ProductClass;
        json_pProduct["VolumeMultiple"] = pProduct->VolumeMultiple;
        json_pProduct["PriceTick"] = pProduct->PriceTick;
        json_pProduct["MaxMarketOrderVolume"] = pProduct->MaxMarketOrderVolume;
        json_pProduct["MinMarketOrderVolume"] = pProduct->MinMarketOrderVolume;
        json_pProduct["MaxLimitOrderVolume"] = pProduct->MaxLimitOrderVolume;
        json_pProduct["MinLimitOrderVolume"] = pProduct->MinLimitOrderVolume;
        json_pProduct["PositionType"] = pProduct->PositionType;
        json_pProduct["PositionDateType"] = pProduct->PositionDateType;
        json_pProduct["CloseDealType"] = pProduct->CloseDealType;
        json_pProduct["TradeCurrencyID"] = pProduct->TradeCurrencyID;
        json_pProduct["MortgageFundUseRange"] = pProduct->MortgageFundUseRange;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pProduct;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryProduct";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询合约保证金率响应
void CTraderHandler::OnRspQryInstrumentMarginRate(
    CThostFtdcInstrumentMarginRateField * pInstrumentMarginRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInstrumentMarginRate():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInstrumentMarginRate:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInstrumentMarginRate:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInstrumentMarginRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pInstrumentMarginRate;
    if ( pInstrumentMarginRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInstrumentMarginRate["InstrumentID"] = pInstrumentMarginRate->InstrumentID;
        json_pInstrumentMarginRate["InvestorRange"] = pInstrumentMarginRate->InvestorRange;
        json_pInstrumentMarginRate["BrokerID"] = pInstrumentMarginRate->BrokerID;
        json_pInstrumentMarginRate["InvestorID"] = pInstrumentMarginRate->InvestorID;
        json_pInstrumentMarginRate["HedgeFlag"] = pInstrumentMarginRate->HedgeFlag;
        json_pInstrumentMarginRate["LongMarginRatioByMoney"] = pInstrumentMarginRate->LongMarginRatioByMoney;
        json_pInstrumentMarginRate["LongMarginRatioByVolume"] = pInstrumentMarginRate->LongMarginRatioByVolume;
        json_pInstrumentMarginRate["ShortMarginRatioByMoney"] = pInstrumentMarginRate->ShortMarginRatioByMoney;
        json_pInstrumentMarginRate["ShortMarginRatioByVolume"] = pInstrumentMarginRate->ShortMarginRatioByVolume;
        json_pInstrumentMarginRate["IsRelative"] = pInstrumentMarginRate->IsRelative;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInstrumentMarginRate;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInstrumentMarginRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///查询保证金监管系统经纪公司资金账户密钥响应
void CTraderHandler::OnRspQryCFMMCTradingAccountKey(
    CThostFtdcCFMMCTradingAccountKeyField * pCFMMCTradingAccountKey,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryCFMMCTradingAccountKey():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryCFMMCTradingAccountKey:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryCFMMCTradingAccountKey:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryCFMMCTradingAccountKey";

    /// 返回数据结构体转化json格式
    Json::Value json_pCFMMCTradingAccountKey;
    if ( pCFMMCTradingAccountKey != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pCFMMCTradingAccountKey["BrokerID"] = pCFMMCTradingAccountKey->BrokerID;
        json_pCFMMCTradingAccountKey["ParticipantID"] = pCFMMCTradingAccountKey->ParticipantID;
        json_pCFMMCTradingAccountKey["AccountID"] = pCFMMCTradingAccountKey->AccountID;
        json_pCFMMCTradingAccountKey["KeyID"] = pCFMMCTradingAccountKey->KeyID;
        json_pCFMMCTradingAccountKey["CurrentKey"] = pCFMMCTradingAccountKey->CurrentKey;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pCFMMCTradingAccountKey;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryCFMMCTradingAccountKey";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///登录请求响应
void CTraderHandler::OnRspUserLogin(
    CThostFtdcRspUserLoginField * pRspUserLogin,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspUserLogin():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspUserLogin:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspUserLogin:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserLogin";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspUserLogin;
    if ( pRspUserLogin != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pRspUserLogin["TradingDay"] = pRspUserLogin->TradingDay;
        json_pRspUserLogin["LoginTime"] = pRspUserLogin->LoginTime;
        json_pRspUserLogin["BrokerID"] = pRspUserLogin->BrokerID;
        json_pRspUserLogin["UserID"] = pRspUserLogin->UserID;
        json_pRspUserLogin["SystemName"] = pRspUserLogin->SystemName;
        json_pRspUserLogin["FrontID"] = pRspUserLogin->FrontID;
        json_pRspUserLogin["SessionID"] = pRspUserLogin->SessionID;
        json_pRspUserLogin["MaxOrderRef"] = pRspUserLogin->MaxOrderRef;
        json_pRspUserLogin["SHFETime"] = pRspUserLogin->SHFETime;
        json_pRspUserLogin["DCETime"] = pRspUserLogin->DCETime;
        json_pRspUserLogin["CZCETime"] = pRspUserLogin->CZCETime;
        json_pRspUserLogin["FFEXTime"] = pRspUserLogin->FFEXTime;
        json_pRspUserLogin["INETime"] = pRspUserLogin->INETime;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspUserLogin;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserLogin";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///期货发起期货资金转银行应答
void CTraderHandler::OnRspFromFutureToBankByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspFromFutureToBankByFuture():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspFromFutureToBankByFuture:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspFromFutureToBankByFuture:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspFromFutureToBankByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqTransfer;
    if ( pReqTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pReqTransfer["TradeCode"] = pReqTransfer->TradeCode;
        json_pReqTransfer["BankID"] = pReqTransfer->BankID;
        json_pReqTransfer["BankBranchID"] = pReqTransfer->BankBranchID;
        json_pReqTransfer["BrokerID"] = pReqTransfer->BrokerID;
        json_pReqTransfer["BrokerBranchID"] = pReqTransfer->BrokerBranchID;
        json_pReqTransfer["TradeDate"] = pReqTransfer->TradeDate;
        json_pReqTransfer["TradeTime"] = pReqTransfer->TradeTime;
        json_pReqTransfer["BankSerial"] = pReqTransfer->BankSerial;
        json_pReqTransfer["TradingDay"] = pReqTransfer->TradingDay;
        json_pReqTransfer["PlateSerial"] = pReqTransfer->PlateSerial;
        json_pReqTransfer["LastFragment"] = pReqTransfer->LastFragment;
        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;
        json_pReqTransfer["CustomerName"] = pReqTransfer->CustomerName;
        json_pReqTransfer["IdCardType"] = pReqTransfer->IdCardType;
        json_pReqTransfer["IdentifiedCardNo"] = pReqTransfer->IdentifiedCardNo;
        json_pReqTransfer["CustType"] = pReqTransfer->CustType;
        json_pReqTransfer["BankAccount"] = pReqTransfer->BankAccount;
        json_pReqTransfer["BankPassWord"] = pReqTransfer->BankPassWord;
        json_pReqTransfer["AccountID"] = pReqTransfer->AccountID;
        json_pReqTransfer["Password"] = pReqTransfer->Password;
        json_pReqTransfer["InstallID"] = pReqTransfer->InstallID;
        json_pReqTransfer["FutureSerial"] = pReqTransfer->FutureSerial;
        json_pReqTransfer["UserID"] = pReqTransfer->UserID;
        json_pReqTransfer["VerifyCertNoFlag"] = pReqTransfer->VerifyCertNoFlag;
        json_pReqTransfer["CurrencyID"] = pReqTransfer->CurrencyID;
        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;
        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;
        json_pReqTransfer["FeePayFlag"] = pReqTransfer->FeePayFlag;
        json_pReqTransfer["CustFee"] = pReqTransfer->CustFee;
        json_pReqTransfer["BrokerFee"] = pReqTransfer->BrokerFee;
        json_pReqTransfer["Message"] = pReqTransfer->Message;
        json_pReqTransfer["Digest"] = pReqTransfer->Digest;
        json_pReqTransfer["BankAccType"] = pReqTransfer->BankAccType;
        json_pReqTransfer["DeviceID"] = pReqTransfer->DeviceID;
        json_pReqTransfer["BankSecuAccType"] = pReqTransfer->BankSecuAccType;
        json_pReqTransfer["BrokerIDByBank"] = pReqTransfer->BrokerIDByBank;
        json_pReqTransfer["BankSecuAcc"] = pReqTransfer->BankSecuAcc;
        json_pReqTransfer["BankPwdFlag"] = pReqTransfer->BankPwdFlag;
        json_pReqTransfer["SecuPwdFlag"] = pReqTransfer->SecuPwdFlag;
        json_pReqTransfer["OperNo"] = pReqTransfer->OperNo;
        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;
        json_pReqTransfer["TID"] = pReqTransfer->TID;
        json_pReqTransfer["TransferStatus"] = pReqTransfer->TransferStatus;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqTransfer;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspFromFutureToBankByFuture";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询监控中心用户令牌
void CTraderHandler::OnRspQueryCFMMCTradingAccountToken(
    CThostFtdcQueryCFMMCTradingAccountTokenField * pQueryCFMMCTradingAccountToken,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQueryCFMMCTradingAccountToken():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQueryCFMMCTradingAccountToken:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQueryCFMMCTradingAccountToken:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQueryCFMMCTradingAccountToken";

    /// 返回数据结构体转化json格式
    Json::Value json_pQueryCFMMCTradingAccountToken;
    if ( pQueryCFMMCTradingAccountToken != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pQueryCFMMCTradingAccountToken["BrokerID"] = pQueryCFMMCTradingAccountToken->BrokerID;
        json_pQueryCFMMCTradingAccountToken["InvestorID"] = pQueryCFMMCTradingAccountToken->InvestorID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pQueryCFMMCTradingAccountToken;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQueryCFMMCTradingAccountToken";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询签约银行响应
void CTraderHandler::OnRspQryContractBank(
    CThostFtdcContractBankField * pContractBank,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryContractBank():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryContractBank:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryContractBank:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryContractBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pContractBank;
    if ( pContractBank != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pContractBank["BrokerID"] = pContractBank->BrokerID;
        json_pContractBank["BankID"] = pContractBank->BankID;
        json_pContractBank["BankBrchID"] = pContractBank->BankBrchID;
        json_pContractBank["BankName"] = pContractBank->BankName;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pContractBank;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryContractBank";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///报单录入请求响应
void CTraderHandler::OnRspOrderInsert(
    CThostFtdcInputOrderField * pInputOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspOrderInsert():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspOrderInsert:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspOrderInsert:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspOrderInsert";

    /// 返回数据结构体转化json格式
    Json::Value json_pInputOrder;
    if ( pInputOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInputOrder["BrokerID"] = pInputOrder->BrokerID;
        json_pInputOrder["InvestorID"] = pInputOrder->InvestorID;
        json_pInputOrder["InstrumentID"] = pInputOrder->InstrumentID;
        json_pInputOrder["OrderRef"] = pInputOrder->OrderRef;
        json_pInputOrder["UserID"] = pInputOrder->UserID;
        json_pInputOrder["OrderPriceType"] = pInputOrder->OrderPriceType;
        json_pInputOrder["Direction"] = pInputOrder->Direction;
        json_pInputOrder["CombOffsetFlag"] = pInputOrder->CombOffsetFlag;
        json_pInputOrder["CombHedgeFlag"] = pInputOrder->CombHedgeFlag;
        json_pInputOrder["LimitPrice"] = pInputOrder->LimitPrice;
        json_pInputOrder["VolumeTotalOriginal"] = pInputOrder->VolumeTotalOriginal;
        json_pInputOrder["TimeCondition"] = pInputOrder->TimeCondition;
        json_pInputOrder["GTDDate"] = pInputOrder->GTDDate;
        json_pInputOrder["VolumeCondition"] = pInputOrder->VolumeCondition;
        json_pInputOrder["MinVolume"] = pInputOrder->MinVolume;
        json_pInputOrder["ContingentCondition"] = pInputOrder->ContingentCondition;
        json_pInputOrder["StopPrice"] = pInputOrder->StopPrice;
        json_pInputOrder["ForceCloseReason"] = pInputOrder->ForceCloseReason;
        json_pInputOrder["IsAutoSuspend"] = pInputOrder->IsAutoSuspend;
        json_pInputOrder["BusinessUnit"] = pInputOrder->BusinessUnit;
        json_pInputOrder["RequestID"] = pInputOrder->RequestID;
        json_pInputOrder["UserForceClose"] = pInputOrder->UserForceClose;
        json_pInputOrder["IsSwapOrder"] = pInputOrder->IsSwapOrder;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInputOrder;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspOrderInsert";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询仓单折抵信息响应
void CTraderHandler::OnRspQryEWarrantOffset(
    CThostFtdcEWarrantOffsetField * pEWarrantOffset,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryEWarrantOffset():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryEWarrantOffset:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryEWarrantOffset:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryEWarrantOffset";

    /// 返回数据结构体转化json格式
    Json::Value json_pEWarrantOffset;
    if ( pEWarrantOffset != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pEWarrantOffset["TradingDay"] = pEWarrantOffset->TradingDay;
        json_pEWarrantOffset["BrokerID"] = pEWarrantOffset->BrokerID;
        json_pEWarrantOffset["InvestorID"] = pEWarrantOffset->InvestorID;
        json_pEWarrantOffset["ExchangeID"] = pEWarrantOffset->ExchangeID;
        json_pEWarrantOffset["InstrumentID"] = pEWarrantOffset->InstrumentID;
        json_pEWarrantOffset["Direction"] = pEWarrantOffset->Direction;
        json_pEWarrantOffset["HedgeFlag"] = pEWarrantOffset->HedgeFlag;
        json_pEWarrantOffset["Volume"] = pEWarrantOffset->Volume;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pEWarrantOffset;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryEWarrantOffset";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///用户口令更新请求响应
void CTraderHandler::OnRspUserPasswordUpdate(
    CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspUserPasswordUpdate():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspUserPasswordUpdate:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspUserPasswordUpdate:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserPasswordUpdate";

    /// 返回数据结构体转化json格式
    Json::Value json_pUserPasswordUpdate;
    if ( pUserPasswordUpdate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pUserPasswordUpdate["BrokerID"] = pUserPasswordUpdate->BrokerID;
        json_pUserPasswordUpdate["UserID"] = pUserPasswordUpdate->UserID;
        json_pUserPasswordUpdate["OldPassword"] = pUserPasswordUpdate->OldPassword;
        json_pUserPasswordUpdate["NewPassword"] = pUserPasswordUpdate->NewPassword;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pUserPasswordUpdate;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserPasswordUpdate";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询交易所调整保证金率响应
void CTraderHandler::OnRspQryExchangeMarginRateAdjust(
    CThostFtdcExchangeMarginRateAdjustField * pExchangeMarginRateAdjust,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryExchangeMarginRateAdjust():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryExchangeMarginRateAdjust:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryExchangeMarginRateAdjust:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchangeMarginRateAdjust";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchangeMarginRateAdjust;
    if ( pExchangeMarginRateAdjust != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pExchangeMarginRateAdjust["BrokerID"] = pExchangeMarginRateAdjust->BrokerID;
        json_pExchangeMarginRateAdjust["InstrumentID"] = pExchangeMarginRateAdjust->InstrumentID;
        json_pExchangeMarginRateAdjust["HedgeFlag"] = pExchangeMarginRateAdjust->HedgeFlag;
        json_pExchangeMarginRateAdjust["LongMarginRatioByMoney"] = pExchangeMarginRateAdjust->LongMarginRatioByMoney;
        json_pExchangeMarginRateAdjust["LongMarginRatioByVolume"] = pExchangeMarginRateAdjust->LongMarginRatioByVolume;
        json_pExchangeMarginRateAdjust["ShortMarginRatioByMoney"] = pExchangeMarginRateAdjust->ShortMarginRatioByMoney;
        json_pExchangeMarginRateAdjust["ShortMarginRatioByVolume"] = pExchangeMarginRateAdjust->ShortMarginRatioByVolume;
        json_pExchangeMarginRateAdjust["ExchLongMarginRatioByMoney"] = pExchangeMarginRateAdjust->ExchLongMarginRatioByMoney;
        json_pExchangeMarginRateAdjust["ExchLongMarginRatioByVolume"] = pExchangeMarginRateAdjust->ExchLongMarginRatioByVolume;
        json_pExchangeMarginRateAdjust["ExchShortMarginRatioByMoney"] = pExchangeMarginRateAdjust->ExchShortMarginRatioByMoney;
        json_pExchangeMarginRateAdjust["ExchShortMarginRatioByVolume"] = pExchangeMarginRateAdjust->ExchShortMarginRatioByVolume;
        json_pExchangeMarginRateAdjust["NoLongMarginRatioByMoney"] = pExchangeMarginRateAdjust->NoLongMarginRatioByMoney;
        json_pExchangeMarginRateAdjust["NoLongMarginRatioByVolume"] = pExchangeMarginRateAdjust->NoLongMarginRatioByVolume;
        json_pExchangeMarginRateAdjust["NoShortMarginRatioByMoney"] = pExchangeMarginRateAdjust->NoShortMarginRatioByMoney;
        json_pExchangeMarginRateAdjust["NoShortMarginRatioByVolume"] = pExchangeMarginRateAdjust->NoShortMarginRatioByVolume;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pExchangeMarginRateAdjust;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchangeMarginRateAdjust";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///期货发起银行资金转期货应答
void CTraderHandler::OnRspFromBankToFutureByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspFromBankToFutureByFuture():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspFromBankToFutureByFuture:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspFromBankToFutureByFuture:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspFromBankToFutureByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqTransfer;
    if ( pReqTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pReqTransfer["TradeCode"] = pReqTransfer->TradeCode;
        json_pReqTransfer["BankID"] = pReqTransfer->BankID;
        json_pReqTransfer["BankBranchID"] = pReqTransfer->BankBranchID;
        json_pReqTransfer["BrokerID"] = pReqTransfer->BrokerID;
        json_pReqTransfer["BrokerBranchID"] = pReqTransfer->BrokerBranchID;
        json_pReqTransfer["TradeDate"] = pReqTransfer->TradeDate;
        json_pReqTransfer["TradeTime"] = pReqTransfer->TradeTime;
        json_pReqTransfer["BankSerial"] = pReqTransfer->BankSerial;
        json_pReqTransfer["TradingDay"] = pReqTransfer->TradingDay;
        json_pReqTransfer["PlateSerial"] = pReqTransfer->PlateSerial;
        json_pReqTransfer["LastFragment"] = pReqTransfer->LastFragment;
        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;
        json_pReqTransfer["CustomerName"] = pReqTransfer->CustomerName;
        json_pReqTransfer["IdCardType"] = pReqTransfer->IdCardType;
        json_pReqTransfer["IdentifiedCardNo"] = pReqTransfer->IdentifiedCardNo;
        json_pReqTransfer["CustType"] = pReqTransfer->CustType;
        json_pReqTransfer["BankAccount"] = pReqTransfer->BankAccount;
        json_pReqTransfer["BankPassWord"] = pReqTransfer->BankPassWord;
        json_pReqTransfer["AccountID"] = pReqTransfer->AccountID;
        json_pReqTransfer["Password"] = pReqTransfer->Password;
        json_pReqTransfer["InstallID"] = pReqTransfer->InstallID;
        json_pReqTransfer["FutureSerial"] = pReqTransfer->FutureSerial;
        json_pReqTransfer["UserID"] = pReqTransfer->UserID;
        json_pReqTransfer["VerifyCertNoFlag"] = pReqTransfer->VerifyCertNoFlag;
        json_pReqTransfer["CurrencyID"] = pReqTransfer->CurrencyID;
        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;
        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;
        json_pReqTransfer["FeePayFlag"] = pReqTransfer->FeePayFlag;
        json_pReqTransfer["CustFee"] = pReqTransfer->CustFee;
        json_pReqTransfer["BrokerFee"] = pReqTransfer->BrokerFee;
        json_pReqTransfer["Message"] = pReqTransfer->Message;
        json_pReqTransfer["Digest"] = pReqTransfer->Digest;
        json_pReqTransfer["BankAccType"] = pReqTransfer->BankAccType;
        json_pReqTransfer["DeviceID"] = pReqTransfer->DeviceID;
        json_pReqTransfer["BankSecuAccType"] = pReqTransfer->BankSecuAccType;
        json_pReqTransfer["BrokerIDByBank"] = pReqTransfer->BrokerIDByBank;
        json_pReqTransfer["BankSecuAcc"] = pReqTransfer->BankSecuAcc;
        json_pReqTransfer["BankPwdFlag"] = pReqTransfer->BankPwdFlag;
        json_pReqTransfer["SecuPwdFlag"] = pReqTransfer->SecuPwdFlag;
        json_pReqTransfer["OperNo"] = pReqTransfer->OperNo;
        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;
        json_pReqTransfer["TID"] = pReqTransfer->TID;
        json_pReqTransfer["TransferStatus"] = pReqTransfer->TransferStatus;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqTransfer;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspFromBankToFutureByFuture";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询投资者持仓明细响应
void CTraderHandler::OnRspQryInvestorPositionCombineDetail(
    CThostFtdcInvestorPositionCombineDetailField * pInvestorPositionCombineDetail,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInvestorPositionCombineDetail():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInvestorPositionCombineDetail:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInvestorPositionCombineDetail:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorPositionCombineDetail";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorPositionCombineDetail;
    if ( pInvestorPositionCombineDetail != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInvestorPositionCombineDetail["TradingDay"] = pInvestorPositionCombineDetail->TradingDay;
        json_pInvestorPositionCombineDetail["OpenDate"] = pInvestorPositionCombineDetail->OpenDate;
        json_pInvestorPositionCombineDetail["ExchangeID"] = pInvestorPositionCombineDetail->ExchangeID;
        json_pInvestorPositionCombineDetail["SettlementID"] = pInvestorPositionCombineDetail->SettlementID;
        json_pInvestorPositionCombineDetail["BrokerID"] = pInvestorPositionCombineDetail->BrokerID;
        json_pInvestorPositionCombineDetail["InvestorID"] = pInvestorPositionCombineDetail->InvestorID;
        json_pInvestorPositionCombineDetail["ComTradeID"] = pInvestorPositionCombineDetail->ComTradeID;
        json_pInvestorPositionCombineDetail["TradeID"] = pInvestorPositionCombineDetail->TradeID;
        json_pInvestorPositionCombineDetail["InstrumentID"] = pInvestorPositionCombineDetail->InstrumentID;
        json_pInvestorPositionCombineDetail["HedgeFlag"] = pInvestorPositionCombineDetail->HedgeFlag;
        json_pInvestorPositionCombineDetail["Direction"] = pInvestorPositionCombineDetail->Direction;
        json_pInvestorPositionCombineDetail["TotalAmt"] = pInvestorPositionCombineDetail->TotalAmt;
        json_pInvestorPositionCombineDetail["Margin"] = pInvestorPositionCombineDetail->Margin;
        json_pInvestorPositionCombineDetail["ExchMargin"] = pInvestorPositionCombineDetail->ExchMargin;
        json_pInvestorPositionCombineDetail["MarginRateByMoney"] = pInvestorPositionCombineDetail->MarginRateByMoney;
        json_pInvestorPositionCombineDetail["MarginRateByVolume"] = pInvestorPositionCombineDetail->MarginRateByVolume;
        json_pInvestorPositionCombineDetail["LegID"] = pInvestorPositionCombineDetail->LegID;
        json_pInvestorPositionCombineDetail["LegMultiple"] = pInvestorPositionCombineDetail->LegMultiple;
        json_pInvestorPositionCombineDetail["CombInstrumentID"] = pInvestorPositionCombineDetail->CombInstrumentID;
        json_pInvestorPositionCombineDetail["TradeGroupID"] = pInvestorPositionCombineDetail->TradeGroupID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInvestorPositionCombineDetail;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorPositionCombineDetail";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///投资者结算结果确认响应
void CTraderHandler::OnRspSettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspSettlementInfoConfirm():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspSettlementInfoConfirm:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspSettlementInfoConfirm:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspSettlementInfoConfirm";

    /// 返回数据结构体转化json格式
    Json::Value json_pSettlementInfoConfirm;
    if ( pSettlementInfoConfirm != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pSettlementInfoConfirm["BrokerID"] = pSettlementInfoConfirm->BrokerID;
        json_pSettlementInfoConfirm["InvestorID"] = pSettlementInfoConfirm->InvestorID;
        json_pSettlementInfoConfirm["ConfirmDate"] = pSettlementInfoConfirm->ConfirmDate;
        json_pSettlementInfoConfirm["ConfirmTime"] = pSettlementInfoConfirm->ConfirmTime;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pSettlementInfoConfirm;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspSettlementInfoConfirm";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询银期签约关系响应
void CTraderHandler::OnRspQryAccountregister(
    CThostFtdcAccountregisterField * pAccountregister,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryAccountregister():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryAccountregister:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryAccountregister:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryAccountregister";

    /// 返回数据结构体转化json格式
    Json::Value json_pAccountregister;
    if ( pAccountregister != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pAccountregister["TradeDay"] = pAccountregister->TradeDay;
        json_pAccountregister["BankID"] = pAccountregister->BankID;
        json_pAccountregister["BankBranchID"] = pAccountregister->BankBranchID;
        json_pAccountregister["BankAccount"] = pAccountregister->BankAccount;
        json_pAccountregister["BrokerID"] = pAccountregister->BrokerID;
        json_pAccountregister["BrokerBranchID"] = pAccountregister->BrokerBranchID;
        json_pAccountregister["AccountID"] = pAccountregister->AccountID;
        json_pAccountregister["IdCardType"] = pAccountregister->IdCardType;
        json_pAccountregister["IdentifiedCardNo"] = pAccountregister->IdentifiedCardNo;
        json_pAccountregister["CustomerName"] = pAccountregister->CustomerName;
        json_pAccountregister["CurrencyID"] = pAccountregister->CurrencyID;
        json_pAccountregister["OpenOrDestroy"] = pAccountregister->OpenOrDestroy;
        json_pAccountregister["RegDate"] = pAccountregister->RegDate;
        json_pAccountregister["OutDate"] = pAccountregister->OutDate;
        json_pAccountregister["TID"] = pAccountregister->TID;
        json_pAccountregister["CustType"] = pAccountregister->CustType;
        json_pAccountregister["BankAccType"] = pAccountregister->BankAccType;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pAccountregister;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryAccountregister";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询二级代理操作员银期权限响应
void CTraderHandler::OnRspQrySecAgentACIDMap(
    CThostFtdcSecAgentACIDMapField * pSecAgentACIDMap,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQrySecAgentACIDMap():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQrySecAgentACIDMap:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQrySecAgentACIDMap:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQrySecAgentACIDMap";

    /// 返回数据结构体转化json格式
    Json::Value json_pSecAgentACIDMap;
    if ( pSecAgentACIDMap != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pSecAgentACIDMap["BrokerID"] = pSecAgentACIDMap->BrokerID;
        json_pSecAgentACIDMap["UserID"] = pSecAgentACIDMap->UserID;
        json_pSecAgentACIDMap["AccountID"] = pSecAgentACIDMap->AccountID;
        json_pSecAgentACIDMap["CurrencyID"] = pSecAgentACIDMap->CurrencyID;
        json_pSecAgentACIDMap["BrokerSecAgentID"] = pSecAgentACIDMap->BrokerSecAgentID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pSecAgentACIDMap;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQrySecAgentACIDMap";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询交易编码响应
void CTraderHandler::OnRspQryTradingCode(
    CThostFtdcTradingCodeField * pTradingCode,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryTradingCode():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryTradingCode:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryTradingCode:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTradingCode";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingCode;
    if ( pTradingCode != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pTradingCode["InvestorID"] = pTradingCode->InvestorID;
        json_pTradingCode["BrokerID"] = pTradingCode->BrokerID;
        json_pTradingCode["ExchangeID"] = pTradingCode->ExchangeID;
        json_pTradingCode["ClientID"] = pTradingCode->ClientID;
        json_pTradingCode["IsActive"] = pTradingCode->IsActive;
        json_pTradingCode["ClientIDType"] = pTradingCode->ClientIDType;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTradingCode;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTradingCode";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询结算信息确认响应
void CTraderHandler::OnRspQrySettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQrySettlementInfoConfirm():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQrySettlementInfoConfirm:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQrySettlementInfoConfirm:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQrySettlementInfoConfirm";

    /// 返回数据结构体转化json格式
    Json::Value json_pSettlementInfoConfirm;
    if ( pSettlementInfoConfirm != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pSettlementInfoConfirm["BrokerID"] = pSettlementInfoConfirm->BrokerID;
        json_pSettlementInfoConfirm["InvestorID"] = pSettlementInfoConfirm->InvestorID;
        json_pSettlementInfoConfirm["ConfirmDate"] = pSettlementInfoConfirm->ConfirmDate;
        json_pSettlementInfoConfirm["ConfirmTime"] = pSettlementInfoConfirm->ConfirmTime;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pSettlementInfoConfirm;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQrySettlementInfoConfirm";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询转帐流水响应
void CTraderHandler::OnRspQryTransferSerial(
    CThostFtdcTransferSerialField * pTransferSerial,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryTransferSerial():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryTransferSerial:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryTransferSerial:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTransferSerial";

    /// 返回数据结构体转化json格式
    Json::Value json_pTransferSerial;
    if ( pTransferSerial != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pTransferSerial["PlateSerial"] = pTransferSerial->PlateSerial;
        json_pTransferSerial["TradeDate"] = pTransferSerial->TradeDate;
        json_pTransferSerial["TradingDay"] = pTransferSerial->TradingDay;
        json_pTransferSerial["TradeTime"] = pTransferSerial->TradeTime;
        json_pTransferSerial["TradeCode"] = pTransferSerial->TradeCode;
        json_pTransferSerial["SessionID"] = pTransferSerial->SessionID;
        json_pTransferSerial["BankID"] = pTransferSerial->BankID;
        json_pTransferSerial["BankBranchID"] = pTransferSerial->BankBranchID;
        json_pTransferSerial["BankAccType"] = pTransferSerial->BankAccType;
        json_pTransferSerial["BankAccount"] = pTransferSerial->BankAccount;
        json_pTransferSerial["BankSerial"] = pTransferSerial->BankSerial;
        json_pTransferSerial["BrokerID"] = pTransferSerial->BrokerID;
        json_pTransferSerial["BrokerBranchID"] = pTransferSerial->BrokerBranchID;
        json_pTransferSerial["FutureAccType"] = pTransferSerial->FutureAccType;
        json_pTransferSerial["AccountID"] = pTransferSerial->AccountID;
        json_pTransferSerial["InvestorID"] = pTransferSerial->InvestorID;
        json_pTransferSerial["FutureSerial"] = pTransferSerial->FutureSerial;
        json_pTransferSerial["IdCardType"] = pTransferSerial->IdCardType;
        json_pTransferSerial["IdentifiedCardNo"] = pTransferSerial->IdentifiedCardNo;
        json_pTransferSerial["CurrencyID"] = pTransferSerial->CurrencyID;
        json_pTransferSerial["TradeAmount"] = pTransferSerial->TradeAmount;
        json_pTransferSerial["CustFee"] = pTransferSerial->CustFee;
        json_pTransferSerial["BrokerFee"] = pTransferSerial->BrokerFee;
        json_pTransferSerial["AvailabilityFlag"] = pTransferSerial->AvailabilityFlag;
        json_pTransferSerial["OperatorCode"] = pTransferSerial->OperatorCode;
        json_pTransferSerial["BankNewAccount"] = pTransferSerial->BankNewAccount;
        json_pTransferSerial["ErrorID"] = pTransferSerial->ErrorID;
        json_pTransferSerial["ErrorMsg"] = pTransferSerial->ErrorMsg;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTransferSerial;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTransferSerial";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询投资者持仓响应
void CTraderHandler::OnRspQryInvestorPosition(
    CThostFtdcInvestorPositionField * pInvestorPosition,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInvestorPosition():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInvestorPosition:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInvestorPosition:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorPosition";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorPosition;
    if ( pInvestorPosition != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInvestorPosition["InstrumentID"] = pInvestorPosition->InstrumentID;
        json_pInvestorPosition["BrokerID"] = pInvestorPosition->BrokerID;
        json_pInvestorPosition["InvestorID"] = pInvestorPosition->InvestorID;
        json_pInvestorPosition["PosiDirection"] = pInvestorPosition->PosiDirection;
        json_pInvestorPosition["HedgeFlag"] = pInvestorPosition->HedgeFlag;
        json_pInvestorPosition["PositionDate"] = pInvestorPosition->PositionDate;
        json_pInvestorPosition["YdPosition"] = pInvestorPosition->YdPosition;
        json_pInvestorPosition["Position"] = pInvestorPosition->Position;
        json_pInvestorPosition["LongFrozen"] = pInvestorPosition->LongFrozen;
        json_pInvestorPosition["ShortFrozen"] = pInvestorPosition->ShortFrozen;
        json_pInvestorPosition["LongFrozenAmount"] = pInvestorPosition->LongFrozenAmount;
        json_pInvestorPosition["ShortFrozenAmount"] = pInvestorPosition->ShortFrozenAmount;
        json_pInvestorPosition["OpenVolume"] = pInvestorPosition->OpenVolume;
        json_pInvestorPosition["CloseVolume"] = pInvestorPosition->CloseVolume;
        json_pInvestorPosition["OpenAmount"] = pInvestorPosition->OpenAmount;
        json_pInvestorPosition["CloseAmount"] = pInvestorPosition->CloseAmount;
        json_pInvestorPosition["PositionCost"] = pInvestorPosition->PositionCost;
        json_pInvestorPosition["PreMargin"] = pInvestorPosition->PreMargin;
        json_pInvestorPosition["UseMargin"] = pInvestorPosition->UseMargin;
        json_pInvestorPosition["FrozenMargin"] = pInvestorPosition->FrozenMargin;
        json_pInvestorPosition["FrozenCash"] = pInvestorPosition->FrozenCash;
        json_pInvestorPosition["FrozenCommission"] = pInvestorPosition->FrozenCommission;
        json_pInvestorPosition["CashIn"] = pInvestorPosition->CashIn;
        json_pInvestorPosition["Commission"] = pInvestorPosition->Commission;
        json_pInvestorPosition["CloseProfit"] = pInvestorPosition->CloseProfit;
        json_pInvestorPosition["PositionProfit"] = pInvestorPosition->PositionProfit;
        json_pInvestorPosition["PreSettlementPrice"] = pInvestorPosition->PreSettlementPrice;
        json_pInvestorPosition["SettlementPrice"] = pInvestorPosition->SettlementPrice;
        json_pInvestorPosition["TradingDay"] = pInvestorPosition->TradingDay;
        json_pInvestorPosition["SettlementID"] = pInvestorPosition->SettlementID;
        json_pInvestorPosition["OpenCost"] = pInvestorPosition->OpenCost;
        json_pInvestorPosition["ExchangeMargin"] = pInvestorPosition->ExchangeMargin;
        json_pInvestorPosition["CombPosition"] = pInvestorPosition->CombPosition;
        json_pInvestorPosition["CombLongFrozen"] = pInvestorPosition->CombLongFrozen;
        json_pInvestorPosition["CombShortFrozen"] = pInvestorPosition->CombShortFrozen;
        json_pInvestorPosition["CloseProfitByDate"] = pInvestorPosition->CloseProfitByDate;
        json_pInvestorPosition["CloseProfitByTrade"] = pInvestorPosition->CloseProfitByTrade;
        json_pInvestorPosition["TodayPosition"] = pInvestorPosition->TodayPosition;
        json_pInvestorPosition["MarginRateByMoney"] = pInvestorPosition->MarginRateByMoney;
        json_pInvestorPosition["MarginRateByVolume"] = pInvestorPosition->MarginRateByVolume;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInvestorPosition;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorPosition";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///登出请求响应
void CTraderHandler::OnRspUserLogout(
    CThostFtdcUserLogoutField * pUserLogout,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspUserLogout():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspUserLogout:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspUserLogout:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserLogout";

    /// 返回数据结构体转化json格式
    Json::Value json_pUserLogout;
    if ( pUserLogout != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pUserLogout["BrokerID"] = pUserLogout->BrokerID;
        json_pUserLogout["UserID"] = pUserLogout->UserID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pUserLogout;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserLogout";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询投资者持仓明细响应
void CTraderHandler::OnRspQryInvestorPositionDetail(
    CThostFtdcInvestorPositionDetailField * pInvestorPositionDetail,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInvestorPositionDetail():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInvestorPositionDetail:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInvestorPositionDetail:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorPositionDetail";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorPositionDetail;
    if ( pInvestorPositionDetail != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInvestorPositionDetail["InstrumentID"] = pInvestorPositionDetail->InstrumentID;
        json_pInvestorPositionDetail["BrokerID"] = pInvestorPositionDetail->BrokerID;
        json_pInvestorPositionDetail["InvestorID"] = pInvestorPositionDetail->InvestorID;
        json_pInvestorPositionDetail["HedgeFlag"] = pInvestorPositionDetail->HedgeFlag;
        json_pInvestorPositionDetail["Direction"] = pInvestorPositionDetail->Direction;
        json_pInvestorPositionDetail["OpenDate"] = pInvestorPositionDetail->OpenDate;
        json_pInvestorPositionDetail["TradeID"] = pInvestorPositionDetail->TradeID;
        json_pInvestorPositionDetail["Volume"] = pInvestorPositionDetail->Volume;
        json_pInvestorPositionDetail["OpenPrice"] = pInvestorPositionDetail->OpenPrice;
        json_pInvestorPositionDetail["TradingDay"] = pInvestorPositionDetail->TradingDay;
        json_pInvestorPositionDetail["SettlementID"] = pInvestorPositionDetail->SettlementID;
        json_pInvestorPositionDetail["TradeType"] = pInvestorPositionDetail->TradeType;
        json_pInvestorPositionDetail["CombInstrumentID"] = pInvestorPositionDetail->CombInstrumentID;
        json_pInvestorPositionDetail["ExchangeID"] = pInvestorPositionDetail->ExchangeID;
        json_pInvestorPositionDetail["CloseProfitByDate"] = pInvestorPositionDetail->CloseProfitByDate;
        json_pInvestorPositionDetail["CloseProfitByTrade"] = pInvestorPositionDetail->CloseProfitByTrade;
        json_pInvestorPositionDetail["PositionProfitByDate"] = pInvestorPositionDetail->PositionProfitByDate;
        json_pInvestorPositionDetail["PositionProfitByTrade"] = pInvestorPositionDetail->PositionProfitByTrade;
        json_pInvestorPositionDetail["Margin"] = pInvestorPositionDetail->Margin;
        json_pInvestorPositionDetail["ExchMargin"] = pInvestorPositionDetail->ExchMargin;
        json_pInvestorPositionDetail["MarginRateByMoney"] = pInvestorPositionDetail->MarginRateByMoney;
        json_pInvestorPositionDetail["MarginRateByVolume"] = pInvestorPositionDetail->MarginRateByVolume;
        json_pInvestorPositionDetail["LastSettlementPrice"] = pInvestorPositionDetail->LastSettlementPrice;
        json_pInvestorPositionDetail["SettlementPrice"] = pInvestorPositionDetail->SettlementPrice;
        json_pInvestorPositionDetail["CloseVolume"] = pInvestorPositionDetail->CloseVolume;
        json_pInvestorPositionDetail["CloseAmount"] = pInvestorPositionDetail->CloseAmount;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInvestorPositionDetail;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorPositionDetail";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询预埋撤单响应
void CTraderHandler::OnRspQryParkedOrderAction(
    CThostFtdcParkedOrderActionField * pParkedOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryParkedOrderAction():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryParkedOrderAction:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryParkedOrderAction:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryParkedOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrderAction;
    if ( pParkedOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pParkedOrderAction["BrokerID"] = pParkedOrderAction->BrokerID;
        json_pParkedOrderAction["InvestorID"] = pParkedOrderAction->InvestorID;
        json_pParkedOrderAction["OrderActionRef"] = pParkedOrderAction->OrderActionRef;
        json_pParkedOrderAction["OrderRef"] = pParkedOrderAction->OrderRef;
        json_pParkedOrderAction["RequestID"] = pParkedOrderAction->RequestID;
        json_pParkedOrderAction["FrontID"] = pParkedOrderAction->FrontID;
        json_pParkedOrderAction["SessionID"] = pParkedOrderAction->SessionID;
        json_pParkedOrderAction["ExchangeID"] = pParkedOrderAction->ExchangeID;
        json_pParkedOrderAction["OrderSysID"] = pParkedOrderAction->OrderSysID;
        json_pParkedOrderAction["ActionFlag"] = pParkedOrderAction->ActionFlag;
        json_pParkedOrderAction["LimitPrice"] = pParkedOrderAction->LimitPrice;
        json_pParkedOrderAction["VolumeChange"] = pParkedOrderAction->VolumeChange;
        json_pParkedOrderAction["UserID"] = pParkedOrderAction->UserID;
        json_pParkedOrderAction["InstrumentID"] = pParkedOrderAction->InstrumentID;
        json_pParkedOrderAction["ParkedOrderActionID"] = pParkedOrderAction->ParkedOrderActionID;
        json_pParkedOrderAction["UserType"] = pParkedOrderAction->UserType;
        json_pParkedOrderAction["Status"] = pParkedOrderAction->Status;
        json_pParkedOrderAction["ErrorID"] = pParkedOrderAction->ErrorID;
        json_pParkedOrderAction["ErrorMsg"] = pParkedOrderAction->ErrorMsg;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pParkedOrderAction;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryParkedOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询经纪公司交易参数响应
void CTraderHandler::OnRspQryBrokerTradingParams(
    CThostFtdcBrokerTradingParamsField * pBrokerTradingParams,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryBrokerTradingParams():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryBrokerTradingParams:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryBrokerTradingParams:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryBrokerTradingParams";

    /// 返回数据结构体转化json格式
    Json::Value json_pBrokerTradingParams;
    if ( pBrokerTradingParams != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pBrokerTradingParams["BrokerID"] = pBrokerTradingParams->BrokerID;
        json_pBrokerTradingParams["InvestorID"] = pBrokerTradingParams->InvestorID;
        json_pBrokerTradingParams["MarginPriceType"] = pBrokerTradingParams->MarginPriceType;
        json_pBrokerTradingParams["Algorithm"] = pBrokerTradingParams->Algorithm;
        json_pBrokerTradingParams["AvailIncludeCloseProfit"] = pBrokerTradingParams->AvailIncludeCloseProfit;
        json_pBrokerTradingParams["CurrencyID"] = pBrokerTradingParams->CurrencyID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pBrokerTradingParams;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryBrokerTradingParams";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询交易所保证金率响应
void CTraderHandler::OnRspQryExchangeMarginRate(
    CThostFtdcExchangeMarginRateField * pExchangeMarginRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryExchangeMarginRate():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryExchangeMarginRate:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryExchangeMarginRate:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchangeMarginRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchangeMarginRate;
    if ( pExchangeMarginRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pExchangeMarginRate["BrokerID"] = pExchangeMarginRate->BrokerID;
        json_pExchangeMarginRate["InstrumentID"] = pExchangeMarginRate->InstrumentID;
        json_pExchangeMarginRate["HedgeFlag"] = pExchangeMarginRate->HedgeFlag;
        json_pExchangeMarginRate["LongMarginRatioByMoney"] = pExchangeMarginRate->LongMarginRatioByMoney;
        json_pExchangeMarginRate["LongMarginRatioByVolume"] = pExchangeMarginRate->LongMarginRatioByVolume;
        json_pExchangeMarginRate["ShortMarginRatioByMoney"] = pExchangeMarginRate->ShortMarginRatioByMoney;
        json_pExchangeMarginRate["ShortMarginRatioByVolume"] = pExchangeMarginRate->ShortMarginRatioByVolume;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pExchangeMarginRate;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchangeMarginRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询预埋单响应
void CTraderHandler::OnRspQryParkedOrder(
    CThostFtdcParkedOrderField * pParkedOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryParkedOrder():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryParkedOrder:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryParkedOrder:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryParkedOrder";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrder;
    if ( pParkedOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pParkedOrder["BrokerID"] = pParkedOrder->BrokerID;
        json_pParkedOrder["InvestorID"] = pParkedOrder->InvestorID;
        json_pParkedOrder["InstrumentID"] = pParkedOrder->InstrumentID;
        json_pParkedOrder["OrderRef"] = pParkedOrder->OrderRef;
        json_pParkedOrder["UserID"] = pParkedOrder->UserID;
        json_pParkedOrder["OrderPriceType"] = pParkedOrder->OrderPriceType;
        json_pParkedOrder["Direction"] = pParkedOrder->Direction;
        json_pParkedOrder["CombOffsetFlag"] = pParkedOrder->CombOffsetFlag;
        json_pParkedOrder["CombHedgeFlag"] = pParkedOrder->CombHedgeFlag;
        json_pParkedOrder["LimitPrice"] = pParkedOrder->LimitPrice;
        json_pParkedOrder["VolumeTotalOriginal"] = pParkedOrder->VolumeTotalOriginal;
        json_pParkedOrder["TimeCondition"] = pParkedOrder->TimeCondition;
        json_pParkedOrder["GTDDate"] = pParkedOrder->GTDDate;
        json_pParkedOrder["VolumeCondition"] = pParkedOrder->VolumeCondition;
        json_pParkedOrder["MinVolume"] = pParkedOrder->MinVolume;
        json_pParkedOrder["ContingentCondition"] = pParkedOrder->ContingentCondition;
        json_pParkedOrder["StopPrice"] = pParkedOrder->StopPrice;
        json_pParkedOrder["ForceCloseReason"] = pParkedOrder->ForceCloseReason;
        json_pParkedOrder["IsAutoSuspend"] = pParkedOrder->IsAutoSuspend;
        json_pParkedOrder["BusinessUnit"] = pParkedOrder->BusinessUnit;
        json_pParkedOrder["RequestID"] = pParkedOrder->RequestID;
        json_pParkedOrder["UserForceClose"] = pParkedOrder->UserForceClose;
        json_pParkedOrder["ExchangeID"] = pParkedOrder->ExchangeID;
        json_pParkedOrder["ParkedOrderID"] = pParkedOrder->ParkedOrderID;
        json_pParkedOrder["UserType"] = pParkedOrder->UserType;
        json_pParkedOrder["Status"] = pParkedOrder->Status;
        json_pParkedOrder["ErrorID"] = pParkedOrder->ErrorID;
        json_pParkedOrder["ErrorMsg"] = pParkedOrder->ErrorMsg;
        json_pParkedOrder["IsSwapOrder"] = pParkedOrder->IsSwapOrder;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pParkedOrder;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryParkedOrder";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///期货发起查询银行余额应答
void CTraderHandler::OnRspQueryBankAccountMoneyByFuture(
    CThostFtdcReqQueryAccountField * pReqQueryAccount,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQueryBankAccountMoneyByFuture():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQueryBankAccountMoneyByFuture:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQueryBankAccountMoneyByFuture:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQueryBankAccountMoneyByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqQueryAccount;
    if ( pReqQueryAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pReqQueryAccount["TradeCode"] = pReqQueryAccount->TradeCode;
        json_pReqQueryAccount["BankID"] = pReqQueryAccount->BankID;
        json_pReqQueryAccount["BankBranchID"] = pReqQueryAccount->BankBranchID;
        json_pReqQueryAccount["BrokerID"] = pReqQueryAccount->BrokerID;
        json_pReqQueryAccount["BrokerBranchID"] = pReqQueryAccount->BrokerBranchID;
        json_pReqQueryAccount["TradeDate"] = pReqQueryAccount->TradeDate;
        json_pReqQueryAccount["TradeTime"] = pReqQueryAccount->TradeTime;
        json_pReqQueryAccount["BankSerial"] = pReqQueryAccount->BankSerial;
        json_pReqQueryAccount["TradingDay"] = pReqQueryAccount->TradingDay;
        json_pReqQueryAccount["PlateSerial"] = pReqQueryAccount->PlateSerial;
        json_pReqQueryAccount["LastFragment"] = pReqQueryAccount->LastFragment;
        json_pReqQueryAccount["SessionID"] = pReqQueryAccount->SessionID;
        json_pReqQueryAccount["CustomerName"] = pReqQueryAccount->CustomerName;
        json_pReqQueryAccount["IdCardType"] = pReqQueryAccount->IdCardType;
        json_pReqQueryAccount["IdentifiedCardNo"] = pReqQueryAccount->IdentifiedCardNo;
        json_pReqQueryAccount["CustType"] = pReqQueryAccount->CustType;
        json_pReqQueryAccount["BankAccount"] = pReqQueryAccount->BankAccount;
        json_pReqQueryAccount["BankPassWord"] = pReqQueryAccount->BankPassWord;
        json_pReqQueryAccount["AccountID"] = pReqQueryAccount->AccountID;
        json_pReqQueryAccount["Password"] = pReqQueryAccount->Password;
        json_pReqQueryAccount["FutureSerial"] = pReqQueryAccount->FutureSerial;
        json_pReqQueryAccount["InstallID"] = pReqQueryAccount->InstallID;
        json_pReqQueryAccount["UserID"] = pReqQueryAccount->UserID;
        json_pReqQueryAccount["VerifyCertNoFlag"] = pReqQueryAccount->VerifyCertNoFlag;
        json_pReqQueryAccount["CurrencyID"] = pReqQueryAccount->CurrencyID;
        json_pReqQueryAccount["Digest"] = pReqQueryAccount->Digest;
        json_pReqQueryAccount["BankAccType"] = pReqQueryAccount->BankAccType;
        json_pReqQueryAccount["DeviceID"] = pReqQueryAccount->DeviceID;
        json_pReqQueryAccount["BankSecuAccType"] = pReqQueryAccount->BankSecuAccType;
        json_pReqQueryAccount["BrokerIDByBank"] = pReqQueryAccount->BrokerIDByBank;
        json_pReqQueryAccount["BankSecuAcc"] = pReqQueryAccount->BankSecuAcc;
        json_pReqQueryAccount["BankPwdFlag"] = pReqQueryAccount->BankPwdFlag;
        json_pReqQueryAccount["SecuPwdFlag"] = pReqQueryAccount->SecuPwdFlag;
        json_pReqQueryAccount["OperNo"] = pReqQueryAccount->OperNo;
        json_pReqQueryAccount["RequestID"] = pReqQueryAccount->RequestID;
        json_pReqQueryAccount["TID"] = pReqQueryAccount->TID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqQueryAccount;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQueryBankAccountMoneyByFuture";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///客户端认证响应
void CTraderHandler::OnRspAuthenticate(
    CThostFtdcRspAuthenticateField * pRspAuthenticateField,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspAuthenticate():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspAuthenticate:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspAuthenticate:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspAuthenticate";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspAuthenticateField;
    if ( pRspAuthenticateField != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pRspAuthenticateField["BrokerID"] = pRspAuthenticateField->BrokerID;
        json_pRspAuthenticateField["UserID"] = pRspAuthenticateField->UserID;
        json_pRspAuthenticateField["UserProductInfo"] = pRspAuthenticateField->UserProductInfo;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspAuthenticateField;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspAuthenticate";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///查询最大报单数量响应
void CTraderHandler::OnRspQueryMaxOrderVolume(
    CThostFtdcQueryMaxOrderVolumeField * pQueryMaxOrderVolume,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQueryMaxOrderVolume():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQueryMaxOrderVolume:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQueryMaxOrderVolume:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQueryMaxOrderVolume";

    /// 返回数据结构体转化json格式
    Json::Value json_pQueryMaxOrderVolume;
    if ( pQueryMaxOrderVolume != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pQueryMaxOrderVolume["BrokerID"] = pQueryMaxOrderVolume->BrokerID;
        json_pQueryMaxOrderVolume["InvestorID"] = pQueryMaxOrderVolume->InvestorID;
        json_pQueryMaxOrderVolume["InstrumentID"] = pQueryMaxOrderVolume->InstrumentID;
        json_pQueryMaxOrderVolume["Direction"] = pQueryMaxOrderVolume->Direction;
        json_pQueryMaxOrderVolume["OffsetFlag"] = pQueryMaxOrderVolume->OffsetFlag;
        json_pQueryMaxOrderVolume["HedgeFlag"] = pQueryMaxOrderVolume->HedgeFlag;
        json_pQueryMaxOrderVolume["MaxVolume"] = pQueryMaxOrderVolume->MaxVolume;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pQueryMaxOrderVolume;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQueryMaxOrderVolume";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询汇率响应
void CTraderHandler::OnRspQryExchangeRate(
    CThostFtdcExchangeRateField * pExchangeRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryExchangeRate():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryExchangeRate:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryExchangeRate:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchangeRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchangeRate;
    if ( pExchangeRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pExchangeRate["BrokerID"] = pExchangeRate->BrokerID;
        json_pExchangeRate["FromCurrencyID"] = pExchangeRate->FromCurrencyID;
        json_pExchangeRate["FromCurrencyUnit"] = pExchangeRate->FromCurrencyUnit;
        json_pExchangeRate["ToCurrencyID"] = pExchangeRate->ToCurrencyID;
        json_pExchangeRate["ExchangeRate"] = pExchangeRate->ExchangeRate;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pExchangeRate;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchangeRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询交易通知响应
void CTraderHandler::OnRspQryTradingNotice(
    CThostFtdcTradingNoticeField * pTradingNotice,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryTradingNotice():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryTradingNotice:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryTradingNotice:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTradingNotice";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingNotice;
    if ( pTradingNotice != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pTradingNotice["BrokerID"] = pTradingNotice->BrokerID;
        json_pTradingNotice["InvestorRange"] = pTradingNotice->InvestorRange;
        json_pTradingNotice["InvestorID"] = pTradingNotice->InvestorID;
        json_pTradingNotice["SequenceSeries"] = pTradingNotice->SequenceSeries;
        json_pTradingNotice["UserID"] = pTradingNotice->UserID;
        json_pTradingNotice["SendTime"] = pTradingNotice->SendTime;
        json_pTradingNotice["SequenceNo"] = pTradingNotice->SequenceNo;
        json_pTradingNotice["FieldContent"] = pTradingNotice->FieldContent;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTradingNotice;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTradingNotice";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///预埋撤单录入请求响应
void CTraderHandler::OnRspParkedOrderAction(
    CThostFtdcParkedOrderActionField * pParkedOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspParkedOrderAction():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspParkedOrderAction:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspParkedOrderAction:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspParkedOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrderAction;
    if ( pParkedOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pParkedOrderAction["BrokerID"] = pParkedOrderAction->BrokerID;
        json_pParkedOrderAction["InvestorID"] = pParkedOrderAction->InvestorID;
        json_pParkedOrderAction["OrderActionRef"] = pParkedOrderAction->OrderActionRef;
        json_pParkedOrderAction["OrderRef"] = pParkedOrderAction->OrderRef;
        json_pParkedOrderAction["RequestID"] = pParkedOrderAction->RequestID;
        json_pParkedOrderAction["FrontID"] = pParkedOrderAction->FrontID;
        json_pParkedOrderAction["SessionID"] = pParkedOrderAction->SessionID;
        json_pParkedOrderAction["ExchangeID"] = pParkedOrderAction->ExchangeID;
        json_pParkedOrderAction["OrderSysID"] = pParkedOrderAction->OrderSysID;
        json_pParkedOrderAction["ActionFlag"] = pParkedOrderAction->ActionFlag;
        json_pParkedOrderAction["LimitPrice"] = pParkedOrderAction->LimitPrice;
        json_pParkedOrderAction["VolumeChange"] = pParkedOrderAction->VolumeChange;
        json_pParkedOrderAction["UserID"] = pParkedOrderAction->UserID;
        json_pParkedOrderAction["InstrumentID"] = pParkedOrderAction->InstrumentID;
        json_pParkedOrderAction["ParkedOrderActionID"] = pParkedOrderAction->ParkedOrderActionID;
        json_pParkedOrderAction["UserType"] = pParkedOrderAction->UserType;
        json_pParkedOrderAction["Status"] = pParkedOrderAction->Status;
        json_pParkedOrderAction["ErrorID"] = pParkedOrderAction->ErrorID;
        json_pParkedOrderAction["ErrorMsg"] = pParkedOrderAction->ErrorMsg;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pParkedOrderAction;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspParkedOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询客户通知响应
void CTraderHandler::OnRspQryNotice(
    CThostFtdcNoticeField * pNotice,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryNotice():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryNotice:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryNotice:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryNotice";

    /// 返回数据结构体转化json格式
    Json::Value json_pNotice;
    if ( pNotice != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pNotice["BrokerID"] = pNotice->BrokerID;
        json_pNotice["Content"] = pNotice->Content;
        json_pNotice["SequenceLabel"] = pNotice->SequenceLabel;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pNotice;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryNotice";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询资金账户响应
void CTraderHandler::OnRspQryTradingAccount(
    CThostFtdcTradingAccountField * pTradingAccount,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryTradingAccount():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryTradingAccount:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryTradingAccount:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTradingAccount";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingAccount;
    if ( pTradingAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pTradingAccount["BrokerID"] = pTradingAccount->BrokerID;
        json_pTradingAccount["AccountID"] = pTradingAccount->AccountID;
        json_pTradingAccount["PreMortgage"] = pTradingAccount->PreMortgage;
        json_pTradingAccount["PreCredit"] = pTradingAccount->PreCredit;
        json_pTradingAccount["PreDeposit"] = pTradingAccount->PreDeposit;
        json_pTradingAccount["PreBalance"] = pTradingAccount->PreBalance;
        json_pTradingAccount["PreMargin"] = pTradingAccount->PreMargin;
        json_pTradingAccount["InterestBase"] = pTradingAccount->InterestBase;
        json_pTradingAccount["Interest"] = pTradingAccount->Interest;
        json_pTradingAccount["Deposit"] = pTradingAccount->Deposit;
        json_pTradingAccount["Withdraw"] = pTradingAccount->Withdraw;
        json_pTradingAccount["FrozenMargin"] = pTradingAccount->FrozenMargin;
        json_pTradingAccount["FrozenCash"] = pTradingAccount->FrozenCash;
        json_pTradingAccount["FrozenCommission"] = pTradingAccount->FrozenCommission;
        json_pTradingAccount["CurrMargin"] = pTradingAccount->CurrMargin;
        json_pTradingAccount["CashIn"] = pTradingAccount->CashIn;
        json_pTradingAccount["Commission"] = pTradingAccount->Commission;
        json_pTradingAccount["CloseProfit"] = pTradingAccount->CloseProfit;
        json_pTradingAccount["PositionProfit"] = pTradingAccount->PositionProfit;
        json_pTradingAccount["Balance"] = pTradingAccount->Balance;
        json_pTradingAccount["Available"] = pTradingAccount->Available;
        json_pTradingAccount["WithdrawQuota"] = pTradingAccount->WithdrawQuota;
        json_pTradingAccount["Reserve"] = pTradingAccount->Reserve;
        json_pTradingAccount["TradingDay"] = pTradingAccount->TradingDay;
        json_pTradingAccount["SettlementID"] = pTradingAccount->SettlementID;
        json_pTradingAccount["Credit"] = pTradingAccount->Credit;
        json_pTradingAccount["Mortgage"] = pTradingAccount->Mortgage;
        json_pTradingAccount["ExchangeMargin"] = pTradingAccount->ExchangeMargin;
        json_pTradingAccount["DeliveryMargin"] = pTradingAccount->DeliveryMargin;
        json_pTradingAccount["ExchangeDeliveryMargin"] = pTradingAccount->ExchangeDeliveryMargin;
        json_pTradingAccount["ReserveBalance"] = pTradingAccount->ReserveBalance;
        json_pTradingAccount["CurrencyID"] = pTradingAccount->CurrencyID;
        json_pTradingAccount["PreFundMortgageIn"] = pTradingAccount->PreFundMortgageIn;
        json_pTradingAccount["PreFundMortgageOut"] = pTradingAccount->PreFundMortgageOut;
        json_pTradingAccount["FundMortgageIn"] = pTradingAccount->FundMortgageIn;
        json_pTradingAccount["FundMortgageOut"] = pTradingAccount->FundMortgageOut;
        json_pTradingAccount["FundMortgageAvailable"] = pTradingAccount->FundMortgageAvailable;
        json_pTradingAccount["MortgageableFund"] = pTradingAccount->MortgageableFund;
        json_pTradingAccount["SpecProductMargin"] = pTradingAccount->SpecProductMargin;
        json_pTradingAccount["SpecProductFrozenMargin"] = pTradingAccount->SpecProductFrozenMargin;
        json_pTradingAccount["SpecProductCommission"] = pTradingAccount->SpecProductCommission;
        json_pTradingAccount["SpecProductFrozenCommission"] = pTradingAccount->SpecProductFrozenCommission;
        json_pTradingAccount["SpecProductPositionProfit"] = pTradingAccount->SpecProductPositionProfit;
        json_pTradingAccount["SpecProductCloseProfit"] = pTradingAccount->SpecProductCloseProfit;
        json_pTradingAccount["SpecProductPositionProfitByAlg"] = pTradingAccount->SpecProductPositionProfitByAlg;
        json_pTradingAccount["SpecProductExchangeMargin"] = pTradingAccount->SpecProductExchangeMargin;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTradingAccount;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTradingAccount";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///资金账户口令更新请求响应
void CTraderHandler::OnRspTradingAccountPasswordUpdate(
    CThostFtdcTradingAccountPasswordUpdateField * pTradingAccountPasswordUpdate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspTradingAccountPasswordUpdate():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspTradingAccountPasswordUpdate:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspTradingAccountPasswordUpdate:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspTradingAccountPasswordUpdate";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingAccountPasswordUpdate;
    if ( pTradingAccountPasswordUpdate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pTradingAccountPasswordUpdate["BrokerID"] = pTradingAccountPasswordUpdate->BrokerID;
        json_pTradingAccountPasswordUpdate["AccountID"] = pTradingAccountPasswordUpdate->AccountID;
        json_pTradingAccountPasswordUpdate["OldPassword"] = pTradingAccountPasswordUpdate->OldPassword;
        json_pTradingAccountPasswordUpdate["NewPassword"] = pTradingAccountPasswordUpdate->NewPassword;
        json_pTradingAccountPasswordUpdate["CurrencyID"] = pTradingAccountPasswordUpdate->CurrencyID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTradingAccountPasswordUpdate;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspTradingAccountPasswordUpdate";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询报单响应
void CTraderHandler::OnRspQryOrder(
    CThostFtdcOrderField * pOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryOrder():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryOrder:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryOrder:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryOrder";

    /// 返回数据结构体转化json格式
    Json::Value json_pOrder;
    if ( pOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pOrder["BrokerID"] = pOrder->BrokerID;
        json_pOrder["InvestorID"] = pOrder->InvestorID;
        json_pOrder["InstrumentID"] = pOrder->InstrumentID;
        json_pOrder["OrderRef"] = pOrder->OrderRef;
        json_pOrder["UserID"] = pOrder->UserID;
        json_pOrder["OrderPriceType"] = pOrder->OrderPriceType;
        json_pOrder["Direction"] = pOrder->Direction;
        json_pOrder["CombOffsetFlag"] = pOrder->CombOffsetFlag;
        json_pOrder["CombHedgeFlag"] = pOrder->CombHedgeFlag;
        json_pOrder["LimitPrice"] = pOrder->LimitPrice;
        json_pOrder["VolumeTotalOriginal"] = pOrder->VolumeTotalOriginal;
        json_pOrder["TimeCondition"] = pOrder->TimeCondition;
        json_pOrder["GTDDate"] = pOrder->GTDDate;
        json_pOrder["VolumeCondition"] = pOrder->VolumeCondition;
        json_pOrder["MinVolume"] = pOrder->MinVolume;
        json_pOrder["ContingentCondition"] = pOrder->ContingentCondition;
        json_pOrder["StopPrice"] = pOrder->StopPrice;
        json_pOrder["ForceCloseReason"] = pOrder->ForceCloseReason;
        json_pOrder["IsAutoSuspend"] = pOrder->IsAutoSuspend;
        json_pOrder["BusinessUnit"] = pOrder->BusinessUnit;
        json_pOrder["RequestID"] = pOrder->RequestID;
        json_pOrder["OrderLocalID"] = pOrder->OrderLocalID;
        json_pOrder["ExchangeID"] = pOrder->ExchangeID;
        json_pOrder["ParticipantID"] = pOrder->ParticipantID;
        json_pOrder["ClientID"] = pOrder->ClientID;
        json_pOrder["ExchangeInstID"] = pOrder->ExchangeInstID;
        json_pOrder["TraderID"] = pOrder->TraderID;
        json_pOrder["InstallID"] = pOrder->InstallID;
        json_pOrder["OrderSubmitStatus"] = pOrder->OrderSubmitStatus;
        json_pOrder["NotifySequence"] = pOrder->NotifySequence;
        json_pOrder["TradingDay"] = pOrder->TradingDay;
        json_pOrder["SettlementID"] = pOrder->SettlementID;
        json_pOrder["OrderSysID"] = pOrder->OrderSysID;
        json_pOrder["OrderSource"] = pOrder->OrderSource;
        json_pOrder["OrderStatus"] = pOrder->OrderStatus;
        json_pOrder["OrderType"] = pOrder->OrderType;
        json_pOrder["VolumeTraded"] = pOrder->VolumeTraded;
        json_pOrder["VolumeTotal"] = pOrder->VolumeTotal;
        json_pOrder["InsertDate"] = pOrder->InsertDate;
        json_pOrder["InsertTime"] = pOrder->InsertTime;
        json_pOrder["ActiveTime"] = pOrder->ActiveTime;
        json_pOrder["SuspendTime"] = pOrder->SuspendTime;
        json_pOrder["UpdateTime"] = pOrder->UpdateTime;
        json_pOrder["CancelTime"] = pOrder->CancelTime;
        json_pOrder["ActiveTraderID"] = pOrder->ActiveTraderID;
        json_pOrder["ClearingPartID"] = pOrder->ClearingPartID;
        json_pOrder["SequenceNo"] = pOrder->SequenceNo;
        json_pOrder["FrontID"] = pOrder->FrontID;
        json_pOrder["SessionID"] = pOrder->SessionID;
        json_pOrder["UserProductInfo"] = pOrder->UserProductInfo;
        json_pOrder["StatusMsg"] = pOrder->StatusMsg;
        json_pOrder["UserForceClose"] = pOrder->UserForceClose;
        json_pOrder["ActiveUserID"] = pOrder->ActiveUserID;
        json_pOrder["BrokerOrderSeq"] = pOrder->BrokerOrderSeq;
        json_pOrder["RelativeOrderSysID"] = pOrder->RelativeOrderSysID;
        json_pOrder["ZCETotalTradedVolume"] = pOrder->ZCETotalTradedVolume;
        json_pOrder["IsSwapOrder"] = pOrder->IsSwapOrder;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pOrder;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryOrder";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询行情响应
void CTraderHandler::OnRspQryDepthMarketData(
    CThostFtdcDepthMarketDataField * pDepthMarketData,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryDepthMarketData():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryDepthMarketData:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryDepthMarketData:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryDepthMarketData";

    /// 返回数据结构体转化json格式
    Json::Value json_pDepthMarketData;
    if ( pDepthMarketData != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pDepthMarketData["TradingDay"] = pDepthMarketData->TradingDay;
        json_pDepthMarketData["InstrumentID"] = pDepthMarketData->InstrumentID;
        json_pDepthMarketData["ExchangeID"] = pDepthMarketData->ExchangeID;
        json_pDepthMarketData["ExchangeInstID"] = pDepthMarketData->ExchangeInstID;
        json_pDepthMarketData["LastPrice"] = pDepthMarketData->LastPrice;
        json_pDepthMarketData["PreSettlementPrice"] = pDepthMarketData->PreSettlementPrice;
        json_pDepthMarketData["PreClosePrice"] = pDepthMarketData->PreClosePrice;
        json_pDepthMarketData["PreOpenInterest"] = pDepthMarketData->PreOpenInterest;
        json_pDepthMarketData["OpenPrice"] = pDepthMarketData->OpenPrice;
        json_pDepthMarketData["HighestPrice"] = pDepthMarketData->HighestPrice;
        json_pDepthMarketData["LowestPrice"] = pDepthMarketData->LowestPrice;
        json_pDepthMarketData["Volume"] = pDepthMarketData->Volume;
        json_pDepthMarketData["Turnover"] = pDepthMarketData->Turnover;
        json_pDepthMarketData["OpenInterest"] = pDepthMarketData->OpenInterest;
        json_pDepthMarketData["ClosePrice"] = pDepthMarketData->ClosePrice;
        json_pDepthMarketData["SettlementPrice"] = pDepthMarketData->SettlementPrice;
        json_pDepthMarketData["UpperLimitPrice"] = pDepthMarketData->UpperLimitPrice;
        json_pDepthMarketData["LowerLimitPrice"] = pDepthMarketData->LowerLimitPrice;
        json_pDepthMarketData["PreDelta"] = pDepthMarketData->PreDelta;
        json_pDepthMarketData["CurrDelta"] = pDepthMarketData->CurrDelta;
        json_pDepthMarketData["UpdateTime"] = pDepthMarketData->UpdateTime;
        json_pDepthMarketData["UpdateMillisec"] = pDepthMarketData->UpdateMillisec;
        json_pDepthMarketData["BidPrice1"] = pDepthMarketData->BidPrice1;
        json_pDepthMarketData["BidVolume1"] = pDepthMarketData->BidVolume1;
        json_pDepthMarketData["AskPrice1"] = pDepthMarketData->AskPrice1;
        json_pDepthMarketData["AskVolume1"] = pDepthMarketData->AskVolume1;
        json_pDepthMarketData["BidPrice2"] = pDepthMarketData->BidPrice2;
        json_pDepthMarketData["BidVolume2"] = pDepthMarketData->BidVolume2;
        json_pDepthMarketData["AskPrice2"] = pDepthMarketData->AskPrice2;
        json_pDepthMarketData["AskVolume2"] = pDepthMarketData->AskVolume2;
        json_pDepthMarketData["BidPrice3"] = pDepthMarketData->BidPrice3;
        json_pDepthMarketData["BidVolume3"] = pDepthMarketData->BidVolume3;
        json_pDepthMarketData["AskPrice3"] = pDepthMarketData->AskPrice3;
        json_pDepthMarketData["AskVolume3"] = pDepthMarketData->AskVolume3;
        json_pDepthMarketData["BidPrice4"] = pDepthMarketData->BidPrice4;
        json_pDepthMarketData["BidVolume4"] = pDepthMarketData->BidVolume4;
        json_pDepthMarketData["AskPrice4"] = pDepthMarketData->AskPrice4;
        json_pDepthMarketData["AskVolume4"] = pDepthMarketData->AskVolume4;
        json_pDepthMarketData["BidPrice5"] = pDepthMarketData->BidPrice5;
        json_pDepthMarketData["BidVolume5"] = pDepthMarketData->BidVolume5;
        json_pDepthMarketData["AskPrice5"] = pDepthMarketData->AskPrice5;
        json_pDepthMarketData["AskVolume5"] = pDepthMarketData->AskVolume5;
        json_pDepthMarketData["AveragePrice"] = pDepthMarketData->AveragePrice;
        json_pDepthMarketData["ActionDay"] = pDepthMarketData->ActionDay;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pDepthMarketData;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryDepthMarketData";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询合约手续费率响应
void CTraderHandler::OnRspQryInstrumentCommissionRate(
    CThostFtdcInstrumentCommissionRateField * pInstrumentCommissionRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryInstrumentCommissionRate():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryInstrumentCommissionRate:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryInstrumentCommissionRate:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInstrumentCommissionRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pInstrumentCommissionRate;
    if ( pInstrumentCommissionRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pInstrumentCommissionRate["InstrumentID"] = pInstrumentCommissionRate->InstrumentID;
        json_pInstrumentCommissionRate["InvestorRange"] = pInstrumentCommissionRate->InvestorRange;
        json_pInstrumentCommissionRate["BrokerID"] = pInstrumentCommissionRate->BrokerID;
        json_pInstrumentCommissionRate["InvestorID"] = pInstrumentCommissionRate->InvestorID;
        json_pInstrumentCommissionRate["OpenRatioByMoney"] = pInstrumentCommissionRate->OpenRatioByMoney;
        json_pInstrumentCommissionRate["OpenRatioByVolume"] = pInstrumentCommissionRate->OpenRatioByVolume;
        json_pInstrumentCommissionRate["CloseRatioByMoney"] = pInstrumentCommissionRate->CloseRatioByMoney;
        json_pInstrumentCommissionRate["CloseRatioByVolume"] = pInstrumentCommissionRate->CloseRatioByVolume;
        json_pInstrumentCommissionRate["CloseTodayRatioByMoney"] = pInstrumentCommissionRate->CloseTodayRatioByMoney;
        json_pInstrumentCommissionRate["CloseTodayRatioByVolume"] = pInstrumentCommissionRate->CloseTodayRatioByVolume;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInstrumentCommissionRate;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInstrumentCommissionRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///删除预埋撤单响应
void CTraderHandler::OnRspRemoveParkedOrderAction(
    CThostFtdcRemoveParkedOrderActionField * pRemoveParkedOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspRemoveParkedOrderAction():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspRemoveParkedOrderAction:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspRemoveParkedOrderAction:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspRemoveParkedOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pRemoveParkedOrderAction;
    if ( pRemoveParkedOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pRemoveParkedOrderAction["BrokerID"] = pRemoveParkedOrderAction->BrokerID;
        json_pRemoveParkedOrderAction["InvestorID"] = pRemoveParkedOrderAction->InvestorID;
        json_pRemoveParkedOrderAction["ParkedOrderActionID"] = pRemoveParkedOrderAction->ParkedOrderActionID;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRemoveParkedOrderAction;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspRemoveParkedOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}

///请求查询成交响应
void CTraderHandler::OnRspQryTrade(
    CThostFtdcTradeField * pTrade,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspQryTrade():被执行...\n");
    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 返回结果检查
    if ( pRspInfo )  {
        // typedef int TThostFtdcErrorIDType;
        // typedef char TThostFtdcErrorMsgType[81];
        if (pRspInfo->ErrorID != 0) {
            char ErrorMsg[243];
            gbk2utf8(pRspInfo->ErrorMsg,ErrorMsg,sizeof(ErrorMsg));
            std::cout << "OnRspQryTrade:出错:ErrorId=" << pRspInfo->ErrorID << ","
                      << "ErrorMsg=" << ErrorMsg << std::endl;
        }
    } else {
        std::cout << "OnRspQryTrade:出错:没有提供出错信息" << std::endl;
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTrade";

    /// 返回数据结构体转化json格式
    Json::Value json_pTrade;
    if ( pTrade != NULL ) {
        // TODO : 这里需要将编码转化为utf-8

        json_pTrade["BrokerID"] = pTrade->BrokerID;
        json_pTrade["InvestorID"] = pTrade->InvestorID;
        json_pTrade["InstrumentID"] = pTrade->InstrumentID;
        json_pTrade["OrderRef"] = pTrade->OrderRef;
        json_pTrade["UserID"] = pTrade->UserID;
        json_pTrade["ExchangeID"] = pTrade->ExchangeID;
        json_pTrade["TradeID"] = pTrade->TradeID;
        json_pTrade["Direction"] = pTrade->Direction;
        json_pTrade["OrderSysID"] = pTrade->OrderSysID;
        json_pTrade["ParticipantID"] = pTrade->ParticipantID;
        json_pTrade["ClientID"] = pTrade->ClientID;
        json_pTrade["TradingRole"] = pTrade->TradingRole;
        json_pTrade["ExchangeInstID"] = pTrade->ExchangeInstID;
        json_pTrade["OffsetFlag"] = pTrade->OffsetFlag;
        json_pTrade["HedgeFlag"] = pTrade->HedgeFlag;
        json_pTrade["Price"] = pTrade->Price;
        json_pTrade["Volume"] = pTrade->Volume;
        json_pTrade["TradeDate"] = pTrade->TradeDate;
        json_pTrade["TradeTime"] = pTrade->TradeTime;
        json_pTrade["TradeType"] = pTrade->TradeType;
        json_pTrade["PriceSource"] = pTrade->PriceSource;
        json_pTrade["TraderID"] = pTrade->TraderID;
        json_pTrade["OrderLocalID"] = pTrade->OrderLocalID;
        json_pTrade["ClearingPartID"] = pTrade->ClearingPartID;
        json_pTrade["BusinessUnit"] = pTrade->BusinessUnit;
        json_pTrade["SequenceNo"] = pTrade->SequenceNo;
        json_pTrade["TradingDay"] = pTrade->TradingDay;
        json_pTrade["SettlementID"] = pTrade->SettlementID;
        json_pTrade["BrokerOrderSeq"] = pTrade->BrokerOrderSeq;
        json_pTrade["TradeSource"] = pTrade->TradeSource;
    }

    /// 出错信息
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
    json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTrade;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTrade";
    message.respInfo = json_Response.toStyledString();
    message.send(sender);
}


/**********************************************************
*                   onRtn开头的方法                         *
***********************************************************/



///期货发起查询银行余额通知
void CTraderHandler::OnRtnQueryBankBalanceByFuture(
    CThostFtdcNotifyQueryAccountField * pNotifyQueryAccount
) {
    printf("OnRtnQueryBankBalanceByFuture():被执行...\n");
}

///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromBankToFutureByFuture(
    CThostFtdcRspRepealField * pRspRepeal
) {
    printf("OnRtnRepealFromBankToFutureByFuture():被执行...\n");
}

///银行发起银行资金转期货通知
void CTraderHandler::OnRtnFromBankToFutureByBank(
    CThostFtdcRspTransferField * pRspTransfer
) {
    printf("OnRtnFromBankToFutureByBank():被执行...\n");
}

///合约交易状态通知
void CTraderHandler::OnRtnInstrumentStatus(
    CThostFtdcInstrumentStatusField * pInstrumentStatus
) {
    printf("OnRtnInstrumentStatus():被执行...\n");
}

///交易通知
void CTraderHandler::OnRtnTradingNotice(
    CThostFtdcTradingNoticeInfoField * pTradingNoticeInfo
) {
    printf("OnRtnTradingNotice():被执行...\n");
}

///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromFutureToBankByFutureManual(
    CThostFtdcRspRepealField * pRspRepeal
) {
    printf("OnRtnRepealFromFutureToBankByFutureManual():被执行...\n");
}

///期货发起银行资金转期货通知
void CTraderHandler::OnRtnFromBankToFutureByFuture(
    CThostFtdcRspTransferField * pRspTransfer
) {
    printf("OnRtnFromBankToFutureByFuture():被执行...\n");
}

///银行发起期货资金转银行通知
void CTraderHandler::OnRtnFromFutureToBankByBank(
    CThostFtdcRspTransferField * pRspTransfer
) {
    printf("OnRtnFromFutureToBankByBank():被执行...\n");
}

///成交通知
void CTraderHandler::OnRtnTrade(
    CThostFtdcTradeField * pTrade
) {
    printf("OnRtnTrade():被执行...\n");
}

///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromBankToFutureByFutureManual(
    CThostFtdcRspRepealField * pRspRepeal
) {
    printf("OnRtnRepealFromBankToFutureByFutureManual():被执行...\n");
}

///期货发起期货资金转银行通知
void CTraderHandler::OnRtnFromFutureToBankByFuture(
    CThostFtdcRspTransferField * pRspTransfer
) {
    printf("OnRtnFromFutureToBankByFuture():被执行...\n");
}

///银行发起变更银行账号通知
void CTraderHandler::OnRtnChangeAccountByBank(
    CThostFtdcChangeAccountField * pChangeAccount
) {
    printf("OnRtnChangeAccountByBank():被执行...\n");
}

///银行发起冲正期货转银行通知
void CTraderHandler::OnRtnRepealFromFutureToBankByBank(
    CThostFtdcRspRepealField * pRspRepeal
) {
    printf("OnRtnRepealFromFutureToBankByBank():被执行...\n");
}

///银行发起银期开户通知
void CTraderHandler::OnRtnOpenAccountByBank(
    CThostFtdcOpenAccountField * pOpenAccount
) {
    printf("OnRtnOpenAccountByBank():被执行...\n");
}

///保证金监控中心用户令牌
void CTraderHandler::OnRtnCFMMCTradingAccountToken(
    CThostFtdcCFMMCTradingAccountTokenField * pCFMMCTradingAccountToken
) {
    printf("OnRtnCFMMCTradingAccountToken():被执行...\n");
}

///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromFutureToBankByFuture(
    CThostFtdcRspRepealField * pRspRepeal
) {
    printf("OnRtnRepealFromFutureToBankByFuture():被执行...\n");
}

///提示条件单校验错误
void CTraderHandler::OnRtnErrorConditionalOrder(
    CThostFtdcErrorConditionalOrderField * pErrorConditionalOrder
) {
    printf("OnRtnErrorConditionalOrder():被执行...\n");
}

///银行发起冲正银行转期货通知
void CTraderHandler::OnRtnRepealFromBankToFutureByBank(
    CThostFtdcRspRepealField * pRspRepeal
) {
    printf("OnRtnRepealFromBankToFutureByBank():被执行...\n");
}

///报单通知
void CTraderHandler::OnRtnOrder(
    CThostFtdcOrderField * pOrder
) {
    printf("OnRtnOrder():被执行...\n");
}

///银行发起银期销户通知
void CTraderHandler::OnRtnCancelAccountByBank(
    CThostFtdcCancelAccountField * pCancelAccount
) {
    printf("OnRtnCancelAccountByBank():被执行...\n");
}


/**********************************************************
*                   onErrRtn开头的方法                      *
***********************************************************/


///系统运行时期货端手工发起冲正期货转银行错误回报
void CTraderHandler::OnErrRtnRepealFutureToBankByFutureManual(
    CThostFtdcReqRepealField * pReqRepeal,
    CThostFtdcRspInfoField * pRspInfo
) {
    printf("OnErrRtnRepealFutureToBankByFutureManual():被执行...\n");
}

///期货发起期货资金转银行错误回报
void CTraderHandler::OnErrRtnFutureToBankByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo
) {
    printf("OnErrRtnFutureToBankByFuture():被执行...\n");
}

///报单录入错误回报
void CTraderHandler::OnErrRtnOrderInsert(
    CThostFtdcInputOrderField * pInputOrder,
    CThostFtdcRspInfoField * pRspInfo
) {
    printf("OnErrRtnOrderInsert():被执行...\n");
}

///系统运行时期货端手工发起冲正银行转期货错误回报
void CTraderHandler::OnErrRtnRepealBankToFutureByFutureManual(
    CThostFtdcReqRepealField * pReqRepeal,
    CThostFtdcRspInfoField * pRspInfo
) {
    printf("OnErrRtnRepealBankToFutureByFutureManual():被执行...\n");
}

///期货发起银行资金转期货错误回报
void CTraderHandler::OnErrRtnBankToFutureByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo
) {
    printf("OnErrRtnBankToFutureByFuture():被执行...\n");
}

///期货发起查询银行余额错误回报
void CTraderHandler::OnErrRtnQueryBankBalanceByFuture(
    CThostFtdcReqQueryAccountField * pReqQueryAccount,
    CThostFtdcRspInfoField * pRspInfo
) {
    printf("OnErrRtnQueryBankBalanceByFuture():被执行...\n");
}

///报单操作错误回报
void CTraderHandler::OnErrRtnOrderAction(
    CThostFtdcOrderActionField * pOrderAction,
    CThostFtdcRspInfoField * pRspInfo
) {
    printf("OnErrRtnOrderAction():被执行...\n");
}



/**********************************************************
*                     onRspError方法                       *
***********************************************************/

///错误应答
void CTraderHandler::OnRspError(
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {
    printf("OnRspError():被执行...\n");
}
