# -*- coding: utf-8 -*-
from channel import CTPChannel
from CTPStruct import *
from time import sleep

{% for method in reqMethodDict.itervalues() %}
{% set parameter = method['parameters'][0]  %}
def test_{{ method['name'][3:]}}():
    '''
    测试{{ method['name'][3:]}}
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_{{ method['name'][3:]}}():开始'
    sleep(1)
    ch = CTPChannel()
    data = {{parameter['raw_type']}}()
    errorID,errorMsg,responeDataList =  ch.{{method['name'][3:]}}(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_{{ method['name'][3:]}}():请求完成'

    assert errorID == 0,u'请求失败'

    print 'test_{{ method['name'][3:]}}():执行结束'
    print '----------------------------------------------------------------------'

{% endfor %}
