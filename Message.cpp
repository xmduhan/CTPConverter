#include <Message.h>

///////////////////////////// RequestMessage ///////////////////////////////////

// RequestMessage的接收函数
void RequestMessage::recv(zmq::socket_t & socket){
    int n=5,i = 0;
    do {
        switch(i){
            case 0: routeKey = s_recv(socket); break;
            case 1: header = s_recv(socket); break;
            case 2: apiName = s_recv(socket); break;
            case 3: reqInfo = s_recv(socket); break;
            case 4: metaData = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));

    // 消息格式出错检查
    InvalidMessageFormat e;

    // 检查消息头
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;

        throw e;
    }

    // 检查消息头
    if ( header.compare("REQUEST") != 0 ){
        InvalidMessageFormat e;
        throw e;
    }
}

/// RequestMessage的发送函数
void RequestMessage::send(zmq::socket_t & socket){

    InvalidMessageFormat e;
    // 检查消息头
    if ( header.compare("REQUEST") != 0 ){
        InvalidMessageFormat e;
        throw e;
    }

    // 按Request格式发送消息
    s_sendmore(socket,routeKey);
    s_sendmore(socket,header);
    s_sendmore(socket,apiName);
    s_sendmore(socket,reqInfo);
    s_send(socket,metaData);
}

//////////////////////////// RequestIDMessage //////////////////////////////////
/// RequestIDMessage的接收函数
void RequestIDMessage::recv(zmq::socket_t & socket){
    int n=6,i = 0;
    do {
        switch(i){
            case 0: routeKey = s_recv(socket); break;
            case 1: header = s_recv(socket); break;
            case 2: requestID = s_recv(socket); break;
            case 3: apiName = s_recv(socket); break;
            case 4: errorInfo = s_recv(socket); break;
            case 5: metaData = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));


    // 消息格式出错检查
    InvalidMessageFormat e;

    // 检查消息长度
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        throw e;
    }

    // 检查消息头
    if ( header.compare("REQUESTID") != 0 ){
        throw e;
    }
}

/// RequestIDMessage的发送函数
void RequestIDMessage::send(zmq::socket_t & socket){

    InvalidMessageFormat e;
    // 检查消息头
    if ( header.compare("REQUESTID") != 0 ){
        throw e;
    }

    // 按RequestID消息格式发送消息
    s_sendmore(socket,routeKey);
    s_sendmore(socket,header);
    s_sendmore(socket,requestID);
    s_sendmore(socket,apiName);
    s_sendmore(socket,errorInfo);
    s_send(socket,metaData);
}

//////////////////////////// ResponseMessage ///////////////////////////////////
// TODO 这里没有考虑第1帧是客户端地址
/// ResponseMessage的接收函数
void ResponseMessage::recv(zmq::socket_t & socket){
    int n=7,i = 0;
    do {
        switch(i){
            case 0: routeKey = s_recv(socket); break;
            case 1: header = s_recv(socket); break;
            case 2: requestID = s_recv(socket); break;
            case 3: apiName = s_recv(socket); break;
            case 4: respInfo = s_recv(socket); break;
            case 5: isLast = s_recv(socket); break;
            case 6: metaData = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));
    // 消息格式出错检查
    InvalidMessageFormat e;

    // 检查消息长度
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        throw e;
    }

    // 检查消息头
    if ( header.compare("RESPONSE") != 0 ){
        throw e;
    }
}

/// ResponseMessage的发送函数
void ResponseMessage::send(zmq::socket_t & socket){

    InvalidMessageFormat e;
    // 检查消息头
    if ( header.compare("RESPONSE") != 0 ){
        throw e;
    }

    // 按RequestID消息格式发送消息
    s_sendmore(socket,routeKey);
    s_sendmore(socket,header);
    s_sendmore(socket,requestID);
    s_sendmore(socket,apiName);
    s_sendmore(socket,respInfo);
    s_sendmore(socket,isLast);
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
    InvalidMessageFormat e;

    // 检查消息长度
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
        throw e;
    }

    // 检查消息头
    if ( header.compare("PUBLISH") != 0 ){
        throw e;
    }

}

/// PublishMessage的发送函数
void PublishMessage::send(zmq::socket_t & socket){

    InvalidMessageFormat e;
    // 检查消息头
    if ( header.compare("PUBLISH") != 0 ){
        throw e;
    }

    // 按RequestID消息格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,apiName);
    s_send(socket,respInfo);
}

//////////////////////////// PushbackMessage ///////////////////////////////////

/// PushbackMessage的接收函数
void PushbackMessage::recv(zmq::socket_t & socket){
    int n=4,i = 0;
    do {
        switch(i){
            case 0: requestID = s_recv(socket); break;
            case 1: apiName = s_recv(socket); break;
            case 2: respInfo = s_recv(socket); break;
            case 3: isLast = s_recv(socket); break;
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
    s_sendmore(socket,respInfo);
    s_send(socket,isLast);
}


//////////////////////////// MdRequestMessage ///////////////////////////////////

void MdRequestMessage::recv(zmq::socket_t & socket){

    int n=3,i = 0;
    do {
        switch(i){
            case 0: header = s_recv(socket); break;
            case 1: apiName = s_recv(socket); break;
            case 2: reqInfo = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));

    // 消息格式出错检查
    InvalidMessageFormat e;

    // 检查消息头
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;

        throw e;
    }

    // 检查消息头
    if ( header.compare("REQUEST") != 0 ){
        InvalidMessageFormat e;
        throw e;
    }
}

void MdRequestMessage ::send(zmq::socket_t & socket){

    InvalidMessageFormat e;
    // 检查消息头
    if ( header.compare("REQUEST") != 0 ){
        InvalidMessageFormat e;
        throw e;
    }

    // 按Request格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,apiName);
    s_sendmore(socket,reqInfo);
}

//////////////////////////// MdResponseMessage ///////////////////////////////////

void MdResponseMessage::recv(zmq::socket_t & socket){


    int n=3,i = 0;
    do {
        switch(i){
            case 0: header = s_recv(socket); break;
            case 1: apiName = s_recv(socket); break;
            case 2: errorInfo = s_recv(socket); break;
            default: s_recv(socket); break;
        };
        i++;
    } while(s_more(socket));

    // 消息格式出错检查
    InvalidMessageFormat e;

    // 检查消息头
    if ( i != n ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;

        throw e;
    }

    // 检查消息头
    if ( header.compare("RESPONSE") != 0 ){
        InvalidMessageFormat e;
        throw e;
    }
}

void MdResponseMessage::send(zmq::socket_t & socket){

    InvalidMessageFormat e;
    // 检查消息头
    if ( header.compare("RESPONSE") != 0 ){
        InvalidMessageFormat e;
        throw e;
    }

    // 按Request格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,apiName);
    s_sendmore(socket,errorInfo);
}

//////////////////////////// MarketDataMessage ///////////////////////////////////

/// MarketDataMessage的接收函数
//void MarketDataMessage::recv(zmq::socket_t & socket){
//    int n=4,i = 0;
//    do {
//        switch(i){
//            case 0: marketDataInfo = s_recv(socket); break;
//            default: s_recv(socket); break;
//        };
//        i++;
//    } while(s_more(socket));
//    // 消息格式出错检查
//    if ( i != n ){
//        // 执行到这里说明收到的消息和我们定义的帧数不一致
//        //std::cout << "消息格式不正确(帧数不一致)" << std::endl;
//        InvalidMessageFormat e;
//        throw e;
//    }
//}
//
///// MarketDataMessage的发送函数
//void MarketDataMessage::send(zmq::socket_t & socket){
//    s_send(socket,marketDataInfo);
//}
