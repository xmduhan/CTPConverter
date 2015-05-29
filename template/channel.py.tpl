# -*- coding: utf-8 -*-

import os
import zmq
import json
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


{% for method in reqMethodDict.itervalues() %}
    {% set parameter = method['parameters'][0]  %}
    def {{ method['name'][3:]}}(self,data,metaData={}):
		'''
		{{ method['remark'][3:] }}
		data 调用api需要填写参数表单,类型为{{parameter['raw_type']}},具体定义参见CTPStruct.py
		metaData 调用函数时的附加信息
		TODO 同步调用似乎不需要附加信息
		返回信息格式[errorCode,errorMessage,responseData=[...]]
		'''
		if not isinstance(data,{{parameter['raw_type']}}):
			return -2000,u'参数表单类型不正确',[]
			pass


		requestApiName = 'Req{{method['name'][3:]}}'
		responseApiName = 'OnRsp{{method['name'][3:]}}'

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
		poller.register(self.request, zmq.POLLIN)
		sockets = dict(poller.poll(self.timeout))
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

		respnoseDataList = []
		while(True):
			sockets = dict(poller.poll(self.timeout))
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
			errorID = respInfo['Parameters']['RspInfo']['ErrorID']
			errorMsg = respInfo['Parameters']['RspInfo']['ErrorMsg']

			if errorID != 0 :
				return errorID,errorMsg,[]

			respnoseData = respInfo['Parameters']['Data']
			# TODO 将数据转化为对象格式
			respnoseDataList.append(respnoseData)

			# 已处理完最后一条消息
			if int(responseMessage.isLast) == 1:
				break;

		# 返回成功
		return 0,'',respnoseDataList



{% endfor %}
