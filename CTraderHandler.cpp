#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>
#include <json/json.h>
#include <comhelper.h>


/// 构造函数
CTraderHandler::CTraderHandler(Configure * pConfigure) {

    std::cout << "CTraderHandler():开始执行..." << std::endl;

    // 读取配置数据信息
    this->pConfigure = pConfigure;
    // 创建zmq通讯环境
    pContext = new zmq::context_t(1);
    pSender = new zmq::socket_t(*pContext, ZMQ_PUSH);
    pSender->bind(pConfigure->pushbackPipe);

    std::cout << "CTraderHandler():执行结束..." << std::endl;
}

/// 成功连接服务器消息
void CTraderHandler::OnFrontConnected() {

    std::cout << "OnFrontConnected():开始执行..." << std::endl;

    zmq::socket_t & sender = *pSender;
    PushbackMessage message;
    message.requestID = "0";
    message.apiName = "OnFrontConnected";
    message.respInfo = "";
    message.send(sender);

    std::cout << "OnFrontConnected():执行结束..." << std::endl;
}


// 字符操作使用的临时缓冲区,由于ctp最长的字符串变量长度2049,并且需要字符串编码的转换,
// 定义3倍长度来保证不会超出
static char buffer[1024*10];

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

    std::cout << "OnRspQryInstrument():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInstrument";

    /// 返回数据结构体转化json格式
    Json::Value json_pInstrument;
    if ( pInstrument != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInstrument->InstrumentID,
            buffer,
            sizeof(pInstrument->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["InstrumentID"] = buffer;


        gbk2utf8(
            pInstrument->ExchangeID,
            buffer,
            sizeof(pInstrument->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["ExchangeID"] = buffer;


        gbk2utf8(
            pInstrument->InstrumentName,
            buffer,
            sizeof(pInstrument->InstrumentName) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["InstrumentName"] = buffer;


        gbk2utf8(
            pInstrument->ExchangeInstID,
            buffer,
            sizeof(pInstrument->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["ExchangeInstID"] = buffer;


        gbk2utf8(
            pInstrument->ProductID,
            buffer,
            sizeof(pInstrument->ProductID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["ProductID"] = buffer;


        json_pInstrument["ProductClass"] = pInstrument->ProductClass;


        json_pInstrument["DeliveryYear"] = pInstrument->DeliveryYear;


        json_pInstrument["DeliveryMonth"] = pInstrument->DeliveryMonth;


        json_pInstrument["MaxMarketOrderVolume"] = pInstrument->MaxMarketOrderVolume;


        json_pInstrument["MinMarketOrderVolume"] = pInstrument->MinMarketOrderVolume;


        json_pInstrument["MaxLimitOrderVolume"] = pInstrument->MaxLimitOrderVolume;


        json_pInstrument["MinLimitOrderVolume"] = pInstrument->MinLimitOrderVolume;


        json_pInstrument["VolumeMultiple"] = pInstrument->VolumeMultiple;


        json_pInstrument["PriceTick"] = pInstrument->PriceTick;


        gbk2utf8(
            pInstrument->CreateDate,
            buffer,
            sizeof(pInstrument->CreateDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["CreateDate"] = buffer;


        gbk2utf8(
            pInstrument->OpenDate,
            buffer,
            sizeof(pInstrument->OpenDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["OpenDate"] = buffer;


        gbk2utf8(
            pInstrument->ExpireDate,
            buffer,
            sizeof(pInstrument->ExpireDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["ExpireDate"] = buffer;


        gbk2utf8(
            pInstrument->StartDelivDate,
            buffer,
            sizeof(pInstrument->StartDelivDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["StartDelivDate"] = buffer;


        gbk2utf8(
            pInstrument->EndDelivDate,
            buffer,
            sizeof(pInstrument->EndDelivDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrument["EndDelivDate"] = buffer;


        json_pInstrument["InstLifePhase"] = pInstrument->InstLifePhase;


        json_pInstrument["IsTrading"] = pInstrument->IsTrading;


        json_pInstrument["PositionType"] = pInstrument->PositionType;


        json_pInstrument["PositionDateType"] = pInstrument->PositionDateType;


        json_pInstrument["LongMarginRatio"] = pInstrument->LongMarginRatio;


        json_pInstrument["ShortMarginRatio"] = pInstrument->ShortMarginRatio;


        json_pInstrument["MaxMarginSideAlgorithm"] = pInstrument->MaxMarginSideAlgorithm;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInstrument():执行结束..." << std::endl;
}

///请求查询投资者结算结果响应
void CTraderHandler::OnRspQrySettlementInfo(
    CThostFtdcSettlementInfoField * pSettlementInfo,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQrySettlementInfo():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQrySettlementInfo";

    /// 返回数据结构体转化json格式
    Json::Value json_pSettlementInfo;
    if ( pSettlementInfo != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pSettlementInfo->TradingDay,
            buffer,
            sizeof(pSettlementInfo->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfo["TradingDay"] = buffer;


        json_pSettlementInfo["SettlementID"] = pSettlementInfo->SettlementID;


        gbk2utf8(
            pSettlementInfo->BrokerID,
            buffer,
            sizeof(pSettlementInfo->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfo["BrokerID"] = buffer;


        gbk2utf8(
            pSettlementInfo->InvestorID,
            buffer,
            sizeof(pSettlementInfo->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfo["InvestorID"] = buffer;


        json_pSettlementInfo["SequenceNo"] = pSettlementInfo->SequenceNo;


        gbk2utf8(
            pSettlementInfo->Content,
            buffer,
            sizeof(pSettlementInfo->Content) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfo["Content"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQrySettlementInfo():执行结束..." << std::endl;
}

///预埋单录入请求响应
void CTraderHandler::OnRspParkedOrderInsert(
    CThostFtdcParkedOrderField * pParkedOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspParkedOrderInsert():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspParkedOrderInsert";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrder;
    if ( pParkedOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pParkedOrder->BrokerID,
            buffer,
            sizeof(pParkedOrder->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["BrokerID"] = buffer;


        gbk2utf8(
            pParkedOrder->InvestorID,
            buffer,
            sizeof(pParkedOrder->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["InvestorID"] = buffer;


        gbk2utf8(
            pParkedOrder->InstrumentID,
            buffer,
            sizeof(pParkedOrder->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["InstrumentID"] = buffer;


        gbk2utf8(
            pParkedOrder->OrderRef,
            buffer,
            sizeof(pParkedOrder->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["OrderRef"] = buffer;


        gbk2utf8(
            pParkedOrder->UserID,
            buffer,
            sizeof(pParkedOrder->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["UserID"] = buffer;


        json_pParkedOrder["OrderPriceType"] = pParkedOrder->OrderPriceType;


        json_pParkedOrder["Direction"] = pParkedOrder->Direction;


        gbk2utf8(
            pParkedOrder->CombOffsetFlag,
            buffer,
            sizeof(pParkedOrder->CombOffsetFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["CombOffsetFlag"] = buffer;


        gbk2utf8(
            pParkedOrder->CombHedgeFlag,
            buffer,
            sizeof(pParkedOrder->CombHedgeFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["CombHedgeFlag"] = buffer;


        json_pParkedOrder["LimitPrice"] = pParkedOrder->LimitPrice;


        json_pParkedOrder["VolumeTotalOriginal"] = pParkedOrder->VolumeTotalOriginal;


        json_pParkedOrder["TimeCondition"] = pParkedOrder->TimeCondition;


        gbk2utf8(
            pParkedOrder->GTDDate,
            buffer,
            sizeof(pParkedOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["GTDDate"] = buffer;


        json_pParkedOrder["VolumeCondition"] = pParkedOrder->VolumeCondition;


        json_pParkedOrder["MinVolume"] = pParkedOrder->MinVolume;


        json_pParkedOrder["ContingentCondition"] = pParkedOrder->ContingentCondition;


        json_pParkedOrder["StopPrice"] = pParkedOrder->StopPrice;


        json_pParkedOrder["ForceCloseReason"] = pParkedOrder->ForceCloseReason;


        json_pParkedOrder["IsAutoSuspend"] = pParkedOrder->IsAutoSuspend;


        gbk2utf8(
            pParkedOrder->BusinessUnit,
            buffer,
            sizeof(pParkedOrder->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["BusinessUnit"] = buffer;


        json_pParkedOrder["RequestID"] = pParkedOrder->RequestID;


        json_pParkedOrder["UserForceClose"] = pParkedOrder->UserForceClose;


        gbk2utf8(
            pParkedOrder->ExchangeID,
            buffer,
            sizeof(pParkedOrder->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["ExchangeID"] = buffer;


        gbk2utf8(
            pParkedOrder->ParkedOrderID,
            buffer,
            sizeof(pParkedOrder->ParkedOrderID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["ParkedOrderID"] = buffer;


        json_pParkedOrder["UserType"] = pParkedOrder->UserType;


        json_pParkedOrder["Status"] = pParkedOrder->Status;


        json_pParkedOrder["ErrorID"] = pParkedOrder->ErrorID;


        gbk2utf8(
            pParkedOrder->ErrorMsg,
            buffer,
            sizeof(pParkedOrder->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["ErrorMsg"] = buffer;


        json_pParkedOrder["IsSwapOrder"] = pParkedOrder->IsSwapOrder;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspParkedOrderInsert():执行结束..." << std::endl;
}

///请求查询交易所响应
void CTraderHandler::OnRspQryExchange(
    CThostFtdcExchangeField * pExchange,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryExchange():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchange";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchange;
    if ( pExchange != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pExchange->ExchangeID,
            buffer,
            sizeof(pExchange->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchange["ExchangeID"] = buffer;


        gbk2utf8(
            pExchange->ExchangeName,
            buffer,
            sizeof(pExchange->ExchangeName) * 3 // 字符串转化变长的风险保障
        );
        json_pExchange["ExchangeName"] = buffer;


        json_pExchange["ExchangeProperty"] = pExchange->ExchangeProperty;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryExchange():执行结束..." << std::endl;
}

///报单操作请求响应
void CTraderHandler::OnRspOrderAction(
    CThostFtdcInputOrderActionField * pInputOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspOrderAction():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pInputOrderAction;
    if ( pInputOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInputOrderAction->BrokerID,
            buffer,
            sizeof(pInputOrderAction->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrderAction["BrokerID"] = buffer;


        gbk2utf8(
            pInputOrderAction->InvestorID,
            buffer,
            sizeof(pInputOrderAction->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrderAction["InvestorID"] = buffer;


        json_pInputOrderAction["OrderActionRef"] = pInputOrderAction->OrderActionRef;


        gbk2utf8(
            pInputOrderAction->OrderRef,
            buffer,
            sizeof(pInputOrderAction->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrderAction["OrderRef"] = buffer;


        json_pInputOrderAction["RequestID"] = pInputOrderAction->RequestID;


        json_pInputOrderAction["FrontID"] = pInputOrderAction->FrontID;


        json_pInputOrderAction["SessionID"] = pInputOrderAction->SessionID;


        gbk2utf8(
            pInputOrderAction->ExchangeID,
            buffer,
            sizeof(pInputOrderAction->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrderAction["ExchangeID"] = buffer;


        gbk2utf8(
            pInputOrderAction->OrderSysID,
            buffer,
            sizeof(pInputOrderAction->OrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrderAction["OrderSysID"] = buffer;


        json_pInputOrderAction["ActionFlag"] = pInputOrderAction->ActionFlag;


        json_pInputOrderAction["LimitPrice"] = pInputOrderAction->LimitPrice;


        json_pInputOrderAction["VolumeChange"] = pInputOrderAction->VolumeChange;


        gbk2utf8(
            pInputOrderAction->UserID,
            buffer,
            sizeof(pInputOrderAction->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrderAction["UserID"] = buffer;


        gbk2utf8(
            pInputOrderAction->InstrumentID,
            buffer,
            sizeof(pInputOrderAction->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrderAction["InstrumentID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspOrderAction():执行结束..." << std::endl;
}

///请求查询投资者响应
void CTraderHandler::OnRspQryInvestor(
    CThostFtdcInvestorField * pInvestor,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryInvestor():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestor";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestor;
    if ( pInvestor != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInvestor->InvestorID,
            buffer,
            sizeof(pInvestor->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["InvestorID"] = buffer;


        gbk2utf8(
            pInvestor->BrokerID,
            buffer,
            sizeof(pInvestor->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["BrokerID"] = buffer;


        gbk2utf8(
            pInvestor->InvestorGroupID,
            buffer,
            sizeof(pInvestor->InvestorGroupID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["InvestorGroupID"] = buffer;


        gbk2utf8(
            pInvestor->InvestorName,
            buffer,
            sizeof(pInvestor->InvestorName) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["InvestorName"] = buffer;


        json_pInvestor["IdentifiedCardType"] = pInvestor->IdentifiedCardType;


        gbk2utf8(
            pInvestor->IdentifiedCardNo,
            buffer,
            sizeof(pInvestor->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["IdentifiedCardNo"] = buffer;


        json_pInvestor["IsActive"] = pInvestor->IsActive;


        gbk2utf8(
            pInvestor->Telephone,
            buffer,
            sizeof(pInvestor->Telephone) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["Telephone"] = buffer;


        gbk2utf8(
            pInvestor->Address,
            buffer,
            sizeof(pInvestor->Address) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["Address"] = buffer;


        gbk2utf8(
            pInvestor->OpenDate,
            buffer,
            sizeof(pInvestor->OpenDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["OpenDate"] = buffer;


        gbk2utf8(
            pInvestor->Mobile,
            buffer,
            sizeof(pInvestor->Mobile) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["Mobile"] = buffer;


        gbk2utf8(
            pInvestor->CommModelID,
            buffer,
            sizeof(pInvestor->CommModelID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["CommModelID"] = buffer;


        gbk2utf8(
            pInvestor->MarginModelID,
            buffer,
            sizeof(pInvestor->MarginModelID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestor["MarginModelID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInvestor():执行结束..." << std::endl;
}

///删除预埋单响应
void CTraderHandler::OnRspRemoveParkedOrder(
    CThostFtdcRemoveParkedOrderField * pRemoveParkedOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspRemoveParkedOrder():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspRemoveParkedOrder";

    /// 返回数据结构体转化json格式
    Json::Value json_pRemoveParkedOrder;
    if ( pRemoveParkedOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pRemoveParkedOrder->BrokerID,
            buffer,
            sizeof(pRemoveParkedOrder->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRemoveParkedOrder["BrokerID"] = buffer;


        gbk2utf8(
            pRemoveParkedOrder->InvestorID,
            buffer,
            sizeof(pRemoveParkedOrder->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pRemoveParkedOrder["InvestorID"] = buffer;


        gbk2utf8(
            pRemoveParkedOrder->ParkedOrderID,
            buffer,
            sizeof(pRemoveParkedOrder->ParkedOrderID) * 3 // 字符串转化变长的风险保障
        );
        json_pRemoveParkedOrder["ParkedOrderID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspRemoveParkedOrder():执行结束..." << std::endl;
}

///请求查询投资者品种/跨品种保证金响应
void CTraderHandler::OnRspQryInvestorProductGroupMargin(
    CThostFtdcInvestorProductGroupMarginField * pInvestorProductGroupMargin,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryInvestorProductGroupMargin():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorProductGroupMargin";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorProductGroupMargin;
    if ( pInvestorProductGroupMargin != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInvestorProductGroupMargin->ProductGroupID,
            buffer,
            sizeof(pInvestorProductGroupMargin->ProductGroupID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorProductGroupMargin["ProductGroupID"] = buffer;


        gbk2utf8(
            pInvestorProductGroupMargin->BrokerID,
            buffer,
            sizeof(pInvestorProductGroupMargin->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorProductGroupMargin["BrokerID"] = buffer;


        gbk2utf8(
            pInvestorProductGroupMargin->InvestorID,
            buffer,
            sizeof(pInvestorProductGroupMargin->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorProductGroupMargin["InvestorID"] = buffer;


        gbk2utf8(
            pInvestorProductGroupMargin->TradingDay,
            buffer,
            sizeof(pInvestorProductGroupMargin->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorProductGroupMargin["TradingDay"] = buffer;


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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInvestorProductGroupMargin():执行结束..." << std::endl;
}

///请求查询转帐银行响应
void CTraderHandler::OnRspQryTransferBank(
    CThostFtdcTransferBankField * pTransferBank,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryTransferBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTransferBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pTransferBank;
    if ( pTransferBank != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pTransferBank->BankID,
            buffer,
            sizeof(pTransferBank->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferBank["BankID"] = buffer;


        gbk2utf8(
            pTransferBank->BankBrchID,
            buffer,
            sizeof(pTransferBank->BankBrchID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferBank["BankBrchID"] = buffer;


        gbk2utf8(
            pTransferBank->BankName,
            buffer,
            sizeof(pTransferBank->BankName) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferBank["BankName"] = buffer;


        json_pTransferBank["IsActive"] = pTransferBank->IsActive;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryTransferBank():执行结束..." << std::endl;
}

///请求查询经纪公司交易算法响应
void CTraderHandler::OnRspQryBrokerTradingAlgos(
    CThostFtdcBrokerTradingAlgosField * pBrokerTradingAlgos,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryBrokerTradingAlgos():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryBrokerTradingAlgos";

    /// 返回数据结构体转化json格式
    Json::Value json_pBrokerTradingAlgos;
    if ( pBrokerTradingAlgos != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pBrokerTradingAlgos->BrokerID,
            buffer,
            sizeof(pBrokerTradingAlgos->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pBrokerTradingAlgos["BrokerID"] = buffer;


        gbk2utf8(
            pBrokerTradingAlgos->ExchangeID,
            buffer,
            sizeof(pBrokerTradingAlgos->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pBrokerTradingAlgos["ExchangeID"] = buffer;


        gbk2utf8(
            pBrokerTradingAlgos->InstrumentID,
            buffer,
            sizeof(pBrokerTradingAlgos->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pBrokerTradingAlgos["InstrumentID"] = buffer;


        json_pBrokerTradingAlgos["HandlePositionAlgoID"] = pBrokerTradingAlgos->HandlePositionAlgoID;


        json_pBrokerTradingAlgos["FindMarginRateAlgoID"] = pBrokerTradingAlgos->FindMarginRateAlgoID;


        json_pBrokerTradingAlgos["HandleTradingAccountAlgoID"] = pBrokerTradingAlgos->HandleTradingAccountAlgoID;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryBrokerTradingAlgos():执行结束..." << std::endl;
}

///请求查询产品响应
void CTraderHandler::OnRspQryProduct(
    CThostFtdcProductField * pProduct,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryProduct():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryProduct";

    /// 返回数据结构体转化json格式
    Json::Value json_pProduct;
    if ( pProduct != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pProduct->ProductID,
            buffer,
            sizeof(pProduct->ProductID) * 3 // 字符串转化变长的风险保障
        );
        json_pProduct["ProductID"] = buffer;


        gbk2utf8(
            pProduct->ProductName,
            buffer,
            sizeof(pProduct->ProductName) * 3 // 字符串转化变长的风险保障
        );
        json_pProduct["ProductName"] = buffer;


        gbk2utf8(
            pProduct->ExchangeID,
            buffer,
            sizeof(pProduct->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pProduct["ExchangeID"] = buffer;


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


        gbk2utf8(
            pProduct->TradeCurrencyID,
            buffer,
            sizeof(pProduct->TradeCurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pProduct["TradeCurrencyID"] = buffer;


        json_pProduct["MortgageFundUseRange"] = pProduct->MortgageFundUseRange;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryProduct():执行结束..." << std::endl;
}

///请求查询合约保证金率响应
void CTraderHandler::OnRspQryInstrumentMarginRate(
    CThostFtdcInstrumentMarginRateField * pInstrumentMarginRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryInstrumentMarginRate():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInstrumentMarginRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pInstrumentMarginRate;
    if ( pInstrumentMarginRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInstrumentMarginRate->InstrumentID,
            buffer,
            sizeof(pInstrumentMarginRate->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentMarginRate["InstrumentID"] = buffer;


        json_pInstrumentMarginRate["InvestorRange"] = pInstrumentMarginRate->InvestorRange;


        gbk2utf8(
            pInstrumentMarginRate->BrokerID,
            buffer,
            sizeof(pInstrumentMarginRate->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentMarginRate["BrokerID"] = buffer;


        gbk2utf8(
            pInstrumentMarginRate->InvestorID,
            buffer,
            sizeof(pInstrumentMarginRate->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentMarginRate["InvestorID"] = buffer;


        json_pInstrumentMarginRate["HedgeFlag"] = pInstrumentMarginRate->HedgeFlag;


        json_pInstrumentMarginRate["LongMarginRatioByMoney"] = pInstrumentMarginRate->LongMarginRatioByMoney;


        json_pInstrumentMarginRate["LongMarginRatioByVolume"] = pInstrumentMarginRate->LongMarginRatioByVolume;


        json_pInstrumentMarginRate["ShortMarginRatioByMoney"] = pInstrumentMarginRate->ShortMarginRatioByMoney;


        json_pInstrumentMarginRate["ShortMarginRatioByVolume"] = pInstrumentMarginRate->ShortMarginRatioByVolume;


        json_pInstrumentMarginRate["IsRelative"] = pInstrumentMarginRate->IsRelative;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInstrumentMarginRate():执行结束..." << std::endl;
}

///查询保证金监管系统经纪公司资金账户密钥响应
void CTraderHandler::OnRspQryCFMMCTradingAccountKey(
    CThostFtdcCFMMCTradingAccountKeyField * pCFMMCTradingAccountKey,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryCFMMCTradingAccountKey():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryCFMMCTradingAccountKey";

    /// 返回数据结构体转化json格式
    Json::Value json_pCFMMCTradingAccountKey;
    if ( pCFMMCTradingAccountKey != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pCFMMCTradingAccountKey->BrokerID,
            buffer,
            sizeof(pCFMMCTradingAccountKey->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountKey["BrokerID"] = buffer;


        gbk2utf8(
            pCFMMCTradingAccountKey->ParticipantID,
            buffer,
            sizeof(pCFMMCTradingAccountKey->ParticipantID) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountKey["ParticipantID"] = buffer;


        gbk2utf8(
            pCFMMCTradingAccountKey->AccountID,
            buffer,
            sizeof(pCFMMCTradingAccountKey->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountKey["AccountID"] = buffer;


        json_pCFMMCTradingAccountKey["KeyID"] = pCFMMCTradingAccountKey->KeyID;


        gbk2utf8(
            pCFMMCTradingAccountKey->CurrentKey,
            buffer,
            sizeof(pCFMMCTradingAccountKey->CurrentKey) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountKey["CurrentKey"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryCFMMCTradingAccountKey():执行结束..." << std::endl;
}

///登录请求响应
void CTraderHandler::OnRspUserLogin(
    CThostFtdcRspUserLoginField * pRspUserLogin,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspUserLogin():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserLogin";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspUserLogin;
    if ( pRspUserLogin != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pRspUserLogin->TradingDay,
            buffer,
            sizeof(pRspUserLogin->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["TradingDay"] = buffer;


        gbk2utf8(
            pRspUserLogin->LoginTime,
            buffer,
            sizeof(pRspUserLogin->LoginTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["LoginTime"] = buffer;


        gbk2utf8(
            pRspUserLogin->BrokerID,
            buffer,
            sizeof(pRspUserLogin->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["BrokerID"] = buffer;


        gbk2utf8(
            pRspUserLogin->UserID,
            buffer,
            sizeof(pRspUserLogin->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["UserID"] = buffer;


        gbk2utf8(
            pRspUserLogin->SystemName,
            buffer,
            sizeof(pRspUserLogin->SystemName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["SystemName"] = buffer;


        json_pRspUserLogin["FrontID"] = pRspUserLogin->FrontID;


        json_pRspUserLogin["SessionID"] = pRspUserLogin->SessionID;


        gbk2utf8(
            pRspUserLogin->MaxOrderRef,
            buffer,
            sizeof(pRspUserLogin->MaxOrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["MaxOrderRef"] = buffer;


        gbk2utf8(
            pRspUserLogin->SHFETime,
            buffer,
            sizeof(pRspUserLogin->SHFETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["SHFETime"] = buffer;


        gbk2utf8(
            pRspUserLogin->DCETime,
            buffer,
            sizeof(pRspUserLogin->DCETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["DCETime"] = buffer;


        gbk2utf8(
            pRspUserLogin->CZCETime,
            buffer,
            sizeof(pRspUserLogin->CZCETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["CZCETime"] = buffer;


        gbk2utf8(
            pRspUserLogin->FFEXTime,
            buffer,
            sizeof(pRspUserLogin->FFEXTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["FFEXTime"] = buffer;


        gbk2utf8(
            pRspUserLogin->INETime,
            buffer,
            sizeof(pRspUserLogin->INETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["INETime"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspUserLogin():执行结束..." << std::endl;
}

///期货发起期货资金转银行应答
void CTraderHandler::OnRspFromFutureToBankByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspFromFutureToBankByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspFromFutureToBankByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqTransfer;
    if ( pReqTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pReqTransfer->TradeCode,
            buffer,
            sizeof(pReqTransfer->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradeCode"] = buffer;


        gbk2utf8(
            pReqTransfer->BankID,
            buffer,
            sizeof(pReqTransfer->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankID"] = buffer;


        gbk2utf8(
            pReqTransfer->BankBranchID,
            buffer,
            sizeof(pReqTransfer->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankBranchID"] = buffer;


        gbk2utf8(
            pReqTransfer->BrokerID,
            buffer,
            sizeof(pReqTransfer->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BrokerID"] = buffer;


        gbk2utf8(
            pReqTransfer->BrokerBranchID,
            buffer,
            sizeof(pReqTransfer->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BrokerBranchID"] = buffer;


        gbk2utf8(
            pReqTransfer->TradeDate,
            buffer,
            sizeof(pReqTransfer->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradeDate"] = buffer;


        gbk2utf8(
            pReqTransfer->TradeTime,
            buffer,
            sizeof(pReqTransfer->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradeTime"] = buffer;


        gbk2utf8(
            pReqTransfer->BankSerial,
            buffer,
            sizeof(pReqTransfer->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankSerial"] = buffer;


        gbk2utf8(
            pReqTransfer->TradingDay,
            buffer,
            sizeof(pReqTransfer->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradingDay"] = buffer;


        json_pReqTransfer["PlateSerial"] = pReqTransfer->PlateSerial;


        json_pReqTransfer["LastFragment"] = pReqTransfer->LastFragment;


        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;


        gbk2utf8(
            pReqTransfer->CustomerName,
            buffer,
            sizeof(pReqTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CustomerName"] = buffer;


        json_pReqTransfer["IdCardType"] = pReqTransfer->IdCardType;


        gbk2utf8(
            pReqTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pReqTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["IdentifiedCardNo"] = buffer;


        json_pReqTransfer["CustType"] = pReqTransfer->CustType;


        gbk2utf8(
            pReqTransfer->BankAccount,
            buffer,
            sizeof(pReqTransfer->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankAccount"] = buffer;


        gbk2utf8(
            pReqTransfer->BankPassWord,
            buffer,
            sizeof(pReqTransfer->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankPassWord"] = buffer;


        gbk2utf8(
            pReqTransfer->AccountID,
            buffer,
            sizeof(pReqTransfer->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["AccountID"] = buffer;


        gbk2utf8(
            pReqTransfer->Password,
            buffer,
            sizeof(pReqTransfer->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["Password"] = buffer;


        json_pReqTransfer["InstallID"] = pReqTransfer->InstallID;


        json_pReqTransfer["FutureSerial"] = pReqTransfer->FutureSerial;


        gbk2utf8(
            pReqTransfer->UserID,
            buffer,
            sizeof(pReqTransfer->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["UserID"] = buffer;


        json_pReqTransfer["VerifyCertNoFlag"] = pReqTransfer->VerifyCertNoFlag;


        gbk2utf8(
            pReqTransfer->CurrencyID,
            buffer,
            sizeof(pReqTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CurrencyID"] = buffer;


        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;


        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;


        json_pReqTransfer["FeePayFlag"] = pReqTransfer->FeePayFlag;


        json_pReqTransfer["CustFee"] = pReqTransfer->CustFee;


        json_pReqTransfer["BrokerFee"] = pReqTransfer->BrokerFee;


        gbk2utf8(
            pReqTransfer->Message,
            buffer,
            sizeof(pReqTransfer->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["Message"] = buffer;


        gbk2utf8(
            pReqTransfer->Digest,
            buffer,
            sizeof(pReqTransfer->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["Digest"] = buffer;


        json_pReqTransfer["BankAccType"] = pReqTransfer->BankAccType;


        gbk2utf8(
            pReqTransfer->DeviceID,
            buffer,
            sizeof(pReqTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["DeviceID"] = buffer;


        json_pReqTransfer["BankSecuAccType"] = pReqTransfer->BankSecuAccType;


        gbk2utf8(
            pReqTransfer->BrokerIDByBank,
            buffer,
            sizeof(pReqTransfer->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BrokerIDByBank"] = buffer;


        gbk2utf8(
            pReqTransfer->BankSecuAcc,
            buffer,
            sizeof(pReqTransfer->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankSecuAcc"] = buffer;


        json_pReqTransfer["BankPwdFlag"] = pReqTransfer->BankPwdFlag;


        json_pReqTransfer["SecuPwdFlag"] = pReqTransfer->SecuPwdFlag;


        gbk2utf8(
            pReqTransfer->OperNo,
            buffer,
            sizeof(pReqTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["OperNo"] = buffer;


        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;


        json_pReqTransfer["TID"] = pReqTransfer->TID;


        json_pReqTransfer["TransferStatus"] = pReqTransfer->TransferStatus;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspFromFutureToBankByFuture():执行结束..." << std::endl;
}

///请求查询监控中心用户令牌
void CTraderHandler::OnRspQueryCFMMCTradingAccountToken(
    CThostFtdcQueryCFMMCTradingAccountTokenField * pQueryCFMMCTradingAccountToken,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQueryCFMMCTradingAccountToken():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQueryCFMMCTradingAccountToken";

    /// 返回数据结构体转化json格式
    Json::Value json_pQueryCFMMCTradingAccountToken;
    if ( pQueryCFMMCTradingAccountToken != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pQueryCFMMCTradingAccountToken->BrokerID,
            buffer,
            sizeof(pQueryCFMMCTradingAccountToken->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pQueryCFMMCTradingAccountToken["BrokerID"] = buffer;


        gbk2utf8(
            pQueryCFMMCTradingAccountToken->InvestorID,
            buffer,
            sizeof(pQueryCFMMCTradingAccountToken->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pQueryCFMMCTradingAccountToken["InvestorID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQueryCFMMCTradingAccountToken():执行结束..." << std::endl;
}

///请求查询签约银行响应
void CTraderHandler::OnRspQryContractBank(
    CThostFtdcContractBankField * pContractBank,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryContractBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryContractBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pContractBank;
    if ( pContractBank != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pContractBank->BrokerID,
            buffer,
            sizeof(pContractBank->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pContractBank["BrokerID"] = buffer;


        gbk2utf8(
            pContractBank->BankID,
            buffer,
            sizeof(pContractBank->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pContractBank["BankID"] = buffer;


        gbk2utf8(
            pContractBank->BankBrchID,
            buffer,
            sizeof(pContractBank->BankBrchID) * 3 // 字符串转化变长的风险保障
        );
        json_pContractBank["BankBrchID"] = buffer;


        gbk2utf8(
            pContractBank->BankName,
            buffer,
            sizeof(pContractBank->BankName) * 3 // 字符串转化变长的风险保障
        );
        json_pContractBank["BankName"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryContractBank():执行结束..." << std::endl;
}

///报单录入请求响应
void CTraderHandler::OnRspOrderInsert(
    CThostFtdcInputOrderField * pInputOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspOrderInsert():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspOrderInsert";

    /// 返回数据结构体转化json格式
    Json::Value json_pInputOrder;
    if ( pInputOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInputOrder->BrokerID,
            buffer,
            sizeof(pInputOrder->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["BrokerID"] = buffer;


        gbk2utf8(
            pInputOrder->InvestorID,
            buffer,
            sizeof(pInputOrder->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["InvestorID"] = buffer;


        gbk2utf8(
            pInputOrder->InstrumentID,
            buffer,
            sizeof(pInputOrder->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["InstrumentID"] = buffer;


        gbk2utf8(
            pInputOrder->OrderRef,
            buffer,
            sizeof(pInputOrder->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["OrderRef"] = buffer;


        gbk2utf8(
            pInputOrder->UserID,
            buffer,
            sizeof(pInputOrder->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["UserID"] = buffer;


        json_pInputOrder["OrderPriceType"] = pInputOrder->OrderPriceType;


        json_pInputOrder["Direction"] = pInputOrder->Direction;


        gbk2utf8(
            pInputOrder->CombOffsetFlag,
            buffer,
            sizeof(pInputOrder->CombOffsetFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["CombOffsetFlag"] = buffer;


        gbk2utf8(
            pInputOrder->CombHedgeFlag,
            buffer,
            sizeof(pInputOrder->CombHedgeFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["CombHedgeFlag"] = buffer;


        json_pInputOrder["LimitPrice"] = pInputOrder->LimitPrice;


        json_pInputOrder["VolumeTotalOriginal"] = pInputOrder->VolumeTotalOriginal;


        json_pInputOrder["TimeCondition"] = pInputOrder->TimeCondition;


        gbk2utf8(
            pInputOrder->GTDDate,
            buffer,
            sizeof(pInputOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["GTDDate"] = buffer;


        json_pInputOrder["VolumeCondition"] = pInputOrder->VolumeCondition;


        json_pInputOrder["MinVolume"] = pInputOrder->MinVolume;


        json_pInputOrder["ContingentCondition"] = pInputOrder->ContingentCondition;


        json_pInputOrder["StopPrice"] = pInputOrder->StopPrice;


        json_pInputOrder["ForceCloseReason"] = pInputOrder->ForceCloseReason;


        json_pInputOrder["IsAutoSuspend"] = pInputOrder->IsAutoSuspend;


        gbk2utf8(
            pInputOrder->BusinessUnit,
            buffer,
            sizeof(pInputOrder->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["BusinessUnit"] = buffer;


        json_pInputOrder["RequestID"] = pInputOrder->RequestID;


        json_pInputOrder["UserForceClose"] = pInputOrder->UserForceClose;


        json_pInputOrder["IsSwapOrder"] = pInputOrder->IsSwapOrder;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspOrderInsert():执行结束..." << std::endl;
}

///请求查询仓单折抵信息响应
void CTraderHandler::OnRspQryEWarrantOffset(
    CThostFtdcEWarrantOffsetField * pEWarrantOffset,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryEWarrantOffset():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryEWarrantOffset";

    /// 返回数据结构体转化json格式
    Json::Value json_pEWarrantOffset;
    if ( pEWarrantOffset != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pEWarrantOffset->TradingDay,
            buffer,
            sizeof(pEWarrantOffset->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pEWarrantOffset["TradingDay"] = buffer;


        gbk2utf8(
            pEWarrantOffset->BrokerID,
            buffer,
            sizeof(pEWarrantOffset->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pEWarrantOffset["BrokerID"] = buffer;


        gbk2utf8(
            pEWarrantOffset->InvestorID,
            buffer,
            sizeof(pEWarrantOffset->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pEWarrantOffset["InvestorID"] = buffer;


        gbk2utf8(
            pEWarrantOffset->ExchangeID,
            buffer,
            sizeof(pEWarrantOffset->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pEWarrantOffset["ExchangeID"] = buffer;


        gbk2utf8(
            pEWarrantOffset->InstrumentID,
            buffer,
            sizeof(pEWarrantOffset->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pEWarrantOffset["InstrumentID"] = buffer;


        json_pEWarrantOffset["Direction"] = pEWarrantOffset->Direction;


        json_pEWarrantOffset["HedgeFlag"] = pEWarrantOffset->HedgeFlag;


        json_pEWarrantOffset["Volume"] = pEWarrantOffset->Volume;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryEWarrantOffset():执行结束..." << std::endl;
}

///用户口令更新请求响应
void CTraderHandler::OnRspUserPasswordUpdate(
    CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspUserPasswordUpdate():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserPasswordUpdate";

    /// 返回数据结构体转化json格式
    Json::Value json_pUserPasswordUpdate;
    if ( pUserPasswordUpdate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pUserPasswordUpdate->BrokerID,
            buffer,
            sizeof(pUserPasswordUpdate->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pUserPasswordUpdate["BrokerID"] = buffer;


        gbk2utf8(
            pUserPasswordUpdate->UserID,
            buffer,
            sizeof(pUserPasswordUpdate->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pUserPasswordUpdate["UserID"] = buffer;


        gbk2utf8(
            pUserPasswordUpdate->OldPassword,
            buffer,
            sizeof(pUserPasswordUpdate->OldPassword) * 3 // 字符串转化变长的风险保障
        );
        json_pUserPasswordUpdate["OldPassword"] = buffer;


        gbk2utf8(
            pUserPasswordUpdate->NewPassword,
            buffer,
            sizeof(pUserPasswordUpdate->NewPassword) * 3 // 字符串转化变长的风险保障
        );
        json_pUserPasswordUpdate["NewPassword"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspUserPasswordUpdate():执行结束..." << std::endl;
}

///请求查询交易所调整保证金率响应
void CTraderHandler::OnRspQryExchangeMarginRateAdjust(
    CThostFtdcExchangeMarginRateAdjustField * pExchangeMarginRateAdjust,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryExchangeMarginRateAdjust():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchangeMarginRateAdjust";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchangeMarginRateAdjust;
    if ( pExchangeMarginRateAdjust != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pExchangeMarginRateAdjust->BrokerID,
            buffer,
            sizeof(pExchangeMarginRateAdjust->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchangeMarginRateAdjust["BrokerID"] = buffer;


        gbk2utf8(
            pExchangeMarginRateAdjust->InstrumentID,
            buffer,
            sizeof(pExchangeMarginRateAdjust->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchangeMarginRateAdjust["InstrumentID"] = buffer;


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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryExchangeMarginRateAdjust():执行结束..." << std::endl;
}

///期货发起银行资金转期货应答
void CTraderHandler::OnRspFromBankToFutureByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspFromBankToFutureByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspFromBankToFutureByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqTransfer;
    if ( pReqTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pReqTransfer->TradeCode,
            buffer,
            sizeof(pReqTransfer->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradeCode"] = buffer;


        gbk2utf8(
            pReqTransfer->BankID,
            buffer,
            sizeof(pReqTransfer->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankID"] = buffer;


        gbk2utf8(
            pReqTransfer->BankBranchID,
            buffer,
            sizeof(pReqTransfer->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankBranchID"] = buffer;


        gbk2utf8(
            pReqTransfer->BrokerID,
            buffer,
            sizeof(pReqTransfer->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BrokerID"] = buffer;


        gbk2utf8(
            pReqTransfer->BrokerBranchID,
            buffer,
            sizeof(pReqTransfer->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BrokerBranchID"] = buffer;


        gbk2utf8(
            pReqTransfer->TradeDate,
            buffer,
            sizeof(pReqTransfer->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradeDate"] = buffer;


        gbk2utf8(
            pReqTransfer->TradeTime,
            buffer,
            sizeof(pReqTransfer->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradeTime"] = buffer;


        gbk2utf8(
            pReqTransfer->BankSerial,
            buffer,
            sizeof(pReqTransfer->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankSerial"] = buffer;


        gbk2utf8(
            pReqTransfer->TradingDay,
            buffer,
            sizeof(pReqTransfer->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["TradingDay"] = buffer;


        json_pReqTransfer["PlateSerial"] = pReqTransfer->PlateSerial;


        json_pReqTransfer["LastFragment"] = pReqTransfer->LastFragment;


        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;


        gbk2utf8(
            pReqTransfer->CustomerName,
            buffer,
            sizeof(pReqTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CustomerName"] = buffer;


        json_pReqTransfer["IdCardType"] = pReqTransfer->IdCardType;


        gbk2utf8(
            pReqTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pReqTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["IdentifiedCardNo"] = buffer;


        json_pReqTransfer["CustType"] = pReqTransfer->CustType;


        gbk2utf8(
            pReqTransfer->BankAccount,
            buffer,
            sizeof(pReqTransfer->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankAccount"] = buffer;


        gbk2utf8(
            pReqTransfer->BankPassWord,
            buffer,
            sizeof(pReqTransfer->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankPassWord"] = buffer;


        gbk2utf8(
            pReqTransfer->AccountID,
            buffer,
            sizeof(pReqTransfer->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["AccountID"] = buffer;


        gbk2utf8(
            pReqTransfer->Password,
            buffer,
            sizeof(pReqTransfer->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["Password"] = buffer;


        json_pReqTransfer["InstallID"] = pReqTransfer->InstallID;


        json_pReqTransfer["FutureSerial"] = pReqTransfer->FutureSerial;


        gbk2utf8(
            pReqTransfer->UserID,
            buffer,
            sizeof(pReqTransfer->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["UserID"] = buffer;


        json_pReqTransfer["VerifyCertNoFlag"] = pReqTransfer->VerifyCertNoFlag;


        gbk2utf8(
            pReqTransfer->CurrencyID,
            buffer,
            sizeof(pReqTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CurrencyID"] = buffer;


        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;


        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;


        json_pReqTransfer["FeePayFlag"] = pReqTransfer->FeePayFlag;


        json_pReqTransfer["CustFee"] = pReqTransfer->CustFee;


        json_pReqTransfer["BrokerFee"] = pReqTransfer->BrokerFee;


        gbk2utf8(
            pReqTransfer->Message,
            buffer,
            sizeof(pReqTransfer->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["Message"] = buffer;


        gbk2utf8(
            pReqTransfer->Digest,
            buffer,
            sizeof(pReqTransfer->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["Digest"] = buffer;


        json_pReqTransfer["BankAccType"] = pReqTransfer->BankAccType;


        gbk2utf8(
            pReqTransfer->DeviceID,
            buffer,
            sizeof(pReqTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["DeviceID"] = buffer;


        json_pReqTransfer["BankSecuAccType"] = pReqTransfer->BankSecuAccType;


        gbk2utf8(
            pReqTransfer->BrokerIDByBank,
            buffer,
            sizeof(pReqTransfer->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BrokerIDByBank"] = buffer;


        gbk2utf8(
            pReqTransfer->BankSecuAcc,
            buffer,
            sizeof(pReqTransfer->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["BankSecuAcc"] = buffer;


        json_pReqTransfer["BankPwdFlag"] = pReqTransfer->BankPwdFlag;


        json_pReqTransfer["SecuPwdFlag"] = pReqTransfer->SecuPwdFlag;


        gbk2utf8(
            pReqTransfer->OperNo,
            buffer,
            sizeof(pReqTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["OperNo"] = buffer;


        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;


        json_pReqTransfer["TID"] = pReqTransfer->TID;


        json_pReqTransfer["TransferStatus"] = pReqTransfer->TransferStatus;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspFromBankToFutureByFuture():执行结束..." << std::endl;
}

///请求查询投资者持仓明细响应
void CTraderHandler::OnRspQryInvestorPositionCombineDetail(
    CThostFtdcInvestorPositionCombineDetailField * pInvestorPositionCombineDetail,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryInvestorPositionCombineDetail():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorPositionCombineDetail";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorPositionCombineDetail;
    if ( pInvestorPositionCombineDetail != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInvestorPositionCombineDetail->TradingDay,
            buffer,
            sizeof(pInvestorPositionCombineDetail->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["TradingDay"] = buffer;


        gbk2utf8(
            pInvestorPositionCombineDetail->OpenDate,
            buffer,
            sizeof(pInvestorPositionCombineDetail->OpenDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["OpenDate"] = buffer;


        gbk2utf8(
            pInvestorPositionCombineDetail->ExchangeID,
            buffer,
            sizeof(pInvestorPositionCombineDetail->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["ExchangeID"] = buffer;


        json_pInvestorPositionCombineDetail["SettlementID"] = pInvestorPositionCombineDetail->SettlementID;


        gbk2utf8(
            pInvestorPositionCombineDetail->BrokerID,
            buffer,
            sizeof(pInvestorPositionCombineDetail->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["BrokerID"] = buffer;


        gbk2utf8(
            pInvestorPositionCombineDetail->InvestorID,
            buffer,
            sizeof(pInvestorPositionCombineDetail->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["InvestorID"] = buffer;


        gbk2utf8(
            pInvestorPositionCombineDetail->ComTradeID,
            buffer,
            sizeof(pInvestorPositionCombineDetail->ComTradeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["ComTradeID"] = buffer;


        gbk2utf8(
            pInvestorPositionCombineDetail->TradeID,
            buffer,
            sizeof(pInvestorPositionCombineDetail->TradeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["TradeID"] = buffer;


        gbk2utf8(
            pInvestorPositionCombineDetail->InstrumentID,
            buffer,
            sizeof(pInvestorPositionCombineDetail->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["InstrumentID"] = buffer;


        json_pInvestorPositionCombineDetail["HedgeFlag"] = pInvestorPositionCombineDetail->HedgeFlag;


        json_pInvestorPositionCombineDetail["Direction"] = pInvestorPositionCombineDetail->Direction;


        json_pInvestorPositionCombineDetail["TotalAmt"] = pInvestorPositionCombineDetail->TotalAmt;


        json_pInvestorPositionCombineDetail["Margin"] = pInvestorPositionCombineDetail->Margin;


        json_pInvestorPositionCombineDetail["ExchMargin"] = pInvestorPositionCombineDetail->ExchMargin;


        json_pInvestorPositionCombineDetail["MarginRateByMoney"] = pInvestorPositionCombineDetail->MarginRateByMoney;


        json_pInvestorPositionCombineDetail["MarginRateByVolume"] = pInvestorPositionCombineDetail->MarginRateByVolume;


        json_pInvestorPositionCombineDetail["LegID"] = pInvestorPositionCombineDetail->LegID;


        json_pInvestorPositionCombineDetail["LegMultiple"] = pInvestorPositionCombineDetail->LegMultiple;


        gbk2utf8(
            pInvestorPositionCombineDetail->CombInstrumentID,
            buffer,
            sizeof(pInvestorPositionCombineDetail->CombInstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionCombineDetail["CombInstrumentID"] = buffer;


        json_pInvestorPositionCombineDetail["TradeGroupID"] = pInvestorPositionCombineDetail->TradeGroupID;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInvestorPositionCombineDetail():执行结束..." << std::endl;
}

///请求查询银期签约关系响应
void CTraderHandler::OnRspQryAccountregister(
    CThostFtdcAccountregisterField * pAccountregister,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryAccountregister():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryAccountregister";

    /// 返回数据结构体转化json格式
    Json::Value json_pAccountregister;
    if ( pAccountregister != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pAccountregister->TradeDay,
            buffer,
            sizeof(pAccountregister->TradeDay) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["TradeDay"] = buffer;


        gbk2utf8(
            pAccountregister->BankID,
            buffer,
            sizeof(pAccountregister->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["BankID"] = buffer;


        gbk2utf8(
            pAccountregister->BankBranchID,
            buffer,
            sizeof(pAccountregister->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["BankBranchID"] = buffer;


        gbk2utf8(
            pAccountregister->BankAccount,
            buffer,
            sizeof(pAccountregister->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["BankAccount"] = buffer;


        gbk2utf8(
            pAccountregister->BrokerID,
            buffer,
            sizeof(pAccountregister->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["BrokerID"] = buffer;


        gbk2utf8(
            pAccountregister->BrokerBranchID,
            buffer,
            sizeof(pAccountregister->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["BrokerBranchID"] = buffer;


        gbk2utf8(
            pAccountregister->AccountID,
            buffer,
            sizeof(pAccountregister->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["AccountID"] = buffer;


        json_pAccountregister["IdCardType"] = pAccountregister->IdCardType;


        gbk2utf8(
            pAccountregister->IdentifiedCardNo,
            buffer,
            sizeof(pAccountregister->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["IdentifiedCardNo"] = buffer;


        gbk2utf8(
            pAccountregister->CustomerName,
            buffer,
            sizeof(pAccountregister->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["CustomerName"] = buffer;


        gbk2utf8(
            pAccountregister->CurrencyID,
            buffer,
            sizeof(pAccountregister->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["CurrencyID"] = buffer;


        json_pAccountregister["OpenOrDestroy"] = pAccountregister->OpenOrDestroy;


        gbk2utf8(
            pAccountregister->RegDate,
            buffer,
            sizeof(pAccountregister->RegDate) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["RegDate"] = buffer;


        gbk2utf8(
            pAccountregister->OutDate,
            buffer,
            sizeof(pAccountregister->OutDate) * 3 // 字符串转化变长的风险保障
        );
        json_pAccountregister["OutDate"] = buffer;


        json_pAccountregister["TID"] = pAccountregister->TID;


        json_pAccountregister["CustType"] = pAccountregister->CustType;


        json_pAccountregister["BankAccType"] = pAccountregister->BankAccType;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryAccountregister():执行结束..." << std::endl;
}

///请求查询二级代理操作员银期权限响应
void CTraderHandler::OnRspQrySecAgentACIDMap(
    CThostFtdcSecAgentACIDMapField * pSecAgentACIDMap,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQrySecAgentACIDMap():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQrySecAgentACIDMap";

    /// 返回数据结构体转化json格式
    Json::Value json_pSecAgentACIDMap;
    if ( pSecAgentACIDMap != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pSecAgentACIDMap->BrokerID,
            buffer,
            sizeof(pSecAgentACIDMap->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pSecAgentACIDMap["BrokerID"] = buffer;


        gbk2utf8(
            pSecAgentACIDMap->UserID,
            buffer,
            sizeof(pSecAgentACIDMap->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pSecAgentACIDMap["UserID"] = buffer;


        gbk2utf8(
            pSecAgentACIDMap->AccountID,
            buffer,
            sizeof(pSecAgentACIDMap->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pSecAgentACIDMap["AccountID"] = buffer;


        gbk2utf8(
            pSecAgentACIDMap->CurrencyID,
            buffer,
            sizeof(pSecAgentACIDMap->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pSecAgentACIDMap["CurrencyID"] = buffer;


        gbk2utf8(
            pSecAgentACIDMap->BrokerSecAgentID,
            buffer,
            sizeof(pSecAgentACIDMap->BrokerSecAgentID) * 3 // 字符串转化变长的风险保障
        );
        json_pSecAgentACIDMap["BrokerSecAgentID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQrySecAgentACIDMap():执行结束..." << std::endl;
}

///请求查询交易编码响应
void CTraderHandler::OnRspQryTradingCode(
    CThostFtdcTradingCodeField * pTradingCode,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryTradingCode():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTradingCode";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingCode;
    if ( pTradingCode != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pTradingCode->InvestorID,
            buffer,
            sizeof(pTradingCode->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingCode["InvestorID"] = buffer;


        gbk2utf8(
            pTradingCode->BrokerID,
            buffer,
            sizeof(pTradingCode->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingCode["BrokerID"] = buffer;


        gbk2utf8(
            pTradingCode->ExchangeID,
            buffer,
            sizeof(pTradingCode->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingCode["ExchangeID"] = buffer;


        gbk2utf8(
            pTradingCode->ClientID,
            buffer,
            sizeof(pTradingCode->ClientID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingCode["ClientID"] = buffer;


        json_pTradingCode["IsActive"] = pTradingCode->IsActive;


        json_pTradingCode["ClientIDType"] = pTradingCode->ClientIDType;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryTradingCode():执行结束..." << std::endl;
}

///请求查询结算信息确认响应
void CTraderHandler::OnRspQrySettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQrySettlementInfoConfirm():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQrySettlementInfoConfirm";

    /// 返回数据结构体转化json格式
    Json::Value json_pSettlementInfoConfirm;
    if ( pSettlementInfoConfirm != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pSettlementInfoConfirm->BrokerID,
            buffer,
            sizeof(pSettlementInfoConfirm->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["BrokerID"] = buffer;


        gbk2utf8(
            pSettlementInfoConfirm->InvestorID,
            buffer,
            sizeof(pSettlementInfoConfirm->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["InvestorID"] = buffer;


        gbk2utf8(
            pSettlementInfoConfirm->ConfirmDate,
            buffer,
            sizeof(pSettlementInfoConfirm->ConfirmDate) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["ConfirmDate"] = buffer;


        gbk2utf8(
            pSettlementInfoConfirm->ConfirmTime,
            buffer,
            sizeof(pSettlementInfoConfirm->ConfirmTime) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["ConfirmTime"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQrySettlementInfoConfirm():执行结束..." << std::endl;
}

///请求查询转帐流水响应
void CTraderHandler::OnRspQryTransferSerial(
    CThostFtdcTransferSerialField * pTransferSerial,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryTransferSerial():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTransferSerial";

    /// 返回数据结构体转化json格式
    Json::Value json_pTransferSerial;
    if ( pTransferSerial != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pTransferSerial["PlateSerial"] = pTransferSerial->PlateSerial;


        gbk2utf8(
            pTransferSerial->TradeDate,
            buffer,
            sizeof(pTransferSerial->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["TradeDate"] = buffer;


        gbk2utf8(
            pTransferSerial->TradingDay,
            buffer,
            sizeof(pTransferSerial->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["TradingDay"] = buffer;


        gbk2utf8(
            pTransferSerial->TradeTime,
            buffer,
            sizeof(pTransferSerial->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["TradeTime"] = buffer;


        gbk2utf8(
            pTransferSerial->TradeCode,
            buffer,
            sizeof(pTransferSerial->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["TradeCode"] = buffer;


        json_pTransferSerial["SessionID"] = pTransferSerial->SessionID;


        gbk2utf8(
            pTransferSerial->BankID,
            buffer,
            sizeof(pTransferSerial->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["BankID"] = buffer;


        gbk2utf8(
            pTransferSerial->BankBranchID,
            buffer,
            sizeof(pTransferSerial->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["BankBranchID"] = buffer;


        json_pTransferSerial["BankAccType"] = pTransferSerial->BankAccType;


        gbk2utf8(
            pTransferSerial->BankAccount,
            buffer,
            sizeof(pTransferSerial->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["BankAccount"] = buffer;


        gbk2utf8(
            pTransferSerial->BankSerial,
            buffer,
            sizeof(pTransferSerial->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["BankSerial"] = buffer;


        gbk2utf8(
            pTransferSerial->BrokerID,
            buffer,
            sizeof(pTransferSerial->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["BrokerID"] = buffer;


        gbk2utf8(
            pTransferSerial->BrokerBranchID,
            buffer,
            sizeof(pTransferSerial->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["BrokerBranchID"] = buffer;


        json_pTransferSerial["FutureAccType"] = pTransferSerial->FutureAccType;


        gbk2utf8(
            pTransferSerial->AccountID,
            buffer,
            sizeof(pTransferSerial->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["AccountID"] = buffer;


        gbk2utf8(
            pTransferSerial->InvestorID,
            buffer,
            sizeof(pTransferSerial->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["InvestorID"] = buffer;


        json_pTransferSerial["FutureSerial"] = pTransferSerial->FutureSerial;


        json_pTransferSerial["IdCardType"] = pTransferSerial->IdCardType;


        gbk2utf8(
            pTransferSerial->IdentifiedCardNo,
            buffer,
            sizeof(pTransferSerial->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["IdentifiedCardNo"] = buffer;


        gbk2utf8(
            pTransferSerial->CurrencyID,
            buffer,
            sizeof(pTransferSerial->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["CurrencyID"] = buffer;


        json_pTransferSerial["TradeAmount"] = pTransferSerial->TradeAmount;


        json_pTransferSerial["CustFee"] = pTransferSerial->CustFee;


        json_pTransferSerial["BrokerFee"] = pTransferSerial->BrokerFee;


        json_pTransferSerial["AvailabilityFlag"] = pTransferSerial->AvailabilityFlag;


        gbk2utf8(
            pTransferSerial->OperatorCode,
            buffer,
            sizeof(pTransferSerial->OperatorCode) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["OperatorCode"] = buffer;


        gbk2utf8(
            pTransferSerial->BankNewAccount,
            buffer,
            sizeof(pTransferSerial->BankNewAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["BankNewAccount"] = buffer;


        json_pTransferSerial["ErrorID"] = pTransferSerial->ErrorID;


        gbk2utf8(
            pTransferSerial->ErrorMsg,
            buffer,
            sizeof(pTransferSerial->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pTransferSerial["ErrorMsg"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryTransferSerial():执行结束..." << std::endl;
}

///请求查询投资者持仓响应
void CTraderHandler::OnRspQryInvestorPosition(
    CThostFtdcInvestorPositionField * pInvestorPosition,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryInvestorPosition():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorPosition";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorPosition;
    if ( pInvestorPosition != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInvestorPosition->InstrumentID,
            buffer,
            sizeof(pInvestorPosition->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPosition["InstrumentID"] = buffer;


        gbk2utf8(
            pInvestorPosition->BrokerID,
            buffer,
            sizeof(pInvestorPosition->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPosition["BrokerID"] = buffer;


        gbk2utf8(
            pInvestorPosition->InvestorID,
            buffer,
            sizeof(pInvestorPosition->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPosition["InvestorID"] = buffer;


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


        gbk2utf8(
            pInvestorPosition->TradingDay,
            buffer,
            sizeof(pInvestorPosition->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPosition["TradingDay"] = buffer;


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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInvestorPosition():执行结束..." << std::endl;
}

///登出请求响应
void CTraderHandler::OnRspUserLogout(
    CThostFtdcUserLogoutField * pUserLogout,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspUserLogout():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserLogout";

    /// 返回数据结构体转化json格式
    Json::Value json_pUserLogout;
    if ( pUserLogout != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pUserLogout->BrokerID,
            buffer,
            sizeof(pUserLogout->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pUserLogout["BrokerID"] = buffer;


        gbk2utf8(
            pUserLogout->UserID,
            buffer,
            sizeof(pUserLogout->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pUserLogout["UserID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspUserLogout():执行结束..." << std::endl;
}

///请求查询投资者持仓明细响应
void CTraderHandler::OnRspQryInvestorPositionDetail(
    CThostFtdcInvestorPositionDetailField * pInvestorPositionDetail,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryInvestorPositionDetail():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInvestorPositionDetail";

    /// 返回数据结构体转化json格式
    Json::Value json_pInvestorPositionDetail;
    if ( pInvestorPositionDetail != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInvestorPositionDetail->InstrumentID,
            buffer,
            sizeof(pInvestorPositionDetail->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["InstrumentID"] = buffer;


        gbk2utf8(
            pInvestorPositionDetail->BrokerID,
            buffer,
            sizeof(pInvestorPositionDetail->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["BrokerID"] = buffer;


        gbk2utf8(
            pInvestorPositionDetail->InvestorID,
            buffer,
            sizeof(pInvestorPositionDetail->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["InvestorID"] = buffer;


        json_pInvestorPositionDetail["HedgeFlag"] = pInvestorPositionDetail->HedgeFlag;


        json_pInvestorPositionDetail["Direction"] = pInvestorPositionDetail->Direction;


        gbk2utf8(
            pInvestorPositionDetail->OpenDate,
            buffer,
            sizeof(pInvestorPositionDetail->OpenDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["OpenDate"] = buffer;


        gbk2utf8(
            pInvestorPositionDetail->TradeID,
            buffer,
            sizeof(pInvestorPositionDetail->TradeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["TradeID"] = buffer;


        json_pInvestorPositionDetail["Volume"] = pInvestorPositionDetail->Volume;


        json_pInvestorPositionDetail["OpenPrice"] = pInvestorPositionDetail->OpenPrice;


        gbk2utf8(
            pInvestorPositionDetail->TradingDay,
            buffer,
            sizeof(pInvestorPositionDetail->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["TradingDay"] = buffer;


        json_pInvestorPositionDetail["SettlementID"] = pInvestorPositionDetail->SettlementID;


        json_pInvestorPositionDetail["TradeType"] = pInvestorPositionDetail->TradeType;


        gbk2utf8(
            pInvestorPositionDetail->CombInstrumentID,
            buffer,
            sizeof(pInvestorPositionDetail->CombInstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["CombInstrumentID"] = buffer;


        gbk2utf8(
            pInvestorPositionDetail->ExchangeID,
            buffer,
            sizeof(pInvestorPositionDetail->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInvestorPositionDetail["ExchangeID"] = buffer;


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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInvestorPositionDetail():执行结束..." << std::endl;
}

///请求查询客户通知响应
void CTraderHandler::OnRspQryNotice(
    CThostFtdcNoticeField * pNotice,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryNotice():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryNotice";

    /// 返回数据结构体转化json格式
    Json::Value json_pNotice;
    if ( pNotice != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pNotice->BrokerID,
            buffer,
            sizeof(pNotice->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotice["BrokerID"] = buffer;


        gbk2utf8(
            pNotice->Content,
            buffer,
            sizeof(pNotice->Content) * 3 // 字符串转化变长的风险保障
        );
        json_pNotice["Content"] = buffer;


        gbk2utf8(
            pNotice->SequenceLabel,
            buffer,
            sizeof(pNotice->SequenceLabel) * 3 // 字符串转化变长的风险保障
        );
        json_pNotice["SequenceLabel"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryNotice():执行结束..." << std::endl;
}

///请求查询经纪公司交易参数响应
void CTraderHandler::OnRspQryBrokerTradingParams(
    CThostFtdcBrokerTradingParamsField * pBrokerTradingParams,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryBrokerTradingParams():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryBrokerTradingParams";

    /// 返回数据结构体转化json格式
    Json::Value json_pBrokerTradingParams;
    if ( pBrokerTradingParams != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pBrokerTradingParams->BrokerID,
            buffer,
            sizeof(pBrokerTradingParams->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pBrokerTradingParams["BrokerID"] = buffer;


        gbk2utf8(
            pBrokerTradingParams->InvestorID,
            buffer,
            sizeof(pBrokerTradingParams->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pBrokerTradingParams["InvestorID"] = buffer;


        json_pBrokerTradingParams["MarginPriceType"] = pBrokerTradingParams->MarginPriceType;


        json_pBrokerTradingParams["Algorithm"] = pBrokerTradingParams->Algorithm;


        json_pBrokerTradingParams["AvailIncludeCloseProfit"] = pBrokerTradingParams->AvailIncludeCloseProfit;


        gbk2utf8(
            pBrokerTradingParams->CurrencyID,
            buffer,
            sizeof(pBrokerTradingParams->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pBrokerTradingParams["CurrencyID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryBrokerTradingParams():执行结束..." << std::endl;
}

///请求查询交易所保证金率响应
void CTraderHandler::OnRspQryExchangeMarginRate(
    CThostFtdcExchangeMarginRateField * pExchangeMarginRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryExchangeMarginRate():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchangeMarginRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchangeMarginRate;
    if ( pExchangeMarginRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pExchangeMarginRate->BrokerID,
            buffer,
            sizeof(pExchangeMarginRate->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchangeMarginRate["BrokerID"] = buffer;


        gbk2utf8(
            pExchangeMarginRate->InstrumentID,
            buffer,
            sizeof(pExchangeMarginRate->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchangeMarginRate["InstrumentID"] = buffer;


        json_pExchangeMarginRate["HedgeFlag"] = pExchangeMarginRate->HedgeFlag;


        json_pExchangeMarginRate["LongMarginRatioByMoney"] = pExchangeMarginRate->LongMarginRatioByMoney;


        json_pExchangeMarginRate["LongMarginRatioByVolume"] = pExchangeMarginRate->LongMarginRatioByVolume;


        json_pExchangeMarginRate["ShortMarginRatioByMoney"] = pExchangeMarginRate->ShortMarginRatioByMoney;


        json_pExchangeMarginRate["ShortMarginRatioByVolume"] = pExchangeMarginRate->ShortMarginRatioByVolume;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryExchangeMarginRate():执行结束..." << std::endl;
}

///请求查询预埋单响应
void CTraderHandler::OnRspQryParkedOrder(
    CThostFtdcParkedOrderField * pParkedOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryParkedOrder():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryParkedOrder";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrder;
    if ( pParkedOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pParkedOrder->BrokerID,
            buffer,
            sizeof(pParkedOrder->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["BrokerID"] = buffer;


        gbk2utf8(
            pParkedOrder->InvestorID,
            buffer,
            sizeof(pParkedOrder->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["InvestorID"] = buffer;


        gbk2utf8(
            pParkedOrder->InstrumentID,
            buffer,
            sizeof(pParkedOrder->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["InstrumentID"] = buffer;


        gbk2utf8(
            pParkedOrder->OrderRef,
            buffer,
            sizeof(pParkedOrder->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["OrderRef"] = buffer;


        gbk2utf8(
            pParkedOrder->UserID,
            buffer,
            sizeof(pParkedOrder->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["UserID"] = buffer;


        json_pParkedOrder["OrderPriceType"] = pParkedOrder->OrderPriceType;


        json_pParkedOrder["Direction"] = pParkedOrder->Direction;


        gbk2utf8(
            pParkedOrder->CombOffsetFlag,
            buffer,
            sizeof(pParkedOrder->CombOffsetFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["CombOffsetFlag"] = buffer;


        gbk2utf8(
            pParkedOrder->CombHedgeFlag,
            buffer,
            sizeof(pParkedOrder->CombHedgeFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["CombHedgeFlag"] = buffer;


        json_pParkedOrder["LimitPrice"] = pParkedOrder->LimitPrice;


        json_pParkedOrder["VolumeTotalOriginal"] = pParkedOrder->VolumeTotalOriginal;


        json_pParkedOrder["TimeCondition"] = pParkedOrder->TimeCondition;


        gbk2utf8(
            pParkedOrder->GTDDate,
            buffer,
            sizeof(pParkedOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["GTDDate"] = buffer;


        json_pParkedOrder["VolumeCondition"] = pParkedOrder->VolumeCondition;


        json_pParkedOrder["MinVolume"] = pParkedOrder->MinVolume;


        json_pParkedOrder["ContingentCondition"] = pParkedOrder->ContingentCondition;


        json_pParkedOrder["StopPrice"] = pParkedOrder->StopPrice;


        json_pParkedOrder["ForceCloseReason"] = pParkedOrder->ForceCloseReason;


        json_pParkedOrder["IsAutoSuspend"] = pParkedOrder->IsAutoSuspend;


        gbk2utf8(
            pParkedOrder->BusinessUnit,
            buffer,
            sizeof(pParkedOrder->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["BusinessUnit"] = buffer;


        json_pParkedOrder["RequestID"] = pParkedOrder->RequestID;


        json_pParkedOrder["UserForceClose"] = pParkedOrder->UserForceClose;


        gbk2utf8(
            pParkedOrder->ExchangeID,
            buffer,
            sizeof(pParkedOrder->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["ExchangeID"] = buffer;


        gbk2utf8(
            pParkedOrder->ParkedOrderID,
            buffer,
            sizeof(pParkedOrder->ParkedOrderID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["ParkedOrderID"] = buffer;


        json_pParkedOrder["UserType"] = pParkedOrder->UserType;


        json_pParkedOrder["Status"] = pParkedOrder->Status;


        json_pParkedOrder["ErrorID"] = pParkedOrder->ErrorID;


        gbk2utf8(
            pParkedOrder->ErrorMsg,
            buffer,
            sizeof(pParkedOrder->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["ErrorMsg"] = buffer;


        json_pParkedOrder["IsSwapOrder"] = pParkedOrder->IsSwapOrder;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryParkedOrder():执行结束..." << std::endl;
}

///期货发起查询银行余额应答
void CTraderHandler::OnRspQueryBankAccountMoneyByFuture(
    CThostFtdcReqQueryAccountField * pReqQueryAccount,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQueryBankAccountMoneyByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQueryBankAccountMoneyByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqQueryAccount;
    if ( pReqQueryAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pReqQueryAccount->TradeCode,
            buffer,
            sizeof(pReqQueryAccount->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["TradeCode"] = buffer;


        gbk2utf8(
            pReqQueryAccount->BankID,
            buffer,
            sizeof(pReqQueryAccount->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BankID"] = buffer;


        gbk2utf8(
            pReqQueryAccount->BankBranchID,
            buffer,
            sizeof(pReqQueryAccount->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BankBranchID"] = buffer;


        gbk2utf8(
            pReqQueryAccount->BrokerID,
            buffer,
            sizeof(pReqQueryAccount->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BrokerID"] = buffer;


        gbk2utf8(
            pReqQueryAccount->BrokerBranchID,
            buffer,
            sizeof(pReqQueryAccount->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BrokerBranchID"] = buffer;


        gbk2utf8(
            pReqQueryAccount->TradeDate,
            buffer,
            sizeof(pReqQueryAccount->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["TradeDate"] = buffer;


        gbk2utf8(
            pReqQueryAccount->TradeTime,
            buffer,
            sizeof(pReqQueryAccount->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["TradeTime"] = buffer;


        gbk2utf8(
            pReqQueryAccount->BankSerial,
            buffer,
            sizeof(pReqQueryAccount->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BankSerial"] = buffer;


        gbk2utf8(
            pReqQueryAccount->TradingDay,
            buffer,
            sizeof(pReqQueryAccount->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["TradingDay"] = buffer;


        json_pReqQueryAccount["PlateSerial"] = pReqQueryAccount->PlateSerial;


        json_pReqQueryAccount["LastFragment"] = pReqQueryAccount->LastFragment;


        json_pReqQueryAccount["SessionID"] = pReqQueryAccount->SessionID;


        gbk2utf8(
            pReqQueryAccount->CustomerName,
            buffer,
            sizeof(pReqQueryAccount->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["CustomerName"] = buffer;


        json_pReqQueryAccount["IdCardType"] = pReqQueryAccount->IdCardType;


        gbk2utf8(
            pReqQueryAccount->IdentifiedCardNo,
            buffer,
            sizeof(pReqQueryAccount->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["IdentifiedCardNo"] = buffer;


        json_pReqQueryAccount["CustType"] = pReqQueryAccount->CustType;


        gbk2utf8(
            pReqQueryAccount->BankAccount,
            buffer,
            sizeof(pReqQueryAccount->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BankAccount"] = buffer;


        gbk2utf8(
            pReqQueryAccount->BankPassWord,
            buffer,
            sizeof(pReqQueryAccount->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BankPassWord"] = buffer;


        gbk2utf8(
            pReqQueryAccount->AccountID,
            buffer,
            sizeof(pReqQueryAccount->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["AccountID"] = buffer;


        gbk2utf8(
            pReqQueryAccount->Password,
            buffer,
            sizeof(pReqQueryAccount->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["Password"] = buffer;


        json_pReqQueryAccount["FutureSerial"] = pReqQueryAccount->FutureSerial;


        json_pReqQueryAccount["InstallID"] = pReqQueryAccount->InstallID;


        gbk2utf8(
            pReqQueryAccount->UserID,
            buffer,
            sizeof(pReqQueryAccount->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["UserID"] = buffer;


        json_pReqQueryAccount["VerifyCertNoFlag"] = pReqQueryAccount->VerifyCertNoFlag;


        gbk2utf8(
            pReqQueryAccount->CurrencyID,
            buffer,
            sizeof(pReqQueryAccount->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["CurrencyID"] = buffer;


        gbk2utf8(
            pReqQueryAccount->Digest,
            buffer,
            sizeof(pReqQueryAccount->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["Digest"] = buffer;


        json_pReqQueryAccount["BankAccType"] = pReqQueryAccount->BankAccType;


        gbk2utf8(
            pReqQueryAccount->DeviceID,
            buffer,
            sizeof(pReqQueryAccount->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["DeviceID"] = buffer;


        json_pReqQueryAccount["BankSecuAccType"] = pReqQueryAccount->BankSecuAccType;


        gbk2utf8(
            pReqQueryAccount->BrokerIDByBank,
            buffer,
            sizeof(pReqQueryAccount->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BrokerIDByBank"] = buffer;


        gbk2utf8(
            pReqQueryAccount->BankSecuAcc,
            buffer,
            sizeof(pReqQueryAccount->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["BankSecuAcc"] = buffer;


        json_pReqQueryAccount["BankPwdFlag"] = pReqQueryAccount->BankPwdFlag;


        json_pReqQueryAccount["SecuPwdFlag"] = pReqQueryAccount->SecuPwdFlag;


        gbk2utf8(
            pReqQueryAccount->OperNo,
            buffer,
            sizeof(pReqQueryAccount->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["OperNo"] = buffer;


        json_pReqQueryAccount["RequestID"] = pReqQueryAccount->RequestID;


        json_pReqQueryAccount["TID"] = pReqQueryAccount->TID;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQueryBankAccountMoneyByFuture():执行结束..." << std::endl;
}

///客户端认证响应
void CTraderHandler::OnRspAuthenticate(
    CThostFtdcRspAuthenticateField * pRspAuthenticateField,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspAuthenticate():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspAuthenticate";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspAuthenticateField;
    if ( pRspAuthenticateField != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pRspAuthenticateField->BrokerID,
            buffer,
            sizeof(pRspAuthenticateField->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspAuthenticateField["BrokerID"] = buffer;


        gbk2utf8(
            pRspAuthenticateField->UserID,
            buffer,
            sizeof(pRspAuthenticateField->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspAuthenticateField["UserID"] = buffer;


        gbk2utf8(
            pRspAuthenticateField->UserProductInfo,
            buffer,
            sizeof(pRspAuthenticateField->UserProductInfo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspAuthenticateField["UserProductInfo"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspAuthenticate():执行结束..." << std::endl;
}

///查询最大报单数量响应
void CTraderHandler::OnRspQueryMaxOrderVolume(
    CThostFtdcQueryMaxOrderVolumeField * pQueryMaxOrderVolume,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQueryMaxOrderVolume():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQueryMaxOrderVolume";

    /// 返回数据结构体转化json格式
    Json::Value json_pQueryMaxOrderVolume;
    if ( pQueryMaxOrderVolume != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pQueryMaxOrderVolume->BrokerID,
            buffer,
            sizeof(pQueryMaxOrderVolume->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pQueryMaxOrderVolume["BrokerID"] = buffer;


        gbk2utf8(
            pQueryMaxOrderVolume->InvestorID,
            buffer,
            sizeof(pQueryMaxOrderVolume->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pQueryMaxOrderVolume["InvestorID"] = buffer;


        gbk2utf8(
            pQueryMaxOrderVolume->InstrumentID,
            buffer,
            sizeof(pQueryMaxOrderVolume->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pQueryMaxOrderVolume["InstrumentID"] = buffer;


        json_pQueryMaxOrderVolume["Direction"] = pQueryMaxOrderVolume->Direction;


        json_pQueryMaxOrderVolume["OffsetFlag"] = pQueryMaxOrderVolume->OffsetFlag;


        json_pQueryMaxOrderVolume["HedgeFlag"] = pQueryMaxOrderVolume->HedgeFlag;


        json_pQueryMaxOrderVolume["MaxVolume"] = pQueryMaxOrderVolume->MaxVolume;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQueryMaxOrderVolume():执行结束..." << std::endl;
}

///请求查询汇率响应
void CTraderHandler::OnRspQryExchangeRate(
    CThostFtdcExchangeRateField * pExchangeRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryExchangeRate():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryExchangeRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pExchangeRate;
    if ( pExchangeRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pExchangeRate->BrokerID,
            buffer,
            sizeof(pExchangeRate->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchangeRate["BrokerID"] = buffer;


        gbk2utf8(
            pExchangeRate->FromCurrencyID,
            buffer,
            sizeof(pExchangeRate->FromCurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchangeRate["FromCurrencyID"] = buffer;


        json_pExchangeRate["FromCurrencyUnit"] = pExchangeRate->FromCurrencyUnit;


        gbk2utf8(
            pExchangeRate->ToCurrencyID,
            buffer,
            sizeof(pExchangeRate->ToCurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pExchangeRate["ToCurrencyID"] = buffer;


        json_pExchangeRate["ExchangeRate"] = pExchangeRate->ExchangeRate;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryExchangeRate():执行结束..." << std::endl;
}

///请求查询交易通知响应
void CTraderHandler::OnRspQryTradingNotice(
    CThostFtdcTradingNoticeField * pTradingNotice,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryTradingNotice():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTradingNotice";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingNotice;
    if ( pTradingNotice != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pTradingNotice->BrokerID,
            buffer,
            sizeof(pTradingNotice->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNotice["BrokerID"] = buffer;


        json_pTradingNotice["InvestorRange"] = pTradingNotice->InvestorRange;


        gbk2utf8(
            pTradingNotice->InvestorID,
            buffer,
            sizeof(pTradingNotice->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNotice["InvestorID"] = buffer;


        json_pTradingNotice["SequenceSeries"] = pTradingNotice->SequenceSeries;


        gbk2utf8(
            pTradingNotice->UserID,
            buffer,
            sizeof(pTradingNotice->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNotice["UserID"] = buffer;


        gbk2utf8(
            pTradingNotice->SendTime,
            buffer,
            sizeof(pTradingNotice->SendTime) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNotice["SendTime"] = buffer;


        json_pTradingNotice["SequenceNo"] = pTradingNotice->SequenceNo;


        gbk2utf8(
            pTradingNotice->FieldContent,
            buffer,
            sizeof(pTradingNotice->FieldContent) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNotice["FieldContent"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryTradingNotice():执行结束..." << std::endl;
}

///预埋撤单录入请求响应
void CTraderHandler::OnRspParkedOrderAction(
    CThostFtdcParkedOrderActionField * pParkedOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspParkedOrderAction():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspParkedOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrderAction;
    if ( pParkedOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pParkedOrderAction->BrokerID,
            buffer,
            sizeof(pParkedOrderAction->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["BrokerID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->InvestorID,
            buffer,
            sizeof(pParkedOrderAction->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["InvestorID"] = buffer;


        json_pParkedOrderAction["OrderActionRef"] = pParkedOrderAction->OrderActionRef;


        gbk2utf8(
            pParkedOrderAction->OrderRef,
            buffer,
            sizeof(pParkedOrderAction->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["OrderRef"] = buffer;


        json_pParkedOrderAction["RequestID"] = pParkedOrderAction->RequestID;


        json_pParkedOrderAction["FrontID"] = pParkedOrderAction->FrontID;


        json_pParkedOrderAction["SessionID"] = pParkedOrderAction->SessionID;


        gbk2utf8(
            pParkedOrderAction->ExchangeID,
            buffer,
            sizeof(pParkedOrderAction->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["ExchangeID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->OrderSysID,
            buffer,
            sizeof(pParkedOrderAction->OrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["OrderSysID"] = buffer;


        json_pParkedOrderAction["ActionFlag"] = pParkedOrderAction->ActionFlag;


        json_pParkedOrderAction["LimitPrice"] = pParkedOrderAction->LimitPrice;


        json_pParkedOrderAction["VolumeChange"] = pParkedOrderAction->VolumeChange;


        gbk2utf8(
            pParkedOrderAction->UserID,
            buffer,
            sizeof(pParkedOrderAction->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["UserID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->InstrumentID,
            buffer,
            sizeof(pParkedOrderAction->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["InstrumentID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->ParkedOrderActionID,
            buffer,
            sizeof(pParkedOrderAction->ParkedOrderActionID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["ParkedOrderActionID"] = buffer;


        json_pParkedOrderAction["UserType"] = pParkedOrderAction->UserType;


        json_pParkedOrderAction["Status"] = pParkedOrderAction->Status;


        json_pParkedOrderAction["ErrorID"] = pParkedOrderAction->ErrorID;


        gbk2utf8(
            pParkedOrderAction->ErrorMsg,
            buffer,
            sizeof(pParkedOrderAction->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["ErrorMsg"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspParkedOrderAction():执行结束..." << std::endl;
}

///请求查询预埋撤单响应
void CTraderHandler::OnRspQryParkedOrderAction(
    CThostFtdcParkedOrderActionField * pParkedOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryParkedOrderAction():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryParkedOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pParkedOrderAction;
    if ( pParkedOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pParkedOrderAction->BrokerID,
            buffer,
            sizeof(pParkedOrderAction->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["BrokerID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->InvestorID,
            buffer,
            sizeof(pParkedOrderAction->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["InvestorID"] = buffer;


        json_pParkedOrderAction["OrderActionRef"] = pParkedOrderAction->OrderActionRef;


        gbk2utf8(
            pParkedOrderAction->OrderRef,
            buffer,
            sizeof(pParkedOrderAction->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["OrderRef"] = buffer;


        json_pParkedOrderAction["RequestID"] = pParkedOrderAction->RequestID;


        json_pParkedOrderAction["FrontID"] = pParkedOrderAction->FrontID;


        json_pParkedOrderAction["SessionID"] = pParkedOrderAction->SessionID;


        gbk2utf8(
            pParkedOrderAction->ExchangeID,
            buffer,
            sizeof(pParkedOrderAction->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["ExchangeID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->OrderSysID,
            buffer,
            sizeof(pParkedOrderAction->OrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["OrderSysID"] = buffer;


        json_pParkedOrderAction["ActionFlag"] = pParkedOrderAction->ActionFlag;


        json_pParkedOrderAction["LimitPrice"] = pParkedOrderAction->LimitPrice;


        json_pParkedOrderAction["VolumeChange"] = pParkedOrderAction->VolumeChange;


        gbk2utf8(
            pParkedOrderAction->UserID,
            buffer,
            sizeof(pParkedOrderAction->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["UserID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->InstrumentID,
            buffer,
            sizeof(pParkedOrderAction->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["InstrumentID"] = buffer;


        gbk2utf8(
            pParkedOrderAction->ParkedOrderActionID,
            buffer,
            sizeof(pParkedOrderAction->ParkedOrderActionID) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["ParkedOrderActionID"] = buffer;


        json_pParkedOrderAction["UserType"] = pParkedOrderAction->UserType;


        json_pParkedOrderAction["Status"] = pParkedOrderAction->Status;


        json_pParkedOrderAction["ErrorID"] = pParkedOrderAction->ErrorID;


        gbk2utf8(
            pParkedOrderAction->ErrorMsg,
            buffer,
            sizeof(pParkedOrderAction->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrderAction["ErrorMsg"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryParkedOrderAction():执行结束..." << std::endl;
}

///请求查询资金账户响应
void CTraderHandler::OnRspQryTradingAccount(
    CThostFtdcTradingAccountField * pTradingAccount,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryTradingAccount():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTradingAccount";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingAccount;
    if ( pTradingAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pTradingAccount->BrokerID,
            buffer,
            sizeof(pTradingAccount->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccount["BrokerID"] = buffer;


        gbk2utf8(
            pTradingAccount->AccountID,
            buffer,
            sizeof(pTradingAccount->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccount["AccountID"] = buffer;


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


        gbk2utf8(
            pTradingAccount->TradingDay,
            buffer,
            sizeof(pTradingAccount->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccount["TradingDay"] = buffer;


        json_pTradingAccount["SettlementID"] = pTradingAccount->SettlementID;


        json_pTradingAccount["Credit"] = pTradingAccount->Credit;


        json_pTradingAccount["Mortgage"] = pTradingAccount->Mortgage;


        json_pTradingAccount["ExchangeMargin"] = pTradingAccount->ExchangeMargin;


        json_pTradingAccount["DeliveryMargin"] = pTradingAccount->DeliveryMargin;


        json_pTradingAccount["ExchangeDeliveryMargin"] = pTradingAccount->ExchangeDeliveryMargin;


        json_pTradingAccount["ReserveBalance"] = pTradingAccount->ReserveBalance;


        gbk2utf8(
            pTradingAccount->CurrencyID,
            buffer,
            sizeof(pTradingAccount->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccount["CurrencyID"] = buffer;


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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryTradingAccount():执行结束..." << std::endl;
}

///资金账户口令更新请求响应
void CTraderHandler::OnRspTradingAccountPasswordUpdate(
    CThostFtdcTradingAccountPasswordUpdateField * pTradingAccountPasswordUpdate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspTradingAccountPasswordUpdate():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspTradingAccountPasswordUpdate";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingAccountPasswordUpdate;
    if ( pTradingAccountPasswordUpdate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pTradingAccountPasswordUpdate->BrokerID,
            buffer,
            sizeof(pTradingAccountPasswordUpdate->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccountPasswordUpdate["BrokerID"] = buffer;


        gbk2utf8(
            pTradingAccountPasswordUpdate->AccountID,
            buffer,
            sizeof(pTradingAccountPasswordUpdate->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccountPasswordUpdate["AccountID"] = buffer;


        gbk2utf8(
            pTradingAccountPasswordUpdate->OldPassword,
            buffer,
            sizeof(pTradingAccountPasswordUpdate->OldPassword) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccountPasswordUpdate["OldPassword"] = buffer;


        gbk2utf8(
            pTradingAccountPasswordUpdate->NewPassword,
            buffer,
            sizeof(pTradingAccountPasswordUpdate->NewPassword) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccountPasswordUpdate["NewPassword"] = buffer;


        gbk2utf8(
            pTradingAccountPasswordUpdate->CurrencyID,
            buffer,
            sizeof(pTradingAccountPasswordUpdate->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingAccountPasswordUpdate["CurrencyID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspTradingAccountPasswordUpdate():执行结束..." << std::endl;
}

///投资者结算结果确认响应
void CTraderHandler::OnRspSettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspSettlementInfoConfirm():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspSettlementInfoConfirm";

    /// 返回数据结构体转化json格式
    Json::Value json_pSettlementInfoConfirm;
    if ( pSettlementInfoConfirm != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pSettlementInfoConfirm->BrokerID,
            buffer,
            sizeof(pSettlementInfoConfirm->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["BrokerID"] = buffer;


        gbk2utf8(
            pSettlementInfoConfirm->InvestorID,
            buffer,
            sizeof(pSettlementInfoConfirm->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["InvestorID"] = buffer;


        gbk2utf8(
            pSettlementInfoConfirm->ConfirmDate,
            buffer,
            sizeof(pSettlementInfoConfirm->ConfirmDate) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["ConfirmDate"] = buffer;


        gbk2utf8(
            pSettlementInfoConfirm->ConfirmTime,
            buffer,
            sizeof(pSettlementInfoConfirm->ConfirmTime) * 3 // 字符串转化变长的风险保障
        );
        json_pSettlementInfoConfirm["ConfirmTime"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspSettlementInfoConfirm():执行结束..." << std::endl;
}

///请求查询行情响应
void CTraderHandler::OnRspQryDepthMarketData(
    CThostFtdcDepthMarketDataField * pDepthMarketData,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryDepthMarketData():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryDepthMarketData";

    /// 返回数据结构体转化json格式
    Json::Value json_pDepthMarketData;
    if ( pDepthMarketData != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pDepthMarketData->TradingDay,
            buffer,
            sizeof(pDepthMarketData->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pDepthMarketData["TradingDay"] = buffer;


        gbk2utf8(
            pDepthMarketData->InstrumentID,
            buffer,
            sizeof(pDepthMarketData->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pDepthMarketData["InstrumentID"] = buffer;


        gbk2utf8(
            pDepthMarketData->ExchangeID,
            buffer,
            sizeof(pDepthMarketData->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pDepthMarketData["ExchangeID"] = buffer;


        gbk2utf8(
            pDepthMarketData->ExchangeInstID,
            buffer,
            sizeof(pDepthMarketData->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pDepthMarketData["ExchangeInstID"] = buffer;


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


        gbk2utf8(
            pDepthMarketData->UpdateTime,
            buffer,
            sizeof(pDepthMarketData->UpdateTime) * 3 // 字符串转化变长的风险保障
        );
        json_pDepthMarketData["UpdateTime"] = buffer;


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


        gbk2utf8(
            pDepthMarketData->ActionDay,
            buffer,
            sizeof(pDepthMarketData->ActionDay) * 3 // 字符串转化变长的风险保障
        );
        json_pDepthMarketData["ActionDay"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryDepthMarketData():执行结束..." << std::endl;
}

///删除预埋撤单响应
void CTraderHandler::OnRspRemoveParkedOrderAction(
    CThostFtdcRemoveParkedOrderActionField * pRemoveParkedOrderAction,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspRemoveParkedOrderAction():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspRemoveParkedOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pRemoveParkedOrderAction;
    if ( pRemoveParkedOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pRemoveParkedOrderAction->BrokerID,
            buffer,
            sizeof(pRemoveParkedOrderAction->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRemoveParkedOrderAction["BrokerID"] = buffer;


        gbk2utf8(
            pRemoveParkedOrderAction->InvestorID,
            buffer,
            sizeof(pRemoveParkedOrderAction->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pRemoveParkedOrderAction["InvestorID"] = buffer;


        gbk2utf8(
            pRemoveParkedOrderAction->ParkedOrderActionID,
            buffer,
            sizeof(pRemoveParkedOrderAction->ParkedOrderActionID) * 3 // 字符串转化变长的风险保障
        );
        json_pRemoveParkedOrderAction["ParkedOrderActionID"] = buffer;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspRemoveParkedOrderAction():执行结束..." << std::endl;
}

///请求查询合约手续费率响应
void CTraderHandler::OnRspQryInstrumentCommissionRate(
    CThostFtdcInstrumentCommissionRateField * pInstrumentCommissionRate,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryInstrumentCommissionRate():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryInstrumentCommissionRate";

    /// 返回数据结构体转化json格式
    Json::Value json_pInstrumentCommissionRate;
    if ( pInstrumentCommissionRate != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pInstrumentCommissionRate->InstrumentID,
            buffer,
            sizeof(pInstrumentCommissionRate->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentCommissionRate["InstrumentID"] = buffer;


        json_pInstrumentCommissionRate["InvestorRange"] = pInstrumentCommissionRate->InvestorRange;


        gbk2utf8(
            pInstrumentCommissionRate->BrokerID,
            buffer,
            sizeof(pInstrumentCommissionRate->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentCommissionRate["BrokerID"] = buffer;


        gbk2utf8(
            pInstrumentCommissionRate->InvestorID,
            buffer,
            sizeof(pInstrumentCommissionRate->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentCommissionRate["InvestorID"] = buffer;


        json_pInstrumentCommissionRate["OpenRatioByMoney"] = pInstrumentCommissionRate->OpenRatioByMoney;


        json_pInstrumentCommissionRate["OpenRatioByVolume"] = pInstrumentCommissionRate->OpenRatioByVolume;


        json_pInstrumentCommissionRate["CloseRatioByMoney"] = pInstrumentCommissionRate->CloseRatioByMoney;


        json_pInstrumentCommissionRate["CloseRatioByVolume"] = pInstrumentCommissionRate->CloseRatioByVolume;


        json_pInstrumentCommissionRate["CloseTodayRatioByMoney"] = pInstrumentCommissionRate->CloseTodayRatioByMoney;


        json_pInstrumentCommissionRate["CloseTodayRatioByVolume"] = pInstrumentCommissionRate->CloseTodayRatioByVolume;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryInstrumentCommissionRate():执行结束..." << std::endl;
}

///请求查询报单响应
void CTraderHandler::OnRspQryOrder(
    CThostFtdcOrderField * pOrder,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryOrder():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryOrder";

    /// 返回数据结构体转化json格式
    Json::Value json_pOrder;
    if ( pOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pOrder->BrokerID,
            buffer,
            sizeof(pOrder->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["BrokerID"] = buffer;


        gbk2utf8(
            pOrder->InvestorID,
            buffer,
            sizeof(pOrder->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["InvestorID"] = buffer;


        gbk2utf8(
            pOrder->InstrumentID,
            buffer,
            sizeof(pOrder->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["InstrumentID"] = buffer;


        gbk2utf8(
            pOrder->OrderRef,
            buffer,
            sizeof(pOrder->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["OrderRef"] = buffer;


        gbk2utf8(
            pOrder->UserID,
            buffer,
            sizeof(pOrder->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["UserID"] = buffer;


        json_pOrder["OrderPriceType"] = pOrder->OrderPriceType;


        json_pOrder["Direction"] = pOrder->Direction;


        gbk2utf8(
            pOrder->CombOffsetFlag,
            buffer,
            sizeof(pOrder->CombOffsetFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["CombOffsetFlag"] = buffer;


        gbk2utf8(
            pOrder->CombHedgeFlag,
            buffer,
            sizeof(pOrder->CombHedgeFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["CombHedgeFlag"] = buffer;


        json_pOrder["LimitPrice"] = pOrder->LimitPrice;


        json_pOrder["VolumeTotalOriginal"] = pOrder->VolumeTotalOriginal;


        json_pOrder["TimeCondition"] = pOrder->TimeCondition;


        gbk2utf8(
            pOrder->GTDDate,
            buffer,
            sizeof(pOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["GTDDate"] = buffer;


        json_pOrder["VolumeCondition"] = pOrder->VolumeCondition;


        json_pOrder["MinVolume"] = pOrder->MinVolume;


        json_pOrder["ContingentCondition"] = pOrder->ContingentCondition;


        json_pOrder["StopPrice"] = pOrder->StopPrice;


        json_pOrder["ForceCloseReason"] = pOrder->ForceCloseReason;


        json_pOrder["IsAutoSuspend"] = pOrder->IsAutoSuspend;


        gbk2utf8(
            pOrder->BusinessUnit,
            buffer,
            sizeof(pOrder->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["BusinessUnit"] = buffer;


        json_pOrder["RequestID"] = pOrder->RequestID;


        gbk2utf8(
            pOrder->OrderLocalID,
            buffer,
            sizeof(pOrder->OrderLocalID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["OrderLocalID"] = buffer;


        gbk2utf8(
            pOrder->ExchangeID,
            buffer,
            sizeof(pOrder->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ExchangeID"] = buffer;


        gbk2utf8(
            pOrder->ParticipantID,
            buffer,
            sizeof(pOrder->ParticipantID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ParticipantID"] = buffer;


        gbk2utf8(
            pOrder->ClientID,
            buffer,
            sizeof(pOrder->ClientID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ClientID"] = buffer;


        gbk2utf8(
            pOrder->ExchangeInstID,
            buffer,
            sizeof(pOrder->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ExchangeInstID"] = buffer;


        gbk2utf8(
            pOrder->TraderID,
            buffer,
            sizeof(pOrder->TraderID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["TraderID"] = buffer;


        json_pOrder["InstallID"] = pOrder->InstallID;


        json_pOrder["OrderSubmitStatus"] = pOrder->OrderSubmitStatus;


        json_pOrder["NotifySequence"] = pOrder->NotifySequence;


        gbk2utf8(
            pOrder->TradingDay,
            buffer,
            sizeof(pOrder->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["TradingDay"] = buffer;


        json_pOrder["SettlementID"] = pOrder->SettlementID;


        gbk2utf8(
            pOrder->OrderSysID,
            buffer,
            sizeof(pOrder->OrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["OrderSysID"] = buffer;


        json_pOrder["OrderSource"] = pOrder->OrderSource;


        json_pOrder["OrderStatus"] = pOrder->OrderStatus;


        json_pOrder["OrderType"] = pOrder->OrderType;


        json_pOrder["VolumeTraded"] = pOrder->VolumeTraded;


        json_pOrder["VolumeTotal"] = pOrder->VolumeTotal;


        gbk2utf8(
            pOrder->InsertDate,
            buffer,
            sizeof(pOrder->InsertDate) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["InsertDate"] = buffer;


        gbk2utf8(
            pOrder->InsertTime,
            buffer,
            sizeof(pOrder->InsertTime) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["InsertTime"] = buffer;


        gbk2utf8(
            pOrder->ActiveTime,
            buffer,
            sizeof(pOrder->ActiveTime) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ActiveTime"] = buffer;


        gbk2utf8(
            pOrder->SuspendTime,
            buffer,
            sizeof(pOrder->SuspendTime) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["SuspendTime"] = buffer;


        gbk2utf8(
            pOrder->UpdateTime,
            buffer,
            sizeof(pOrder->UpdateTime) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["UpdateTime"] = buffer;


        gbk2utf8(
            pOrder->CancelTime,
            buffer,
            sizeof(pOrder->CancelTime) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["CancelTime"] = buffer;


        gbk2utf8(
            pOrder->ActiveTraderID,
            buffer,
            sizeof(pOrder->ActiveTraderID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ActiveTraderID"] = buffer;


        gbk2utf8(
            pOrder->ClearingPartID,
            buffer,
            sizeof(pOrder->ClearingPartID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ClearingPartID"] = buffer;


        json_pOrder["SequenceNo"] = pOrder->SequenceNo;


        json_pOrder["FrontID"] = pOrder->FrontID;


        json_pOrder["SessionID"] = pOrder->SessionID;


        gbk2utf8(
            pOrder->UserProductInfo,
            buffer,
            sizeof(pOrder->UserProductInfo) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["UserProductInfo"] = buffer;


        gbk2utf8(
            pOrder->StatusMsg,
            buffer,
            sizeof(pOrder->StatusMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["StatusMsg"] = buffer;


        json_pOrder["UserForceClose"] = pOrder->UserForceClose;


        gbk2utf8(
            pOrder->ActiveUserID,
            buffer,
            sizeof(pOrder->ActiveUserID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["ActiveUserID"] = buffer;


        json_pOrder["BrokerOrderSeq"] = pOrder->BrokerOrderSeq;


        gbk2utf8(
            pOrder->RelativeOrderSysID,
            buffer,
            sizeof(pOrder->RelativeOrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["RelativeOrderSysID"] = buffer;


        json_pOrder["ZCETotalTradedVolume"] = pOrder->ZCETotalTradedVolume;


        json_pOrder["IsSwapOrder"] = pOrder->IsSwapOrder;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryOrder():执行结束..." << std::endl;
}

///请求查询成交响应
void CTraderHandler::OnRspQryTrade(
    CThostFtdcTradeField * pTrade,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspQryTrade():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspQryTrade";

    /// 返回数据结构体转化json格式
    Json::Value json_pTrade;
    if ( pTrade != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pTrade->BrokerID,
            buffer,
            sizeof(pTrade->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["BrokerID"] = buffer;


        gbk2utf8(
            pTrade->InvestorID,
            buffer,
            sizeof(pTrade->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["InvestorID"] = buffer;


        gbk2utf8(
            pTrade->InstrumentID,
            buffer,
            sizeof(pTrade->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["InstrumentID"] = buffer;


        gbk2utf8(
            pTrade->OrderRef,
            buffer,
            sizeof(pTrade->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["OrderRef"] = buffer;


        gbk2utf8(
            pTrade->UserID,
            buffer,
            sizeof(pTrade->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["UserID"] = buffer;


        gbk2utf8(
            pTrade->ExchangeID,
            buffer,
            sizeof(pTrade->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["ExchangeID"] = buffer;


        gbk2utf8(
            pTrade->TradeID,
            buffer,
            sizeof(pTrade->TradeID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["TradeID"] = buffer;


        json_pTrade["Direction"] = pTrade->Direction;


        gbk2utf8(
            pTrade->OrderSysID,
            buffer,
            sizeof(pTrade->OrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["OrderSysID"] = buffer;


        gbk2utf8(
            pTrade->ParticipantID,
            buffer,
            sizeof(pTrade->ParticipantID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["ParticipantID"] = buffer;


        gbk2utf8(
            pTrade->ClientID,
            buffer,
            sizeof(pTrade->ClientID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["ClientID"] = buffer;


        json_pTrade["TradingRole"] = pTrade->TradingRole;


        gbk2utf8(
            pTrade->ExchangeInstID,
            buffer,
            sizeof(pTrade->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["ExchangeInstID"] = buffer;


        json_pTrade["OffsetFlag"] = pTrade->OffsetFlag;


        json_pTrade["HedgeFlag"] = pTrade->HedgeFlag;


        json_pTrade["Price"] = pTrade->Price;


        json_pTrade["Volume"] = pTrade->Volume;


        gbk2utf8(
            pTrade->TradeDate,
            buffer,
            sizeof(pTrade->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["TradeDate"] = buffer;


        gbk2utf8(
            pTrade->TradeTime,
            buffer,
            sizeof(pTrade->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["TradeTime"] = buffer;


        json_pTrade["TradeType"] = pTrade->TradeType;


        json_pTrade["PriceSource"] = pTrade->PriceSource;


        gbk2utf8(
            pTrade->TraderID,
            buffer,
            sizeof(pTrade->TraderID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["TraderID"] = buffer;


        gbk2utf8(
            pTrade->OrderLocalID,
            buffer,
            sizeof(pTrade->OrderLocalID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["OrderLocalID"] = buffer;


        gbk2utf8(
            pTrade->ClearingPartID,
            buffer,
            sizeof(pTrade->ClearingPartID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["ClearingPartID"] = buffer;


        gbk2utf8(
            pTrade->BusinessUnit,
            buffer,
            sizeof(pTrade->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["BusinessUnit"] = buffer;


        json_pTrade["SequenceNo"] = pTrade->SequenceNo;


        gbk2utf8(
            pTrade->TradingDay,
            buffer,
            sizeof(pTrade->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["TradingDay"] = buffer;


        json_pTrade["SettlementID"] = pTrade->SettlementID;


        json_pTrade["BrokerOrderSeq"] = pTrade->BrokerOrderSeq;


        json_pTrade["TradeSource"] = pTrade->TradeSource;

    }

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
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspQryTrade():执行结束..." << std::endl;
}


/**********************************************************
*                   onRtn开头的方法                         *
***********************************************************/



///期货发起查询银行余额通知
void CTraderHandler::OnRtnQueryBankBalanceByFuture(
    CThostFtdcNotifyQueryAccountField * pNotifyQueryAccount
) {
    std::cout << "OnRtnQueryBankBalanceByFuture():开始执行..." << std::endl;

    std::cout << "OnRtnQueryBankBalanceByFuture():执行结束..." << std::endl;
}

///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromBankToFutureByFuture(
    CThostFtdcRspRepealField * pRspRepeal
) {
    std::cout << "OnRtnRepealFromBankToFutureByFuture():开始执行..." << std::endl;

    std::cout << "OnRtnRepealFromBankToFutureByFuture():执行结束..." << std::endl;
}

///银行发起银行资金转期货通知
void CTraderHandler::OnRtnFromBankToFutureByBank(
    CThostFtdcRspTransferField * pRspTransfer
) {
    std::cout << "OnRtnFromBankToFutureByBank():开始执行..." << std::endl;

    std::cout << "OnRtnFromBankToFutureByBank():执行结束..." << std::endl;
}

///保证金监控中心用户令牌
void CTraderHandler::OnRtnCFMMCTradingAccountToken(
    CThostFtdcCFMMCTradingAccountTokenField * pCFMMCTradingAccountToken
) {
    std::cout << "OnRtnCFMMCTradingAccountToken():开始执行..." << std::endl;

    std::cout << "OnRtnCFMMCTradingAccountToken():执行结束..." << std::endl;
}

///合约交易状态通知
void CTraderHandler::OnRtnInstrumentStatus(
    CThostFtdcInstrumentStatusField * pInstrumentStatus
) {
    std::cout << "OnRtnInstrumentStatus():开始执行..." << std::endl;

    std::cout << "OnRtnInstrumentStatus():执行结束..." << std::endl;
}

///交易通知
void CTraderHandler::OnRtnTradingNotice(
    CThostFtdcTradingNoticeInfoField * pTradingNoticeInfo
) {
    std::cout << "OnRtnTradingNotice():开始执行..." << std::endl;

    std::cout << "OnRtnTradingNotice():执行结束..." << std::endl;
}

///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromFutureToBankByFutureManual(
    CThostFtdcRspRepealField * pRspRepeal
) {
    std::cout << "OnRtnRepealFromFutureToBankByFutureManual():开始执行..." << std::endl;

    std::cout << "OnRtnRepealFromFutureToBankByFutureManual():执行结束..." << std::endl;
}

///期货发起银行资金转期货通知
void CTraderHandler::OnRtnFromBankToFutureByFuture(
    CThostFtdcRspTransferField * pRspTransfer
) {
    std::cout << "OnRtnFromBankToFutureByFuture():开始执行..." << std::endl;

    std::cout << "OnRtnFromBankToFutureByFuture():执行结束..." << std::endl;
}

///银行发起期货资金转银行通知
void CTraderHandler::OnRtnFromFutureToBankByBank(
    CThostFtdcRspTransferField * pRspTransfer
) {
    std::cout << "OnRtnFromFutureToBankByBank():开始执行..." << std::endl;

    std::cout << "OnRtnFromFutureToBankByBank():执行结束..." << std::endl;
}

///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromBankToFutureByFutureManual(
    CThostFtdcRspRepealField * pRspRepeal
) {
    std::cout << "OnRtnRepealFromBankToFutureByFutureManual():开始执行..." << std::endl;

    std::cout << "OnRtnRepealFromBankToFutureByFutureManual():执行结束..." << std::endl;
}

///期货发起期货资金转银行通知
void CTraderHandler::OnRtnFromFutureToBankByFuture(
    CThostFtdcRspTransferField * pRspTransfer
) {
    std::cout << "OnRtnFromFutureToBankByFuture():开始执行..." << std::endl;

    std::cout << "OnRtnFromFutureToBankByFuture():执行结束..." << std::endl;
}

///银行发起变更银行账号通知
void CTraderHandler::OnRtnChangeAccountByBank(
    CThostFtdcChangeAccountField * pChangeAccount
) {
    std::cout << "OnRtnChangeAccountByBank():开始执行..." << std::endl;

    std::cout << "OnRtnChangeAccountByBank():执行结束..." << std::endl;
}

///银行发起冲正期货转银行通知
void CTraderHandler::OnRtnRepealFromFutureToBankByBank(
    CThostFtdcRspRepealField * pRspRepeal
) {
    std::cout << "OnRtnRepealFromFutureToBankByBank():开始执行..." << std::endl;

    std::cout << "OnRtnRepealFromFutureToBankByBank():执行结束..." << std::endl;
}

///银行发起银期开户通知
void CTraderHandler::OnRtnOpenAccountByBank(
    CThostFtdcOpenAccountField * pOpenAccount
) {
    std::cout << "OnRtnOpenAccountByBank():开始执行..." << std::endl;

    std::cout << "OnRtnOpenAccountByBank():执行结束..." << std::endl;
}

///成交通知
void CTraderHandler::OnRtnTrade(
    CThostFtdcTradeField * pTrade
) {
    std::cout << "OnRtnTrade():开始执行..." << std::endl;

    std::cout << "OnRtnTrade():执行结束..." << std::endl;
}

///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromFutureToBankByFuture(
    CThostFtdcRspRepealField * pRspRepeal
) {
    std::cout << "OnRtnRepealFromFutureToBankByFuture():开始执行..." << std::endl;

    std::cout << "OnRtnRepealFromFutureToBankByFuture():执行结束..." << std::endl;
}

///提示条件单校验错误
void CTraderHandler::OnRtnErrorConditionalOrder(
    CThostFtdcErrorConditionalOrderField * pErrorConditionalOrder
) {
    std::cout << "OnRtnErrorConditionalOrder():开始执行..." << std::endl;

    std::cout << "OnRtnErrorConditionalOrder():执行结束..." << std::endl;
}

///银行发起冲正银行转期货通知
void CTraderHandler::OnRtnRepealFromBankToFutureByBank(
    CThostFtdcRspRepealField * pRspRepeal
) {
    std::cout << "OnRtnRepealFromBankToFutureByBank():开始执行..." << std::endl;

    std::cout << "OnRtnRepealFromBankToFutureByBank():执行结束..." << std::endl;
}

///报单通知
void CTraderHandler::OnRtnOrder(
    CThostFtdcOrderField * pOrder
) {
    std::cout << "OnRtnOrder():开始执行..." << std::endl;

    std::cout << "OnRtnOrder():执行结束..." << std::endl;
}

///银行发起银期销户通知
void CTraderHandler::OnRtnCancelAccountByBank(
    CThostFtdcCancelAccountField * pCancelAccount
) {
    std::cout << "OnRtnCancelAccountByBank():开始执行..." << std::endl;

    std::cout << "OnRtnCancelAccountByBank():执行结束..." << std::endl;
}


/**********************************************************
*                   onErrRtn开头的方法                      *
***********************************************************/


///系统运行时期货端手工发起冲正期货转银行错误回报
void CTraderHandler::OnErrRtnRepealFutureToBankByFutureManual(
    CThostFtdcReqRepealField * pReqRepeal,
    CThostFtdcRspInfoField * pRspInfo
) {
    std::cout << "OnErrRtnRepealFutureToBankByFutureManual():开始执行..." << std::endl;

    std::cout << "OnErrRtnRepealFutureToBankByFutureManual():执行结束..." << std::endl;
}

///期货发起期货资金转银行错误回报
void CTraderHandler::OnErrRtnFutureToBankByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo
) {
    std::cout << "OnErrRtnFutureToBankByFuture():开始执行..." << std::endl;

    std::cout << "OnErrRtnFutureToBankByFuture():执行结束..." << std::endl;
}

///报单录入错误回报
void CTraderHandler::OnErrRtnOrderInsert(
    CThostFtdcInputOrderField * pInputOrder,
    CThostFtdcRspInfoField * pRspInfo
) {
    std::cout << "OnErrRtnOrderInsert():开始执行..." << std::endl;

    std::cout << "OnErrRtnOrderInsert():执行结束..." << std::endl;
}

///系统运行时期货端手工发起冲正银行转期货错误回报
void CTraderHandler::OnErrRtnRepealBankToFutureByFutureManual(
    CThostFtdcReqRepealField * pReqRepeal,
    CThostFtdcRspInfoField * pRspInfo
) {
    std::cout << "OnErrRtnRepealBankToFutureByFutureManual():开始执行..." << std::endl;

    std::cout << "OnErrRtnRepealBankToFutureByFutureManual():执行结束..." << std::endl;
}

///期货发起银行资金转期货错误回报
void CTraderHandler::OnErrRtnBankToFutureByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo
) {
    std::cout << "OnErrRtnBankToFutureByFuture():开始执行..." << std::endl;

    std::cout << "OnErrRtnBankToFutureByFuture():执行结束..." << std::endl;
}

///期货发起查询银行余额错误回报
void CTraderHandler::OnErrRtnQueryBankBalanceByFuture(
    CThostFtdcReqQueryAccountField * pReqQueryAccount,
    CThostFtdcRspInfoField * pRspInfo
) {
    std::cout << "OnErrRtnQueryBankBalanceByFuture():开始执行..." << std::endl;

    std::cout << "OnErrRtnQueryBankBalanceByFuture():执行结束..." << std::endl;
}

///报单操作错误回报
void CTraderHandler::OnErrRtnOrderAction(
    CThostFtdcOrderActionField * pOrderAction,
    CThostFtdcRspInfoField * pRspInfo
) {
    std::cout << "OnErrRtnOrderAction():开始执行..." << std::endl;

    std::cout << "OnErrRtnOrderAction():执行结束..." << std::endl;
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
    std::cout << "OnRspError():开始执行..." << std::endl;

    std::cout << "OnRspError():执行结束..." << std::endl;
}
