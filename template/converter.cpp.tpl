
#include <converter.h>
#include <json/json.h>


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

void test02(){
    loadConfig();
    CApiWrapper api(&config);
    api.init();
}

void writeJson() {
    using namespace std;

    Json::Value root;
    Json::Value arrayObj;
    Json::Value item;

    item["cpp"] = "jsoncpp";
    item["java"] = "jsoninjava";
    item["php"] = "support";
    arrayObj.append(item);

    root["name"] = "json";
    root["array"] = arrayObj;

    root.toStyledString();
    std::string out = root.toStyledString();
    std::cout << out << std::endl;
}

void readJson() {
    using namespace std;
    std::string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\",\"cpp1\":\"jxx\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";

    Json::Reader reader;
    Json::Value value;

    if (reader.parse(strValue, value))
    {
        std::string out = value["name"].asString();
        //std::cout << out << std::endl;
        const Json::Value arrayObj = value["array"];

        for (int i=0; i<arrayObj.size(); i++){
            const Json::Value::Members memberNames = arrayObj[i].getMemberNames();
            for(int j=0; j<memberNames.size(); j++){
                std::cout << memberNames[j] << std::endl;
            }
        }
        //for (unsigned int i = 0; i < arrayObj.size(); i++)
        //{
            //if (!arrayObj[i].isMember("cpp"))
            //    continue;
            //out = arrayObj[i].asString();
            //std::cout << out;
            //if (i != (arrayObj.size() - 1))
            //    std::cout << std::endl;
            //std::cout << "1111" << std::endl;
        //}
    }
}

void readJsonDict(){
    std::string strValue = "{\"a\":\"1\",\"b\":\"2\",\"c\":\"3\"}";
    Json::Reader reader;
    Json::Value value;
    reader.parse(strValue, value);
    std::cout << "value.isObject=" << value.isObject() << std::endl;
    const Json::Value::Members memberNames = value.getMemberNames();
    for(int i=0; i<memberNames.size(); i++){
        std::cout << memberNames[i] << ":" << value[memberNames[i]] << std::endl;
    }
}


int main(){
    config.load();
    CThostFtdcInstrumentField pInstrument;
    CThostFtdcRspInfoField pRspInfo;
    int nRequestID;
    bool bIsLast;
    CTraderHandler traderHandler = CTraderHandler(&config);
    traderHandler.OnRspQryInstrument(&pInstrument,&pRspInfo,nRequestID,bIsLast);
    return 0;
}
