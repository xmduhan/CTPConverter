
#include <Configure.h>
#include <stdlib.h>
#include <stdio.h>



/// 构造函数
Configure::Configure() {

}

/// 读取配置信息
void Configure::load() {
    this->FrontAddress = getenv("CTP_FrontAddress");
    ///经纪公司代码
    this->BrokerID = getenv("CTP_BrokerId");
    ///用户代码
    this->UserID = getenv("CTP_UserId");
    ///密码
    this->Password = getenv("CTP_Password");
    /// 请求通信管道
    this->RequestPipe = getenv("CTP_RequestPipe");
    /// 回调信息管道
    this->PushbackPipe = getenv("CTP_PushbackPipe");
    /// 广播信息管道
    this->PublishPipe = getenv("CTP_PublishPipe");
}
