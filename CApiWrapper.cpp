
#include <CApiWrapper.h>
#include <stdio.h>
#include <string.h>


/// 构造函数
CApiWrapper::CApiWrapper(Configure * pConfigure) {

    // 读取配置数据信息
    this->pConfigure = pConfigure;

    // 创建CTP API工作对象
    pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();

    // 创建SPI工作对象并让其和API关联
    pTraderHandler = new CTraderHandler();
    pTraderApi->RegisterSpi(pTraderHandler);

    // 初始化RequestID序列
    RequestID = 0;

    // 初始化上次出错代码和出错信息
    lastErrorCode = 0;
    strcpy(lastErrorMessage,"");
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
    // TODO : 这里需要等待登录成功返回信息(OnRspUserLogin)
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
    CThostFtdcQryTradingAccountField * pQryTradingAccount;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingAccount(
            pQryTradingAccount,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询保证金监管系统经纪公司资金账户密钥
int CApiWrapper::ReqQryCFMMCTradingAccountKey(char * pJsonData )
{
    printf("ReqQryCFMMCTradingAccountKey():被执行...\n");
    CThostFtdcQryCFMMCTradingAccountKeyField * pQryCFMMCTradingAccountKey;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryCFMMCTradingAccountKey(
            pQryCFMMCTradingAccountKey,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///用户口令更新请求
int CApiWrapper::ReqUserPasswordUpdate(char * pJsonData )
{
    printf("ReqUserPasswordUpdate():被执行...\n");
    CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserPasswordUpdate(
            pUserPasswordUpdate,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///预埋撤单录入请求
int CApiWrapper::ReqParkedOrderAction(char * pJsonData )
{
    printf("ReqParkedOrderAction():被执行...\n");
    CThostFtdcParkedOrderActionField * pParkedOrderAction;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqParkedOrderAction(
            pParkedOrderAction,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询交易通知
int CApiWrapper::ReqQryTradingNotice(char * pJsonData )
{
    printf("ReqQryTradingNotice():被执行...\n");
    CThostFtdcQryTradingNoticeField * pQryTradingNotice;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingNotice(
            pQryTradingNotice,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询成交
int CApiWrapper::ReqQryTrade(char * pJsonData )
{
    printf("ReqQryTrade():被执行...\n");
    CThostFtdcQryTradeField * pQryTrade;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTrade(
            pQryTrade,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///查询最大报单数量请求
int CApiWrapper::ReqQueryMaxOrderVolume(char * pJsonData )
{
    printf("ReqQueryMaxOrderVolume():被执行...\n");
    CThostFtdcQueryMaxOrderVolumeField * pQueryMaxOrderVolume;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryMaxOrderVolume(
            pQueryMaxOrderVolume,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///投资者结算结果确认
int CApiWrapper::ReqSettlementInfoConfirm(char * pJsonData )
{
    printf("ReqSettlementInfoConfirm():被执行...\n");
    CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqSettlementInfoConfirm(
            pSettlementInfoConfirm,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询投资者持仓
int CApiWrapper::ReqQryInvestorPosition(char * pJsonData )
{
    printf("ReqQryInvestorPosition():被执行...\n");
    CThostFtdcQryInvestorPositionField * pQryInvestorPosition;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPosition(
            pQryInvestorPosition,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询经纪公司交易算法
int CApiWrapper::ReqQryBrokerTradingAlgos(char * pJsonData )
{
    printf("ReqQryBrokerTradingAlgos():被执行...\n");
    CThostFtdcQryBrokerTradingAlgosField * pQryBrokerTradingAlgos;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryBrokerTradingAlgos(
            pQryBrokerTradingAlgos,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询报单
int CApiWrapper::ReqQryOrder(char * pJsonData )
{
    printf("ReqQryOrder():被执行...\n");
    CThostFtdcQryOrderField * pQryOrder;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryOrder(
            pQryOrder,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询交易所
int CApiWrapper::ReqQryExchange(char * pJsonData )
{
    printf("ReqQryExchange():被执行...\n");
    CThostFtdcQryExchangeField * pQryExchange;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchange(
            pQryExchange,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///用户登录请求
int CApiWrapper::ReqUserLogin(char * pJsonData )
{
    printf("ReqUserLogin():被执行...\n");
    CThostFtdcReqUserLoginField * pReqUserLoginField;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserLogin(
            pReqUserLoginField,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///期货发起期货资金转银行请求
int CApiWrapper::ReqFromFutureToBankByFuture(char * pJsonData )
{
    printf("ReqFromFutureToBankByFuture():被执行...\n");
    CThostFtdcReqTransferField * pReqTransfer;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqFromFutureToBankByFuture(
            pReqTransfer,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///期货发起银行资金转期货请求
int CApiWrapper::ReqFromBankToFutureByFuture(char * pJsonData )
{
    printf("ReqFromBankToFutureByFuture():被执行...\n");
    CThostFtdcReqTransferField * pReqTransfer;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqFromBankToFutureByFuture(
            pReqTransfer,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询结算信息确认
int CApiWrapper::ReqQrySettlementInfoConfirm(char * pJsonData )
{
    printf("ReqQrySettlementInfoConfirm():被执行...\n");
    CThostFtdcQrySettlementInfoConfirmField * pQrySettlementInfoConfirm;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySettlementInfoConfirm(
            pQrySettlementInfoConfirm,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询经纪公司交易参数
int CApiWrapper::ReqQryBrokerTradingParams(char * pJsonData )
{
    printf("ReqQryBrokerTradingParams():被执行...\n");
    CThostFtdcQryBrokerTradingParamsField * pQryBrokerTradingParams;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryBrokerTradingParams(
            pQryBrokerTradingParams,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询监控中心用户令牌
int CApiWrapper::ReqQueryCFMMCTradingAccountToken(char * pJsonData )
{
    printf("ReqQueryCFMMCTradingAccountToken():被执行...\n");
    CThostFtdcQueryCFMMCTradingAccountTokenField * pQueryCFMMCTradingAccountToken;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryCFMMCTradingAccountToken(
            pQueryCFMMCTradingAccountToken,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询客户通知
int CApiWrapper::ReqQryNotice(char * pJsonData )
{
    printf("ReqQryNotice():被执行...\n");
    CThostFtdcQryNoticeField * pQryNotice;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryNotice(
            pQryNotice,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询汇率
int CApiWrapper::ReqQryExchangeRate(char * pJsonData )
{
    printf("ReqQryExchangeRate():被执行...\n");
    CThostFtdcQryExchangeRateField * pQryExchangeRate;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeRate(
            pQryExchangeRate,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///预埋单录入请求
int CApiWrapper::ReqParkedOrderInsert(char * pJsonData )
{
    printf("ReqParkedOrderInsert():被执行...\n");
    CThostFtdcParkedOrderField * pParkedOrder;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqParkedOrderInsert(
            pParkedOrder,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询签约银行
int CApiWrapper::ReqQryContractBank(char * pJsonData )
{
    printf("ReqQryContractBank():被执行...\n");
    CThostFtdcQryContractBankField * pQryContractBank;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryContractBank(
            pQryContractBank,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询投资者持仓明细
int CApiWrapper::ReqQryInvestorPositionCombineDetail(char * pJsonData )
{
    printf("ReqQryInvestorPositionCombineDetail():被执行...\n");
    CThostFtdcQryInvestorPositionCombineDetailField * pQryInvestorPositionCombineDetail;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPositionCombineDetail(
            pQryInvestorPositionCombineDetail,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询交易所保证金率
int CApiWrapper::ReqQryExchangeMarginRate(char * pJsonData )
{
    printf("ReqQryExchangeMarginRate():被执行...\n");
    CThostFtdcQryExchangeMarginRateField * pQryExchangeMarginRate;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeMarginRate(
            pQryExchangeMarginRate,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询二级代理操作员银期权限
int CApiWrapper::ReqQrySecAgentACIDMap(char * pJsonData )
{
    printf("ReqQrySecAgentACIDMap():被执行...\n");
    CThostFtdcQrySecAgentACIDMapField * pQrySecAgentACIDMap;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySecAgentACIDMap(
            pQrySecAgentACIDMap,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询转帐流水
int CApiWrapper::ReqQryTransferSerial(char * pJsonData )
{
    printf("ReqQryTransferSerial():被执行...\n");
    CThostFtdcQryTransferSerialField * pQryTransferSerial;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTransferSerial(
            pQryTransferSerial,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///期货发起查询银行余额请求
int CApiWrapper::ReqQueryBankAccountMoneyByFuture(char * pJsonData )
{
    printf("ReqQueryBankAccountMoneyByFuture():被执行...\n");
    CThostFtdcReqQueryAccountField * pReqQueryAccount;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQueryBankAccountMoneyByFuture(
            pReqQueryAccount,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询预埋撤单
int CApiWrapper::ReqQryParkedOrderAction(char * pJsonData )
{
    printf("ReqQryParkedOrderAction():被执行...\n");
    CThostFtdcQryParkedOrderActionField * pQryParkedOrderAction;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryParkedOrderAction(
            pQryParkedOrderAction,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///客户端认证请求
int CApiWrapper::ReqAuthenticate(char * pJsonData )
{
    printf("ReqAuthenticate():被执行...\n");
    CThostFtdcReqAuthenticateField * pReqAuthenticateField;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqAuthenticate(
            pReqAuthenticateField,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///报单录入请求
int CApiWrapper::ReqOrderInsert(char * pJsonData )
{
    printf("ReqOrderInsert():被执行...\n");
    CThostFtdcInputOrderField * pInputOrder;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqOrderInsert(
            pInputOrder,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询投资者结算结果
int CApiWrapper::ReqQrySettlementInfo(char * pJsonData )
{
    printf("ReqQrySettlementInfo():被执行...\n");
    CThostFtdcQrySettlementInfoField * pQrySettlementInfo;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQrySettlementInfo(
            pQrySettlementInfo,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///登出请求
int CApiWrapper::ReqUserLogout(char * pJsonData )
{
    printf("ReqUserLogout():被执行...\n");
    CThostFtdcUserLogoutField * pUserLogout;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqUserLogout(
            pUserLogout,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询合约
int CApiWrapper::ReqQryInstrument(char * pJsonData )
{
    printf("ReqQryInstrument():被执行...\n");
    CThostFtdcQryInstrumentField * pQryInstrument;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrument(
            pQryInstrument,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///报单操作请求
int CApiWrapper::ReqOrderAction(char * pJsonData )
{
    printf("ReqOrderAction():被执行...\n");
    CThostFtdcInputOrderActionField * pInputOrderAction;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqOrderAction(
            pInputOrderAction,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询合约手续费率
int CApiWrapper::ReqQryInstrumentCommissionRate(char * pJsonData )
{
    printf("ReqQryInstrumentCommissionRate():被执行...\n");
    CThostFtdcQryInstrumentCommissionRateField * pQryInstrumentCommissionRate;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrumentCommissionRate(
            pQryInstrumentCommissionRate,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询合约保证金率
int CApiWrapper::ReqQryInstrumentMarginRate(char * pJsonData )
{
    printf("ReqQryInstrumentMarginRate():被执行...\n");
    CThostFtdcQryInstrumentMarginRateField * pQryInstrumentMarginRate;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInstrumentMarginRate(
            pQryInstrumentMarginRate,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询投资者
int CApiWrapper::ReqQryInvestor(char * pJsonData )
{
    printf("ReqQryInvestor():被执行...\n");
    CThostFtdcQryInvestorField * pQryInvestor;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestor(
            pQryInvestor,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询预埋单
int CApiWrapper::ReqQryParkedOrder(char * pJsonData )
{
    printf("ReqQryParkedOrder():被执行...\n");
    CThostFtdcQryParkedOrderField * pQryParkedOrder;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryParkedOrder(
            pQryParkedOrder,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询投资者品种/跨品种保证金
int CApiWrapper::ReqQryInvestorProductGroupMargin(char * pJsonData )
{
    printf("ReqQryInvestorProductGroupMargin():被执行...\n");
    CThostFtdcQryInvestorProductGroupMarginField * pQryInvestorProductGroupMargin;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorProductGroupMargin(
            pQryInvestorProductGroupMargin,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询行情
int CApiWrapper::ReqQryDepthMarketData(char * pJsonData )
{
    printf("ReqQryDepthMarketData():被执行...\n");
    CThostFtdcQryDepthMarketDataField * pQryDepthMarketData;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryDepthMarketData(
            pQryDepthMarketData,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询转帐银行
int CApiWrapper::ReqQryTransferBank(char * pJsonData )
{
    printf("ReqQryTransferBank():被执行...\n");
    CThostFtdcQryTransferBankField * pQryTransferBank;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTransferBank(
            pQryTransferBank,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求删除预埋撤单
int CApiWrapper::ReqRemoveParkedOrderAction(char * pJsonData )
{
    printf("ReqRemoveParkedOrderAction():被执行...\n");
    CThostFtdcRemoveParkedOrderActionField * pRemoveParkedOrderAction;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqRemoveParkedOrderAction(
            pRemoveParkedOrderAction,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询产品
int CApiWrapper::ReqQryProduct(char * pJsonData )
{
    printf("ReqQryProduct():被执行...\n");
    CThostFtdcQryProductField * pQryProduct;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryProduct(
            pQryProduct,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询交易编码
int CApiWrapper::ReqQryTradingCode(char * pJsonData )
{
    printf("ReqQryTradingCode():被执行...\n");
    CThostFtdcQryTradingCodeField * pQryTradingCode;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryTradingCode(
            pQryTradingCode,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///资金账户口令更新请求
int CApiWrapper::ReqTradingAccountPasswordUpdate(char * pJsonData )
{
    printf("ReqTradingAccountPasswordUpdate():被执行...\n");
    CThostFtdcTradingAccountPasswordUpdateField * pTradingAccountPasswordUpdate;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqTradingAccountPasswordUpdate(
            pTradingAccountPasswordUpdate,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询银期签约关系
int CApiWrapper::ReqQryAccountregister(char * pJsonData )
{
    printf("ReqQryAccountregister():被执行...\n");
    CThostFtdcQryAccountregisterField * pQryAccountregister;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryAccountregister(
            pQryAccountregister,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询交易所调整保证金率
int CApiWrapper::ReqQryExchangeMarginRateAdjust(char * pJsonData )
{
    printf("ReqQryExchangeMarginRateAdjust():被执行...\n");
    CThostFtdcQryExchangeMarginRateAdjustField * pQryExchangeMarginRateAdjust;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryExchangeMarginRateAdjust(
            pQryExchangeMarginRateAdjust,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询仓单折抵信息
int CApiWrapper::ReqQryEWarrantOffset(char * pJsonData )
{
    printf("ReqQryEWarrantOffset():被执行...\n");
    CThostFtdcQryEWarrantOffsetField * pQryEWarrantOffset;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryEWarrantOffset(
            pQryEWarrantOffset,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求查询投资者持仓明细
int CApiWrapper::ReqQryInvestorPositionDetail(char * pJsonData )
{
    printf("ReqQryInvestorPositionDetail():被执行...\n");
    CThostFtdcQryInvestorPositionDetailField * pQryInvestorPositionDetail;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqQryInvestorPositionDetail(
            pQryInvestorPositionDetail,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}

///请求删除预埋单
int CApiWrapper::ReqRemoveParkedOrder(char * pJsonData )
{
    printf("ReqRemoveParkedOrder():被执行...\n");
    CThostFtdcRemoveParkedOrderField * pRemoveParkedOrder;
    int nRequestID;

    // 获取RequestID
    nRequestID = getNextRequestID();

    // TODO:这里将pJsonData转化为对应的结构参数

    // 调用对应的CTP API函数
    int result =
        pTraderApi->ReqRemoveParkedOrder(
            pRemoveParkedOrder,
            nRequestID
        );

    // TODO:检查API调用是否失败

    return 0;
}
