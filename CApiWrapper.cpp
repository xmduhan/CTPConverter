
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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///币种代码
    //date.CurrencyID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///用户代码
    //date.UserID = ;
    ///原来的口令
    //date.OldPassword = ;
    ///新的口令
    //date.NewPassword = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///报单操作引用
    //date.OrderActionRef = ;
    ///报单引用
    //date.OrderRef = ;
    ///请求编号
    //date.RequestID = ;
    ///前置编号
    //date.FrontID = ;
    ///会话编号
    //date.SessionID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///报单编号
    //date.OrderSysID = ;
    ///操作标志
    //date.ActionFlag = ;
    ///价格
    //date.LimitPrice = ;
    ///数量变化
    //date.VolumeChange = ;
    ///用户代码
    //date.UserID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///预埋撤单单编号
    //date.ParkedOrderActionID = ;
    ///用户类型
    //date.UserType = ;
    ///预埋撤单状态
    //date.Status = ;
    ///错误代码
    //date.ErrorID = ;
    ///错误信息
    //date.ErrorMsg = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///成交编号
    //date.TradeID = ;
    ///开始时间
    //date.TradeTimeStart = ;
    ///结束时间
    //date.TradeTimeEnd = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///买卖方向
    //date.Direction = ;
    ///开平标志
    //date.OffsetFlag = ;
    ///投机套保标志
    //date.HedgeFlag = ;
    ///最大允许报单数量
    //date.MaxVolume = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///确认日期
    //date.ConfirmDate = ;
    ///确认时间
    //date.ConfirmTime = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///合约代码
    //date.InstrumentID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///报单编号
    //date.OrderSysID = ;
    ///开始时间
    //date.InsertTimeStart = ;
    ///结束时间
    //date.InsertTimeEnd = ;

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

    ///交易所代码
    //date.ExchangeID = ;

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

    ///交易日
    //date.TradingDay = ;
    ///经纪公司代码
    //date.BrokerID = ;
    ///用户代码
    //date.UserID = ;
    ///密码
    //date.Password = ;
    ///用户端产品信息
    //date.UserProductInfo = ;
    ///接口端产品信息
    //date.InterfaceProductInfo = ;
    ///协议信息
    //date.ProtocolInfo = ;
    ///Mac地址
    //date.MacAddress = ;
    ///动态密码
    //date.OneTimePassword = ;
    ///终端IP地址
    //date.ClientIPAddress = ;

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

    ///业务功能码
    //date.TradeCode = ;
    ///银行代码
    //date.BankID = ;
    ///银行分支机构代码
    //date.BankBranchID = ;
    ///期商代码
    //date.BrokerID = ;
    ///期商分支机构代码
    //date.BrokerBranchID = ;
    ///交易日期
    //date.TradeDate = ;
    ///交易时间
    //date.TradeTime = ;
    ///银行流水号
    //date.BankSerial = ;
    ///交易系统日期
    //date.TradingDay = ;
    ///银期平台消息流水号
    //date.PlateSerial = ;
    ///最后分片标志
    //date.LastFragment = ;
    ///会话号
    //date.SessionID = ;
    ///客户姓名
    //date.CustomerName = ;
    ///证件类型
    //date.IdCardType = ;
    ///证件号码
    //date.IdentifiedCardNo = ;
    ///客户类型
    //date.CustType = ;
    ///银行帐号
    //date.BankAccount = ;
    ///银行密码
    //date.BankPassWord = ;
    ///投资者帐号
    //date.AccountID = ;
    ///期货密码
    //date.Password = ;
    ///安装编号
    //date.InstallID = ;
    ///期货公司流水号
    //date.FutureSerial = ;
    ///用户标识
    //date.UserID = ;
    ///验证客户证件号码标志
    //date.VerifyCertNoFlag = ;
    ///币种代码
    //date.CurrencyID = ;
    ///转帐金额
    //date.TradeAmount = ;
    ///期货可取金额
    //date.FutureFetchAmount = ;
    ///费用支付标志
    //date.FeePayFlag = ;
    ///应收客户费用
    //date.CustFee = ;
    ///应收期货公司费用
    //date.BrokerFee = ;
    ///发送方给接收方的消息
    //date.Message = ;
    ///摘要
    //date.Digest = ;
    ///银行帐号类型
    //date.BankAccType = ;
    ///渠道标志
    //date.DeviceID = ;
    ///期货单位帐号类型
    //date.BankSecuAccType = ;
    ///期货公司银行编码
    //date.BrokerIDByBank = ;
    ///期货单位帐号
    //date.BankSecuAcc = ;
    ///银行密码标志
    //date.BankPwdFlag = ;
    ///期货资金密码核对标志
    //date.SecuPwdFlag = ;
    ///交易柜员
    //date.OperNo = ;
    ///请求编号
    //date.RequestID = ;
    ///交易ID
    //date.TID = ;
    ///转账交易状态
    //date.TransferStatus = ;

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

    ///业务功能码
    //date.TradeCode = ;
    ///银行代码
    //date.BankID = ;
    ///银行分支机构代码
    //date.BankBranchID = ;
    ///期商代码
    //date.BrokerID = ;
    ///期商分支机构代码
    //date.BrokerBranchID = ;
    ///交易日期
    //date.TradeDate = ;
    ///交易时间
    //date.TradeTime = ;
    ///银行流水号
    //date.BankSerial = ;
    ///交易系统日期
    //date.TradingDay = ;
    ///银期平台消息流水号
    //date.PlateSerial = ;
    ///最后分片标志
    //date.LastFragment = ;
    ///会话号
    //date.SessionID = ;
    ///客户姓名
    //date.CustomerName = ;
    ///证件类型
    //date.IdCardType = ;
    ///证件号码
    //date.IdentifiedCardNo = ;
    ///客户类型
    //date.CustType = ;
    ///银行帐号
    //date.BankAccount = ;
    ///银行密码
    //date.BankPassWord = ;
    ///投资者帐号
    //date.AccountID = ;
    ///期货密码
    //date.Password = ;
    ///安装编号
    //date.InstallID = ;
    ///期货公司流水号
    //date.FutureSerial = ;
    ///用户标识
    //date.UserID = ;
    ///验证客户证件号码标志
    //date.VerifyCertNoFlag = ;
    ///币种代码
    //date.CurrencyID = ;
    ///转帐金额
    //date.TradeAmount = ;
    ///期货可取金额
    //date.FutureFetchAmount = ;
    ///费用支付标志
    //date.FeePayFlag = ;
    ///应收客户费用
    //date.CustFee = ;
    ///应收期货公司费用
    //date.BrokerFee = ;
    ///发送方给接收方的消息
    //date.Message = ;
    ///摘要
    //date.Digest = ;
    ///银行帐号类型
    //date.BankAccType = ;
    ///渠道标志
    //date.DeviceID = ;
    ///期货单位帐号类型
    //date.BankSecuAccType = ;
    ///期货公司银行编码
    //date.BrokerIDByBank = ;
    ///期货单位帐号
    //date.BankSecuAcc = ;
    ///银行密码标志
    //date.BankPwdFlag = ;
    ///期货资金密码核对标志
    //date.SecuPwdFlag = ;
    ///交易柜员
    //date.OperNo = ;
    ///请求编号
    //date.RequestID = ;
    ///交易ID
    //date.TID = ;
    ///转账交易状态
    //date.TransferStatus = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///币种代码
    //date.CurrencyID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///源币种
    //date.FromCurrencyID = ;
    ///目标币种
    //date.ToCurrencyID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///报单引用
    //date.OrderRef = ;
    ///用户代码
    //date.UserID = ;
    ///报单价格条件
    //date.OrderPriceType = ;
    ///买卖方向
    //date.Direction = ;
    ///组合开平标志
    //date.CombOffsetFlag = ;
    ///组合投机套保标志
    //date.CombHedgeFlag = ;
    ///价格
    //date.LimitPrice = ;
    ///数量
    //date.VolumeTotalOriginal = ;
    ///有效期类型
    //date.TimeCondition = ;
    ///GTD日期
    //date.GTDDate = ;
    ///成交量类型
    //date.VolumeCondition = ;
    ///最小成交量
    //date.MinVolume = ;
    ///触发条件
    //date.ContingentCondition = ;
    ///止损价
    //date.StopPrice = ;
    ///强平原因
    //date.ForceCloseReason = ;
    ///自动挂起标志
    //date.IsAutoSuspend = ;
    ///业务单元
    //date.BusinessUnit = ;
    ///请求编号
    //date.RequestID = ;
    ///用户强评标志
    //date.UserForceClose = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///预埋报单编号
    //date.ParkedOrderID = ;
    ///用户类型
    //date.UserType = ;
    ///预埋单状态
    //date.Status = ;
    ///错误代码
    //date.ErrorID = ;
    ///错误信息
    //date.ErrorMsg = ;
    ///互换单标志
    //date.IsSwapOrder = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///银行代码
    //date.BankID = ;
    ///银行分中心代码
    //date.BankBrchID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///组合持仓合约编码
    //date.CombInstrumentID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///投机套保标志
    //date.HedgeFlag = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///用户代码
    //date.UserID = ;
    ///资金账户
    //date.AccountID = ;
    ///币种
    //date.CurrencyID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者帐号
    //date.AccountID = ;
    ///银行编码
    //date.BankID = ;
    ///币种代码
    //date.CurrencyID = ;

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

    ///业务功能码
    //date.TradeCode = ;
    ///银行代码
    //date.BankID = ;
    ///银行分支机构代码
    //date.BankBranchID = ;
    ///期商代码
    //date.BrokerID = ;
    ///期商分支机构代码
    //date.BrokerBranchID = ;
    ///交易日期
    //date.TradeDate = ;
    ///交易时间
    //date.TradeTime = ;
    ///银行流水号
    //date.BankSerial = ;
    ///交易系统日期
    //date.TradingDay = ;
    ///银期平台消息流水号
    //date.PlateSerial = ;
    ///最后分片标志
    //date.LastFragment = ;
    ///会话号
    //date.SessionID = ;
    ///客户姓名
    //date.CustomerName = ;
    ///证件类型
    //date.IdCardType = ;
    ///证件号码
    //date.IdentifiedCardNo = ;
    ///客户类型
    //date.CustType = ;
    ///银行帐号
    //date.BankAccount = ;
    ///银行密码
    //date.BankPassWord = ;
    ///投资者帐号
    //date.AccountID = ;
    ///期货密码
    //date.Password = ;
    ///期货公司流水号
    //date.FutureSerial = ;
    ///安装编号
    //date.InstallID = ;
    ///用户标识
    //date.UserID = ;
    ///验证客户证件号码标志
    //date.VerifyCertNoFlag = ;
    ///币种代码
    //date.CurrencyID = ;
    ///摘要
    //date.Digest = ;
    ///银行帐号类型
    //date.BankAccType = ;
    ///渠道标志
    //date.DeviceID = ;
    ///期货单位帐号类型
    //date.BankSecuAccType = ;
    ///期货公司银行编码
    //date.BrokerIDByBank = ;
    ///期货单位帐号
    //date.BankSecuAcc = ;
    ///银行密码标志
    //date.BankPwdFlag = ;
    ///期货资金密码核对标志
    //date.SecuPwdFlag = ;
    ///交易柜员
    //date.OperNo = ;
    ///请求编号
    //date.RequestID = ;
    ///交易ID
    //date.TID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///交易所代码
    //date.ExchangeID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///用户代码
    //date.UserID = ;
    ///用户端产品信息
    //date.UserProductInfo = ;
    ///认证码
    //date.AuthCode = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///报单引用
    //date.OrderRef = ;
    ///用户代码
    //date.UserID = ;
    ///报单价格条件
    //date.OrderPriceType = ;
    ///买卖方向
    //date.Direction = ;
    ///组合开平标志
    //date.CombOffsetFlag = ;
    ///组合投机套保标志
    //date.CombHedgeFlag = ;
    ///价格
    //date.LimitPrice = ;
    ///数量
    //date.VolumeTotalOriginal = ;
    ///有效期类型
    //date.TimeCondition = ;
    ///GTD日期
    //date.GTDDate = ;
    ///成交量类型
    //date.VolumeCondition = ;
    ///最小成交量
    //date.MinVolume = ;
    ///触发条件
    //date.ContingentCondition = ;
    ///止损价
    //date.StopPrice = ;
    ///强平原因
    //date.ForceCloseReason = ;
    ///自动挂起标志
    //date.IsAutoSuspend = ;
    ///业务单元
    //date.BusinessUnit = ;
    ///请求编号
    //date.RequestID = ;
    ///用户强评标志
    //date.UserForceClose = ;
    ///互换单标志
    //date.IsSwapOrder = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///交易日
    //date.TradingDay = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///用户代码
    //date.UserID = ;

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

    ///合约代码
    //date.InstrumentID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///合约在交易所的代码
    //date.ExchangeInstID = ;
    ///产品代码
    //date.ProductID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///报单操作引用
    //date.OrderActionRef = ;
    ///报单引用
    //date.OrderRef = ;
    ///请求编号
    //date.RequestID = ;
    ///前置编号
    //date.FrontID = ;
    ///会话编号
    //date.SessionID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///报单编号
    //date.OrderSysID = ;
    ///操作标志
    //date.ActionFlag = ;
    ///价格
    //date.LimitPrice = ;
    ///数量变化
    //date.VolumeChange = ;
    ///用户代码
    //date.UserID = ;
    ///合约代码
    //date.InstrumentID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///投机套保标志
    //date.HedgeFlag = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///交易所代码
    //date.ExchangeID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///品种/跨品种标示
    //date.ProductGroupID = ;
    ///投机套保标志
    //date.HedgeFlag = ;

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

    ///合约代码
    //date.InstrumentID = ;

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

    ///银行代码
    //date.BankID = ;
    ///银行分中心代码
    //date.BankBrchID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///预埋撤单编号
    //date.ParkedOrderActionID = ;

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

    ///产品代码
    //date.ProductID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///客户代码
    //date.ClientID = ;
    ///交易编码类型
    //date.ClientIDType = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者帐号
    //date.AccountID = ;
    ///原来的口令
    //date.OldPassword = ;
    ///新的口令
    //date.NewPassword = ;
    ///币种代码
    //date.CurrencyID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者帐号
    //date.AccountID = ;
    ///银行编码
    //date.BankID = ;
    ///银行分支机构编码
    //date.BankBranchID = ;
    ///币种代码
    //date.CurrencyID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///合约代码
    //date.InstrumentID = ;
    ///投机套保标志
    //date.HedgeFlag = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///交易所代码
    //date.ExchangeID = ;
    ///合约代码
    //date.InstrumentID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///合约代码
    //date.InstrumentID = ;

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

    ///经纪公司代码
    //date.BrokerID = ;
    ///投资者代码
    //date.InvestorID = ;
    ///预埋报单编号
    //date.ParkedOrderID = ;

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqRemoveParkedOrder(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息

    return result;
}
