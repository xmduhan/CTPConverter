#include <converter.h>
#include <json/json.h>
#include <comhelper.h>


// 配置数据
Configure configtest;

/// 读取配置数据
void loadConfig() {
    configtest.load();
    printf("FrontAddress=%s\n",configtest.FrontAddress);
    printf("BrokerID=%s\n",configtest.BrokerID);
    printf("UserID=%s\n",configtest.UserID);
    printf("Password=%s\n",configtest.Password);
    printf("RequestPipe=%s\n",configtest.RequestPipe);
    printf("PushbackPipe=%s\n",configtest.PushbackPipe);
    printf("PublishPipe=%s\n",configtest.PublishPipe);
}


void test01() {
    zmq::context_t * pContext = new zmq::context_t(1);
    zmq::socket_t * pReceiver = new zmq::socket_t(*pContext, ZMQ_PULL);
    pReceiver->connect(configtest.PushbackPipe);
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

    while(1) {
        try {
            requestMessage.recv(*pReceiver);
            std::cout << "requestMessage.header=" << requestMessage.header << std::endl;
            std::cout << "requestMessage.apiName=" << requestMessage.apiName << std::endl;
            std::cout << "requestMessage.reqInfo=" << requestMessage.reqInfo << std::endl;
            std::cout << "requestMessage.metaData=" << requestMessage.metaData << std::endl;
        } catch(std::exception & e) {
            std::cout << e.what() << std::endl;
        }
    }

}

void test02() {
    loadConfig();
    CApiWrapper api(&configtest);
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

        for (int i=0; i<arrayObj.size(); i++) {
            const Json::Value::Members memberNames = arrayObj[i].getMemberNames();
            for(int j=0; j<memberNames.size(); j++) {
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

void readJsonDict() {
    std::string strValue = "{\"a\":\"1\",\"b\":\"2\",\"c\":\"3\"}";
    Json::Reader reader;
    Json::Value value;
    reader.parse(strValue, value);
    std::cout << "value.isObject=" << value.isObject() << std::endl;
    const Json::Value::Members memberNames = value.getMemberNames();
    for(int i=0; i<memberNames.size(); i++) {
        std::cout << memberNames[i] << ":" << value[memberNames[i]] << std::endl;
    }
}

void test03() {
    configtest.load();
    CThostFtdcInstrumentField pInstrument;
    CThostFtdcRspInfoField pRspInfo;
    int nRequestID;
    bool bIsLast;
    CTraderHandler traderHandler = CTraderHandler(&configtest);
    while(1) {
        traderHandler.OnRspQryInstrument(&pInstrument,&pRspInfo,nRequestID,bIsLast);
        //traderHandler.OnRspQryInstrument(0,&pRspInfo,nRequestID,bIsLast);
        std::cout << "message send ..." << std::endl;
        getchar();
    }
}

void test04() {
    std::string jsonString = "\
    {\
       \"ResponseMethod\" : \"ReqQryTradingAccount\",\
       \"Parameters\" : {\
          \"Data\" : {\
             \"string\" : \"1234567890\",\
             \"char\" : \"c\",\
             \"int\" : 123456,\
             \"double\" : 3.1415926\
            }\
        }\
    }\
    ";

    char str[10];
    char c = '0';
    int i = 0;
    double d = 0.0;

    try {
        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        Assert<std::exception>(!Data.empty());

        // TODO : 处理没有提供的字段并设置默认值
        ////////////// 字符处理过程 ////////////////
        if ( !Data["char"].empty()) {
            c = Data["char"].asString()[0];
        } else {
            c = '0';
        }
        ///////////// 整型处理过程 ////////////////
        if (!Data["int"].empty()) {
            i = Data["int"].asInt();
        } else {
            i = 0;
        }
        ///////////// 浮点处理过程 ////////////////
        if (!Data["double"].empty()) {
            d = Data["double"].asDouble();
        } else {
            d = 0;
        }
        ///////////// 字符串处理过程 ////////////////
        if (!Data["string"].empty()) {
            str[sizeof(str)-1] = 0;
            strncpy(str,Data["string"].asCString(),sizeof(str)-1);
        } else {
            strcpy(str,"");
        }

        // 查看输出结果
        std::cout << "c=" << c << std::endl;
        std::cout << "i=" << i << std::endl;
        std::cout << "d=" << d << std::endl;
        std::cout << "str=" << str << '|' << std::endl;

        for(i=0; i<sizeof(str); i++) {
            printf("%d:%d\n",i,(int)str[i]);
        }

        //}catch (std::exception & e){
    } catch (...) {
        //std::cout << "exception:" << e.what() << std::endl;
        std::cout << "json数据格式错误" << std::endl;
    }
}

void test05(){
    std::string jsonString = "\
    {\
       \"ResponseMethod\" : \"ReqQryTradingAccount\",\
       \"Parameters\" : {\
          \"Data\" : {\
              \"a\":1 \
            }\
        }\
    }\
    ";
    loadConfig();
    CApiWrapper api(&configtest);
    api.init();
    int result  ;

    for( int i=0; i<10; i++ ) {
        result = api.ReqQryInvestor(jsonString);
        std::cout << "result=" << result << std::endl;

        // 读取Api响应数据
        zmq::context_t context(1);
        zmq::socket_t receiver(context, ZMQ_PULL);
        PushbackMessage message;
        receiver.connect(configtest.PushbackPipe);
        message.recv(receiver);
        std::cout << "message.requestID = " << message.requestID << std::endl;
        std::cout << "message.apiName = " << message.apiName << std::endl;
        std::cout << "message.respInfo = " << message.respInfo << std::endl;
        sleep(1);
    }
}
