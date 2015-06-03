#include <ThostFtdcMdApi.h>
#include <ThostFtdcUserApiStruct.h>
#include <ThostFtdcUserApiDataType.h>
#include <Configure.h>
#include <CMdHandler.h>
#include <zmq.hpp>
#include <Message.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <map>

class CMdWrapper {

public:
    /// 构造函数
    CMdWrapper(MdConfigure * pConfigure);
    /////////////////  变量定义 //////////////////
    /// 对应的API实例
    CThostFtdcMdApi * pMdApi;
    /// 对应的SPI实例
    CMdHandler * pMdHandler;
    /// 配置信息
    MdConfigure * pConfigure;
    /// RequestID序列器
    int RequestID;
    /// 上次出错代码
    int lastErrorID;
    /// 上次出错信息
    std::string lastErrorMsg;
    /// 启动CTP连接
    void init();
    /// 获取下一个RequestID序列
    int getNextRequestID();
    /// 获取当前RequestID序列
    int getCurrentRequestID();
    /// 获取上次出错代码
    int getLastErrorID();
    /// 获取上次错误信息
    std::string getLastErrorMsg();

    void initApiMap();

    ////////////// API方法的wrapper ///////////////

    ///请求查询资金账户
    int ReqQryTradingAccount(std::string jsonString);

    ///请求查询保证金监管系统经纪公司资金账户密钥
    int ReqQryCFMMCTradingAccountKey(std::string jsonString);

    ///用户口令更新请求
    int ReqUserPasswordUpdate(std::string jsonString);

    ///请求查询交易通知
    int ReqQryTradingNotice(std::string jsonString);

    ///请求查询成交
    int ReqQryTrade(std::string jsonString);

    ///查询最大报单数量请求
    int ReqQueryMaxOrderVolume(std::string jsonString);

    ///投资者结算结果确认
    int ReqSettlementInfoConfirm(std::string jsonString);

    ///请求查询投资者持仓
    int ReqQryInvestorPosition(std::string jsonString);

    ///请求查询经纪公司交易算法
    int ReqQryBrokerTradingAlgos(std::string jsonString);

    ///请求查询报单
    int ReqQryOrder(std::string jsonString);

    ///请求查询交易所
    int ReqQryExchange(std::string jsonString);

    ///用户登录请求
    int ReqUserLogin(std::string jsonString);

    ///期货发起期货资金转银行请求
    int ReqFromFutureToBankByFuture(std::string jsonString);

    ///请求查询汇率
    int ReqQryExchangeRate(std::string jsonString);

    ///请求查询投资者持仓明细
    int ReqQryInvestorPositionDetail(std::string jsonString);

    ///请求查询结算信息确认
    int ReqQrySettlementInfoConfirm(std::string jsonString);

    ///请求查询经纪公司交易参数
    int ReqQryBrokerTradingParams(std::string jsonString);

    ///请求查询监控中心用户令牌
    int ReqQueryCFMMCTradingAccountToken(std::string jsonString);

    ///请求查询客户通知
    int ReqQryNotice(std::string jsonString);

    ///期货发起银行资金转期货请求
    int ReqFromBankToFutureByFuture(std::string jsonString);

    ///预埋单录入请求
    int ReqParkedOrderInsert(std::string jsonString);

    ///请求查询投资者持仓明细
    int ReqQryInvestorPositionCombineDetail(std::string jsonString);

    ///报单录入请求
    int ReqOrderInsert(std::string jsonString);

    ///请求查询二级代理操作员银期权限
    int ReqQrySecAgentACIDMap(std::string jsonString);

    ///预埋撤单录入请求
    int ReqParkedOrderAction(std::string jsonString);

    ///期货发起查询银行余额请求
    int ReqQueryBankAccountMoneyByFuture(std::string jsonString);

    ///请求查询预埋撤单
    int ReqQryParkedOrderAction(std::string jsonString);

    ///客户端认证请求
    int ReqAuthenticate(std::string jsonString);

    ///请求查询交易所保证金率
    int ReqQryExchangeMarginRate(std::string jsonString);

    ///资金账户口令更新请求
    int ReqTradingAccountPasswordUpdate(std::string jsonString);

    ///登出请求
    int ReqUserLogout(std::string jsonString);

    ///请求查询合约
    int ReqQryInstrument(std::string jsonString);

    ///报单操作请求
    int ReqOrderAction(std::string jsonString);

    ///请求查询合约手续费率
    int ReqQryInstrumentCommissionRate(std::string jsonString);

    ///请求查询合约保证金率
    int ReqQryInstrumentMarginRate(std::string jsonString);

    ///请求查询投资者
    int ReqQryInvestor(std::string jsonString);

    ///请求查询交易所调整保证金率
    int ReqQryExchangeMarginRateAdjust(std::string jsonString);

    ///请求查询投资者品种/跨品种保证金
    int ReqQryInvestorProductGroupMargin(std::string jsonString);

    ///请求查询仓单折抵信息
    int ReqQryEWarrantOffset(std::string jsonString);

    ///请求查询行情
    int ReqQryDepthMarketData(std::string jsonString);

    ///请求查询转帐银行
    int ReqQryTransferBank(std::string jsonString);

    ///请求删除预埋撤单
    int ReqRemoveParkedOrderAction(std::string jsonString);

    ///请求查询产品
    int ReqQryProduct(std::string jsonString);

    ///请求查询交易编码
    int ReqQryTradingCode(std::string jsonString);

    ///请求查询投资者结算结果
    int ReqQrySettlementInfo(std::string jsonString);

    ///请求查询银期签约关系
    int ReqQryAccountregister(std::string jsonString);

    ///请求查询预埋单
    int ReqQryParkedOrder(std::string jsonString);

    ///请求查询转帐流水
    int ReqQryTransferSerial(std::string jsonString);

    ///请求查询签约银行
    int ReqQryContractBank(std::string jsonString);

    ///请求删除预埋单
    int ReqRemoveParkedOrder(std::string jsonString);


    std::map<std::string,int (CMdWrapper::*) (std::string)> apiMap;

    int callApiByName(std::string apiName,std::string jsonString);

};