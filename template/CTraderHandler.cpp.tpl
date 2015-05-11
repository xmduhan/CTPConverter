#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>


/// 构造函数
CTraderHandler::CTraderHandler(Configure * pConfigure) {
	printf("CTraderHandler():被执行...\n");
	// 读取配置数据信息
	this->pConfigure = pConfigure;
	// 创建zmq通讯环境
	pContext = new zmq::context_t(1);
	pSender = new zmq::socket_t(*pContext, ZMQ_PUSH);
	pSender->bind(pConfigure->PushbackPipe);
}

/// 成功连接服务器消息
void CTraderHandler::OnFrontConnected() {
    printf("OnFrontConnected():被执行...\n");
	zmq::socket_t & sendder = *pSender;
	PushbackMessage message;
	message.requestID = "0";
	message.apiName = "OnFrontConnected";
	message.respInfo = "";
	message.send(sendder);
}

char buffer[1024];

/**********************************************************
*                   onRsp开头的方法                         *
***********************************************************/

{% for method in onRspMethodDict.itervalues() %}
	{{ method['remark'] }}
	{{method['returns']}} CTraderHandler::{{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
){
	printf("{{method['name']}}():被执行...\n");
	zmq::socket_t & sendder = *pSender;
	PushbackMessage message;
	sprintf(buffer,"%d",nRequestID);
	message.requestID = buffer;
	message.apiName = "{{method['name']}}";
	message.respInfo = "";
	message.send(sendder);
}
{% endfor %}

/**********************************************************
*                   onRtn开头的方法                         *
***********************************************************/


{% for method in onRtnMethodDict.itervalues() %}
	{{ method['remark'] }}
	{{method['returns']}} CTraderHandler::{{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
){
	printf("{{method['name']}}():被执行...\n");
}
{% endfor %}

/**********************************************************
*                   onErrRtn开头的方法                      *
***********************************************************/

{% for method in onErrRtnMethodDict.itervalues() %}
	{{ method['remark'] }}
	{{method['returns']}} CTraderHandler::{{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
){
	printf("{{method['name']}}():被执行...\n");
}
{% endfor %}


/**********************************************************
*                     onRspError方法                       *
***********************************************************/
{% for method in onRspErrorMethodDict.itervalues() %}
	{{ method['remark'] }}
	{{method['returns']}} CTraderHandler::{{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
){
	printf("{{method['name']}}():被执行...\n");
}
{% endfor %}
