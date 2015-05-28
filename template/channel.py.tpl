# -*- coding: utf-8 -*-

class CTPChannel :
    '''
    CTP通讯管道类,该类和CTPConverter进程通讯,对外实现python语言封装的CTP接口,在设计上该类
    既支持同步接口也支持异步接口,但是目前暂时先实现同步接口.
    '''

    def __init__():
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
