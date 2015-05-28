# -*- coding: utf-8 -*-

{% for struct in structDict.itervalues() %}
{% set fields = struct['fields'] %}
class {{struct['name']}}:
    '''
    {{struct['remark'][3:]}}
    {%- for field in fields %}
        {% set type = typedefDict[field['type']] %}
        {{field['name']}} {{field['remark'][3:]}} {{type['type']}}
        {%- if type['len'] %}[{{type['len'] }}] {% endif -%}
    {% endfor %}
    '''

    def __init__(self,**fields):
        ''' '''
    {% for field in fields %}
        '''{{field['remark'][3:]}}'''
        self.{{field['name']}} = None
    {% endfor %}
        self.__dict__.update(fields)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}

{% endfor %}
