# -*- coding: utf-8 -*-
import os
import zmq
import json
from datetime import datetime
from time import sleep
from message import *
from channel import CTPChannel
from CTPStruct import *
from nose.plugins.attrib import attr


def setup():
    '''
    所有用例的公共初始化代码
    '''
    global frontAddress,mdFrontAddress,brokerID,userID,password
    # 读取环境变量中的信息
    frontAddress = os.environ.get('CTP_FRONT_ADDRESS')
    assert frontAddress,u'必须定义环境变量:CTP_FRONT_ADDRESS'
    mdFrontAddress = os.environ.get('CTP_MD_FRONT_ADDRESS')
    assert mdFrontAddress,u'必须定义环境变量:CTP_MD_FRONT_ADDRESS'
    brokerID = os.environ.get('CTP_BROKER_ID')
    assert brokerID,u'必须定义环境变量:CTP_BROKER_ID'
    userID = os.environ.get('CTP_USER_ID')
    assert userID,u'必须定义环境变量:CTP_USER_ID'
    password = os.environ.get('CTP_PASSWORD')
    assert password,u'必须定义环境变量:CTP_PASSWORD'


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


@attr('test_connect_to_ctp_converter')
def test_connect_to_ctp_converter():
    '''
    测试和CTPConverter的连接
    用于检查与CTPConverter的连接是否正常和测试响应延时
    '''
    sleep(1)

    requestApiName = 'ReqQryTradingAccount'
    responseApiName = 'OnRspQryTradingAccount'
    timeout = 1000*10

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


@attr('test_call_not_exist_api')
def test_call_not_exist_api():
    '''
    测试调用不在的api
    '''
    sleep(1)

    requestApiName = 'unkown_api_name'
    timeout = 1000 * 10
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
    assert int(requestIDMessage.requestID) == 0
    assert requestIDMessage.apiName == requestApiName
    errorInfo = json.loads(requestIDMessage.errorInfo)
    assert errorInfo['ErrorID'] == -1000
    print errorInfo['ErrorID'],errorInfo['ErrorMsg']
    assert requestIDMessage.metaData == json.dumps(metaData)



@attr('test_call_OrderInsert')
def test_call_OrderInsert():
    '''
    报单测试
    '''
    sleep(1)

    requestApiName = 'ReqOrderInsert'
    timeout = 1000 * 2

    # 生成调用数据格式
    reqInfo = getDefaultReqInfo(requestApiName)
    requestData = CThostFtdcInputOrderField()
    requestData.BrokerID = brokerID
    requestData.InvestorID = userID
    requestData.InstrumentID = 'IF1507'
    requestData.OrderRef = '000000000001'
    requestData.UserID = userID
    requestData.OrderPriceType = '1'     # 任意价
    requestData.Direction = '0'          # 买
    requestData.CombOffsetFlag = '0'     # 开仓
    requestData.CombHedgeFlag = '1'      # 投机
    requestData.LimitPrice = 0           # 限价 0表不限制
    requestData.VolumeTotalOriginal = 1  # 手数
    requestData.TimeCondition = '1'      # 立即完成否则撤消
    requestData.GTDDate = ''
    requestData.VolumeCondition = '1'    # 成交类型  '1' 任何数量  '2' 最小数量 '3'全部数量
    requestData.MinVolume = 1            # 最小数量
    requestData.ContingentCondition = '1' # 触发类型 '1' 立即否则撤消
    requestData.StopPrice = 0             # 止损价
    requestData.ForceCloseReason = '0'    # 强平标识 '0'非强平
    requestData.IsAutoSuspend = 0         # 自动挂起标识
    requestData.BusinessUnit = ''         # 业务单元
    requestData.RequestID = 1
    requestData.UserForceClose = 0        # 用户强平标识
    requestData.IsSwapOrder = 0           # 互换单标识
    reqInfo['Parameters']['Data'] = requestData.toDict()
    #print reqInfo

    # 创建通讯环境
    context = zmq.Context()

    # 连接request通讯管道
    requestAddress = os.getenv('CTP_REQUEST_PIPE',None)
    assert requestAddress
    request = context.socket(zmq.DEALER)
    request.connect(requestAddress)
    request.setsockopt(zmq.LINGER,0)

    # 连接publish通讯管道
    publishAddress = os.getenv('CTP_PUBLISH_PIPE',None)
    assert publishAddress
    publish = context.socket(zmq.SUB)
    publish.connect(publishAddress)
    publish.setsockopt_string(zmq.SUBSCRIBE,u'')

    # 准备请求消息
    requestMessage = RequestMessage()
    requestMessage.header = 'REQUEST'
    requestMessage.apiName = requestApiName
    requestMessage.reqInfo = json.dumps(reqInfo)
    requestMessage.metaData = json.dumps({})

    # 发送消息
    requestMessage.send(request)

    ################### 等待服务器的REQUESTID响应 ###################
    poller = zmq.Poller()
    poller.register(request, zmq.POLLIN)
    sockets = dict(poller.poll(timeout))
    assert request in sockets

    # 从request通讯管道读取返回信息
    requestIDMessage = RequestIDMessage()
    requestIDMessage.recv(request)
    # 检查立即返回信息的格式
    assert requestIDMessage.header == 'REQUESTID'
    assert int(requestIDMessage.requestID) > 0
    assert requestIDMessage.apiName == requestApiName
    assert requestIDMessage.errorInfo == ''
    assert requestIDMessage.metaData == json.dumps({})

    # 等待OnRsp消息,实际等不到
    poller = zmq.Poller()
    poller.register(request, zmq.POLLIN)
    poller.register(publish, zmq.POLLIN)
    sockets = dict(poller.poll(timeout))
    # 由于我们的开单格式正确,不会收到OnRsp消息
    assert request not in sockets
    # 应该至少能收到OnRtnOrder消息
    assert publish in sockets

    # 接收第1条OnRtnOrder消息
    publishMessage = PublishMessage()
    publishMessage.recv(publish)
    assert publishMessage.header == 'PUBLISH'
    assert publishMessage.apiName == 'OnRtnOrder'
    #print publishMessage.respInfo

    # 读取返回信息
    respInfo = json.loads(publishMessage.respInfo)

    # 检查开单的状态
    responseData = respInfo['Parameters']['Data']
    #assert responseData['OrderSubmitStatus'] == '0'
    #assert responseData['OrderStatus'] == 'a'
