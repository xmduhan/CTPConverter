# -*- coding: utf-8 -*-

import cppheader
import os
from pandas import DataFrame
from jinja2 import Environment, FileSystemLoader

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

    # 获取各类方法信息,目前分为：req,onRsp,onRtn,onErrRtn
    apiMethodDict = cppheader.getClassMethods(ApiClass,'public')
    spiMethodDict = cppheader.getClassMethods(SpiClass,'public')
    reqMethodDict = {name:apiMethodDict[name] for name in apiMethodDict.keys() if name.startswith('Req')}
    onRspMethodDict = {name:spiMethodDict[name] for name in spiMethodDict.keys() if name.startswith('OnRsp')}
    onRtnMethodDict = {name:spiMethodDict[name] for name in spiMethodDict.keys() if name.startswith('OnRtn')}
    onErrRtnMethodDict = {name:spiMethodDict[name] for name in spiMethodDict.keys() if name.startswith('OnErrRtn')}
    #TODO:OnRspError这个函数比较特殊没有对应的req方法,这个函数是否可以和其他函数相同的处理方法还需要进一步确认.

    # 合并生成一个API和SPI的函数全集,这样可以方便我们用名称类获取函数信息
    # API类和SPI类中没有重名的函数,所以可以这么做.
    # 确认API和SPI没有重复：set(SpiMethods.keys()).intersection(ApiMethods.keys())
    methodDict = {}
    methodDict.update(apiMethodDict)
    methodDict.update(spiMethodDict)

    # 数据打包到字典中
    data = {
        'reqMethodDict':reqMethodDict,
        'onRspMethodDict':onRspMethodDict,
        'onRtnMethodDict':onRtnMethodDict,
        'onErrRtnMethodDict':onErrRtnMethodDict,
    }

    return data


def renderTemplate(template,data):
    '''
    将一个模板文件转化对应的cpp文件
    template 模板名称
    注意：这里假设所有模板文件的的后缀都是".cpp.tpl"
    '''
	# 初始化模板系统目录
    env = Environment(loader=FileSystemLoader(templateDir))
    source = env.get_template(template)
    outputFileName = '.'.join(template.split('.')[:-1])
    with open(outputFileName, 'w') as f :
		# 模板生成到文件
		f.write(source.render(**data).encode('utf-8'))
		# 对生成的代码进行格式化
		os.system('astyle %s' % outputFileName)
	# TODO: source 和 template 命名对掉了需要修改回来



def main():
    '''
    将数filename.cpp.tpl转化为对应的.cpp文件
    '''
    # 读取ctp接口的各类定义信息,用于生成模板
    data = loadCtpHeaderData()

    # 读取所有模板列表
    templates = [ i for i in os.listdir(templateDir) if i.endswith('cpp.tpl') ]

    # 遍历所有cpp.tpl模板文件,并生成.cpp文件
    for template in templates:
        renderTemplate(template,data)



if __name__ == '__main__':
    main()
