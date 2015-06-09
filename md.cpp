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

    // 初始化zmq环境
    zmq::context_t context(1);
    zmq::socket_t pushback  (context, ZMQ_PULL);
    zmq::socket_t publish  (context, ZMQ_PUB);

    // 连接对应通讯管道
    pushback.connect(config.pushbackPipe);
    publish.bind(config.publishPipe);

    std::cout << "main():行情广播地址为:" << config.publishPipe << std::endl;
    sleep(1);    // 给一定时间让订阅者连接上来，以免错过条消息


    // 初始化api接口实例
    CMdWrapper api(&config);
    api.init();

    // 定义消息变量
    PushbackMessage pushbackMessage;
    MarketDataMessage marketDataMessage;

    long timeout = 1;
    long lastTime = s_clock();
    long thisTime = 0;
    long timeDelta = 0;
    long loopTimes = 0;
    long mdCount = 0;

    std::cout << "main():转发市场报价信息..." << std::endl;
    api.SubscribeMarketData(config.instrumentIDArray,config.instrumentCount);

    // 发送一条空消息供订阅客户端测试通路.
    // 注意:程序能执行到这里,说明已成功和ctp服务器建立连接.
    // 所以当客户端收到这条空消息时可以认为连接行情通道建立成功.
    marketDataMessage.marketDataInfo = "";
    marketDataMessage.send(publish);

    while(1) {
        zmq::pollitem_t pullItems [] = {
            { pushback, 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll (pullItems, 1, timeout);
        if ( pullItems[0].revents & ZMQ_POLLIN) {

            // 从pushback管道读取消息
            pushbackMessage.recv(pushback);

            // 如果消息是行情数据,将其返回客户端
            if (pushbackMessage.apiName == "OnRtnDepthMarketData") {
                marketDataMessage.marketDataInfo = pushbackMessage.respInfo;
                marketDataMessage.send(publish);
                mdCount++;
            }

            // 如果消息是订阅处理结果将其显示出来
            if (pushbackMessage.apiName == "OnRspSubMarketData") {
                Json::Reader jsonReader;
                Json::Value respInfo;
                assert(jsonReader.parse(pushbackMessage.respInfo,respInfo));
                int errorID = respInfo["Parameters"]["RspInfo"]["ErrorID"].asInt();
                std::string instrumentID = respInfo["Parameters"]["Data"]["InstrumentID"].asString();
                assert(errorID==0);
                std::cout << instrumentID << ":行情订阅成功." << std::endl;
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
        }
    }
}
