#include <CMdHandler.h>


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CMdHandler::OnFrontConnected() {
    std::cout << "OnFrontConnected():开始执行..." << std::endl;

    std::cout << "OnFrontConnected():执行结束..." << std::endl;
}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理
void CMdHandler::OnFrontDisconnected(int nReason) {
    std::cout << "OnFrontDisconnected():开始执行..." << std::endl;

    std::cout << "OnFrontDisconnected():开始执行..." << std::endl;
}

///心跳超时警告。当长时间未收到报文时，该方法被调用
void CMdHandler::OnHeartBeatWarning(int nTimeLapse) {
    std::cout << "OnHeartBeatWarning():开始执行..." << std::endl;

    std::cout << "OnHeartBeatWarning():开始执行..." << std::endl;
}

///深度行情通知
void CMdHandler::OnRtnDepthMarketData(
    CThostFtdcDepthMarketDataField *pDepthMarketData
) {
    std::cout << "OnRtnDepthMarketData():开始执行..." << std::endl;

    std::cout << "OnRtnDepthMarketData():开始执行..." << std::endl;
}