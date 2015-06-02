#include <CMDHandler.h>


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CMDHandler::OnFrontConnected(){
    std::cout << "OnFrontConnected():开始执行..." << std::endl;

    std::cout << "OnFrontConnected():执行结束..." << std::endl;
}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理
void CMDHandler::OnFrontDisconnected(int nReason){
    std::cout << "OnFrontDisconnected():开始执行..." << std::endl;

    std::cout << "OnFrontDisconnected():开始执行..." << std::endl;
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
void CMDHandler::OnHeartBeatWarning(int nTimeLapse){
    std::cout << "OnHeartBeatWarning():开始执行..." << std::endl;

    std::cout << "OnHeartBeatWarning():开始执行..." << std::endl;
}

///登录请求响应
void CMDHandler::OnRspUserLogin(
    CThostFtdcRspUserLoginField *pRspUserLogin,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast
){
    std::cout << "OnRspUserLogin():开始执行..." << std::endl;

    std::cout << "OnRspUserLogin():开始执行..." << std::endl;
}

///登出请求响应
void CMDHandler::OnRspUserLogout(
    CThostFtdcUserLogoutField *pUserLogout,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast
){
    std::cout << "OnRspUserLogout():开始执行..." << std::endl;

    std::cout << "OnRspUserLogout():开始执行..." << std::endl;
}

///错误应答
void CMDHandler::OnRspError(
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast
){
    std::cout << "OnRspError():开始执行..." << std::endl;

    std::cout << "OnRspError():开始执行..." << std::endl;
}

///订阅行情应答
void CMDHandler::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast
){
    std::cout << "OnRspSubMarketData():开始执行..." << std::endl;

    std::cout << "OnRspSubMarketData():开始执行..." << std::endl;
}

///取消订阅行情应答
void CMDHandler::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast
){
    std::cout << "OnRspUnSubMarketData():开始执行..." << std::endl;

    std::cout << "OnRspUnSubMarketData():开始执行..." << std::endl;
}

///深度行情通知
void CMDHandler::OnRtnDepthMarketData(
    CThostFtdcDepthMarketDataField *pDepthMarketData
){
    std::cout << "OnRtnDepthMarketData():开始执行..." << std::endl;

    std::cout << "OnRtnDepthMarketData():开始执行..." << std::endl;
}
