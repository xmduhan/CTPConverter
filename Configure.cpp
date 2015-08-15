
#include <Configure.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
//#include <comhelper.h>
#include <iostream>


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
    /// 返回消息管道
    this->responsePipe = getenv("CTP_RESPONSE_PIPE");
    assert(this->responsePipe);
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

    /// 返回通信管道
    char * responsePipe = commandOption.get("--ResponsePipe");
    assert(responsePipe != NULL);
    this->responsePipe = responsePipe;

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


void MdConfigure::loadInstrumentIDList(){
    // 确保文件存在
    assert(fileExists(this->instrumentIDConfigFile));
    // 读取文件内容,并解析数据
    Json::Reader jsonReader;
    Json::Value instrumentIDList;
    std::string fileContent = fileReadAll(this->instrumentIDConfigFile);
    assert(jsonReader.parse(fileContent,instrumentIDList));
    // 确保不超出品种数组的长度
    assert(instrumentIDList.size()>0);
    assert(instrumentIDList.size()<INSTRUMENT_ARRAY_SIZE);
    // 读取品种订阅列表转化位ctp md api要求的格式
    for (unsigned int i = 0; i < instrumentIDList.size(); i++){
        const char * instrumentID = instrumentIDList[i].asString().c_str();
        instrumentIDArray[i] = (char *) malloc(strlen(instrumentID)+1);
        strcpy(instrumentIDArray[i],instrumentID);
    }
    instrumentCount = instrumentIDList.size();
}

/// 从环境变量中读取配置信息
void MdConfigure::loadFromEnvironment(){
    /// 服务器地址
    this->frontAddress = getenv("CTP_MD_FRONT_ADDRESS");
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
    /// 请求通信管道
    this->responsePipe = getenv("CTP_RESPONSE_PIPE");
    assert(this->responsePipe);
    /// 回调信息管道
    this->pushbackPipe = getenv("CTP_PUSHBACK_PIPE");
    assert(this->pushbackPipe);
    /// 广播信息管道
    this->publishPipe = getenv("CTP_PUBLISH_PIPE");
    assert(this->publishPipe);

    // 读取品种列表配置文件
    //this->instrumentIDConfigFile = getenv("CTP_INSTRUMENT_ID_CONFIG_FILE");
    //assert(this->instrumentIDConfigFile != NULL);
    //assert(fileExists(this->instrumentIDConfigFile));
    //loadInstrumentIDList();
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
    char * requestPipe = commandOption.get("--RequestPipe");
    assert(requestPipe != NULL);
    this->requestPipe = requestPipe;

    /// 请求通信管道
    char * responsePipe = commandOption.get("--ResponsePipe");
    assert(responsePipe != NULL);
    this->responsePipe = responsePipe;

    /// 回调信息管道
    char * pushbackPipe = commandOption.get("--PushbackPipe");
    assert(pushbackPipe != NULL);
    this->pushbackPipe = pushbackPipe;

    /// 广播信息管道
    char * publishPipe = commandOption.get("--PublishPipe");
    assert(publishPipe != NULL);
    this->publishPipe = publishPipe;

    /// 品种列表配置文件
    //char * instrumentIDConfigFile = commandOption.get("--InstrumentIDConfigFile");
    //assert(instrumentIDConfigFile != NULL);
    //assert(fileExists(instrumentIDConfigFile));
    //this->instrumentIDConfigFile = instrumentIDConfigFile;
    //loadInstrumentIDList();

}
