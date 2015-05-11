#pragma once

#include <ThostFtdcTraderApi.h>
#include <Message.h>
#include <Configure.h>


class CTraderHandler : public CThostFtdcTraderSpi{

public:

	/// 构造函数
	CTraderHandler(Configure * pConfigure);
	/// 配置信息
    Configure * pConfigure;
	/// zmq通讯环境
	zmq::context_t * pContext;
    /// 通讯套接字
    zmq::socket_t * pSender;

	/// 成功连接回调
	virtual void OnFrontConnected();

/**********************************************************
*                   onRsp开头的方法                         *
***********************************************************/

{% for method in onRspMethodDict.itervalues() %}
	{{ method['remark'] }}
	virtual {{method['returns']}} {{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
);
{% endfor %}

/**********************************************************
*                   onRtn开头的方法                         *
***********************************************************/


{% for method in onRtnMethodDict.itervalues() %}
	{{ method['remark'] }}
	virtual {{method['returns']}} {{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
);
{% endfor %}

/**********************************************************
*                   onErrRtn开头的方法                      *
***********************************************************/

{% for method in onErrRtnMethodDict.itervalues() %}
	{{ method['remark'] }}
	virtual {{method['returns']}} {{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
);
{% endfor %}


/**********************************************************
*                     onRspError方法                       *
***********************************************************/
{% for method in onRspErrorMethodDict.itervalues() %}
	{{ method['remark'] }}
	virtual {{method['returns']}} {{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
);
{% endfor %}

};
