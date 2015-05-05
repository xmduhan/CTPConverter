# -*- coding: utf-8 -*-

#%% 代码实线路径
1、先讲相关的函数列在列在ctpapi.cpp和ctpspi.cpp中。
2、在converter中增加登录和退出的代码。
3、监听代码框架编写
4、生成zmq套接字连接代码。
5、json的处理（含打包和拆包）

#%% 修改到项目目录 
os.chdir('/home/duhan/github/CTPConverter')
!pwd
#%% 获取ctp所有的方法名称
# 获取CThostFtdcTraderSpi的所有方法（以OnRsp,OnRtn,OnErrRtn开头)
# 获取CThostFtdcTraderApi的所有方法（以Req开头）





#%% API 封装的基本结构
### 将一个json参数拆包，填如API的参数结构中，调用API。


#%% SPI 封装的基本结构
### 将返回参数打包成一个json接口然后发送到队列中 









