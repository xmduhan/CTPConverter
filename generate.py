# -*- coding: utf-8 -*-

import cppheader
import os
from pandas import DataFrame
from jinja2 import Environment, FileSystemLoader
from os.path import join

# 模板目录
templateDir = 'template'

def loadCtpHeaderData():
    '''
    读取提供模板生态代码的ctp api函数信息
    '''
    # c++头文件的定义信息
    TraderApi_h = cppheader.getCppHeader('include/ThostFtdcTraderApi.h',['TRADER_API_EXPORT'])
    ApiStruct_h = cppheader.getCppHeader('include/ThostFtdcUserApiStruct.h')
    typedefDict = cppheader.getTypedefDict('include/ThostFtdcUserApiDataType.h')
    enumDict = cppheader.getEnumDict('include/ThostFtdcUserApiDataType.h')

    # 从头文件信息中获取API和SPI的类定义信息
    ApiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderApi')
    SpiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderSpi')

    #%% 读取api和spi类中的所有函数
    apiMethodInfoDict = cppheader.getClassMethods(ApiClass,'public')
    spiMethodInfoDict = cppheader.getClassMethods(SpiClass,'public')

    # 合并生成一个API和SPI的函数全集,这样可以方便我们用名称类获取函数信息
    # API类和SPI类中没有重名的函数,所以可以这么做.
    # 确认API和SPI没有重复：set(SpiMethods.keys()).intersection(ApiMethods.keys())
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
    #TODO:OnRspError这个函数比较特殊没有对应的req方法,这个函数是否可以和其他函数相同的处理方法还需要进一步确认.
    reqMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('Req')}
    onRspMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRsp')}
    onRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRtn')}
    onErrRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnErrRtn')}

    # 数据打包到字典中
    data = {
        'reqMethodDict':reqMethodDict,
        'onRspMethodDict':onRspMethodDict,
        'onRtnMethodDict':onRtnMethodDict,
        'onErrRtnMethodDict':onErrRtnMethodDict,
    }

    return data


def renderTemplate(filename,data,outdir='.'):
    '''
    将一个模板文件转化对应的.cpp文件
    filename 模板名称
    注意：这里假设所有模板文件的的后缀都是".cpp.tpl"
    '''
	# 初始化模板系统目录
    env = Environment(loader=FileSystemLoader(templateDir))
    template = env.get_template(filename)
    output = join(outdir,'.'.join(filename.split('.')[:-1]))
    with open(output, 'w') as f :
		# 模板生成到文件
		f.write(template.render(**data).encode('utf-8'))
		# 对生成的代码进行格式化
    os.system('astyle -q %s' % output)


def main():
    '''
    将数filename.cpp.tpl转化为对应的.cpp文件
    '''
    # 读取ctp接口的各类定义信息,用于生成模板
    data = loadCtpHeaderData()

    # 遍历所有.cpp.tpl模板文件,并生成.cpp文件
    templates = [ i for i in os.listdir(templateDir) if i.endswith('.cpp.tpl') ]
    for template in templates:
        renderTemplate(template,data)

    # 遍历所有的.h.tpl模板文件，并生成.h文件
    templates = [ i for i in os.listdir(templateDir) if i.endswith('.h.tpl') ]
    for template in templates:
        renderTemplate(template,data,'include')




if __name__ == '__main__':
    main()
