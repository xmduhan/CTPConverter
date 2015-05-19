
#include <converter.h>
#include <json/json.h>
#include <comhelper.h>


// 配置信息
Configure config;


// 返回信息路由表




int main(){


    //  Prepare our context and sockets
    zmq::context_t context(1);
    zmq::socket_t frontend (context, ZMQ_ROUTER);
    zmq::socket_t backend  (context, ZMQ_PULL);
    //zmq::socket_t backend  (context, ZMQ_PUBLISH);
    frontend.bind("tcp://*:5555");    //  For clients
    backend.bind("tcp://*:5556");     //  For workers






    return 0;
}
