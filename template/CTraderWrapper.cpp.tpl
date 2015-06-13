
#include <CTraderWrapper.h>
#include <json/json.h>
#include <comhelper.h>



/// 构造函数
CTraderWrapper::CTraderWrapper(Configure * pConfigure){

	// 读取配置数据信息
	this->pConfigure = pConfigure;

	// 创建CTP API工作对象
	pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();

	// 创建SPI工作对象并让其和API关联
	pTraderHandler = new CTraderHandler(pConfigure);
	pTraderApi->RegisterSpi(pTraderHandler);

	// 初始化RequestID序列
	//RequestID = 0;

	// 初始化上次出错代码和出错信息
	lastErrorID = 0;
	lastErrorMsg = "";

}

// 将所有api函数映射到名称
void CTraderWrapper::initApiMap(){
	{% for method in reqMethodDict.itervalues() %}
		//{{method['name']}}
		apiMap["{{method['name']}}"] = &CTraderWrapper::{{method['name']}};
	{% endfor %}
}

/// 启动CTP连接
void CTraderWrapper::init(){

	std::cout << "CTraderWrapper::init():开始执行..." << std::endl;
	// 初始化api名称对照表
	initApiMap();

	// 创建zmq通讯环境
	zmq::context_t context(1);
	zmq::socket_t receiver(context, ZMQ_PULL);
	PushbackMessage message;

	//设置服务信息推送信息
	// 订阅相关信息推送
	//// THOST_TERT_RESTART:从本交易日开始重传
	//// THOST_TERT_RESUME:从上次收到的续传
	//// THOST_TERT_QUICK:只传送登录后私有流的内容
	pTraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	// 订阅公共流
	//// THOST_TERT_RESTART:从本交易日开始重传
	//// THOST_TERT_RESUME:从上次收到的续传
	//// THOST_TERT_QUICK:只传送登录后公共流的内容
	pTraderApi->SubscribePublicTopic(THOST_TERT_QUICK);

	/// 设置服务器地址
	pTraderApi->RegisterFront(pConfigure->frontAddress);

	// 连接spi的Pushback管道
	std::cout << "CTraderWrapper::init():Pushback管道地址为:" << pConfigure->pushbackPipe << std::endl;
	receiver.connect(pConfigure->pushbackPipe);

	// 连接交易系统
	std::cout << "CTraderWrapper::init():尝试连接服务器..." << std::endl;
	pTraderApi->Init();

	// 等待服务器发出OnFrontConnected事件
	std::cout << "CTraderWrapper::init():等待服务器响应消息..." << std::endl;
	message.recv(receiver);
	std::cout << "CTraderWrapper::init():已收到服务器响应消息..." << std::endl;

	// 确认收到的返回信息是由OnFrontConnected发出
	assert(message.requestID.compare("0") == 0);
	assert(message.apiName.compare("OnFrontConnected") == 0);
	assert(message.respInfo.compare("") == 0);

	// 发出登陆请求
	std::cout << "CTraderWrapper::init():发出登录请求..." << std::endl;
	CThostFtdcReqUserLoginField userLoginField;
	strcpy(userLoginField.BrokerID,pConfigure->brokerID);
	strcpy(userLoginField.UserID,pConfigure->userID);
	strcpy(userLoginField.Password,pConfigure->password);
	int requestID = 0;
	pTraderApi->ReqUserLogin(&userLoginField,requestID);

	// 等待登录成功返回信息
	std::cout << "CTraderWrapper::init():等待登录结果..." << std::endl;
	message.recv(receiver);
	std::cout << "CTraderWrapper::init():已收到登录返回信息..." << std::endl;

	assert(message.requestID.compare("0") == 0);
	assert(message.apiName.compare("OnRspUserLogin") == 0);
	//assert(message.respInfo.compare("") == 0);
	//std::cout << "message.respInfo=" << message.respInfo << std::endl;
	// 检查是否登录成功,如果不成功将终止程序
	Json::Reader jsonReader;
	Json::Value jsonData;
	if (!jsonReader.parse(message.respInfo,jsonData)){
		throw std::exception();
	}
	int ErrorID = jsonData["Parameters"]["Data"]["RspInfo"]["ErrorID"].asInt();
	assert(ErrorID == 0);

	std::cout << "CTraderWrapper::init():登录成功..." << std::endl;

	std::cout << "CTraderWrapper::init():执行完毕..." << std::endl;
}


/// 获取下一个RequestID序列
//int CTraderWrapper::getNextRequestID(){
//	return 	++this->RequestID;
//}

/// 获取当前RequestID序列
//int CTraderWrapper::getCurrentRequestID(){
//	return 	this->RequestID;
//}

/// 获取上次出错代码
int CTraderWrapper::getLastErrorID(){
	return lastErrorID;
}

/// 获取上次错误信息
std::string CTraderWrapper::getLastErrorMsg(){
	return lastErrorMsg;
}


{% for method in reqMethodDict.itervalues() %}
	{{ method['remark'] }}
	/// 调用成功返回RequestID,失败返回-1
	/// 通过查看lastErrorID和lastErrorMsg查看出错的原因
	int CTraderWrapper::{{method['name']}}(std::string jsonString,int requestID)
{
	printf("{{method['name']}}():被执行...\n");

	{% set parameter = method['parameters'][0] %}
	{{ parameter['raw_type'] }} data;
    int nRequestID;

	// 解析json格式数据
	try{

		Json::Reader jsonReader;
        Json::Value jsonData;

        if (!jsonReader.parse(jsonString, jsonData)){
            throw std::exception();
        }

        Json::Value Parameters = jsonData["Parameters"];
        Assert<std::exception>(!Parameters.empty());
        Json::Value Data = Parameters["Data"];
		//Assert<std::exception>(!Data.empty());


		// TODO:这里将pJsonData转化为对应的结构参数
		{%- set dataTypeName = parameter['raw_type'] %}
		{%- set dataType = structDict[dataTypeName] %}
		{% for field in dataType['fields'] %}
			{%- set typeInfo = typedefDict[field['type']] %}
			{%- if typeInfo['len'] == None %}
				{{ field['remark'] }} {{ typeInfo['type']}} {{field['name']}}
				{% if typeInfo['type'] == 'char' -%}
					if ( !Data["{{field['name']}}"].empty()){
						data.{{field['name']}} = Data["{{field['name']}}"].asString()[0];
					}else{
						data.{{field['name']}} = '0';
					}
				{% elif typeInfo['type'] == 'int' -%}
					if (!Data["{{field['name']}}"].empty()){
						data.{{field['name']}} = Data["{{field['name']}}"].asInt();
					}else{
						data.{{field['name']}} = 0;
					}
				{% elif typeInfo['type'] == 'double' -%}
					if (!Data["{{field['name']}}"].empty()){
						data.{{field['name']}} = Data["{{field['name']}}"].asDouble();
					}else{
						data.{{field['name']}} = 0;
					}
				{% else -%}
					未知类型 {{typeInfo['type']}};
				{%- endif %}
			{%- else %}
				{{ field['remark'] }} {{typeInfo['type']}} {{field['name']}}[{{typeInfo['len']}}];
				{% if typeInfo['type'] == 'char' -%}
					if (!Data["{{field['name']}}"].empty()){
						data.{{field['name']}}[sizeof(data.{{field['name']}})-1] = 0;
						strncpy(data.{{field['name']}},Data["{{field['name']}}"].asCString(),sizeof(data.{{field['name']}})-1);
					}else{
						strcpy(data.{{field['name']}},"");
					}
				{% else -%}
					未知类型{{typeInfo['type']}}[{{typeInfo['len']}}];
				{%- endif -%}
			{%- endif %}
		{%- endfor %}
	}catch (...){
		lastErrorID = -1001;
		lastErrorMsg = "json数据格式错误";
		return -1;
	}

	// 获取RequestID
	//nRequestID = getNextRequestID();
	nRequestID = requestID;

	// 调用对应的CTP API函数
	{{method['returns']}} result =
	pTraderApi->{{method['name']}}(&data, nRequestID);

	// TODO:检查API调用是否失败,并设置LastError信息
	if ( result != 0 ){
		lastErrorID = result;
		switch(result){
			case -1 : lastErrorMsg = "网络连接失败"; break;
			case -2 : lastErrorMsg = "未处理请求超过许可数"; break;
			case -3 : lastErrorMsg = "每秒发送请求超过许可数"; break;
			default : lastErrorMsg = "未知错误";
		}

		//return result;
		return -1;
	}

	// 如果执行成功重置最近错误信息，并将RequestID返回调用程序
	lastErrorID = 0;
	lastErrorMsg = "";
	return 0;
}

{% endfor %}

// 通过名称调用api
int CTraderWrapper::callApiByName(std::string apiName,std::string jsonString,int requestID){

	if (apiExists(apiName)){
		return (this->*apiMap[apiName])(jsonString,requestID);
	}else{
		lastErrorID = -1000;
		lastErrorMsg = "没有这个接口函数";
		return -1;
	}
	return 0;

}

bool CTraderWrapper::apiExists(std::string apiName){

	if ( apiMap.find(apiName) != apiMap.end() ){
		return true;
	}else{
		return false;
	}

}
