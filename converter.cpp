
#include <stdio.h>
#include <CTraderHandler.h>
#include <Configure.h>
#include <CApiWrapper.h>
#include <unistd.h>
#include <zmq.hpp>
#include <zhelpers.hpp>



// 配置数据
Configure config;

/// 读取配置数据
void loadConfig() {
    config.load();
    printf("FrontAddress=%s\n",config.FrontAddress);
    printf("BrokerID=%s\n",config.BrokerID);
    printf("UserID=%s\n",config.UserID);
    printf("Password=%s\n",config.Password);
    printf("RequestPipe=%s\n",config.RequestPipe);
    printf("PushbackPipe=%s\n",config.PushbackPipe);
    printf("PublishPipe=%s\n",config.PublishPipe);
}


int main() {

    //loadConfig();

    //CTraderHandler traderHandler = CTraderHandler();
    //traderHandler.OnRspQryInstrument(0,0,0,0);

    //CApiWrapper api(&config);
    //api.init();

    zmq::context_t * pContext = new zmq::context_t(1);
    zmq::socket_t * pReceiver = new zmq::socket_t(*pContext, ZMQ_PULL);
    pReceiver->connect("tcp://localhost:10000");

    while(1) {
        std::cout << "-----------begin-----------" << std::endl;
        do {
            std::cout << "接收到来自[tcp://localhost:10000]的消息:" << s_recv(*pReceiver) << std::endl;
        } while(s_more(*pReceiver));
        std::cout << "------------end------------" << std::endl;
        sleep(5);
    }
    return 0;
}