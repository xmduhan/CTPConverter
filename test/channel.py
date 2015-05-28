# -*- coding: utf-8 -*-



class CTPChannel :
    '''
    CTP通讯管道类,该类和CTPConverter进程通讯,对外实现python语言封装的CTP接口,在设计上该类
    既支持同步接口也支持异步接口,但是目前暂时先实现同步接口.
    '''

    def __init__():
        '''
        初始化过程
        '''
        address = os.getenv('CTP_REQUEST_PIPE',None)
        assert address
        # 连接request通讯管道
    	context = zmq.Context()
    	socket = context.socket(zmq.DEALER)
    	socket.connect(address)
    	socket.setsockopt(zmq.LINGER,0)
        self.request = socket



    
	///请求查询资金账户
    def QryTradingAccount(self,CThostFtdcQryTradingAccountField):
        pass


    
	///请求查询保证金监管系统经纪公司资金账户密钥
    def QryCFMMCTradingAccountKey(self,CThostFtdcQryCFMMCTradingAccountKeyField):
        pass


    
	///用户口令更新请求
    def UserPasswordUpdate(self,CThostFtdcUserPasswordUpdateField):
        pass


    
	///请求查询交易通知
    def QryTradingNotice(self,CThostFtdcQryTradingNoticeField):
        pass


    
	///请求查询成交
    def QryTrade(self,CThostFtdcQryTradeField):
        pass


    
	///查询最大报单数量请求
    def QueryMaxOrderVolume(self,CThostFtdcQueryMaxOrderVolumeField):
        pass


    
	///投资者结算结果确认
    def SettlementInfoConfirm(self,CThostFtdcSettlementInfoConfirmField):
        pass


    
	///请求查询投资者持仓
    def QryInvestorPosition(self,CThostFtdcQryInvestorPositionField):
        pass


    
	///请求查询经纪公司交易算法
    def QryBrokerTradingAlgos(self,CThostFtdcQryBrokerTradingAlgosField):
        pass


    
	///请求查询报单
    def QryOrder(self,CThostFtdcQryOrderField):
        pass


    
	///请求查询交易所
    def QryExchange(self,CThostFtdcQryExchangeField):
        pass


    
	///用户登录请求
    def UserLogin(self,CThostFtdcReqUserLoginField):
        pass


    
	///期货发起期货资金转银行请求
    def FromFutureToBankByFuture(self,CThostFtdcReqTransferField):
        pass


    
	///请求查询汇率
    def QryExchangeRate(self,CThostFtdcQryExchangeRateField):
        pass


    
	///请求查询投资者持仓明细
    def QryInvestorPositionDetail(self,CThostFtdcQryInvestorPositionDetailField):
        pass


    
	///请求查询结算信息确认
    def QrySettlementInfoConfirm(self,CThostFtdcQrySettlementInfoConfirmField):
        pass


    
	///请求查询经纪公司交易参数
    def QryBrokerTradingParams(self,CThostFtdcQryBrokerTradingParamsField):
        pass


    
	///请求查询监控中心用户令牌
    def QueryCFMMCTradingAccountToken(self,CThostFtdcQueryCFMMCTradingAccountTokenField):
        pass


    
	///请求查询客户通知
    def QryNotice(self,CThostFtdcQryNoticeField):
        pass


    
	///期货发起银行资金转期货请求
    def FromBankToFutureByFuture(self,CThostFtdcReqTransferField):
        pass


    
	///预埋单录入请求
    def ParkedOrderInsert(self,CThostFtdcParkedOrderField):
        pass


    
	///请求查询投资者持仓明细
    def QryInvestorPositionCombineDetail(self,CThostFtdcQryInvestorPositionCombineDetailField):
        pass


    
	///报单录入请求
    def OrderInsert(self,CThostFtdcInputOrderField):
        pass


    
	///请求查询二级代理操作员银期权限
    def QrySecAgentACIDMap(self,CThostFtdcQrySecAgentACIDMapField):
        pass


    
	///预埋撤单录入请求
    def ParkedOrderAction(self,CThostFtdcParkedOrderActionField):
        pass


    
	///期货发起查询银行余额请求
    def QueryBankAccountMoneyByFuture(self,CThostFtdcReqQueryAccountField):
        pass


    
	///请求查询预埋撤单
    def QryParkedOrderAction(self,CThostFtdcQryParkedOrderActionField):
        pass


    
	///客户端认证请求
    def Authenticate(self,CThostFtdcReqAuthenticateField):
        pass


    
	///请求查询交易所保证金率
    def QryExchangeMarginRate(self,CThostFtdcQryExchangeMarginRateField):
        pass


    
	///资金账户口令更新请求
    def TradingAccountPasswordUpdate(self,CThostFtdcTradingAccountPasswordUpdateField):
        pass


    
	///登出请求
    def UserLogout(self,CThostFtdcUserLogoutField):
        pass


    
	///请求查询合约
    def QryInstrument(self,CThostFtdcQryInstrumentField):
        pass


    
	///报单操作请求
    def OrderAction(self,CThostFtdcInputOrderActionField):
        pass


    
	///请求查询合约手续费率
    def QryInstrumentCommissionRate(self,CThostFtdcQryInstrumentCommissionRateField):
        pass


    
	///请求查询合约保证金率
    def QryInstrumentMarginRate(self,CThostFtdcQryInstrumentMarginRateField):
        pass


    
	///请求查询投资者
    def QryInvestor(self,CThostFtdcQryInvestorField):
        pass


    
	///请求查询交易所调整保证金率
    def QryExchangeMarginRateAdjust(self,CThostFtdcQryExchangeMarginRateAdjustField):
        pass


    
	///请求查询投资者品种/跨品种保证金
    def QryInvestorProductGroupMargin(self,CThostFtdcQryInvestorProductGroupMarginField):
        pass


    
	///请求查询仓单折抵信息
    def QryEWarrantOffset(self,CThostFtdcQryEWarrantOffsetField):
        pass


    
	///请求查询行情
    def QryDepthMarketData(self,CThostFtdcQryDepthMarketDataField):
        pass


    
	///请求查询转帐银行
    def QryTransferBank(self,CThostFtdcQryTransferBankField):
        pass


    
	///请求删除预埋撤单
    def RemoveParkedOrderAction(self,CThostFtdcRemoveParkedOrderActionField):
        pass


    
	///请求查询产品
    def QryProduct(self,CThostFtdcQryProductField):
        pass


    
	///请求查询交易编码
    def QryTradingCode(self,CThostFtdcQryTradingCodeField):
        pass


    
	///请求查询投资者结算结果
    def QrySettlementInfo(self,CThostFtdcQrySettlementInfoField):
        pass


    
	///请求查询银期签约关系
    def QryAccountregister(self,CThostFtdcQryAccountregisterField):
        pass


    
	///请求查询预埋单
    def QryParkedOrder(self,CThostFtdcQryParkedOrderField):
        pass


    
	///请求查询转帐流水
    def QryTransferSerial(self,CThostFtdcQryTransferSerialField):
        pass


    
	///请求查询签约银行
    def QryContractBank(self,CThostFtdcQryContractBankField):
        pass


    
	///请求删除预埋单
    def RemoveParkedOrder(self,CThostFtdcRemoveParkedOrderField):
        pass

