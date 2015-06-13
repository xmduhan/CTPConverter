
#include <CTraderWrapper.h>
#include <json/json.h>
#include <comhelper.h>



/// 构造函数
CTraderWrapper::CTraderWrapper(Configure * pConfigure) {

    // 读取配置数据信息
    this->pConfigure = pConfigure;

    // 创建CTP API工作对象
    pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();

    // 创建SPI工作对象并让其和API关联
    pTraderHandler = new CTraderHandler(pConfigure);
    pTraderApi->RegisterSpi(pTraderHandler);

    // 初始化RequestID序列
    //RequestID = 0;

    // 初始化上次出错代码和出错信息
    lastErrorID = 0;
    lastErrorMsg = "";

}

// 将所有api函数映射到名称
void CTraderWrapper::initApiMap() {

    //ReqQryTradingAccount
    apiMap["ReqQryTradingAccount"] = &CTraderWrapper::ReqQryTradingAccount;

    //ReqQryCFMMCTradingAccountKey
    apiMap["ReqQryCFMMCTradingAccountKey"] = &CTraderWrapper::ReqQryCFMMCTradingAccountKey;

    //ReqUserPasswordUpdate
    apiMap["ReqUserPasswordUpdate"] = &CTraderWrapper::ReqUserPasswordUpdate;

    //ReqParkedOrderAction
    apiMap["ReqParkedOrderAction"] = &CTraderWrapper::ReqParkedOrderAction;

    //ReqQryTradingNotice
    apiMap["ReqQryTradingNotice"] = &CTraderWrapper::ReqQryTradingNotice;

    //ReqQryTrade
    apiMap["ReqQryTrade"] = &CTraderWrapper::ReqQryTrade;

    //ReqQueryMaxOrderVolume
    apiMap["ReqQueryMaxOrderVolume"] = &CTraderWrapper::ReqQueryMaxOrderVolume;

    //ReqSettlementInfoConfirm
    apiMap["ReqSettlementInfoConfirm"] = &CTraderWrapper::ReqSettlementInfoConfirm;

    //ReqQryInvestorPosition
    apiMap["ReqQryInvestorPosition"] = &CTraderWrapper::ReqQryInvestorPosition;

    //ReqQryBrokerTradingAlgos
    apiMap["ReqQryBrokerTradingAlgos"] = &CTraderWrapper::ReqQryBrokerTradingAlgos;

    //ReqQryOrder
    apiMap["ReqQryOrder"] = &CTraderWrapper::ReqQryOrder;

    //ReqQryExchange
    apiMap["ReqQryExchange"] = &CTraderWrapper::ReqQryExchange;

    //ReqUserLogin
    apiMap["ReqUserLogin"] = &CTraderWrapper::ReqUserLogin;

    //ReqFromFutureToBankByFuture
    apiMap["ReqFromFutureToBankByFuture"] = &CTraderWrapper::ReqFromFutureToBankByFuture;

    //ReqFromBankToFutureByFuture
    apiMap["ReqFromBankToFutureByFuture"] = &CTraderWrapper::ReqFromBankToFutureByFuture;

    //ReqQrySettlementInfoConfirm
    apiMap["ReqQrySettlementInfoConfirm"] = &CTraderWrapper::ReqQrySettlementInfoConfirm;

    //ReqQryBrokerTradingParams
    apiMap["ReqQryBrokerTradingParams"] = &CTraderWrapper::ReqQryBrokerTradingParams;

    //ReqQueryCFMMCTradingAccountToken
    apiMap["ReqQueryCFMMCTradingAccountToken"] = &CTraderWrapper::ReqQueryCFMMCTradingAccountToken;

    //ReqQryNotice
    apiMap["ReqQryNotice"] = &CTraderWrapper::ReqQryNotice;

    //ReqQryExchangeRate
    apiMap["ReqQryExchangeRate"] = &CTraderWrapper::ReqQryExchangeRate;

    //ReqParkedOrderInsert
    apiMap["ReqParkedOrderInsert"] = &CTraderWrapper::ReqParkedOrderInsert;

    //ReqQryContractBank
    apiMap["ReqQryContractBank"] = &CTraderWrapper::ReqQryContractBank;

    //ReqQryInvestorPositionCombineDetail
    apiMap["ReqQryInvestorPositionCombineDetail"] = &CTraderWrapper::ReqQryInvestorPositionCombineDetail;

    //ReqQryExchangeMarginRate
    apiMap["ReqQryExchangeMarginRate"] = &CTraderWrapper::ReqQryExchangeMarginRate;

    //ReqQrySecAgentACIDMap
    apiMap["ReqQrySecAgentACIDMap"] = &CTraderWrapper::ReqQrySecAgentACIDMap;

    //ReqQryTransferSerial
    apiMap["ReqQryTransferSerial"] = &CTraderWrapper::ReqQryTransferSerial;

    //ReqQueryBankAccountMoneyByFuture
    apiMap["ReqQueryBankAccountMoneyByFuture"] = &CTraderWrapper::ReqQueryBankAccountMoneyByFuture;

    //ReqQryParkedOrderAction
    apiMap["ReqQryParkedOrderAction"] = &CTraderWrapper::ReqQryParkedOrderAction;

    //ReqAuthenticate
    apiMap["ReqAuthenticate"] = &CTraderWrapper::ReqAuthenticate;

    //ReqOrderInsert
    apiMap["ReqOrderInsert"] = &CTraderWrapper::ReqOrderInsert;

    //ReqQrySettlementInfo
    apiMap["ReqQrySettlementInfo"] = &CTraderWrapper::ReqQrySettlementInfo;

    //ReqUserLogout
    apiMap["ReqUserLogout"] = &CTraderWrapper::ReqUserLogout;

    //ReqQryInstrument
    apiMap["ReqQryInstrument"] = &CTraderWrapper::ReqQryInstrument;

    //ReqOrderAction
    apiMap["ReqOrderAction"] = &CTraderWrapper::ReqOrderAction;

    //ReqQryInstrumentCommissionRate
    apiMap["ReqQryInstrumentCommissionRate"] = &CTraderWrapper::ReqQryInstrumentCommissionRate;

    //ReqQryInstrumentMarginRate
    apiMap["ReqQryInstrumentMarginRate"] = &CTraderWrapper::ReqQryInstrumentMarginRate;

    //ReqQryInvestor
    apiMap["ReqQryInvestor"] = &CTraderWrapper::ReqQryInvestor;

    //ReqQryParkedOrder
    apiMap["ReqQryParkedOrder"] = &CTraderWrapper::ReqQryParkedOrder;

    //ReqQryInvestorProductGroupMargin
    apiMap["ReqQryInvestorProductGroupMargin"] = &CTraderWrapper::ReqQryInvestorProductGroupMargin;

    //ReqQryDepthMarketData
    apiMap["ReqQryDepthMarketData"] = &CTraderWrapper::ReqQryDepthMarketData;

    //ReqQryTransferBank
    apiMap["ReqQryTransferBank"] = &CTraderWrapper::ReqQryTransferBank;

    //ReqRemoveParkedOrderAction
    apiMap["ReqRemoveParkedOrderAction"] = &CTraderWrapper::ReqRemoveParkedOrderAction;

    //ReqQryProduct
    apiMap["ReqQryProduct"] = &CTraderWrapper::ReqQryProduct;

    //ReqQryTradingCode
    apiMap["ReqQryTradingCode"] = &CTraderWrapper::ReqQryTradingCode;

    //ReqTradingAccountPasswordUpdate
    apiMap["ReqTradingAccountPasswordUpdate"] = &CTraderWrapper::ReqTradingAccountPasswordUpdate;

    //ReqQryAccountregister
    apiMap["ReqQryAccountregister"] = &CTraderWrapper::ReqQryAccountregister;

    //ReqQryExchangeMarginRateAdjust
    apiMap["ReqQryExchangeMarginRateAdjust"] = &CTraderWrapper::ReqQryExchangeMarginRateAdjust;

    //ReqQryEWarrantOffset
    apiMap["ReqQryEWarrantOffset"] = &CTraderWrapper::ReqQryEWarrantOffset;

    //ReqQryInvestorPositionDetail
    apiMap["ReqQryInvestorPositionDetail"] = &CTraderWrapper::ReqQryInvestorPositionDetail;

    //ReqRemoveParkedOrder
    apiMap["ReqRemoveParkedOrder"] = &CTraderWrapper::ReqRemoveParkedOrder;

}

/// 启动CTP连接
void CTraderWrapper::init() {

    std::cout << "CTraderWrapper::init():开始执行..." << std::endl;
    // 初始化api名称对照表
    initApiMap();

    // 创建zmq通讯环境
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_PULL);
    PushbackMessage message;

    //设置服务信息推送信息
    // 订阅相关信息推送
    //// THOST_TERT_RESTART:从本交易日开始重传
    //// THOST_TERT_RESUME:从上次收到的续传
    //// THOST_TERT_QUICK:只传送登录后私有流的内容
    pTraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);
    // 订阅公共流
    //// THOST_TERT_RESTART:从本交易日开始重传
    //// THOST_TERT_RESUME:从上次收到的续传
    //// THOST_TERT_QUICK:只传送登录后公共流的内容
    pTraderApi->SubscribePublicTopic(THOST_TERT_QUICK);

    /// 设置服务器地址
    pTraderApi->RegisterFront(pConfigure->frontAddress);

    // 连接spi的Pushback管道
    std::cout << "CTraderWrapper::init():Pushback管道地址为:" << pConfigure->pushbackPipe << std::endl;
    receiver.connect(pConfigure->pushbackPipe);

    // 连接交易系统
    std::cout << "CTraderWrapper::init():尝试连接服务器..." << std::endl;
    pTraderApi->Init();

    // 等待服务器发出OnFrontConnected事件
    std::cout << "CTraderWrapper::init():等待服务器响应消息..." << std::endl;
    message.recv(receiver);
    std::cout << "CTraderWrapper::init():已收到服务器响应消息..." << std::endl;

    // 确认收到的返回信息是由OnFrontConnected发出
    assert(message.requestID.compare("0") == 0);
    assert(message.apiName.compare("OnFrontConnected") == 0);
    assert(message.respInfo.compare("") == 0);

    // 发出登陆请求
    std::cout << "CTraderWrapper::init():发出登录请求..." << std::endl;
    CThostFtdcReqUserLoginField userLoginField;
    strcpy(userLoginField.BrokerID,pConfigure->brokerID);
    strcpy(userLoginField.UserID,pConfigure->userID);
    strcpy(userLoginField.Password,pConfigure->password);
    int requestID = 0;
    pTraderApi->ReqUserLogin(&userLoginField,requestID);

    // 等待登录成功返回信息
    std::cout << "CTraderWrapper::init():等待登录结果..." << std::endl;
    message.recv(receiver);
    std::cout << "CTraderWrapper::init():已收到登录返回信息..." << std::endl;

    assert(message.requestID.compare("0") == 0);
    assert(message.apiName.compare("OnRspUserLogin") == 0);
    //assert(message.respInfo.compare("") == 0);
    //std::cout << "message.respInfo=" << message.respInfo << std::endl;
    // 检查是否登录成功,如果不成功将终止程序
    Json::Reader jsonReader;
    Json::Value jsonData;
    if (!jsonReader.parse(message.respInfo,jsonData)) {
        throw std::exception();
    }
    int ErrorID = jsonData["Parameters"]["Data"]["RspInfo"]["ErrorID"].asInt();
    assert(ErrorID == 0);

    std::cout << "CTraderWrapper::init():登录成功..." << std::endl;

    std::cout << "CTraderWrapper::init():执行完毕..." << std::endl;
}


/// 获取下一个RequestID序列
//int CTraderWrapper::getNextRequestID(){
//	return 	++this->RequestID;
//}

/// 获取当前RequestID序列
//int CTraderWrapper::getCurrentRequestID(){
//	return 	this->RequestID;
//}

/// 获取上次出错代码
int CTraderWrapper::getLastErrorID() {
    return lastErrorID;
}

/// 获取上次错误信息
std::string CTraderWrapper::getLastErrorMsg() {
    return lastErrorMsg;
}



///请求查询资金账户
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryTradingAccount(std::string jsonString,int requestID)
{
    printf("ReqQryTradingAccount():被执行...\n");


    CThostFtdcQryTradingAccountField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingAccount(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询保证金监管系统经纪公司资金账户密钥
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryCFMMCTradingAccountKey(std::string jsonString,int requestID)
{
    printf("ReqQryCFMMCTradingAccountKey():被执行...\n");


    CThostFtdcQryCFMMCTradingAccountKeyField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryCFMMCTradingAccountKey(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///用户口令更新请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqUserPasswordUpdate(std::string jsonString,int requestID)
{
    printf("ReqUserPasswordUpdate():被执行...\n");


    CThostFtdcUserPasswordUpdateField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///原来的口令 char OldPassword[41];
        if (!Data["OldPassword"].empty()) {
            data.OldPassword[sizeof(data.OldPassword)-1] = 0;
            strncpy(data.OldPassword,Data["OldPassword"].asCString(),sizeof(data.OldPassword)-1);
        } else {
            strcpy(data.OldPassword,"");
        }

        ///新的口令 char NewPassword[41];
        if (!Data["NewPassword"].empty()) {
            data.NewPassword[sizeof(data.NewPassword)-1] = 0;
            strncpy(data.NewPassword,Data["NewPassword"].asCString(),sizeof(data.NewPassword)-1);
        } else {
            strcpy(data.NewPassword,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserPasswordUpdate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///预埋撤单录入请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqParkedOrderAction(std::string jsonString,int requestID)
{
    printf("ReqParkedOrderAction():被执行...\n");


    CThostFtdcParkedOrderActionField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///报单操作引用 int OrderActionRef
        if (!Data["OrderActionRef"].empty()) {
            data.OrderActionRef = Data["OrderActionRef"].asInt();
        } else {
            data.OrderActionRef = 0;
        }

        ///报单引用 char OrderRef[13];
        if (!Data["OrderRef"].empty()) {
            data.OrderRef[sizeof(data.OrderRef)-1] = 0;
            strncpy(data.OrderRef,Data["OrderRef"].asCString(),sizeof(data.OrderRef)-1);
        } else {
            strcpy(data.OrderRef,"");
        }

        ///请求编号 int RequestID
        if (!Data["RequestID"].empty()) {
            data.RequestID = Data["RequestID"].asInt();
        } else {
            data.RequestID = 0;
        }

        ///前置编号 int FrontID
        if (!Data["FrontID"].empty()) {
            data.FrontID = Data["FrontID"].asInt();
        } else {
            data.FrontID = 0;
        }

        ///会话编号 int SessionID
        if (!Data["SessionID"].empty()) {
            data.SessionID = Data["SessionID"].asInt();
        } else {
            data.SessionID = 0;
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///报单编号 char OrderSysID[21];
        if (!Data["OrderSysID"].empty()) {
            data.OrderSysID[sizeof(data.OrderSysID)-1] = 0;
            strncpy(data.OrderSysID,Data["OrderSysID"].asCString(),sizeof(data.OrderSysID)-1);
        } else {
            strcpy(data.OrderSysID,"");
        }

        ///操作标志 char ActionFlag
        if ( !Data["ActionFlag"].empty()) {
            data.ActionFlag = Data["ActionFlag"].asString()[0];
        } else {
            data.ActionFlag = '0';
        }

        ///价格 double LimitPrice
        if (!Data["LimitPrice"].empty()) {
            data.LimitPrice = Data["LimitPrice"].asDouble();
        } else {
            data.LimitPrice = 0;
        }

        ///数量变化 int VolumeChange
        if (!Data["VolumeChange"].empty()) {
            data.VolumeChange = Data["VolumeChange"].asInt();
        } else {
            data.VolumeChange = 0;
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///预埋撤单单编号 char ParkedOrderActionID[13];
        if (!Data["ParkedOrderActionID"].empty()) {
            data.ParkedOrderActionID[sizeof(data.ParkedOrderActionID)-1] = 0;
            strncpy(data.ParkedOrderActionID,Data["ParkedOrderActionID"].asCString(),sizeof(data.ParkedOrderActionID)-1);
        } else {
            strcpy(data.ParkedOrderActionID,"");
        }

        ///用户类型 char UserType
        if ( !Data["UserType"].empty()) {
            data.UserType = Data["UserType"].asString()[0];
        } else {
            data.UserType = '0';
        }

        ///预埋撤单状态 char Status
        if ( !Data["Status"].empty()) {
            data.Status = Data["Status"].asString()[0];
        } else {
            data.Status = '0';
        }

        ///错误代码 int ErrorID
        if (!Data["ErrorID"].empty()) {
            data.ErrorID = Data["ErrorID"].asInt();
        } else {
            data.ErrorID = 0;
        }

        ///错误信息 char ErrorMsg[81];
        if (!Data["ErrorMsg"].empty()) {
            data.ErrorMsg[sizeof(data.ErrorMsg)-1] = 0;
            strncpy(data.ErrorMsg,Data["ErrorMsg"].asCString(),sizeof(data.ErrorMsg)-1);
        } else {
            strcpy(data.ErrorMsg,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqParkedOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询交易通知
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryTradingNotice(std::string jsonString,int requestID)
{
    printf("ReqQryTradingNotice():被执行...\n");


    CThostFtdcQryTradingNoticeField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingNotice(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询成交
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryTrade(std::string jsonString,int requestID)
{
    printf("ReqQryTrade():被执行...\n");


    CThostFtdcQryTradeField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///成交编号 char TradeID[21];
        if (!Data["TradeID"].empty()) {
            data.TradeID[sizeof(data.TradeID)-1] = 0;
            strncpy(data.TradeID,Data["TradeID"].asCString(),sizeof(data.TradeID)-1);
        } else {
            strcpy(data.TradeID,"");
        }

        ///开始时间 char TradeTimeStart[9];
        if (!Data["TradeTimeStart"].empty()) {
            data.TradeTimeStart[sizeof(data.TradeTimeStart)-1] = 0;
            strncpy(data.TradeTimeStart,Data["TradeTimeStart"].asCString(),sizeof(data.TradeTimeStart)-1);
        } else {
            strcpy(data.TradeTimeStart,"");
        }

        ///结束时间 char TradeTimeEnd[9];
        if (!Data["TradeTimeEnd"].empty()) {
            data.TradeTimeEnd[sizeof(data.TradeTimeEnd)-1] = 0;
            strncpy(data.TradeTimeEnd,Data["TradeTimeEnd"].asCString(),sizeof(data.TradeTimeEnd)-1);
        } else {
            strcpy(data.TradeTimeEnd,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTrade(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///查询最大报单数量请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQueryMaxOrderVolume(std::string jsonString,int requestID)
{
    printf("ReqQueryMaxOrderVolume():被执行...\n");


    CThostFtdcQueryMaxOrderVolumeField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///买卖方向 char Direction
        if ( !Data["Direction"].empty()) {
            data.Direction = Data["Direction"].asString()[0];
        } else {
            data.Direction = '0';
        }

        ///开平标志 char OffsetFlag
        if ( !Data["OffsetFlag"].empty()) {
            data.OffsetFlag = Data["OffsetFlag"].asString()[0];
        } else {
            data.OffsetFlag = '0';
        }

        ///投机套保标志 char HedgeFlag
        if ( !Data["HedgeFlag"].empty()) {
            data.HedgeFlag = Data["HedgeFlag"].asString()[0];
        } else {
            data.HedgeFlag = '0';
        }

        ///最大允许报单数量 int MaxVolume
        if (!Data["MaxVolume"].empty()) {
            data.MaxVolume = Data["MaxVolume"].asInt();
        } else {
            data.MaxVolume = 0;
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryMaxOrderVolume(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///投资者结算结果确认
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqSettlementInfoConfirm(std::string jsonString,int requestID)
{
    printf("ReqSettlementInfoConfirm():被执行...\n");


    CThostFtdcSettlementInfoConfirmField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///确认日期 char ConfirmDate[9];
        if (!Data["ConfirmDate"].empty()) {
            data.ConfirmDate[sizeof(data.ConfirmDate)-1] = 0;
            strncpy(data.ConfirmDate,Data["ConfirmDate"].asCString(),sizeof(data.ConfirmDate)-1);
        } else {
            strcpy(data.ConfirmDate,"");
        }

        ///确认时间 char ConfirmTime[9];
        if (!Data["ConfirmTime"].empty()) {
            data.ConfirmTime[sizeof(data.ConfirmTime)-1] = 0;
            strncpy(data.ConfirmTime,Data["ConfirmTime"].asCString(),sizeof(data.ConfirmTime)-1);
        } else {
            strcpy(data.ConfirmTime,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqSettlementInfoConfirm(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询投资者持仓
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInvestorPosition(std::string jsonString,int requestID)
{
    printf("ReqQryInvestorPosition():被执行...\n");


    CThostFtdcQryInvestorPositionField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPosition(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询经纪公司交易算法
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryBrokerTradingAlgos(std::string jsonString,int requestID)
{
    printf("ReqQryBrokerTradingAlgos():被执行...\n");


    CThostFtdcQryBrokerTradingAlgosField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryBrokerTradingAlgos(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询报单
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryOrder(std::string jsonString,int requestID)
{
    printf("ReqQryOrder():被执行...\n");


    CThostFtdcQryOrderField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///报单编号 char OrderSysID[21];
        if (!Data["OrderSysID"].empty()) {
            data.OrderSysID[sizeof(data.OrderSysID)-1] = 0;
            strncpy(data.OrderSysID,Data["OrderSysID"].asCString(),sizeof(data.OrderSysID)-1);
        } else {
            strcpy(data.OrderSysID,"");
        }

        ///开始时间 char InsertTimeStart[9];
        if (!Data["InsertTimeStart"].empty()) {
            data.InsertTimeStart[sizeof(data.InsertTimeStart)-1] = 0;
            strncpy(data.InsertTimeStart,Data["InsertTimeStart"].asCString(),sizeof(data.InsertTimeStart)-1);
        } else {
            strcpy(data.InsertTimeStart,"");
        }

        ///结束时间 char InsertTimeEnd[9];
        if (!Data["InsertTimeEnd"].empty()) {
            data.InsertTimeEnd[sizeof(data.InsertTimeEnd)-1] = 0;
            strncpy(data.InsertTimeEnd,Data["InsertTimeEnd"].asCString(),sizeof(data.InsertTimeEnd)-1);
        } else {
            strcpy(data.InsertTimeEnd,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryOrder(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询交易所
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryExchange(std::string jsonString,int requestID)
{
    printf("ReqQryExchange():被执行...\n");


    CThostFtdcQryExchangeField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchange(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///用户登录请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqUserLogin(std::string jsonString,int requestID)
{
    printf("ReqUserLogin():被执行...\n");


    CThostFtdcReqUserLoginField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///交易日 char TradingDay[9];
        if (!Data["TradingDay"].empty()) {
            data.TradingDay[sizeof(data.TradingDay)-1] = 0;
            strncpy(data.TradingDay,Data["TradingDay"].asCString(),sizeof(data.TradingDay)-1);
        } else {
            strcpy(data.TradingDay,"");
        }

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///密码 char Password[41];
        if (!Data["Password"].empty()) {
            data.Password[sizeof(data.Password)-1] = 0;
            strncpy(data.Password,Data["Password"].asCString(),sizeof(data.Password)-1);
        } else {
            strcpy(data.Password,"");
        }

        ///用户端产品信息 char UserProductInfo[11];
        if (!Data["UserProductInfo"].empty()) {
            data.UserProductInfo[sizeof(data.UserProductInfo)-1] = 0;
            strncpy(data.UserProductInfo,Data["UserProductInfo"].asCString(),sizeof(data.UserProductInfo)-1);
        } else {
            strcpy(data.UserProductInfo,"");
        }

        ///接口端产品信息 char InterfaceProductInfo[11];
        if (!Data["InterfaceProductInfo"].empty()) {
            data.InterfaceProductInfo[sizeof(data.InterfaceProductInfo)-1] = 0;
            strncpy(data.InterfaceProductInfo,Data["InterfaceProductInfo"].asCString(),sizeof(data.InterfaceProductInfo)-1);
        } else {
            strcpy(data.InterfaceProductInfo,"");
        }

        ///协议信息 char ProtocolInfo[11];
        if (!Data["ProtocolInfo"].empty()) {
            data.ProtocolInfo[sizeof(data.ProtocolInfo)-1] = 0;
            strncpy(data.ProtocolInfo,Data["ProtocolInfo"].asCString(),sizeof(data.ProtocolInfo)-1);
        } else {
            strcpy(data.ProtocolInfo,"");
        }

        ///Mac地址 char MacAddress[21];
        if (!Data["MacAddress"].empty()) {
            data.MacAddress[sizeof(data.MacAddress)-1] = 0;
            strncpy(data.MacAddress,Data["MacAddress"].asCString(),sizeof(data.MacAddress)-1);
        } else {
            strcpy(data.MacAddress,"");
        }

        ///动态密码 char OneTimePassword[41];
        if (!Data["OneTimePassword"].empty()) {
            data.OneTimePassword[sizeof(data.OneTimePassword)-1] = 0;
            strncpy(data.OneTimePassword,Data["OneTimePassword"].asCString(),sizeof(data.OneTimePassword)-1);
        } else {
            strcpy(data.OneTimePassword,"");
        }

        ///终端IP地址 char ClientIPAddress[16];
        if (!Data["ClientIPAddress"].empty()) {
            data.ClientIPAddress[sizeof(data.ClientIPAddress)-1] = 0;
            strncpy(data.ClientIPAddress,Data["ClientIPAddress"].asCString(),sizeof(data.ClientIPAddress)-1);
        } else {
            strcpy(data.ClientIPAddress,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserLogin(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///期货发起期货资金转银行请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqFromFutureToBankByFuture(std::string jsonString,int requestID)
{
    printf("ReqFromFutureToBankByFuture():被执行...\n");


    CThostFtdcReqTransferField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///业务功能码 char TradeCode[7];
        if (!Data["TradeCode"].empty()) {
            data.TradeCode[sizeof(data.TradeCode)-1] = 0;
            strncpy(data.TradeCode,Data["TradeCode"].asCString(),sizeof(data.TradeCode)-1);
        } else {
            strcpy(data.TradeCode,"");
        }

        ///银行代码 char BankID[4];
        if (!Data["BankID"].empty()) {
            data.BankID[sizeof(data.BankID)-1] = 0;
            strncpy(data.BankID,Data["BankID"].asCString(),sizeof(data.BankID)-1);
        } else {
            strcpy(data.BankID,"");
        }

        ///银行分支机构代码 char BankBranchID[5];
        if (!Data["BankBranchID"].empty()) {
            data.BankBranchID[sizeof(data.BankBranchID)-1] = 0;
            strncpy(data.BankBranchID,Data["BankBranchID"].asCString(),sizeof(data.BankBranchID)-1);
        } else {
            strcpy(data.BankBranchID,"");
        }

        ///期商代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///期商分支机构代码 char BrokerBranchID[31];
        if (!Data["BrokerBranchID"].empty()) {
            data.BrokerBranchID[sizeof(data.BrokerBranchID)-1] = 0;
            strncpy(data.BrokerBranchID,Data["BrokerBranchID"].asCString(),sizeof(data.BrokerBranchID)-1);
        } else {
            strcpy(data.BrokerBranchID,"");
        }

        ///交易日期 char TradeDate[9];
        if (!Data["TradeDate"].empty()) {
            data.TradeDate[sizeof(data.TradeDate)-1] = 0;
            strncpy(data.TradeDate,Data["TradeDate"].asCString(),sizeof(data.TradeDate)-1);
        } else {
            strcpy(data.TradeDate,"");
        }

        ///交易时间 char TradeTime[9];
        if (!Data["TradeTime"].empty()) {
            data.TradeTime[sizeof(data.TradeTime)-1] = 0;
            strncpy(data.TradeTime,Data["TradeTime"].asCString(),sizeof(data.TradeTime)-1);
        } else {
            strcpy(data.TradeTime,"");
        }

        ///银行流水号 char BankSerial[13];
        if (!Data["BankSerial"].empty()) {
            data.BankSerial[sizeof(data.BankSerial)-1] = 0;
            strncpy(data.BankSerial,Data["BankSerial"].asCString(),sizeof(data.BankSerial)-1);
        } else {
            strcpy(data.BankSerial,"");
        }

        ///交易系统日期 char TradingDay[9];
        if (!Data["TradingDay"].empty()) {
            data.TradingDay[sizeof(data.TradingDay)-1] = 0;
            strncpy(data.TradingDay,Data["TradingDay"].asCString(),sizeof(data.TradingDay)-1);
        } else {
            strcpy(data.TradingDay,"");
        }

        ///银期平台消息流水号 int PlateSerial
        if (!Data["PlateSerial"].empty()) {
            data.PlateSerial = Data["PlateSerial"].asInt();
        } else {
            data.PlateSerial = 0;
        }

        ///最后分片标志 char LastFragment
        if ( !Data["LastFragment"].empty()) {
            data.LastFragment = Data["LastFragment"].asString()[0];
        } else {
            data.LastFragment = '0';
        }

        ///会话号 int SessionID
        if (!Data["SessionID"].empty()) {
            data.SessionID = Data["SessionID"].asInt();
        } else {
            data.SessionID = 0;
        }

        ///客户姓名 char CustomerName[51];
        if (!Data["CustomerName"].empty()) {
            data.CustomerName[sizeof(data.CustomerName)-1] = 0;
            strncpy(data.CustomerName,Data["CustomerName"].asCString(),sizeof(data.CustomerName)-1);
        } else {
            strcpy(data.CustomerName,"");
        }

        ///证件类型 char IdCardType
        if ( !Data["IdCardType"].empty()) {
            data.IdCardType = Data["IdCardType"].asString()[0];
        } else {
            data.IdCardType = '0';
        }

        ///证件号码 char IdentifiedCardNo[51];
        if (!Data["IdentifiedCardNo"].empty()) {
            data.IdentifiedCardNo[sizeof(data.IdentifiedCardNo)-1] = 0;
            strncpy(data.IdentifiedCardNo,Data["IdentifiedCardNo"].asCString(),sizeof(data.IdentifiedCardNo)-1);
        } else {
            strcpy(data.IdentifiedCardNo,"");
        }

        ///客户类型 char CustType
        if ( !Data["CustType"].empty()) {
            data.CustType = Data["CustType"].asString()[0];
        } else {
            data.CustType = '0';
        }

        ///银行帐号 char BankAccount[41];
        if (!Data["BankAccount"].empty()) {
            data.BankAccount[sizeof(data.BankAccount)-1] = 0;
            strncpy(data.BankAccount,Data["BankAccount"].asCString(),sizeof(data.BankAccount)-1);
        } else {
            strcpy(data.BankAccount,"");
        }

        ///银行密码 char BankPassWord[41];
        if (!Data["BankPassWord"].empty()) {
            data.BankPassWord[sizeof(data.BankPassWord)-1] = 0;
            strncpy(data.BankPassWord,Data["BankPassWord"].asCString(),sizeof(data.BankPassWord)-1);
        } else {
            strcpy(data.BankPassWord,"");
        }

        ///投资者帐号 char AccountID[13];
        if (!Data["AccountID"].empty()) {
            data.AccountID[sizeof(data.AccountID)-1] = 0;
            strncpy(data.AccountID,Data["AccountID"].asCString(),sizeof(data.AccountID)-1);
        } else {
            strcpy(data.AccountID,"");
        }

        ///期货密码 char Password[41];
        if (!Data["Password"].empty()) {
            data.Password[sizeof(data.Password)-1] = 0;
            strncpy(data.Password,Data["Password"].asCString(),sizeof(data.Password)-1);
        } else {
            strcpy(data.Password,"");
        }

        ///安装编号 int InstallID
        if (!Data["InstallID"].empty()) {
            data.InstallID = Data["InstallID"].asInt();
        } else {
            data.InstallID = 0;
        }

        ///期货公司流水号 int FutureSerial
        if (!Data["FutureSerial"].empty()) {
            data.FutureSerial = Data["FutureSerial"].asInt();
        } else {
            data.FutureSerial = 0;
        }

        ///用户标识 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///验证客户证件号码标志 char VerifyCertNoFlag
        if ( !Data["VerifyCertNoFlag"].empty()) {
            data.VerifyCertNoFlag = Data["VerifyCertNoFlag"].asString()[0];
        } else {
            data.VerifyCertNoFlag = '0';
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

        ///转帐金额 double TradeAmount
        if (!Data["TradeAmount"].empty()) {
            data.TradeAmount = Data["TradeAmount"].asDouble();
        } else {
            data.TradeAmount = 0;
        }

        ///期货可取金额 double FutureFetchAmount
        if (!Data["FutureFetchAmount"].empty()) {
            data.FutureFetchAmount = Data["FutureFetchAmount"].asDouble();
        } else {
            data.FutureFetchAmount = 0;
        }

        ///费用支付标志 char FeePayFlag
        if ( !Data["FeePayFlag"].empty()) {
            data.FeePayFlag = Data["FeePayFlag"].asString()[0];
        } else {
            data.FeePayFlag = '0';
        }

        ///应收客户费用 double CustFee
        if (!Data["CustFee"].empty()) {
            data.CustFee = Data["CustFee"].asDouble();
        } else {
            data.CustFee = 0;
        }

        ///应收期货公司费用 double BrokerFee
        if (!Data["BrokerFee"].empty()) {
            data.BrokerFee = Data["BrokerFee"].asDouble();
        } else {
            data.BrokerFee = 0;
        }

        ///发送方给接收方的消息 char Message[129];
        if (!Data["Message"].empty()) {
            data.Message[sizeof(data.Message)-1] = 0;
            strncpy(data.Message,Data["Message"].asCString(),sizeof(data.Message)-1);
        } else {
            strcpy(data.Message,"");
        }

        ///摘要 char Digest[36];
        if (!Data["Digest"].empty()) {
            data.Digest[sizeof(data.Digest)-1] = 0;
            strncpy(data.Digest,Data["Digest"].asCString(),sizeof(data.Digest)-1);
        } else {
            strcpy(data.Digest,"");
        }

        ///银行帐号类型 char BankAccType
        if ( !Data["BankAccType"].empty()) {
            data.BankAccType = Data["BankAccType"].asString()[0];
        } else {
            data.BankAccType = '0';
        }

        ///渠道标志 char DeviceID[3];
        if (!Data["DeviceID"].empty()) {
            data.DeviceID[sizeof(data.DeviceID)-1] = 0;
            strncpy(data.DeviceID,Data["DeviceID"].asCString(),sizeof(data.DeviceID)-1);
        } else {
            strcpy(data.DeviceID,"");
        }

        ///期货单位帐号类型 char BankSecuAccType
        if ( !Data["BankSecuAccType"].empty()) {
            data.BankSecuAccType = Data["BankSecuAccType"].asString()[0];
        } else {
            data.BankSecuAccType = '0';
        }

        ///期货公司银行编码 char BrokerIDByBank[33];
        if (!Data["BrokerIDByBank"].empty()) {
            data.BrokerIDByBank[sizeof(data.BrokerIDByBank)-1] = 0;
            strncpy(data.BrokerIDByBank,Data["BrokerIDByBank"].asCString(),sizeof(data.BrokerIDByBank)-1);
        } else {
            strcpy(data.BrokerIDByBank,"");
        }

        ///期货单位帐号 char BankSecuAcc[41];
        if (!Data["BankSecuAcc"].empty()) {
            data.BankSecuAcc[sizeof(data.BankSecuAcc)-1] = 0;
            strncpy(data.BankSecuAcc,Data["BankSecuAcc"].asCString(),sizeof(data.BankSecuAcc)-1);
        } else {
            strcpy(data.BankSecuAcc,"");
        }

        ///银行密码标志 char BankPwdFlag
        if ( !Data["BankPwdFlag"].empty()) {
            data.BankPwdFlag = Data["BankPwdFlag"].asString()[0];
        } else {
            data.BankPwdFlag = '0';
        }

        ///期货资金密码核对标志 char SecuPwdFlag
        if ( !Data["SecuPwdFlag"].empty()) {
            data.SecuPwdFlag = Data["SecuPwdFlag"].asString()[0];
        } else {
            data.SecuPwdFlag = '0';
        }

        ///交易柜员 char OperNo[17];
        if (!Data["OperNo"].empty()) {
            data.OperNo[sizeof(data.OperNo)-1] = 0;
            strncpy(data.OperNo,Data["OperNo"].asCString(),sizeof(data.OperNo)-1);
        } else {
            strcpy(data.OperNo,"");
        }

        ///请求编号 int RequestID
        if (!Data["RequestID"].empty()) {
            data.RequestID = Data["RequestID"].asInt();
        } else {
            data.RequestID = 0;
        }

        ///交易ID int TID
        if (!Data["TID"].empty()) {
            data.TID = Data["TID"].asInt();
        } else {
            data.TID = 0;
        }

        ///转账交易状态 char TransferStatus
        if ( !Data["TransferStatus"].empty()) {
            data.TransferStatus = Data["TransferStatus"].asString()[0];
        } else {
            data.TransferStatus = '0';
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqFromFutureToBankByFuture(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///期货发起银行资金转期货请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqFromBankToFutureByFuture(std::string jsonString,int requestID)
{
    printf("ReqFromBankToFutureByFuture():被执行...\n");


    CThostFtdcReqTransferField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///业务功能码 char TradeCode[7];
        if (!Data["TradeCode"].empty()) {
            data.TradeCode[sizeof(data.TradeCode)-1] = 0;
            strncpy(data.TradeCode,Data["TradeCode"].asCString(),sizeof(data.TradeCode)-1);
        } else {
            strcpy(data.TradeCode,"");
        }

        ///银行代码 char BankID[4];
        if (!Data["BankID"].empty()) {
            data.BankID[sizeof(data.BankID)-1] = 0;
            strncpy(data.BankID,Data["BankID"].asCString(),sizeof(data.BankID)-1);
        } else {
            strcpy(data.BankID,"");
        }

        ///银行分支机构代码 char BankBranchID[5];
        if (!Data["BankBranchID"].empty()) {
            data.BankBranchID[sizeof(data.BankBranchID)-1] = 0;
            strncpy(data.BankBranchID,Data["BankBranchID"].asCString(),sizeof(data.BankBranchID)-1);
        } else {
            strcpy(data.BankBranchID,"");
        }

        ///期商代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///期商分支机构代码 char BrokerBranchID[31];
        if (!Data["BrokerBranchID"].empty()) {
            data.BrokerBranchID[sizeof(data.BrokerBranchID)-1] = 0;
            strncpy(data.BrokerBranchID,Data["BrokerBranchID"].asCString(),sizeof(data.BrokerBranchID)-1);
        } else {
            strcpy(data.BrokerBranchID,"");
        }

        ///交易日期 char TradeDate[9];
        if (!Data["TradeDate"].empty()) {
            data.TradeDate[sizeof(data.TradeDate)-1] = 0;
            strncpy(data.TradeDate,Data["TradeDate"].asCString(),sizeof(data.TradeDate)-1);
        } else {
            strcpy(data.TradeDate,"");
        }

        ///交易时间 char TradeTime[9];
        if (!Data["TradeTime"].empty()) {
            data.TradeTime[sizeof(data.TradeTime)-1] = 0;
            strncpy(data.TradeTime,Data["TradeTime"].asCString(),sizeof(data.TradeTime)-1);
        } else {
            strcpy(data.TradeTime,"");
        }

        ///银行流水号 char BankSerial[13];
        if (!Data["BankSerial"].empty()) {
            data.BankSerial[sizeof(data.BankSerial)-1] = 0;
            strncpy(data.BankSerial,Data["BankSerial"].asCString(),sizeof(data.BankSerial)-1);
        } else {
            strcpy(data.BankSerial,"");
        }

        ///交易系统日期 char TradingDay[9];
        if (!Data["TradingDay"].empty()) {
            data.TradingDay[sizeof(data.TradingDay)-1] = 0;
            strncpy(data.TradingDay,Data["TradingDay"].asCString(),sizeof(data.TradingDay)-1);
        } else {
            strcpy(data.TradingDay,"");
        }

        ///银期平台消息流水号 int PlateSerial
        if (!Data["PlateSerial"].empty()) {
            data.PlateSerial = Data["PlateSerial"].asInt();
        } else {
            data.PlateSerial = 0;
        }

        ///最后分片标志 char LastFragment
        if ( !Data["LastFragment"].empty()) {
            data.LastFragment = Data["LastFragment"].asString()[0];
        } else {
            data.LastFragment = '0';
        }

        ///会话号 int SessionID
        if (!Data["SessionID"].empty()) {
            data.SessionID = Data["SessionID"].asInt();
        } else {
            data.SessionID = 0;
        }

        ///客户姓名 char CustomerName[51];
        if (!Data["CustomerName"].empty()) {
            data.CustomerName[sizeof(data.CustomerName)-1] = 0;
            strncpy(data.CustomerName,Data["CustomerName"].asCString(),sizeof(data.CustomerName)-1);
        } else {
            strcpy(data.CustomerName,"");
        }

        ///证件类型 char IdCardType
        if ( !Data["IdCardType"].empty()) {
            data.IdCardType = Data["IdCardType"].asString()[0];
        } else {
            data.IdCardType = '0';
        }

        ///证件号码 char IdentifiedCardNo[51];
        if (!Data["IdentifiedCardNo"].empty()) {
            data.IdentifiedCardNo[sizeof(data.IdentifiedCardNo)-1] = 0;
            strncpy(data.IdentifiedCardNo,Data["IdentifiedCardNo"].asCString(),sizeof(data.IdentifiedCardNo)-1);
        } else {
            strcpy(data.IdentifiedCardNo,"");
        }

        ///客户类型 char CustType
        if ( !Data["CustType"].empty()) {
            data.CustType = Data["CustType"].asString()[0];
        } else {
            data.CustType = '0';
        }

        ///银行帐号 char BankAccount[41];
        if (!Data["BankAccount"].empty()) {
            data.BankAccount[sizeof(data.BankAccount)-1] = 0;
            strncpy(data.BankAccount,Data["BankAccount"].asCString(),sizeof(data.BankAccount)-1);
        } else {
            strcpy(data.BankAccount,"");
        }

        ///银行密码 char BankPassWord[41];
        if (!Data["BankPassWord"].empty()) {
            data.BankPassWord[sizeof(data.BankPassWord)-1] = 0;
            strncpy(data.BankPassWord,Data["BankPassWord"].asCString(),sizeof(data.BankPassWord)-1);
        } else {
            strcpy(data.BankPassWord,"");
        }

        ///投资者帐号 char AccountID[13];
        if (!Data["AccountID"].empty()) {
            data.AccountID[sizeof(data.AccountID)-1] = 0;
            strncpy(data.AccountID,Data["AccountID"].asCString(),sizeof(data.AccountID)-1);
        } else {
            strcpy(data.AccountID,"");
        }

        ///期货密码 char Password[41];
        if (!Data["Password"].empty()) {
            data.Password[sizeof(data.Password)-1] = 0;
            strncpy(data.Password,Data["Password"].asCString(),sizeof(data.Password)-1);
        } else {
            strcpy(data.Password,"");
        }

        ///安装编号 int InstallID
        if (!Data["InstallID"].empty()) {
            data.InstallID = Data["InstallID"].asInt();
        } else {
            data.InstallID = 0;
        }

        ///期货公司流水号 int FutureSerial
        if (!Data["FutureSerial"].empty()) {
            data.FutureSerial = Data["FutureSerial"].asInt();
        } else {
            data.FutureSerial = 0;
        }

        ///用户标识 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///验证客户证件号码标志 char VerifyCertNoFlag
        if ( !Data["VerifyCertNoFlag"].empty()) {
            data.VerifyCertNoFlag = Data["VerifyCertNoFlag"].asString()[0];
        } else {
            data.VerifyCertNoFlag = '0';
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

        ///转帐金额 double TradeAmount
        if (!Data["TradeAmount"].empty()) {
            data.TradeAmount = Data["TradeAmount"].asDouble();
        } else {
            data.TradeAmount = 0;
        }

        ///期货可取金额 double FutureFetchAmount
        if (!Data["FutureFetchAmount"].empty()) {
            data.FutureFetchAmount = Data["FutureFetchAmount"].asDouble();
        } else {
            data.FutureFetchAmount = 0;
        }

        ///费用支付标志 char FeePayFlag
        if ( !Data["FeePayFlag"].empty()) {
            data.FeePayFlag = Data["FeePayFlag"].asString()[0];
        } else {
            data.FeePayFlag = '0';
        }

        ///应收客户费用 double CustFee
        if (!Data["CustFee"].empty()) {
            data.CustFee = Data["CustFee"].asDouble();
        } else {
            data.CustFee = 0;
        }

        ///应收期货公司费用 double BrokerFee
        if (!Data["BrokerFee"].empty()) {
            data.BrokerFee = Data["BrokerFee"].asDouble();
        } else {
            data.BrokerFee = 0;
        }

        ///发送方给接收方的消息 char Message[129];
        if (!Data["Message"].empty()) {
            data.Message[sizeof(data.Message)-1] = 0;
            strncpy(data.Message,Data["Message"].asCString(),sizeof(data.Message)-1);
        } else {
            strcpy(data.Message,"");
        }

        ///摘要 char Digest[36];
        if (!Data["Digest"].empty()) {
            data.Digest[sizeof(data.Digest)-1] = 0;
            strncpy(data.Digest,Data["Digest"].asCString(),sizeof(data.Digest)-1);
        } else {
            strcpy(data.Digest,"");
        }

        ///银行帐号类型 char BankAccType
        if ( !Data["BankAccType"].empty()) {
            data.BankAccType = Data["BankAccType"].asString()[0];
        } else {
            data.BankAccType = '0';
        }

        ///渠道标志 char DeviceID[3];
        if (!Data["DeviceID"].empty()) {
            data.DeviceID[sizeof(data.DeviceID)-1] = 0;
            strncpy(data.DeviceID,Data["DeviceID"].asCString(),sizeof(data.DeviceID)-1);
        } else {
            strcpy(data.DeviceID,"");
        }

        ///期货单位帐号类型 char BankSecuAccType
        if ( !Data["BankSecuAccType"].empty()) {
            data.BankSecuAccType = Data["BankSecuAccType"].asString()[0];
        } else {
            data.BankSecuAccType = '0';
        }

        ///期货公司银行编码 char BrokerIDByBank[33];
        if (!Data["BrokerIDByBank"].empty()) {
            data.BrokerIDByBank[sizeof(data.BrokerIDByBank)-1] = 0;
            strncpy(data.BrokerIDByBank,Data["BrokerIDByBank"].asCString(),sizeof(data.BrokerIDByBank)-1);
        } else {
            strcpy(data.BrokerIDByBank,"");
        }

        ///期货单位帐号 char BankSecuAcc[41];
        if (!Data["BankSecuAcc"].empty()) {
            data.BankSecuAcc[sizeof(data.BankSecuAcc)-1] = 0;
            strncpy(data.BankSecuAcc,Data["BankSecuAcc"].asCString(),sizeof(data.BankSecuAcc)-1);
        } else {
            strcpy(data.BankSecuAcc,"");
        }

        ///银行密码标志 char BankPwdFlag
        if ( !Data["BankPwdFlag"].empty()) {
            data.BankPwdFlag = Data["BankPwdFlag"].asString()[0];
        } else {
            data.BankPwdFlag = '0';
        }

        ///期货资金密码核对标志 char SecuPwdFlag
        if ( !Data["SecuPwdFlag"].empty()) {
            data.SecuPwdFlag = Data["SecuPwdFlag"].asString()[0];
        } else {
            data.SecuPwdFlag = '0';
        }

        ///交易柜员 char OperNo[17];
        if (!Data["OperNo"].empty()) {
            data.OperNo[sizeof(data.OperNo)-1] = 0;
            strncpy(data.OperNo,Data["OperNo"].asCString(),sizeof(data.OperNo)-1);
        } else {
            strcpy(data.OperNo,"");
        }

        ///请求编号 int RequestID
        if (!Data["RequestID"].empty()) {
            data.RequestID = Data["RequestID"].asInt();
        } else {
            data.RequestID = 0;
        }

        ///交易ID int TID
        if (!Data["TID"].empty()) {
            data.TID = Data["TID"].asInt();
        } else {
            data.TID = 0;
        }

        ///转账交易状态 char TransferStatus
        if ( !Data["TransferStatus"].empty()) {
            data.TransferStatus = Data["TransferStatus"].asString()[0];
        } else {
            data.TransferStatus = '0';
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqFromBankToFutureByFuture(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询结算信息确认
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQrySettlementInfoConfirm(std::string jsonString,int requestID)
{
    printf("ReqQrySettlementInfoConfirm():被执行...\n");


    CThostFtdcQrySettlementInfoConfirmField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySettlementInfoConfirm(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询经纪公司交易参数
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryBrokerTradingParams(std::string jsonString,int requestID)
{
    printf("ReqQryBrokerTradingParams():被执行...\n");


    CThostFtdcQryBrokerTradingParamsField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryBrokerTradingParams(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询监控中心用户令牌
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQueryCFMMCTradingAccountToken(std::string jsonString,int requestID)
{
    printf("ReqQueryCFMMCTradingAccountToken():被执行...\n");


    CThostFtdcQueryCFMMCTradingAccountTokenField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryCFMMCTradingAccountToken(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询客户通知
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryNotice(std::string jsonString,int requestID)
{
    printf("ReqQryNotice():被执行...\n");


    CThostFtdcQryNoticeField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryNotice(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询汇率
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryExchangeRate(std::string jsonString,int requestID)
{
    printf("ReqQryExchangeRate():被执行...\n");


    CThostFtdcQryExchangeRateField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///源币种 char FromCurrencyID[4];
        if (!Data["FromCurrencyID"].empty()) {
            data.FromCurrencyID[sizeof(data.FromCurrencyID)-1] = 0;
            strncpy(data.FromCurrencyID,Data["FromCurrencyID"].asCString(),sizeof(data.FromCurrencyID)-1);
        } else {
            strcpy(data.FromCurrencyID,"");
        }

        ///目标币种 char ToCurrencyID[4];
        if (!Data["ToCurrencyID"].empty()) {
            data.ToCurrencyID[sizeof(data.ToCurrencyID)-1] = 0;
            strncpy(data.ToCurrencyID,Data["ToCurrencyID"].asCString(),sizeof(data.ToCurrencyID)-1);
        } else {
            strcpy(data.ToCurrencyID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///预埋单录入请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqParkedOrderInsert(std::string jsonString,int requestID)
{
    printf("ReqParkedOrderInsert():被执行...\n");


    CThostFtdcParkedOrderField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///报单引用 char OrderRef[13];
        if (!Data["OrderRef"].empty()) {
            data.OrderRef[sizeof(data.OrderRef)-1] = 0;
            strncpy(data.OrderRef,Data["OrderRef"].asCString(),sizeof(data.OrderRef)-1);
        } else {
            strcpy(data.OrderRef,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///报单价格条件 char OrderPriceType
        if ( !Data["OrderPriceType"].empty()) {
            data.OrderPriceType = Data["OrderPriceType"].asString()[0];
        } else {
            data.OrderPriceType = '0';
        }

        ///买卖方向 char Direction
        if ( !Data["Direction"].empty()) {
            data.Direction = Data["Direction"].asString()[0];
        } else {
            data.Direction = '0';
        }

        ///组合开平标志 char CombOffsetFlag[5];
        if (!Data["CombOffsetFlag"].empty()) {
            data.CombOffsetFlag[sizeof(data.CombOffsetFlag)-1] = 0;
            strncpy(data.CombOffsetFlag,Data["CombOffsetFlag"].asCString(),sizeof(data.CombOffsetFlag)-1);
        } else {
            strcpy(data.CombOffsetFlag,"");
        }

        ///组合投机套保标志 char CombHedgeFlag[5];
        if (!Data["CombHedgeFlag"].empty()) {
            data.CombHedgeFlag[sizeof(data.CombHedgeFlag)-1] = 0;
            strncpy(data.CombHedgeFlag,Data["CombHedgeFlag"].asCString(),sizeof(data.CombHedgeFlag)-1);
        } else {
            strcpy(data.CombHedgeFlag,"");
        }

        ///价格 double LimitPrice
        if (!Data["LimitPrice"].empty()) {
            data.LimitPrice = Data["LimitPrice"].asDouble();
        } else {
            data.LimitPrice = 0;
        }

        ///数量 int VolumeTotalOriginal
        if (!Data["VolumeTotalOriginal"].empty()) {
            data.VolumeTotalOriginal = Data["VolumeTotalOriginal"].asInt();
        } else {
            data.VolumeTotalOriginal = 0;
        }

        ///有效期类型 char TimeCondition
        if ( !Data["TimeCondition"].empty()) {
            data.TimeCondition = Data["TimeCondition"].asString()[0];
        } else {
            data.TimeCondition = '0';
        }

        ///GTD日期 char GTDDate[9];
        if (!Data["GTDDate"].empty()) {
            data.GTDDate[sizeof(data.GTDDate)-1] = 0;
            strncpy(data.GTDDate,Data["GTDDate"].asCString(),sizeof(data.GTDDate)-1);
        } else {
            strcpy(data.GTDDate,"");
        }

        ///成交量类型 char VolumeCondition
        if ( !Data["VolumeCondition"].empty()) {
            data.VolumeCondition = Data["VolumeCondition"].asString()[0];
        } else {
            data.VolumeCondition = '0';
        }

        ///最小成交量 int MinVolume
        if (!Data["MinVolume"].empty()) {
            data.MinVolume = Data["MinVolume"].asInt();
        } else {
            data.MinVolume = 0;
        }

        ///触发条件 char ContingentCondition
        if ( !Data["ContingentCondition"].empty()) {
            data.ContingentCondition = Data["ContingentCondition"].asString()[0];
        } else {
            data.ContingentCondition = '0';
        }

        ///止损价 double StopPrice
        if (!Data["StopPrice"].empty()) {
            data.StopPrice = Data["StopPrice"].asDouble();
        } else {
            data.StopPrice = 0;
        }

        ///强平原因 char ForceCloseReason
        if ( !Data["ForceCloseReason"].empty()) {
            data.ForceCloseReason = Data["ForceCloseReason"].asString()[0];
        } else {
            data.ForceCloseReason = '0';
        }

        ///自动挂起标志 int IsAutoSuspend
        if (!Data["IsAutoSuspend"].empty()) {
            data.IsAutoSuspend = Data["IsAutoSuspend"].asInt();
        } else {
            data.IsAutoSuspend = 0;
        }

        ///业务单元 char BusinessUnit[21];
        if (!Data["BusinessUnit"].empty()) {
            data.BusinessUnit[sizeof(data.BusinessUnit)-1] = 0;
            strncpy(data.BusinessUnit,Data["BusinessUnit"].asCString(),sizeof(data.BusinessUnit)-1);
        } else {
            strcpy(data.BusinessUnit,"");
        }

        ///请求编号 int RequestID
        if (!Data["RequestID"].empty()) {
            data.RequestID = Data["RequestID"].asInt();
        } else {
            data.RequestID = 0;
        }

        ///用户强评标志 int UserForceClose
        if (!Data["UserForceClose"].empty()) {
            data.UserForceClose = Data["UserForceClose"].asInt();
        } else {
            data.UserForceClose = 0;
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///预埋报单编号 char ParkedOrderID[13];
        if (!Data["ParkedOrderID"].empty()) {
            data.ParkedOrderID[sizeof(data.ParkedOrderID)-1] = 0;
            strncpy(data.ParkedOrderID,Data["ParkedOrderID"].asCString(),sizeof(data.ParkedOrderID)-1);
        } else {
            strcpy(data.ParkedOrderID,"");
        }

        ///用户类型 char UserType
        if ( !Data["UserType"].empty()) {
            data.UserType = Data["UserType"].asString()[0];
        } else {
            data.UserType = '0';
        }

        ///预埋单状态 char Status
        if ( !Data["Status"].empty()) {
            data.Status = Data["Status"].asString()[0];
        } else {
            data.Status = '0';
        }

        ///错误代码 int ErrorID
        if (!Data["ErrorID"].empty()) {
            data.ErrorID = Data["ErrorID"].asInt();
        } else {
            data.ErrorID = 0;
        }

        ///错误信息 char ErrorMsg[81];
        if (!Data["ErrorMsg"].empty()) {
            data.ErrorMsg[sizeof(data.ErrorMsg)-1] = 0;
            strncpy(data.ErrorMsg,Data["ErrorMsg"].asCString(),sizeof(data.ErrorMsg)-1);
        } else {
            strcpy(data.ErrorMsg,"");
        }

        ///互换单标志 int IsSwapOrder
        if (!Data["IsSwapOrder"].empty()) {
            data.IsSwapOrder = Data["IsSwapOrder"].asInt();
        } else {
            data.IsSwapOrder = 0;
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqParkedOrderInsert(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询签约银行
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryContractBank(std::string jsonString,int requestID)
{
    printf("ReqQryContractBank():被执行...\n");


    CThostFtdcQryContractBankField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///银行代码 char BankID[4];
        if (!Data["BankID"].empty()) {
            data.BankID[sizeof(data.BankID)-1] = 0;
            strncpy(data.BankID,Data["BankID"].asCString(),sizeof(data.BankID)-1);
        } else {
            strcpy(data.BankID,"");
        }

        ///银行分中心代码 char BankBrchID[5];
        if (!Data["BankBrchID"].empty()) {
            data.BankBrchID[sizeof(data.BankBrchID)-1] = 0;
            strncpy(data.BankBrchID,Data["BankBrchID"].asCString(),sizeof(data.BankBrchID)-1);
        } else {
            strcpy(data.BankBrchID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryContractBank(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询投资者持仓明细
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInvestorPositionCombineDetail(std::string jsonString,int requestID)
{
    printf("ReqQryInvestorPositionCombineDetail():被执行...\n");


    CThostFtdcQryInvestorPositionCombineDetailField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///组合持仓合约编码 char CombInstrumentID[31];
        if (!Data["CombInstrumentID"].empty()) {
            data.CombInstrumentID[sizeof(data.CombInstrumentID)-1] = 0;
            strncpy(data.CombInstrumentID,Data["CombInstrumentID"].asCString(),sizeof(data.CombInstrumentID)-1);
        } else {
            strcpy(data.CombInstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPositionCombineDetail(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询交易所保证金率
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryExchangeMarginRate(std::string jsonString,int requestID)
{
    printf("ReqQryExchangeMarginRate():被执行...\n");


    CThostFtdcQryExchangeMarginRateField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///投机套保标志 char HedgeFlag
        if ( !Data["HedgeFlag"].empty()) {
            data.HedgeFlag = Data["HedgeFlag"].asString()[0];
        } else {
            data.HedgeFlag = '0';
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeMarginRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询二级代理操作员银期权限
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQrySecAgentACIDMap(std::string jsonString,int requestID)
{
    printf("ReqQrySecAgentACIDMap():被执行...\n");


    CThostFtdcQrySecAgentACIDMapField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///资金账户 char AccountID[13];
        if (!Data["AccountID"].empty()) {
            data.AccountID[sizeof(data.AccountID)-1] = 0;
            strncpy(data.AccountID,Data["AccountID"].asCString(),sizeof(data.AccountID)-1);
        } else {
            strcpy(data.AccountID,"");
        }

        ///币种 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySecAgentACIDMap(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询转帐流水
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryTransferSerial(std::string jsonString,int requestID)
{
    printf("ReqQryTransferSerial():被执行...\n");


    CThostFtdcQryTransferSerialField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者帐号 char AccountID[13];
        if (!Data["AccountID"].empty()) {
            data.AccountID[sizeof(data.AccountID)-1] = 0;
            strncpy(data.AccountID,Data["AccountID"].asCString(),sizeof(data.AccountID)-1);
        } else {
            strcpy(data.AccountID,"");
        }

        ///银行编码 char BankID[4];
        if (!Data["BankID"].empty()) {
            data.BankID[sizeof(data.BankID)-1] = 0;
            strncpy(data.BankID,Data["BankID"].asCString(),sizeof(data.BankID)-1);
        } else {
            strcpy(data.BankID,"");
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTransferSerial(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///期货发起查询银行余额请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQueryBankAccountMoneyByFuture(std::string jsonString,int requestID)
{
    printf("ReqQueryBankAccountMoneyByFuture():被执行...\n");


    CThostFtdcReqQueryAccountField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///业务功能码 char TradeCode[7];
        if (!Data["TradeCode"].empty()) {
            data.TradeCode[sizeof(data.TradeCode)-1] = 0;
            strncpy(data.TradeCode,Data["TradeCode"].asCString(),sizeof(data.TradeCode)-1);
        } else {
            strcpy(data.TradeCode,"");
        }

        ///银行代码 char BankID[4];
        if (!Data["BankID"].empty()) {
            data.BankID[sizeof(data.BankID)-1] = 0;
            strncpy(data.BankID,Data["BankID"].asCString(),sizeof(data.BankID)-1);
        } else {
            strcpy(data.BankID,"");
        }

        ///银行分支机构代码 char BankBranchID[5];
        if (!Data["BankBranchID"].empty()) {
            data.BankBranchID[sizeof(data.BankBranchID)-1] = 0;
            strncpy(data.BankBranchID,Data["BankBranchID"].asCString(),sizeof(data.BankBranchID)-1);
        } else {
            strcpy(data.BankBranchID,"");
        }

        ///期商代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///期商分支机构代码 char BrokerBranchID[31];
        if (!Data["BrokerBranchID"].empty()) {
            data.BrokerBranchID[sizeof(data.BrokerBranchID)-1] = 0;
            strncpy(data.BrokerBranchID,Data["BrokerBranchID"].asCString(),sizeof(data.BrokerBranchID)-1);
        } else {
            strcpy(data.BrokerBranchID,"");
        }

        ///交易日期 char TradeDate[9];
        if (!Data["TradeDate"].empty()) {
            data.TradeDate[sizeof(data.TradeDate)-1] = 0;
            strncpy(data.TradeDate,Data["TradeDate"].asCString(),sizeof(data.TradeDate)-1);
        } else {
            strcpy(data.TradeDate,"");
        }

        ///交易时间 char TradeTime[9];
        if (!Data["TradeTime"].empty()) {
            data.TradeTime[sizeof(data.TradeTime)-1] = 0;
            strncpy(data.TradeTime,Data["TradeTime"].asCString(),sizeof(data.TradeTime)-1);
        } else {
            strcpy(data.TradeTime,"");
        }

        ///银行流水号 char BankSerial[13];
        if (!Data["BankSerial"].empty()) {
            data.BankSerial[sizeof(data.BankSerial)-1] = 0;
            strncpy(data.BankSerial,Data["BankSerial"].asCString(),sizeof(data.BankSerial)-1);
        } else {
            strcpy(data.BankSerial,"");
        }

        ///交易系统日期 char TradingDay[9];
        if (!Data["TradingDay"].empty()) {
            data.TradingDay[sizeof(data.TradingDay)-1] = 0;
            strncpy(data.TradingDay,Data["TradingDay"].asCString(),sizeof(data.TradingDay)-1);
        } else {
            strcpy(data.TradingDay,"");
        }

        ///银期平台消息流水号 int PlateSerial
        if (!Data["PlateSerial"].empty()) {
            data.PlateSerial = Data["PlateSerial"].asInt();
        } else {
            data.PlateSerial = 0;
        }

        ///最后分片标志 char LastFragment
        if ( !Data["LastFragment"].empty()) {
            data.LastFragment = Data["LastFragment"].asString()[0];
        } else {
            data.LastFragment = '0';
        }

        ///会话号 int SessionID
        if (!Data["SessionID"].empty()) {
            data.SessionID = Data["SessionID"].asInt();
        } else {
            data.SessionID = 0;
        }

        ///客户姓名 char CustomerName[51];
        if (!Data["CustomerName"].empty()) {
            data.CustomerName[sizeof(data.CustomerName)-1] = 0;
            strncpy(data.CustomerName,Data["CustomerName"].asCString(),sizeof(data.CustomerName)-1);
        } else {
            strcpy(data.CustomerName,"");
        }

        ///证件类型 char IdCardType
        if ( !Data["IdCardType"].empty()) {
            data.IdCardType = Data["IdCardType"].asString()[0];
        } else {
            data.IdCardType = '0';
        }

        ///证件号码 char IdentifiedCardNo[51];
        if (!Data["IdentifiedCardNo"].empty()) {
            data.IdentifiedCardNo[sizeof(data.IdentifiedCardNo)-1] = 0;
            strncpy(data.IdentifiedCardNo,Data["IdentifiedCardNo"].asCString(),sizeof(data.IdentifiedCardNo)-1);
        } else {
            strcpy(data.IdentifiedCardNo,"");
        }

        ///客户类型 char CustType
        if ( !Data["CustType"].empty()) {
            data.CustType = Data["CustType"].asString()[0];
        } else {
            data.CustType = '0';
        }

        ///银行帐号 char BankAccount[41];
        if (!Data["BankAccount"].empty()) {
            data.BankAccount[sizeof(data.BankAccount)-1] = 0;
            strncpy(data.BankAccount,Data["BankAccount"].asCString(),sizeof(data.BankAccount)-1);
        } else {
            strcpy(data.BankAccount,"");
        }

        ///银行密码 char BankPassWord[41];
        if (!Data["BankPassWord"].empty()) {
            data.BankPassWord[sizeof(data.BankPassWord)-1] = 0;
            strncpy(data.BankPassWord,Data["BankPassWord"].asCString(),sizeof(data.BankPassWord)-1);
        } else {
            strcpy(data.BankPassWord,"");
        }

        ///投资者帐号 char AccountID[13];
        if (!Data["AccountID"].empty()) {
            data.AccountID[sizeof(data.AccountID)-1] = 0;
            strncpy(data.AccountID,Data["AccountID"].asCString(),sizeof(data.AccountID)-1);
        } else {
            strcpy(data.AccountID,"");
        }

        ///期货密码 char Password[41];
        if (!Data["Password"].empty()) {
            data.Password[sizeof(data.Password)-1] = 0;
            strncpy(data.Password,Data["Password"].asCString(),sizeof(data.Password)-1);
        } else {
            strcpy(data.Password,"");
        }

        ///期货公司流水号 int FutureSerial
        if (!Data["FutureSerial"].empty()) {
            data.FutureSerial = Data["FutureSerial"].asInt();
        } else {
            data.FutureSerial = 0;
        }

        ///安装编号 int InstallID
        if (!Data["InstallID"].empty()) {
            data.InstallID = Data["InstallID"].asInt();
        } else {
            data.InstallID = 0;
        }

        ///用户标识 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///验证客户证件号码标志 char VerifyCertNoFlag
        if ( !Data["VerifyCertNoFlag"].empty()) {
            data.VerifyCertNoFlag = Data["VerifyCertNoFlag"].asString()[0];
        } else {
            data.VerifyCertNoFlag = '0';
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

        ///摘要 char Digest[36];
        if (!Data["Digest"].empty()) {
            data.Digest[sizeof(data.Digest)-1] = 0;
            strncpy(data.Digest,Data["Digest"].asCString(),sizeof(data.Digest)-1);
        } else {
            strcpy(data.Digest,"");
        }

        ///银行帐号类型 char BankAccType
        if ( !Data["BankAccType"].empty()) {
            data.BankAccType = Data["BankAccType"].asString()[0];
        } else {
            data.BankAccType = '0';
        }

        ///渠道标志 char DeviceID[3];
        if (!Data["DeviceID"].empty()) {
            data.DeviceID[sizeof(data.DeviceID)-1] = 0;
            strncpy(data.DeviceID,Data["DeviceID"].asCString(),sizeof(data.DeviceID)-1);
        } else {
            strcpy(data.DeviceID,"");
        }

        ///期货单位帐号类型 char BankSecuAccType
        if ( !Data["BankSecuAccType"].empty()) {
            data.BankSecuAccType = Data["BankSecuAccType"].asString()[0];
        } else {
            data.BankSecuAccType = '0';
        }

        ///期货公司银行编码 char BrokerIDByBank[33];
        if (!Data["BrokerIDByBank"].empty()) {
            data.BrokerIDByBank[sizeof(data.BrokerIDByBank)-1] = 0;
            strncpy(data.BrokerIDByBank,Data["BrokerIDByBank"].asCString(),sizeof(data.BrokerIDByBank)-1);
        } else {
            strcpy(data.BrokerIDByBank,"");
        }

        ///期货单位帐号 char BankSecuAcc[41];
        if (!Data["BankSecuAcc"].empty()) {
            data.BankSecuAcc[sizeof(data.BankSecuAcc)-1] = 0;
            strncpy(data.BankSecuAcc,Data["BankSecuAcc"].asCString(),sizeof(data.BankSecuAcc)-1);
        } else {
            strcpy(data.BankSecuAcc,"");
        }

        ///银行密码标志 char BankPwdFlag
        if ( !Data["BankPwdFlag"].empty()) {
            data.BankPwdFlag = Data["BankPwdFlag"].asString()[0];
        } else {
            data.BankPwdFlag = '0';
        }

        ///期货资金密码核对标志 char SecuPwdFlag
        if ( !Data["SecuPwdFlag"].empty()) {
            data.SecuPwdFlag = Data["SecuPwdFlag"].asString()[0];
        } else {
            data.SecuPwdFlag = '0';
        }

        ///交易柜员 char OperNo[17];
        if (!Data["OperNo"].empty()) {
            data.OperNo[sizeof(data.OperNo)-1] = 0;
            strncpy(data.OperNo,Data["OperNo"].asCString(),sizeof(data.OperNo)-1);
        } else {
            strcpy(data.OperNo,"");
        }

        ///请求编号 int RequestID
        if (!Data["RequestID"].empty()) {
            data.RequestID = Data["RequestID"].asInt();
        } else {
            data.RequestID = 0;
        }

        ///交易ID int TID
        if (!Data["TID"].empty()) {
            data.TID = Data["TID"].asInt();
        } else {
            data.TID = 0;
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryBankAccountMoneyByFuture(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询预埋撤单
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryParkedOrderAction(std::string jsonString,int requestID)
{
    printf("ReqQryParkedOrderAction():被执行...\n");


    CThostFtdcQryParkedOrderActionField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryParkedOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///客户端认证请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqAuthenticate(std::string jsonString,int requestID)
{
    printf("ReqAuthenticate():被执行...\n");


    CThostFtdcReqAuthenticateField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///用户端产品信息 char UserProductInfo[11];
        if (!Data["UserProductInfo"].empty()) {
            data.UserProductInfo[sizeof(data.UserProductInfo)-1] = 0;
            strncpy(data.UserProductInfo,Data["UserProductInfo"].asCString(),sizeof(data.UserProductInfo)-1);
        } else {
            strcpy(data.UserProductInfo,"");
        }

        ///认证码 char AuthCode[17];
        if (!Data["AuthCode"].empty()) {
            data.AuthCode[sizeof(data.AuthCode)-1] = 0;
            strncpy(data.AuthCode,Data["AuthCode"].asCString(),sizeof(data.AuthCode)-1);
        } else {
            strcpy(data.AuthCode,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqAuthenticate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///报单录入请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqOrderInsert(std::string jsonString,int requestID)
{
    printf("ReqOrderInsert():被执行...\n");


    CThostFtdcInputOrderField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///报单引用 char OrderRef[13];
        if (!Data["OrderRef"].empty()) {
            data.OrderRef[sizeof(data.OrderRef)-1] = 0;
            strncpy(data.OrderRef,Data["OrderRef"].asCString(),sizeof(data.OrderRef)-1);
        } else {
            strcpy(data.OrderRef,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///报单价格条件 char OrderPriceType
        if ( !Data["OrderPriceType"].empty()) {
            data.OrderPriceType = Data["OrderPriceType"].asString()[0];
        } else {
            data.OrderPriceType = '0';
        }

        ///买卖方向 char Direction
        if ( !Data["Direction"].empty()) {
            data.Direction = Data["Direction"].asString()[0];
        } else {
            data.Direction = '0';
        }

        ///组合开平标志 char CombOffsetFlag[5];
        if (!Data["CombOffsetFlag"].empty()) {
            data.CombOffsetFlag[sizeof(data.CombOffsetFlag)-1] = 0;
            strncpy(data.CombOffsetFlag,Data["CombOffsetFlag"].asCString(),sizeof(data.CombOffsetFlag)-1);
        } else {
            strcpy(data.CombOffsetFlag,"");
        }

        ///组合投机套保标志 char CombHedgeFlag[5];
        if (!Data["CombHedgeFlag"].empty()) {
            data.CombHedgeFlag[sizeof(data.CombHedgeFlag)-1] = 0;
            strncpy(data.CombHedgeFlag,Data["CombHedgeFlag"].asCString(),sizeof(data.CombHedgeFlag)-1);
        } else {
            strcpy(data.CombHedgeFlag,"");
        }

        ///价格 double LimitPrice
        if (!Data["LimitPrice"].empty()) {
            data.LimitPrice = Data["LimitPrice"].asDouble();
        } else {
            data.LimitPrice = 0;
        }

        ///数量 int VolumeTotalOriginal
        if (!Data["VolumeTotalOriginal"].empty()) {
            data.VolumeTotalOriginal = Data["VolumeTotalOriginal"].asInt();
        } else {
            data.VolumeTotalOriginal = 0;
        }

        ///有效期类型 char TimeCondition
        if ( !Data["TimeCondition"].empty()) {
            data.TimeCondition = Data["TimeCondition"].asString()[0];
        } else {
            data.TimeCondition = '0';
        }

        ///GTD日期 char GTDDate[9];
        if (!Data["GTDDate"].empty()) {
            data.GTDDate[sizeof(data.GTDDate)-1] = 0;
            strncpy(data.GTDDate,Data["GTDDate"].asCString(),sizeof(data.GTDDate)-1);
        } else {
            strcpy(data.GTDDate,"");
        }

        ///成交量类型 char VolumeCondition
        if ( !Data["VolumeCondition"].empty()) {
            data.VolumeCondition = Data["VolumeCondition"].asString()[0];
        } else {
            data.VolumeCondition = '0';
        }

        ///最小成交量 int MinVolume
        if (!Data["MinVolume"].empty()) {
            data.MinVolume = Data["MinVolume"].asInt();
        } else {
            data.MinVolume = 0;
        }

        ///触发条件 char ContingentCondition
        if ( !Data["ContingentCondition"].empty()) {
            data.ContingentCondition = Data["ContingentCondition"].asString()[0];
        } else {
            data.ContingentCondition = '0';
        }

        ///止损价 double StopPrice
        if (!Data["StopPrice"].empty()) {
            data.StopPrice = Data["StopPrice"].asDouble();
        } else {
            data.StopPrice = 0;
        }

        ///强平原因 char ForceCloseReason
        if ( !Data["ForceCloseReason"].empty()) {
            data.ForceCloseReason = Data["ForceCloseReason"].asString()[0];
        } else {
            data.ForceCloseReason = '0';
        }

        ///自动挂起标志 int IsAutoSuspend
        if (!Data["IsAutoSuspend"].empty()) {
            data.IsAutoSuspend = Data["IsAutoSuspend"].asInt();
        } else {
            data.IsAutoSuspend = 0;
        }

        ///业务单元 char BusinessUnit[21];
        if (!Data["BusinessUnit"].empty()) {
            data.BusinessUnit[sizeof(data.BusinessUnit)-1] = 0;
            strncpy(data.BusinessUnit,Data["BusinessUnit"].asCString(),sizeof(data.BusinessUnit)-1);
        } else {
            strcpy(data.BusinessUnit,"");
        }

        ///请求编号 int RequestID
        if (!Data["RequestID"].empty()) {
            data.RequestID = Data["RequestID"].asInt();
        } else {
            data.RequestID = 0;
        }

        ///用户强评标志 int UserForceClose
        if (!Data["UserForceClose"].empty()) {
            data.UserForceClose = Data["UserForceClose"].asInt();
        } else {
            data.UserForceClose = 0;
        }

        ///互换单标志 int IsSwapOrder
        if (!Data["IsSwapOrder"].empty()) {
            data.IsSwapOrder = Data["IsSwapOrder"].asInt();
        } else {
            data.IsSwapOrder = 0;
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqOrderInsert(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询投资者结算结果
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQrySettlementInfo(std::string jsonString,int requestID)
{
    printf("ReqQrySettlementInfo():被执行...\n");


    CThostFtdcQrySettlementInfoField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///交易日 char TradingDay[9];
        if (!Data["TradingDay"].empty()) {
            data.TradingDay[sizeof(data.TradingDay)-1] = 0;
            strncpy(data.TradingDay,Data["TradingDay"].asCString(),sizeof(data.TradingDay)-1);
        } else {
            strcpy(data.TradingDay,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySettlementInfo(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///登出请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqUserLogout(std::string jsonString,int requestID)
{
    printf("ReqUserLogout():被执行...\n");


    CThostFtdcUserLogoutField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserLogout(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询合约
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInstrument(std::string jsonString,int requestID)
{
    printf("ReqQryInstrument():被执行...\n");


    CThostFtdcQryInstrumentField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///合约在交易所的代码 char ExchangeInstID[31];
        if (!Data["ExchangeInstID"].empty()) {
            data.ExchangeInstID[sizeof(data.ExchangeInstID)-1] = 0;
            strncpy(data.ExchangeInstID,Data["ExchangeInstID"].asCString(),sizeof(data.ExchangeInstID)-1);
        } else {
            strcpy(data.ExchangeInstID,"");
        }

        ///产品代码 char ProductID[31];
        if (!Data["ProductID"].empty()) {
            data.ProductID[sizeof(data.ProductID)-1] = 0;
            strncpy(data.ProductID,Data["ProductID"].asCString(),sizeof(data.ProductID)-1);
        } else {
            strcpy(data.ProductID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrument(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///报单操作请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqOrderAction(std::string jsonString,int requestID)
{
    printf("ReqOrderAction():被执行...\n");


    CThostFtdcInputOrderActionField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///报单操作引用 int OrderActionRef
        if (!Data["OrderActionRef"].empty()) {
            data.OrderActionRef = Data["OrderActionRef"].asInt();
        } else {
            data.OrderActionRef = 0;
        }

        ///报单引用 char OrderRef[13];
        if (!Data["OrderRef"].empty()) {
            data.OrderRef[sizeof(data.OrderRef)-1] = 0;
            strncpy(data.OrderRef,Data["OrderRef"].asCString(),sizeof(data.OrderRef)-1);
        } else {
            strcpy(data.OrderRef,"");
        }

        ///请求编号 int RequestID
        if (!Data["RequestID"].empty()) {
            data.RequestID = Data["RequestID"].asInt();
        } else {
            data.RequestID = 0;
        }

        ///前置编号 int FrontID
        if (!Data["FrontID"].empty()) {
            data.FrontID = Data["FrontID"].asInt();
        } else {
            data.FrontID = 0;
        }

        ///会话编号 int SessionID
        if (!Data["SessionID"].empty()) {
            data.SessionID = Data["SessionID"].asInt();
        } else {
            data.SessionID = 0;
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///报单编号 char OrderSysID[21];
        if (!Data["OrderSysID"].empty()) {
            data.OrderSysID[sizeof(data.OrderSysID)-1] = 0;
            strncpy(data.OrderSysID,Data["OrderSysID"].asCString(),sizeof(data.OrderSysID)-1);
        } else {
            strcpy(data.OrderSysID,"");
        }

        ///操作标志 char ActionFlag
        if ( !Data["ActionFlag"].empty()) {
            data.ActionFlag = Data["ActionFlag"].asString()[0];
        } else {
            data.ActionFlag = '0';
        }

        ///价格 double LimitPrice
        if (!Data["LimitPrice"].empty()) {
            data.LimitPrice = Data["LimitPrice"].asDouble();
        } else {
            data.LimitPrice = 0;
        }

        ///数量变化 int VolumeChange
        if (!Data["VolumeChange"].empty()) {
            data.VolumeChange = Data["VolumeChange"].asInt();
        } else {
            data.VolumeChange = 0;
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询合约手续费率
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInstrumentCommissionRate(std::string jsonString,int requestID)
{
    printf("ReqQryInstrumentCommissionRate():被执行...\n");


    CThostFtdcQryInstrumentCommissionRateField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrumentCommissionRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询合约保证金率
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInstrumentMarginRate(std::string jsonString,int requestID)
{
    printf("ReqQryInstrumentMarginRate():被执行...\n");


    CThostFtdcQryInstrumentMarginRateField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///投机套保标志 char HedgeFlag
        if ( !Data["HedgeFlag"].empty()) {
            data.HedgeFlag = Data["HedgeFlag"].asString()[0];
        } else {
            data.HedgeFlag = '0';
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrumentMarginRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询投资者
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInvestor(std::string jsonString,int requestID)
{
    printf("ReqQryInvestor():被执行...\n");


    CThostFtdcQryInvestorField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestor(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询预埋单
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryParkedOrder(std::string jsonString,int requestID)
{
    printf("ReqQryParkedOrder():被执行...\n");


    CThostFtdcQryParkedOrderField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryParkedOrder(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询投资者品种/跨品种保证金
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInvestorProductGroupMargin(std::string jsonString,int requestID)
{
    printf("ReqQryInvestorProductGroupMargin():被执行...\n");


    CThostFtdcQryInvestorProductGroupMarginField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///品种/跨品种标示 char ProductGroupID[31];
        if (!Data["ProductGroupID"].empty()) {
            data.ProductGroupID[sizeof(data.ProductGroupID)-1] = 0;
            strncpy(data.ProductGroupID,Data["ProductGroupID"].asCString(),sizeof(data.ProductGroupID)-1);
        } else {
            strcpy(data.ProductGroupID,"");
        }

        ///投机套保标志 char HedgeFlag
        if ( !Data["HedgeFlag"].empty()) {
            data.HedgeFlag = Data["HedgeFlag"].asString()[0];
        } else {
            data.HedgeFlag = '0';
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorProductGroupMargin(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询行情
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryDepthMarketData(std::string jsonString,int requestID)
{
    printf("ReqQryDepthMarketData():被执行...\n");


    CThostFtdcQryDepthMarketDataField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryDepthMarketData(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询转帐银行
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryTransferBank(std::string jsonString,int requestID)
{
    printf("ReqQryTransferBank():被执行...\n");


    CThostFtdcQryTransferBankField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///银行代码 char BankID[4];
        if (!Data["BankID"].empty()) {
            data.BankID[sizeof(data.BankID)-1] = 0;
            strncpy(data.BankID,Data["BankID"].asCString(),sizeof(data.BankID)-1);
        } else {
            strcpy(data.BankID,"");
        }

        ///银行分中心代码 char BankBrchID[5];
        if (!Data["BankBrchID"].empty()) {
            data.BankBrchID[sizeof(data.BankBrchID)-1] = 0;
            strncpy(data.BankBrchID,Data["BankBrchID"].asCString(),sizeof(data.BankBrchID)-1);
        } else {
            strcpy(data.BankBrchID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTransferBank(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求删除预埋撤单
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqRemoveParkedOrderAction(std::string jsonString,int requestID)
{
    printf("ReqRemoveParkedOrderAction():被执行...\n");


    CThostFtdcRemoveParkedOrderActionField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///预埋撤单编号 char ParkedOrderActionID[13];
        if (!Data["ParkedOrderActionID"].empty()) {
            data.ParkedOrderActionID[sizeof(data.ParkedOrderActionID)-1] = 0;
            strncpy(data.ParkedOrderActionID,Data["ParkedOrderActionID"].asCString(),sizeof(data.ParkedOrderActionID)-1);
        } else {
            strcpy(data.ParkedOrderActionID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqRemoveParkedOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询产品
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryProduct(std::string jsonString,int requestID)
{
    printf("ReqQryProduct():被执行...\n");


    CThostFtdcQryProductField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///产品代码 char ProductID[31];
        if (!Data["ProductID"].empty()) {
            data.ProductID[sizeof(data.ProductID)-1] = 0;
            strncpy(data.ProductID,Data["ProductID"].asCString(),sizeof(data.ProductID)-1);
        } else {
            strcpy(data.ProductID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryProduct(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询交易编码
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryTradingCode(std::string jsonString,int requestID)
{
    printf("ReqQryTradingCode():被执行...\n");


    CThostFtdcQryTradingCodeField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///客户代码 char ClientID[11];
        if (!Data["ClientID"].empty()) {
            data.ClientID[sizeof(data.ClientID)-1] = 0;
            strncpy(data.ClientID,Data["ClientID"].asCString(),sizeof(data.ClientID)-1);
        } else {
            strcpy(data.ClientID,"");
        }

        ///交易编码类型 char ClientIDType
        if ( !Data["ClientIDType"].empty()) {
            data.ClientIDType = Data["ClientIDType"].asString()[0];
        } else {
            data.ClientIDType = '0';
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingCode(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///资金账户口令更新请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqTradingAccountPasswordUpdate(std::string jsonString,int requestID)
{
    printf("ReqTradingAccountPasswordUpdate():被执行...\n");


    CThostFtdcTradingAccountPasswordUpdateField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者帐号 char AccountID[13];
        if (!Data["AccountID"].empty()) {
            data.AccountID[sizeof(data.AccountID)-1] = 0;
            strncpy(data.AccountID,Data["AccountID"].asCString(),sizeof(data.AccountID)-1);
        } else {
            strcpy(data.AccountID,"");
        }

        ///原来的口令 char OldPassword[41];
        if (!Data["OldPassword"].empty()) {
            data.OldPassword[sizeof(data.OldPassword)-1] = 0;
            strncpy(data.OldPassword,Data["OldPassword"].asCString(),sizeof(data.OldPassword)-1);
        } else {
            strcpy(data.OldPassword,"");
        }

        ///新的口令 char NewPassword[41];
        if (!Data["NewPassword"].empty()) {
            data.NewPassword[sizeof(data.NewPassword)-1] = 0;
            strncpy(data.NewPassword,Data["NewPassword"].asCString(),sizeof(data.NewPassword)-1);
        } else {
            strcpy(data.NewPassword,"");
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqTradingAccountPasswordUpdate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询银期签约关系
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryAccountregister(std::string jsonString,int requestID)
{
    printf("ReqQryAccountregister():被执行...\n");


    CThostFtdcQryAccountregisterField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者帐号 char AccountID[13];
        if (!Data["AccountID"].empty()) {
            data.AccountID[sizeof(data.AccountID)-1] = 0;
            strncpy(data.AccountID,Data["AccountID"].asCString(),sizeof(data.AccountID)-1);
        } else {
            strcpy(data.AccountID,"");
        }

        ///银行编码 char BankID[4];
        if (!Data["BankID"].empty()) {
            data.BankID[sizeof(data.BankID)-1] = 0;
            strncpy(data.BankID,Data["BankID"].asCString(),sizeof(data.BankID)-1);
        } else {
            strcpy(data.BankID,"");
        }

        ///银行分支机构编码 char BankBranchID[5];
        if (!Data["BankBranchID"].empty()) {
            data.BankBranchID[sizeof(data.BankBranchID)-1] = 0;
            strncpy(data.BankBranchID,Data["BankBranchID"].asCString(),sizeof(data.BankBranchID)-1);
        } else {
            strcpy(data.BankBranchID,"");
        }

        ///币种代码 char CurrencyID[4];
        if (!Data["CurrencyID"].empty()) {
            data.CurrencyID[sizeof(data.CurrencyID)-1] = 0;
            strncpy(data.CurrencyID,Data["CurrencyID"].asCString(),sizeof(data.CurrencyID)-1);
        } else {
            strcpy(data.CurrencyID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryAccountregister(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询交易所调整保证金率
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryExchangeMarginRateAdjust(std::string jsonString,int requestID)
{
    printf("ReqQryExchangeMarginRateAdjust():被执行...\n");


    CThostFtdcQryExchangeMarginRateAdjustField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

        ///投机套保标志 char HedgeFlag
        if ( !Data["HedgeFlag"].empty()) {
            data.HedgeFlag = Data["HedgeFlag"].asString()[0];
        } else {
            data.HedgeFlag = '0';
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeMarginRateAdjust(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询仓单折抵信息
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryEWarrantOffset(std::string jsonString,int requestID)
{
    printf("ReqQryEWarrantOffset():被执行...\n");


    CThostFtdcQryEWarrantOffsetField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///交易所代码 char ExchangeID[9];
        if (!Data["ExchangeID"].empty()) {
            data.ExchangeID[sizeof(data.ExchangeID)-1] = 0;
            strncpy(data.ExchangeID,Data["ExchangeID"].asCString(),sizeof(data.ExchangeID)-1);
        } else {
            strcpy(data.ExchangeID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryEWarrantOffset(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求查询投资者持仓明细
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqQryInvestorPositionDetail(std::string jsonString,int requestID)
{
    printf("ReqQryInvestorPositionDetail():被执行...\n");


    CThostFtdcQryInvestorPositionDetailField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///合约代码 char InstrumentID[31];
        if (!Data["InstrumentID"].empty()) {
            data.InstrumentID[sizeof(data.InstrumentID)-1] = 0;
            strncpy(data.InstrumentID,Data["InstrumentID"].asCString(),sizeof(data.InstrumentID)-1);
        } else {
            strcpy(data.InstrumentID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPositionDetail(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}


///请求删除预埋单
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CTraderWrapper::ReqRemoveParkedOrder(std::string jsonString,int requestID)
{
    printf("ReqRemoveParkedOrder():被执行...\n");


    CThostFtdcRemoveParkedOrderField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///投资者代码 char InvestorID[13];
        if (!Data["InvestorID"].empty()) {
            data.InvestorID[sizeof(data.InvestorID)-1] = 0;
            strncpy(data.InvestorID,Data["InvestorID"].asCString(),sizeof(data.InvestorID)-1);
        } else {
            strcpy(data.InvestorID,"");
        }

        ///预埋报单编号 char ParkedOrderID[13];
        if (!Data["ParkedOrderID"].empty()) {
            data.ParkedOrderID[sizeof(data.ParkedOrderID)-1] = 0;
            strncpy(data.ParkedOrderID,Data["ParkedOrderID"].asCString(),sizeof(data.ParkedOrderID)-1);
        } else {
            strcpy(data.ParkedOrderID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    //nRequestID = getNextRequestID();
    nRequestID = requestID;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqRemoveParkedOrder(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}



// 通过名称调用api
int CTraderWrapper::callApiByName(std::string apiName,std::string jsonString,int requestID) {

    if (apiExists(apiName)) {
        return (this->*apiMap[apiName])(jsonString,requestID);
    } else {
        lastErrorID = -1000;
        lastErrorMsg = "没有这个接口函数";
        return -1;
    }
    return 0;

}

bool CTraderWrapper::apiExists(std::string apiName) {

    if ( apiMap.find(apiName) != apiMap.end() ) {
        return true;
    } else {
        return false;
    }

}