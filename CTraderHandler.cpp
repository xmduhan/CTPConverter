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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInstrument->ProductClass);
        json_pInstrument["ProductClass"] = buffer;



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




        sprintf(buffer,"%c",pInstrument->InstLifePhase);
        json_pInstrument["InstLifePhase"] = buffer;



        json_pInstrument["IsTrading"] = pInstrument->IsTrading;



        sprintf(buffer,"%c",pInstrument->PositionType);
        json_pInstrument["PositionType"] = buffer;




        sprintf(buffer,"%c",pInstrument->PositionDateType);
        json_pInstrument["PositionDateType"] = buffer;



        json_pInstrument["LongMarginRatio"] = pInstrument->LongMarginRatio;


        json_pInstrument["ShortMarginRatio"] = pInstrument->ShortMarginRatio;



        sprintf(buffer,"%c",pInstrument->MaxMarginSideAlgorithm);
        json_pInstrument["MaxMarginSideAlgorithm"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pParkedOrder->OrderPriceType);
        json_pParkedOrder["OrderPriceType"] = buffer;




        sprintf(buffer,"%c",pParkedOrder->Direction);
        json_pParkedOrder["Direction"] = buffer;




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



        sprintf(buffer,"%c",pParkedOrder->TimeCondition);
        json_pParkedOrder["TimeCondition"] = buffer;




        gbk2utf8(
            pParkedOrder->GTDDate,
            buffer,
            sizeof(pParkedOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["GTDDate"] = buffer;




        sprintf(buffer,"%c",pParkedOrder->VolumeCondition);
        json_pParkedOrder["VolumeCondition"] = buffer;



        json_pParkedOrder["MinVolume"] = pParkedOrder->MinVolume;



        sprintf(buffer,"%c",pParkedOrder->ContingentCondition);
        json_pParkedOrder["ContingentCondition"] = buffer;



        json_pParkedOrder["StopPrice"] = pParkedOrder->StopPrice;



        sprintf(buffer,"%c",pParkedOrder->ForceCloseReason);
        json_pParkedOrder["ForceCloseReason"] = buffer;



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




        sprintf(buffer,"%c",pParkedOrder->UserType);
        json_pParkedOrder["UserType"] = buffer;




        sprintf(buffer,"%c",pParkedOrder->Status);
        json_pParkedOrder["Status"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pExchange->ExchangeProperty);
        json_pExchange["ExchangeProperty"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInputOrderAction->ActionFlag);
        json_pInputOrderAction["ActionFlag"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInvestor->IdentifiedCardType);
        json_pInvestor["IdentifiedCardType"] = buffer;




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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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



        sprintf(buffer,"%c",pInvestorProductGroupMargin->HedgeFlag);
        json_pInvestorProductGroupMargin["HedgeFlag"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pBrokerTradingAlgos->HandlePositionAlgoID);
        json_pBrokerTradingAlgos["HandlePositionAlgoID"] = buffer;




        sprintf(buffer,"%c",pBrokerTradingAlgos->FindMarginRateAlgoID);
        json_pBrokerTradingAlgos["FindMarginRateAlgoID"] = buffer;




        sprintf(buffer,"%c",pBrokerTradingAlgos->HandleTradingAccountAlgoID);
        json_pBrokerTradingAlgos["HandleTradingAccountAlgoID"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pProduct->ProductClass);
        json_pProduct["ProductClass"] = buffer;



        json_pProduct["VolumeMultiple"] = pProduct->VolumeMultiple;


        json_pProduct["PriceTick"] = pProduct->PriceTick;


        json_pProduct["MaxMarketOrderVolume"] = pProduct->MaxMarketOrderVolume;


        json_pProduct["MinMarketOrderVolume"] = pProduct->MinMarketOrderVolume;


        json_pProduct["MaxLimitOrderVolume"] = pProduct->MaxLimitOrderVolume;


        json_pProduct["MinLimitOrderVolume"] = pProduct->MinLimitOrderVolume;



        sprintf(buffer,"%c",pProduct->PositionType);
        json_pProduct["PositionType"] = buffer;




        sprintf(buffer,"%c",pProduct->PositionDateType);
        json_pProduct["PositionDateType"] = buffer;




        sprintf(buffer,"%c",pProduct->CloseDealType);
        json_pProduct["CloseDealType"] = buffer;




        gbk2utf8(
            pProduct->TradeCurrencyID,
            buffer,
            sizeof(pProduct->TradeCurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pProduct["TradeCurrencyID"] = buffer;




        sprintf(buffer,"%c",pProduct->MortgageFundUseRange);
        json_pProduct["MortgageFundUseRange"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInstrumentMarginRate->InvestorRange);
        json_pInstrumentMarginRate["InvestorRange"] = buffer;




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




        sprintf(buffer,"%c",pInstrumentMarginRate->HedgeFlag);
        json_pInstrumentMarginRate["HedgeFlag"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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



        sprintf(buffer,"%c",pReqTransfer->LastFragment);
        json_pReqTransfer["LastFragment"] = buffer;



        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;



        gbk2utf8(
            pReqTransfer->CustomerName,
            buffer,
            sizeof(pReqTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->IdCardType);
        json_pReqTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pReqTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pReqTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->CustType);
        json_pReqTransfer["CustType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->VerifyCertNoFlag);
        json_pReqTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->CurrencyID,
            buffer,
            sizeof(pReqTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CurrencyID"] = buffer;



        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;


        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;



        sprintf(buffer,"%c",pReqTransfer->FeePayFlag);
        json_pReqTransfer["FeePayFlag"] = buffer;



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




        sprintf(buffer,"%c",pReqTransfer->BankAccType);
        json_pReqTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pReqTransfer->DeviceID,
            buffer,
            sizeof(pReqTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->BankSecuAccType);
        json_pReqTransfer["BankSecuAccType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->BankPwdFlag);
        json_pReqTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->SecuPwdFlag);
        json_pReqTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->OperNo,
            buffer,
            sizeof(pReqTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["OperNo"] = buffer;



        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;


        json_pReqTransfer["TID"] = pReqTransfer->TID;



        sprintf(buffer,"%c",pReqTransfer->TransferStatus);
        json_pReqTransfer["TransferStatus"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInputOrder->OrderPriceType);
        json_pInputOrder["OrderPriceType"] = buffer;




        sprintf(buffer,"%c",pInputOrder->Direction);
        json_pInputOrder["Direction"] = buffer;




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



        sprintf(buffer,"%c",pInputOrder->TimeCondition);
        json_pInputOrder["TimeCondition"] = buffer;




        gbk2utf8(
            pInputOrder->GTDDate,
            buffer,
            sizeof(pInputOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["GTDDate"] = buffer;




        sprintf(buffer,"%c",pInputOrder->VolumeCondition);
        json_pInputOrder["VolumeCondition"] = buffer;



        json_pInputOrder["MinVolume"] = pInputOrder->MinVolume;



        sprintf(buffer,"%c",pInputOrder->ContingentCondition);
        json_pInputOrder["ContingentCondition"] = buffer;



        json_pInputOrder["StopPrice"] = pInputOrder->StopPrice;



        sprintf(buffer,"%c",pInputOrder->ForceCloseReason);
        json_pInputOrder["ForceCloseReason"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pEWarrantOffset->Direction);
        json_pEWarrantOffset["Direction"] = buffer;




        sprintf(buffer,"%c",pEWarrantOffset->HedgeFlag);
        json_pEWarrantOffset["HedgeFlag"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pExchangeMarginRateAdjust->HedgeFlag);
        json_pExchangeMarginRateAdjust["HedgeFlag"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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



        sprintf(buffer,"%c",pReqTransfer->LastFragment);
        json_pReqTransfer["LastFragment"] = buffer;



        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;



        gbk2utf8(
            pReqTransfer->CustomerName,
            buffer,
            sizeof(pReqTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->IdCardType);
        json_pReqTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pReqTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pReqTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->CustType);
        json_pReqTransfer["CustType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->VerifyCertNoFlag);
        json_pReqTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->CurrencyID,
            buffer,
            sizeof(pReqTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CurrencyID"] = buffer;



        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;


        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;



        sprintf(buffer,"%c",pReqTransfer->FeePayFlag);
        json_pReqTransfer["FeePayFlag"] = buffer;



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




        sprintf(buffer,"%c",pReqTransfer->BankAccType);
        json_pReqTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pReqTransfer->DeviceID,
            buffer,
            sizeof(pReqTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->BankSecuAccType);
        json_pReqTransfer["BankSecuAccType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->BankPwdFlag);
        json_pReqTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->SecuPwdFlag);
        json_pReqTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->OperNo,
            buffer,
            sizeof(pReqTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["OperNo"] = buffer;



        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;


        json_pReqTransfer["TID"] = pReqTransfer->TID;



        sprintf(buffer,"%c",pReqTransfer->TransferStatus);
        json_pReqTransfer["TransferStatus"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInvestorPositionCombineDetail->HedgeFlag);
        json_pInvestorPositionCombineDetail["HedgeFlag"] = buffer;




        sprintf(buffer,"%c",pInvestorPositionCombineDetail->Direction);
        json_pInvestorPositionCombineDetail["Direction"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pAccountregister->IdCardType);
        json_pAccountregister["IdCardType"] = buffer;




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




        sprintf(buffer,"%c",pAccountregister->OpenOrDestroy);
        json_pAccountregister["OpenOrDestroy"] = buffer;




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



        sprintf(buffer,"%c",pAccountregister->CustType);
        json_pAccountregister["CustType"] = buffer;




        sprintf(buffer,"%c",pAccountregister->BankAccType);
        json_pAccountregister["BankAccType"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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



        sprintf(buffer,"%c",pTradingCode->ClientIDType);
        json_pTradingCode["ClientIDType"] = buffer;


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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pTransferSerial->BankAccType);
        json_pTransferSerial["BankAccType"] = buffer;




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




        sprintf(buffer,"%c",pTransferSerial->FutureAccType);
        json_pTransferSerial["FutureAccType"] = buffer;




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



        sprintf(buffer,"%c",pTransferSerial->IdCardType);
        json_pTransferSerial["IdCardType"] = buffer;




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



        sprintf(buffer,"%c",pTransferSerial->AvailabilityFlag);
        json_pTransferSerial["AvailabilityFlag"] = buffer;




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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInvestorPosition->PosiDirection);
        json_pInvestorPosition["PosiDirection"] = buffer;




        sprintf(buffer,"%c",pInvestorPosition->HedgeFlag);
        json_pInvestorPosition["HedgeFlag"] = buffer;




        sprintf(buffer,"%c",pInvestorPosition->PositionDate);
        json_pInvestorPosition["PositionDate"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInvestorPositionDetail->HedgeFlag);
        json_pInvestorPositionDetail["HedgeFlag"] = buffer;




        sprintf(buffer,"%c",pInvestorPositionDetail->Direction);
        json_pInvestorPositionDetail["Direction"] = buffer;




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



        sprintf(buffer,"%c",pInvestorPositionDetail->TradeType);
        json_pInvestorPositionDetail["TradeType"] = buffer;




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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pBrokerTradingParams->MarginPriceType);
        json_pBrokerTradingParams["MarginPriceType"] = buffer;




        sprintf(buffer,"%c",pBrokerTradingParams->Algorithm);
        json_pBrokerTradingParams["Algorithm"] = buffer;




        sprintf(buffer,"%c",pBrokerTradingParams->AvailIncludeCloseProfit);
        json_pBrokerTradingParams["AvailIncludeCloseProfit"] = buffer;




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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pExchangeMarginRate->HedgeFlag);
        json_pExchangeMarginRate["HedgeFlag"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pParkedOrder->OrderPriceType);
        json_pParkedOrder["OrderPriceType"] = buffer;




        sprintf(buffer,"%c",pParkedOrder->Direction);
        json_pParkedOrder["Direction"] = buffer;




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



        sprintf(buffer,"%c",pParkedOrder->TimeCondition);
        json_pParkedOrder["TimeCondition"] = buffer;




        gbk2utf8(
            pParkedOrder->GTDDate,
            buffer,
            sizeof(pParkedOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pParkedOrder["GTDDate"] = buffer;




        sprintf(buffer,"%c",pParkedOrder->VolumeCondition);
        json_pParkedOrder["VolumeCondition"] = buffer;



        json_pParkedOrder["MinVolume"] = pParkedOrder->MinVolume;



        sprintf(buffer,"%c",pParkedOrder->ContingentCondition);
        json_pParkedOrder["ContingentCondition"] = buffer;



        json_pParkedOrder["StopPrice"] = pParkedOrder->StopPrice;



        sprintf(buffer,"%c",pParkedOrder->ForceCloseReason);
        json_pParkedOrder["ForceCloseReason"] = buffer;



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




        sprintf(buffer,"%c",pParkedOrder->UserType);
        json_pParkedOrder["UserType"] = buffer;




        sprintf(buffer,"%c",pParkedOrder->Status);
        json_pParkedOrder["Status"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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



        sprintf(buffer,"%c",pReqQueryAccount->LastFragment);
        json_pReqQueryAccount["LastFragment"] = buffer;



        json_pReqQueryAccount["SessionID"] = pReqQueryAccount->SessionID;



        gbk2utf8(
            pReqQueryAccount->CustomerName,
            buffer,
            sizeof(pReqQueryAccount->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->IdCardType);
        json_pReqQueryAccount["IdCardType"] = buffer;




        gbk2utf8(
            pReqQueryAccount->IdentifiedCardNo,
            buffer,
            sizeof(pReqQueryAccount->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->CustType);
        json_pReqQueryAccount["CustType"] = buffer;




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




        sprintf(buffer,"%c",pReqQueryAccount->VerifyCertNoFlag);
        json_pReqQueryAccount["VerifyCertNoFlag"] = buffer;




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




        sprintf(buffer,"%c",pReqQueryAccount->BankAccType);
        json_pReqQueryAccount["BankAccType"] = buffer;




        gbk2utf8(
            pReqQueryAccount->DeviceID,
            buffer,
            sizeof(pReqQueryAccount->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->BankSecuAccType);
        json_pReqQueryAccount["BankSecuAccType"] = buffer;




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




        sprintf(buffer,"%c",pReqQueryAccount->BankPwdFlag);
        json_pReqQueryAccount["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->SecuPwdFlag);
        json_pReqQueryAccount["SecuPwdFlag"] = buffer;




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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pQueryMaxOrderVolume->Direction);
        json_pQueryMaxOrderVolume["Direction"] = buffer;




        sprintf(buffer,"%c",pQueryMaxOrderVolume->OffsetFlag);
        json_pQueryMaxOrderVolume["OffsetFlag"] = buffer;




        sprintf(buffer,"%c",pQueryMaxOrderVolume->HedgeFlag);
        json_pQueryMaxOrderVolume["HedgeFlag"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pTradingNotice->InvestorRange);
        json_pTradingNotice["InvestorRange"] = buffer;




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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pParkedOrderAction->ActionFlag);
        json_pParkedOrderAction["ActionFlag"] = buffer;



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




        sprintf(buffer,"%c",pParkedOrderAction->UserType);
        json_pParkedOrderAction["UserType"] = buffer;




        sprintf(buffer,"%c",pParkedOrderAction->Status);
        json_pParkedOrderAction["Status"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pParkedOrderAction->ActionFlag);
        json_pParkedOrderAction["ActionFlag"] = buffer;



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




        sprintf(buffer,"%c",pParkedOrderAction->UserType);
        json_pParkedOrderAction["UserType"] = buffer;




        sprintf(buffer,"%c",pParkedOrderAction->Status);
        json_pParkedOrderAction["Status"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pInstrumentCommissionRate->InvestorRange);
        json_pInstrumentCommissionRate["InvestorRange"] = buffer;




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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pOrder->OrderPriceType);
        json_pOrder["OrderPriceType"] = buffer;




        sprintf(buffer,"%c",pOrder->Direction);
        json_pOrder["Direction"] = buffer;




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



        sprintf(buffer,"%c",pOrder->TimeCondition);
        json_pOrder["TimeCondition"] = buffer;




        gbk2utf8(
            pOrder->GTDDate,
            buffer,
            sizeof(pOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["GTDDate"] = buffer;




        sprintf(buffer,"%c",pOrder->VolumeCondition);
        json_pOrder["VolumeCondition"] = buffer;



        json_pOrder["MinVolume"] = pOrder->MinVolume;



        sprintf(buffer,"%c",pOrder->ContingentCondition);
        json_pOrder["ContingentCondition"] = buffer;



        json_pOrder["StopPrice"] = pOrder->StopPrice;



        sprintf(buffer,"%c",pOrder->ForceCloseReason);
        json_pOrder["ForceCloseReason"] = buffer;



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



        sprintf(buffer,"%c",pOrder->OrderSubmitStatus);
        json_pOrder["OrderSubmitStatus"] = buffer;



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




        sprintf(buffer,"%c",pOrder->OrderSource);
        json_pOrder["OrderSource"] = buffer;




        sprintf(buffer,"%c",pOrder->OrderStatus);
        json_pOrder["OrderStatus"] = buffer;




        sprintf(buffer,"%c",pOrder->OrderType);
        json_pOrder["OrderType"] = buffer;



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
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
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




        sprintf(buffer,"%c",pTrade->Direction);
        json_pTrade["Direction"] = buffer;




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




        sprintf(buffer,"%c",pTrade->TradingRole);
        json_pTrade["TradingRole"] = buffer;




        gbk2utf8(
            pTrade->ExchangeInstID,
            buffer,
            sizeof(pTrade->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["ExchangeInstID"] = buffer;




        sprintf(buffer,"%c",pTrade->OffsetFlag);
        json_pTrade["OffsetFlag"] = buffer;




        sprintf(buffer,"%c",pTrade->HedgeFlag);
        json_pTrade["HedgeFlag"] = buffer;



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




        sprintf(buffer,"%c",pTrade->TradeType);
        json_pTrade["TradeType"] = buffer;




        sprintf(buffer,"%c",pTrade->PriceSource);
        json_pTrade["PriceSource"] = buffer;




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



        sprintf(buffer,"%c",pTrade->TradeSource);
        json_pTrade["TradeSource"] = buffer;


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
    int nRequestID = 0;
    std::cout << "OnRtnQueryBankBalanceByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnQueryBankBalanceByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pNotifyQueryAccount;
    if ( pNotifyQueryAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pNotifyQueryAccount->TradeCode,
            buffer,
            sizeof(pNotifyQueryAccount->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["TradeCode"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BankID,
            buffer,
            sizeof(pNotifyQueryAccount->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BankID"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BankBranchID,
            buffer,
            sizeof(pNotifyQueryAccount->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BankBranchID"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BrokerID,
            buffer,
            sizeof(pNotifyQueryAccount->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BrokerID"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BrokerBranchID,
            buffer,
            sizeof(pNotifyQueryAccount->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BrokerBranchID"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->TradeDate,
            buffer,
            sizeof(pNotifyQueryAccount->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["TradeDate"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->TradeTime,
            buffer,
            sizeof(pNotifyQueryAccount->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["TradeTime"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BankSerial,
            buffer,
            sizeof(pNotifyQueryAccount->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BankSerial"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->TradingDay,
            buffer,
            sizeof(pNotifyQueryAccount->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["TradingDay"] = buffer;



        json_pNotifyQueryAccount["PlateSerial"] = pNotifyQueryAccount->PlateSerial;




        sprintf(buffer,"%c",pNotifyQueryAccount->LastFragment);
        json_pNotifyQueryAccount["LastFragment"] = buffer;



        json_pNotifyQueryAccount["SessionID"] = pNotifyQueryAccount->SessionID;




        gbk2utf8(
            pNotifyQueryAccount->CustomerName,
            buffer,
            sizeof(pNotifyQueryAccount->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["CustomerName"] = buffer;




        sprintf(buffer,"%c",pNotifyQueryAccount->IdCardType);
        json_pNotifyQueryAccount["IdCardType"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->IdentifiedCardNo,
            buffer,
            sizeof(pNotifyQueryAccount->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pNotifyQueryAccount->CustType);
        json_pNotifyQueryAccount["CustType"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BankAccount,
            buffer,
            sizeof(pNotifyQueryAccount->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BankAccount"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BankPassWord,
            buffer,
            sizeof(pNotifyQueryAccount->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BankPassWord"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->AccountID,
            buffer,
            sizeof(pNotifyQueryAccount->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["AccountID"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->Password,
            buffer,
            sizeof(pNotifyQueryAccount->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["Password"] = buffer;



        json_pNotifyQueryAccount["FutureSerial"] = pNotifyQueryAccount->FutureSerial;



        json_pNotifyQueryAccount["InstallID"] = pNotifyQueryAccount->InstallID;




        gbk2utf8(
            pNotifyQueryAccount->UserID,
            buffer,
            sizeof(pNotifyQueryAccount->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["UserID"] = buffer;




        sprintf(buffer,"%c",pNotifyQueryAccount->VerifyCertNoFlag);
        json_pNotifyQueryAccount["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->CurrencyID,
            buffer,
            sizeof(pNotifyQueryAccount->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["CurrencyID"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->Digest,
            buffer,
            sizeof(pNotifyQueryAccount->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["Digest"] = buffer;




        sprintf(buffer,"%c",pNotifyQueryAccount->BankAccType);
        json_pNotifyQueryAccount["BankAccType"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->DeviceID,
            buffer,
            sizeof(pNotifyQueryAccount->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["DeviceID"] = buffer;




        sprintf(buffer,"%c",pNotifyQueryAccount->BankSecuAccType);
        json_pNotifyQueryAccount["BankSecuAccType"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BrokerIDByBank,
            buffer,
            sizeof(pNotifyQueryAccount->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->BankSecuAcc,
            buffer,
            sizeof(pNotifyQueryAccount->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pNotifyQueryAccount->BankPwdFlag);
        json_pNotifyQueryAccount["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pNotifyQueryAccount->SecuPwdFlag);
        json_pNotifyQueryAccount["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pNotifyQueryAccount->OperNo,
            buffer,
            sizeof(pNotifyQueryAccount->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["OperNo"] = buffer;



        json_pNotifyQueryAccount["RequestID"] = pNotifyQueryAccount->RequestID;

        nRequestID = pNotifyQueryAccount->RequestID;



        json_pNotifyQueryAccount["TID"] = pNotifyQueryAccount->TID;



        json_pNotifyQueryAccount["BankUseAmount"] = pNotifyQueryAccount->BankUseAmount;



        json_pNotifyQueryAccount["BankFetchAmount"] = pNotifyQueryAccount->BankFetchAmount;



        json_pNotifyQueryAccount["ErrorID"] = pNotifyQueryAccount->ErrorID;




        gbk2utf8(
            pNotifyQueryAccount->ErrorMsg,
            buffer,
            sizeof(pNotifyQueryAccount->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pNotifyQueryAccount["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pNotifyQueryAccount;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnQueryBankBalanceByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnQueryBankBalanceByFuture():执行结束..." << std::endl;
}

///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromBankToFutureByFuture(
    CThostFtdcRspRepealField * pRspRepeal
) {
    int nRequestID = 0;
    std::cout << "OnRtnRepealFromBankToFutureByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnRepealFromBankToFutureByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspRepeal;
    if ( pRspRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pRspRepeal["RepealTimeInterval"] = pRspRepeal->RepealTimeInterval;



        json_pRspRepeal["RepealedTimes"] = pRspRepeal->RepealedTimes;




        sprintf(buffer,"%c",pRspRepeal->BankRepealFlag);
        json_pRspRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BrokerRepealFlag);
        json_pRspRepeal["BrokerRepealFlag"] = buffer;



        json_pRspRepeal["PlateRepealSerial"] = pRspRepeal->PlateRepealSerial;




        gbk2utf8(
            pRspRepeal->BankRepealSerial,
            buffer,
            sizeof(pRspRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankRepealSerial"] = buffer;



        json_pRspRepeal["FutureRepealSerial"] = pRspRepeal->FutureRepealSerial;




        gbk2utf8(
            pRspRepeal->TradeCode,
            buffer,
            sizeof(pRspRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pRspRepeal->BankID,
            buffer,
            sizeof(pRspRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankID"] = buffer;




        gbk2utf8(
            pRspRepeal->BankBranchID,
            buffer,
            sizeof(pRspRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerID,
            buffer,
            sizeof(pRspRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerBranchID,
            buffer,
            sizeof(pRspRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeDate,
            buffer,
            sizeof(pRspRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeTime,
            buffer,
            sizeof(pRspRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSerial,
            buffer,
            sizeof(pRspRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pRspRepeal->TradingDay,
            buffer,
            sizeof(pRspRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradingDay"] = buffer;



        json_pRspRepeal["PlateSerial"] = pRspRepeal->PlateSerial;




        sprintf(buffer,"%c",pRspRepeal->LastFragment);
        json_pRspRepeal["LastFragment"] = buffer;



        json_pRspRepeal["SessionID"] = pRspRepeal->SessionID;




        gbk2utf8(
            pRspRepeal->CustomerName,
            buffer,
            sizeof(pRspRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->IdCardType);
        json_pRspRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pRspRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pRspRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->CustType);
        json_pRspRepeal["CustType"] = buffer;




        gbk2utf8(
            pRspRepeal->BankAccount,
            buffer,
            sizeof(pRspRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pRspRepeal->BankPassWord,
            buffer,
            sizeof(pRspRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pRspRepeal->AccountID,
            buffer,
            sizeof(pRspRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["AccountID"] = buffer;




        gbk2utf8(
            pRspRepeal->Password,
            buffer,
            sizeof(pRspRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Password"] = buffer;



        json_pRspRepeal["InstallID"] = pRspRepeal->InstallID;



        json_pRspRepeal["FutureSerial"] = pRspRepeal->FutureSerial;




        gbk2utf8(
            pRspRepeal->UserID,
            buffer,
            sizeof(pRspRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->VerifyCertNoFlag);
        json_pRspRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->CurrencyID,
            buffer,
            sizeof(pRspRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CurrencyID"] = buffer;



        json_pRspRepeal["TradeAmount"] = pRspRepeal->TradeAmount;



        json_pRspRepeal["FutureFetchAmount"] = pRspRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pRspRepeal->FeePayFlag);
        json_pRspRepeal["FeePayFlag"] = buffer;



        json_pRspRepeal["CustFee"] = pRspRepeal->CustFee;



        json_pRspRepeal["BrokerFee"] = pRspRepeal->BrokerFee;




        gbk2utf8(
            pRspRepeal->Message,
            buffer,
            sizeof(pRspRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Message"] = buffer;




        gbk2utf8(
            pRspRepeal->Digest,
            buffer,
            sizeof(pRspRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankAccType);
        json_pRspRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->DeviceID,
            buffer,
            sizeof(pRspRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankSecuAccType);
        json_pRspRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerIDByBank,
            buffer,
            sizeof(pRspRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSecuAcc,
            buffer,
            sizeof(pRspRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankPwdFlag);
        json_pRspRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->SecuPwdFlag);
        json_pRspRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->OperNo,
            buffer,
            sizeof(pRspRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["OperNo"] = buffer;



        json_pRspRepeal["RequestID"] = pRspRepeal->RequestID;

        nRequestID = pRspRepeal->RequestID;



        json_pRspRepeal["TID"] = pRspRepeal->TID;




        sprintf(buffer,"%c",pRspRepeal->TransferStatus);
        json_pRspRepeal["TransferStatus"] = buffer;



        json_pRspRepeal["ErrorID"] = pRspRepeal->ErrorID;




        gbk2utf8(
            pRspRepeal->ErrorMsg,
            buffer,
            sizeof(pRspRepeal->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnRepealFromBankToFutureByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnRepealFromBankToFutureByFuture():执行结束..." << std::endl;
}

///银行发起银行资金转期货通知
void CTraderHandler::OnRtnFromBankToFutureByBank(
    CThostFtdcRspTransferField * pRspTransfer
) {
    int nRequestID = 0;
    std::cout << "OnRtnFromBankToFutureByBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnFromBankToFutureByBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspTransfer;
    if ( pRspTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pRspTransfer->TradeCode,
            buffer,
            sizeof(pRspTransfer->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeCode"] = buffer;




        gbk2utf8(
            pRspTransfer->BankID,
            buffer,
            sizeof(pRspTransfer->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankID"] = buffer;




        gbk2utf8(
            pRspTransfer->BankBranchID,
            buffer,
            sizeof(pRspTransfer->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerID,
            buffer,
            sizeof(pRspTransfer->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerBranchID,
            buffer,
            sizeof(pRspTransfer->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeDate,
            buffer,
            sizeof(pRspTransfer->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeDate"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeTime,
            buffer,
            sizeof(pRspTransfer->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeTime"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSerial,
            buffer,
            sizeof(pRspTransfer->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSerial"] = buffer;




        gbk2utf8(
            pRspTransfer->TradingDay,
            buffer,
            sizeof(pRspTransfer->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradingDay"] = buffer;



        json_pRspTransfer["PlateSerial"] = pRspTransfer->PlateSerial;




        sprintf(buffer,"%c",pRspTransfer->LastFragment);
        json_pRspTransfer["LastFragment"] = buffer;



        json_pRspTransfer["SessionID"] = pRspTransfer->SessionID;




        gbk2utf8(
            pRspTransfer->CustomerName,
            buffer,
            sizeof(pRspTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->IdCardType);
        json_pRspTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pRspTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pRspTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->CustType);
        json_pRspTransfer["CustType"] = buffer;




        gbk2utf8(
            pRspTransfer->BankAccount,
            buffer,
            sizeof(pRspTransfer->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankAccount"] = buffer;




        gbk2utf8(
            pRspTransfer->BankPassWord,
            buffer,
            sizeof(pRspTransfer->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankPassWord"] = buffer;




        gbk2utf8(
            pRspTransfer->AccountID,
            buffer,
            sizeof(pRspTransfer->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["AccountID"] = buffer;




        gbk2utf8(
            pRspTransfer->Password,
            buffer,
            sizeof(pRspTransfer->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Password"] = buffer;



        json_pRspTransfer["InstallID"] = pRspTransfer->InstallID;



        json_pRspTransfer["FutureSerial"] = pRspTransfer->FutureSerial;




        gbk2utf8(
            pRspTransfer->UserID,
            buffer,
            sizeof(pRspTransfer->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["UserID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->VerifyCertNoFlag);
        json_pRspTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->CurrencyID,
            buffer,
            sizeof(pRspTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CurrencyID"] = buffer;



        json_pRspTransfer["TradeAmount"] = pRspTransfer->TradeAmount;



        json_pRspTransfer["FutureFetchAmount"] = pRspTransfer->FutureFetchAmount;




        sprintf(buffer,"%c",pRspTransfer->FeePayFlag);
        json_pRspTransfer["FeePayFlag"] = buffer;



        json_pRspTransfer["CustFee"] = pRspTransfer->CustFee;



        json_pRspTransfer["BrokerFee"] = pRspTransfer->BrokerFee;




        gbk2utf8(
            pRspTransfer->Message,
            buffer,
            sizeof(pRspTransfer->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Message"] = buffer;




        gbk2utf8(
            pRspTransfer->Digest,
            buffer,
            sizeof(pRspTransfer->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Digest"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankAccType);
        json_pRspTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->DeviceID,
            buffer,
            sizeof(pRspTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankSecuAccType);
        json_pRspTransfer["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerIDByBank,
            buffer,
            sizeof(pRspTransfer->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSecuAcc,
            buffer,
            sizeof(pRspTransfer->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankPwdFlag);
        json_pRspTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->SecuPwdFlag);
        json_pRspTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->OperNo,
            buffer,
            sizeof(pRspTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["OperNo"] = buffer;



        json_pRspTransfer["RequestID"] = pRspTransfer->RequestID;

        nRequestID = pRspTransfer->RequestID;



        json_pRspTransfer["TID"] = pRspTransfer->TID;




        sprintf(buffer,"%c",pRspTransfer->TransferStatus);
        json_pRspTransfer["TransferStatus"] = buffer;



        json_pRspTransfer["ErrorID"] = pRspTransfer->ErrorID;




        gbk2utf8(
            pRspTransfer->ErrorMsg,
            buffer,
            sizeof(pRspTransfer->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspTransfer;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnFromBankToFutureByBank";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnFromBankToFutureByBank():执行结束..." << std::endl;
}

///保证金监控中心用户令牌
void CTraderHandler::OnRtnCFMMCTradingAccountToken(
    CThostFtdcCFMMCTradingAccountTokenField * pCFMMCTradingAccountToken
) {
    int nRequestID = 0;
    std::cout << "OnRtnCFMMCTradingAccountToken():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnCFMMCTradingAccountToken";

    /// 返回数据结构体转化json格式
    Json::Value json_pCFMMCTradingAccountToken;
    if ( pCFMMCTradingAccountToken != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pCFMMCTradingAccountToken->BrokerID,
            buffer,
            sizeof(pCFMMCTradingAccountToken->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountToken["BrokerID"] = buffer;




        gbk2utf8(
            pCFMMCTradingAccountToken->ParticipantID,
            buffer,
            sizeof(pCFMMCTradingAccountToken->ParticipantID) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountToken["ParticipantID"] = buffer;




        gbk2utf8(
            pCFMMCTradingAccountToken->AccountID,
            buffer,
            sizeof(pCFMMCTradingAccountToken->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountToken["AccountID"] = buffer;



        json_pCFMMCTradingAccountToken["KeyID"] = pCFMMCTradingAccountToken->KeyID;




        gbk2utf8(
            pCFMMCTradingAccountToken->Token,
            buffer,
            sizeof(pCFMMCTradingAccountToken->Token) * 3 // 字符串转化变长的风险保障
        );
        json_pCFMMCTradingAccountToken["Token"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pCFMMCTradingAccountToken;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnCFMMCTradingAccountToken";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnCFMMCTradingAccountToken():执行结束..." << std::endl;
}

///合约交易状态通知
void CTraderHandler::OnRtnInstrumentStatus(
    CThostFtdcInstrumentStatusField * pInstrumentStatus
) {
    int nRequestID = 0;
    std::cout << "OnRtnInstrumentStatus():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnInstrumentStatus";

    /// 返回数据结构体转化json格式
    Json::Value json_pInstrumentStatus;
    if ( pInstrumentStatus != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pInstrumentStatus->ExchangeID,
            buffer,
            sizeof(pInstrumentStatus->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentStatus["ExchangeID"] = buffer;




        gbk2utf8(
            pInstrumentStatus->ExchangeInstID,
            buffer,
            sizeof(pInstrumentStatus->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentStatus["ExchangeInstID"] = buffer;




        gbk2utf8(
            pInstrumentStatus->SettlementGroupID,
            buffer,
            sizeof(pInstrumentStatus->SettlementGroupID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentStatus["SettlementGroupID"] = buffer;




        gbk2utf8(
            pInstrumentStatus->InstrumentID,
            buffer,
            sizeof(pInstrumentStatus->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentStatus["InstrumentID"] = buffer;




        sprintf(buffer,"%c",pInstrumentStatus->InstrumentStatus);
        json_pInstrumentStatus["InstrumentStatus"] = buffer;



        json_pInstrumentStatus["TradingSegmentSN"] = pInstrumentStatus->TradingSegmentSN;




        gbk2utf8(
            pInstrumentStatus->EnterTime,
            buffer,
            sizeof(pInstrumentStatus->EnterTime) * 3 // 字符串转化变长的风险保障
        );
        json_pInstrumentStatus["EnterTime"] = buffer;




        sprintf(buffer,"%c",pInstrumentStatus->EnterReason);
        json_pInstrumentStatus["EnterReason"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInstrumentStatus;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnInstrumentStatus";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnInstrumentStatus():执行结束..." << std::endl;
}

///交易通知
void CTraderHandler::OnRtnTradingNotice(
    CThostFtdcTradingNoticeInfoField * pTradingNoticeInfo
) {
    int nRequestID = 0;
    std::cout << "OnRtnTradingNotice():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnTradingNotice";

    /// 返回数据结构体转化json格式
    Json::Value json_pTradingNoticeInfo;
    if ( pTradingNoticeInfo != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pTradingNoticeInfo->BrokerID,
            buffer,
            sizeof(pTradingNoticeInfo->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNoticeInfo["BrokerID"] = buffer;




        gbk2utf8(
            pTradingNoticeInfo->InvestorID,
            buffer,
            sizeof(pTradingNoticeInfo->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNoticeInfo["InvestorID"] = buffer;




        gbk2utf8(
            pTradingNoticeInfo->SendTime,
            buffer,
            sizeof(pTradingNoticeInfo->SendTime) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNoticeInfo["SendTime"] = buffer;




        gbk2utf8(
            pTradingNoticeInfo->FieldContent,
            buffer,
            sizeof(pTradingNoticeInfo->FieldContent) * 3 // 字符串转化变长的风险保障
        );
        json_pTradingNoticeInfo["FieldContent"] = buffer;



        json_pTradingNoticeInfo["SequenceSeries"] = pTradingNoticeInfo->SequenceSeries;



        json_pTradingNoticeInfo["SequenceNo"] = pTradingNoticeInfo->SequenceNo;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTradingNoticeInfo;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnTradingNotice";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnTradingNotice():执行结束..." << std::endl;
}

///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromFutureToBankByFutureManual(
    CThostFtdcRspRepealField * pRspRepeal
) {
    int nRequestID = 0;
    std::cout << "OnRtnRepealFromFutureToBankByFutureManual():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnRepealFromFutureToBankByFutureManual";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspRepeal;
    if ( pRspRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pRspRepeal["RepealTimeInterval"] = pRspRepeal->RepealTimeInterval;



        json_pRspRepeal["RepealedTimes"] = pRspRepeal->RepealedTimes;




        sprintf(buffer,"%c",pRspRepeal->BankRepealFlag);
        json_pRspRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BrokerRepealFlag);
        json_pRspRepeal["BrokerRepealFlag"] = buffer;



        json_pRspRepeal["PlateRepealSerial"] = pRspRepeal->PlateRepealSerial;




        gbk2utf8(
            pRspRepeal->BankRepealSerial,
            buffer,
            sizeof(pRspRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankRepealSerial"] = buffer;



        json_pRspRepeal["FutureRepealSerial"] = pRspRepeal->FutureRepealSerial;




        gbk2utf8(
            pRspRepeal->TradeCode,
            buffer,
            sizeof(pRspRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pRspRepeal->BankID,
            buffer,
            sizeof(pRspRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankID"] = buffer;




        gbk2utf8(
            pRspRepeal->BankBranchID,
            buffer,
            sizeof(pRspRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerID,
            buffer,
            sizeof(pRspRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerBranchID,
            buffer,
            sizeof(pRspRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeDate,
            buffer,
            sizeof(pRspRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeTime,
            buffer,
            sizeof(pRspRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSerial,
            buffer,
            sizeof(pRspRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pRspRepeal->TradingDay,
            buffer,
            sizeof(pRspRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradingDay"] = buffer;



        json_pRspRepeal["PlateSerial"] = pRspRepeal->PlateSerial;




        sprintf(buffer,"%c",pRspRepeal->LastFragment);
        json_pRspRepeal["LastFragment"] = buffer;



        json_pRspRepeal["SessionID"] = pRspRepeal->SessionID;




        gbk2utf8(
            pRspRepeal->CustomerName,
            buffer,
            sizeof(pRspRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->IdCardType);
        json_pRspRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pRspRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pRspRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->CustType);
        json_pRspRepeal["CustType"] = buffer;




        gbk2utf8(
            pRspRepeal->BankAccount,
            buffer,
            sizeof(pRspRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pRspRepeal->BankPassWord,
            buffer,
            sizeof(pRspRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pRspRepeal->AccountID,
            buffer,
            sizeof(pRspRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["AccountID"] = buffer;




        gbk2utf8(
            pRspRepeal->Password,
            buffer,
            sizeof(pRspRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Password"] = buffer;



        json_pRspRepeal["InstallID"] = pRspRepeal->InstallID;



        json_pRspRepeal["FutureSerial"] = pRspRepeal->FutureSerial;




        gbk2utf8(
            pRspRepeal->UserID,
            buffer,
            sizeof(pRspRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->VerifyCertNoFlag);
        json_pRspRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->CurrencyID,
            buffer,
            sizeof(pRspRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CurrencyID"] = buffer;



        json_pRspRepeal["TradeAmount"] = pRspRepeal->TradeAmount;



        json_pRspRepeal["FutureFetchAmount"] = pRspRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pRspRepeal->FeePayFlag);
        json_pRspRepeal["FeePayFlag"] = buffer;



        json_pRspRepeal["CustFee"] = pRspRepeal->CustFee;



        json_pRspRepeal["BrokerFee"] = pRspRepeal->BrokerFee;




        gbk2utf8(
            pRspRepeal->Message,
            buffer,
            sizeof(pRspRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Message"] = buffer;




        gbk2utf8(
            pRspRepeal->Digest,
            buffer,
            sizeof(pRspRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankAccType);
        json_pRspRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->DeviceID,
            buffer,
            sizeof(pRspRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankSecuAccType);
        json_pRspRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerIDByBank,
            buffer,
            sizeof(pRspRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSecuAcc,
            buffer,
            sizeof(pRspRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankPwdFlag);
        json_pRspRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->SecuPwdFlag);
        json_pRspRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->OperNo,
            buffer,
            sizeof(pRspRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["OperNo"] = buffer;



        json_pRspRepeal["RequestID"] = pRspRepeal->RequestID;

        nRequestID = pRspRepeal->RequestID;



        json_pRspRepeal["TID"] = pRspRepeal->TID;




        sprintf(buffer,"%c",pRspRepeal->TransferStatus);
        json_pRspRepeal["TransferStatus"] = buffer;



        json_pRspRepeal["ErrorID"] = pRspRepeal->ErrorID;




        gbk2utf8(
            pRspRepeal->ErrorMsg,
            buffer,
            sizeof(pRspRepeal->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnRepealFromFutureToBankByFutureManual";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnRepealFromFutureToBankByFutureManual():执行结束..." << std::endl;
}

///期货发起银行资金转期货通知
void CTraderHandler::OnRtnFromBankToFutureByFuture(
    CThostFtdcRspTransferField * pRspTransfer
) {
    int nRequestID = 0;
    std::cout << "OnRtnFromBankToFutureByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnFromBankToFutureByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspTransfer;
    if ( pRspTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pRspTransfer->TradeCode,
            buffer,
            sizeof(pRspTransfer->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeCode"] = buffer;




        gbk2utf8(
            pRspTransfer->BankID,
            buffer,
            sizeof(pRspTransfer->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankID"] = buffer;




        gbk2utf8(
            pRspTransfer->BankBranchID,
            buffer,
            sizeof(pRspTransfer->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerID,
            buffer,
            sizeof(pRspTransfer->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerBranchID,
            buffer,
            sizeof(pRspTransfer->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeDate,
            buffer,
            sizeof(pRspTransfer->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeDate"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeTime,
            buffer,
            sizeof(pRspTransfer->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeTime"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSerial,
            buffer,
            sizeof(pRspTransfer->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSerial"] = buffer;




        gbk2utf8(
            pRspTransfer->TradingDay,
            buffer,
            sizeof(pRspTransfer->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradingDay"] = buffer;



        json_pRspTransfer["PlateSerial"] = pRspTransfer->PlateSerial;




        sprintf(buffer,"%c",pRspTransfer->LastFragment);
        json_pRspTransfer["LastFragment"] = buffer;



        json_pRspTransfer["SessionID"] = pRspTransfer->SessionID;




        gbk2utf8(
            pRspTransfer->CustomerName,
            buffer,
            sizeof(pRspTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->IdCardType);
        json_pRspTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pRspTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pRspTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->CustType);
        json_pRspTransfer["CustType"] = buffer;




        gbk2utf8(
            pRspTransfer->BankAccount,
            buffer,
            sizeof(pRspTransfer->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankAccount"] = buffer;




        gbk2utf8(
            pRspTransfer->BankPassWord,
            buffer,
            sizeof(pRspTransfer->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankPassWord"] = buffer;




        gbk2utf8(
            pRspTransfer->AccountID,
            buffer,
            sizeof(pRspTransfer->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["AccountID"] = buffer;




        gbk2utf8(
            pRspTransfer->Password,
            buffer,
            sizeof(pRspTransfer->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Password"] = buffer;



        json_pRspTransfer["InstallID"] = pRspTransfer->InstallID;



        json_pRspTransfer["FutureSerial"] = pRspTransfer->FutureSerial;




        gbk2utf8(
            pRspTransfer->UserID,
            buffer,
            sizeof(pRspTransfer->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["UserID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->VerifyCertNoFlag);
        json_pRspTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->CurrencyID,
            buffer,
            sizeof(pRspTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CurrencyID"] = buffer;



        json_pRspTransfer["TradeAmount"] = pRspTransfer->TradeAmount;



        json_pRspTransfer["FutureFetchAmount"] = pRspTransfer->FutureFetchAmount;




        sprintf(buffer,"%c",pRspTransfer->FeePayFlag);
        json_pRspTransfer["FeePayFlag"] = buffer;



        json_pRspTransfer["CustFee"] = pRspTransfer->CustFee;



        json_pRspTransfer["BrokerFee"] = pRspTransfer->BrokerFee;




        gbk2utf8(
            pRspTransfer->Message,
            buffer,
            sizeof(pRspTransfer->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Message"] = buffer;




        gbk2utf8(
            pRspTransfer->Digest,
            buffer,
            sizeof(pRspTransfer->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Digest"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankAccType);
        json_pRspTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->DeviceID,
            buffer,
            sizeof(pRspTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankSecuAccType);
        json_pRspTransfer["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerIDByBank,
            buffer,
            sizeof(pRspTransfer->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSecuAcc,
            buffer,
            sizeof(pRspTransfer->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankPwdFlag);
        json_pRspTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->SecuPwdFlag);
        json_pRspTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->OperNo,
            buffer,
            sizeof(pRspTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["OperNo"] = buffer;



        json_pRspTransfer["RequestID"] = pRspTransfer->RequestID;

        nRequestID = pRspTransfer->RequestID;



        json_pRspTransfer["TID"] = pRspTransfer->TID;




        sprintf(buffer,"%c",pRspTransfer->TransferStatus);
        json_pRspTransfer["TransferStatus"] = buffer;



        json_pRspTransfer["ErrorID"] = pRspTransfer->ErrorID;




        gbk2utf8(
            pRspTransfer->ErrorMsg,
            buffer,
            sizeof(pRspTransfer->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspTransfer;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnFromBankToFutureByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnFromBankToFutureByFuture():执行结束..." << std::endl;
}

///银行发起期货资金转银行通知
void CTraderHandler::OnRtnFromFutureToBankByBank(
    CThostFtdcRspTransferField * pRspTransfer
) {
    int nRequestID = 0;
    std::cout << "OnRtnFromFutureToBankByBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnFromFutureToBankByBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspTransfer;
    if ( pRspTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pRspTransfer->TradeCode,
            buffer,
            sizeof(pRspTransfer->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeCode"] = buffer;




        gbk2utf8(
            pRspTransfer->BankID,
            buffer,
            sizeof(pRspTransfer->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankID"] = buffer;




        gbk2utf8(
            pRspTransfer->BankBranchID,
            buffer,
            sizeof(pRspTransfer->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerID,
            buffer,
            sizeof(pRspTransfer->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerBranchID,
            buffer,
            sizeof(pRspTransfer->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeDate,
            buffer,
            sizeof(pRspTransfer->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeDate"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeTime,
            buffer,
            sizeof(pRspTransfer->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeTime"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSerial,
            buffer,
            sizeof(pRspTransfer->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSerial"] = buffer;




        gbk2utf8(
            pRspTransfer->TradingDay,
            buffer,
            sizeof(pRspTransfer->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradingDay"] = buffer;



        json_pRspTransfer["PlateSerial"] = pRspTransfer->PlateSerial;




        sprintf(buffer,"%c",pRspTransfer->LastFragment);
        json_pRspTransfer["LastFragment"] = buffer;



        json_pRspTransfer["SessionID"] = pRspTransfer->SessionID;




        gbk2utf8(
            pRspTransfer->CustomerName,
            buffer,
            sizeof(pRspTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->IdCardType);
        json_pRspTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pRspTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pRspTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->CustType);
        json_pRspTransfer["CustType"] = buffer;




        gbk2utf8(
            pRspTransfer->BankAccount,
            buffer,
            sizeof(pRspTransfer->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankAccount"] = buffer;




        gbk2utf8(
            pRspTransfer->BankPassWord,
            buffer,
            sizeof(pRspTransfer->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankPassWord"] = buffer;




        gbk2utf8(
            pRspTransfer->AccountID,
            buffer,
            sizeof(pRspTransfer->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["AccountID"] = buffer;




        gbk2utf8(
            pRspTransfer->Password,
            buffer,
            sizeof(pRspTransfer->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Password"] = buffer;



        json_pRspTransfer["InstallID"] = pRspTransfer->InstallID;



        json_pRspTransfer["FutureSerial"] = pRspTransfer->FutureSerial;




        gbk2utf8(
            pRspTransfer->UserID,
            buffer,
            sizeof(pRspTransfer->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["UserID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->VerifyCertNoFlag);
        json_pRspTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->CurrencyID,
            buffer,
            sizeof(pRspTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CurrencyID"] = buffer;



        json_pRspTransfer["TradeAmount"] = pRspTransfer->TradeAmount;



        json_pRspTransfer["FutureFetchAmount"] = pRspTransfer->FutureFetchAmount;




        sprintf(buffer,"%c",pRspTransfer->FeePayFlag);
        json_pRspTransfer["FeePayFlag"] = buffer;



        json_pRspTransfer["CustFee"] = pRspTransfer->CustFee;



        json_pRspTransfer["BrokerFee"] = pRspTransfer->BrokerFee;




        gbk2utf8(
            pRspTransfer->Message,
            buffer,
            sizeof(pRspTransfer->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Message"] = buffer;




        gbk2utf8(
            pRspTransfer->Digest,
            buffer,
            sizeof(pRspTransfer->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Digest"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankAccType);
        json_pRspTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->DeviceID,
            buffer,
            sizeof(pRspTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankSecuAccType);
        json_pRspTransfer["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerIDByBank,
            buffer,
            sizeof(pRspTransfer->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSecuAcc,
            buffer,
            sizeof(pRspTransfer->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankPwdFlag);
        json_pRspTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->SecuPwdFlag);
        json_pRspTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->OperNo,
            buffer,
            sizeof(pRspTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["OperNo"] = buffer;



        json_pRspTransfer["RequestID"] = pRspTransfer->RequestID;

        nRequestID = pRspTransfer->RequestID;



        json_pRspTransfer["TID"] = pRspTransfer->TID;




        sprintf(buffer,"%c",pRspTransfer->TransferStatus);
        json_pRspTransfer["TransferStatus"] = buffer;



        json_pRspTransfer["ErrorID"] = pRspTransfer->ErrorID;




        gbk2utf8(
            pRspTransfer->ErrorMsg,
            buffer,
            sizeof(pRspTransfer->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspTransfer;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnFromFutureToBankByBank";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnFromFutureToBankByBank():执行结束..." << std::endl;
}

///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromBankToFutureByFutureManual(
    CThostFtdcRspRepealField * pRspRepeal
) {
    int nRequestID = 0;
    std::cout << "OnRtnRepealFromBankToFutureByFutureManual():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnRepealFromBankToFutureByFutureManual";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspRepeal;
    if ( pRspRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pRspRepeal["RepealTimeInterval"] = pRspRepeal->RepealTimeInterval;



        json_pRspRepeal["RepealedTimes"] = pRspRepeal->RepealedTimes;




        sprintf(buffer,"%c",pRspRepeal->BankRepealFlag);
        json_pRspRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BrokerRepealFlag);
        json_pRspRepeal["BrokerRepealFlag"] = buffer;



        json_pRspRepeal["PlateRepealSerial"] = pRspRepeal->PlateRepealSerial;




        gbk2utf8(
            pRspRepeal->BankRepealSerial,
            buffer,
            sizeof(pRspRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankRepealSerial"] = buffer;



        json_pRspRepeal["FutureRepealSerial"] = pRspRepeal->FutureRepealSerial;




        gbk2utf8(
            pRspRepeal->TradeCode,
            buffer,
            sizeof(pRspRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pRspRepeal->BankID,
            buffer,
            sizeof(pRspRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankID"] = buffer;




        gbk2utf8(
            pRspRepeal->BankBranchID,
            buffer,
            sizeof(pRspRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerID,
            buffer,
            sizeof(pRspRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerBranchID,
            buffer,
            sizeof(pRspRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeDate,
            buffer,
            sizeof(pRspRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeTime,
            buffer,
            sizeof(pRspRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSerial,
            buffer,
            sizeof(pRspRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pRspRepeal->TradingDay,
            buffer,
            sizeof(pRspRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradingDay"] = buffer;



        json_pRspRepeal["PlateSerial"] = pRspRepeal->PlateSerial;




        sprintf(buffer,"%c",pRspRepeal->LastFragment);
        json_pRspRepeal["LastFragment"] = buffer;



        json_pRspRepeal["SessionID"] = pRspRepeal->SessionID;




        gbk2utf8(
            pRspRepeal->CustomerName,
            buffer,
            sizeof(pRspRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->IdCardType);
        json_pRspRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pRspRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pRspRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->CustType);
        json_pRspRepeal["CustType"] = buffer;




        gbk2utf8(
            pRspRepeal->BankAccount,
            buffer,
            sizeof(pRspRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pRspRepeal->BankPassWord,
            buffer,
            sizeof(pRspRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pRspRepeal->AccountID,
            buffer,
            sizeof(pRspRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["AccountID"] = buffer;




        gbk2utf8(
            pRspRepeal->Password,
            buffer,
            sizeof(pRspRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Password"] = buffer;



        json_pRspRepeal["InstallID"] = pRspRepeal->InstallID;



        json_pRspRepeal["FutureSerial"] = pRspRepeal->FutureSerial;




        gbk2utf8(
            pRspRepeal->UserID,
            buffer,
            sizeof(pRspRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->VerifyCertNoFlag);
        json_pRspRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->CurrencyID,
            buffer,
            sizeof(pRspRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CurrencyID"] = buffer;



        json_pRspRepeal["TradeAmount"] = pRspRepeal->TradeAmount;



        json_pRspRepeal["FutureFetchAmount"] = pRspRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pRspRepeal->FeePayFlag);
        json_pRspRepeal["FeePayFlag"] = buffer;



        json_pRspRepeal["CustFee"] = pRspRepeal->CustFee;



        json_pRspRepeal["BrokerFee"] = pRspRepeal->BrokerFee;




        gbk2utf8(
            pRspRepeal->Message,
            buffer,
            sizeof(pRspRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Message"] = buffer;




        gbk2utf8(
            pRspRepeal->Digest,
            buffer,
            sizeof(pRspRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankAccType);
        json_pRspRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->DeviceID,
            buffer,
            sizeof(pRspRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankSecuAccType);
        json_pRspRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerIDByBank,
            buffer,
            sizeof(pRspRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSecuAcc,
            buffer,
            sizeof(pRspRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankPwdFlag);
        json_pRspRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->SecuPwdFlag);
        json_pRspRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->OperNo,
            buffer,
            sizeof(pRspRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["OperNo"] = buffer;



        json_pRspRepeal["RequestID"] = pRspRepeal->RequestID;

        nRequestID = pRspRepeal->RequestID;



        json_pRspRepeal["TID"] = pRspRepeal->TID;




        sprintf(buffer,"%c",pRspRepeal->TransferStatus);
        json_pRspRepeal["TransferStatus"] = buffer;



        json_pRspRepeal["ErrorID"] = pRspRepeal->ErrorID;




        gbk2utf8(
            pRspRepeal->ErrorMsg,
            buffer,
            sizeof(pRspRepeal->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnRepealFromBankToFutureByFutureManual";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnRepealFromBankToFutureByFutureManual():执行结束..." << std::endl;
}

///期货发起期货资金转银行通知
void CTraderHandler::OnRtnFromFutureToBankByFuture(
    CThostFtdcRspTransferField * pRspTransfer
) {
    int nRequestID = 0;
    std::cout << "OnRtnFromFutureToBankByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnFromFutureToBankByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspTransfer;
    if ( pRspTransfer != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pRspTransfer->TradeCode,
            buffer,
            sizeof(pRspTransfer->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeCode"] = buffer;




        gbk2utf8(
            pRspTransfer->BankID,
            buffer,
            sizeof(pRspTransfer->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankID"] = buffer;




        gbk2utf8(
            pRspTransfer->BankBranchID,
            buffer,
            sizeof(pRspTransfer->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerID,
            buffer,
            sizeof(pRspTransfer->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerID"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerBranchID,
            buffer,
            sizeof(pRspTransfer->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeDate,
            buffer,
            sizeof(pRspTransfer->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeDate"] = buffer;




        gbk2utf8(
            pRspTransfer->TradeTime,
            buffer,
            sizeof(pRspTransfer->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradeTime"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSerial,
            buffer,
            sizeof(pRspTransfer->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSerial"] = buffer;




        gbk2utf8(
            pRspTransfer->TradingDay,
            buffer,
            sizeof(pRspTransfer->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["TradingDay"] = buffer;



        json_pRspTransfer["PlateSerial"] = pRspTransfer->PlateSerial;




        sprintf(buffer,"%c",pRspTransfer->LastFragment);
        json_pRspTransfer["LastFragment"] = buffer;



        json_pRspTransfer["SessionID"] = pRspTransfer->SessionID;




        gbk2utf8(
            pRspTransfer->CustomerName,
            buffer,
            sizeof(pRspTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->IdCardType);
        json_pRspTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pRspTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pRspTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->CustType);
        json_pRspTransfer["CustType"] = buffer;




        gbk2utf8(
            pRspTransfer->BankAccount,
            buffer,
            sizeof(pRspTransfer->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankAccount"] = buffer;




        gbk2utf8(
            pRspTransfer->BankPassWord,
            buffer,
            sizeof(pRspTransfer->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankPassWord"] = buffer;




        gbk2utf8(
            pRspTransfer->AccountID,
            buffer,
            sizeof(pRspTransfer->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["AccountID"] = buffer;




        gbk2utf8(
            pRspTransfer->Password,
            buffer,
            sizeof(pRspTransfer->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Password"] = buffer;



        json_pRspTransfer["InstallID"] = pRspTransfer->InstallID;



        json_pRspTransfer["FutureSerial"] = pRspTransfer->FutureSerial;




        gbk2utf8(
            pRspTransfer->UserID,
            buffer,
            sizeof(pRspTransfer->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["UserID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->VerifyCertNoFlag);
        json_pRspTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->CurrencyID,
            buffer,
            sizeof(pRspTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["CurrencyID"] = buffer;



        json_pRspTransfer["TradeAmount"] = pRspTransfer->TradeAmount;



        json_pRspTransfer["FutureFetchAmount"] = pRspTransfer->FutureFetchAmount;




        sprintf(buffer,"%c",pRspTransfer->FeePayFlag);
        json_pRspTransfer["FeePayFlag"] = buffer;



        json_pRspTransfer["CustFee"] = pRspTransfer->CustFee;



        json_pRspTransfer["BrokerFee"] = pRspTransfer->BrokerFee;




        gbk2utf8(
            pRspTransfer->Message,
            buffer,
            sizeof(pRspTransfer->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Message"] = buffer;




        gbk2utf8(
            pRspTransfer->Digest,
            buffer,
            sizeof(pRspTransfer->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["Digest"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankAccType);
        json_pRspTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->DeviceID,
            buffer,
            sizeof(pRspTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankSecuAccType);
        json_pRspTransfer["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspTransfer->BrokerIDByBank,
            buffer,
            sizeof(pRspTransfer->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspTransfer->BankSecuAcc,
            buffer,
            sizeof(pRspTransfer->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->BankPwdFlag);
        json_pRspTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspTransfer->SecuPwdFlag);
        json_pRspTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspTransfer->OperNo,
            buffer,
            sizeof(pRspTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["OperNo"] = buffer;



        json_pRspTransfer["RequestID"] = pRspTransfer->RequestID;

        nRequestID = pRspTransfer->RequestID;



        json_pRspTransfer["TID"] = pRspTransfer->TID;




        sprintf(buffer,"%c",pRspTransfer->TransferStatus);
        json_pRspTransfer["TransferStatus"] = buffer;



        json_pRspTransfer["ErrorID"] = pRspTransfer->ErrorID;




        gbk2utf8(
            pRspTransfer->ErrorMsg,
            buffer,
            sizeof(pRspTransfer->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspTransfer["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspTransfer;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnFromFutureToBankByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnFromFutureToBankByFuture():执行结束..." << std::endl;
}

///银行发起变更银行账号通知
void CTraderHandler::OnRtnChangeAccountByBank(
    CThostFtdcChangeAccountField * pChangeAccount
) {
    int nRequestID = 0;
    std::cout << "OnRtnChangeAccountByBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnChangeAccountByBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pChangeAccount;
    if ( pChangeAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pChangeAccount->TradeCode,
            buffer,
            sizeof(pChangeAccount->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["TradeCode"] = buffer;




        gbk2utf8(
            pChangeAccount->BankID,
            buffer,
            sizeof(pChangeAccount->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BankID"] = buffer;




        gbk2utf8(
            pChangeAccount->BankBranchID,
            buffer,
            sizeof(pChangeAccount->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BankBranchID"] = buffer;




        gbk2utf8(
            pChangeAccount->BrokerID,
            buffer,
            sizeof(pChangeAccount->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BrokerID"] = buffer;




        gbk2utf8(
            pChangeAccount->BrokerBranchID,
            buffer,
            sizeof(pChangeAccount->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BrokerBranchID"] = buffer;




        gbk2utf8(
            pChangeAccount->TradeDate,
            buffer,
            sizeof(pChangeAccount->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["TradeDate"] = buffer;




        gbk2utf8(
            pChangeAccount->TradeTime,
            buffer,
            sizeof(pChangeAccount->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["TradeTime"] = buffer;




        gbk2utf8(
            pChangeAccount->BankSerial,
            buffer,
            sizeof(pChangeAccount->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BankSerial"] = buffer;




        gbk2utf8(
            pChangeAccount->TradingDay,
            buffer,
            sizeof(pChangeAccount->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["TradingDay"] = buffer;



        json_pChangeAccount["PlateSerial"] = pChangeAccount->PlateSerial;




        sprintf(buffer,"%c",pChangeAccount->LastFragment);
        json_pChangeAccount["LastFragment"] = buffer;



        json_pChangeAccount["SessionID"] = pChangeAccount->SessionID;




        gbk2utf8(
            pChangeAccount->CustomerName,
            buffer,
            sizeof(pChangeAccount->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["CustomerName"] = buffer;




        sprintf(buffer,"%c",pChangeAccount->IdCardType);
        json_pChangeAccount["IdCardType"] = buffer;




        gbk2utf8(
            pChangeAccount->IdentifiedCardNo,
            buffer,
            sizeof(pChangeAccount->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pChangeAccount->Gender);
        json_pChangeAccount["Gender"] = buffer;




        gbk2utf8(
            pChangeAccount->CountryCode,
            buffer,
            sizeof(pChangeAccount->CountryCode) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["CountryCode"] = buffer;




        sprintf(buffer,"%c",pChangeAccount->CustType);
        json_pChangeAccount["CustType"] = buffer;




        gbk2utf8(
            pChangeAccount->Address,
            buffer,
            sizeof(pChangeAccount->Address) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["Address"] = buffer;




        gbk2utf8(
            pChangeAccount->ZipCode,
            buffer,
            sizeof(pChangeAccount->ZipCode) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["ZipCode"] = buffer;




        gbk2utf8(
            pChangeAccount->Telephone,
            buffer,
            sizeof(pChangeAccount->Telephone) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["Telephone"] = buffer;




        gbk2utf8(
            pChangeAccount->MobilePhone,
            buffer,
            sizeof(pChangeAccount->MobilePhone) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["MobilePhone"] = buffer;




        gbk2utf8(
            pChangeAccount->Fax,
            buffer,
            sizeof(pChangeAccount->Fax) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["Fax"] = buffer;




        gbk2utf8(
            pChangeAccount->EMail,
            buffer,
            sizeof(pChangeAccount->EMail) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["EMail"] = buffer;




        sprintf(buffer,"%c",pChangeAccount->MoneyAccountStatus);
        json_pChangeAccount["MoneyAccountStatus"] = buffer;




        gbk2utf8(
            pChangeAccount->BankAccount,
            buffer,
            sizeof(pChangeAccount->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BankAccount"] = buffer;




        gbk2utf8(
            pChangeAccount->BankPassWord,
            buffer,
            sizeof(pChangeAccount->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BankPassWord"] = buffer;




        gbk2utf8(
            pChangeAccount->NewBankAccount,
            buffer,
            sizeof(pChangeAccount->NewBankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["NewBankAccount"] = buffer;




        gbk2utf8(
            pChangeAccount->NewBankPassWord,
            buffer,
            sizeof(pChangeAccount->NewBankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["NewBankPassWord"] = buffer;




        gbk2utf8(
            pChangeAccount->AccountID,
            buffer,
            sizeof(pChangeAccount->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["AccountID"] = buffer;




        gbk2utf8(
            pChangeAccount->Password,
            buffer,
            sizeof(pChangeAccount->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["Password"] = buffer;




        sprintf(buffer,"%c",pChangeAccount->BankAccType);
        json_pChangeAccount["BankAccType"] = buffer;



        json_pChangeAccount["InstallID"] = pChangeAccount->InstallID;




        sprintf(buffer,"%c",pChangeAccount->VerifyCertNoFlag);
        json_pChangeAccount["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pChangeAccount->CurrencyID,
            buffer,
            sizeof(pChangeAccount->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["CurrencyID"] = buffer;




        gbk2utf8(
            pChangeAccount->BrokerIDByBank,
            buffer,
            sizeof(pChangeAccount->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["BrokerIDByBank"] = buffer;




        sprintf(buffer,"%c",pChangeAccount->BankPwdFlag);
        json_pChangeAccount["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pChangeAccount->SecuPwdFlag);
        json_pChangeAccount["SecuPwdFlag"] = buffer;



        json_pChangeAccount["TID"] = pChangeAccount->TID;




        gbk2utf8(
            pChangeAccount->Digest,
            buffer,
            sizeof(pChangeAccount->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["Digest"] = buffer;



        json_pChangeAccount["ErrorID"] = pChangeAccount->ErrorID;




        gbk2utf8(
            pChangeAccount->ErrorMsg,
            buffer,
            sizeof(pChangeAccount->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pChangeAccount["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pChangeAccount;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnChangeAccountByBank";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnChangeAccountByBank():执行结束..." << std::endl;
}

///银行发起冲正期货转银行通知
void CTraderHandler::OnRtnRepealFromFutureToBankByBank(
    CThostFtdcRspRepealField * pRspRepeal
) {
    int nRequestID = 0;
    std::cout << "OnRtnRepealFromFutureToBankByBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnRepealFromFutureToBankByBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspRepeal;
    if ( pRspRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pRspRepeal["RepealTimeInterval"] = pRspRepeal->RepealTimeInterval;



        json_pRspRepeal["RepealedTimes"] = pRspRepeal->RepealedTimes;




        sprintf(buffer,"%c",pRspRepeal->BankRepealFlag);
        json_pRspRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BrokerRepealFlag);
        json_pRspRepeal["BrokerRepealFlag"] = buffer;



        json_pRspRepeal["PlateRepealSerial"] = pRspRepeal->PlateRepealSerial;




        gbk2utf8(
            pRspRepeal->BankRepealSerial,
            buffer,
            sizeof(pRspRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankRepealSerial"] = buffer;



        json_pRspRepeal["FutureRepealSerial"] = pRspRepeal->FutureRepealSerial;




        gbk2utf8(
            pRspRepeal->TradeCode,
            buffer,
            sizeof(pRspRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pRspRepeal->BankID,
            buffer,
            sizeof(pRspRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankID"] = buffer;




        gbk2utf8(
            pRspRepeal->BankBranchID,
            buffer,
            sizeof(pRspRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerID,
            buffer,
            sizeof(pRspRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerBranchID,
            buffer,
            sizeof(pRspRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeDate,
            buffer,
            sizeof(pRspRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeTime,
            buffer,
            sizeof(pRspRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSerial,
            buffer,
            sizeof(pRspRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pRspRepeal->TradingDay,
            buffer,
            sizeof(pRspRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradingDay"] = buffer;



        json_pRspRepeal["PlateSerial"] = pRspRepeal->PlateSerial;




        sprintf(buffer,"%c",pRspRepeal->LastFragment);
        json_pRspRepeal["LastFragment"] = buffer;



        json_pRspRepeal["SessionID"] = pRspRepeal->SessionID;




        gbk2utf8(
            pRspRepeal->CustomerName,
            buffer,
            sizeof(pRspRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->IdCardType);
        json_pRspRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pRspRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pRspRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->CustType);
        json_pRspRepeal["CustType"] = buffer;




        gbk2utf8(
            pRspRepeal->BankAccount,
            buffer,
            sizeof(pRspRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pRspRepeal->BankPassWord,
            buffer,
            sizeof(pRspRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pRspRepeal->AccountID,
            buffer,
            sizeof(pRspRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["AccountID"] = buffer;




        gbk2utf8(
            pRspRepeal->Password,
            buffer,
            sizeof(pRspRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Password"] = buffer;



        json_pRspRepeal["InstallID"] = pRspRepeal->InstallID;



        json_pRspRepeal["FutureSerial"] = pRspRepeal->FutureSerial;




        gbk2utf8(
            pRspRepeal->UserID,
            buffer,
            sizeof(pRspRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->VerifyCertNoFlag);
        json_pRspRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->CurrencyID,
            buffer,
            sizeof(pRspRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CurrencyID"] = buffer;



        json_pRspRepeal["TradeAmount"] = pRspRepeal->TradeAmount;



        json_pRspRepeal["FutureFetchAmount"] = pRspRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pRspRepeal->FeePayFlag);
        json_pRspRepeal["FeePayFlag"] = buffer;



        json_pRspRepeal["CustFee"] = pRspRepeal->CustFee;



        json_pRspRepeal["BrokerFee"] = pRspRepeal->BrokerFee;




        gbk2utf8(
            pRspRepeal->Message,
            buffer,
            sizeof(pRspRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Message"] = buffer;




        gbk2utf8(
            pRspRepeal->Digest,
            buffer,
            sizeof(pRspRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankAccType);
        json_pRspRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->DeviceID,
            buffer,
            sizeof(pRspRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankSecuAccType);
        json_pRspRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerIDByBank,
            buffer,
            sizeof(pRspRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSecuAcc,
            buffer,
            sizeof(pRspRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankPwdFlag);
        json_pRspRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->SecuPwdFlag);
        json_pRspRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->OperNo,
            buffer,
            sizeof(pRspRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["OperNo"] = buffer;



        json_pRspRepeal["RequestID"] = pRspRepeal->RequestID;

        nRequestID = pRspRepeal->RequestID;



        json_pRspRepeal["TID"] = pRspRepeal->TID;




        sprintf(buffer,"%c",pRspRepeal->TransferStatus);
        json_pRspRepeal["TransferStatus"] = buffer;



        json_pRspRepeal["ErrorID"] = pRspRepeal->ErrorID;




        gbk2utf8(
            pRspRepeal->ErrorMsg,
            buffer,
            sizeof(pRspRepeal->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnRepealFromFutureToBankByBank";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnRepealFromFutureToBankByBank():执行结束..." << std::endl;
}

///银行发起银期开户通知
void CTraderHandler::OnRtnOpenAccountByBank(
    CThostFtdcOpenAccountField * pOpenAccount
) {
    int nRequestID = 0;
    std::cout << "OnRtnOpenAccountByBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnOpenAccountByBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pOpenAccount;
    if ( pOpenAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pOpenAccount->TradeCode,
            buffer,
            sizeof(pOpenAccount->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["TradeCode"] = buffer;




        gbk2utf8(
            pOpenAccount->BankID,
            buffer,
            sizeof(pOpenAccount->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BankID"] = buffer;




        gbk2utf8(
            pOpenAccount->BankBranchID,
            buffer,
            sizeof(pOpenAccount->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BankBranchID"] = buffer;




        gbk2utf8(
            pOpenAccount->BrokerID,
            buffer,
            sizeof(pOpenAccount->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BrokerID"] = buffer;




        gbk2utf8(
            pOpenAccount->BrokerBranchID,
            buffer,
            sizeof(pOpenAccount->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BrokerBranchID"] = buffer;




        gbk2utf8(
            pOpenAccount->TradeDate,
            buffer,
            sizeof(pOpenAccount->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["TradeDate"] = buffer;




        gbk2utf8(
            pOpenAccount->TradeTime,
            buffer,
            sizeof(pOpenAccount->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["TradeTime"] = buffer;




        gbk2utf8(
            pOpenAccount->BankSerial,
            buffer,
            sizeof(pOpenAccount->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BankSerial"] = buffer;




        gbk2utf8(
            pOpenAccount->TradingDay,
            buffer,
            sizeof(pOpenAccount->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["TradingDay"] = buffer;



        json_pOpenAccount["PlateSerial"] = pOpenAccount->PlateSerial;




        sprintf(buffer,"%c",pOpenAccount->LastFragment);
        json_pOpenAccount["LastFragment"] = buffer;



        json_pOpenAccount["SessionID"] = pOpenAccount->SessionID;




        gbk2utf8(
            pOpenAccount->CustomerName,
            buffer,
            sizeof(pOpenAccount->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["CustomerName"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->IdCardType);
        json_pOpenAccount["IdCardType"] = buffer;




        gbk2utf8(
            pOpenAccount->IdentifiedCardNo,
            buffer,
            sizeof(pOpenAccount->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->Gender);
        json_pOpenAccount["Gender"] = buffer;




        gbk2utf8(
            pOpenAccount->CountryCode,
            buffer,
            sizeof(pOpenAccount->CountryCode) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["CountryCode"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->CustType);
        json_pOpenAccount["CustType"] = buffer;




        gbk2utf8(
            pOpenAccount->Address,
            buffer,
            sizeof(pOpenAccount->Address) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["Address"] = buffer;




        gbk2utf8(
            pOpenAccount->ZipCode,
            buffer,
            sizeof(pOpenAccount->ZipCode) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["ZipCode"] = buffer;




        gbk2utf8(
            pOpenAccount->Telephone,
            buffer,
            sizeof(pOpenAccount->Telephone) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["Telephone"] = buffer;




        gbk2utf8(
            pOpenAccount->MobilePhone,
            buffer,
            sizeof(pOpenAccount->MobilePhone) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["MobilePhone"] = buffer;




        gbk2utf8(
            pOpenAccount->Fax,
            buffer,
            sizeof(pOpenAccount->Fax) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["Fax"] = buffer;




        gbk2utf8(
            pOpenAccount->EMail,
            buffer,
            sizeof(pOpenAccount->EMail) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["EMail"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->MoneyAccountStatus);
        json_pOpenAccount["MoneyAccountStatus"] = buffer;




        gbk2utf8(
            pOpenAccount->BankAccount,
            buffer,
            sizeof(pOpenAccount->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BankAccount"] = buffer;




        gbk2utf8(
            pOpenAccount->BankPassWord,
            buffer,
            sizeof(pOpenAccount->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BankPassWord"] = buffer;




        gbk2utf8(
            pOpenAccount->AccountID,
            buffer,
            sizeof(pOpenAccount->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["AccountID"] = buffer;




        gbk2utf8(
            pOpenAccount->Password,
            buffer,
            sizeof(pOpenAccount->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["Password"] = buffer;



        json_pOpenAccount["InstallID"] = pOpenAccount->InstallID;




        sprintf(buffer,"%c",pOpenAccount->VerifyCertNoFlag);
        json_pOpenAccount["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pOpenAccount->CurrencyID,
            buffer,
            sizeof(pOpenAccount->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["CurrencyID"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->CashExchangeCode);
        json_pOpenAccount["CashExchangeCode"] = buffer;




        gbk2utf8(
            pOpenAccount->Digest,
            buffer,
            sizeof(pOpenAccount->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["Digest"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->BankAccType);
        json_pOpenAccount["BankAccType"] = buffer;




        gbk2utf8(
            pOpenAccount->DeviceID,
            buffer,
            sizeof(pOpenAccount->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["DeviceID"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->BankSecuAccType);
        json_pOpenAccount["BankSecuAccType"] = buffer;




        gbk2utf8(
            pOpenAccount->BrokerIDByBank,
            buffer,
            sizeof(pOpenAccount->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pOpenAccount->BankSecuAcc,
            buffer,
            sizeof(pOpenAccount->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->BankPwdFlag);
        json_pOpenAccount["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pOpenAccount->SecuPwdFlag);
        json_pOpenAccount["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pOpenAccount->OperNo,
            buffer,
            sizeof(pOpenAccount->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["OperNo"] = buffer;



        json_pOpenAccount["TID"] = pOpenAccount->TID;




        gbk2utf8(
            pOpenAccount->UserID,
            buffer,
            sizeof(pOpenAccount->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["UserID"] = buffer;



        json_pOpenAccount["ErrorID"] = pOpenAccount->ErrorID;




        gbk2utf8(
            pOpenAccount->ErrorMsg,
            buffer,
            sizeof(pOpenAccount->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pOpenAccount["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pOpenAccount;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnOpenAccountByBank";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnOpenAccountByBank():执行结束..." << std::endl;
}

///成交通知
void CTraderHandler::OnRtnTrade(
    CThostFtdcTradeField * pTrade
) {
    int nRequestID = 0;
    std::cout << "OnRtnTrade():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnTrade";

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




        sprintf(buffer,"%c",pTrade->Direction);
        json_pTrade["Direction"] = buffer;




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




        sprintf(buffer,"%c",pTrade->TradingRole);
        json_pTrade["TradingRole"] = buffer;




        gbk2utf8(
            pTrade->ExchangeInstID,
            buffer,
            sizeof(pTrade->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pTrade["ExchangeInstID"] = buffer;




        sprintf(buffer,"%c",pTrade->OffsetFlag);
        json_pTrade["OffsetFlag"] = buffer;




        sprintf(buffer,"%c",pTrade->HedgeFlag);
        json_pTrade["HedgeFlag"] = buffer;



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




        sprintf(buffer,"%c",pTrade->TradeType);
        json_pTrade["TradeType"] = buffer;




        sprintf(buffer,"%c",pTrade->PriceSource);
        json_pTrade["PriceSource"] = buffer;




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




        sprintf(buffer,"%c",pTrade->TradeSource);
        json_pTrade["TradeSource"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pTrade;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnTrade";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnTrade():执行结束..." << std::endl;
}

///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
void CTraderHandler::OnRtnRepealFromFutureToBankByFuture(
    CThostFtdcRspRepealField * pRspRepeal
) {
    int nRequestID = 0;
    std::cout << "OnRtnRepealFromFutureToBankByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnRepealFromFutureToBankByFuture";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspRepeal;
    if ( pRspRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pRspRepeal["RepealTimeInterval"] = pRspRepeal->RepealTimeInterval;



        json_pRspRepeal["RepealedTimes"] = pRspRepeal->RepealedTimes;




        sprintf(buffer,"%c",pRspRepeal->BankRepealFlag);
        json_pRspRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BrokerRepealFlag);
        json_pRspRepeal["BrokerRepealFlag"] = buffer;



        json_pRspRepeal["PlateRepealSerial"] = pRspRepeal->PlateRepealSerial;




        gbk2utf8(
            pRspRepeal->BankRepealSerial,
            buffer,
            sizeof(pRspRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankRepealSerial"] = buffer;



        json_pRspRepeal["FutureRepealSerial"] = pRspRepeal->FutureRepealSerial;




        gbk2utf8(
            pRspRepeal->TradeCode,
            buffer,
            sizeof(pRspRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pRspRepeal->BankID,
            buffer,
            sizeof(pRspRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankID"] = buffer;




        gbk2utf8(
            pRspRepeal->BankBranchID,
            buffer,
            sizeof(pRspRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerID,
            buffer,
            sizeof(pRspRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerBranchID,
            buffer,
            sizeof(pRspRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeDate,
            buffer,
            sizeof(pRspRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeTime,
            buffer,
            sizeof(pRspRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSerial,
            buffer,
            sizeof(pRspRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pRspRepeal->TradingDay,
            buffer,
            sizeof(pRspRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradingDay"] = buffer;



        json_pRspRepeal["PlateSerial"] = pRspRepeal->PlateSerial;




        sprintf(buffer,"%c",pRspRepeal->LastFragment);
        json_pRspRepeal["LastFragment"] = buffer;



        json_pRspRepeal["SessionID"] = pRspRepeal->SessionID;




        gbk2utf8(
            pRspRepeal->CustomerName,
            buffer,
            sizeof(pRspRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->IdCardType);
        json_pRspRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pRspRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pRspRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->CustType);
        json_pRspRepeal["CustType"] = buffer;




        gbk2utf8(
            pRspRepeal->BankAccount,
            buffer,
            sizeof(pRspRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pRspRepeal->BankPassWord,
            buffer,
            sizeof(pRspRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pRspRepeal->AccountID,
            buffer,
            sizeof(pRspRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["AccountID"] = buffer;




        gbk2utf8(
            pRspRepeal->Password,
            buffer,
            sizeof(pRspRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Password"] = buffer;



        json_pRspRepeal["InstallID"] = pRspRepeal->InstallID;



        json_pRspRepeal["FutureSerial"] = pRspRepeal->FutureSerial;




        gbk2utf8(
            pRspRepeal->UserID,
            buffer,
            sizeof(pRspRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->VerifyCertNoFlag);
        json_pRspRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->CurrencyID,
            buffer,
            sizeof(pRspRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CurrencyID"] = buffer;



        json_pRspRepeal["TradeAmount"] = pRspRepeal->TradeAmount;



        json_pRspRepeal["FutureFetchAmount"] = pRspRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pRspRepeal->FeePayFlag);
        json_pRspRepeal["FeePayFlag"] = buffer;



        json_pRspRepeal["CustFee"] = pRspRepeal->CustFee;



        json_pRspRepeal["BrokerFee"] = pRspRepeal->BrokerFee;




        gbk2utf8(
            pRspRepeal->Message,
            buffer,
            sizeof(pRspRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Message"] = buffer;




        gbk2utf8(
            pRspRepeal->Digest,
            buffer,
            sizeof(pRspRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankAccType);
        json_pRspRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->DeviceID,
            buffer,
            sizeof(pRspRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankSecuAccType);
        json_pRspRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerIDByBank,
            buffer,
            sizeof(pRspRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSecuAcc,
            buffer,
            sizeof(pRspRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankPwdFlag);
        json_pRspRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->SecuPwdFlag);
        json_pRspRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->OperNo,
            buffer,
            sizeof(pRspRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["OperNo"] = buffer;



        json_pRspRepeal["RequestID"] = pRspRepeal->RequestID;

        nRequestID = pRspRepeal->RequestID;



        json_pRspRepeal["TID"] = pRspRepeal->TID;




        sprintf(buffer,"%c",pRspRepeal->TransferStatus);
        json_pRspRepeal["TransferStatus"] = buffer;



        json_pRspRepeal["ErrorID"] = pRspRepeal->ErrorID;




        gbk2utf8(
            pRspRepeal->ErrorMsg,
            buffer,
            sizeof(pRspRepeal->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnRepealFromFutureToBankByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnRepealFromFutureToBankByFuture():执行结束..." << std::endl;
}

///提示条件单校验错误
void CTraderHandler::OnRtnErrorConditionalOrder(
    CThostFtdcErrorConditionalOrderField * pErrorConditionalOrder
) {
    int nRequestID = 0;
    std::cout << "OnRtnErrorConditionalOrder():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnErrorConditionalOrder";

    /// 返回数据结构体转化json格式
    Json::Value json_pErrorConditionalOrder;
    if ( pErrorConditionalOrder != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pErrorConditionalOrder->BrokerID,
            buffer,
            sizeof(pErrorConditionalOrder->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["BrokerID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->InvestorID,
            buffer,
            sizeof(pErrorConditionalOrder->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["InvestorID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->InstrumentID,
            buffer,
            sizeof(pErrorConditionalOrder->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["InstrumentID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->OrderRef,
            buffer,
            sizeof(pErrorConditionalOrder->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["OrderRef"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->UserID,
            buffer,
            sizeof(pErrorConditionalOrder->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["UserID"] = buffer;




        sprintf(buffer,"%c",pErrorConditionalOrder->OrderPriceType);
        json_pErrorConditionalOrder["OrderPriceType"] = buffer;




        sprintf(buffer,"%c",pErrorConditionalOrder->Direction);
        json_pErrorConditionalOrder["Direction"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->CombOffsetFlag,
            buffer,
            sizeof(pErrorConditionalOrder->CombOffsetFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["CombOffsetFlag"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->CombHedgeFlag,
            buffer,
            sizeof(pErrorConditionalOrder->CombHedgeFlag) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["CombHedgeFlag"] = buffer;



        json_pErrorConditionalOrder["LimitPrice"] = pErrorConditionalOrder->LimitPrice;



        json_pErrorConditionalOrder["VolumeTotalOriginal"] = pErrorConditionalOrder->VolumeTotalOriginal;




        sprintf(buffer,"%c",pErrorConditionalOrder->TimeCondition);
        json_pErrorConditionalOrder["TimeCondition"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->GTDDate,
            buffer,
            sizeof(pErrorConditionalOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["GTDDate"] = buffer;




        sprintf(buffer,"%c",pErrorConditionalOrder->VolumeCondition);
        json_pErrorConditionalOrder["VolumeCondition"] = buffer;



        json_pErrorConditionalOrder["MinVolume"] = pErrorConditionalOrder->MinVolume;




        sprintf(buffer,"%c",pErrorConditionalOrder->ContingentCondition);
        json_pErrorConditionalOrder["ContingentCondition"] = buffer;



        json_pErrorConditionalOrder["StopPrice"] = pErrorConditionalOrder->StopPrice;




        sprintf(buffer,"%c",pErrorConditionalOrder->ForceCloseReason);
        json_pErrorConditionalOrder["ForceCloseReason"] = buffer;



        json_pErrorConditionalOrder["IsAutoSuspend"] = pErrorConditionalOrder->IsAutoSuspend;




        gbk2utf8(
            pErrorConditionalOrder->BusinessUnit,
            buffer,
            sizeof(pErrorConditionalOrder->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["BusinessUnit"] = buffer;



        json_pErrorConditionalOrder["RequestID"] = pErrorConditionalOrder->RequestID;

        nRequestID = pErrorConditionalOrder->RequestID;




        gbk2utf8(
            pErrorConditionalOrder->OrderLocalID,
            buffer,
            sizeof(pErrorConditionalOrder->OrderLocalID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["OrderLocalID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->ExchangeID,
            buffer,
            sizeof(pErrorConditionalOrder->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ExchangeID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->ParticipantID,
            buffer,
            sizeof(pErrorConditionalOrder->ParticipantID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ParticipantID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->ClientID,
            buffer,
            sizeof(pErrorConditionalOrder->ClientID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ClientID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->ExchangeInstID,
            buffer,
            sizeof(pErrorConditionalOrder->ExchangeInstID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ExchangeInstID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->TraderID,
            buffer,
            sizeof(pErrorConditionalOrder->TraderID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["TraderID"] = buffer;



        json_pErrorConditionalOrder["InstallID"] = pErrorConditionalOrder->InstallID;




        sprintf(buffer,"%c",pErrorConditionalOrder->OrderSubmitStatus);
        json_pErrorConditionalOrder["OrderSubmitStatus"] = buffer;



        json_pErrorConditionalOrder["NotifySequence"] = pErrorConditionalOrder->NotifySequence;




        gbk2utf8(
            pErrorConditionalOrder->TradingDay,
            buffer,
            sizeof(pErrorConditionalOrder->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["TradingDay"] = buffer;



        json_pErrorConditionalOrder["SettlementID"] = pErrorConditionalOrder->SettlementID;




        gbk2utf8(
            pErrorConditionalOrder->OrderSysID,
            buffer,
            sizeof(pErrorConditionalOrder->OrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["OrderSysID"] = buffer;




        sprintf(buffer,"%c",pErrorConditionalOrder->OrderSource);
        json_pErrorConditionalOrder["OrderSource"] = buffer;




        sprintf(buffer,"%c",pErrorConditionalOrder->OrderStatus);
        json_pErrorConditionalOrder["OrderStatus"] = buffer;




        sprintf(buffer,"%c",pErrorConditionalOrder->OrderType);
        json_pErrorConditionalOrder["OrderType"] = buffer;



        json_pErrorConditionalOrder["VolumeTraded"] = pErrorConditionalOrder->VolumeTraded;



        json_pErrorConditionalOrder["VolumeTotal"] = pErrorConditionalOrder->VolumeTotal;




        gbk2utf8(
            pErrorConditionalOrder->InsertDate,
            buffer,
            sizeof(pErrorConditionalOrder->InsertDate) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["InsertDate"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->InsertTime,
            buffer,
            sizeof(pErrorConditionalOrder->InsertTime) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["InsertTime"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->ActiveTime,
            buffer,
            sizeof(pErrorConditionalOrder->ActiveTime) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ActiveTime"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->SuspendTime,
            buffer,
            sizeof(pErrorConditionalOrder->SuspendTime) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["SuspendTime"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->UpdateTime,
            buffer,
            sizeof(pErrorConditionalOrder->UpdateTime) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["UpdateTime"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->CancelTime,
            buffer,
            sizeof(pErrorConditionalOrder->CancelTime) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["CancelTime"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->ActiveTraderID,
            buffer,
            sizeof(pErrorConditionalOrder->ActiveTraderID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ActiveTraderID"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->ClearingPartID,
            buffer,
            sizeof(pErrorConditionalOrder->ClearingPartID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ClearingPartID"] = buffer;



        json_pErrorConditionalOrder["SequenceNo"] = pErrorConditionalOrder->SequenceNo;



        json_pErrorConditionalOrder["FrontID"] = pErrorConditionalOrder->FrontID;



        json_pErrorConditionalOrder["SessionID"] = pErrorConditionalOrder->SessionID;




        gbk2utf8(
            pErrorConditionalOrder->UserProductInfo,
            buffer,
            sizeof(pErrorConditionalOrder->UserProductInfo) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["UserProductInfo"] = buffer;




        gbk2utf8(
            pErrorConditionalOrder->StatusMsg,
            buffer,
            sizeof(pErrorConditionalOrder->StatusMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["StatusMsg"] = buffer;



        json_pErrorConditionalOrder["UserForceClose"] = pErrorConditionalOrder->UserForceClose;




        gbk2utf8(
            pErrorConditionalOrder->ActiveUserID,
            buffer,
            sizeof(pErrorConditionalOrder->ActiveUserID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ActiveUserID"] = buffer;



        json_pErrorConditionalOrder["BrokerOrderSeq"] = pErrorConditionalOrder->BrokerOrderSeq;




        gbk2utf8(
            pErrorConditionalOrder->RelativeOrderSysID,
            buffer,
            sizeof(pErrorConditionalOrder->RelativeOrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["RelativeOrderSysID"] = buffer;



        json_pErrorConditionalOrder["ZCETotalTradedVolume"] = pErrorConditionalOrder->ZCETotalTradedVolume;



        json_pErrorConditionalOrder["ErrorID"] = pErrorConditionalOrder->ErrorID;




        gbk2utf8(
            pErrorConditionalOrder->ErrorMsg,
            buffer,
            sizeof(pErrorConditionalOrder->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pErrorConditionalOrder["ErrorMsg"] = buffer;



        json_pErrorConditionalOrder["IsSwapOrder"] = pErrorConditionalOrder->IsSwapOrder;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pErrorConditionalOrder;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnErrorConditionalOrder";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnErrorConditionalOrder():执行结束..." << std::endl;
}

///银行发起冲正银行转期货通知
void CTraderHandler::OnRtnRepealFromBankToFutureByBank(
    CThostFtdcRspRepealField * pRspRepeal
) {
    int nRequestID = 0;
    std::cout << "OnRtnRepealFromBankToFutureByBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnRepealFromBankToFutureByBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspRepeal;
    if ( pRspRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pRspRepeal["RepealTimeInterval"] = pRspRepeal->RepealTimeInterval;



        json_pRspRepeal["RepealedTimes"] = pRspRepeal->RepealedTimes;




        sprintf(buffer,"%c",pRspRepeal->BankRepealFlag);
        json_pRspRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BrokerRepealFlag);
        json_pRspRepeal["BrokerRepealFlag"] = buffer;



        json_pRspRepeal["PlateRepealSerial"] = pRspRepeal->PlateRepealSerial;




        gbk2utf8(
            pRspRepeal->BankRepealSerial,
            buffer,
            sizeof(pRspRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankRepealSerial"] = buffer;



        json_pRspRepeal["FutureRepealSerial"] = pRspRepeal->FutureRepealSerial;




        gbk2utf8(
            pRspRepeal->TradeCode,
            buffer,
            sizeof(pRspRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pRspRepeal->BankID,
            buffer,
            sizeof(pRspRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankID"] = buffer;




        gbk2utf8(
            pRspRepeal->BankBranchID,
            buffer,
            sizeof(pRspRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerID,
            buffer,
            sizeof(pRspRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerBranchID,
            buffer,
            sizeof(pRspRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeDate,
            buffer,
            sizeof(pRspRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pRspRepeal->TradeTime,
            buffer,
            sizeof(pRspRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSerial,
            buffer,
            sizeof(pRspRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pRspRepeal->TradingDay,
            buffer,
            sizeof(pRspRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["TradingDay"] = buffer;



        json_pRspRepeal["PlateSerial"] = pRspRepeal->PlateSerial;




        sprintf(buffer,"%c",pRspRepeal->LastFragment);
        json_pRspRepeal["LastFragment"] = buffer;



        json_pRspRepeal["SessionID"] = pRspRepeal->SessionID;




        gbk2utf8(
            pRspRepeal->CustomerName,
            buffer,
            sizeof(pRspRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->IdCardType);
        json_pRspRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pRspRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pRspRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->CustType);
        json_pRspRepeal["CustType"] = buffer;




        gbk2utf8(
            pRspRepeal->BankAccount,
            buffer,
            sizeof(pRspRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pRspRepeal->BankPassWord,
            buffer,
            sizeof(pRspRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pRspRepeal->AccountID,
            buffer,
            sizeof(pRspRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["AccountID"] = buffer;




        gbk2utf8(
            pRspRepeal->Password,
            buffer,
            sizeof(pRspRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Password"] = buffer;



        json_pRspRepeal["InstallID"] = pRspRepeal->InstallID;



        json_pRspRepeal["FutureSerial"] = pRspRepeal->FutureSerial;




        gbk2utf8(
            pRspRepeal->UserID,
            buffer,
            sizeof(pRspRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->VerifyCertNoFlag);
        json_pRspRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->CurrencyID,
            buffer,
            sizeof(pRspRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["CurrencyID"] = buffer;



        json_pRspRepeal["TradeAmount"] = pRspRepeal->TradeAmount;



        json_pRspRepeal["FutureFetchAmount"] = pRspRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pRspRepeal->FeePayFlag);
        json_pRspRepeal["FeePayFlag"] = buffer;



        json_pRspRepeal["CustFee"] = pRspRepeal->CustFee;



        json_pRspRepeal["BrokerFee"] = pRspRepeal->BrokerFee;




        gbk2utf8(
            pRspRepeal->Message,
            buffer,
            sizeof(pRspRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Message"] = buffer;




        gbk2utf8(
            pRspRepeal->Digest,
            buffer,
            sizeof(pRspRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankAccType);
        json_pRspRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->DeviceID,
            buffer,
            sizeof(pRspRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankSecuAccType);
        json_pRspRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pRspRepeal->BrokerIDByBank,
            buffer,
            sizeof(pRspRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pRspRepeal->BankSecuAcc,
            buffer,
            sizeof(pRspRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->BankPwdFlag);
        json_pRspRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pRspRepeal->SecuPwdFlag);
        json_pRspRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pRspRepeal->OperNo,
            buffer,
            sizeof(pRspRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["OperNo"] = buffer;



        json_pRspRepeal["RequestID"] = pRspRepeal->RequestID;

        nRequestID = pRspRepeal->RequestID;



        json_pRspRepeal["TID"] = pRspRepeal->TID;




        sprintf(buffer,"%c",pRspRepeal->TransferStatus);
        json_pRspRepeal["TransferStatus"] = buffer;



        json_pRspRepeal["ErrorID"] = pRspRepeal->ErrorID;




        gbk2utf8(
            pRspRepeal->ErrorMsg,
            buffer,
            sizeof(pRspRepeal->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspRepeal["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnRepealFromBankToFutureByBank";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnRepealFromBankToFutureByBank():执行结束..." << std::endl;
}

///报单通知
void CTraderHandler::OnRtnOrder(
    CThostFtdcOrderField * pOrder
) {
    int nRequestID = 0;
    std::cout << "OnRtnOrder():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnOrder";

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




        sprintf(buffer,"%c",pOrder->OrderPriceType);
        json_pOrder["OrderPriceType"] = buffer;




        sprintf(buffer,"%c",pOrder->Direction);
        json_pOrder["Direction"] = buffer;




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




        sprintf(buffer,"%c",pOrder->TimeCondition);
        json_pOrder["TimeCondition"] = buffer;




        gbk2utf8(
            pOrder->GTDDate,
            buffer,
            sizeof(pOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["GTDDate"] = buffer;




        sprintf(buffer,"%c",pOrder->VolumeCondition);
        json_pOrder["VolumeCondition"] = buffer;



        json_pOrder["MinVolume"] = pOrder->MinVolume;




        sprintf(buffer,"%c",pOrder->ContingentCondition);
        json_pOrder["ContingentCondition"] = buffer;



        json_pOrder["StopPrice"] = pOrder->StopPrice;




        sprintf(buffer,"%c",pOrder->ForceCloseReason);
        json_pOrder["ForceCloseReason"] = buffer;



        json_pOrder["IsAutoSuspend"] = pOrder->IsAutoSuspend;




        gbk2utf8(
            pOrder->BusinessUnit,
            buffer,
            sizeof(pOrder->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pOrder["BusinessUnit"] = buffer;



        json_pOrder["RequestID"] = pOrder->RequestID;

        nRequestID = pOrder->RequestID;




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




        sprintf(buffer,"%c",pOrder->OrderSubmitStatus);
        json_pOrder["OrderSubmitStatus"] = buffer;



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




        sprintf(buffer,"%c",pOrder->OrderSource);
        json_pOrder["OrderSource"] = buffer;




        sprintf(buffer,"%c",pOrder->OrderStatus);
        json_pOrder["OrderStatus"] = buffer;




        sprintf(buffer,"%c",pOrder->OrderType);
        json_pOrder["OrderType"] = buffer;



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

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pOrder;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnOrder";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnRtnOrder():执行结束..." << std::endl;
}

///银行发起银期销户通知
void CTraderHandler::OnRtnCancelAccountByBank(
    CThostFtdcCancelAccountField * pCancelAccount
) {
    int nRequestID = 0;
    std::cout << "OnRtnCancelAccountByBank():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRtnCancelAccountByBank";

    /// 返回数据结构体转化json格式
    Json::Value json_pCancelAccount;
    if ( pCancelAccount != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pCancelAccount->TradeCode,
            buffer,
            sizeof(pCancelAccount->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["TradeCode"] = buffer;




        gbk2utf8(
            pCancelAccount->BankID,
            buffer,
            sizeof(pCancelAccount->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BankID"] = buffer;




        gbk2utf8(
            pCancelAccount->BankBranchID,
            buffer,
            sizeof(pCancelAccount->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BankBranchID"] = buffer;




        gbk2utf8(
            pCancelAccount->BrokerID,
            buffer,
            sizeof(pCancelAccount->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BrokerID"] = buffer;




        gbk2utf8(
            pCancelAccount->BrokerBranchID,
            buffer,
            sizeof(pCancelAccount->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BrokerBranchID"] = buffer;




        gbk2utf8(
            pCancelAccount->TradeDate,
            buffer,
            sizeof(pCancelAccount->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["TradeDate"] = buffer;




        gbk2utf8(
            pCancelAccount->TradeTime,
            buffer,
            sizeof(pCancelAccount->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["TradeTime"] = buffer;




        gbk2utf8(
            pCancelAccount->BankSerial,
            buffer,
            sizeof(pCancelAccount->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BankSerial"] = buffer;




        gbk2utf8(
            pCancelAccount->TradingDay,
            buffer,
            sizeof(pCancelAccount->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["TradingDay"] = buffer;



        json_pCancelAccount["PlateSerial"] = pCancelAccount->PlateSerial;




        sprintf(buffer,"%c",pCancelAccount->LastFragment);
        json_pCancelAccount["LastFragment"] = buffer;



        json_pCancelAccount["SessionID"] = pCancelAccount->SessionID;




        gbk2utf8(
            pCancelAccount->CustomerName,
            buffer,
            sizeof(pCancelAccount->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["CustomerName"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->IdCardType);
        json_pCancelAccount["IdCardType"] = buffer;




        gbk2utf8(
            pCancelAccount->IdentifiedCardNo,
            buffer,
            sizeof(pCancelAccount->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->Gender);
        json_pCancelAccount["Gender"] = buffer;




        gbk2utf8(
            pCancelAccount->CountryCode,
            buffer,
            sizeof(pCancelAccount->CountryCode) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["CountryCode"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->CustType);
        json_pCancelAccount["CustType"] = buffer;




        gbk2utf8(
            pCancelAccount->Address,
            buffer,
            sizeof(pCancelAccount->Address) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["Address"] = buffer;




        gbk2utf8(
            pCancelAccount->ZipCode,
            buffer,
            sizeof(pCancelAccount->ZipCode) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["ZipCode"] = buffer;




        gbk2utf8(
            pCancelAccount->Telephone,
            buffer,
            sizeof(pCancelAccount->Telephone) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["Telephone"] = buffer;




        gbk2utf8(
            pCancelAccount->MobilePhone,
            buffer,
            sizeof(pCancelAccount->MobilePhone) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["MobilePhone"] = buffer;




        gbk2utf8(
            pCancelAccount->Fax,
            buffer,
            sizeof(pCancelAccount->Fax) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["Fax"] = buffer;




        gbk2utf8(
            pCancelAccount->EMail,
            buffer,
            sizeof(pCancelAccount->EMail) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["EMail"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->MoneyAccountStatus);
        json_pCancelAccount["MoneyAccountStatus"] = buffer;




        gbk2utf8(
            pCancelAccount->BankAccount,
            buffer,
            sizeof(pCancelAccount->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BankAccount"] = buffer;




        gbk2utf8(
            pCancelAccount->BankPassWord,
            buffer,
            sizeof(pCancelAccount->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BankPassWord"] = buffer;




        gbk2utf8(
            pCancelAccount->AccountID,
            buffer,
            sizeof(pCancelAccount->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["AccountID"] = buffer;




        gbk2utf8(
            pCancelAccount->Password,
            buffer,
            sizeof(pCancelAccount->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["Password"] = buffer;



        json_pCancelAccount["InstallID"] = pCancelAccount->InstallID;




        sprintf(buffer,"%c",pCancelAccount->VerifyCertNoFlag);
        json_pCancelAccount["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pCancelAccount->CurrencyID,
            buffer,
            sizeof(pCancelAccount->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["CurrencyID"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->CashExchangeCode);
        json_pCancelAccount["CashExchangeCode"] = buffer;




        gbk2utf8(
            pCancelAccount->Digest,
            buffer,
            sizeof(pCancelAccount->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["Digest"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->BankAccType);
        json_pCancelAccount["BankAccType"] = buffer;




        gbk2utf8(
            pCancelAccount->DeviceID,
            buffer,
            sizeof(pCancelAccount->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["DeviceID"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->BankSecuAccType);
        json_pCancelAccount["BankSecuAccType"] = buffer;




        gbk2utf8(
            pCancelAccount->BrokerIDByBank,
            buffer,
            sizeof(pCancelAccount->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pCancelAccount->BankSecuAcc,
            buffer,
            sizeof(pCancelAccount->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->BankPwdFlag);
        json_pCancelAccount["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pCancelAccount->SecuPwdFlag);
        json_pCancelAccount["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pCancelAccount->OperNo,
            buffer,
            sizeof(pCancelAccount->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["OperNo"] = buffer;



        json_pCancelAccount["TID"] = pCancelAccount->TID;




        gbk2utf8(
            pCancelAccount->UserID,
            buffer,
            sizeof(pCancelAccount->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["UserID"] = buffer;



        json_pCancelAccount["ErrorID"] = pCancelAccount->ErrorID;




        gbk2utf8(
            pCancelAccount->ErrorMsg,
            buffer,
            sizeof(pCancelAccount->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pCancelAccount["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pCancelAccount;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRtnCancelAccountByBank";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

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
    int nRequestID = 0;
    std::cout << "OnErrRtnRepealFutureToBankByFutureManual():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnErrRtnRepealFutureToBankByFutureManual";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqRepeal;
    if ( pReqRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pReqRepeal["RepealTimeInterval"] = pReqRepeal->RepealTimeInterval;



        json_pReqRepeal["RepealedTimes"] = pReqRepeal->RepealedTimes;




        sprintf(buffer,"%c",pReqRepeal->BankRepealFlag);
        json_pReqRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BrokerRepealFlag);
        json_pReqRepeal["BrokerRepealFlag"] = buffer;



        json_pReqRepeal["PlateRepealSerial"] = pReqRepeal->PlateRepealSerial;




        gbk2utf8(
            pReqRepeal->BankRepealSerial,
            buffer,
            sizeof(pReqRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankRepealSerial"] = buffer;



        json_pReqRepeal["FutureRepealSerial"] = pReqRepeal->FutureRepealSerial;




        gbk2utf8(
            pReqRepeal->TradeCode,
            buffer,
            sizeof(pReqRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pReqRepeal->BankID,
            buffer,
            sizeof(pReqRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankID"] = buffer;




        gbk2utf8(
            pReqRepeal->BankBranchID,
            buffer,
            sizeof(pReqRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pReqRepeal->BrokerID,
            buffer,
            sizeof(pReqRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pReqRepeal->BrokerBranchID,
            buffer,
            sizeof(pReqRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pReqRepeal->TradeDate,
            buffer,
            sizeof(pReqRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pReqRepeal->TradeTime,
            buffer,
            sizeof(pReqRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pReqRepeal->BankSerial,
            buffer,
            sizeof(pReqRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pReqRepeal->TradingDay,
            buffer,
            sizeof(pReqRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradingDay"] = buffer;



        json_pReqRepeal["PlateSerial"] = pReqRepeal->PlateSerial;




        sprintf(buffer,"%c",pReqRepeal->LastFragment);
        json_pReqRepeal["LastFragment"] = buffer;



        json_pReqRepeal["SessionID"] = pReqRepeal->SessionID;




        gbk2utf8(
            pReqRepeal->CustomerName,
            buffer,
            sizeof(pReqRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->IdCardType);
        json_pReqRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pReqRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pReqRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->CustType);
        json_pReqRepeal["CustType"] = buffer;




        gbk2utf8(
            pReqRepeal->BankAccount,
            buffer,
            sizeof(pReqRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pReqRepeal->BankPassWord,
            buffer,
            sizeof(pReqRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pReqRepeal->AccountID,
            buffer,
            sizeof(pReqRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["AccountID"] = buffer;




        gbk2utf8(
            pReqRepeal->Password,
            buffer,
            sizeof(pReqRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["Password"] = buffer;



        json_pReqRepeal["InstallID"] = pReqRepeal->InstallID;



        json_pReqRepeal["FutureSerial"] = pReqRepeal->FutureSerial;




        gbk2utf8(
            pReqRepeal->UserID,
            buffer,
            sizeof(pReqRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->VerifyCertNoFlag);
        json_pReqRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pReqRepeal->CurrencyID,
            buffer,
            sizeof(pReqRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["CurrencyID"] = buffer;



        json_pReqRepeal["TradeAmount"] = pReqRepeal->TradeAmount;



        json_pReqRepeal["FutureFetchAmount"] = pReqRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pReqRepeal->FeePayFlag);
        json_pReqRepeal["FeePayFlag"] = buffer;



        json_pReqRepeal["CustFee"] = pReqRepeal->CustFee;



        json_pReqRepeal["BrokerFee"] = pReqRepeal->BrokerFee;




        gbk2utf8(
            pReqRepeal->Message,
            buffer,
            sizeof(pReqRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["Message"] = buffer;




        gbk2utf8(
            pReqRepeal->Digest,
            buffer,
            sizeof(pReqRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BankAccType);
        json_pReqRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pReqRepeal->DeviceID,
            buffer,
            sizeof(pReqRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BankSecuAccType);
        json_pReqRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pReqRepeal->BrokerIDByBank,
            buffer,
            sizeof(pReqRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pReqRepeal->BankSecuAcc,
            buffer,
            sizeof(pReqRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BankPwdFlag);
        json_pReqRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->SecuPwdFlag);
        json_pReqRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pReqRepeal->OperNo,
            buffer,
            sizeof(pReqRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["OperNo"] = buffer;



        json_pReqRepeal["RequestID"] = pReqRepeal->RequestID;

        nRequestID = pReqRepeal->RequestID;



        json_pReqRepeal["TID"] = pReqRepeal->TID;




        sprintf(buffer,"%c",pReqRepeal->TransferStatus);
        json_pReqRepeal["TransferStatus"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnErrRtnRepealFutureToBankByFutureManual";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnErrRtnRepealFutureToBankByFutureManual():执行结束..." << std::endl;
}

///期货发起期货资金转银行错误回报
void CTraderHandler::OnErrRtnFutureToBankByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo
) {
    int nRequestID = 0;
    std::cout << "OnErrRtnFutureToBankByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnErrRtnFutureToBankByFuture";

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




        sprintf(buffer,"%c",pReqTransfer->LastFragment);
        json_pReqTransfer["LastFragment"] = buffer;



        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;




        gbk2utf8(
            pReqTransfer->CustomerName,
            buffer,
            sizeof(pReqTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->IdCardType);
        json_pReqTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pReqTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pReqTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->CustType);
        json_pReqTransfer["CustType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->VerifyCertNoFlag);
        json_pReqTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->CurrencyID,
            buffer,
            sizeof(pReqTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CurrencyID"] = buffer;



        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;



        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;




        sprintf(buffer,"%c",pReqTransfer->FeePayFlag);
        json_pReqTransfer["FeePayFlag"] = buffer;



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




        sprintf(buffer,"%c",pReqTransfer->BankAccType);
        json_pReqTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pReqTransfer->DeviceID,
            buffer,
            sizeof(pReqTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->BankSecuAccType);
        json_pReqTransfer["BankSecuAccType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->BankPwdFlag);
        json_pReqTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->SecuPwdFlag);
        json_pReqTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->OperNo,
            buffer,
            sizeof(pReqTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["OperNo"] = buffer;



        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;

        nRequestID = pReqTransfer->RequestID;



        json_pReqTransfer["TID"] = pReqTransfer->TID;




        sprintf(buffer,"%c",pReqTransfer->TransferStatus);
        json_pReqTransfer["TransferStatus"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqTransfer;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnErrRtnFutureToBankByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnErrRtnFutureToBankByFuture():执行结束..." << std::endl;
}

///报单录入错误回报
void CTraderHandler::OnErrRtnOrderInsert(
    CThostFtdcInputOrderField * pInputOrder,
    CThostFtdcRspInfoField * pRspInfo
) {
    int nRequestID = 0;
    std::cout << "OnErrRtnOrderInsert():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnErrRtnOrderInsert";

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




        sprintf(buffer,"%c",pInputOrder->OrderPriceType);
        json_pInputOrder["OrderPriceType"] = buffer;




        sprintf(buffer,"%c",pInputOrder->Direction);
        json_pInputOrder["Direction"] = buffer;




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




        sprintf(buffer,"%c",pInputOrder->TimeCondition);
        json_pInputOrder["TimeCondition"] = buffer;




        gbk2utf8(
            pInputOrder->GTDDate,
            buffer,
            sizeof(pInputOrder->GTDDate) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["GTDDate"] = buffer;




        sprintf(buffer,"%c",pInputOrder->VolumeCondition);
        json_pInputOrder["VolumeCondition"] = buffer;



        json_pInputOrder["MinVolume"] = pInputOrder->MinVolume;




        sprintf(buffer,"%c",pInputOrder->ContingentCondition);
        json_pInputOrder["ContingentCondition"] = buffer;



        json_pInputOrder["StopPrice"] = pInputOrder->StopPrice;




        sprintf(buffer,"%c",pInputOrder->ForceCloseReason);
        json_pInputOrder["ForceCloseReason"] = buffer;



        json_pInputOrder["IsAutoSuspend"] = pInputOrder->IsAutoSuspend;




        gbk2utf8(
            pInputOrder->BusinessUnit,
            buffer,
            sizeof(pInputOrder->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pInputOrder["BusinessUnit"] = buffer;



        json_pInputOrder["RequestID"] = pInputOrder->RequestID;

        nRequestID = pInputOrder->RequestID;



        json_pInputOrder["UserForceClose"] = pInputOrder->UserForceClose;



        json_pInputOrder["IsSwapOrder"] = pInputOrder->IsSwapOrder;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pInputOrder;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnErrRtnOrderInsert";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnErrRtnOrderInsert():执行结束..." << std::endl;
}

///系统运行时期货端手工发起冲正银行转期货错误回报
void CTraderHandler::OnErrRtnRepealBankToFutureByFutureManual(
    CThostFtdcReqRepealField * pReqRepeal,
    CThostFtdcRspInfoField * pRspInfo
) {
    int nRequestID = 0;
    std::cout << "OnErrRtnRepealBankToFutureByFutureManual():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnErrRtnRepealBankToFutureByFutureManual";

    /// 返回数据结构体转化json格式
    Json::Value json_pReqRepeal;
    if ( pReqRepeal != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pReqRepeal["RepealTimeInterval"] = pReqRepeal->RepealTimeInterval;



        json_pReqRepeal["RepealedTimes"] = pReqRepeal->RepealedTimes;




        sprintf(buffer,"%c",pReqRepeal->BankRepealFlag);
        json_pReqRepeal["BankRepealFlag"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BrokerRepealFlag);
        json_pReqRepeal["BrokerRepealFlag"] = buffer;



        json_pReqRepeal["PlateRepealSerial"] = pReqRepeal->PlateRepealSerial;




        gbk2utf8(
            pReqRepeal->BankRepealSerial,
            buffer,
            sizeof(pReqRepeal->BankRepealSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankRepealSerial"] = buffer;



        json_pReqRepeal["FutureRepealSerial"] = pReqRepeal->FutureRepealSerial;




        gbk2utf8(
            pReqRepeal->TradeCode,
            buffer,
            sizeof(pReqRepeal->TradeCode) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradeCode"] = buffer;




        gbk2utf8(
            pReqRepeal->BankID,
            buffer,
            sizeof(pReqRepeal->BankID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankID"] = buffer;




        gbk2utf8(
            pReqRepeal->BankBranchID,
            buffer,
            sizeof(pReqRepeal->BankBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankBranchID"] = buffer;




        gbk2utf8(
            pReqRepeal->BrokerID,
            buffer,
            sizeof(pReqRepeal->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BrokerID"] = buffer;




        gbk2utf8(
            pReqRepeal->BrokerBranchID,
            buffer,
            sizeof(pReqRepeal->BrokerBranchID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BrokerBranchID"] = buffer;




        gbk2utf8(
            pReqRepeal->TradeDate,
            buffer,
            sizeof(pReqRepeal->TradeDate) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradeDate"] = buffer;




        gbk2utf8(
            pReqRepeal->TradeTime,
            buffer,
            sizeof(pReqRepeal->TradeTime) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradeTime"] = buffer;




        gbk2utf8(
            pReqRepeal->BankSerial,
            buffer,
            sizeof(pReqRepeal->BankSerial) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankSerial"] = buffer;




        gbk2utf8(
            pReqRepeal->TradingDay,
            buffer,
            sizeof(pReqRepeal->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["TradingDay"] = buffer;



        json_pReqRepeal["PlateSerial"] = pReqRepeal->PlateSerial;




        sprintf(buffer,"%c",pReqRepeal->LastFragment);
        json_pReqRepeal["LastFragment"] = buffer;



        json_pReqRepeal["SessionID"] = pReqRepeal->SessionID;




        gbk2utf8(
            pReqRepeal->CustomerName,
            buffer,
            sizeof(pReqRepeal->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->IdCardType);
        json_pReqRepeal["IdCardType"] = buffer;




        gbk2utf8(
            pReqRepeal->IdentifiedCardNo,
            buffer,
            sizeof(pReqRepeal->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->CustType);
        json_pReqRepeal["CustType"] = buffer;




        gbk2utf8(
            pReqRepeal->BankAccount,
            buffer,
            sizeof(pReqRepeal->BankAccount) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankAccount"] = buffer;




        gbk2utf8(
            pReqRepeal->BankPassWord,
            buffer,
            sizeof(pReqRepeal->BankPassWord) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankPassWord"] = buffer;




        gbk2utf8(
            pReqRepeal->AccountID,
            buffer,
            sizeof(pReqRepeal->AccountID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["AccountID"] = buffer;




        gbk2utf8(
            pReqRepeal->Password,
            buffer,
            sizeof(pReqRepeal->Password) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["Password"] = buffer;



        json_pReqRepeal["InstallID"] = pReqRepeal->InstallID;



        json_pReqRepeal["FutureSerial"] = pReqRepeal->FutureSerial;




        gbk2utf8(
            pReqRepeal->UserID,
            buffer,
            sizeof(pReqRepeal->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["UserID"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->VerifyCertNoFlag);
        json_pReqRepeal["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pReqRepeal->CurrencyID,
            buffer,
            sizeof(pReqRepeal->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["CurrencyID"] = buffer;



        json_pReqRepeal["TradeAmount"] = pReqRepeal->TradeAmount;



        json_pReqRepeal["FutureFetchAmount"] = pReqRepeal->FutureFetchAmount;




        sprintf(buffer,"%c",pReqRepeal->FeePayFlag);
        json_pReqRepeal["FeePayFlag"] = buffer;



        json_pReqRepeal["CustFee"] = pReqRepeal->CustFee;



        json_pReqRepeal["BrokerFee"] = pReqRepeal->BrokerFee;




        gbk2utf8(
            pReqRepeal->Message,
            buffer,
            sizeof(pReqRepeal->Message) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["Message"] = buffer;




        gbk2utf8(
            pReqRepeal->Digest,
            buffer,
            sizeof(pReqRepeal->Digest) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["Digest"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BankAccType);
        json_pReqRepeal["BankAccType"] = buffer;




        gbk2utf8(
            pReqRepeal->DeviceID,
            buffer,
            sizeof(pReqRepeal->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BankSecuAccType);
        json_pReqRepeal["BankSecuAccType"] = buffer;




        gbk2utf8(
            pReqRepeal->BrokerIDByBank,
            buffer,
            sizeof(pReqRepeal->BrokerIDByBank) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BrokerIDByBank"] = buffer;




        gbk2utf8(
            pReqRepeal->BankSecuAcc,
            buffer,
            sizeof(pReqRepeal->BankSecuAcc) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["BankSecuAcc"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->BankPwdFlag);
        json_pReqRepeal["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqRepeal->SecuPwdFlag);
        json_pReqRepeal["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pReqRepeal->OperNo,
            buffer,
            sizeof(pReqRepeal->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqRepeal["OperNo"] = buffer;



        json_pReqRepeal["RequestID"] = pReqRepeal->RequestID;

        nRequestID = pReqRepeal->RequestID;



        json_pReqRepeal["TID"] = pReqRepeal->TID;




        sprintf(buffer,"%c",pReqRepeal->TransferStatus);
        json_pReqRepeal["TransferStatus"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqRepeal;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnErrRtnRepealBankToFutureByFutureManual";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnErrRtnRepealBankToFutureByFutureManual():执行结束..." << std::endl;
}

///期货发起银行资金转期货错误回报
void CTraderHandler::OnErrRtnBankToFutureByFuture(
    CThostFtdcReqTransferField * pReqTransfer,
    CThostFtdcRspInfoField * pRspInfo
) {
    int nRequestID = 0;
    std::cout << "OnErrRtnBankToFutureByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnErrRtnBankToFutureByFuture";

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




        sprintf(buffer,"%c",pReqTransfer->LastFragment);
        json_pReqTransfer["LastFragment"] = buffer;



        json_pReqTransfer["SessionID"] = pReqTransfer->SessionID;




        gbk2utf8(
            pReqTransfer->CustomerName,
            buffer,
            sizeof(pReqTransfer->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->IdCardType);
        json_pReqTransfer["IdCardType"] = buffer;




        gbk2utf8(
            pReqTransfer->IdentifiedCardNo,
            buffer,
            sizeof(pReqTransfer->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->CustType);
        json_pReqTransfer["CustType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->VerifyCertNoFlag);
        json_pReqTransfer["VerifyCertNoFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->CurrencyID,
            buffer,
            sizeof(pReqTransfer->CurrencyID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["CurrencyID"] = buffer;



        json_pReqTransfer["TradeAmount"] = pReqTransfer->TradeAmount;



        json_pReqTransfer["FutureFetchAmount"] = pReqTransfer->FutureFetchAmount;




        sprintf(buffer,"%c",pReqTransfer->FeePayFlag);
        json_pReqTransfer["FeePayFlag"] = buffer;



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




        sprintf(buffer,"%c",pReqTransfer->BankAccType);
        json_pReqTransfer["BankAccType"] = buffer;




        gbk2utf8(
            pReqTransfer->DeviceID,
            buffer,
            sizeof(pReqTransfer->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->BankSecuAccType);
        json_pReqTransfer["BankSecuAccType"] = buffer;




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




        sprintf(buffer,"%c",pReqTransfer->BankPwdFlag);
        json_pReqTransfer["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqTransfer->SecuPwdFlag);
        json_pReqTransfer["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pReqTransfer->OperNo,
            buffer,
            sizeof(pReqTransfer->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqTransfer["OperNo"] = buffer;



        json_pReqTransfer["RequestID"] = pReqTransfer->RequestID;

        nRequestID = pReqTransfer->RequestID;



        json_pReqTransfer["TID"] = pReqTransfer->TID;




        sprintf(buffer,"%c",pReqTransfer->TransferStatus);
        json_pReqTransfer["TransferStatus"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqTransfer;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnErrRtnBankToFutureByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnErrRtnBankToFutureByFuture():执行结束..." << std::endl;
}

///期货发起查询银行余额错误回报
void CTraderHandler::OnErrRtnQueryBankBalanceByFuture(
    CThostFtdcReqQueryAccountField * pReqQueryAccount,
    CThostFtdcRspInfoField * pRspInfo
) {
    int nRequestID = 0;
    std::cout << "OnErrRtnQueryBankBalanceByFuture():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnErrRtnQueryBankBalanceByFuture";

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




        sprintf(buffer,"%c",pReqQueryAccount->LastFragment);
        json_pReqQueryAccount["LastFragment"] = buffer;



        json_pReqQueryAccount["SessionID"] = pReqQueryAccount->SessionID;




        gbk2utf8(
            pReqQueryAccount->CustomerName,
            buffer,
            sizeof(pReqQueryAccount->CustomerName) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["CustomerName"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->IdCardType);
        json_pReqQueryAccount["IdCardType"] = buffer;




        gbk2utf8(
            pReqQueryAccount->IdentifiedCardNo,
            buffer,
            sizeof(pReqQueryAccount->IdentifiedCardNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["IdentifiedCardNo"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->CustType);
        json_pReqQueryAccount["CustType"] = buffer;




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




        sprintf(buffer,"%c",pReqQueryAccount->VerifyCertNoFlag);
        json_pReqQueryAccount["VerifyCertNoFlag"] = buffer;




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




        sprintf(buffer,"%c",pReqQueryAccount->BankAccType);
        json_pReqQueryAccount["BankAccType"] = buffer;




        gbk2utf8(
            pReqQueryAccount->DeviceID,
            buffer,
            sizeof(pReqQueryAccount->DeviceID) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["DeviceID"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->BankSecuAccType);
        json_pReqQueryAccount["BankSecuAccType"] = buffer;




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




        sprintf(buffer,"%c",pReqQueryAccount->BankPwdFlag);
        json_pReqQueryAccount["BankPwdFlag"] = buffer;




        sprintf(buffer,"%c",pReqQueryAccount->SecuPwdFlag);
        json_pReqQueryAccount["SecuPwdFlag"] = buffer;




        gbk2utf8(
            pReqQueryAccount->OperNo,
            buffer,
            sizeof(pReqQueryAccount->OperNo) * 3 // 字符串转化变长的风险保障
        );
        json_pReqQueryAccount["OperNo"] = buffer;



        json_pReqQueryAccount["RequestID"] = pReqQueryAccount->RequestID;

        nRequestID = pReqQueryAccount->RequestID;



        json_pReqQueryAccount["TID"] = pReqQueryAccount->TID;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pReqQueryAccount;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnErrRtnQueryBankBalanceByFuture";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

    std::cout << "OnErrRtnQueryBankBalanceByFuture():执行结束..." << std::endl;
}

///报单操作错误回报
void CTraderHandler::OnErrRtnOrderAction(
    CThostFtdcOrderActionField * pOrderAction,
    CThostFtdcRspInfoField * pRspInfo
) {
    int nRequestID = 0;
    std::cout << "OnErrRtnOrderAction():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnErrRtnOrderAction";

    /// 返回数据结构体转化json格式
    Json::Value json_pOrderAction;
    if ( pOrderAction != NULL ) {
        // TODO : 这里需要将编码转化为utf-8



        gbk2utf8(
            pOrderAction->BrokerID,
            buffer,
            sizeof(pOrderAction->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["BrokerID"] = buffer;




        gbk2utf8(
            pOrderAction->InvestorID,
            buffer,
            sizeof(pOrderAction->InvestorID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["InvestorID"] = buffer;



        json_pOrderAction["OrderActionRef"] = pOrderAction->OrderActionRef;




        gbk2utf8(
            pOrderAction->OrderRef,
            buffer,
            sizeof(pOrderAction->OrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["OrderRef"] = buffer;



        json_pOrderAction["RequestID"] = pOrderAction->RequestID;

        nRequestID = pOrderAction->RequestID;



        json_pOrderAction["FrontID"] = pOrderAction->FrontID;



        json_pOrderAction["SessionID"] = pOrderAction->SessionID;




        gbk2utf8(
            pOrderAction->ExchangeID,
            buffer,
            sizeof(pOrderAction->ExchangeID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["ExchangeID"] = buffer;




        gbk2utf8(
            pOrderAction->OrderSysID,
            buffer,
            sizeof(pOrderAction->OrderSysID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["OrderSysID"] = buffer;




        sprintf(buffer,"%c",pOrderAction->ActionFlag);
        json_pOrderAction["ActionFlag"] = buffer;



        json_pOrderAction["LimitPrice"] = pOrderAction->LimitPrice;



        json_pOrderAction["VolumeChange"] = pOrderAction->VolumeChange;




        gbk2utf8(
            pOrderAction->ActionDate,
            buffer,
            sizeof(pOrderAction->ActionDate) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["ActionDate"] = buffer;




        gbk2utf8(
            pOrderAction->ActionTime,
            buffer,
            sizeof(pOrderAction->ActionTime) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["ActionTime"] = buffer;




        gbk2utf8(
            pOrderAction->TraderID,
            buffer,
            sizeof(pOrderAction->TraderID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["TraderID"] = buffer;



        json_pOrderAction["InstallID"] = pOrderAction->InstallID;




        gbk2utf8(
            pOrderAction->OrderLocalID,
            buffer,
            sizeof(pOrderAction->OrderLocalID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["OrderLocalID"] = buffer;




        gbk2utf8(
            pOrderAction->ActionLocalID,
            buffer,
            sizeof(pOrderAction->ActionLocalID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["ActionLocalID"] = buffer;




        gbk2utf8(
            pOrderAction->ParticipantID,
            buffer,
            sizeof(pOrderAction->ParticipantID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["ParticipantID"] = buffer;




        gbk2utf8(
            pOrderAction->ClientID,
            buffer,
            sizeof(pOrderAction->ClientID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["ClientID"] = buffer;




        gbk2utf8(
            pOrderAction->BusinessUnit,
            buffer,
            sizeof(pOrderAction->BusinessUnit) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["BusinessUnit"] = buffer;




        sprintf(buffer,"%c",pOrderAction->OrderActionStatus);
        json_pOrderAction["OrderActionStatus"] = buffer;




        gbk2utf8(
            pOrderAction->UserID,
            buffer,
            sizeof(pOrderAction->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["UserID"] = buffer;




        gbk2utf8(
            pOrderAction->StatusMsg,
            buffer,
            sizeof(pOrderAction->StatusMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["StatusMsg"] = buffer;




        gbk2utf8(
            pOrderAction->InstrumentID,
            buffer,
            sizeof(pOrderAction->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pOrderAction["InstrumentID"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pOrderAction;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnErrRtnOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);

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

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspError";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspInfo;
    if ( pRspInfo != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;



        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;


    }

    // 定义参数集合
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspInfo;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspError";
    message.respInfo = json_Response.toStyledString();
    message.isLast = "0";
    message.send(sender);


    std::cout << "OnRspError():执行结束..." << std::endl;
}
