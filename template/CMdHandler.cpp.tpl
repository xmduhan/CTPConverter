#include <CMdHandler.h>

static char buffer[1024*10];


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CMdHandler::OnFrontConnected(){
    std::cout << "OnFrontConnected():开始执行..." << std::endl;

    std::cout << "OnFrontConnected():执行结束..." << std::endl;
}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理
void CMdHandler::OnFrontDisconnected(int nReason){
    std::cout << "OnFrontDisconnected():开始执行..." << std::endl;

    std::cout << "OnFrontDisconnected():开始执行..." << std::endl;
}

///心跳超时警告。当长时间未收到报文时，该方法被调用
void CMdHandler::OnHeartBeatWarning(int nTimeLapse){
    std::cout << "OnHeartBeatWarning():开始执行..." << std::endl;

    std::cout << "OnHeartBeatWarning():开始执行..." << std::endl;
}

///深度行情通知
void CMdHandler::OnRtnDepthMarketData(
    CThostFtdcDepthMarketDataField *pDepthMarketData
){
    std::cout << "OnRtnDepthMarketData():开始执行..." << std::endl;

    std::cout << "OnRtnDepthMarketData():开始执行..." << std::endl;
}



/**********************************************************
*                   onRsp开头的方法                         *
***********************************************************/
{% for method in mdOnRspMethodDict.itervalues() %}
	{{ method['remark'] }}
	{{method['returns']}} CMdHandler::{{method['name']}}(
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
			{% if typeInfo['type'] == 'char' and typeInfo['len'] != None %}
				gbk2utf8(
					{{dataVarName}}->{{field['name']}},
					buffer,
					sizeof({{dataVarName}}->{{field['name']}}) * 3 // 字符串转化变长的风险保障
				);
				json_{{dataVarName}}["{{field['name']}}"] = buffer;
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
