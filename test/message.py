# -*- coding: utf-8 -*-


'''
class InvalidMessageFormat:
    pass
'''

class RequestMessage:
    '''
    客户端请求的消息格式
    '''
    def __init__(self):
        #self.routeKey = ''
        self.header = ''
        self.apiName = ''
        self.reqInfo = ''
        self.metaData = ''

    def send(socket):
        '''
        '''
        # TODO 判断消息头
        socket.send_multipart([header,apiName,reqInfo,metaData])

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

    def recv(socket):
        self.header,self.requestID,self.apiName,self.errorInfo,self.metaData = \
        socket.recv_multipart()

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

    def recv(socket):
        self.header,self.requestID,self.apiName,self.respInfo,self.isLast,self.metaData = \
        socket.recv_multipart()


class PublishMessage :
    '''
    公开发布消息
    '''
    def __init__(self):
        self.header =''
        self.apiName = ''
        self.respInfo = ''

    def recv(socket):
        self.header,self.apiName,self.respInfo = socket.recv_multipart()
