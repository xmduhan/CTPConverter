
#include <stdio.h>
#include <CTraderHandler.h>
#include <Configure.h>


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

    loadConfig();

    //CTraderHandler traderHandler = CTraderHandler();
    //traderHandler.OnRspQryInstrument(0,0,0,0);



    return 0;
}