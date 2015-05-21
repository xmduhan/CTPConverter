
#include <converter.h>
#include <json/json.h>
#include <comhelper.h>
#include <Message.h>

// 配置信息
static Configure config;

static char buffer[1024*10];


// 返回信息路由表


int main() {

    // 导入配置信息
    config.load();
    CApiWrapper api(&config);
    api.init();

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

    int result;
    int errorCode;
    std::string errorMessage;


    while(1) {
        zmq::pollitem_t pullItems [] = {
            { listener,  0, ZMQ_POLLIN, 0 },
            { pushback, 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll (pullItems, 2, timeout);

        if ( pullItems[0].revents & ZMQ_POLLIN) {
            do {
                std::cout << "接收到客户端的请求" << std::endl;
                try {
                    requestMessage.recv(listener);
                    std::cout << "客户端请求调用:" << requestMessage.apiName << std::endl;
                } catch(std::exception & e) {
                    std::cout << "异常:" << e.what() << std::endl;
                    std::cout << "消息被丢弃" << std::endl;
                    break;
                }

                // 调用对应的api
                result = api.callApiByName(requestMessage.apiName,requestMessage.reqInfo);

                // 初始化返回信息格式
                requestIDMessage.routeKey = requestMessage.routeKey;
                requestIDMessage.requestID = "0";
                requestIDMessage.header = "REQUESTID";
                requestIDMessage.apiName = requestMessage.apiName;
                requestIDMessage.errorInfo = "";
                requestIDMessage.metaData = requestMessage.metaData;

                // 判断api调用的结果,如果成功返回RequestID,失败返回错误信息
                if ( result > 0 ) {
                    // 调用成功返回的是RequestID
                    sprintf(buffer,"%d",result);
                    requestIDMessage.requestID = buffer;
                } else {
                    errorCode = api.getLastErrorCode();
                    errorMessage = api.getLastErrorMessage();
                    sprintf(buffer,"{ErrorCode:%d,ErrorMessage:%s}",errorCode,errorMessage.c_str());
                    requestIDMessage.errorInfo = buffer;
                    std::cout << "调用api" << requestMessage.apiName << "出错,错误信息如下:" << std::endl;
                    std::cout << "ErrorCode=" << errorCode << std::endl << "," << "ErrorMessage=" << errorMessage << std::endl;
                }

                // 将请求结果信息立即返回给客户端
                try {
                    requestIDMessage.send(listener);
                    std::cout << "客户端请求结果已返回客户端"  << std::endl;
                } catch(std::exception & e) {
                    std::cout << "异常:" << e.what() << std::endl;
                    break;
                }

            } while(false);
        }

        if ( pullItems[1].revents & ZMQ_POLLIN ) {
            do {
                std::cout << "接收到服务器的响应信息" << std::endl;
                try {
                    pushbackMessage.recv(pushback);
                    // TODO : 这里编写消息处理方法
                } catch(std::exception & e) {
                    std::cout << "异常:" << e.what() << std::endl;
                    std::cout << "消息被丢弃" << std::endl;
                    break;
                }
                // TODO 将服务端返回结果发送给客户端
            } while(false);
        }
        // 计算时间
        thisTime = s_clock();
        totalTime += (thisTime - lastTime);

        // TODO : 消息返回路由的超时处理
        lastTime = thisTime;
        if ( totalTime % 1000 == 0 ) {
            std::cout << "totolTime=" << totalTime << std::endl;
        }
    }

    return 0;
}