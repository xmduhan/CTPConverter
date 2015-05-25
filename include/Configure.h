#pragma once
#include <ThostFtdcUserApiDataType.h>


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
    void load();
};
