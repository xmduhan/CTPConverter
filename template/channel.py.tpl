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


{% for method in reqMethodDict.itervalues() %}
    {% set parameter = method['parameters'][0]  %}
    def {{ method['name'][3:]}}(self,data,metaData={}):
        '''
        {{ method['remark'][3:] }}
        '''
        if not isinstance(data,{{parameter['raw_type']}}):
            raise InvalidInputFormat({{parameter['raw_type']}})

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




{% endfor %}
