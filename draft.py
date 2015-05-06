# -*- coding: utf-8 -*-

#%% 代码实线路径
#1、先将相关的函数列在列在ctpapi.cpp和ctpspi.cpp中。
#2、在converter中增加登录和退出的代码。
#3、监听代码框架编写
#4、生成zmq套接字连接代码。
#5、json的处理（含打包和拆包）

#%% 修改到项目目录
import os 
os.chdir('/home/duhan/github/CTPConverter')
import cppheader
from pandas import DataFrame
import pandas as pd
from pandas.io.excel import ExcelWriter
#%% 获取ctp所有的方法名称
# 获取CThostFtdcTraderSpi的所有方法（以OnRsp,OnRtn,OnErrRtn开头)
# 获取CThostFtdcTraderApi的所有方法（以Req开头）
TraderApi_h = cppheader.getCppHeader('include/ThostFtdcTraderApi.h',['TRADER_API_EXPORT'])
ApiStruct_h = cppheader.getCppHeader('include/ThostFtdcUserApiStruct.h')
typedefDict = cppheader.getTypedefDict('include/ThostFtdcUserApiDataType.h')
enumDict = cppheader.getEnumDict('include/ThostFtdcUserApiDataType.h')	
SpiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderSpi')
ApiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderApi')
#%% 读取api和spi类中的所有函数
apiMethodInfoDict = cppheader.getClassMethods(ApiClass,'public')
spiMethodInfoDict = cppheader.getClassMethods(SpiClass,'public')
#合并api和spi函数，形成完整函数集
#这里之所以可能讲所有函数合并，在于api和spi方法没有重复，请看下面语句：
#set(spiMethodInfoDict.keys()).intersection(apiMethodInfoDict.keys())   
methodInfoDict = {}
methodInfoDict.update(apiMethodInfoDict)
methodInfoDict.update(spiMethodInfoDict)
#%% 简化函数信息保留我们需要信息，并对未解决类型进行处理
methodDict = {}
for mi in methodInfoDict.itervalues() :
    method = {}    
    method['name'] = mi['name']
    method['returns'] = mi['returns']
    parameters=[]    
    for pi in mi['parameters'] :
        parameter = {}
        parameter['name'] = pi['name']
        parameter['type'] = pi['type']
        parameter['raw_type'] = pi['raw_type']
        parameter['pointer'] = pi['pointer']
        parameter['unresolved'] = pi['unresolved']        
        parameters.append(parameter)
    method['parameters'] = parameters
    methodDict[method['name']] = method

#%% 将函数分成：Req,OnRsp,OnRtn,OnErrRtn四个大类
reqMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('Req')}
onRspMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRsp')}
onRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRtn')}
onErrRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnErrRtn')}

#%% 查看所有函数的数量
print 'len(reqMethodDict.keys())=',len(reqMethodDict.keys())
print 'len(onRspMethodDict.keys())=',len(onRspMethodDict.keys())
print 'len(onRtnMethodDict.keys())=',len(onRtnMethodDict.keys())
print 'len(onErrRtnMethodDict.keys())=',len(onErrRtnMethodDict.keys())
# OnRsp之所以比Req多一个,因为有一个OnRspError
# 这个函数的处理方法是否要跟其他OnRsp函数一样，需要进一步确认

#%% 确认OnRsp比Req多一个的原因
d1 = {
'request':reqMethodDict.keys(),
'apiname':[ name[3:] for name in reqMethodDict.keys()]
}
df1 = DataFrame(d1)

d2 = {
'response':onRspMethodDict.keys(),
'apiname':[ name[5:] for name in onRspMethodDict.keys()]
}
df2 = DataFrame(d2)

df = df1.merge(df2,on='apiname',how='outer')

writer = ExcelWriter('/tmp/output.xls')
df.to_excel(writer)
writer.save()
# 导出excel查看

#%%
# 根据一个函数名获取函数的定义
method = methodDict['OnRspQryOrder']
print method['doxygen']
print method['name'],'(',
parameters = cppheader.getMethodParameters(method)
for p in parameters:
    print p['type'],p['name']+',',
print ')'

#%%


print methodInfoDict
#%% 根据类型找定义









#%% 遍历模板目录中的所有模板文件
import os
templates = [ i for i in os.listdir('template') if i.endswith('cpp.tpl') ]


for template in templates:
    print '.'.join(template.split('.')[:-1])


#%% API 封装的基本结构
### 将一个json参数拆包，填如API的参数结构中，调用API。







#%% SPI 封装的基本结构
### 将返回参数打包成一个json接口然后发送到队列中 









