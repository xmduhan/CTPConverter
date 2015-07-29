#!/usr/bin/env python
# encoding: utf-8

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

#%% 打印所有函数的声明
methodNameList = methodDict.keys()
methodNameList.sort()
for methodName in methodNameList:
    print methodDict[methodName]['remark']
    print methodName,'(',
    parameters = methodDict[methodName]['parameters']
    print ','.join([p['name'] for p in parameters]),
    print ')'
    if len(parameters) != 0:
        for p in parameters:
            if p['raw_type'] in structDict:
                print '%s(%s)' % (p['name'],p['raw_type'])
                fields = structDict[p['raw_type']]['fields']
                for f in fields:
                    print '|-%s' % f['name'],
                    if 'requestid' in f['name'].lower():
                        print '(*****)',
                    print
    print '---------------------------------------------------------------'



