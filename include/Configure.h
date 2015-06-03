#pragma once
#include <ThostFtdcUserApiDataType.h>
#include <comhelper.h>
#include <json/json.h>

#define INSTRUMENT_ARRAY_SIZE 1024

class Configure {

public:
    /// 构造函数
    Configure();

    /// 服务器地址
    char * frontAddress;
    ///经纪公司代码
    char * brokerID;
    ///用户代码
    char * userID;
    ///密码
    char * password;
    /// 请求通信管道
    char * requestPipe;
    /// 回调信息管道
    char * pushbackPipe;
    /// 广播信息管道
    char * publishPipe;

    /// 读取配置信息
    void loadFromEnvironment();
    void loadFromCommandLine(CommandOption commandOption);
};


class MdConfigure {

public:
    /// 构造函数
    MdConfigure();

    /// 服务器地址
    char * frontAddress;
    ///经纪公司代码
    char * brokerID;
    ///用户代码
    char * userID;
    ///密码
    char * password;
    /// 请求通信管道
    //char * requestPipe;
    /// 回调信息管道
    char * pushbackPipe;
    /// 广播信息管道
    char * publishPipe;
    /// 订阅品种配置文件的路径
    char * instrumentIDConfigFile;
    /// 需要订阅的品种标识
    char * instrumentIDArray[INSTRUMENT_ARRAY_SIZE];
    /// 要订阅品种的长度
    int instrumentCount;

    /// 读取配置信息
    void loadFromEnvironment();
    void loadFromCommandLine(CommandOption commandOption);
};
