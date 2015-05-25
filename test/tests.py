# -*- coding: utf-8 -*-
import zmq
import json
from datetime import datetime


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

	address = 'tcp://localhost:10001'

	# 准备调用接口数据
	reqHeader = 'REQUEST'
	reqApiName = 'ReqQryTradingAccount'
	reqReqInfo = getDefaultReqInfo(reqApiName)
	data = reqReqInfo['Parameters']['Data']
	reqMetaData = {}

	# 连接request通讯管道
	context = zmq.Context()
	socket = context.socket(zmq.DEALER)
	socket.connect(address)
	socket.setsockopt(zmq.LINGER,0)

	startTime = datetime.now()
	# 向协议转换器发出请求
	socket.send_multipart(
		[reqHeader,reqApiName,json.dumps(reqReqInfo),json.dumps(reqMetaData)]
	)
	################### 等待服务器的REQUESTID响应 ###################
	poller = zmq.Poller()
	poller.register(socket, zmq.POLLIN)
	sockets = dict(poller.poll(100))
	assert socket in sockets

	# 从request通讯管道读取返回信息
	respHeader,respRequestID,respApiName,respErrorInfo,respMetaData = \
	socket.recv_multipart()
	# 检查返回的信息是否符合预期
	assert respHeader == 'REQUESTID'
	assert int(respRequestID) > 0
	assert respApiName == reqApiName
	assert respErrorInfo == ''
	assert respMetaData == json.dumps(reqMetaData)


	################### 等待服务器的返回的数据信息 ###################
	poller = zmq.Poller()
	poller.register(socket, zmq.POLLIN)
	sockets = dict(poller.poll(100))
	assert socket in sockets
	# 从request通讯管道读取返回信息
	respHeader,respRequestID,respApiName,respRespInfo,respMetaData = \
	socket.recv_multipart()
	print "respHeader=",respHeader
	print "respRequestID=",respRequestID
	print "respApiName=",respApiName
	print "respRespInfo=",respRespInfo
	print "respMetaData=",respMetaData

	endTime = datetime.now()
	timeDelta = endTime - startTime
	print timeDelta.total_seconds()




#
