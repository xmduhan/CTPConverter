
#include <Configure.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/// 构造函数
Configure::Configure() {

}

/// 读取配置信息
void Configure::load() {
    /// 服务器地址
    this->FrontAddress = getenv("CTP_FrontAddress");
    assert(this->FrontAddress);
    ///经纪公司代码
    this->BrokerID = getenv("CTP_BrokerId");
    assert(this->BrokerID);
    ///用户代码
    this->UserID = getenv("CTP_UserId");
    assert(this->UserID);
    ///密码
    this->Password = getenv("CTP_Password");
    assert(this->Password);
    /// 请求通信管道
    this->RequestPipe = getenv("CTP_RequestPipe");
    assert(this->RequestPipe);
    /// 回调信息管道
    this->PushbackPipe = getenv("CTP_PushbackPipe");
    assert(this->PushbackPipe);

    /// 广播信息管道
    this->PublishPipe = getenv("CTP_PublishPipe");
    assert(this->PublishPipe);
}
