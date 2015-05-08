#include <stdio.h>
#include <ThostFtdcTraderApi.h>
#include <CTraderHandler.h>


/// 构造函数
CTraderHandler::CTraderHandler() {
	printf("CTraderHandler():被执行...\n");
}

/// 成功连接服务器消息
void CTraderHandler::OnFrontConnected() {
    printf("OnFrontConnected():被执行...\n");
}


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
