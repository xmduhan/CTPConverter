#include <CMdWrapper.h>
#include <json/json.h>
#include <comhelper.h>
#include <string>

/// 构造函数
CMdWrapper::CMdWrapper(MdConfigure * pConfigure) {

    // 读取配置数据信息
    this->pConfigure = pConfigure;

    // 创建CTP API工作对象
    pMdApi = CThostFtdcMdApi::CreateFtdcMdApi();

    // 创建SPI工作对象并让其和API关联
    pMdHandler = new CMdHandler(pConfigure);
    pMdApi->RegisterSpi(pMdHandler);

    // 初始化RequestID序列
    RequestID = 0;

    // 初始化上次出错代码和出错信息
    lastErrorID = 0;
    lastErrorMsg = "";

    ////////////// API方法的wrapper ///////////////

    ///登出请求
    int ReqUserLogout(std::string jsonString);

    ///用户登录请求
    int ReqUserLogin(std::string jsonString);


    std::map<std::string,int (CMdWrapper::*) (std::string)> apiMap;

    int callApiByName(std::string apiName,std::string jsonString);

}

// 将所有api函数映射到名称
void CMdWrapper::initApiMap() {

    //ReqUserLogout
    apiMap["ReqUserLogout"] = &CMdWrapper::ReqUserLogout;

    //ReqUserLogin
    apiMap["ReqUserLogin"] = &CMdWrapper::ReqUserLogin;

    //SubscribeMarketData
    apiMap["SubscribeMarketData"] = &CMdWrapper::SubscribeMarketData;
    //UnSubscribeMarketData
    apiMap["UnSubscribeMarketData"] = &CMdWrapper::UnSubscribeMarketData;
}


/// 启动CTP连接
void CMdWrapper::init() {
    std::cout << "CMdWrapper::init():开始执行..." << std::endl;
    // 初始化api名称对照表
    initApiMap();

    // 创建zmq通讯环境
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_PULL);
    PushbackMessage message;

    /// 设置服务器地址
    pMdApi->RegisterFront(pConfigure->frontAddress);

    // 连接spi的Pushback管道
    std::cout << "CMdWrapper::init():Pushback管道地址为:" << pConfigure->pushbackPipe << std::endl;
    receiver.connect(pConfigure->pushbackPipe);

    // 连接交易系统
    std::cout << "CMdWrapper::init():尝试连接服务器..." << std::endl;
    pMdApi->Init();

    // 等待服务器发出OnFrontConnected事件
    std::cout << "CMdWrapper::init():等待服务器响应消息..." << std::endl;
    message.recv(receiver);
    std::cout << "CMdWrapper::init():已收到服务器响应消息..." << std::endl;

    // 确认收到的返回信息是由OnFrontConnected发出
    assert(message.requestID.compare("0") == 0);
    assert(message.apiName.compare("OnFrontConnected") == 0);
    assert(message.respInfo.compare("") == 0);

    // 发出登陆请求
    std::cout << "CMdWrapper::init():发出登录请求..." << std::endl;
    CThostFtdcReqUserLoginField userLoginField;
    strcpy(userLoginField.BrokerID,pConfigure->brokerID);
    strcpy(userLoginField.UserID,pConfigure->userID);
    strcpy(userLoginField.Password,pConfigure->password);
    pMdApi->ReqUserLogin(&userLoginField,getNextRequestID());


    // 等待登录成功返回信息
    std::cout << "CMdWrapper::init():等待登录结果..." << std::endl;
    message.recv(receiver);
    std::cout << "CMdWrapper::init():已收到登录返回信息..." << std::endl;
    //std::cout << "message.requestID=" << message.requestID << std::endl;
    //assert(message.requestID.compare("1") == 0);
    assert(message.apiName.compare("OnRspUserLogin") == 0);

    // 检查是否登录成功,如果不成功将终止程序
    Json::Reader jsonReader;
    Json::Value jsonData;
    if (!jsonReader.parse(message.respInfo,jsonData)) {
        throw std::exception();
    }
    int ErrorID = jsonData["Parameters"]["Data"]["RspInfo"]["ErrorID"].asInt();
    assert(ErrorID == 0);

    std::cout << "CMdWrapper::init():登录成功..." << std::endl;

    std::cout << "CMdWrapper::init():执行完毕..." << std::endl;


}



/// 获取下一个RequestID序列
int CMdWrapper::getNextRequestID() {
    return 	++this->RequestID;
}

/// 获取当前RequestID序列
int CMdWrapper::getCurrentRequestID() {
    return 	this->RequestID;
}

/// 获取上次出错代码
int CMdWrapper::getLastErrorID() {
    return lastErrorID;
}

/// 获取上次错误信息
std::string CMdWrapper::getLastErrorMsg() {
    return lastErrorMsg;
}


# define MAX_SUBCRIBE_COUNT 1000
///订阅行情。
int CMdWrapper::SubscribeMarketData(std::string jsonString) {
    //return pMdApi->SubscribeMarketData(ppInstrumentID,nCount);
    char *ppInstrumentID[MAX_SUBCRIBE_COUNT];
    int nCount;
    int result;

    try {
        std::cout << jsonString << std::endl;
        //1. 解析json格式
        Json::Reader jsonReader;
        Json::Value jsonData;
        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }
        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        if ( Data.size() > MAX_SUBCRIBE_COUNT ) {
            lastErrorID = -1002;
            lastErrorMsg = "一次订阅行情的品种数量太多";
            return -1;
        }

        nCount = Data.size();
        for (unsigned int i = 0; i < Data.size(); i++) {
            const char * instrumentID = Data[i].asString().c_str();
            ppInstrumentID[i] = (char *) instrumentID;
            std::cout << i << ":*+*" << instrumentID << std::endl;
        }

        //nCount = 2;
        //ppInstrumentID[0] = (char *) "IF1509";
        //ppInstrumentID[1] = (char *) "IF1510";

        // 调用SubscribeMarketData
        result = pMdApi->SubscribeMarketData(ppInstrumentID,nCount);
        result = 0;

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    return 0;
}

///退订行情。
int CMdWrapper::UnSubscribeMarketData(std::string jsonString) {
    //return pMdApi->UnSubscribeMarketData(ppInstrumentID,nCount);
    //char *ppInstrumentID[], int nCount
}



///登出请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CMdWrapper::ReqUserLogout(std::string jsonString)
{
    printf("ReqUserLogout():被执行...\n");


    CThostFtdcUserLogoutField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    nRequestID = getNextRequestID();

    // 调用对应的CTP API函数
    int result =
        pMdApi->ReqUserLogout(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    //return nRequestID;
    return 0;
}


///用户登录请求
/// 调用成功返回RequestID,失败返回-1
/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
int CMdWrapper::ReqUserLogin(std::string jsonString)
{
    printf("ReqUserLogin():被执行...\n");


    CThostFtdcReqUserLoginField data;
    int nRequestID;

    // 解析json格式数据
    try {

        Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)) {
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
        //Assert<std::exception>(!Data.empty());


        // TODO:这里将pJsonData转化为对应的结构参数

        ///交易日 char TradingDay[9];
        if (!Data["TradingDay"].empty()) {
            data.TradingDay[sizeof(data.TradingDay)-1] = 0;
            strncpy(data.TradingDay,Data["TradingDay"].asCString(),sizeof(data.TradingDay)-1);
        } else {
            strcpy(data.TradingDay,"");
        }

        ///经纪公司代码 char BrokerID[11];
        if (!Data["BrokerID"].empty()) {
            data.BrokerID[sizeof(data.BrokerID)-1] = 0;
            strncpy(data.BrokerID,Data["BrokerID"].asCString(),sizeof(data.BrokerID)-1);
        } else {
            strcpy(data.BrokerID,"");
        }

        ///用户代码 char UserID[16];
        if (!Data["UserID"].empty()) {
            data.UserID[sizeof(data.UserID)-1] = 0;
            strncpy(data.UserID,Data["UserID"].asCString(),sizeof(data.UserID)-1);
        } else {
            strcpy(data.UserID,"");
        }

        ///密码 char Password[41];
        if (!Data["Password"].empty()) {
            data.Password[sizeof(data.Password)-1] = 0;
            strncpy(data.Password,Data["Password"].asCString(),sizeof(data.Password)-1);
        } else {
            strcpy(data.Password,"");
        }

        ///用户端产品信息 char UserProductInfo[11];
        if (!Data["UserProductInfo"].empty()) {
            data.UserProductInfo[sizeof(data.UserProductInfo)-1] = 0;
            strncpy(data.UserProductInfo,Data["UserProductInfo"].asCString(),sizeof(data.UserProductInfo)-1);
        } else {
            strcpy(data.UserProductInfo,"");
        }

        ///接口端产品信息 char InterfaceProductInfo[11];
        if (!Data["InterfaceProductInfo"].empty()) {
            data.InterfaceProductInfo[sizeof(data.InterfaceProductInfo)-1] = 0;
            strncpy(data.InterfaceProductInfo,Data["InterfaceProductInfo"].asCString(),sizeof(data.InterfaceProductInfo)-1);
        } else {
            strcpy(data.InterfaceProductInfo,"");
        }

        ///协议信息 char ProtocolInfo[11];
        if (!Data["ProtocolInfo"].empty()) {
            data.ProtocolInfo[sizeof(data.ProtocolInfo)-1] = 0;
            strncpy(data.ProtocolInfo,Data["ProtocolInfo"].asCString(),sizeof(data.ProtocolInfo)-1);
        } else {
            strcpy(data.ProtocolInfo,"");
        }

        ///Mac地址 char MacAddress[21];
        if (!Data["MacAddress"].empty()) {
            data.MacAddress[sizeof(data.MacAddress)-1] = 0;
            strncpy(data.MacAddress,Data["MacAddress"].asCString(),sizeof(data.MacAddress)-1);
        } else {
            strcpy(data.MacAddress,"");
        }

        ///动态密码 char OneTimePassword[41];
        if (!Data["OneTimePassword"].empty()) {
            data.OneTimePassword[sizeof(data.OneTimePassword)-1] = 0;
            strncpy(data.OneTimePassword,Data["OneTimePassword"].asCString(),sizeof(data.OneTimePassword)-1);
        } else {
            strcpy(data.OneTimePassword,"");
        }

        ///终端IP地址 char ClientIPAddress[16];
        if (!Data["ClientIPAddress"].empty()) {
            data.ClientIPAddress[sizeof(data.ClientIPAddress)-1] = 0;
            strncpy(data.ClientIPAddress,Data["ClientIPAddress"].asCString(),sizeof(data.ClientIPAddress)-1);
        } else {
            strcpy(data.ClientIPAddress,"");
        }

    } catch (...) {
        lastErrorID = -1001;
        lastErrorMsg = "json数据格式错误";
        return -1;
    }

    // 获取RequestID
    nRequestID = getNextRequestID();

    // 调用对应的CTP API函数
    int result =
        pMdApi->ReqUserLogin(&data, nRequestID);

    // TODO:检查API调用是否失败,并设置LastError信息
    if ( result != 0 ) {
        lastErrorID = result;
        switch(result) {
        case -1 :
            lastErrorMsg = "网络连接失败";
            break;
        case -2 :
            lastErrorMsg = "未处理请求超过许可数";
            break;
        case -3 :
            lastErrorMsg = "每秒发送请求超过许可数";
            break;
        default :
            lastErrorMsg = "未知错误";
        }

        //return result;
        return -1;
    }

    // 如果执行成功重置最近错误信息，并将RequestID返回调用程序
    lastErrorID = 0;
    lastErrorMsg = "";
    //return nRequestID;
    return 0;
}




// 通过名称调用api
int CMdWrapper::callApiByName(std::string apiName,std::string jsonString) {

    if ( apiMap.find(apiName) != apiMap.end() ) {
        return (this->*apiMap[apiName])(jsonString);
    } else {
        lastErrorID = -1000;
        lastErrorMsg = "没有这个接口函数";
        return -1;
    }
}