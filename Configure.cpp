
#include <Configure.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include <comhelper.h>



/// 构造函数
Configure::Configure() {

}

/// 从环境变量中读取配置信息
void Configure::loadFromEnvironment() {
    /// 服务器地址
    this->frontAddress = getenv("CTP_FRONT_ADDRESS");
    assert(this->frontAddress);
    ///经纪公司代码
    this->brokerID = getenv("CTP_BROKER_ID");
    assert(this->brokerID);
    ///用户代码
    this->userID = getenv("CTP_USER_ID");
    assert(this->userID);
    ///密码
    this->password = getenv("CTP_PASSWORD");
    assert(this->password);
    /// 请求通信管道
    this->requestPipe = getenv("CTP_REQUEST_PIPE");
    assert(this->requestPipe);
    /// 回调信息管道
    this->pushbackPipe = getenv("CTP_PUSHBACK_PIPE");
    assert(this->pushbackPipe);
    /// 广播信息管道
    this->publishPipe = getenv("CTP_PUBLISH_PIPE");
    assert(this->publishPipe);
}

/// 从命令行读取配置信息
void  Configure::loadFromCommandLine(CommandOption commandOption){

    /// 服务器地址
    char * frontAddress = commandOption.get("--FrontAddress");
    assert(frontAddress != NULL);
    this->frontAddress = frontAddress;

    ///经纪公司代码
    char * brokerID = commandOption.get("--BrokerID");
    assert(brokerID != NULL);
    this->brokerID = brokerID;

    ///用户代码
    char * userID = commandOption.get("--UserID");
    assert(userID != NULL);
    this->userID = userID;

    ///密码
    char * password = commandOption.get("--Password");
    assert(password != NULL);
    this->password = password;

    /// 请求通信管道
    char * requestPipe = commandOption.get("--RequestPipe");
    assert(requestPipe != NULL);
    this->requestPipe = requestPipe;

    /// 回调信息管道
    char * pushbackPipe = commandOption.get("--PushbackPipe");
    assert(pushbackPipe != NULL);
    this->pushbackPipe = pushbackPipe;

    /// 广播信息管道
    char * publishPipe = commandOption.get("--PublishPipe");
    assert(publishPipe != NULL);
    this->publishPipe = publishPipe;

}



/// 构造函数
MdConfigure::MdConfigure() {

}

/// 从环境变量中读取配置信息
void MdConfigure::loadFromEnvironment(){
    /// 服务器地址
    this->frontAddress = getenv("CTP_FRONT_ADDRESS");
    assert(this->frontAddress);
    ///经纪公司代码
    this->brokerID = getenv("CTP_BROKER_ID");
    assert(this->brokerID);
    ///用户代码
    this->userID = getenv("CTP_USER_ID");
    assert(this->userID);
    ///密码
    this->password = getenv("CTP_PASSWORD");
    assert(this->password);
    /// 请求通信管道
    //this->requestPipe = getenv("CTP_REQUEST_PIPE");
    //assert(this->requestPipe);
    /// 回调信息管道
    this->pushbackPipe = getenv("CTP_PUSHBACK_PIPE");
    assert(this->pushbackPipe);
    /// 广播信息管道
    this->publishPipe = getenv("CTP_PUBLISH_PIPE");
    assert(this->publishPipe);
}

/// 从命令行读取配置信息
void MdConfigure::loadFromCommandLine(CommandOption commandOption){

    /// 服务器地址
    char * frontAddress = commandOption.get("--FrontAddress");
    assert(frontAddress != NULL);
    this->frontAddress = frontAddress;

    ///经纪公司代码
    char * brokerID = commandOption.get("--BrokerID");
    assert(brokerID != NULL);
    this->brokerID = brokerID;

    ///用户代码
    char * userID = commandOption.get("--UserID");
    assert(userID != NULL);
    this->userID = userID;

    ///密码
    char * password = commandOption.get("--Password");
    assert(password != NULL);
    this->password = password;

    /// 请求通信管道
    //char * requestPipe = commandOption.get("--RequestPipe");
    //assert(requestPipe != NULL);
    //this->requestPipe = requestPipe;

    /// 回调信息管道
    char * pushbackPipe = commandOption.get("--PushbackPipe");
    assert(pushbackPipe != NULL);
    this->pushbackPipe = pushbackPipe;

    /// 广播信息管道
    char * publishPipe = commandOption.get("--PublishPipe");
    assert(publishPipe != NULL);
    this->publishPipe = publishPipe;

    /// 品种列表配置文件
    char * instrumentIDConfigFile = commandOption.get("--InstrumentIDConfigFile");
    assert(instrumentIDConfigFile != NULL);
    this->instrumentIDConfigFile = instrumentIDConfigFile;
    // 确保文件存在
    assert(fileExists(this->instrumentIDConfigFile));
    // 读取文件内容,并解析数据
    Json::Reader jsonReader;
    Json::Value instrumentIDList;
    std::string fileContent = fileReadAll(this->instrumentIDConfigFile);
    assert(jsonReader.parse(fileContent,instrumentIDList));
    // 确保不超出品种数组的长度
    assert(instrumentIDList.size()<INSTRUMENT_ARRAY_SIZE);

    for (unsigned int i = 0; i < instrumentIDList.size(); i++){
        const char * instrumentID = instrumentIDList.asString().c_str();
        instrumentIDArray[i] = (char *)malloc(strlen(instrumentID)+1);
        strcpy(instrumentIDArray[i],instrumentID);
    }
    instrumentCount = instrumentIDList.size();

}
