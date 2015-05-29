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


class ResponseTimeOut(Exception):
    '''
    请求超时未响应
    '''

    def __init__(self):
        self.value = u'请求超时未响应'

    def __str__(self):
        return repr(self.value)


class InvalidMessageFormat(Exception):
    '''
    接收到的消息格式不正确
    '''

    def __init__(self,expect,fact):
        self.value = u'接收到的消息格式不正确,期待:%s,实际:%s.' %  (expect,fact)

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
        self.timeout = 1000 * 5



    
    def QryTradingAccount(self,data,metaData={}):
        '''
        请求查询资金账户
		data 调用api需要填写参数表单,类型为CThostFtdcQryTradingAccountField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryTradingAccountField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryCFMMCTradingAccountKey(self,data,metaData={}):
        '''
        请求查询保证金监管系统经纪公司资金账户密钥
		data 调用api需要填写参数表单,类型为CThostFtdcQryCFMMCTradingAccountKeyField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryCFMMCTradingAccountKeyField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def UserPasswordUpdate(self,data,metaData={}):
        '''
        用户口令更新请求
		data 调用api需要填写参数表单,类型为CThostFtdcUserPasswordUpdateField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcUserPasswordUpdateField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryTradingNotice(self,data,metaData={}):
        '''
        请求查询交易通知
		data 调用api需要填写参数表单,类型为CThostFtdcQryTradingNoticeField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryTradingNoticeField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryTrade(self,data,metaData={}):
        '''
        请求查询成交
		data 调用api需要填写参数表单,类型为CThostFtdcQryTradeField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryTradeField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QueryMaxOrderVolume(self,data,metaData={}):
        '''
        查询最大报单数量请求
		data 调用api需要填写参数表单,类型为CThostFtdcQueryMaxOrderVolumeField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQueryMaxOrderVolumeField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def SettlementInfoConfirm(self,data,metaData={}):
        '''
        投资者结算结果确认
		data 调用api需要填写参数表单,类型为CThostFtdcSettlementInfoConfirmField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcSettlementInfoConfirmField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInvestorPosition(self,data,metaData={}):
        '''
        请求查询投资者持仓
		data 调用api需要填写参数表单,类型为CThostFtdcQryInvestorPositionField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInvestorPositionField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryBrokerTradingAlgos(self,data,metaData={}):
        '''
        请求查询经纪公司交易算法
		data 调用api需要填写参数表单,类型为CThostFtdcQryBrokerTradingAlgosField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryBrokerTradingAlgosField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryOrder(self,data,metaData={}):
        '''
        请求查询报单
		data 调用api需要填写参数表单,类型为CThostFtdcQryOrderField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryOrderField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryExchange(self,data,metaData={}):
        '''
        请求查询交易所
		data 调用api需要填写参数表单,类型为CThostFtdcQryExchangeField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryExchangeField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def UserLogin(self,data,metaData={}):
        '''
        用户登录请求
		data 调用api需要填写参数表单,类型为CThostFtdcReqUserLoginField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcReqUserLoginField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def FromFutureToBankByFuture(self,data,metaData={}):
        '''
        期货发起期货资金转银行请求
		data 调用api需要填写参数表单,类型为CThostFtdcReqTransferField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcReqTransferField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryExchangeRate(self,data,metaData={}):
        '''
        请求查询汇率
		data 调用api需要填写参数表单,类型为CThostFtdcQryExchangeRateField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryExchangeRateField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInvestorPositionDetail(self,data,metaData={}):
        '''
        请求查询投资者持仓明细
		data 调用api需要填写参数表单,类型为CThostFtdcQryInvestorPositionDetailField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInvestorPositionDetailField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QrySettlementInfoConfirm(self,data,metaData={}):
        '''
        请求查询结算信息确认
		data 调用api需要填写参数表单,类型为CThostFtdcQrySettlementInfoConfirmField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQrySettlementInfoConfirmField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryBrokerTradingParams(self,data,metaData={}):
        '''
        请求查询经纪公司交易参数
		data 调用api需要填写参数表单,类型为CThostFtdcQryBrokerTradingParamsField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryBrokerTradingParamsField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QueryCFMMCTradingAccountToken(self,data,metaData={}):
        '''
        请求查询监控中心用户令牌
		data 调用api需要填写参数表单,类型为CThostFtdcQueryCFMMCTradingAccountTokenField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQueryCFMMCTradingAccountTokenField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryNotice(self,data,metaData={}):
        '''
        请求查询客户通知
		data 调用api需要填写参数表单,类型为CThostFtdcQryNoticeField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryNoticeField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def FromBankToFutureByFuture(self,data,metaData={}):
        '''
        期货发起银行资金转期货请求
		data 调用api需要填写参数表单,类型为CThostFtdcReqTransferField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcReqTransferField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def ParkedOrderInsert(self,data,metaData={}):
        '''
        预埋单录入请求
		data 调用api需要填写参数表单,类型为CThostFtdcParkedOrderField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcParkedOrderField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInvestorPositionCombineDetail(self,data,metaData={}):
        '''
        请求查询投资者持仓明细
		data 调用api需要填写参数表单,类型为CThostFtdcQryInvestorPositionCombineDetailField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInvestorPositionCombineDetailField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def OrderInsert(self,data,metaData={}):
        '''
        报单录入请求
		data 调用api需要填写参数表单,类型为CThostFtdcInputOrderField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcInputOrderField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QrySecAgentACIDMap(self,data,metaData={}):
        '''
        请求查询二级代理操作员银期权限
		data 调用api需要填写参数表单,类型为CThostFtdcQrySecAgentACIDMapField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQrySecAgentACIDMapField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def ParkedOrderAction(self,data,metaData={}):
        '''
        预埋撤单录入请求
		data 调用api需要填写参数表单,类型为CThostFtdcParkedOrderActionField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcParkedOrderActionField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QueryBankAccountMoneyByFuture(self,data,metaData={}):
        '''
        期货发起查询银行余额请求
		data 调用api需要填写参数表单,类型为CThostFtdcReqQueryAccountField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcReqQueryAccountField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryParkedOrderAction(self,data,metaData={}):
        '''
        请求查询预埋撤单
		data 调用api需要填写参数表单,类型为CThostFtdcQryParkedOrderActionField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryParkedOrderActionField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def Authenticate(self,data,metaData={}):
        '''
        客户端认证请求
		data 调用api需要填写参数表单,类型为CThostFtdcReqAuthenticateField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcReqAuthenticateField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryExchangeMarginRate(self,data,metaData={}):
        '''
        请求查询交易所保证金率
		data 调用api需要填写参数表单,类型为CThostFtdcQryExchangeMarginRateField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryExchangeMarginRateField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def TradingAccountPasswordUpdate(self,data,metaData={}):
        '''
        资金账户口令更新请求
		data 调用api需要填写参数表单,类型为CThostFtdcTradingAccountPasswordUpdateField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcTradingAccountPasswordUpdateField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def UserLogout(self,data,metaData={}):
        '''
        登出请求
		data 调用api需要填写参数表单,类型为CThostFtdcUserLogoutField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcUserLogoutField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInstrument(self,data,metaData={}):
        '''
        请求查询合约
		data 调用api需要填写参数表单,类型为CThostFtdcQryInstrumentField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInstrumentField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def OrderAction(self,data,metaData={}):
        '''
        报单操作请求
		data 调用api需要填写参数表单,类型为CThostFtdcInputOrderActionField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcInputOrderActionField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInstrumentCommissionRate(self,data,metaData={}):
        '''
        请求查询合约手续费率
		data 调用api需要填写参数表单,类型为CThostFtdcQryInstrumentCommissionRateField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInstrumentCommissionRateField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInstrumentMarginRate(self,data,metaData={}):
        '''
        请求查询合约保证金率
		data 调用api需要填写参数表单,类型为CThostFtdcQryInstrumentMarginRateField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInstrumentMarginRateField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInvestor(self,data,metaData={}):
        '''
        请求查询投资者
		data 调用api需要填写参数表单,类型为CThostFtdcQryInvestorField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInvestorField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryExchangeMarginRateAdjust(self,data,metaData={}):
        '''
        请求查询交易所调整保证金率
		data 调用api需要填写参数表单,类型为CThostFtdcQryExchangeMarginRateAdjustField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryExchangeMarginRateAdjustField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryInvestorProductGroupMargin(self,data,metaData={}):
        '''
        请求查询投资者品种/跨品种保证金
		data 调用api需要填写参数表单,类型为CThostFtdcQryInvestorProductGroupMarginField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryInvestorProductGroupMarginField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryEWarrantOffset(self,data,metaData={}):
        '''
        请求查询仓单折抵信息
		data 调用api需要填写参数表单,类型为CThostFtdcQryEWarrantOffsetField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryEWarrantOffsetField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryDepthMarketData(self,data,metaData={}):
        '''
        请求查询行情
		data 调用api需要填写参数表单,类型为CThostFtdcQryDepthMarketDataField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryDepthMarketDataField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryTransferBank(self,data,metaData={}):
        '''
        请求查询转帐银行
		data 调用api需要填写参数表单,类型为CThostFtdcQryTransferBankField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryTransferBankField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def RemoveParkedOrderAction(self,data,metaData={}):
        '''
        请求删除预埋撤单
		data 调用api需要填写参数表单,类型为CThostFtdcRemoveParkedOrderActionField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcRemoveParkedOrderActionField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryProduct(self,data,metaData={}):
        '''
        请求查询产品
		data 调用api需要填写参数表单,类型为CThostFtdcQryProductField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryProductField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryTradingCode(self,data,metaData={}):
        '''
        请求查询交易编码
		data 调用api需要填写参数表单,类型为CThostFtdcQryTradingCodeField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryTradingCodeField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QrySettlementInfo(self,data,metaData={}):
        '''
        请求查询投资者结算结果
		data 调用api需要填写参数表单,类型为CThostFtdcQrySettlementInfoField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQrySettlementInfoField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryAccountregister(self,data,metaData={}):
        '''
        请求查询银期签约关系
		data 调用api需要填写参数表单,类型为CThostFtdcQryAccountregisterField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryAccountregisterField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryParkedOrder(self,data,metaData={}):
        '''
        请求查询预埋单
		data 调用api需要填写参数表单,类型为CThostFtdcQryParkedOrderField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryParkedOrderField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryTransferSerial(self,data,metaData={}):
        '''
        请求查询转帐流水
		data 调用api需要填写参数表单,类型为CThostFtdcQryTransferSerialField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryTransferSerialField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def QryContractBank(self,data,metaData={}):
        '''
        请求查询签约银行
		data 调用api需要填写参数表单,类型为CThostFtdcQryContractBankField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcQryContractBankField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;












    
    def RemoveParkedOrder(self,data,metaData={}):
        '''
        请求删除预埋单
		data 调用api需要填写参数表单,类型为CThostFtdcRemoveParkedOrderField,具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
        '''
        if not isinstance(data,CThostFtdcRemoveParkedOrderField):
            return -2000,u'参数表单类型不正确',[]

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

		################### 等待服务器的REQUESTID响应 ###################
		# 读取服务
		poller = zmq.Poller()
		poller.register(socket, zmq.POLLIN)
		sockets = dict(poller.poll(timeout))
		if not (self.request in sockets) :
			return -2001,u'请求超时收到响应',[]

		# 从request通讯管道读取返回信息
		# TODO 如果在同异步混用的情况下,这个位置无法确定是REQUESTID消息
		requestIDMessage = RequestIDMessage()
		requestIDMessage.recv(self.request)

		if not (requestIDMessage.header == 'REQUESTID'):
			return -2002,u'接收到异常消息格式',[]

		if not (requestIDMessage.apiName == requestApiName) :
			return -2002,u'接收到异常消息格式',[]

		if not (int(requestIDMessage.requestID) > 0):
			errorInfo = json.loads(requestIDMessage.errorInfo)
			return errorInfo['ErrorCode'],errorInfo['ErrorMessage'],[]


		################### 等待服务器的返回的数据信息 ###################
		poller = zmq.Poller()
		poller.register(self.request, zmq.POLLIN)

		respnoseData = []
		while(True):
			sockets = dict(poller.poll(timeout))
			if not (self.request in sockets) :
				return -2001,u'请求超时收到响应',[]

			# 从request通讯管道读取返回信息
			# TODO 如果在同异步混用的情况下,这个位置无法确定是RESPONSE消息
			responseMessage = ResponseMessage()
			responseMessage.recv(self.request)

			# 返回数据信息格式
			if not (responseMessage.header == 'RESPONSE') :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.requestID == requestIDMessage.requestID) :
				return -2002,u'接收到异常消息格式',[]

			if not (responseMessage.apiName == responseApiName) :
				return -2002,u'接收到异常消息格式',[]

			respInfo = json.loads(responseMessage.respInfo)
			print respInfo

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;











