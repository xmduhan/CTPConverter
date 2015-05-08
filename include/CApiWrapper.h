
#include <ThostFtdcTraderApi.h>
#include <ThostFtdcUserApiStruct.h>
#include <ThostFtdcUserApiDataType.h>
#include <Configure.h>
#include <CTraderHandler.h>


class CApiWrapper {

public:
    /// 构造函数
    CApiWrapper(Configure * pConfigure);
    /////////////////  变量定义 //////////////////
    /// 对应的API实例
    CThostFtdcTraderApi * pTraderApi;
    /// 对应的SPI实例
    CTraderHandler * pTraderHandler;
    /// 配置信息
    Configure * pConfigure;
    /// RequestID序列器
    int RequestID;
    /// 上次出错代码
    int lastErrorCode;
    /// 上次出错信息
    char lastErrorMessage[1024];
    ////////////////// 方法定义 ///////////////////
    /// 启动CTP连接
    void init();
    /// 获取下一个RequestID序列
    int getNextRequestID();
    /// 获取当前RequestID序列
    int getCurrentRequestID();
    /// 获取上次出错代码
    int getLastErrorCode();
    /// 获取上次错误信息
    char * getLastErrorMessage();

};