
#include <CApiWrapper.h>
#include <stdio.h>
#include <string.h>


/// 构造函数
CApiWrapper::CApiWrapper(Configure * pConfigure){

	// 读取配置数据信息
	this->pConfigure = pConfigure;

	// 创建CTP API工作对象
	pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();

	// 创建SPI工作对象并让其和API关联
	pTraderHandler = new CTraderHandler();
	pTraderApi->RegisterSpi(pTraderHandler);

	// 初始化RequestID序列
	RequestID = 0;

	// 初始化上次出错代码和出错信息
	lastErrorCode = 0;
	strcpy(lastErrorMessage,"");
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
	// TODO : 这里需要等待登录成功返回信息(OnRspUserLogin)
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

/// 获取上次出错代码
int CApiWrapper::getLastErrorCode(){
	return lastErrorCode;
}

/// 获取上次错误信息
char * CApiWrapper::getLastErrorMessage(){
	return lastErrorMessage;
}


/* TODO:这里两个函数要实现到CTraderHandler中去

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


{% for method in reqMethodDict.itervalues() %}
	{{ method['remark'] }}
	int CApiWrapper::{{method['name']}}(char * pJsonData )
{
	printf("{{method['name']}}():被执行...\n");
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}};
	{%- endfor %}

	// 获取RequestID
	nRequestID = getNextRequestID();

	// TODO:这里将pJsonData转化为对应的结构参数

	// 调用对应的CTP API函数
	{{method['returns']}} result =
	pTraderApi->{{method['name']}}(
		{% for parameter in method['parameters'] -%}
		    {{-parameter['name'] -}}
			{%- if not loop.last %},
			{% endif -%}
		{%- endfor %}
	);

	// TODO:检查API调用是否失败

	return 0;
}
{% endfor %}
