
#include <stdio.h>


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
