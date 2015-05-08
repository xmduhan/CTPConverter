
#include <ThostFtdcTraderApi.h>
#include <ThostFtdcUserApiStruct.h>
#include <ThostFtdcUserApiDataType.h>
#include <Configure.h>
#include <CTraderHandler.h>


class CApiWrapper {

public:
    /// 构造函数
    CApiWrapper(Configure * pConfigure);
    /////////////////  变量定义 //////////////////
    /// 对应的API实例
    CThostFtdcTraderApi * pTraderApi;
    /// 对应的SPI实例
    CTraderHandler * pTraderHandler;
    /// 配置信息
    Configure * pConfigure;
    /// RequestID序列器
    int RequestID;
    /// 上次出错代码
    int lastErrorCode;
    /// 上次出错信息
    char lastErrorMessage[1024];
    ////////////////// 方法定义 ///////////////////
    /// 启动CTP连接
    void init();
    /// 获取下一个RequestID序列
    int getNextRequestID();
    /// 获取当前RequestID序列
    int getCurrentRequestID();
    /// 获取上次出错代码
    int getLastErrorCode();
    /// 获取上次错误信息
    char * getLastErrorMessage();

    ////////////// API方法的wrapper ///////////////

    ///请求查询资金账户
    int ReqQryTradingAccount(char * pJsonData );

    ///请求查询保证金监管系统经纪公司资金账户密钥
    int ReqQryCFMMCTradingAccountKey(char * pJsonData );

    ///用户口令更新请求
    int ReqUserPasswordUpdate(char * pJsonData );

    ///预埋撤单录入请求
    int ReqParkedOrderAction(char * pJsonData );

    ///请求查询交易通知
    int ReqQryTradingNotice(char * pJsonData );

    ///请求查询成交
    int ReqQryTrade(char * pJsonData );

    ///查询最大报单数量请求
    int ReqQueryMaxOrderVolume(char * pJsonData );

    ///投资者结算结果确认
    int ReqSettlementInfoConfirm(char * pJsonData );

    ///请求查询投资者持仓
    int ReqQryInvestorPosition(char * pJsonData );

    ///请求查询经纪公司交易算法
    int ReqQryBrokerTradingAlgos(char * pJsonData );

    ///请求查询报单
    int ReqQryOrder(char * pJsonData );

    ///请求查询交易所
    int ReqQryExchange(char * pJsonData );

    ///用户登录请求
    int ReqUserLogin(char * pJsonData );

    ///期货发起期货资金转银行请求
    int ReqFromFutureToBankByFuture(char * pJsonData );

    ///期货发起银行资金转期货请求
    int ReqFromBankToFutureByFuture(char * pJsonData );

    ///请求查询结算信息确认
    int ReqQrySettlementInfoConfirm(char * pJsonData );

    ///请求查询经纪公司交易参数
    int ReqQryBrokerTradingParams(char * pJsonData );

    ///请求查询监控中心用户令牌
    int ReqQueryCFMMCTradingAccountToken(char * pJsonData );

    ///请求查询客户通知
    int ReqQryNotice(char * pJsonData );

    ///请求查询汇率
    int ReqQryExchangeRate(char * pJsonData );

    ///预埋单录入请求
    int ReqParkedOrderInsert(char * pJsonData );

    ///请求查询签约银行
    int ReqQryContractBank(char * pJsonData );

    ///请求查询投资者持仓明细
    int ReqQryInvestorPositionCombineDetail(char * pJsonData );

    ///请求查询交易所保证金率
    int ReqQryExchangeMarginRate(char * pJsonData );

    ///请求查询二级代理操作员银期权限
    int ReqQrySecAgentACIDMap(char * pJsonData );

    ///请求查询转帐流水
    int ReqQryTransferSerial(char * pJsonData );

    ///期货发起查询银行余额请求
    int ReqQueryBankAccountMoneyByFuture(char * pJsonData );

    ///请求查询预埋撤单
    int ReqQryParkedOrderAction(char * pJsonData );

    ///客户端认证请求
    int ReqAuthenticate(char * pJsonData );

    ///报单录入请求
    int ReqOrderInsert(char * pJsonData );

    ///请求查询投资者结算结果
    int ReqQrySettlementInfo(char * pJsonData );

    ///登出请求
    int ReqUserLogout(char * pJsonData );

    ///请求查询合约
    int ReqQryInstrument(char * pJsonData );

    ///报单操作请求
    int ReqOrderAction(char * pJsonData );

    ///请求查询合约手续费率
    int ReqQryInstrumentCommissionRate(char * pJsonData );

    ///请求查询合约保证金率
    int ReqQryInstrumentMarginRate(char * pJsonData );

    ///请求查询投资者
    int ReqQryInvestor(char * pJsonData );

    ///请求查询预埋单
    int ReqQryParkedOrder(char * pJsonData );

    ///请求查询投资者品种/跨品种保证金
    int ReqQryInvestorProductGroupMargin(char * pJsonData );

    ///请求查询行情
    int ReqQryDepthMarketData(char * pJsonData );

    ///请求查询转帐银行
    int ReqQryTransferBank(char * pJsonData );

    ///请求删除预埋撤单
    int ReqRemoveParkedOrderAction(char * pJsonData );

    ///请求查询产品
    int ReqQryProduct(char * pJsonData );

    ///请求查询交易编码
    int ReqQryTradingCode(char * pJsonData );

    ///资金账户口令更新请求
    int ReqTradingAccountPasswordUpdate(char * pJsonData );

    ///请求查询银期签约关系
    int ReqQryAccountregister(char * pJsonData );

    ///请求查询交易所调整保证金率
    int ReqQryExchangeMarginRateAdjust(char * pJsonData );

    ///请求查询仓单折抵信息
    int ReqQryEWarrantOffset(char * pJsonData );

    ///请求查询投资者持仓明细
    int ReqQryInvestorPositionDetail(char * pJsonData );

    ///请求删除预埋单
    int ReqRemoveParkedOrder(char * pJsonData );


};