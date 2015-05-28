# -*- coding: utf-8 -*-

import os
import zmq
from CTPStruct import *
from message import *


def packageReqInfo(apiName,data):
	'''
	获取一个默认的调用结构
	'''
	reqInfo = {}
	reqInfo['RequestMethod'] = apiName
	parameters = {}
	reqInfo['Parameters'] = parameters
	parameters['Data'] = data
	return reqInfo



class InvalidInputFormat(Exception):
    '''
    数据格式不正确
    '''

    def __init__(self,expect):
        self.value = u'输入的数据格式错误,要求是:%s' %  expect

    def __str__(self):
        return repr(self.value)



class CTPChannel :
    '''
    CTP通讯管道类,该类和CTPConverter进程通讯,对外实现python语言封装的CTP接口,在设计上该类
    既支持同步接口也支持异步接口,但是目前暂时先实现同步接口.
    '''

    def __init__(self):
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
        self.timeout = 1000



    
    def QryTradingAccount(self,data,metaData={}):
        '''
        请求查询资金账户
        '''
        if not isinstance(data,CThostFtdcQryTradingAccountField):
            raise InvalidInputFormat(CThostFtdcQryTradingAccountField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryCFMMCTradingAccountKey(self,data,metaData={}):
        '''
        请求查询保证金监管系统经纪公司资金账户密钥
        '''
        if not isinstance(data,CThostFtdcQryCFMMCTradingAccountKeyField):
            raise InvalidInputFormat(CThostFtdcQryCFMMCTradingAccountKeyField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def UserPasswordUpdate(self,data,metaData={}):
        '''
        用户口令更新请求
        '''
        if not isinstance(data,CThostFtdcUserPasswordUpdateField):
            raise InvalidInputFormat(CThostFtdcUserPasswordUpdateField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryTradingNotice(self,data,metaData={}):
        '''
        请求查询交易通知
        '''
        if not isinstance(data,CThostFtdcQryTradingNoticeField):
            raise InvalidInputFormat(CThostFtdcQryTradingNoticeField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryTrade(self,data,metaData={}):
        '''
        请求查询成交
        '''
        if not isinstance(data,CThostFtdcQryTradeField):
            raise InvalidInputFormat(CThostFtdcQryTradeField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QueryMaxOrderVolume(self,data,metaData={}):
        '''
        查询最大报单数量请求
        '''
        if not isinstance(data,CThostFtdcQueryMaxOrderVolumeField):
            raise InvalidInputFormat(CThostFtdcQueryMaxOrderVolumeField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def SettlementInfoConfirm(self,data,metaData={}):
        '''
        投资者结算结果确认
        '''
        if not isinstance(data,CThostFtdcSettlementInfoConfirmField):
            raise InvalidInputFormat(CThostFtdcSettlementInfoConfirmField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInvestorPosition(self,data,metaData={}):
        '''
        请求查询投资者持仓
        '''
        if not isinstance(data,CThostFtdcQryInvestorPositionField):
            raise InvalidInputFormat(CThostFtdcQryInvestorPositionField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryBrokerTradingAlgos(self,data,metaData={}):
        '''
        请求查询经纪公司交易算法
        '''
        if not isinstance(data,CThostFtdcQryBrokerTradingAlgosField):
            raise InvalidInputFormat(CThostFtdcQryBrokerTradingAlgosField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryOrder(self,data,metaData={}):
        '''
        请求查询报单
        '''
        if not isinstance(data,CThostFtdcQryOrderField):
            raise InvalidInputFormat(CThostFtdcQryOrderField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryExchange(self,data,metaData={}):
        '''
        请求查询交易所
        '''
        if not isinstance(data,CThostFtdcQryExchangeField):
            raise InvalidInputFormat(CThostFtdcQryExchangeField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def UserLogin(self,data,metaData={}):
        '''
        用户登录请求
        '''
        if not isinstance(data,CThostFtdcReqUserLoginField):
            raise InvalidInputFormat(CThostFtdcReqUserLoginField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def FromFutureToBankByFuture(self,data,metaData={}):
        '''
        期货发起期货资金转银行请求
        '''
        if not isinstance(data,CThostFtdcReqTransferField):
            raise InvalidInputFormat(CThostFtdcReqTransferField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryExchangeRate(self,data,metaData={}):
        '''
        请求查询汇率
        '''
        if not isinstance(data,CThostFtdcQryExchangeRateField):
            raise InvalidInputFormat(CThostFtdcQryExchangeRateField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInvestorPositionDetail(self,data,metaData={}):
        '''
        请求查询投资者持仓明细
        '''
        if not isinstance(data,CThostFtdcQryInvestorPositionDetailField):
            raise InvalidInputFormat(CThostFtdcQryInvestorPositionDetailField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QrySettlementInfoConfirm(self,data,metaData={}):
        '''
        请求查询结算信息确认
        '''
        if not isinstance(data,CThostFtdcQrySettlementInfoConfirmField):
            raise InvalidInputFormat(CThostFtdcQrySettlementInfoConfirmField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryBrokerTradingParams(self,data,metaData={}):
        '''
        请求查询经纪公司交易参数
        '''
        if not isinstance(data,CThostFtdcQryBrokerTradingParamsField):
            raise InvalidInputFormat(CThostFtdcQryBrokerTradingParamsField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QueryCFMMCTradingAccountToken(self,data,metaData={}):
        '''
        请求查询监控中心用户令牌
        '''
        if not isinstance(data,CThostFtdcQueryCFMMCTradingAccountTokenField):
            raise InvalidInputFormat(CThostFtdcQueryCFMMCTradingAccountTokenField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryNotice(self,data,metaData={}):
        '''
        请求查询客户通知
        '''
        if not isinstance(data,CThostFtdcQryNoticeField):
            raise InvalidInputFormat(CThostFtdcQryNoticeField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def FromBankToFutureByFuture(self,data,metaData={}):
        '''
        期货发起银行资金转期货请求
        '''
        if not isinstance(data,CThostFtdcReqTransferField):
            raise InvalidInputFormat(CThostFtdcReqTransferField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def ParkedOrderInsert(self,data,metaData={}):
        '''
        预埋单录入请求
        '''
        if not isinstance(data,CThostFtdcParkedOrderField):
            raise InvalidInputFormat(CThostFtdcParkedOrderField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInvestorPositionCombineDetail(self,data,metaData={}):
        '''
        请求查询投资者持仓明细
        '''
        if not isinstance(data,CThostFtdcQryInvestorPositionCombineDetailField):
            raise InvalidInputFormat(CThostFtdcQryInvestorPositionCombineDetailField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def OrderInsert(self,data,metaData={}):
        '''
        报单录入请求
        '''
        if not isinstance(data,CThostFtdcInputOrderField):
            raise InvalidInputFormat(CThostFtdcInputOrderField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QrySecAgentACIDMap(self,data,metaData={}):
        '''
        请求查询二级代理操作员银期权限
        '''
        if not isinstance(data,CThostFtdcQrySecAgentACIDMapField):
            raise InvalidInputFormat(CThostFtdcQrySecAgentACIDMapField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def ParkedOrderAction(self,data,metaData={}):
        '''
        预埋撤单录入请求
        '''
        if not isinstance(data,CThostFtdcParkedOrderActionField):
            raise InvalidInputFormat(CThostFtdcParkedOrderActionField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QueryBankAccountMoneyByFuture(self,data,metaData={}):
        '''
        期货发起查询银行余额请求
        '''
        if not isinstance(data,CThostFtdcReqQueryAccountField):
            raise InvalidInputFormat(CThostFtdcReqQueryAccountField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryParkedOrderAction(self,data,metaData={}):
        '''
        请求查询预埋撤单
        '''
        if not isinstance(data,CThostFtdcQryParkedOrderActionField):
            raise InvalidInputFormat(CThostFtdcQryParkedOrderActionField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def Authenticate(self,data,metaData={}):
        '''
        客户端认证请求
        '''
        if not isinstance(data,CThostFtdcReqAuthenticateField):
            raise InvalidInputFormat(CThostFtdcReqAuthenticateField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryExchangeMarginRate(self,data,metaData={}):
        '''
        请求查询交易所保证金率
        '''
        if not isinstance(data,CThostFtdcQryExchangeMarginRateField):
            raise InvalidInputFormat(CThostFtdcQryExchangeMarginRateField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def TradingAccountPasswordUpdate(self,data,metaData={}):
        '''
        资金账户口令更新请求
        '''
        if not isinstance(data,CThostFtdcTradingAccountPasswordUpdateField):
            raise InvalidInputFormat(CThostFtdcTradingAccountPasswordUpdateField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def UserLogout(self,data,metaData={}):
        '''
        登出请求
        '''
        if not isinstance(data,CThostFtdcUserLogoutField):
            raise InvalidInputFormat(CThostFtdcUserLogoutField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInstrument(self,data,metaData={}):
        '''
        请求查询合约
        '''
        if not isinstance(data,CThostFtdcQryInstrumentField):
            raise InvalidInputFormat(CThostFtdcQryInstrumentField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def OrderAction(self,data,metaData={}):
        '''
        报单操作请求
        '''
        if not isinstance(data,CThostFtdcInputOrderActionField):
            raise InvalidInputFormat(CThostFtdcInputOrderActionField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInstrumentCommissionRate(self,data,metaData={}):
        '''
        请求查询合约手续费率
        '''
        if not isinstance(data,CThostFtdcQryInstrumentCommissionRateField):
            raise InvalidInputFormat(CThostFtdcQryInstrumentCommissionRateField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInstrumentMarginRate(self,data,metaData={}):
        '''
        请求查询合约保证金率
        '''
        if not isinstance(data,CThostFtdcQryInstrumentMarginRateField):
            raise InvalidInputFormat(CThostFtdcQryInstrumentMarginRateField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInvestor(self,data,metaData={}):
        '''
        请求查询投资者
        '''
        if not isinstance(data,CThostFtdcQryInvestorField):
            raise InvalidInputFormat(CThostFtdcQryInvestorField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryExchangeMarginRateAdjust(self,data,metaData={}):
        '''
        请求查询交易所调整保证金率
        '''
        if not isinstance(data,CThostFtdcQryExchangeMarginRateAdjustField):
            raise InvalidInputFormat(CThostFtdcQryExchangeMarginRateAdjustField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryInvestorProductGroupMargin(self,data,metaData={}):
        '''
        请求查询投资者品种/跨品种保证金
        '''
        if not isinstance(data,CThostFtdcQryInvestorProductGroupMarginField):
            raise InvalidInputFormat(CThostFtdcQryInvestorProductGroupMarginField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryEWarrantOffset(self,data,metaData={}):
        '''
        请求查询仓单折抵信息
        '''
        if not isinstance(data,CThostFtdcQryEWarrantOffsetField):
            raise InvalidInputFormat(CThostFtdcQryEWarrantOffsetField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryDepthMarketData(self,data,metaData={}):
        '''
        请求查询行情
        '''
        if not isinstance(data,CThostFtdcQryDepthMarketDataField):
            raise InvalidInputFormat(CThostFtdcQryDepthMarketDataField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryTransferBank(self,data,metaData={}):
        '''
        请求查询转帐银行
        '''
        if not isinstance(data,CThostFtdcQryTransferBankField):
            raise InvalidInputFormat(CThostFtdcQryTransferBankField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def RemoveParkedOrderAction(self,data,metaData={}):
        '''
        请求删除预埋撤单
        '''
        if not isinstance(data,CThostFtdcRemoveParkedOrderActionField):
            raise InvalidInputFormat(CThostFtdcRemoveParkedOrderActionField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryProduct(self,data,metaData={}):
        '''
        请求查询产品
        '''
        if not isinstance(data,CThostFtdcQryProductField):
            raise InvalidInputFormat(CThostFtdcQryProductField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryTradingCode(self,data,metaData={}):
        '''
        请求查询交易编码
        '''
        if not isinstance(data,CThostFtdcQryTradingCodeField):
            raise InvalidInputFormat(CThostFtdcQryTradingCodeField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QrySettlementInfo(self,data,metaData={}):
        '''
        请求查询投资者结算结果
        '''
        if not isinstance(data,CThostFtdcQrySettlementInfoField):
            raise InvalidInputFormat(CThostFtdcQrySettlementInfoField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryAccountregister(self,data,metaData={}):
        '''
        请求查询银期签约关系
        '''
        if not isinstance(data,CThostFtdcQryAccountregisterField):
            raise InvalidInputFormat(CThostFtdcQryAccountregisterField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryParkedOrder(self,data,metaData={}):
        '''
        请求查询预埋单
        '''
        if not isinstance(data,CThostFtdcQryParkedOrderField):
            raise InvalidInputFormat(CThostFtdcQryParkedOrderField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryTransferSerial(self,data,metaData={}):
        '''
        请求查询转帐流水
        '''
        if not isinstance(data,CThostFtdcQryTransferSerialField):
            raise InvalidInputFormat(CThostFtdcQryTransferSerialField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def QryContractBank(self,data,metaData={}):
        '''
        请求查询签约银行
        '''
        if not isinstance(data,CThostFtdcQryContractBankField):
            raise InvalidInputFormat(CThostFtdcQryContractBankField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)





    
    def RemoveParkedOrder(self,data,metaData={}):
        '''
        请求删除预埋单
        '''
        if not isinstance(data,CThostFtdcRemoveParkedOrderField):
            raise InvalidInputFormat(CThostFtdcRemoveParkedOrderField)

        requestApiName = 'Req%s' % method['name'][3:]
    	responseApiName = 'OnRsp%s' % method['name'][3:]

        # 打包消息格式
        reqInfo = packageReqInfo(requestApiName,data.toDict())
    	requestMessage = RequestMessage()
    	requestMessage.header = 'REQUEST'
    	requestMessage.apiName = requestApiName
    	requestMessage.reqInfo = json.dumps(reqInfo)
    	requestMessage.metaData = json.dumps(metaData)

        # 发送到服务器
        requestMessage.send(self.request)




