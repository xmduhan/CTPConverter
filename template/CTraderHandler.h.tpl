#pragma once

#include <ThostFtdcTraderApi.h>

class CTraderHandler : public CThostFtdcTraderSpi{

public:

	/// 构造函数
	CTraderHandler();
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
