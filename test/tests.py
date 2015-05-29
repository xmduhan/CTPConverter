# -*- coding: utf-8 -*-
import os
import zmq
import json
from datetime import datetime
from time import sleep
from message import *
from channel import CTPChannel
from CTPStruct import *


def getDefaultReqInfo(apiName):
	'''
	获取一个默认的调用结构
	'''
	reqInfo = {}
	reqInfo['RequestMethod'] = apiName
	Parameters = {}
	reqInfo['Parameters'] = Parameters
	Data = {}
	Parameters['Data'] = Data
	return reqInfo



def test_ReqQryTradingAccount_0():
	'''
	测试ReqQryTradingAccount xxx
	其他的一些说明
	'''
	requestApiName = 'ReqQryTradingAccount'
	responseApiName = 'OnRspQryTradingAccount'
	timeout = 1000

	# 初始化变量
	#address = 'tcp://localhost:10001'
	address = os.getenv('CTP_REQUEST_PIPE',None)
	assert address

	# 连接request通讯管道
	context = zmq.Context()
	socket = context.socket(zmq.DEALER)
	socket.connect(address)
	socket.setsockopt(zmq.LINGER,0)

	# 准备调用接口数据
	reqInfo = getDefaultReqInfo(requestApiName)
	data = reqInfo['Parameters']['Data']
	metaData = {}
	# TODO 填写对应的请求参数(data)

	requestMessage = RequestMessage()
	requestMessage.header = 'REQUEST'
	requestMessage.apiName = requestApiName
	requestMessage.reqInfo = json.dumps(reqInfo)
	requestMessage.metaData = json.dumps(metaData)

	# 开始计时
	startTime = datetime.now()
	# 向协议转换器发出请求
	requestMessage.send(socket)
	################### 等待服务器的REQUESTID响应 ###################
	poller = zmq.Poller()
	poller.register(socket, zmq.POLLIN)
	sockets = dict(poller.poll(timeout))
	assert socket in sockets

	# 从request通讯管道读取返回信息
	requestIDMessage = RequestIDMessage()
	requestIDMessage.recv(socket)
	# 检查立即返回信息的格式
	assert requestIDMessage.header == 'REQUESTID'
	assert int(requestIDMessage.requestID) > 0
	assert requestIDMessage.apiName == requestApiName
	assert requestIDMessage.errorInfo == ''
	assert requestIDMessage.metaData == json.dumps(metaData)


	################### 等待服务器的返回的数据信息 ###################
	poller = zmq.Poller()
	poller.register(socket, zmq.POLLIN)
	sockets = dict(poller.poll(timeout))
	assert socket in sockets

	# 从request通讯管道读取返回信息
	responseMessage = ResponseMessage()
	responseMessage.recv(socket)

	# 返回数据信息格式
	assert responseMessage.header == 'RESPONSE'
	assert responseMessage.requestID == requestIDMessage.requestID
	assert responseMessage.apiName == responseApiName
	assert int(responseMessage.isLast) == 1
	assert responseMessage.metaData == json.dumps(metaData)

	# TODO 显示关键信息

	endTime = datetime.now()
	timeDelta = endTime - startTime
	print timeDelta.total_seconds()
	sleep(1)


def test_ReqQryTradingAccount_1():
	'''

	'''
	ch = CTPChannel()
	data = CThostFtdcQryTradingAccountField()
	print ch.QryTradingAccount(data)
	


#
