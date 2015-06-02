
#include <Configure.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include <comhelper.h>


/// 构造函数
Configure::Configure() {

}

/// 读取配置信息
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

void  Configure::loadFromCommandLine(CommandOption commandOption){



}
