
#include <trader.h>
#include <json/json.h>
#include <comhelper.h>
#include <Message.h>

#include <chrono>
#include <iostream>

// 配置信息
static Configure config;

static char buffer[1024*10];

#define ROUTE_TABLE_ITEM_TTL 60

// 返回信息路由表
struct RouteTableItem {
    std::string routeKey;
    std::string metaData;
    long ttl;
};
static std::map<int,RouteTableItem *> routeTable;
static std::map<int,RouteTableItem *> ::iterator iterRouteTable;
static std::chrono::time_point<std::chrono::system_clock> startTime, endTime;


int main(int argc,char * argv[]) {

    // 导入配置信息
    CommandOption commandOption(argc,argv);
    if( commandOption.exists("--env") ) {
        // 使用环境变量
        config.loadFromEnvironment();
    } else {
        // 使用命令行参数
        config.loadFromCommandLine(commandOption);
    }

    // 初始化api接口实例
    CTraderWrapper api(&config);
    api.init();

    // 初始化zmq环境
    zmq::context_t context(1);
    zmq::socket_t listener (context, ZMQ_ROUTER);
    zmq::socket_t pushback  (context, ZMQ_PULL);
    zmq::socket_t publish  (context, ZMQ_PUB);

    // 连接对应通讯管道
    listener.bind(config.requestPipe);
    pushback.connect(config.pushbackPipe);
    publish.bind(config.publishPipe);

    // 定义消息变量
    RequestMessage requestMessage;
    RequestIDMessage requestIDMessage;
    ResponseMessage responseMessage;
    PublishMessage publishMessage;
    PushbackMessage pushbackMessage;

    long timeout = 1;
    long lastTime = s_clock();
    long thisTime = 0;
    long timeDelta = 0;
    long loopTimes = 0;


    int result;
    int errorID;
    std::string errorMsg;

    std::cout << "main():开始响应客户端请求" << std::endl;

    while(1) {
        zmq::pollitem_t pullItems [] = {
            { listener,  0, ZMQ_POLLIN, 0 },
            { pushback, 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll (pullItems, 2, timeout);

        if ( pullItems[0].revents & ZMQ_POLLIN) {
            // 记时开始

            startTime = std::chrono::system_clock::now();

            do {
                std::cout << "main():接收到客户端的请求" << std::endl;
                try {
                    requestMessage.recv(listener);
                    std::cout << "main():客户端请求调用:" << requestMessage.apiName << std::endl;
                } catch(std::exception & e) {
                    std::cout << "main():异常:" << e.what() << std::endl;
                    std::cout << "main():消息被丢弃" << std::endl;
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
                    errorID = api.getLastErrorID();
                    errorMsg = api.getLastErrorMsg();
                    //sprintf(buffer,"{ErrorID:%d,ErrorMsg:%s}",errorID,errorMsg.c_str());
                    //requestIDMessage.errorInfo = buffer;
                    Json::Value jsonErrorInfo;
                    jsonErrorInfo["ErrorID"] = errorID;
                    jsonErrorInfo["ErrorMsg"] = errorMsg;
                    requestIDMessage.errorInfo = jsonErrorInfo.toStyledString();
                    std::cout << "main():调用api" << requestMessage.apiName << "出错,错误信息如下:" << std::endl;
                    std::cout << "main():" << "ErrorID=" << errorID << std::endl << "," << "ErrorMsg=" << errorMsg << std::endl;
                }

                // 将请求结果信息立即返回给客户端
                try {
                    requestIDMessage.send(listener);
                    std::cout << "main():客户端请求结果已返回客户端"  << std::endl;
                } catch(std::exception & e) {
                    std::cout << "main():异常:" << e.what() << std::endl;
                    break;
                }

                // 如果调用是成功的，将请求数据放入信息路由路由表中
                if (result > 0)
                    try {
                        int requestID = result;
                        RouteTableItem * pRouteTableItem = new RouteTableItem();
                        pRouteTableItem -> routeKey = requestMessage.routeKey;
                        pRouteTableItem -> metaData = requestMessage.metaData;
                        pRouteTableItem -> ttl = ROUTE_TABLE_ITEM_TTL;
                        routeTable[requestID] = pRouteTableItem;
                    } catch(std::exception & e) {
                        std::cout << "main():异常:" << e.what() << std::endl;
                        break;
                    }


            } while(false);
        }

        if ( pullItems[1].revents & ZMQ_POLLIN ) {
            do {
                std::cout << "main():接收到服务器的响应信息" << std::endl;
                try {
                    pushbackMessage.recv(pushback);
                    // TODO : 这里编写消息处理方法
                    int requestID = atoi(pushbackMessage.requestID.c_str());
                    // requestID如果为0是广播消息
                    if (requestID != 0) {
                        // 处理客户端请求数据
                        // 检查RequestID是否在路由表中
                        if (routeTable.count(requestID) != 0) {
                            RouteTableItem * pRouteTableItem = routeTable[requestID];
                            std::cout << "main():找到路由信息,将信息返回客户端" << std::endl;
                            responseMessage.routeKey = pRouteTableItem->routeKey;
                            responseMessage.header = "RESPONSE";
                            responseMessage.requestID = pushbackMessage.requestID;
                            responseMessage.apiName = pushbackMessage.apiName;
                            responseMessage.respInfo = pushbackMessage.respInfo;
                            responseMessage.isLast = pushbackMessage.isLast;
                            responseMessage.metaData = pRouteTableItem->metaData;
                            responseMessage.send(listener);
                            //std::cout << "main():pushbackMessage.respInfo=" << pushbackMessage.respInfo<< std::endl;
                            std::cout << "main():信息已经成功发送给客户端" << std::endl;
                        } else {
                            std::cout << "main():无法找到返回路由,可能是路由信息已过期" << std::endl;
                        }
                    } else {
                        // 处理广播消息
                        std::cout << "main():收到一条广播消息" << std::endl;
                    }
                } catch(std::exception & e) {
                    std::cout << "main():异常:" << e.what() << std::endl;
                    std::cout << "main():消息被丢弃" << std::endl;
                    break;
                }
                // TODO 将服务端返回结果发送给客户端
                // 记时结束
                endTime = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = endTime-startTime;
                std::cout << "响应请求共耗费:" << elapsed_seconds.count() << "秒" << std::endl;
            } while(false);
        }
        // 计算时间
        thisTime = s_clock();
        timeDelta = thisTime - lastTime;
        lastTime = thisTime;

        // 检查路由表中的过期信息,并将其删除
        loopTimes += timeDelta;
        if ( loopTimes >= 1000 ) {
            loopTimes = 0;
            std::cout << "main():" << "完成了1000次循环,"
                      << "路由表中元素数量为:" <<  routeTable.size() << std::endl;
            // 遍历路由表
            for (iterRouteTable = routeTable.begin(); iterRouteTable != routeTable.end(); iterRouteTable++ ) {
                //std::cout <<  iterRouteTable->first << "=" << iterRouteTable->second << std::endl;
                RouteTableItem * pRouteTableItem = iterRouteTable->second;
                if ( --(pRouteTableItem->ttl) <= 0) {
                    routeTable.erase(iterRouteTable);
                    delete pRouteTableItem;
                }
            }
        }
    }

    return 0;
}