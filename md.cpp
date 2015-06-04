#include <CMdHandler.h>
#include <CMdWrapper.h>
#include <unistd.h>

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

    // 初始化api接口实例
    CMdWrapper api(&config);
    api.init();


    // 初始化zmq环境
    zmq::context_t context(1);
    zmq::socket_t pushback  (context, ZMQ_PULL);
    zmq::socket_t publish  (context, ZMQ_PUB);

    // 连接对应通讯管道
    pushback.connect(config.pushbackPipe);
    publish.bind(config.publishPipe);

    std::cout << "main():行情广播地址为:" << config.publishPipe << std::endl;

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
    while(1) {
        zmq::pollitem_t pullItems [] = {
            { pushback, 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll (pullItems, 1, timeout);
        if ( pullItems[0].revents & ZMQ_POLLIN) {
            pushbackMessage.recv(pushback);
            if (pushbackMessage.apiName == "OnRtnDepthMarketData") {
                //std::cout << "main():接收到行情消息" << i++ << std::endl;
                marketDataMessage.marketDataInfo = pushbackMessage.respInfo;
                marketDataMessage.send(publish);
                mdCount++;
            }else{
                // TODO 需要增加订阅成功的判断和提示
                std::cout << "main():接收到其他消息****" << std::endl;
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
