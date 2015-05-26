# -*- coding: utf-8 -*-
import os
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

	requestData = []
	requestData.append('REQUEST')  # header
	requestData.append(requestApiName)  # requestApiName
	requestData.append(json.dumps(reqInfo)) # reqInfo
	requestData.append(json.dumps(metaData))  # metaData

	# 开始计时
	startTime = datetime.now()
	# 向协议转换器发出请求
	socket.send_multipart(requestData)
	################### 等待服务器的REQUESTID响应 ###################
	poller = zmq.Poller()
	poller.register(socket, zmq.POLLIN)
	sockets = dict(poller.poll(timeout))
	assert socket in sockets

	# 从request通讯管道读取返回信息
	requestIdData = {}
	requestIdData['header'],requestIdData['requestID'],requestIdData['requestApiName'],\
	requestIdData['errorInfo'],requestIdData['metaData'] = socket.recv_multipart()

	# 检查返回的信息是否符合预期
	assert requestIdData['header'] == 'REQUESTID'
	assert int(requestIdData['requestID']) > 0
	assert requestIdData['requestApiName'] == requestApiName
	assert requestIdData['errorInfo'] == ''
	assert requestIdData['metaData'] == json.dumps(metaData)


	################### 等待服务器的返回的数据信息 ###################
	poller = zmq.Poller()
	poller.register(socket, zmq.POLLIN)
	sockets = dict(poller.poll(timeout))
	assert socket in sockets

	# 从request通讯管道读取返回信息
	responseData = {}
	responseData['header'],responseData['requestID'],responseData['responseApiName'],\
	responseData['respInfo'],responseData['isLast'],responseData['metaData'] \
	= socket.recv_multipart()

	# TODO 检查调用是否成功
	assert responseData['header'] == 'RESPONSE'
	assert responseData['requestID'] == requestIdData['requestID']
	assert responseData['responseApiName'] == responseApiName
	#assert int(responseData['isLast']) == 1
	assert responseData['metaData'] == json.dumps(metaData)

	#print "respHeader=",responseData['header']
	#print "respRequestID=",responseData['requestID']
	#print "respApiName=",responseData['responseApiName']
	print "respRespInfo=",responseData['respInfo']
	#print "respMetaData=",responseData['metaData']
	# TODO 显示关键信息

	endTime = datetime.now()
	timeDelta = endTime - startTime
	print timeDelta.total_seconds()



#
