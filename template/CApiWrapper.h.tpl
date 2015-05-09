#pragma once

#include <ThostFtdcTraderApi.h>
#include <ThostFtdcUserApiStruct.h>
#include <ThostFtdcUserApiDataType.h>
#include <Configure.h>
#include <CTraderHandler.h>
#include <zmq.hpp>


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
    /////////////// zmq通讯环境相关  ///////////////
    // 这里的zmq通信只是需要在连接服务器和登录时用来和spi做同步,主要是以下工作:
    // 1. 连接服务器后需要等待服务器响应才能发出登录请求
    // 2. 发出登录请求后需要等待服务器返回登录结果
    /// zmq通讯环境
    zmq::context_t * pContext;
    /// 通讯套接字
    zmq::socket_t * pReceiver;
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

    ////////////// API方法的wrapper ///////////////
    {% for method in reqMethodDict.itervalues() %}
    	{{ method['remark'] }}
    	int {{method['name']}}(char * pJsonData );
    {% endfor %}

};
