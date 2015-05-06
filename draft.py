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
#%% 生成各类相关函数集合
apiMethodDict = cppheader.getClassMethods(ApiClass,'public')
spiMethodDict = cppheader.getClassMethods(SpiClass,'public')
#set(SpiMethods.keys()).intersection(ApiMethods.keys())   # API类和SPI类中没有重名的函数
methodDict = {}
methodDict.update(apiMethodDict)
methodDict.update(spiMethodDict)
reqMethodDict = {name:apiMethodDict[name] for name in apiMethodDict.keys() if name.startswith('Req')}
onRspMethodDict = {name:spiMethodDict[name] for name in spiMethodDict.keys() if name.startswith('OnRsp')}
onRtnMethodDict = {name:spiMethodDict[name] for name in spiMethodDict.keys() if name.startswith('OnRtn')}
onErrRtnMethodDict = {name:spiMethodDict[name] for name in spiMethodDict.keys() if name.startswith('OnErrRtn')}
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









