#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>
#include <json/json.h>


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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInstrument;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInstrument";
    json_Parameters.append(json_pInstrument);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInstrument";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pSettlementInfo;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQrySettlementInfo";
    json_Parameters.append(json_pSettlementInfo);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQrySettlementInfo";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pParkedOrder;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspParkedOrderInsert";
    json_Parameters.append(json_pParkedOrder);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspParkedOrderInsert";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pExchange;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryExchange";
    json_Parameters.append(json_pExchange);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchange";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInputOrderAction;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspOrderAction";
    json_Parameters.append(json_pInputOrderAction);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInvestor;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInvestor";
    json_Parameters.append(json_pInvestor);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestor";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pRemoveParkedOrder;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspRemoveParkedOrder";
    json_Parameters.append(json_pRemoveParkedOrder);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspRemoveParkedOrder";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInvestorProductGroupMargin;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInvestorProductGroupMargin";
    json_Parameters.append(json_pInvestorProductGroupMargin);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorProductGroupMargin";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pTransferBank;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryTransferBank";
    json_Parameters.append(json_pTransferBank);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTransferBank";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pBrokerTradingAlgos;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryBrokerTradingAlgos";
    json_Parameters.append(json_pBrokerTradingAlgos);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryBrokerTradingAlgos";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pProduct;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryProduct";
    json_Parameters.append(json_pProduct);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryProduct";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInstrumentMarginRate;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInstrumentMarginRate";
    json_Parameters.append(json_pInstrumentMarginRate);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInstrumentMarginRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pCFMMCTradingAccountKey;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryCFMMCTradingAccountKey";
    json_Parameters.append(json_pCFMMCTradingAccountKey);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryCFMMCTradingAccountKey";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pRspUserLogin;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspUserLogin";
    json_Parameters.append(json_pRspUserLogin);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserLogin";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pReqTransfer;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspFromFutureToBankByFuture";
    json_Parameters.append(json_pReqTransfer);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspFromFutureToBankByFuture";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pQueryCFMMCTradingAccountToken;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQueryCFMMCTradingAccountToken";
    json_Parameters.append(json_pQueryCFMMCTradingAccountToken);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQueryCFMMCTradingAccountToken";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pContractBank;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryContractBank";
    json_Parameters.append(json_pContractBank);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryContractBank";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInputOrder;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspOrderInsert";
    json_Parameters.append(json_pInputOrder);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspOrderInsert";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pEWarrantOffset;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryEWarrantOffset";
    json_Parameters.append(json_pEWarrantOffset);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryEWarrantOffset";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pUserPasswordUpdate;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspUserPasswordUpdate";
    json_Parameters.append(json_pUserPasswordUpdate);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserPasswordUpdate";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pExchangeMarginRateAdjust;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryExchangeMarginRateAdjust";
    json_Parameters.append(json_pExchangeMarginRateAdjust);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchangeMarginRateAdjust";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pReqTransfer;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspFromBankToFutureByFuture";
    json_Parameters.append(json_pReqTransfer);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspFromBankToFutureByFuture";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInvestorPositionCombineDetail;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInvestorPositionCombineDetail";
    json_Parameters.append(json_pInvestorPositionCombineDetail);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorPositionCombineDetail";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pSettlementInfoConfirm;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspSettlementInfoConfirm";
    json_Parameters.append(json_pSettlementInfoConfirm);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspSettlementInfoConfirm";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pAccountregister;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryAccountregister";
    json_Parameters.append(json_pAccountregister);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryAccountregister";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pSecAgentACIDMap;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQrySecAgentACIDMap";
    json_Parameters.append(json_pSecAgentACIDMap);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQrySecAgentACIDMap";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pTradingCode;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryTradingCode";
    json_Parameters.append(json_pTradingCode);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTradingCode";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pSettlementInfoConfirm;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQrySettlementInfoConfirm";
    json_Parameters.append(json_pSettlementInfoConfirm);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQrySettlementInfoConfirm";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pTransferSerial;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryTransferSerial";
    json_Parameters.append(json_pTransferSerial);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTransferSerial";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInvestorPosition;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInvestorPosition";
    json_Parameters.append(json_pInvestorPosition);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorPosition";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pUserLogout;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspUserLogout";
    json_Parameters.append(json_pUserLogout);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserLogout";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInvestorPositionDetail;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInvestorPositionDetail";
    json_Parameters.append(json_pInvestorPositionDetail);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInvestorPositionDetail";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pParkedOrderAction;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryParkedOrderAction";
    json_Parameters.append(json_pParkedOrderAction);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryParkedOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pBrokerTradingParams;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryBrokerTradingParams";
    json_Parameters.append(json_pBrokerTradingParams);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryBrokerTradingParams";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pExchangeMarginRate;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryExchangeMarginRate";
    json_Parameters.append(json_pExchangeMarginRate);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchangeMarginRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pParkedOrder;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryParkedOrder";
    json_Parameters.append(json_pParkedOrder);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryParkedOrder";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pReqQueryAccount;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQueryBankAccountMoneyByFuture";
    json_Parameters.append(json_pReqQueryAccount);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQueryBankAccountMoneyByFuture";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pRspAuthenticateField;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspAuthenticate";
    json_Parameters.append(json_pRspAuthenticateField);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspAuthenticate";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pQueryMaxOrderVolume;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQueryMaxOrderVolume";
    json_Parameters.append(json_pQueryMaxOrderVolume);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQueryMaxOrderVolume";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pExchangeRate;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryExchangeRate";
    json_Parameters.append(json_pExchangeRate);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryExchangeRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pTradingNotice;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryTradingNotice";
    json_Parameters.append(json_pTradingNotice);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTradingNotice";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pParkedOrderAction;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspParkedOrderAction";
    json_Parameters.append(json_pParkedOrderAction);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspParkedOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pNotice;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryNotice";
    json_Parameters.append(json_pNotice);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryNotice";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pTradingAccount;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryTradingAccount";
    json_Parameters.append(json_pTradingAccount);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTradingAccount";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pTradingAccountPasswordUpdate;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspTradingAccountPasswordUpdate";
    json_Parameters.append(json_pTradingAccountPasswordUpdate);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspTradingAccountPasswordUpdate";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pOrder;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryOrder";
    json_Parameters.append(json_pOrder);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryOrder";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pDepthMarketData;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryDepthMarketData";
    json_Parameters.append(json_pDepthMarketData);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryDepthMarketData";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pInstrumentCommissionRate;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryInstrumentCommissionRate";
    json_Parameters.append(json_pInstrumentCommissionRate);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryInstrumentCommissionRate";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pRemoveParkedOrderAction;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspRemoveParkedOrderAction";
    json_Parameters.append(json_pRemoveParkedOrderAction);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspRemoveParkedOrderAction";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
    zmq::socket_t & sendder = *pSender;

    // 生成返回的json格式
    Json::Value json_Response;
    Json::Value json_Parameters;
    Json::Value json_pTrade;
    Json::Value json_pRspInfo;
    Json::Value json_nRequestID;
    Json::Value json_bIsLast;
    json_Response["apiName"] = "OnRspQryTrade";
    json_Parameters.append(json_pTrade);
    json_Parameters.append(json_pRspInfo);
    json_Parameters.append(json_nRequestID);
    json_Parameters.append(json_bIsLast);
    json_Response["parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspQryTrade";
    message.respInfo = json_Response.toStyledString();
    message.send(sendder);
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
