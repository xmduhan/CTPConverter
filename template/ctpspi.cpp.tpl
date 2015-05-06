
#include <ThostFtdcTraderApi.h>




class CTraderHandler : public CThostFtdcTraderSpi{

public:


{% for method in onRspMethodDict.itervalues() %}
virtual {{method['returns']}} {{method['name']}}(
	{% for parameter in method['parameters'] -%}
	    {{ parameter['type'] }} {{parameter['name'] -}}
		{%- if not loop.last %},
		{% endif -%}
	{%- endfor %}
){

}
{% endfor %}





};
