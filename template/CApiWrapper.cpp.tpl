
#include <CApiWrapper.h>
#include <stdio.h>
#include <string.h>


/// 构造函数
CApiWrapper::CApiWrapper(Configure * pConfigure){

	// 读取配置数据信息
	this->pConfigure = pConfigure;

	// 创建CTP API工作对象
	this->pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();

	// 创建SPI工作对象并让其和API关联
	this->pTraderHandler = new CTraderHandler();
	pTraderApi->RegisterSpi(pTraderHandler);

	// 初始化RequestID序列
	this->RequestID = 0;
}

/// 启动CTP连接
void CApiWrapper::init(){

	//Configure * pConfigure = this->pConfigure;
	//设置服务信息推送信息
	// 订阅相关信息推送
	//// THOST_TERT_RESTART:从本交易日开始重传
	//// THOST_TERT_RESUME:从上次收到的续传
	//// THOST_TERT_QUICK:只传送登录后私有流的内容
	pTraderApi->SubscribePrivateTopic(THOST_TERT_RESUME);
	// 订阅公共流
	//// THOST_TERT_RESTART:从本交易日开始重传
	//// THOST_TERT_RESUME:从上次收到的续传
	//// THOST_TERT_QUICK:只传送登录后公共流的内容
	pTraderApi->SubscribePublicTopic(THOST_TERT_RESUME);

	/// 设置服务器地址
	pTraderApi->RegisterFront(pConfigure->FrontAddress);

	// 连接交易系统
	pTraderApi->Init();
	// TODO : 这里需要等待工作线程收到OnFrontConnected回调
	// ... ...

	// 发出登陆请求
	CThostFtdcReqUserLoginField userLoginField;
	strcpy(userLoginField.BrokerID,pConfigure->BrokerID);
	strcpy(userLoginField.UserID,pConfigure->UserID);
	strcpy(userLoginField.Password,pConfigure->Password);
	pTraderApi->ReqUserLogin(&userLoginField,getNextRequestID());
	// TODO : 这里需要等待登录成功返回信息
	// ... ...

}


/// 获取下一个RequestID序列
int CApiWrapper::getNextRequestID(){
	return 	++this->RequestID;
}

/// 获取当前RequestID序列
int CApiWrapper::getCurrentRequestID(){
	return 	this->RequestID;
}

/*

// 允许登录事件
virtual void OnFrontConnected() {
    static int i = 0;
    printf("OnFrontConnected():被执行...\n");
    // 在登出后系统会重新调用OnFrontConnected，这里简单判断并忽略第1次之后的所有调用。
    if (i++==0) {
        sem_post(&sem);
    }
}

// 登录结果响应
virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    printf("OnRspUserLogin():被执行...\n");
    if (pRspInfo->ErrorID == 0) {
        printf("登录成功!\n");
        sem_post(&sem);
    } else {
        printf("登录失败!\n");
    }
}
*/



/*
1、重载CTraderHander(实现登录操作部分，或者直接在CTraderHander实现)
2、创建TraderApi实例
3、登录ReqUserLogin（管理CTP_FrontAddress，CTP_BrokerId，CTP_UserId，CTP_Password）
4、

// 创建TraderAPI和回调响应控制器的实例
CThostFtdcTraderApi *pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
CTraderHandler traderHandler = CTraderHandler();
CTraderHandler * pTraderHandler = &traderHandler;
pTraderApi->RegisterSpi(pTraderHandler);

// 订阅相关信息推送
//// THOST_TERT_RESTART:从本交易日开始重传
//// THOST_TERT_RESUME:从上次收到的续传
//// THOST_TERT_QUICK:只传送登录后私有流的内容
pTraderApi->SubscribePrivateTopic(THOST_TERT_RESUME);
// 订阅公共流
//// THOST_TERT_RESTART:从本交易日开始重传
//// THOST_TERT_RESUME:从上次收到的续传
//// THOST_TERT_QUICK:只传送登录后公共流的内容
pTraderApi->SubscribePublicTopic(THOST_TERT_RESUME);

// 设置服务器地址
pTraderApi->RegisterFront(CTP_FrontAddress);
// 链接交易系统
pTraderApi->Init();
// 等待服务器发出登录消息
sem_wait(&sem);
// 发出登陆请求
pTraderApi->ReqUserLogin(&userLoginField, requestID++);
// 等待登录成功消息
sem_wait(&sem);


CThostFtdcInputOrderField requestData;
// 确保没有初始化的数据不会被访问
memset(&requestData,0,sizeof(requestData));
....

// 调用API,并等待响应函数返回
int result = pTraderApi->ReqOrderInsert(&requestData,requestID++);
sem_wait(&sem);






{% for method in reqMethodDict.itervalues() %}
	{{ method['remark'] }}
	{{method['returns']}} {{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
){
	printf("{{method['name']}}():被执行...\n");
}
{% endfor %}

*/
