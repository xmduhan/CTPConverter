#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>
#include <json/json.h>
#include <comhelper.h>


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
	zmq::socket_t & sender = *pSender;
	PushbackMessage message;
	message.requestID = "0";
	message.apiName = "OnFrontConnected";
	message.respInfo = "";
	message.send(sender);
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

	std::cout << "{{method['name']}}():被执行..." << std::endl;

	// 生成发送管道的引用
	zmq::socket_t & sender = *pSender;
	// 读取处理结果信息
	Json::Value json_pRspInfo;
	// 如果RspInfo为空，或者RspInfo的错误代码为0，说明查询成功。
	// 这里不需要判断是否成功直接将信息返回客户端即可
    if ( pRspInfo != NULL )  {
		json_pRspInfo["ErrorID"] = pRspInfo->ErrorID;
		json_pRspInfo["ErrorMsg"] = pRspInfo->ErrorMsg;
    }else{
		json_pRspInfo["ErrorID"] = 0;
		json_pRspInfo["ErrorMsg"] = "";
	}

	// 生成返回的json格式
	Json::Value json_Response;
	json_Response["ResponseMethod"] = "{{method['name']}}";

	/// 返回数据结构体转化json格式
	{%- set dataVarName = method['parameters'][0]['name'] %}
	{%- set dataTypeName = method['parameters'][0]['raw_type'] %}
	{%- set dataType = structDict[dataTypeName] %}
	Json::Value json_{{dataVarName}};
	if ( {{dataVarName}} != NULL ) {
		// TODO : 这里需要将编码转化为utf-8
		{% for field in dataType['fields'] %}
			json_{{dataVarName}}["{{field['name']}}"] = {{dataVarName}}->{{field['name']}};
		{%- endfor %}
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
	message.send(sender);

	std::cout << "{{method['name']}}():执行结束..." << std::endl;
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
