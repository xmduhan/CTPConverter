#include <comhelper.h>
#include <string>
#include <iostream>
#include <json/json.h>


int main(int argc, char * argv []){

    int errorID = -1;
    std::string errorMsg = "测试错误";

    // 打包json格式
    Json::Value json_pRspInfo;
    json_pRspInfo["ErrorID"] = errorID;
    json_pRspInfo["ErrorMsg"] = errorMsg;
    Json::Value json_bIsLast = false;
    Json::Value json_nRequestID = "1";
    Json::Value json_Response;
    json_Response["ResponseMethod"] = "apiName";
    Json::Value json_Data;
    Json::Value json_Parameters;
    json_Parameters["Data"] = json_Data;
    json_Parameters["RspInfo"] = json_pRspInfo;
    json_Parameters["RequestID"] = json_nRequestID;
    json_Parameters["IsLast"] = json_bIsLast;
    json_Response["Parameters"] = json_Parameters;

    std::cout << json_Response.toStyledString() << std::endl;
}
