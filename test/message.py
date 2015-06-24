# -*- coding: utf-8 -*-



class InvalidMessageFormat(Exception):
    '''
    消息格式不正确时抛出的异常
    '''

    def __init__(self):
        self.value = u'不正确的消息格式'

    def __str__(self):
        return repr(self.value)


class RequestMessage:
    '''
    客户端请求的消息格式
    '''
    def __init__(self):
        #self.routeKey = ''
        self.header = 'REQUEST'
        self.apiName = ''
        self.reqInfo = ''
        self.metaData = ''

    def send(self,socket):
        '''
        '''
        if self.header != 'REQUEST':
            raise InvalidMessageFormat()
        socket.send_multipart([self.header,self.apiName,self.reqInfo,self.metaData])


class RequestIDMessage :
    '''
    服务器端返回RequestID消息格式
    '''
    def __init__(self):
        #self.routeKey = ''
        self.header = ''
        self.requestID = ''
        self.apiName = ''
        self.errorInfo = ''
        self.metaData = ''

    def recv(self,socket):
        '''
        从服务器上接受REQUESTID消息,即立即返回消息
        '''
        received = socket.recv_multipart()
        if len(received) != 5 :
            raise InvalidMessageFormat()
        self.header,self.requestID,self.apiName,self.errorInfo,self.metaData = received
        if self.header != 'REQUESTID' :
            raise InvalidMessageFormat()


class ResponseMessage :
    '''
    服务器返回请求结果的消息格式
    '''
    def __init__(self):
        #self.routeKey = ''
        self.header = ''
        self.requestID = ''
        self.apiName = ''
        self.respInfo = ''
        self.isLast = ''
        self.metaData = ''

    def recv(self,socket):
        '''
        服务器上接受数据消息
        '''
        received = socket.recv_multipart()
        if len(received) != 6 :
            raise InvalidMessageFormat()
        self.header,self.requestID,self.apiName,self.respInfo,self.isLast,self.metaData = received
        if self.header != 'RESPONSE' :
            raise InvalidMessageFormat()


class PublishMessage :
    '''
    公开发布消息
    '''
    def __init__(self):
        self.header =''
        self.apiName = ''
        self.respInfo = ''

    def recv(self,socket):
        '''
        接受发布消息
        '''
        received = socket.recv_multipart()
        if len(received) != 3 :
            raise InvalidMessageFormat()
        self.header,self.apiName,self.respInfo = received
