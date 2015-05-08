
#include <ThostFtdcTraderApi.h>
#include <ThostFtdcUserApiStruct.h>
#include <ThostFtdcUserApiDataType.h>
#include <Configure.h>
#include <CTraderHandler.h>


class CApiWrapper {

public:
    /// 构造函数
    CApiWrapper(Configure * pConfigure);
    /// 对应的API实例
    CThostFtdcTraderApi * pTraderApi;
    /// 对应的SPI实例
    CTraderHandler * pTraderHandler;
    /// 配置信息
    Configure * pConfigure;
    /// RequestID序列器
    int RequestID;
    /// 启动CTP连接
    void init();
    /// 获取下一个RequestID序列
    int getNextRequestID();
    /// 获取当前RequestID序列
    int getCurrentRequestID();

};