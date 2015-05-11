#include <Message.h>

///////////////////////////// RequestMessage ///////////////////////////////////

// RequestMessage的接收函数
void RequestMessage::recv(zmq::socket_t & socket){
    int n=4,i = 0;
    do {
        switch(i){
            case 0: header = s_recv(socket); break;
            case 1: apiName = s_recv(socket); break;
            case 2: reqInfo = s_recv(socket); break;
            case 3: metaData = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));
    // 消息格式出错检查
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        InvalidMessageFormat e;
        throw e;
    }
}

/// RequestMessage的发送函数
void RequestMessage::send(zmq::socket_t & socket){
    // 按Request格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,apiName);
    s_sendmore(socket,reqInfo);
    s_send(socket,metaData);
}

//////////////////////////// RequestIDMessage //////////////////////////////////

/// RequestIDMessage的接收函数
void RequestIDMessage::recv(zmq::socket_t & socket){
    int n=5,i = 0;
    do {
        switch(i){
            case 0: header = s_recv(socket); break;
            case 1: requestID = s_recv(socket); break;
            case 2: apiName = s_recv(socket); break;
            case 3: errorInfo = s_recv(socket); break;
            case 4: metaData = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));
    // 消息格式出错检查
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        InvalidMessageFormat e;
        throw e;
    }
}

/// RequestIDMessage的发送函数
void RequestIDMessage::send(zmq::socket_t & socket){
    // 按RequestID消息格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,requestID);
    s_sendmore(socket,apiName);
    s_sendmore(socket,errorInfo);
    s_send(socket,metaData);
}

//////////////////////////// ResponseMessage ///////////////////////////////////

/// ResponseMessage的接收函数
void ResponseMessage::recv(zmq::socket_t & socket){
    int n=5,i = 0;
    do {
        switch(i){
            case 0: header = s_recv(socket); break;
            case 1: requestID = s_recv(socket); break;
            case 2: apiName = s_recv(socket); break;
            case 3: respInfo = s_recv(socket); break;
            case 4: metaData = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));
    // 消息格式出错检查
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        InvalidMessageFormat e;
        throw e;
    }
}

/// ResponseMessage的发送函数
void ResponseMessage::send(zmq::socket_t & socket){
    // 按RequestID消息格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,requestID);
    s_sendmore(socket,apiName);
    s_sendmore(socket,respInfo);
    s_send(socket,metaData);
}

//////////////////////////// PublishMessage ////////////////////////////////////

/// PublishMessage的接收函数
void PublishMessage::recv(zmq::socket_t & socket){
    int n=3,i = 0;
    do {
        switch(i){
            case 0: header = s_recv(socket); break;
            case 1: apiName = s_recv(socket); break;
            case 2: respInfo = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));
    // 消息格式出错检查
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        InvalidMessageFormat e;
        throw e;
    }
}

/// PublishMessage的发送函数
void PublishMessage::send(zmq::socket_t & socket){
    // 按RequestID消息格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,apiName);
    s_send(socket,respInfo);
}

//////////////////////////// PushbackMessage ///////////////////////////////////

/// PushbackMessage的接收函数
void PushbackMessage::recv(zmq::socket_t & socket){
    int n=3,i = 0;
    do {
        switch(i){
            case 0: requestID = s_recv(socket); break;
            case 1: apiName = s_recv(socket); break;
            case 2: respInfo = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));
    // 消息格式出错检查
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        InvalidMessageFormat e;
        throw e;
    }
}

/// PushbackMessage的发送函数
void PushbackMessage::send(zmq::socket_t & socket){
    // 按RequestID消息格式发送消息
    s_sendmore(socket,requestID);
    s_sendmore(socket,apiName);
    s_send(socket,respInfo);
}
