
#include <converter.h>


// 配置数据
Configure config;

/// 读取配置数据
void loadConfig(){
    config.load();
    printf("FrontAddress=%s\n",config.FrontAddress);
    printf("BrokerID=%s\n",config.BrokerID);
    printf("UserID=%s\n",config.UserID);
    printf("Password=%s\n",config.Password);
    printf("RequestPipe=%s\n",config.RequestPipe);
    printf("PushbackPipe=%s\n",config.PushbackPipe);
    printf("PublishPipe=%s\n",config.PublishPipe);
}


void test01(){
    zmq::context_t * pContext = new zmq::context_t(1);
    zmq::socket_t * pReceiver = new zmq::socket_t(*pContext, ZMQ_PULL);
    pReceiver->connect(config.PushbackPipe);
    //pReceiver->connect("ipc://ipc/pushback");

    //zmq::socket_t * pSender = new zmq::socket_t(*pContext, ZMQ_PUSH);
    ////pSender->bind("tcp://*:10000");
    //pSender->bind("ipc://pushback");

    /*
    while(1){
        std::cout << "-----------begin-----------" << std::endl;
        do {
            std::cout << "接收到来自[tcp://localhost:10000]的消息:" << s_recv(*pReceiver) << std::endl;
        } while(s_more(*pReceiver));
        std::cout << "------------end------------" << std::endl;
        sleep(5);
    }
    */

    RequestMessage requestMessage;
    //requestMessage.send(*pSender);

    while(1){
        try{
            requestMessage.recv(*pReceiver);
            std::cout << "requestMessage.header=" << requestMessage.header << std::endl;
            std::cout << "requestMessage.apiName=" << requestMessage.apiName << std::endl;
            std::cout << "requestMessage.reqInfo=" << requestMessage.reqInfo << std::endl;
            std::cout << "requestMessage.metaData=" << requestMessage.metaData << std::endl;
        }catch(std::exception & e){
            std::cout << e.what() << std::endl;
        }
    }

}



int main(){

    loadConfig();

    //CTraderHandler traderHandler = CTraderHandler();
    //traderHandler.OnRspQryInstrument(0,0,0,0);

    CApiWrapper api(&config);
    api.init();
    return 0;
}
