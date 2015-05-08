
#include <CApiWrapper.h>
#include <stdio.h>
#include <string.h>


/// 构造函数
CApiWrapper::CApiWrapper(Configure * pConfigure) {

    // 读取配置数据信息
    this->pConfigure = pConfigure;

    // 创建CTP API工作对象
    this->pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();

    // 创建SPI工作对象并让其和API关联
    this->pTraderHandler = new CTraderHandler();
    pTraderApi->RegisterSpi(pTraderHandler);

    // 初始化RequestID序列
    this->RequestID = 0;
}

/// 启动CTP连接
void CApiWrapper::init() {

    //Configure * pConfigure = this->pConfigure;
    //设置服务信息推送信息
    // 订阅相关信息推送
    //// THOST_TERT_RESTART:从本交易日开始重传
    //// THOST_TERT_RESUME:从上次收到的续传
    //// THOST_TERT_QUICK:只传送登录后私有流的内容
    pTraderApi->SubscribePrivateTopic(THOST_TERT_RESUME);
    // 订阅公共流
    //// THOST_TERT_RESTART:从本交易日开始重传
    //// THOST_TERT_RESUME:从上次收到的续传
    //// THOST_TERT_QUICK:只传送登录后公共流的内容
    pTraderApi->SubscribePublicTopic(THOST_TERT_RESUME);

    /// 设置服务器地址
    pTraderApi->RegisterFront(pConfigure->FrontAddress);

    // 连接交易系统
    pTraderApi->Init();
    // TODO : 这里需要等待工作线程收到OnFrontConnected回调
    // ... ...

    // 发出登陆请求
    CThostFtdcReqUserLoginField userLoginField;
    strcpy(userLoginField.BrokerID,pConfigure->BrokerID);
    strcpy(userLoginField.UserID,pConfigure->UserID);
    strcpy(userLoginField.Password,pConfigure->Password);
    pTraderApi->ReqUserLogin(&userLoginField,getNextRequestID());
    // TODO : 这里需要等待登录成功返回信息
    // ... ...

}


/// 获取下一个RequestID序列
int CApiWrapper::getNextRequestID() {
    return 	++this->RequestID;
}

/// 获取当前RequestID序列
int CApiWrapper::getCurrentRequestID() {
    return 	this->RequestID;
}

/*

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



/*
1、重载CTraderHander(实现登录操作部分，或者直接在CTraderHander实现)
2、创建TraderApi实例
3、登录ReqUserLogin（管理CTP_FrontAddress，CTP_BrokerId，CTP_UserId，CTP_Password）
4、

// 创建TraderAPI和回调响应控制器的实例
CThostFtdcTraderApi *pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
CTraderHandler traderHandler = CTraderHandler();
CTraderHandler * pTraderHandler = &traderHandler;
pTraderApi->RegisterSpi(pTraderHandler);

// 订阅相关信息推送
//// THOST_TERT_RESTART:从本交易日开始重传
//// THOST_TERT_RESUME:从上次收到的续传
//// THOST_TERT_QUICK:只传送登录后私有流的内容
pTraderApi->SubscribePrivateTopic(THOST_TERT_RESUME);
// 订阅公共流
//// THOST_TERT_RESTART:从本交易日开始重传
//// THOST_TERT_RESUME:从上次收到的续传
//// THOST_TERT_QUICK:只传送登录后公共流的内容
pTraderApi->SubscribePublicTopic(THOST_TERT_RESUME);

// 设置服务器地址
pTraderApi->RegisterFront(CTP_FrontAddress);
// 链接交易系统
pTraderApi->Init();
// 等待服务器发出登录消息
sem_wait(&sem);
// 发出登陆请求
pTraderApi->ReqUserLogin(&userLoginField, requestID++);
// 等待登录成功消息
sem_wait(&sem);


CThostFtdcInputOrderField requestData;
// 确保没有初始化的数据不会被访问
memset(&requestData,0,sizeof(requestData));
....

// 调用API,并等待响应函数返回
int result = pTraderApi->ReqOrderInsert(&requestData,requestID++);
sem_wait(&sem);







	///请求查询资金账户
	int ReqQryTradingAccount(
	CThostFtdcQryTradingAccountField * pQryTradingAccount,
		int nRequestID
){
	printf("ReqQryTradingAccount():被执行...\n");
}

	///请求查询保证金监管系统经纪公司资金账户密钥
	int ReqQryCFMMCTradingAccountKey(
	CThostFtdcQryCFMMCTradingAccountKeyField * pQryCFMMCTradingAccountKey,
		int nRequestID
){
	printf("ReqQryCFMMCTradingAccountKey():被执行...\n");
}

	///用户口令更新请求
	int ReqUserPasswordUpdate(
	CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate,
		int nRequestID
){
	printf("ReqUserPasswordUpdate():被执行...\n");
}

	///预埋撤单录入请求
	int ReqParkedOrderAction(
	CThostFtdcParkedOrderActionField * pParkedOrderAction,
		int nRequestID
){
	printf("ReqParkedOrderAction():被执行...\n");
}

	///请求查询交易通知
	int ReqQryTradingNotice(
	CThostFtdcQryTradingNoticeField * pQryTradingNotice,
		int nRequestID
){
	printf("ReqQryTradingNotice():被执行...\n");
}

	///请求查询成交
	int ReqQryTrade(
	CThostFtdcQryTradeField * pQryTrade,
		int nRequestID
){
	printf("ReqQryTrade():被执行...\n");
}

	///查询最大报单数量请求
	int ReqQueryMaxOrderVolume(
	CThostFtdcQueryMaxOrderVolumeField * pQueryMaxOrderVolume,
		int nRequestID
){
	printf("ReqQueryMaxOrderVolume():被执行...\n");
}

	///投资者结算结果确认
	int ReqSettlementInfoConfirm(
	CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
		int nRequestID
){
	printf("ReqSettlementInfoConfirm():被执行...\n");
}

	///请求查询投资者持仓
	int ReqQryInvestorPosition(
	CThostFtdcQryInvestorPositionField * pQryInvestorPosition,
		int nRequestID
){
	printf("ReqQryInvestorPosition():被执行...\n");
}

	///请求查询经纪公司交易算法
	int ReqQryBrokerTradingAlgos(
	CThostFtdcQryBrokerTradingAlgosField * pQryBrokerTradingAlgos,
		int nRequestID
){
	printf("ReqQryBrokerTradingAlgos():被执行...\n");
}

	///请求查询报单
	int ReqQryOrder(
	CThostFtdcQryOrderField * pQryOrder,
		int nRequestID
){
	printf("ReqQryOrder():被执行...\n");
}

	///请求查询交易所
	int ReqQryExchange(
	CThostFtdcQryExchangeField * pQryExchange,
		int nRequestID
){
	printf("ReqQryExchange():被执行...\n");
}

	///用户登录请求
	int ReqUserLogin(
	CThostFtdcReqUserLoginField * pReqUserLoginField,
		int nRequestID
){
	printf("ReqUserLogin():被执行...\n");
}

	///期货发起期货资金转银行请求
	int ReqFromFutureToBankByFuture(
	CThostFtdcReqTransferField * pReqTransfer,
		int nRequestID
){
	printf("ReqFromFutureToBankByFuture():被执行...\n");
}

	///期货发起银行资金转期货请求
	int ReqFromBankToFutureByFuture(
	CThostFtdcReqTransferField * pReqTransfer,
		int nRequestID
){
	printf("ReqFromBankToFutureByFuture():被执行...\n");
}

	///请求查询结算信息确认
	int ReqQrySettlementInfoConfirm(
	CThostFtdcQrySettlementInfoConfirmField * pQrySettlementInfoConfirm,
		int nRequestID
){
	printf("ReqQrySettlementInfoConfirm():被执行...\n");
}

	///请求查询经纪公司交易参数
	int ReqQryBrokerTradingParams(
	CThostFtdcQryBrokerTradingParamsField * pQryBrokerTradingParams,
		int nRequestID
){
	printf("ReqQryBrokerTradingParams():被执行...\n");
}

	///请求查询监控中心用户令牌
	int ReqQueryCFMMCTradingAccountToken(
	CThostFtdcQueryCFMMCTradingAccountTokenField * pQueryCFMMCTradingAccountToken,
		int nRequestID
){
	printf("ReqQueryCFMMCTradingAccountToken():被执行...\n");
}

	///请求查询客户通知
	int ReqQryNotice(
	CThostFtdcQryNoticeField * pQryNotice,
		int nRequestID
){
	printf("ReqQryNotice():被执行...\n");
}

	///请求查询汇率
	int ReqQryExchangeRate(
	CThostFtdcQryExchangeRateField * pQryExchangeRate,
		int nRequestID
){
	printf("ReqQryExchangeRate():被执行...\n");
}

	///预埋单录入请求
	int ReqParkedOrderInsert(
	CThostFtdcParkedOrderField * pParkedOrder,
		int nRequestID
){
	printf("ReqParkedOrderInsert():被执行...\n");
}

	///请求查询签约银行
	int ReqQryContractBank(
	CThostFtdcQryContractBankField * pQryContractBank,
		int nRequestID
){
	printf("ReqQryContractBank():被执行...\n");
}

	///请求查询投资者持仓明细
	int ReqQryInvestorPositionCombineDetail(
	CThostFtdcQryInvestorPositionCombineDetailField * pQryInvestorPositionCombineDetail,
		int nRequestID
){
	printf("ReqQryInvestorPositionCombineDetail():被执行...\n");
}

	///请求查询交易所保证金率
	int ReqQryExchangeMarginRate(
	CThostFtdcQryExchangeMarginRateField * pQryExchangeMarginRate,
		int nRequestID
){
	printf("ReqQryExchangeMarginRate():被执行...\n");
}

	///请求查询二级代理操作员银期权限
	int ReqQrySecAgentACIDMap(
	CThostFtdcQrySecAgentACIDMapField * pQrySecAgentACIDMap,
		int nRequestID
){
	printf("ReqQrySecAgentACIDMap():被执行...\n");
}

	///请求查询转帐流水
	int ReqQryTransferSerial(
	CThostFtdcQryTransferSerialField * pQryTransferSerial,
		int nRequestID
){
	printf("ReqQryTransferSerial():被执行...\n");
}

	///期货发起查询银行余额请求
	int ReqQueryBankAccountMoneyByFuture(
	CThostFtdcReqQueryAccountField * pReqQueryAccount,
		int nRequestID
){
	printf("ReqQueryBankAccountMoneyByFuture():被执行...\n");
}

	///请求查询预埋撤单
	int ReqQryParkedOrderAction(
	CThostFtdcQryParkedOrderActionField * pQryParkedOrderAction,
		int nRequestID
){
	printf("ReqQryParkedOrderAction():被执行...\n");
}

	///客户端认证请求
	int ReqAuthenticate(
	CThostFtdcReqAuthenticateField * pReqAuthenticateField,
		int nRequestID
){
	printf("ReqAuthenticate():被执行...\n");
}

	///报单录入请求
	int ReqOrderInsert(
	CThostFtdcInputOrderField * pInputOrder,
		int nRequestID
){
	printf("ReqOrderInsert():被执行...\n");
}

	///请求查询投资者结算结果
	int ReqQrySettlementInfo(
	CThostFtdcQrySettlementInfoField * pQrySettlementInfo,
		int nRequestID
){
	printf("ReqQrySettlementInfo():被执行...\n");
}

	///登出请求
	int ReqUserLogout(
	CThostFtdcUserLogoutField * pUserLogout,
		int nRequestID
){
	printf("ReqUserLogout():被执行...\n");
}

	///请求查询合约
	int ReqQryInstrument(
	CThostFtdcQryInstrumentField * pQryInstrument,
		int nRequestID
){
	printf("ReqQryInstrument():被执行...\n");
}

	///报单操作请求
	int ReqOrderAction(
	CThostFtdcInputOrderActionField * pInputOrderAction,
		int nRequestID
){
	printf("ReqOrderAction():被执行...\n");
}

	///请求查询合约手续费率
	int ReqQryInstrumentCommissionRate(
	CThostFtdcQryInstrumentCommissionRateField * pQryInstrumentCommissionRate,
		int nRequestID
){
	printf("ReqQryInstrumentCommissionRate():被执行...\n");
}

	///请求查询合约保证金率
	int ReqQryInstrumentMarginRate(
	CThostFtdcQryInstrumentMarginRateField * pQryInstrumentMarginRate,
		int nRequestID
){
	printf("ReqQryInstrumentMarginRate():被执行...\n");
}

	///请求查询投资者
	int ReqQryInvestor(
	CThostFtdcQryInvestorField * pQryInvestor,
		int nRequestID
){
	printf("ReqQryInvestor():被执行...\n");
}

	///请求查询预埋单
	int ReqQryParkedOrder(
	CThostFtdcQryParkedOrderField * pQryParkedOrder,
		int nRequestID
){
	printf("ReqQryParkedOrder():被执行...\n");
}

	///请求查询投资者品种/跨品种保证金
	int ReqQryInvestorProductGroupMargin(
	CThostFtdcQryInvestorProductGroupMarginField * pQryInvestorProductGroupMargin,
		int nRequestID
){
	printf("ReqQryInvestorProductGroupMargin():被执行...\n");
}

	///请求查询行情
	int ReqQryDepthMarketData(
	CThostFtdcQryDepthMarketDataField * pQryDepthMarketData,
		int nRequestID
){
	printf("ReqQryDepthMarketData():被执行...\n");
}

	///请求查询转帐银行
	int ReqQryTransferBank(
	CThostFtdcQryTransferBankField * pQryTransferBank,
		int nRequestID
){
	printf("ReqQryTransferBank():被执行...\n");
}

	///请求删除预埋撤单
	int ReqRemoveParkedOrderAction(
	CThostFtdcRemoveParkedOrderActionField * pRemoveParkedOrderAction,
		int nRequestID
){
	printf("ReqRemoveParkedOrderAction():被执行...\n");
}

	///请求查询产品
	int ReqQryProduct(
	CThostFtdcQryProductField * pQryProduct,
		int nRequestID
){
	printf("ReqQryProduct():被执行...\n");
}

	///请求查询交易编码
	int ReqQryTradingCode(
	CThostFtdcQryTradingCodeField * pQryTradingCode,
		int nRequestID
){
	printf("ReqQryTradingCode():被执行...\n");
}

	///资金账户口令更新请求
	int ReqTradingAccountPasswordUpdate(
	CThostFtdcTradingAccountPasswordUpdateField * pTradingAccountPasswordUpdate,
		int nRequestID
){
	printf("ReqTradingAccountPasswordUpdate():被执行...\n");
}

	///请求查询银期签约关系
	int ReqQryAccountregister(
	CThostFtdcQryAccountregisterField * pQryAccountregister,
		int nRequestID
){
	printf("ReqQryAccountregister():被执行...\n");
}

	///请求查询交易所调整保证金率
	int ReqQryExchangeMarginRateAdjust(
	CThostFtdcQryExchangeMarginRateAdjustField * pQryExchangeMarginRateAdjust,
		int nRequestID
){
	printf("ReqQryExchangeMarginRateAdjust():被执行...\n");
}

	///请求查询仓单折抵信息
	int ReqQryEWarrantOffset(
	CThostFtdcQryEWarrantOffsetField * pQryEWarrantOffset,
		int nRequestID
){
	printf("ReqQryEWarrantOffset():被执行...\n");
}

	///请求查询投资者持仓明细
	int ReqQryInvestorPositionDetail(
	CThostFtdcQryInvestorPositionDetailField * pQryInvestorPositionDetail,
		int nRequestID
){
	printf("ReqQryInvestorPositionDetail():被执行...\n");
}

	///请求删除预埋单
	int ReqRemoveParkedOrder(
	CThostFtdcRemoveParkedOrderField * pRemoveParkedOrder,
		int nRequestID
){
	printf("ReqRemoveParkedOrder():被执行...\n");
}


*/