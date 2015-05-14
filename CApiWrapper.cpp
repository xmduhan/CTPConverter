
#include <CApiWrapper.h>



/// 构造函数
CApiWrapper::CApiWrapper(Configure * pConfigure) {

    // 读取配置数据信息
    this->pConfigure = pConfigure;

    // 创建CTP API工作对象
    pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();

    // 创建SPI工作对象并让其和API关联
    pTraderHandler = new CTraderHandler(pConfigure);
    pTraderApi->RegisterSpi(pTraderHandler);

    // 初始化RequestID序列
    RequestID = 0;

    // 初始化上次出错代码和出错信息
    lastErrorCode = 0;
    strcpy(lastErrorMessage,"");

}

/// 启动CTP连接
void CApiWrapper::init() {

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
    pTraderApi->RegisterFront(pConfigure->FrontAddress);

    // 连接spi的Pushback管道
    printf("pConfigure->PushbackPipe=%s\n",pConfigure->PushbackPipe);
    receiver.connect(pConfigure->PushbackPipe);

    // 连接交易系统
    printf("尝试连接服务器\n");
    pTraderApi->Init();
    // 等待服务器发出OnFrontConnected事件
    message.recv(receiver);
    // 确认收到的返回信息是由OnFrontConnected发出
    assert(message.requestID.compare("0") == 0);
    assert(message.apiName.compare("OnFrontConnected") == 0);
    assert(message.respInfo.compare("") == 0);

    // 发出登陆请求
    CThostFtdcReqUserLoginField userLoginField;
    strcpy(userLoginField.BrokerID,pConfigure->BrokerID);
    strcpy(userLoginField.UserID,pConfigure->UserID);
    strcpy(userLoginField.Password,pConfigure->Password);
    pTraderApi->ReqUserLogin(&userLoginField,getNextRequestID());

    // 等待登录成功返回信息
    message.recv(receiver);
    assert(message.requestID.compare("1") == 0);
    assert(message.apiName.compare("OnRspUserLogin") == 0);
    assert(message.respInfo.compare("") == 0);
    // TODO : 这里需要检查登录是否成功

    printf("Init():执行完毕\n");
}


/// 获取下一个RequestID序列
int CApiWrapper::getNextRequestID() {
    return 	++this->RequestID;
}

/// 获取当前RequestID序列
int CApiWrapper::getCurrentRequestID() {
    return 	this->RequestID;
}

/// 获取上次出错代码
int CApiWrapper::getLastErrorCode() {
    return lastErrorCode;
}

/// 获取上次错误信息
char * CApiWrapper::getLastErrorMessage() {
    return lastErrorMessage;
}


/* TODO:这里两个函数要实现到CTraderHandler中去

// 允许登录事件
virtual void OnFrontConnected() {
    static int i = 0;
    printf("OnFrontConnected():被执行...\n");
    // 在登出后系统会重新调用OnFrontConnected，这里简单判断并忽略第1次之后的所有调用。
    if (i++==0) {
        sem_post(&sem);
    }
}

// 登录结果响应
virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    printf("OnRspUserLogin():被执行...\n");
    if (pRspInfo->ErrorID == 0) {
        printf("登录成功!\n");
        sem_post(&sem);
    } else {
        printf("登录失败!\n");
    }
}
*/



///请求查询资金账户
int CApiWrapper::ReqQryTradingAccount(char * pJsonData )
{
    printf("ReqQryTradingAccount():被执行...\n");

    CThostFtdcQryTradingAccountField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingAccount(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询保证金监管系统经纪公司资金账户密钥
int CApiWrapper::ReqQryCFMMCTradingAccountKey(char * pJsonData )
{
    printf("ReqQryCFMMCTradingAccountKey():被执行...\n");

    CThostFtdcQryCFMMCTradingAccountKeyField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryCFMMCTradingAccountKey(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///用户口令更新请求
int CApiWrapper::ReqUserPasswordUpdate(char * pJsonData )
{
    printf("ReqUserPasswordUpdate():被执行...\n");

    CThostFtdcUserPasswordUpdateField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///原来的口令 char OldPassword[41];
    ////////////// 字符串类型的处理	//////////////

    ///新的口令 char NewPassword[41];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserPasswordUpdate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///预埋撤单录入请求
int CApiWrapper::ReqParkedOrderAction(char * pJsonData )
{
    printf("ReqParkedOrderAction():被执行...\n");

    CThostFtdcParkedOrderActionField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///报单操作引用 int OrderActionRef
    ////////////// int 类型赋值处理 //////////////

    ///报单引用 char OrderRef[13];
    ////////////// 字符串类型的处理	//////////////

    ///请求编号 int RequestID
    ////////////// int 类型赋值处理 //////////////

    ///前置编号 int FrontID
    ////////////// int 类型赋值处理 //////////////

    ///会话编号 int SessionID
    ////////////// int 类型赋值处理 //////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///报单编号 char OrderSysID[21];
    ////////////// 字符串类型的处理	//////////////

    ///操作标志 char ActionFlag
    ////////////// char 类型赋值处理 //////////////

    ///价格 double LimitPrice
    ////////////// double 类型赋值处理 //////////////

    ///数量变化 int VolumeChange
    ////////////// int 类型赋值处理 //////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///预埋撤单单编号 char ParkedOrderActionID[13];
    ////////////// 字符串类型的处理	//////////////

    ///用户类型 char UserType
    ////////////// char 类型赋值处理 //////////////

    ///预埋撤单状态 char Status
    ////////////// char 类型赋值处理 //////////////

    ///错误代码 int ErrorID
    ////////////// int 类型赋值处理 //////////////

    ///错误信息 char ErrorMsg[81];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqParkedOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询交易通知
int CApiWrapper::ReqQryTradingNotice(char * pJsonData )
{
    printf("ReqQryTradingNotice():被执行...\n");

    CThostFtdcQryTradingNoticeField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingNotice(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询成交
int CApiWrapper::ReqQryTrade(char * pJsonData )
{
    printf("ReqQryTrade():被执行...\n");

    CThostFtdcQryTradeField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///成交编号 char TradeID[21];
    ////////////// 字符串类型的处理	//////////////

    ///开始时间 char TradeTimeStart[9];
    ////////////// 字符串类型的处理	//////////////

    ///结束时间 char TradeTimeEnd[9];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTrade(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///查询最大报单数量请求
int CApiWrapper::ReqQueryMaxOrderVolume(char * pJsonData )
{
    printf("ReqQueryMaxOrderVolume():被执行...\n");

    CThostFtdcQueryMaxOrderVolumeField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///买卖方向 char Direction
    ////////////// char 类型赋值处理 //////////////

    ///开平标志 char OffsetFlag
    ////////////// char 类型赋值处理 //////////////

    ///投机套保标志 char HedgeFlag
    ////////////// char 类型赋值处理 //////////////

    ///最大允许报单数量 int MaxVolume
    ////////////// int 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryMaxOrderVolume(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///投资者结算结果确认
int CApiWrapper::ReqSettlementInfoConfirm(char * pJsonData )
{
    printf("ReqSettlementInfoConfirm():被执行...\n");

    CThostFtdcSettlementInfoConfirmField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///确认日期 char ConfirmDate[9];
    ////////////// 字符串类型的处理	//////////////

    ///确认时间 char ConfirmTime[9];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqSettlementInfoConfirm(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询投资者持仓
int CApiWrapper::ReqQryInvestorPosition(char * pJsonData )
{
    printf("ReqQryInvestorPosition():被执行...\n");

    CThostFtdcQryInvestorPositionField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPosition(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询经纪公司交易算法
int CApiWrapper::ReqQryBrokerTradingAlgos(char * pJsonData )
{
    printf("ReqQryBrokerTradingAlgos():被执行...\n");

    CThostFtdcQryBrokerTradingAlgosField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryBrokerTradingAlgos(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询报单
int CApiWrapper::ReqQryOrder(char * pJsonData )
{
    printf("ReqQryOrder():被执行...\n");

    CThostFtdcQryOrderField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///报单编号 char OrderSysID[21];
    ////////////// 字符串类型的处理	//////////////

    ///开始时间 char InsertTimeStart[9];
    ////////////// 字符串类型的处理	//////////////

    ///结束时间 char InsertTimeEnd[9];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryOrder(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询交易所
int CApiWrapper::ReqQryExchange(char * pJsonData )
{
    printf("ReqQryExchange():被执行...\n");

    CThostFtdcQryExchangeField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchange(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///用户登录请求
int CApiWrapper::ReqUserLogin(char * pJsonData )
{
    printf("ReqUserLogin():被执行...\n");

    CThostFtdcReqUserLoginField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///交易日 char TradingDay[9];
    ////////////// 字符串类型的处理	//////////////

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///密码 char Password[41];
    ////////////// 字符串类型的处理	//////////////

    ///用户端产品信息 char UserProductInfo[11];
    ////////////// 字符串类型的处理	//////////////

    ///接口端产品信息 char InterfaceProductInfo[11];
    ////////////// 字符串类型的处理	//////////////

    ///协议信息 char ProtocolInfo[11];
    ////////////// 字符串类型的处理	//////////////

    ///Mac地址 char MacAddress[21];
    ////////////// 字符串类型的处理	//////////////

    ///动态密码 char OneTimePassword[41];
    ////////////// 字符串类型的处理	//////////////

    ///终端IP地址 char ClientIPAddress[16];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserLogin(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///期货发起期货资金转银行请求
int CApiWrapper::ReqFromFutureToBankByFuture(char * pJsonData )
{
    printf("ReqFromFutureToBankByFuture():被执行...\n");

    CThostFtdcReqTransferField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///业务功能码 char TradeCode[7];
    ////////////// 字符串类型的处理	//////////////

    ///银行代码 char BankID[4];
    ////////////// 字符串类型的处理	//////////////

    ///银行分支机构代码 char BankBranchID[5];
    ////////////// 字符串类型的处理	//////////////

    ///期商代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///期商分支机构代码 char BrokerBranchID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易日期 char TradeDate[9];
    ////////////// 字符串类型的处理	//////////////

    ///交易时间 char TradeTime[9];
    ////////////// 字符串类型的处理	//////////////

    ///银行流水号 char BankSerial[13];
    ////////////// 字符串类型的处理	//////////////

    ///交易系统日期 char TradingDay[9];
    ////////////// 字符串类型的处理	//////////////

    ///银期平台消息流水号 int PlateSerial
    ////////////// int 类型赋值处理 //////////////

    ///最后分片标志 char LastFragment
    ////////////// char 类型赋值处理 //////////////

    ///会话号 int SessionID
    ////////////// int 类型赋值处理 //////////////

    ///客户姓名 char CustomerName[51];
    ////////////// 字符串类型的处理	//////////////

    ///证件类型 char IdCardType
    ////////////// char 类型赋值处理 //////////////

    ///证件号码 char IdentifiedCardNo[51];
    ////////////// 字符串类型的处理	//////////////

    ///客户类型 char CustType
    ////////////// char 类型赋值处理 //////////////

    ///银行帐号 char BankAccount[41];
    ////////////// 字符串类型的处理	//////////////

    ///银行密码 char BankPassWord[41];
    ////////////// 字符串类型的处理	//////////////

    ///投资者帐号 char AccountID[13];
    ////////////// 字符串类型的处理	//////////////

    ///期货密码 char Password[41];
    ////////////// 字符串类型的处理	//////////////

    ///安装编号 int InstallID
    ////////////// int 类型赋值处理 //////////////

    ///期货公司流水号 int FutureSerial
    ////////////// int 类型赋值处理 //////////////

    ///用户标识 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///验证客户证件号码标志 char VerifyCertNoFlag
    ////////////// char 类型赋值处理 //////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////

    ///转帐金额 double TradeAmount
    ////////////// double 类型赋值处理 //////////////

    ///期货可取金额 double FutureFetchAmount
    ////////////// double 类型赋值处理 //////////////

    ///费用支付标志 char FeePayFlag
    ////////////// char 类型赋值处理 //////////////

    ///应收客户费用 double CustFee
    ////////////// double 类型赋值处理 //////////////

    ///应收期货公司费用 double BrokerFee
    ////////////// double 类型赋值处理 //////////////

    ///发送方给接收方的消息 char Message[129];
    ////////////// 字符串类型的处理	//////////////

    ///摘要 char Digest[36];
    ////////////// 字符串类型的处理	//////////////

    ///银行帐号类型 char BankAccType
    ////////////// char 类型赋值处理 //////////////

    ///渠道标志 char DeviceID[3];
    ////////////// 字符串类型的处理	//////////////

    ///期货单位帐号类型 char BankSecuAccType
    ////////////// char 类型赋值处理 //////////////

    ///期货公司银行编码 char BrokerIDByBank[33];
    ////////////// 字符串类型的处理	//////////////

    ///期货单位帐号 char BankSecuAcc[41];
    ////////////// 字符串类型的处理	//////////////

    ///银行密码标志 char BankPwdFlag
    ////////////// char 类型赋值处理 //////////////

    ///期货资金密码核对标志 char SecuPwdFlag
    ////////////// char 类型赋值处理 //////////////

    ///交易柜员 char OperNo[17];
    ////////////// 字符串类型的处理	//////////////

    ///请求编号 int RequestID
    ////////////// int 类型赋值处理 //////////////

    ///交易ID int TID
    ////////////// int 类型赋值处理 //////////////

    ///转账交易状态 char TransferStatus
    ////////////// char 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqFromFutureToBankByFuture(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///期货发起银行资金转期货请求
int CApiWrapper::ReqFromBankToFutureByFuture(char * pJsonData )
{
    printf("ReqFromBankToFutureByFuture():被执行...\n");

    CThostFtdcReqTransferField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///业务功能码 char TradeCode[7];
    ////////////// 字符串类型的处理	//////////////

    ///银行代码 char BankID[4];
    ////////////// 字符串类型的处理	//////////////

    ///银行分支机构代码 char BankBranchID[5];
    ////////////// 字符串类型的处理	//////////////

    ///期商代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///期商分支机构代码 char BrokerBranchID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易日期 char TradeDate[9];
    ////////////// 字符串类型的处理	//////////////

    ///交易时间 char TradeTime[9];
    ////////////// 字符串类型的处理	//////////////

    ///银行流水号 char BankSerial[13];
    ////////////// 字符串类型的处理	//////////////

    ///交易系统日期 char TradingDay[9];
    ////////////// 字符串类型的处理	//////////////

    ///银期平台消息流水号 int PlateSerial
    ////////////// int 类型赋值处理 //////////////

    ///最后分片标志 char LastFragment
    ////////////// char 类型赋值处理 //////////////

    ///会话号 int SessionID
    ////////////// int 类型赋值处理 //////////////

    ///客户姓名 char CustomerName[51];
    ////////////// 字符串类型的处理	//////////////

    ///证件类型 char IdCardType
    ////////////// char 类型赋值处理 //////////////

    ///证件号码 char IdentifiedCardNo[51];
    ////////////// 字符串类型的处理	//////////////

    ///客户类型 char CustType
    ////////////// char 类型赋值处理 //////////////

    ///银行帐号 char BankAccount[41];
    ////////////// 字符串类型的处理	//////////////

    ///银行密码 char BankPassWord[41];
    ////////////// 字符串类型的处理	//////////////

    ///投资者帐号 char AccountID[13];
    ////////////// 字符串类型的处理	//////////////

    ///期货密码 char Password[41];
    ////////////// 字符串类型的处理	//////////////

    ///安装编号 int InstallID
    ////////////// int 类型赋值处理 //////////////

    ///期货公司流水号 int FutureSerial
    ////////////// int 类型赋值处理 //////////////

    ///用户标识 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///验证客户证件号码标志 char VerifyCertNoFlag
    ////////////// char 类型赋值处理 //////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////

    ///转帐金额 double TradeAmount
    ////////////// double 类型赋值处理 //////////////

    ///期货可取金额 double FutureFetchAmount
    ////////////// double 类型赋值处理 //////////////

    ///费用支付标志 char FeePayFlag
    ////////////// char 类型赋值处理 //////////////

    ///应收客户费用 double CustFee
    ////////////// double 类型赋值处理 //////////////

    ///应收期货公司费用 double BrokerFee
    ////////////// double 类型赋值处理 //////////////

    ///发送方给接收方的消息 char Message[129];
    ////////////// 字符串类型的处理	//////////////

    ///摘要 char Digest[36];
    ////////////// 字符串类型的处理	//////////////

    ///银行帐号类型 char BankAccType
    ////////////// char 类型赋值处理 //////////////

    ///渠道标志 char DeviceID[3];
    ////////////// 字符串类型的处理	//////////////

    ///期货单位帐号类型 char BankSecuAccType
    ////////////// char 类型赋值处理 //////////////

    ///期货公司银行编码 char BrokerIDByBank[33];
    ////////////// 字符串类型的处理	//////////////

    ///期货单位帐号 char BankSecuAcc[41];
    ////////////// 字符串类型的处理	//////////////

    ///银行密码标志 char BankPwdFlag
    ////////////// char 类型赋值处理 //////////////

    ///期货资金密码核对标志 char SecuPwdFlag
    ////////////// char 类型赋值处理 //////////////

    ///交易柜员 char OperNo[17];
    ////////////// 字符串类型的处理	//////////////

    ///请求编号 int RequestID
    ////////////// int 类型赋值处理 //////////////

    ///交易ID int TID
    ////////////// int 类型赋值处理 //////////////

    ///转账交易状态 char TransferStatus
    ////////////// char 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqFromBankToFutureByFuture(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询结算信息确认
int CApiWrapper::ReqQrySettlementInfoConfirm(char * pJsonData )
{
    printf("ReqQrySettlementInfoConfirm():被执行...\n");

    CThostFtdcQrySettlementInfoConfirmField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySettlementInfoConfirm(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询经纪公司交易参数
int CApiWrapper::ReqQryBrokerTradingParams(char * pJsonData )
{
    printf("ReqQryBrokerTradingParams():被执行...\n");

    CThostFtdcQryBrokerTradingParamsField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryBrokerTradingParams(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询监控中心用户令牌
int CApiWrapper::ReqQueryCFMMCTradingAccountToken(char * pJsonData )
{
    printf("ReqQueryCFMMCTradingAccountToken():被执行...\n");

    CThostFtdcQueryCFMMCTradingAccountTokenField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryCFMMCTradingAccountToken(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询客户通知
int CApiWrapper::ReqQryNotice(char * pJsonData )
{
    printf("ReqQryNotice():被执行...\n");

    CThostFtdcQryNoticeField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryNotice(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询汇率
int CApiWrapper::ReqQryExchangeRate(char * pJsonData )
{
    printf("ReqQryExchangeRate():被执行...\n");

    CThostFtdcQryExchangeRateField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///源币种 char FromCurrencyID[4];
    ////////////// 字符串类型的处理	//////////////

    ///目标币种 char ToCurrencyID[4];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///预埋单录入请求
int CApiWrapper::ReqParkedOrderInsert(char * pJsonData )
{
    printf("ReqParkedOrderInsert():被执行...\n");

    CThostFtdcParkedOrderField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///报单引用 char OrderRef[13];
    ////////////// 字符串类型的处理	//////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///报单价格条件 char OrderPriceType
    ////////////// char 类型赋值处理 //////////////

    ///买卖方向 char Direction
    ////////////// char 类型赋值处理 //////////////

    ///组合开平标志 char CombOffsetFlag[5];
    ////////////// 字符串类型的处理	//////////////

    ///组合投机套保标志 char CombHedgeFlag[5];
    ////////////// 字符串类型的处理	//////////////

    ///价格 double LimitPrice
    ////////////// double 类型赋值处理 //////////////

    ///数量 int VolumeTotalOriginal
    ////////////// int 类型赋值处理 //////////////

    ///有效期类型 char TimeCondition
    ////////////// char 类型赋值处理 //////////////

    ///GTD日期 char GTDDate[9];
    ////////////// 字符串类型的处理	//////////////

    ///成交量类型 char VolumeCondition
    ////////////// char 类型赋值处理 //////////////

    ///最小成交量 int MinVolume
    ////////////// int 类型赋值处理 //////////////

    ///触发条件 char ContingentCondition
    ////////////// char 类型赋值处理 //////////////

    ///止损价 double StopPrice
    ////////////// double 类型赋值处理 //////////////

    ///强平原因 char ForceCloseReason
    ////////////// char 类型赋值处理 //////////////

    ///自动挂起标志 int IsAutoSuspend
    ////////////// int 类型赋值处理 //////////////

    ///业务单元 char BusinessUnit[21];
    ////////////// 字符串类型的处理	//////////////

    ///请求编号 int RequestID
    ////////////// int 类型赋值处理 //////////////

    ///用户强评标志 int UserForceClose
    ////////////// int 类型赋值处理 //////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///预埋报单编号 char ParkedOrderID[13];
    ////////////// 字符串类型的处理	//////////////

    ///用户类型 char UserType
    ////////////// char 类型赋值处理 //////////////

    ///预埋单状态 char Status
    ////////////// char 类型赋值处理 //////////////

    ///错误代码 int ErrorID
    ////////////// int 类型赋值处理 //////////////

    ///错误信息 char ErrorMsg[81];
    ////////////// 字符串类型的处理	//////////////

    ///互换单标志 int IsSwapOrder
    ////////////// int 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqParkedOrderInsert(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询签约银行
int CApiWrapper::ReqQryContractBank(char * pJsonData )
{
    printf("ReqQryContractBank():被执行...\n");

    CThostFtdcQryContractBankField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///银行代码 char BankID[4];
    ////////////// 字符串类型的处理	//////////////

    ///银行分中心代码 char BankBrchID[5];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryContractBank(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询投资者持仓明细
int CApiWrapper::ReqQryInvestorPositionCombineDetail(char * pJsonData )
{
    printf("ReqQryInvestorPositionCombineDetail():被执行...\n");

    CThostFtdcQryInvestorPositionCombineDetailField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///组合持仓合约编码 char CombInstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPositionCombineDetail(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询交易所保证金率
int CApiWrapper::ReqQryExchangeMarginRate(char * pJsonData )
{
    printf("ReqQryExchangeMarginRate():被执行...\n");

    CThostFtdcQryExchangeMarginRateField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///投机套保标志 char HedgeFlag
    ////////////// char 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeMarginRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询二级代理操作员银期权限
int CApiWrapper::ReqQrySecAgentACIDMap(char * pJsonData )
{
    printf("ReqQrySecAgentACIDMap():被执行...\n");

    CThostFtdcQrySecAgentACIDMapField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///资金账户 char AccountID[13];
    ////////////// 字符串类型的处理	//////////////

    ///币种 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySecAgentACIDMap(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询转帐流水
int CApiWrapper::ReqQryTransferSerial(char * pJsonData )
{
    printf("ReqQryTransferSerial():被执行...\n");

    CThostFtdcQryTransferSerialField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者帐号 char AccountID[13];
    ////////////// 字符串类型的处理	//////////////

    ///银行编码 char BankID[4];
    ////////////// 字符串类型的处理	//////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTransferSerial(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///期货发起查询银行余额请求
int CApiWrapper::ReqQueryBankAccountMoneyByFuture(char * pJsonData )
{
    printf("ReqQueryBankAccountMoneyByFuture():被执行...\n");

    CThostFtdcReqQueryAccountField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///业务功能码 char TradeCode[7];
    ////////////// 字符串类型的处理	//////////////

    ///银行代码 char BankID[4];
    ////////////// 字符串类型的处理	//////////////

    ///银行分支机构代码 char BankBranchID[5];
    ////////////// 字符串类型的处理	//////////////

    ///期商代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///期商分支机构代码 char BrokerBranchID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易日期 char TradeDate[9];
    ////////////// 字符串类型的处理	//////////////

    ///交易时间 char TradeTime[9];
    ////////////// 字符串类型的处理	//////////////

    ///银行流水号 char BankSerial[13];
    ////////////// 字符串类型的处理	//////////////

    ///交易系统日期 char TradingDay[9];
    ////////////// 字符串类型的处理	//////////////

    ///银期平台消息流水号 int PlateSerial
    ////////////// int 类型赋值处理 //////////////

    ///最后分片标志 char LastFragment
    ////////////// char 类型赋值处理 //////////////

    ///会话号 int SessionID
    ////////////// int 类型赋值处理 //////////////

    ///客户姓名 char CustomerName[51];
    ////////////// 字符串类型的处理	//////////////

    ///证件类型 char IdCardType
    ////////////// char 类型赋值处理 //////////////

    ///证件号码 char IdentifiedCardNo[51];
    ////////////// 字符串类型的处理	//////////////

    ///客户类型 char CustType
    ////////////// char 类型赋值处理 //////////////

    ///银行帐号 char BankAccount[41];
    ////////////// 字符串类型的处理	//////////////

    ///银行密码 char BankPassWord[41];
    ////////////// 字符串类型的处理	//////////////

    ///投资者帐号 char AccountID[13];
    ////////////// 字符串类型的处理	//////////////

    ///期货密码 char Password[41];
    ////////////// 字符串类型的处理	//////////////

    ///期货公司流水号 int FutureSerial
    ////////////// int 类型赋值处理 //////////////

    ///安装编号 int InstallID
    ////////////// int 类型赋值处理 //////////////

    ///用户标识 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///验证客户证件号码标志 char VerifyCertNoFlag
    ////////////// char 类型赋值处理 //////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////

    ///摘要 char Digest[36];
    ////////////// 字符串类型的处理	//////////////

    ///银行帐号类型 char BankAccType
    ////////////// char 类型赋值处理 //////////////

    ///渠道标志 char DeviceID[3];
    ////////////// 字符串类型的处理	//////////////

    ///期货单位帐号类型 char BankSecuAccType
    ////////////// char 类型赋值处理 //////////////

    ///期货公司银行编码 char BrokerIDByBank[33];
    ////////////// 字符串类型的处理	//////////////

    ///期货单位帐号 char BankSecuAcc[41];
    ////////////// 字符串类型的处理	//////////////

    ///银行密码标志 char BankPwdFlag
    ////////////// char 类型赋值处理 //////////////

    ///期货资金密码核对标志 char SecuPwdFlag
    ////////////// char 类型赋值处理 //////////////

    ///交易柜员 char OperNo[17];
    ////////////// 字符串类型的处理	//////////////

    ///请求编号 int RequestID
    ////////////// int 类型赋值处理 //////////////

    ///交易ID int TID
    ////////////// int 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryBankAccountMoneyByFuture(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询预埋撤单
int CApiWrapper::ReqQryParkedOrderAction(char * pJsonData )
{
    printf("ReqQryParkedOrderAction():被执行...\n");

    CThostFtdcQryParkedOrderActionField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryParkedOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///客户端认证请求
int CApiWrapper::ReqAuthenticate(char * pJsonData )
{
    printf("ReqAuthenticate():被执行...\n");

    CThostFtdcReqAuthenticateField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///用户端产品信息 char UserProductInfo[11];
    ////////////// 字符串类型的处理	//////////////

    ///认证码 char AuthCode[17];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqAuthenticate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///报单录入请求
int CApiWrapper::ReqOrderInsert(char * pJsonData )
{
    printf("ReqOrderInsert():被执行...\n");

    CThostFtdcInputOrderField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///报单引用 char OrderRef[13];
    ////////////// 字符串类型的处理	//////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///报单价格条件 char OrderPriceType
    ////////////// char 类型赋值处理 //////////////

    ///买卖方向 char Direction
    ////////////// char 类型赋值处理 //////////////

    ///组合开平标志 char CombOffsetFlag[5];
    ////////////// 字符串类型的处理	//////////////

    ///组合投机套保标志 char CombHedgeFlag[5];
    ////////////// 字符串类型的处理	//////////////

    ///价格 double LimitPrice
    ////////////// double 类型赋值处理 //////////////

    ///数量 int VolumeTotalOriginal
    ////////////// int 类型赋值处理 //////////////

    ///有效期类型 char TimeCondition
    ////////////// char 类型赋值处理 //////////////

    ///GTD日期 char GTDDate[9];
    ////////////// 字符串类型的处理	//////////////

    ///成交量类型 char VolumeCondition
    ////////////// char 类型赋值处理 //////////////

    ///最小成交量 int MinVolume
    ////////////// int 类型赋值处理 //////////////

    ///触发条件 char ContingentCondition
    ////////////// char 类型赋值处理 //////////////

    ///止损价 double StopPrice
    ////////////// double 类型赋值处理 //////////////

    ///强平原因 char ForceCloseReason
    ////////////// char 类型赋值处理 //////////////

    ///自动挂起标志 int IsAutoSuspend
    ////////////// int 类型赋值处理 //////////////

    ///业务单元 char BusinessUnit[21];
    ////////////// 字符串类型的处理	//////////////

    ///请求编号 int RequestID
    ////////////// int 类型赋值处理 //////////////

    ///用户强评标志 int UserForceClose
    ////////////// int 类型赋值处理 //////////////

    ///互换单标志 int IsSwapOrder
    ////////////// int 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqOrderInsert(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询投资者结算结果
int CApiWrapper::ReqQrySettlementInfo(char * pJsonData )
{
    printf("ReqQrySettlementInfo():被执行...\n");

    CThostFtdcQrySettlementInfoField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///交易日 char TradingDay[9];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySettlementInfo(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///登出请求
int CApiWrapper::ReqUserLogout(char * pJsonData )
{
    printf("ReqUserLogout():被执行...\n");

    CThostFtdcUserLogoutField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserLogout(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询合约
int CApiWrapper::ReqQryInstrument(char * pJsonData )
{
    printf("ReqQryInstrument():被执行...\n");

    CThostFtdcQryInstrumentField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///合约在交易所的代码 char ExchangeInstID[31];
    ////////////// 字符串类型的处理	//////////////

    ///产品代码 char ProductID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrument(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///报单操作请求
int CApiWrapper::ReqOrderAction(char * pJsonData )
{
    printf("ReqOrderAction():被执行...\n");

    CThostFtdcInputOrderActionField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///报单操作引用 int OrderActionRef
    ////////////// int 类型赋值处理 //////////////

    ///报单引用 char OrderRef[13];
    ////////////// 字符串类型的处理	//////////////

    ///请求编号 int RequestID
    ////////////// int 类型赋值处理 //////////////

    ///前置编号 int FrontID
    ////////////// int 类型赋值处理 //////////////

    ///会话编号 int SessionID
    ////////////// int 类型赋值处理 //////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///报单编号 char OrderSysID[21];
    ////////////// 字符串类型的处理	//////////////

    ///操作标志 char ActionFlag
    ////////////// char 类型赋值处理 //////////////

    ///价格 double LimitPrice
    ////////////// double 类型赋值处理 //////////////

    ///数量变化 int VolumeChange
    ////////////// int 类型赋值处理 //////////////

    ///用户代码 char UserID[16];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询合约手续费率
int CApiWrapper::ReqQryInstrumentCommissionRate(char * pJsonData )
{
    printf("ReqQryInstrumentCommissionRate():被执行...\n");

    CThostFtdcQryInstrumentCommissionRateField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrumentCommissionRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询合约保证金率
int CApiWrapper::ReqQryInstrumentMarginRate(char * pJsonData )
{
    printf("ReqQryInstrumentMarginRate():被执行...\n");

    CThostFtdcQryInstrumentMarginRateField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///投机套保标志 char HedgeFlag
    ////////////// char 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrumentMarginRate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询投资者
int CApiWrapper::ReqQryInvestor(char * pJsonData )
{
    printf("ReqQryInvestor():被执行...\n");

    CThostFtdcQryInvestorField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestor(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询预埋单
int CApiWrapper::ReqQryParkedOrder(char * pJsonData )
{
    printf("ReqQryParkedOrder():被执行...\n");

    CThostFtdcQryParkedOrderField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryParkedOrder(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询投资者品种/跨品种保证金
int CApiWrapper::ReqQryInvestorProductGroupMargin(char * pJsonData )
{
    printf("ReqQryInvestorProductGroupMargin():被执行...\n");

    CThostFtdcQryInvestorProductGroupMarginField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///品种/跨品种标示 char ProductGroupID[31];
    ////////////// 字符串类型的处理	//////////////

    ///投机套保标志 char HedgeFlag
    ////////////// char 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorProductGroupMargin(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询行情
int CApiWrapper::ReqQryDepthMarketData(char * pJsonData )
{
    printf("ReqQryDepthMarketData():被执行...\n");

    CThostFtdcQryDepthMarketDataField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryDepthMarketData(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询转帐银行
int CApiWrapper::ReqQryTransferBank(char * pJsonData )
{
    printf("ReqQryTransferBank():被执行...\n");

    CThostFtdcQryTransferBankField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///银行代码 char BankID[4];
    ////////////// 字符串类型的处理	//////////////

    ///银行分中心代码 char BankBrchID[5];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTransferBank(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求删除预埋撤单
int CApiWrapper::ReqRemoveParkedOrderAction(char * pJsonData )
{
    printf("ReqRemoveParkedOrderAction():被执行...\n");

    CThostFtdcRemoveParkedOrderActionField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///预埋撤单编号 char ParkedOrderActionID[13];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqRemoveParkedOrderAction(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询产品
int CApiWrapper::ReqQryProduct(char * pJsonData )
{
    printf("ReqQryProduct():被执行...\n");

    CThostFtdcQryProductField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///产品代码 char ProductID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryProduct(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询交易编码
int CApiWrapper::ReqQryTradingCode(char * pJsonData )
{
    printf("ReqQryTradingCode():被执行...\n");

    CThostFtdcQryTradingCodeField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///客户代码 char ClientID[11];
    ////////////// 字符串类型的处理	//////////////

    ///交易编码类型 char ClientIDType
    ////////////// char 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingCode(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///资金账户口令更新请求
int CApiWrapper::ReqTradingAccountPasswordUpdate(char * pJsonData )
{
    printf("ReqTradingAccountPasswordUpdate():被执行...\n");

    CThostFtdcTradingAccountPasswordUpdateField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者帐号 char AccountID[13];
    ////////////// 字符串类型的处理	//////////////

    ///原来的口令 char OldPassword[41];
    ////////////// 字符串类型的处理	//////////////

    ///新的口令 char NewPassword[41];
    ////////////// 字符串类型的处理	//////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqTradingAccountPasswordUpdate(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询银期签约关系
int CApiWrapper::ReqQryAccountregister(char * pJsonData )
{
    printf("ReqQryAccountregister():被执行...\n");

    CThostFtdcQryAccountregisterField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者帐号 char AccountID[13];
    ////////////// 字符串类型的处理	//////////////

    ///银行编码 char BankID[4];
    ////////////// 字符串类型的处理	//////////////

    ///银行分支机构编码 char BankBranchID[5];
    ////////////// 字符串类型的处理	//////////////

    ///币种代码 char CurrencyID[4];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryAccountregister(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询交易所调整保证金率
int CApiWrapper::ReqQryExchangeMarginRateAdjust(char * pJsonData )
{
    printf("ReqQryExchangeMarginRateAdjust():被执行...\n");

    CThostFtdcQryExchangeMarginRateAdjustField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////

    ///投机套保标志 char HedgeFlag
    ////////////// char 类型赋值处理 //////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeMarginRateAdjust(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询仓单折抵信息
int CApiWrapper::ReqQryEWarrantOffset(char * pJsonData )
{
    printf("ReqQryEWarrantOffset():被执行...\n");

    CThostFtdcQryEWarrantOffsetField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///交易所代码 char ExchangeID[9];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryEWarrantOffset(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求查询投资者持仓明细
int CApiWrapper::ReqQryInvestorPositionDetail(char * pJsonData )
{
    printf("ReqQryInvestorPositionDetail():被执行...\n");

    CThostFtdcQryInvestorPositionDetailField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///合约代码 char InstrumentID[31];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPositionDetail(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}

///请求删除预埋单
int CApiWrapper::ReqRemoveParkedOrder(char * pJsonData )
{
    printf("ReqRemoveParkedOrder():被执行...\n");

    CThostFtdcRemoveParkedOrderField data;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    ///经纪公司代码 char BrokerID[11];
    ////////////// 字符串类型的处理	//////////////

    ///投资者代码 char InvestorID[13];
    ////////////// 字符串类型的处理	//////////////

    ///预埋报单编号 char ParkedOrderID[13];
    ////////////// 字符串类型的处理	//////////////


    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqRemoveParkedOrder(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}
