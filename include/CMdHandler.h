#include <ThostFtdcMdApi.h>
#include <iostream>
#include <json/json.h>
#include <Message.h>
#include <comhelper.h>
#include <Configure.h>

class CMdHandler : public CThostFtdcMdSpi {
public:


    /// 配置信息
    MdConfigure * pConfigure;
    /// zmq通讯环境
    zmq::context_t * pContext;
    /// 通讯套接字
    zmq::socket_t * pSender;

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    virtual void OnFrontConnected();

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理
    virtual void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    virtual void OnHeartBeatWarning(int nTimeLapse);

    ///深度行情通知
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);



    ///登录请求响应
    virtual void OnRspUserLogin(
        CThostFtdcRspUserLoginField * pRspUserLogin,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///订阅行情应答
    virtual void OnRspSubMarketData(
        CThostFtdcSpecificInstrumentField * pSpecificInstrument,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///取消订阅行情应答
    virtual void OnRspUnSubMarketData(
        CThostFtdcSpecificInstrumentField * pSpecificInstrument,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );

    ///登出请求响应
    virtual void OnRspUserLogout(
        CThostFtdcUserLogoutField * pUserLogout,
        CThostFtdcRspInfoField * pRspInfo,
        int nRequestID,
        bool bIsLast
    );


};