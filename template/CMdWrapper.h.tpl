#pragma once
#include <ThostFtdcMdApi.h>
#include <ThostFtdcUserApiStruct.h>
#include <ThostFtdcUserApiDataType.h>
#include <Configure.h>
#include <CMdHandler.h>
#include <zmq.hpp>
#include <Message.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <map>

class CMdWrapper {

public:
    /// 构造函数
    CMdWrapper(MdConfigure * pConfigure);
    /////////////////  变量定义 //////////////////
    /// 对应的API实例
    CThostFtdcMdApi * pMdApi;
    /// 对应的SPI实例
    CMdHandler * pMdHandler;
    /// 配置信息
    MdConfigure * pConfigure;
    /// RequestID序列器
    int RequestID;
    /// 上次出错代码
    int lastErrorID;
    /// 上次出错信息
    std::string lastErrorMsg;

    /// 获取下一个RequestID序列
    int getNextRequestID();
    /// 获取当前RequestID序列
    int getCurrentRequestID();
    /// 获取上次出错代码
    int getLastErrorID();
    /// 获取上次错误信息
    std::string getLastErrorMsg();
    /// 初始化函数跳转表
    void initApiMap();
    /// 启动CTP连接
    void init();
    ///订阅行情
    virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount);
    ///退订行情
    virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

    ////////////// API方法的wrapper ///////////////
    {% for method in mdReqMethodDict.itervalues() %}
    	{{ method['remark'] }}
    	int {{method['name']}}(std::string jsonString);
    {% endfor %}



    std::map<std::string,int (CMdWrapper::*) (std::string)> apiMap;

    int callApiByName(std::string apiName,std::string jsonString);

};
