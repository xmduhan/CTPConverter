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



def test_connet_to_ctp_converter():
	'''
	测试和CTPConverter的连接
	用于检查与CTPConverter的连接是否正常和测试响应延时
	'''
	sleep(1)

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



def test_QryTradingAccount():
    '''
    测试QryTradingAccount
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTradingAccount():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTradingAccountField()
    errorID,errorMsg,responeDataList =  ch.QryTradingAccount(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d-----------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTradingAccount():请求完成'

    assert errorID == 0,u'请求失败'

    print 'test_QryTradingAccount():执行结束'
    print '----------------------------------------------------------------------'


def test_QryCFMMCTradingAccountKey():
    '''
    测试QryCFMMCTradingAccountKey
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryCFMMCTradingAccountKey():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryCFMMCTradingAccountKeyField()
    errorID,errorMsg,responeDataList =  ch.QryCFMMCTradingAccountKey(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d-----------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryCFMMCTradingAccountKey():请求完成'

    assert errorID == 0,u'请求失败'

    print 'test_QryCFMMCTradingAccountKey():执行结束'
    print '----------------------------------------------------------------------'


def test_QryTradingNotice():
    '''
    测试QryTradingNotice
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTradingNotice():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTradingNoticeField()
    errorID,errorMsg,responeDataList =  ch.QryTradingNotice(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d-----------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTradingNotice():请求完成'

    assert errorID == 0,u'请求失败'

    print 'test_QryTradingNotice():执行结束'
    print '----------------------------------------------------------------------'


def test_QryTrade():
    '''
    测试QryTrade
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTrade():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTradeField()
    errorID,errorMsg,responeDataList =  ch.QryTrade(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d-----------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTrade():请求完成'

    assert errorID == 0,u'请求失败'

    print 'test_QryTrade():执行结束'
    print '----------------------------------------------------------------------'


def test_QueryMaxOrderVolume():
    '''
    测试QueryMaxOrderVolume
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QueryMaxOrderVolume():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQueryMaxOrderVolumeField()
    errorID,errorMsg,responeDataList =  ch.QueryMaxOrderVolume(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d-----------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QueryMaxOrderVolume():请求完成'

    assert errorID == 0,u'请求失败'

    print 'test_QueryMaxOrderVolume():执行结束'
    print '----------------------------------------------------------------------'






#
