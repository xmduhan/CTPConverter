
#include <converter.h>
#include <json/json.h>
#include <comhelper.h>
#include <Message.h>

// 配置信息
Configure config;


// 返回信息路由表




int main(){

    // 导入配置信息
    config.load();

    // 初始化zmq环境
    zmq::context_t context(1);
    zmq::socket_t listener (context, ZMQ_ROUTER);
    zmq::socket_t pushback  (context, ZMQ_PULL);
    zmq::socket_t publish  (context, ZMQ_PUB);

    // 连接对应通讯管道
    listener.bind(config.RequestPipe);
    pushback.connect(config.PushbackPipe);
    publish.bind(config.PublishPipe);

    // 定义消息变量
    RequestMessage requestMessage;
    RequestIDMessage requestIDMessage;
    ResponseMessage responseMessage;
    PublishMessage publishMessage;
    PushbackMessage pushbackMessage;

    long timeout = 1;
    long lastTime = s_clock();
    long thisTime = 0;
    long totalTime = 0;

    while(1){
        zmq::pollitem_t pullItems [] = {
            { listener,  0, ZMQ_POLLIN, 0 },
            { pushback, 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll (pullItems, 2, timeout);

        if ( pullItems[0].revents & ZMQ_POLLIN){
            std::cout << "接收到客户端的请求" << std::endl;
            try{
                requestMessage.recv(listener);
                // TODO : 这里编写消息处理方法
            }catch(std::exception & e){
                std::cout << "异常:" << e.what() << std::endl;
                std::cout << "消息被丢弃" << std::endl;
            }
        }

        if ( pullItems[1].revents & ZMQ_POLLIN){
            std::cout << "接收到服务器的响应信息" << std::endl;
            try{
                pushbackMessage.recv(pushback);
                // TODO : 这里编写消息处理方法
            }catch(std::exception & e){
                std::cout << "异常:" << e.what() << std::endl;
                std::cout << "消息被丢弃" << std::endl;
            }
        }
        // 计算时间
        thisTime = s_clock();
        totalTime += (thisTime - lastTime);

        // TODO : 消息返回路由的超时处理
        lastTime = thisTime;
        if ( totalTime % 1000 == 0 ){
            std::cout << "totolTime=" << totalTime << std::endl;
        }
    }

    return 0;
}
