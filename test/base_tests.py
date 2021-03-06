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
from datetime import datetime
from dateutil.relativedelta import relativedelta
import uuid
from nose.tools import nottest

def setup():
    '''
    所有用例的公共初始化代码
    '''
    global frontAddress,mdFrontAddress,brokerID,userID,password,\
        requestAddress,responseAddress,publishAddress
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

    requestAddress = os.getenv('CTP_REQUEST_PIPE',None)
    assert requestAddress
    responseAddress = os.getenv('CTP_RESPONSE_PIPE',None)
    assert responseAddress
    publishAddress = os.getenv('CTP_PUBLISH_PIPE',None)
    assert publishAddress



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
    global requestAddress,responseAddress
    sleep(1)

    requestApiName = 'ReqQryTradingAccount'
    responseApiName = 'OnRspQryTradingAccount'
    timeout = 1000*10

    # 初始化变量
    #requestAddress = 'tcp://localhost:10001'

    # 初始化zmq通讯环境
    context = zmq.Context()

    # 生成客户端身份定义符
    identity = str(uuid.uuid1())

    # 连接request通讯管道
    request = context.socket(zmq.DEALER)
    request.setsockopt(zmq.IDENTITY,identity)
    request.connect(requestAddress)
    request.setsockopt(zmq.LINGER,0)

    # 连接response通讯管道
    response = context.socket(zmq.DEALER)
    response.setsockopt(zmq.IDENTITY,identity)
    response.connect(responseAddress)
    response.setsockopt(zmq.LINGER,0)

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
    assert requestIDMessage.metaData == json.dumps(metaData)


    ################### 等待服务器的返回的数据信息 ###################
    poller = zmq.Poller()
    poller.register(response, zmq.POLLIN)
    sockets = dict(poller.poll(timeout))
    assert response in sockets

    # 从response通讯管道读取返回信息
    responseMessage = ResponseMessage()
    responseMessage.recv(response)

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
    global requestAddress
    sleep(1)

    requestApiName = 'unkown_api_name'
    timeout = 1000 * 10

    # 连接request通讯管道
    context = zmq.Context()
    request = context.socket(zmq.DEALER)
    request.connect(requestAddress)
    request.setsockopt(zmq.LINGER,0)

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
    assert int(requestIDMessage.requestID) == 0
    assert requestIDMessage.apiName == requestApiName
    errorInfo = json.loads(requestIDMessage.errorInfo)
    assert errorInfo['ErrorID'] == -1000
    print errorInfo['ErrorID'],errorInfo['ErrorMsg']
    assert requestIDMessage.metaData == json.dumps(metaData)


@attr('test_call_SettlementInfoConfirm')
def test_call_SettlementInfoConfirm():
    '''
    交易信息确认
    '''
    ch = CTPChannel()
    requestData = CThostFtdcSettlementInfoConfirmField()
    requestData.BrokerID = brokerID
    requestData.InvestorID = userID
    requestData.ConfirmDate = ''
    requestData.ConfirmTime = ''
    result = ch.SettlementInfoConfirm(requestData)
    #print result[0],result[1],result[2]
    assert result[0] == 0


orderRefSeq = 0
def getOrderRef():
    '''
    获取OrderRef序列值
    '''
    global orderRefSeq
    orderRefSeq += 1
    return ('%12d' % orderRefSeq).replace(' ','0') # '000000000001'


def getDefaultInstrumentID(months=1):
    '''
    获得一个保证可以使用的合同代码
    '''
    return datetime.strftime(datetime.now() + relativedelta(months=months),"IF%y%m")


def getDefaultInputOrderFieldBuyOpen():
    '''
    获得一个默认的参数合法的,提交请求结构
    '''
    inputOrderField = CThostFtdcInputOrderField()
    inputOrderField.BrokerID = brokerID
    inputOrderField.InvestorID = userID
    inputOrderField.InstrumentID = getDefaultInstrumentID()
    inputOrderField.OrderRef =  getOrderRef() #
    inputOrderField.UserID = userID
    inputOrderField.OrderPriceType = '1'     # 任意价
    inputOrderField.Direction = '0'          # 买
    inputOrderField.CombOffsetFlag = '0'     # 开仓
    inputOrderField.CombHedgeFlag = '1'      # 投机
    inputOrderField.LimitPrice = 0           # 限价 0表不限制
    inputOrderField.VolumeTotalOriginal = 1  # 手数
    inputOrderField.TimeCondition = '1'      # 立即完成否则撤消
    inputOrderField.GTDDate = ''
    inputOrderField.VolumeCondition = '1'    # 成交类型  '1' 任何数量  '2' 最小数量 '3'全部数量
    inputOrderField.MinVolume = 1            # 最小数量
    inputOrderField.ContingentCondition = '1' # 触发类型 '1' 立即否则撤消
    inputOrderField.StopPrice = 0             # 止损价
    inputOrderField.ForceCloseReason = '0'    # 强平标识 '0'非强平
    inputOrderField.IsAutoSuspend = 0         # 自动挂起标识
    inputOrderField.BusinessUnit = ''         # 业务单元
    inputOrderField.RequestID = 1
    inputOrderField.UserForceClose = 0        # 用户强平标识
    inputOrderField.IsSwapOrder = 0           # 互换单标识
    return inputOrderField


def getDefaultInputOrderFieldBuyClose():
    '''
    获得一个默认的参数合法的,提交请求结构
    '''
    inputOrderField = CThostFtdcInputOrderField()
    inputOrderField.BrokerID = brokerID
    inputOrderField.InvestorID = userID
    inputOrderField.InstrumentID = getDefaultInstrumentID()
    inputOrderField.OrderRef =  getOrderRef() #
    inputOrderField.UserID = userID
    inputOrderField.OrderPriceType = '1'     # 任意价
    inputOrderField.Direction = '1'          # 卖
    inputOrderField.CombOffsetFlag = '1'     # 平仓
    inputOrderField.CombHedgeFlag = '1'      # 投机
    inputOrderField.LimitPrice = 0           # 限价 0表不限制
    inputOrderField.VolumeTotalOriginal = 1  # 手数
    inputOrderField.TimeCondition = '1'      # 立即完成否则撤消
    inputOrderField.GTDDate = ''
    inputOrderField.VolumeCondition = '1'    # 成交类型  '1' 任何数量  '2' 最小数量 '3'全部数量
    inputOrderField.MinVolume = 1            # 最小数量
    inputOrderField.ContingentCondition = '1' # 触发类型 '1' 立即否则撤消
    inputOrderField.StopPrice = 0             # 止损价
    inputOrderField.ForceCloseReason = '0'    # 强平标识 '0'非强平
    inputOrderField.IsAutoSuspend = 0         # 自动挂起标识
    inputOrderField.BusinessUnit = ''         # 业务单元
    inputOrderField.RequestID = 1
    inputOrderField.UserForceClose = 0        # 用户强平标识
    inputOrderField.IsSwapOrder = 0           # 互换单标识
    return inputOrderField


def callOrderInsert(requestData):
    '''
    报单测试
    '''
    global requestAddress,responseAddress,publishAddress
    sleep(1)

    requestApiName = 'ReqOrderInsert'
    timeout = 1000 * 2

    # 创建通讯环境
    context = zmq.Context()

    # 生成客户端身份定义符
    identity = str(uuid.uuid1())

    # 连接request通讯管道
    request = context.socket(zmq.DEALER)
    request.setsockopt(zmq.IDENTITY,identity)
    request.connect(requestAddress)
    request.setsockopt(zmq.LINGER,0)

    # 连接response通讯管道
    response = context.socket(zmq.DEALER)
    response.setsockopt(zmq.IDENTITY,identity)
    response.connect(responseAddress)
    response.setsockopt(zmq.LINGER,0)

    # 连接publish通讯管道
    publish = context.socket(zmq.SUB)
    publish.connect(publishAddress)
    publish.setsockopt_string(zmq.SUBSCRIBE,u'')

    # 准备开仓数据信息
    reqInfo = getDefaultReqInfo(requestApiName)
    reqInfo['Parameters']['Data'] = requestData.toDict()
    #print reqInfo

    # 发送消息到协议转换器
    requestMessage = RequestMessage()
    requestMessage.header = 'REQUEST'
    requestMessage.apiName = requestApiName
    requestMessage.reqInfo = json.dumps(reqInfo)
    requestMessage.metaData = json.dumps({})
    requestMessage.send(request)

    # 等待服务器的REQUESTID响应
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


    while True:
        poller = zmq.Poller()
        poller.register(response, zmq.POLLIN)
        poller.register(publish, zmq.POLLIN)
        sockets = dict(poller.poll(timeout))
        # 由于我们的开单格式正确,不会收到OnRsp消息
        # 应该至少能收到OnRtnOrder消息
        assert response in sockets
        # assert publish not in sockets

        # 接收第1条OnRtnOrder消息
        responseMessage = ResponseMessage()
        responseMessage.recv(response)
        print 'responseMessage.apiName=', responseMessage.apiName
        assert responseMessage.header == 'RESPONSE'
        assert responseMessage.apiName == 'OnRtnOrder'
        #print responseMessage.respInfo

        # 读取返回信息
        respInfo = json.loads(responseMessage.respInfo)
        responseData = respInfo['Parameters']['Data']

        # 检查开单的状态
        orderSubmitStatus = responseData['OrderSubmitStatus']  # '0' 订单已提交
        orderStatus = responseData['OrderStatus']  # 'a' 未知状态
        statusMsg = responseData['StatusMsg']
        print orderSubmitStatus,orderStatus,statusMsg

        if orderSubmitStatus != '0' or  orderStatus != 'a':
            break

    if orderSubmitStatus == '4' and orderStatus == '5':
        # 在非交易时间执行测试用例,报单会被拒绝,忽略这个错误
        return -1

    #  如果程序到达这里说明报单已经提交成功了
    assert orderSubmitStatus == '0'    #已经提交
    assert orderStatus == '0'   # 全部成交

    # 接下来等待OnRtnTrader消息
    poller = zmq.Poller()
    poller.register(response, zmq.POLLIN)
    poller.register(publish, zmq.POLLIN)
    sockets = dict(poller.poll(timeout))
    # 由于我们的开单格式正确,不会收到OnRsp消息
    assert response not in sockets
    # 应该至少能收到OnRtnOrder消息
    assert publish in sockets

    # 接收第1条OnRtnOrder消息
    publishMessage = PublishMessage()
    publishMessage.recv(publish)
    assert publishMessage.header == 'PUBLISH'
    assert publishMessage.apiName == 'OnRtnTrade'
    #print publishMessage.respInfo

    # 读取返回数据进行确认
    respInfo = json.loads(publishMessage.respInfo)
    responseData = respInfo['Parameters']['Data']
    tradeType = responseData['TradeType']
    tradeSource = responseData['TradeSource']
    price = responseData['Price']
    assert tradeType == '0'     # '0' 普通成交
    assert tradeSource == '0'   # '0' 来自交易所普通回报

    return price

@nottest
@attr('test_BuyOpenAndClose')
def test_BuyOpenAndClose():
    '''
    测试开仓和平仓
    '''
    test_call_SettlementInfoConfirm()
    price0 = callOrderInsert(getDefaultInputOrderFieldBuyOpen())

    if price0 > 0 :
        price1 = callOrderInsert(getDefaultInputOrderFieldBuyClose())

    if price0 > 0 and price1 > 0 :
        print 'price0=',price0
        print 'price1=',price1
        print 'diff=',price1-price0
    else:
        print u'可能由于市场不处于交易状态的原因,开平仓测试没有实际进行测试'

@nottest
@attr('test_md_subscribe_depth_market')
def test_md_subscribe_depth_market():
    """
    测试订阅服务
    """
    # 创建zmq通讯环境
    timeout = 1000
    context = zmq.Context()

    # 创建request通讯管道
    request = context.socket(zmq.REQ)
    request.connect(requestAddress)
    #request.setsockopt(zmq.LINGER,0)

    #创建publish通讯管道
    publish = context.socket(zmq.SUB)
    publish.connect(publishAddress)
    publish.setsockopt_string(zmq.SUBSCRIBE,u'')

    # 初始化调用变量
    requestApiName = 'SubscribeMarketData'
    reqInfo = getDefaultReqInfo(requestApiName)
    data = [getDefaultInstrumentID(1)]
    reqInfo['Parameters']['Data'] = data

    # 发送消息
    requestMessage = MdRequestMessage()
    requestMessage.header = 'REQUEST'
    requestMessage.apiName = requestApiName
    requestMessage.reqInfo = json.dumps(reqInfo)
    requestMessage.send(request)

    # 等待服务器响应
    poller = zmq.Poller()
    poller.register(request, zmq.POLLIN)
    sockets = dict(poller.poll(timeout))
    assert request in sockets

    # 读取服务器响应信息
    responseMessage = MdResponseMessage()
    responseMessage.recv(request)
    errorInfo = json.loads(responseMessage.errorInfo)
    assert errorInfo['ErrorID'] == 0

    # 检查使用是否成功
    publishMessage = PublishMessage()
    publishMessage.recv(publish)
    assert publishMessage.header == 'PUBLISH'
    assert publishMessage.apiName == 'OnRspSubMarketData'
    respInfo = json.loads(publishMessage.respInfo)
    assert respInfo['Parameters']['RspInfo']['ErrorID'] == 0

    # 让订阅信息运行一下
    sleep(2)

    # 准备调用停止订阅
    requestApiName = 'UnSubscribeMarketData'
    reqInfo = getDefaultReqInfo(requestApiName)
    data = [getDefaultInstrumentID(1)]
    reqInfo['Parameters']['Data'] = data

    # 发送消息
    requestMessage = MdRequestMessage()
    requestMessage.header = 'REQUEST'
    requestMessage.apiName = requestApiName
    requestMessage.reqInfo = json.dumps(reqInfo)
    requestMessage.send(request)

    # 等待服务器响应
    poller = zmq.Poller()
    poller.register(request, zmq.POLLIN)
    sockets = dict(poller.poll(timeout))
    assert request in sockets

    # 读取服务器响应信息
    responseMessage = MdResponseMessage()
    responseMessage.recv(request)
    errorInfo = json.loads(responseMessage.errorInfo)
    assert errorInfo['ErrorID'] == 0

    i = 0
    j = 0
    while True:
        # 等待服务器响应
        poller = zmq.Poller()
        poller.register(publish, zmq.POLLIN)
        sockets = dict(poller.poll(timeout))
        if publish in sockets:
            publishMessage = PublishMessage()
            publishMessage.recv(publish)
            respInfo = json.loads(publishMessage.respInfo)
            print publishMessage.apiName
            if publishMessage.apiName == 'OnRspUnSubMarketData':
                assert respInfo['Parameters']['RspInfo']['ErrorID'] == 0
                print '已收到OnUnRspSubMarketData响应...'
                break
            else:
                print respInfo
            i += 1
            if i > 50:
                raise Exception(u'等待服务器响应超时')
        else:
            j += 1
            if j > 3:
                raise Exception(u'等待服务器响应超时')


