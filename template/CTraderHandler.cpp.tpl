#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>
#include <json/json.h>
#include <comhelper.h>


/// 构造函数
CTraderHandler::CTraderHandler(Configure * pConfigure) {

	std::cout << "CTraderHandler():开始执行..." << std::endl;

	// 读取配置数据信息
	this->pConfigure = pConfigure;
	// 创建zmq通讯环境
	pContext = new zmq::context_t(1);
	pSender = new zmq::socket_t(*pContext, ZMQ_PUSH);
	pSender->bind(pConfigure->pushbackPipe);

	std::cout << "CTraderHandler():执行结束..." << std::endl;
}

/// 成功连接服务器消息
void CTraderHandler::OnFrontConnected() {

	std::cout << "OnFrontConnected():开始执行..." << std::endl;

	zmq::socket_t & sender = *pSender;
	PushbackMessage message;
	message.requestID = "0";
	message.apiName = "OnFrontConnected";
	message.respInfo = "";
	message.send(sender);

	std::cout << "OnFrontConnected():执行结束..." << std::endl;
}


// 字符操作使用的临时缓冲区,由于ctp最长的字符串变量长度2049,并且需要字符串编码的转换,
// 定义3倍长度来保证不会超出
static char buffer[1024*10];

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

	std::cout << "{{method['name']}}():开始执行..." << std::endl;

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
			{%- set typeInfo = typedefDict[field['type']] %}
			{% if typeInfo['type'] == 'char' %}
				{% if typeInfo['len'] != None %}
					gbk2utf8(
						{{dataVarName}}->{{field['name']}},
						buffer,
						sizeof({{dataVarName}}->{{field['name']}}) * 3 // 字符串转化变长的风险保障
					);
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% else %}
					sprintf(buffer,"%c",{{dataVarName}}->{{field['name']}});
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% endif %}
			{% else %}
				json_{{dataVarName}}["{{field['name']}}"] = {{dataVarName}}->{{field['name']}};
			{% endif %}
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
	message.isLast = bIsLast ? "1" : "0";
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
	int nRequestID = 0;
    std::cout << "{{method['name']}}():开始执行..." << std::endl;

	// 生成发送管道的引用
	zmq::socket_t & sender = *pSender;

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
			{%- set typeInfo = typedefDict[field['type']] %}
			{% if typeInfo['type'] == 'char' %}
				{% if typeInfo['len'] != None %}
					gbk2utf8(
						{{dataVarName}}->{{field['name']}},
						buffer,
						sizeof({{dataVarName}}->{{field['name']}}) * 3 // 字符串转化变长的风险保障
					);
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% else %}
					sprintf(buffer,"%c",{{dataVarName}}->{{field['name']}});
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% endif %}
			{% else %}
				json_{{dataVarName}}["{{field['name']}}"] = {{dataVarName}}->{{field['name']}};
			{% endif %}
		{%- endfor %}
	}

	// 定义参数集合
	Json::Value json_Parameters;
	json_Parameters["Data"] = json_{{dataVarName}};
	json_Response["Parameters"] = json_Parameters;

	// 打包消息结构并压入Pushback管道
	PushbackMessage message;
	sprintf(buffer,"%d",nRequestID);
	message.requestID = buffer;
	message.apiName = "{{method['name']}}";
	message.respInfo = json_Response.toStyledString();
	message.isLast = "0";
	message.send(sender);

	std::cout << "{{method['name']}}():执行结束..." << std::endl;
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
    int nRequestID = 0;
	std::cout << "{{method['name']}}():开始执行..." << std::endl;

	// 生成发送管道的引用
	zmq::socket_t & sender = *pSender;

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
			{%- set typeInfo = typedefDict[field['type']] %}
			{% if typeInfo['type'] == 'char' %}
				{% if typeInfo['len'] != None %}
					gbk2utf8(
						{{dataVarName}}->{{field['name']}},
						buffer,
						sizeof({{dataVarName}}->{{field['name']}}) * 3 // 字符串转化变长的风险保障
					);
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% else %}
					sprintf(buffer,"%c",{{dataVarName}}->{{field['name']}});
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% endif %}
			{% else %}
				json_{{dataVarName}}["{{field['name']}}"] = {{dataVarName}}->{{field['name']}};
			{% endif %}
		{%- endfor %}
	}

	// 定义参数集合
	Json::Value json_Parameters;
	json_Parameters["Data"] = json_{{dataVarName}};
	json_Response["Parameters"] = json_Parameters;

	// 打包消息结构并压入Pushback管道
	PushbackMessage message;
	sprintf(buffer,"%d",nRequestID);
	message.requestID = buffer;
	message.apiName = "{{method['name']}}";
	message.respInfo = json_Response.toStyledString();
	message.isLast = "0";
	message.send(sender);

	std::cout << "{{method['name']}}():执行结束..." << std::endl;
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
	std::cout << "{{method['name']}}():开始执行..." << std::endl;

	// 生成发送管道的引用
	zmq::socket_t & sender = *pSender;

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
			{%- set typeInfo = typedefDict[field['type']] %}
			{% if typeInfo['type'] == 'char' %}
				{% if typeInfo['len'] != None %}
					gbk2utf8(
						{{dataVarName}}->{{field['name']}},
						buffer,
						sizeof({{dataVarName}}->{{field['name']}}) * 3 // 字符串转化变长的风险保障
					);
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% else %}
					sprintf(buffer,"%c",{{dataVarName}}->{{field['name']}});
					json_{{dataVarName}}["{{field['name']}}"] = buffer;
				{% endif %}
			{% else %}
				json_{{dataVarName}}["{{field['name']}}"] = {{dataVarName}}->{{field['name']}};
			{% endif %}
		{%- endfor %}
	}

	// 定义参数集合
	Json::Value json_Parameters;
	json_Parameters["Data"] = json_{{dataVarName}};
	json_Response["Parameters"] = json_Parameters;

	// 打包消息结构并压入Pushback管道
	PushbackMessage message;
	message.requestID = "0";
	message.apiName = "{{method['name']}}";
	message.respInfo = json_Response.toStyledString();
	message.isLast = "0";
	message.send(sender);


	std::cout << "{{method['name']}}():执行结束..." << std::endl;
}
{% endfor %}
