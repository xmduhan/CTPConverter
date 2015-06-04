# -*- coding: utf-8 -*-
import sys
import cppheader
import os
from pandas import DataFrame
from jinja2 import Environment, FileSystemLoader
from os.path import join
import pickle

# 模板目录
templateDir = 'template'
templateData = 'template_data.pk'


def loadCtpHeaderData():
    '''
    读取提供模板生态代码的ctp api函数信息
    '''

    # 如果存在模板数据文件直接从数据文件中读取
    if os.path.exists(templateData) :
        data = pickle.load(open(templateData, 'rU' ))
        return data

    # c++头文件的定义信息
    TraderApi_h = cppheader.getCppHeader('include/ThostFtdcTraderApi.h',['TRADER_API_EXPORT'])
    MdApi_h = cppheader.getCppHeader('include/ThostFtdcMdApi.h',['MD_API_EXPORT'])
    ApiStruct_h = cppheader.getCppHeader('include/ThostFtdcUserApiStruct.h')
    typedefDict = cppheader.getTypedefDict('include/ThostFtdcUserApiDataType.h')
    enumDict = cppheader.getEnumDict('include/ThostFtdcUserApiDataType.h')

    # 从头文件信息中获取API和SPI的类定义信息
    ApiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderApi')
    SpiClass = cppheader.getClass(TraderApi_h,'CThostFtdcTraderSpi')
    MdSpiClass = cppheader.getClass(MdApi_h,'CThostFtdcMdSpi')
    MdApiClass = cppheader.getClass(MdApi_h,'CThostFtdcMdApi')

    # 读取api和spi类中的所有函数
    apiMethodInfoDict = cppheader.getClassMethods(ApiClass,'public')
    spiMethodInfoDict = cppheader.getClassMethods(SpiClass,'public')
    mdApiMethodInfoDict = cppheader.getClassMethods(MdApiClass,'public')
    mdSpiMethodInfoDict = cppheader.getClassMethods(MdSpiClass,'public')

    # 合并生成一个API和SPI的函数全集,这样可以方便我们用名称类获取函数信息
    # API类和SPI类中没有重名的函数,所以可以这么做.
    # 确认API和SPI没有重复：set(SpiMethods.keys()).intersection(ApiMethods.keys())
    methodInfoDict = {}
    methodInfoDict.update(apiMethodInfoDict)
    methodInfoDict.update(spiMethodInfoDict)

    mdMethodInfoDict = {}
    mdMethodInfoDict.update(mdApiMethodInfoDict)
    mdMethodInfoDict.update(mdSpiMethodInfoDict)

    # 简化函数信息保留我们需要信息，并对未解决类型进行处理
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

    # 将函数分成：Req,OnRsp,OnRtn,OnErrRtn,OnRspError五个大类
    # 每一类函数的参数结构都是相同的
    reqMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('Req')}
    onRspMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRsp') and k != 'OnRspError'}
    onRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnRtn')}
    onErrRtnMethodDict = {k:v for k,v in methodDict.iteritems() if k.startswith('OnErrRtn')}
    onRspErrorMethodDict = {k:v for k,v in methodDict.iteritems() if k == 'OnRspError'}

    mdReqMethodDict = {k:v for k,v in mdMethodDict.iteritems() if k.startswith('Req')}
    mdOnRspMethodDict = {k:v for k,v in mdMethodDict.iteritems() if k.startswith('OnRsp') and k != 'OnRspError'}

    # 生成所有结构体定义的关键信息的字典结构
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


    # 数据打包到字典中
    data = {
        'reqMethodDict':reqMethodDict,
        'onRspMethodDict':onRspMethodDict,
        'onRtnMethodDict':onRtnMethodDict,
        'onErrRtnMethodDict':onErrRtnMethodDict,
        'onRspErrorMethodDict':onRspErrorMethodDict,
        'mdReqMethodDict':mdReqMethodDict,
        'mdOnRspMethodDict':mdOnRspMethodDict,
        'structDict':structDict,
        'typedefDict':typedefDict,
        'mdMethodDict':mdMethodDict,
    }

    #  保存模板数据以便下次访问提高速度
    pickle.dump( data, open(templateData,"wb") )
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
    #print 'filename.split(".")[-2]=',filename.split('.')[-2]
    if filename.split('.')[-2] in ('h','cpp'):
        os.system('astyle -q %s' % output)


def renderAll(data):
    '''
    将模板目录中的所有.cpp.tpl和.h.tpl的文件转化成对应的代码文件
    '''
    # 遍历所有.cpp.tpl模板文件,并生成.cpp文件
    templates = [ i for i in os.listdir(templateDir) if i.endswith('.cpp.tpl') ]
    for template in templates:
        renderTemplate(template,data)

    # 遍历所有的.h.tpl模板文件，并生成.h文件
    templates = [ i for i in os.listdir(templateDir) if i.endswith('.h.tpl') ]
    for template in templates:
        renderTemplate(template,data,'include')


def main():
    '''
    命令使用格式:
    python generate.py [--all] | [template file name] [source place dir]
    '''
    # 读取ctp接口的各类定义信息,用于生成模板
    data = loadCtpHeaderData()

    if len(sys.argv) < 2:
        print '请使用以下命令格式启动程序:'
        print 'python generate.py [--all] | [template file name] [source place dir]'
        return

    if sys.argv[1] == '--all' :
        renderAll(data)

    else:
        # 读取命令参数
        templateFile = sys.argv[1]
        if len(sys.argv) >= 3 :
            outputDir = sys.argv[2]
        else :
            outputDir = '.'

        # 调用生成模板
        renderTemplate(templateFile,data,outputDir)







if __name__ == '__main__':
    main()
