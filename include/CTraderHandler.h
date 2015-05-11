#pragma once

#include <ThostFtdcTraderApi.h>
#include <Message.h>
#include <Configure.h>


class CTraderHandler : public CThostFtdcTraderSpi {

public:

    /// 构造函数
    CTraderHandler(Configure * pConfigure);
    /// 配置信息
    Configure * pConfigure;
    /// zmq通讯环境
    zmq::context_t * pContext;
    /// 通讯套接字
    zmq::socket_t * pSender;

    /// 成功连接回调
    virtual void OnFrontConnected();

    /**********************************************************
    *                   onRsp开头的方法                         *
    ***********************************************************/


    ///请求查询合约响应
    virtual void OnRspQryInstrument(
        CThostFtdcInstrumentField * pInstrument,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询投资者结算结果响应
    virtual void OnRspQrySettlementInfo(
        CThostFtdcSettlementInfoField * pSettlementInfo,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///预埋单录入请求响应
    virtual void OnRspParkedOrderInsert(
        CThostFtdcParkedOrderField * pParkedOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询交易所响应
    virtual void OnRspQryExchange(
        CThostFtdcExchangeField * pExchange,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///报单操作请求响应
    virtual void OnRspOrderAction(
        CThostFtdcInputOrderActionField * pInputOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询投资者响应
    virtual void OnRspQryInvestor(
        CThostFtdcInvestorField * pInvestor,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///删除预埋单响应
    virtual void OnRspRemoveParkedOrder(
        CThostFtdcRemoveParkedOrderField * pRemoveParkedOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询投资者品种/跨品种保证金响应
    virtual void OnRspQryInvestorProductGroupMargin(
        CThostFtdcInvestorProductGroupMarginField * pInvestorProductGroupMargin,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询转帐银行响应
    virtual void OnRspQryTransferBank(
        CThostFtdcTransferBankField * pTransferBank,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询经纪公司交易算法响应
    virtual void OnRspQryBrokerTradingAlgos(
        CThostFtdcBrokerTradingAlgosField * pBrokerTradingAlgos,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询产品响应
    virtual void OnRspQryProduct(
        CThostFtdcProductField * pProduct,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询合约保证金率响应
    virtual void OnRspQryInstrumentMarginRate(
        CThostFtdcInstrumentMarginRateField * pInstrumentMarginRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///查询保证金监管系统经纪公司资金账户密钥响应
    virtual void OnRspQryCFMMCTradingAccountKey(
        CThostFtdcCFMMCTradingAccountKeyField * pCFMMCTradingAccountKey,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///登录请求响应
    virtual void OnRspUserLogin(
        CThostFtdcRspUserLoginField * pRspUserLogin,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///期货发起期货资金转银行应答
    virtual void OnRspFromFutureToBankByFuture(
        CThostFtdcReqTransferField * pReqTransfer,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询监控中心用户令牌
    virtual void OnRspQueryCFMMCTradingAccountToken(
        CThostFtdcQueryCFMMCTradingAccountTokenField * pQueryCFMMCTradingAccountToken,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询签约银行响应
    virtual void OnRspQryContractBank(
        CThostFtdcContractBankField * pContractBank,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///报单录入请求响应
    virtual void OnRspOrderInsert(
        CThostFtdcInputOrderField * pInputOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询仓单折抵信息响应
    virtual void OnRspQryEWarrantOffset(
        CThostFtdcEWarrantOffsetField * pEWarrantOffset,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///用户口令更新请求响应
    virtual void OnRspUserPasswordUpdate(
        CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询交易所调整保证金率响应
    virtual void OnRspQryExchangeMarginRateAdjust(
        CThostFtdcExchangeMarginRateAdjustField * pExchangeMarginRateAdjust,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///期货发起银行资金转期货应答
    virtual void OnRspFromBankToFutureByFuture(
        CThostFtdcReqTransferField * pReqTransfer,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询投资者持仓明细响应
    virtual void OnRspQryInvestorPositionCombineDetail(
        CThostFtdcInvestorPositionCombineDetailField * pInvestorPositionCombineDetail,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///投资者结算结果确认响应
    virtual void OnRspSettlementInfoConfirm(
        CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询银期签约关系响应
    virtual void OnRspQryAccountregister(
        CThostFtdcAccountregisterField * pAccountregister,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询二级代理操作员银期权限响应
    virtual void OnRspQrySecAgentACIDMap(
        CThostFtdcSecAgentACIDMapField * pSecAgentACIDMap,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询交易编码响应
    virtual void OnRspQryTradingCode(
        CThostFtdcTradingCodeField * pTradingCode,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询结算信息确认响应
    virtual void OnRspQrySettlementInfoConfirm(
        CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询转帐流水响应
    virtual void OnRspQryTransferSerial(
        CThostFtdcTransferSerialField * pTransferSerial,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询投资者持仓响应
    virtual void OnRspQryInvestorPosition(
        CThostFtdcInvestorPositionField * pInvestorPosition,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///登出请求响应
    virtual void OnRspUserLogout(
        CThostFtdcUserLogoutField * pUserLogout,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询投资者持仓明细响应
    virtual void OnRspQryInvestorPositionDetail(
        CThostFtdcInvestorPositionDetailField * pInvestorPositionDetail,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询预埋撤单响应
    virtual void OnRspQryParkedOrderAction(
        CThostFtdcParkedOrderActionField * pParkedOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询经纪公司交易参数响应
    virtual void OnRspQryBrokerTradingParams(
        CThostFtdcBrokerTradingParamsField * pBrokerTradingParams,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询交易所保证金率响应
    virtual void OnRspQryExchangeMarginRate(
        CThostFtdcExchangeMarginRateField * pExchangeMarginRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询预埋单响应
    virtual void OnRspQryParkedOrder(
        CThostFtdcParkedOrderField * pParkedOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///期货发起查询银行余额应答
    virtual void OnRspQueryBankAccountMoneyByFuture(
        CThostFtdcReqQueryAccountField * pReqQueryAccount,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///客户端认证响应
    virtual void OnRspAuthenticate(
        CThostFtdcRspAuthenticateField * pRspAuthenticateField,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///查询最大报单数量响应
    virtual void OnRspQueryMaxOrderVolume(
        CThostFtdcQueryMaxOrderVolumeField * pQueryMaxOrderVolume,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询汇率响应
    virtual void OnRspQryExchangeRate(
        CThostFtdcExchangeRateField * pExchangeRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询交易通知响应
    virtual void OnRspQryTradingNotice(
        CThostFtdcTradingNoticeField * pTradingNotice,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///预埋撤单录入请求响应
    virtual void OnRspParkedOrderAction(
        CThostFtdcParkedOrderActionField * pParkedOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询客户通知响应
    virtual void OnRspQryNotice(
        CThostFtdcNoticeField * pNotice,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询资金账户响应
    virtual void OnRspQryTradingAccount(
        CThostFtdcTradingAccountField * pTradingAccount,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///资金账户口令更新请求响应
    virtual void OnRspTradingAccountPasswordUpdate(
        CThostFtdcTradingAccountPasswordUpdateField * pTradingAccountPasswordUpdate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询报单响应
    virtual void OnRspQryOrder(
        CThostFtdcOrderField * pOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询行情响应
    virtual void OnRspQryDepthMarketData(
        CThostFtdcDepthMarketDataField * pDepthMarketData,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询合约手续费率响应
    virtual void OnRspQryInstrumentCommissionRate(
        CThostFtdcInstrumentCommissionRateField * pInstrumentCommissionRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///删除预埋撤单响应
    virtual void OnRspRemoveParkedOrderAction(
        CThostFtdcRemoveParkedOrderActionField * pRemoveParkedOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///请求查询成交响应
    virtual void OnRspQryTrade(
        CThostFtdcTradeField * pTrade,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );


    /**********************************************************
    *                   onRtn开头的方法                         *
    ***********************************************************/



    ///期货发起查询银行余额通知
    virtual void OnRtnQueryBankBalanceByFuture(
        CThostFtdcNotifyQueryAccountField * pNotifyQueryAccount
    );

    ///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromBankToFutureByFuture(
        CThostFtdcRspRepealField * pRspRepeal
    );

    ///银行发起银行资金转期货通知
    virtual void OnRtnFromBankToFutureByBank(
        CThostFtdcRspTransferField * pRspTransfer
    );

    ///合约交易状态通知
    virtual void OnRtnInstrumentStatus(
        CThostFtdcInstrumentStatusField * pInstrumentStatus
    );

    ///交易通知
    virtual void OnRtnTradingNotice(
        CThostFtdcTradingNoticeInfoField * pTradingNoticeInfo
    );

    ///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromFutureToBankByFutureManual(
        CThostFtdcRspRepealField * pRspRepeal
    );

    ///期货发起银行资金转期货通知
    virtual void OnRtnFromBankToFutureByFuture(
        CThostFtdcRspTransferField * pRspTransfer
    );

    ///银行发起期货资金转银行通知
    virtual void OnRtnFromFutureToBankByBank(
        CThostFtdcRspTransferField * pRspTransfer
    );

    ///成交通知
    virtual void OnRtnTrade(
        CThostFtdcTradeField * pTrade
    );

    ///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromBankToFutureByFutureManual(
        CThostFtdcRspRepealField * pRspRepeal
    );

    ///期货发起期货资金转银行通知
    virtual void OnRtnFromFutureToBankByFuture(
        CThostFtdcRspTransferField * pRspTransfer
    );

    ///银行发起变更银行账号通知
    virtual void OnRtnChangeAccountByBank(
        CThostFtdcChangeAccountField * pChangeAccount
    );

    ///银行发起冲正期货转银行通知
    virtual void OnRtnRepealFromFutureToBankByBank(
        CThostFtdcRspRepealField * pRspRepeal
    );

    ///银行发起银期开户通知
    virtual void OnRtnOpenAccountByBank(
        CThostFtdcOpenAccountField * pOpenAccount
    );

    ///保证金监控中心用户令牌
    virtual void OnRtnCFMMCTradingAccountToken(
        CThostFtdcCFMMCTradingAccountTokenField * pCFMMCTradingAccountToken
    );

    ///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromFutureToBankByFuture(
        CThostFtdcRspRepealField * pRspRepeal
    );

    ///提示条件单校验错误
    virtual void OnRtnErrorConditionalOrder(
        CThostFtdcErrorConditionalOrderField * pErrorConditionalOrder
    );

    ///银行发起冲正银行转期货通知
    virtual void OnRtnRepealFromBankToFutureByBank(
        CThostFtdcRspRepealField * pRspRepeal
    );

    ///报单通知
    virtual void OnRtnOrder(
        CThostFtdcOrderField * pOrder
    );

    ///银行发起银期销户通知
    virtual void OnRtnCancelAccountByBank(
        CThostFtdcCancelAccountField * pCancelAccount
    );


    /**********************************************************
    *                   onErrRtn开头的方法                      *
    ***********************************************************/


    ///系统运行时期货端手工发起冲正期货转银行错误回报
    virtual void OnErrRtnRepealFutureToBankByFutureManual(
        CThostFtdcReqRepealField * pReqRepeal,
        CThostFtdcRspInfoField * pRspInfo
    );

    ///期货发起期货资金转银行错误回报
    virtual void OnErrRtnFutureToBankByFuture(
        CThostFtdcReqTransferField * pReqTransfer,
        CThostFtdcRspInfoField * pRspInfo
    );

    ///报单录入错误回报
    virtual void OnErrRtnOrderInsert(
        CThostFtdcInputOrderField * pInputOrder,
        CThostFtdcRspInfoField * pRspInfo
    );

    ///系统运行时期货端手工发起冲正银行转期货错误回报
    virtual void OnErrRtnRepealBankToFutureByFutureManual(
        CThostFtdcReqRepealField * pReqRepeal,
        CThostFtdcRspInfoField * pRspInfo
    );

    ///期货发起银行资金转期货错误回报
    virtual void OnErrRtnBankToFutureByFuture(
        CThostFtdcReqTransferField * pReqTransfer,
        CThostFtdcRspInfoField * pRspInfo
    );

    ///期货发起查询银行余额错误回报
    virtual void OnErrRtnQueryBankBalanceByFuture(
        CThostFtdcReqQueryAccountField * pReqQueryAccount,
        CThostFtdcRspInfoField * pRspInfo
    );

    ///报单操作错误回报
    virtual void OnErrRtnOrderAction(
        CThostFtdcOrderActionField * pOrderAction,
        CThostFtdcRspInfoField * pRspInfo
    );



    /**********************************************************
    *                     onRspError方法                       *
    ***********************************************************/

    ///错误应答
    virtual void OnRspError(
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );


};