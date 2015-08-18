#pragma once
#include <string>
#include <exception>
#include <zmq.hpp>
#include <zhelpers.hpp>

class InvalidMessageFormat : public std::exception {
public:
    virtual const char * what() const throw() override{
        return (char*) "InvalidMessageFormat:消息格式不正确";
    }
};


class Message {
public:
    virtual void recv(zmq::socket_t & socket){};
    virtual void send(zmq::socket_t & socket){};
};


/// 客户端请求的消息格式
class RequestMessage : public Message {
public:
    // 消息结构数据
    std::string routeKey;
    std::string header;
    std::string apiName;
    std::string reqInfo;
    std::string metaData;
    virtual void recv(zmq::socket_t & socket);
    virtual void send(zmq::socket_t & socket);
};

/// 服务器端返回RequestID消息格式
class RequestIDMessage : public Message{
public:
    std::string routeKey;
    std::string header;
    std::string requestID;
    std::string apiName;
    std::string errorInfo;
    std::string metaData;
    virtual void recv(zmq::socket_t & socket);
    virtual void send(zmq::socket_t & socket);
};

/// 服务器返回请求结果的消息格式
class ResponseMessage : public Message{
public:
    std::string routeKey;
    std::string header;
    std::string requestID;
    std::string apiName;
    std::string respInfo;
    std::string isLast;
    std::string metaData;
    virtual void recv(zmq::socket_t & socket);
    virtual void send(zmq::socket_t & socket);
};

/// 公开发布消息
class PublishMessage : public Message{
public:
    std::string header;
    std::string apiName;
    std::string respInfo;
    virtual void recv(zmq::socket_t & socket);
    virtual void send(zmq::socket_t & socket);
};

/// 回到函数返回队列消息
class PushbackMessage : public Message{
public:
    std::string requestID;
    std::string apiName;
    std::string respInfo;
    std::string isLast;
    virtual void recv(zmq::socket_t & socket);
    virtual void send(zmq::socket_t & socket);
};


/// 客户端请求的消息格式
class MdRequestMessage : public Message {
public:
    // 消息结构数据
    std::string header;
    std::string apiName;
    std::string reqInfo;
    virtual void recv(zmq::socket_t & socket);
    virtual void send(zmq::socket_t & socket);
};

/// 服务器端返回RequestID消息格式
class MdResponseMessage : public Message{
public:
    std::string header;
    std::string apiName;
    std::string errorInfo;
    virtual void recv(zmq::socket_t & socket);
    virtual void send(zmq::socket_t & socket);
};


/// 行情消息
//class MarketDataMessage{
//public:
//    std::string marketDataInfo;
//    virtual void recv(zmq::socket_t & socket);
//    virtual void send(zmq::socket_t & socket);
//};
