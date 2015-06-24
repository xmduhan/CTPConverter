# -*- coding: utf-8 -*-

#%% 代码实线路径
#1、先将相关的函数列在列在CTraderHandler.cpp（ok）
#2、CApiWrapper类
# (0) 类的接口设计(头文件定义)

CApiWrapper 手工编写部分（基本ok）
-- 登录过程(ok)
-- requestId(ok)
CApiWrapper 自动编写部分（ok）
防止头文件重定义问题（Configure.h马上就有这个问题）(ok)
在CTraderHandler类中实现：
重载virtual void OnFrontConnected()  (ok)
#2、在converter中增加登录和退出的代码。(已封装到CApiWrapper中)

#3、生成zmq套接字连接代码。
连接zmq环境成功(ok)
接受初步消息 (ok)
**按消息格式接受多段消息(ok)
**需要有一个文件实现消息格式的封装。(ok,基本完成，其中路由)

** 将socket改为非指针定义(ok,变相实现)

**禁止pushback管道使用tcp配置，而应使用inpc或者ipc(ok,解决了bind绑定和connect使用同一个地址问题，就不需要这么做了)
**OnFrontConnected中可以返回消息 (ok)
**OnRspUserLogin()中可以返回消息 (ok)

#4、json的处理（含打包和拆包）
(1)jsoncpp的安装 (ok)
(2)OnRsp,(ok)
(5)初步完成CApiWrapper代码编写 (ok)
1、完成调用到响应的贯通(ok)
1、处理返回信息的编码问题(ok)
2、主程序代码结构编写(ok)
1、c++如何使用hashmap问题(ok)
1、makefile改进提高速度(ok)
1、测试框架(ok)
1、完成api调用的测试的完整用例(ok)
（1）接受消息的时候需要保存测试用例
2、atom文件过滤的问题（ok）
1、测试用例的完善(ok)
(1)环境变量的重新命名,并完善到测试用例中(ok)
(2)请求和返回的变量名冲突问题(ok)
1、响应消息增加isLast字段(ok)
1、python的消息也要单独封装起来，这样修改消息格式的时候方便。(ok)
1、初步实线ctp同步库的封装代码生成(ok)
1、请求结构和返回结构数据的生成(ok)
1、将class转化为dict，将dict转化位class(ok)
1、CTPChannel类代码生成(可以先通过写死环境变量初始化连接)（ok）
1、解决errorCode和errorId不一致问题(ok)
1、在CTPChannel统一出错代码(ok)
1、让trader命令行参数而不是使用环境变量(ok)
1、实线MD API(ok)
(2)设计一个CTPChannel的类，一个channel对应一个converter(ok)
|--如何管理进程converter(何时创建何时销毁)
|--如果保证不同的converter进程使用的通讯管道都不重复?

(3)接口的python wrapper如何找到对应的channel (ok)
|--是否把api作为channel的成员函数(采用)
|--是否把让api的第一个参数是channel 
|--在api函数中调用一个getChannel()函数（获取空闲的channel)
1、转换器要实现流量控制功能，并缓存过于频繁的查请求，并按能按指定频率进行
(1)RequestID要移到tarder主函数中来处理(ok)
(2)增加定义查询请求队列(ok)
(3)查询请求处理机制改为先入队再处理的方式。(ok)
(4)增加流量控制罗辑(ok)
(5)增加参数读取功能设置(ok)
------------------------------------------------------------------------------

1、需要处理服务器重启后不能执行之前缓存中的数据
1、编码问题应该是可以设置的，增加客户端编码和服务器编码

1、创建订单的结构体中居然有一个requestID，这需要从参数拷贝过去，需要一段特殊代码
1、编写生成python测试用例拷贝原型的脚本(是否做成单独的库文件)
1、在响应函数中如果收到last标识需要删路由表，防止路由表无线膨胀
1、测试用例可以自行启动CTP接口(这样可以方便很多)
1、测试行情查询请求的性能是否符合要求。
1、需要设计出错信息
1、如何添加测试框架问题
1、确认c++ map是 linked 还是 hashmap
2、调用信息时放入一个空的Data对象会报错的问题()


(3)OnRtn,
(4)OnErrRtn
(6)OnRsp字符串编码转化的问题



#5、监听代码框架编写(使用CTRL+C退出程序)


暂缓：
1、c++如何写日志问题(暂缓)
1、简单阅读一下测试用例编写的章节(暂缓,似乎不能得到什么)
(1)Message.h和python中的message.py一个是服务端，一个是客户端要如何区分清楚(暂缓)
1、测试查询账号能否使用trader api（似乎不行,暂缓）
（2）如何给成员加注释(暂缓)

# 其他备注：
# (1) ctp api 的初始化操作(含登录，涉及和spi类的交互)
# (2) ctpapi.cpp改为CApiWrapper 封装所有Req开头的函数，参数：（1）原始json数据包
# (3) req函数返回RequestId这个id由这个wrapper维护
# (4) 如果req函数返回-1表示出错，可以通过getLastError机制获取信息。

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
MdApi_h = cppheader.getCppHeader('include/ThostFtdcMdApi.h',['MD_API_EXPORT'])
ApiStruct_h = cppheader.getCppHeader('include/ThostFtdcUserApiStruct.h')
typedefDict = cppheader.getTypedefDict('include/ThostFtdcUserApiDataType.h')
enumDict = cppheader.getEnumDict('include/ThostFtdcUserApiDataType.h')
SpiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderSpi')
ApiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderApi')
MdSpiClass = cppheader.getClass(MdApi_h,'CThostFtdcMdSpi')
MdApiClass = cppheader.getClass(MdApi_h,'CThostFtdcMdApi')
#%% 读取api和spi类中的所有函数
apiMethodInfoDict = cppheader.getClassMethods(ApiClass,'public')
spiMethodInfoDict = cppheader.getClassMethods(SpiClass,'public')
mdApiMethodInfoDict = cppheader.getClassMethods(MdApiClass,'public')
mdSpiMethodInfoDict = cppheader.getClassMethods(MdSpiClass,'public')
#合并api和spi函数，形成完整函数集
#这里之所以可能讲所有函数合并，在于api和spi方法没有重复，请看下面语句：
#set(spiMethodInfoDict.keys()).intersection(apiMethodInfoDict.keys())
methodInfoDict = {}
methodInfoDict.update(apiMethodInfoDict)
methodInfoDict.update(spiMethodInfoDict)
mdMethodInfoDict = {}
mdMethodInfoDict.update(mdApiMethodInfoDict)
mdMethodInfoDict.update(mdSpiMethodInfoDict)
#%% 简化函数信息保留我们需要信息，并对未解决类型进行处理
methodDict = {}
for mi in methodInfoDict.itervalues() :
    method = {}
    method['name'] = mi['name']
    method['returns'] = mi['returns']
    method['remark'] = mi['doxygen'].decode('utf8')
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


mdMethodDict = {}
for mi in mdMethodInfoDict.itervalues() :
    method = {}
    method['name'] = mi['name']
    method['returns'] = mi['returns']
    method['remark'] = mi['doxygen'].decode('utf8')
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
    mdMethodDict[method['name']] = method

#%% 将函数分成：Req,OnRsp,OnRtn,OnErrRtn,OnRspError四个大类
reqMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('Req')}
onRspMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRsp') and k != 'OnRspError'}
onRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRtn')}
onErrRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnErrRtn')}
onRspErrorMethodDict = {k:v for k,v in methodDict.iteritems() if k == 'OnRspError'}


mdReqMethodDict = {k:v for k,v in mdMethodDict.iteritems() if k.startswith('Req')}
mdOnRspMethodDict = {k:v for k,v in mdMethodDict.iteritems() if k.startswith('OnRsp') and k != 'OnRspError'}


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

#%%类型名称查找结构体定义
structDict = {}
structInfoDict =  cppheader.getClasses(ApiStruct_h)
for si in  structInfoDict.viewvalues():
    struct = {}
    struct['name'] = si['name']
    struct['remark'] = si['doxygen'].decode('utf8')
    fields = []
    for pi in si['properties']['public']:
        field = {}
        field['name'] = pi['name']
        field['type'] = pi['type']
        field['raw_type'] = pi['raw_type']
        field['pointer'] = pi['pointer']
        field['unresolved'] = pi['unresolved']
        field['remark'] = pi['doxygen'].decode('utf8')
        fields.append(field)
    struct['fields'] = fields
    structDict[si['name']] = struct

#%%
structDict['CThostFtdcRspInfoField']
ErrorID
ErrorMsg

#%% 寻找ctp定义变量中最长的类型
maxLen = 0
for i in typedefDict.itervalues():
    l = int(i.get('len',0) or '0')
    if l > maxLen :
        maxLen = l
print 'maxLen=',maxLen

#%% 遍历模板目录中的所有模板文件
import os
templates = [ i for i in os.listdir('template') if i.endswith('cpp.tpl') ]


for template in templates:
    print '.'.join(template.split('.')[:-1])


#%% API 封装的基本结构
### 将一个json参数拆包，填如API的参数结构中，调用API。







#%% SPI 封装的基本结构
### 将返回参数打包成一个json接口然后发送到队列中


for name,method in onRspMethodDict.iteritems():
    print name



#%% python执行ctp接口调用例子
import os
os.chdir('/home/duhan/github/CTPConverter/test')

from channel import CTPChannel
from CTPStruct import *

ch = CTPChannel()
data = CThostFtdcQryTradingAccountField()
errorID,errorMsg,responeDataList =  ch.QryTradingAccount(data)
print errorID,errorMsg,responeDataList
print len(responeDataList)
print responeDataList[0].toDict()


#%% 使用命令行启动trader
import os
frontAddress = os.environ.get('CTP_FRONT_ADDRESS') 
assert frontAddress
brokerID = os.environ.get('CTP_BROKER_ID') 
assert brokerID
userID = os.environ.get('CTP_USER_ID') 
assert userID
password = os.environ.get('CTP_PASSWORD') 
assert password
requestPipe = os.environ.get('CTP_REQUEST_PIPE') 
assert requestPipe
pushbackPipe = os.environ.get('CTP_PUSHBACK_PIPE') 
assert pushbackPipe
publishPipe = os.environ.get('CTP_PUBLISH_PIPE') 
assert publishPipe
instrumentIDConfigFile = os.environ.get('CTP_INSTRUMENT_ID_CONFIG_FILE') 
assert instrumentIDConfigFile

command = ' '.join(['bin/trader',
'--FrontAddress %s' % frontAddress,
'--BrokerID %s' % brokerID,
'--UserID %s' % userID,
'--Password %s' % password,
'--RequestPipe %s' % requestPipe,
'--PushbackPipe %s' % pushbackPipe,
'--PublishPipe %s' % publishPipe,
'--PnstrumentIDConfigFile %s' % instrumentIDConfigFile,
])


command


#%%
import json
content = json.dumps(['IF1506','IF1507'])
with open('/tmp/config.json', 'w') as f:
    f.write(content.encode('utf-8'))
    
#%% 为CThostFtdcDepthMarketDataField生成django model
for field in structDict['CThostFtdcDepthMarketDataField']['fields'] :    
    fieldName = field['name']
    fieldRemark = field['remark'][3:]
    fieldType = typedefDict[field['raw_type']]['type']
    fieldLen = typedefDict[field['raw_type']]['len']    
    #print fieldName,fieldType,fieldLen,type(fieldLen)
    if fieldType == 'char':
        print '''%s = models.CharField(u'%s', max_length=%s, default='') ''' \
            % (fieldName,fieldRemark,fieldLen)
    if fieldType == 'int':
        print '''%s = models.IntegerField(u'%s', default=0) ''' \
            % (fieldName,fieldRemark)
    if fieldType == 'double':
        print '''%s = models.FloatField(u'%s', default=0) ''' \
            % (fieldName,fieldRemark)
    
#%% 生成admin的fields列表 
fields = []
for field in structDict['CThostFtdcDepthMarketDataField']['fields'] :    
    fieldName = field['name']
    fields.append(fieldName)
fields