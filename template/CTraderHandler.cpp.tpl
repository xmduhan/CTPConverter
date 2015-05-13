#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>
#include <json/json.h>


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
	// 生成发送管道的引用
	zmq::socket_t & sendder = *pSender;

	// 生成返回的json格式
	Json::Value json_Response;
	json_Response["ResponseMethod"] = "{{method['name']}}";

	/// 返回数据结构体转化json格式
	{%- set dataVarName = method['parameters'][0]['name'] %}
	{%- set dataTypeName = method['parameters'][0]['raw_type'] %}
	{%- set dataType = structDict[dataTypeName] %}
	Json::Value json_{{dataVarName}};
	{% for field in dataType['fields'] %}
		json_{{dataVarName}}["{{field['name']}}"] = {{dataVarName}}->{{field['name']}};
	{%- endfor %}

	/// 出错信息
	Json::Value json_pRspInfo;
	json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
	json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;

	/// json_nRequestID
	Json::Value json_nRequestID;
	json_nRequestID = nRequestID;

	/// 数据末尾标识
	Json::Value json_bIsLast;
	json_bIsLast = bIsLast;

	// 定义参数集合
	// TODO:参数集是用dict还是是用list需要在考虑一下
	Json::Value json_Parameters;
	json_Parameters["Data"] = json_{{dataVarName}};
	json_Parameters["RspInfo"] = json_pRspInfo;
	json_Parameters["RequestID"] = json_nRequestID;
	json_Parameters["IsLast"] = json_bIsLast;
	json_Response["Parameters"] = json_Parameters;

	// 打包消息结构并压入Pushback管道
	PushbackMessage message;
	sprintf(buffer,"%d",nRequestID);
	message.requestID = buffer;
	message.apiName = "{{method['name']}}";
	message.respInfo = json_Response.toStyledString();
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
