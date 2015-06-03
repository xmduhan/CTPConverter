#include <CMdHandler.h>

static char buffer[1024*10];


/// 构造函数
CMdHandler::CMdHandler(MdConfigure * pConfigure) {

    std::cout << "CMdHandler():开始执行..." << std::endl;

    // 读取配置数据信息
    this->pConfigure = pConfigure;
    // 创建zmq通讯环境
    pContext = new zmq::context_t(1);
    pSender = new zmq::socket_t(*pContext, ZMQ_PUSH);
    pSender->bind(pConfigure->pushbackPipe);

    std::cout << "CMdHandler():执行结束..." << std::endl;
}



///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CMdHandler::OnFrontConnected() {
    std::cout << "OnFrontConnected():开始执行..." << std::endl;

    zmq::socket_t & sender = *pSender;
    PushbackMessage message;
    message.requestID = "0";
    message.apiName = "OnFrontConnected";
    message.respInfo = "";
    message.send(sender);

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
    /// TODO
    std::cout << "OnRtnDepthMarketData():开始执行..." << std::endl;
}


/**********************************************************
*                   onRsp开头的方法                         *
***********************************************************/

///登录请求响应
void CMdHandler::OnRspUserLogin(
    CThostFtdcRspUserLoginField * pRspUserLogin,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspUserLogin():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserLogin";

    /// 返回数据结构体转化json格式
    Json::Value json_pRspUserLogin;
    if ( pRspUserLogin != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pRspUserLogin->TradingDay,
            buffer,
            sizeof(pRspUserLogin->TradingDay) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["TradingDay"] = buffer;


        gbk2utf8(
            pRspUserLogin->LoginTime,
            buffer,
            sizeof(pRspUserLogin->LoginTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["LoginTime"] = buffer;


        gbk2utf8(
            pRspUserLogin->BrokerID,
            buffer,
            sizeof(pRspUserLogin->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["BrokerID"] = buffer;


        gbk2utf8(
            pRspUserLogin->UserID,
            buffer,
            sizeof(pRspUserLogin->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["UserID"] = buffer;


        gbk2utf8(
            pRspUserLogin->SystemName,
            buffer,
            sizeof(pRspUserLogin->SystemName) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["SystemName"] = buffer;


        json_pRspUserLogin["FrontID"] = pRspUserLogin->FrontID;


        json_pRspUserLogin["SessionID"] = pRspUserLogin->SessionID;


        gbk2utf8(
            pRspUserLogin->MaxOrderRef,
            buffer,
            sizeof(pRspUserLogin->MaxOrderRef) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["MaxOrderRef"] = buffer;


        gbk2utf8(
            pRspUserLogin->SHFETime,
            buffer,
            sizeof(pRspUserLogin->SHFETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["SHFETime"] = buffer;


        gbk2utf8(
            pRspUserLogin->DCETime,
            buffer,
            sizeof(pRspUserLogin->DCETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["DCETime"] = buffer;


        gbk2utf8(
            pRspUserLogin->CZCETime,
            buffer,
            sizeof(pRspUserLogin->CZCETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["CZCETime"] = buffer;


        gbk2utf8(
            pRspUserLogin->FFEXTime,
            buffer,
            sizeof(pRspUserLogin->FFEXTime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["FFEXTime"] = buffer;


        gbk2utf8(
            pRspUserLogin->INETime,
            buffer,
            sizeof(pRspUserLogin->INETime) * 3 // 字符串转化变长的风险保障
        );
        json_pRspUserLogin["INETime"] = buffer;

    }

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pRspUserLogin;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserLogin";
    message.respInfo = json_Response.toStyledString();
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspUserLogin():执行结束..." << std::endl;
}

///订阅行情应答
void CMdHandler::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField * pSpecificInstrument,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspSubMarketData():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspSubMarketData";

    /// 返回数据结构体转化json格式
    Json::Value json_pSpecificInstrument;
    if ( pSpecificInstrument != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pSpecificInstrument->InstrumentID,
            buffer,
            sizeof(pSpecificInstrument->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pSpecificInstrument["InstrumentID"] = buffer;

    }

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pSpecificInstrument;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspSubMarketData";
    message.respInfo = json_Response.toStyledString();
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspSubMarketData():执行结束..." << std::endl;
}

///取消订阅行情应答
void CMdHandler::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField * pSpecificInstrument,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspUnSubMarketData():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUnSubMarketData";

    /// 返回数据结构体转化json格式
    Json::Value json_pSpecificInstrument;
    if ( pSpecificInstrument != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pSpecificInstrument->InstrumentID,
            buffer,
            sizeof(pSpecificInstrument->InstrumentID) * 3 // 字符串转化变长的风险保障
        );
        json_pSpecificInstrument["InstrumentID"] = buffer;

    }

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pSpecificInstrument;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUnSubMarketData";
    message.respInfo = json_Response.toStyledString();
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspUnSubMarketData():执行结束..." << std::endl;
}

///登出请求响应
void CMdHandler::OnRspUserLogout(
    CThostFtdcUserLogoutField * pUserLogout,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
) {

    std::cout << "OnRspUserLogout():开始执行..." << std::endl;

    // 生成发送管道的引用
    zmq::socket_t & sender = *pSender;
    // 读取处理结果信息
    Json::Value json_pRspInfo;
    // 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
    // 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
        json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
        gbk2utf8(
            pRspInfo->ErrorMsg,
            buffer,
            sizeof(pRspInfo->ErrorMsg) * 3 // 字符串转化变长的风险保障
        );
        json_pRspInfo["ErrorMsg"] = buffer;
    } else {
        json_pRspInfo["ErrorID"] = 0;
        json_pRspInfo["ErrorMsg"] = "";
    }

    // 生成返回的json格式
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "OnRspUserLogout";

    /// 返回数据结构体转化json格式
    Json::Value json_pUserLogout;
    if ( pUserLogout != NULL ) {
        // TODO : 这里需要将编码转化为utf-8


        gbk2utf8(
            pUserLogout->BrokerID,
            buffer,
            sizeof(pUserLogout->BrokerID) * 3 // 字符串转化变长的风险保障
        );
        json_pUserLogout["BrokerID"] = buffer;


        gbk2utf8(
            pUserLogout->UserID,
            buffer,
            sizeof(pUserLogout->UserID) * 3 // 字符串转化变长的风险保障
        );
        json_pUserLogout["UserID"] = buffer;

    }

    /// json_nRequestID
    Json::Value json_nRequestID;
    json_nRequestID = nRequestID;

    /// 数据末尾标识
    Json::Value json_bIsLast;
    json_bIsLast = bIsLast;

    // 定义参数集合
    // TODO:参数集是用dict还是是用list需要在考虑一下
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_pUserLogout;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    // 打包消息结构并压入Pushback管道
    PushbackMessage message;
    sprintf(buffer,"%d",nRequestID);
    message.requestID = buffer;
    message.apiName = "OnRspUserLogout";
    message.respInfo = json_Response.toStyledString();
    message.isLast = bIsLast ? "1" : "0";
    message.send(sender);

    std::cout << "OnRspUserLogout():执行结束..." << std::endl;
}
