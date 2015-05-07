#include <ThostFtdcUserApiDataType.h>

class Configure {

public:
    /// 构造函数
    Configure();

    /// 服务器地址
    char * FrontAddress;
    ///经纪公司代码
    char * BrokerID;
    ///用户代码
    char * UserID;
    ///密码
    char * Password;
    /// 请求通信管道
    char * RequestPipe;
    /// 回调信息管道
    char * PushbackPipe;
    /// 广播信息管道
    char * PublishPipe;

    /// 读取配置信息
    void load();
};