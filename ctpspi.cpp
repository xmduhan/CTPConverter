
#include <ThostFtdcTraderApi.h>




class CTraderHandler : public CThostFtdcTraderSpi {

public:


    virtual void OnRspQryInstrument(
        CThostFtdcInstrumentField * pInstrument,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQrySettlementInfo(
        CThostFtdcSettlementInfoField * pSettlementInfo,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspParkedOrderInsert(
        CThostFtdcParkedOrderField * pParkedOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryExchange(
        CThostFtdcExchangeField * pExchange,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspOrderAction(
        CThostFtdcInputOrderActionField * pInputOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryInvestor(
        CThostFtdcInvestorField * pInvestor,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspRemoveParkedOrder(
        CThostFtdcRemoveParkedOrderField * pRemoveParkedOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryInvestorProductGroupMargin(
        CThostFtdcInvestorProductGroupMarginField * pInvestorProductGroupMargin,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryTransferBank(
        CThostFtdcTransferBankField * pTransferBank,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryBrokerTradingAlgos(
        CThostFtdcBrokerTradingAlgosField * pBrokerTradingAlgos,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryProduct(
        CThostFtdcProductField * pProduct,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryInstrumentMarginRate(
        CThostFtdcInstrumentMarginRateField * pInstrumentMarginRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspError(
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryCFMMCTradingAccountKey(
        CThostFtdcCFMMCTradingAccountKeyField * pCFMMCTradingAccountKey,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspUserLogin(
        CThostFtdcRspUserLoginField * pRspUserLogin,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspFromFutureToBankByFuture(
        CThostFtdcReqTransferField * pReqTransfer,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQueryCFMMCTradingAccountToken(
        CThostFtdcQueryCFMMCTradingAccountTokenField * pQueryCFMMCTradingAccountToken,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryContractBank(
        CThostFtdcContractBankField * pContractBank,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspOrderInsert(
        CThostFtdcInputOrderField * pInputOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryEWarrantOffset(
        CThostFtdcEWarrantOffsetField * pEWarrantOffset,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspUserPasswordUpdate(
        CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryExchangeMarginRateAdjust(
        CThostFtdcExchangeMarginRateAdjustField * pExchangeMarginRateAdjust,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspFromBankToFutureByFuture(
        CThostFtdcReqTransferField * pReqTransfer,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryInvestorPositionCombineDetail(
        CThostFtdcInvestorPositionCombineDetailField * pInvestorPositionCombineDetail,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspSettlementInfoConfirm(
        CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryAccountregister(
        CThostFtdcAccountregisterField * pAccountregister,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQrySecAgentACIDMap(
        CThostFtdcSecAgentACIDMapField * pSecAgentACIDMap,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryTradingCode(
        CThostFtdcTradingCodeField * pTradingCode,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQrySettlementInfoConfirm(
        CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryTransferSerial(
        CThostFtdcTransferSerialField * pTransferSerial,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryInvestorPosition(
        CThostFtdcInvestorPositionField * pInvestorPosition,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspUserLogout(
        CThostFtdcUserLogoutField * pUserLogout,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryInvestorPositionDetail(
        CThostFtdcInvestorPositionDetailField * pInvestorPositionDetail,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryParkedOrderAction(
        CThostFtdcParkedOrderActionField * pParkedOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryBrokerTradingParams(
        CThostFtdcBrokerTradingParamsField * pBrokerTradingParams,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryExchangeMarginRate(
        CThostFtdcExchangeMarginRateField * pExchangeMarginRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryParkedOrder(
        CThostFtdcParkedOrderField * pParkedOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQueryBankAccountMoneyByFuture(
        CThostFtdcReqQueryAccountField * pReqQueryAccount,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspAuthenticate(
        CThostFtdcRspAuthenticateField * pRspAuthenticateField,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQueryMaxOrderVolume(
        CThostFtdcQueryMaxOrderVolumeField * pQueryMaxOrderVolume,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryExchangeRate(
        CThostFtdcExchangeRateField * pExchangeRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryTradingNotice(
        CThostFtdcTradingNoticeField * pTradingNotice,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspParkedOrderAction(
        CThostFtdcParkedOrderActionField * pParkedOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryNotice(
        CThostFtdcNoticeField * pNotice,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryTradingAccount(
        CThostFtdcTradingAccountField * pTradingAccount,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspTradingAccountPasswordUpdate(
        CThostFtdcTradingAccountPasswordUpdateField * pTradingAccountPasswordUpdate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryOrder(
        CThostFtdcOrderField * pOrder,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryDepthMarketData(
        CThostFtdcDepthMarketDataField * pDepthMarketData,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryInstrumentCommissionRate(
        CThostFtdcInstrumentCommissionRateField * pInstrumentCommissionRate,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspRemoveParkedOrderAction(
        CThostFtdcRemoveParkedOrderActionField * pRemoveParkedOrderAction,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


    virtual void OnRspQryTrade(
        CThostFtdcTradeField * pTrade,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    ) {

    }


};