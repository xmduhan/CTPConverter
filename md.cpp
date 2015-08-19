#include <CMdHandler.h>
#include <CMdWrapper.h>
#include <unistd.h>
#include <json/json.h>

static MdConfigure config;
static char buffer[1024*10];

int main(int argc,char * argv[]){
    // 导入配置信息
    CommandOption commandOption(argc,argv);
    if( commandOption.exists("--env") ) {
        // 使用环境变量
        config.loadFromEnvironment();
    } else {
        // 使用命令行参数
        config.loadFromCommandLine(commandOption);
    }

    // 忠诚选项判断
    // 即当父进程退出,本进程也退出
    bool loyalty;
    if( commandOption.exists("--loyalty") ) {
        loyalty = true;
    } else {
        loyalty = false;
    }
    pid_t originalPpid = getppid();

    // 初始化zmq环境
    zmq::context_t context(1);
    zmq::socket_t request  (context, ZMQ_REP);
    zmq::socket_t pushback  (context, ZMQ_PULL);
    zmq::socket_t publish  (context, ZMQ_PUB);

    // 连接对应通讯管道
    request.bind(config.requestPipe);
    pushback.connect(config.pushbackPipe);
    publish.bind(config.publishPipe);

    //std::cout << "main():request地址为:" << config.requestPipe << std::endl;
    //std::cout << "main():pushback地址为:" << config.pushbackPipe << std::endl;
    //std::cout << "main():publish地址为:" << config.publishPipe << std::endl;
    sleep(1);    // 给一定时间让订阅者连接上来，以免错过第1条消息


    // 初始化api接口实例
    CMdWrapper api(&config);
    api.init();

    // 定义消息变量
    MdRequestMessage requestMessage;
    MdResponseMessage responseMessage;
    PushbackMessage pushbackMessage;
    PublishMessage publishMessage;

    long timeout = 1;
    long lastTime = s_clock();
    long thisTime = 0;
    long timeDelta = 0;
    long loopTimes = 0;
    long mdCount = 0;

    while(1) {
        // 尝试读取通讯管道
        zmq::pollitem_t pullItems [] = {
            { request, 0, ZMQ_POLLIN, 0 },
            { pushback, 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll (pullItems, 2, timeout);

        // 接收到来自客户端的请求
        if (pullItems[0].revents & ZMQ_POLLIN) {
            // 调用对应的api函数
            std::cout << "接收到1条客户端的请求..." << std::endl;
            requestMessage.recv(request);
            std::cout << "要求调用" << requestMessage.apiName << std::endl;
            int result = api.callApiByName(requestMessage.apiName,requestMessage.reqInfo);
            Json::Value jsonErrorInfo;
            if ( result == 0 ){
                jsonErrorInfo["ErrorID"] = 0;
                jsonErrorInfo["ErrorMsg"] = "";
                std::cout << "调用对应api返回成功" << std::endl;
            }else{
                jsonErrorInfo["ErrorID"] = api.getLastErrorID();
                jsonErrorInfo["ErrorMsg"] = api.getLastErrorMsg();
                std::cout << "调用api出错:(" << api.getLastErrorID()
                    << ")" << api.getLastErrorMsg() << std::endl;
            }
            responseMessage.header = "RESPONSE";
            responseMessage.apiName = requestMessage.apiName;
            responseMessage.errorInfo = jsonErrorInfo.toStyledString();
            responseMessage.send(request);
            std::cout << "信息已返回客户端..." << std::endl;
        }

        // 处理通讯线程通过pushback管道发回的消息
        if ( pullItems[1].revents & ZMQ_POLLIN) {

            // 从pushback管道读取消息
            pushbackMessage.recv(pushback);
            publishMessage.header = "PUBLISH";
            publishMessage.apiName = pushbackMessage.apiName;
            publishMessage.respInfo = pushbackMessage.respInfo;
            publishMessage.send(publish);

            // 如果消息是行情数据,将其返回客户端
            if (pushbackMessage.apiName == "OnRtnDepthMarketData") {
                mdCount++;
            }else{
                std::cout << "收到服务器响应(推送)消息..." << std::endl;
                std::cout << "已经消息推送到订阅接口..." << std::endl;
            }
        }

        // 打印提示信息
        thisTime = s_clock();
        timeDelta = thisTime - lastTime;
        lastTime = thisTime;
        loopTimes += timeDelta;
        if ( loopTimes >= 1000 ) {
            loopTimes = 0;
            std::cout << "main():" << "接收到行情数据:" << mdCount << std::endl;
            mdCount = 0;

            // 忠诚选项的处理
            if (loyalty) {
                // 检查父进程是否还在运行
                pid_t ppid = getppid();
                if ( ppid != originalPpid ) {
                    // 如果父进程不在运行程序退出
                    break;
                }
            }
        }
    }
}
