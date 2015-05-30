# -*- coding: utf-8 -*-
from channel import CTPChannel
from CTPStruct import *
from time import sleep
from nose.plugins.attrib import attr




@attr('QryTradingAccount')
def test_QryTradingAccount():
    '''
    测试QryTradingAccount
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTradingAccount():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTradingAccountField()
    errorID,errorMsg,responeDataList =  ch.QryTradingAccount(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTradingAccount():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryTradingAccount():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryCFMMCTradingAccountKey')
def test_QryCFMMCTradingAccountKey():
    '''
    测试QryCFMMCTradingAccountKey
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryCFMMCTradingAccountKey():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryCFMMCTradingAccountKeyField()
    errorID,errorMsg,responeDataList =  ch.QryCFMMCTradingAccountKey(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryCFMMCTradingAccountKey():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryCFMMCTradingAccountKey():执行结束'
    print '----------------------------------------------------------------------'






@attr('QryTradingNotice')
def test_QryTradingNotice():
    '''
    测试QryTradingNotice
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTradingNotice():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTradingNoticeField()
    errorID,errorMsg,responeDataList =  ch.QryTradingNotice(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTradingNotice():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryTradingNotice():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryTrade')
def test_QryTrade():
    '''
    测试QryTrade
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTrade():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTradeField()
    errorID,errorMsg,responeDataList =  ch.QryTrade(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTrade():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryTrade():执行结束'
    print '----------------------------------------------------------------------'




@attr('QueryMaxOrderVolume')
def test_QueryMaxOrderVolume():
    '''
    测试QueryMaxOrderVolume
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QueryMaxOrderVolume():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQueryMaxOrderVolumeField()
    errorID,errorMsg,responeDataList =  ch.QueryMaxOrderVolume(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QueryMaxOrderVolume():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QueryMaxOrderVolume():执行结束'
    print '----------------------------------------------------------------------'






@attr('QryInvestorPosition')
def test_QryInvestorPosition():
    '''
    测试QryInvestorPosition
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInvestorPosition():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInvestorPositionField()
    errorID,errorMsg,responeDataList =  ch.QryInvestorPosition(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInvestorPosition():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInvestorPosition():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryBrokerTradingAlgos')
def test_QryBrokerTradingAlgos():
    '''
    测试QryBrokerTradingAlgos
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryBrokerTradingAlgos():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryBrokerTradingAlgosField()
    errorID,errorMsg,responeDataList =  ch.QryBrokerTradingAlgos(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryBrokerTradingAlgos():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryBrokerTradingAlgos():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryOrder')
def test_QryOrder():
    '''
    测试QryOrder
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryOrder():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryOrderField()
    errorID,errorMsg,responeDataList =  ch.QryOrder(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryOrder():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryOrder():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryExchange')
def test_QryExchange():
    '''
    测试QryExchange
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryExchange():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryExchangeField()
    errorID,errorMsg,responeDataList =  ch.QryExchange(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryExchange():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryExchange():执行结束'
    print '----------------------------------------------------------------------'








@attr('QryExchangeRate')
def test_QryExchangeRate():
    '''
    测试QryExchangeRate
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryExchangeRate():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryExchangeRateField()
    errorID,errorMsg,responeDataList =  ch.QryExchangeRate(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryExchangeRate():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryExchangeRate():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryInvestorPositionDetail')
def test_QryInvestorPositionDetail():
    '''
    测试QryInvestorPositionDetail
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInvestorPositionDetail():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInvestorPositionDetailField()
    errorID,errorMsg,responeDataList =  ch.QryInvestorPositionDetail(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInvestorPositionDetail():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInvestorPositionDetail():执行结束'
    print '----------------------------------------------------------------------'




@attr('QrySettlementInfoConfirm')
def test_QrySettlementInfoConfirm():
    '''
    测试QrySettlementInfoConfirm
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QrySettlementInfoConfirm():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQrySettlementInfoConfirmField()
    errorID,errorMsg,responeDataList =  ch.QrySettlementInfoConfirm(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QrySettlementInfoConfirm():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QrySettlementInfoConfirm():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryBrokerTradingParams')
def test_QryBrokerTradingParams():
    '''
    测试QryBrokerTradingParams
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryBrokerTradingParams():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryBrokerTradingParamsField()
    errorID,errorMsg,responeDataList =  ch.QryBrokerTradingParams(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryBrokerTradingParams():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryBrokerTradingParams():执行结束'
    print '----------------------------------------------------------------------'




@attr('QueryCFMMCTradingAccountToken')
def test_QueryCFMMCTradingAccountToken():
    '''
    测试QueryCFMMCTradingAccountToken
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QueryCFMMCTradingAccountToken():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQueryCFMMCTradingAccountTokenField()
    errorID,errorMsg,responeDataList =  ch.QueryCFMMCTradingAccountToken(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QueryCFMMCTradingAccountToken():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QueryCFMMCTradingAccountToken():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryNotice')
def test_QryNotice():
    '''
    测试QryNotice
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryNotice():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryNoticeField()
    errorID,errorMsg,responeDataList =  ch.QryNotice(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryNotice():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryNotice():执行结束'
    print '----------------------------------------------------------------------'








@attr('QryInvestorPositionCombineDetail')
def test_QryInvestorPositionCombineDetail():
    '''
    测试QryInvestorPositionCombineDetail
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInvestorPositionCombineDetail():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInvestorPositionCombineDetailField()
    errorID,errorMsg,responeDataList =  ch.QryInvestorPositionCombineDetail(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInvestorPositionCombineDetail():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInvestorPositionCombineDetail():执行结束'
    print '----------------------------------------------------------------------'






@attr('QrySecAgentACIDMap')
def test_QrySecAgentACIDMap():
    '''
    测试QrySecAgentACIDMap
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QrySecAgentACIDMap():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQrySecAgentACIDMapField()
    errorID,errorMsg,responeDataList =  ch.QrySecAgentACIDMap(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QrySecAgentACIDMap():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QrySecAgentACIDMap():执行结束'
    print '----------------------------------------------------------------------'






@attr('QueryBankAccountMoneyByFuture')
def test_QueryBankAccountMoneyByFuture():
    '''
    测试QueryBankAccountMoneyByFuture
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QueryBankAccountMoneyByFuture():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcReqQueryAccountField()
    errorID,errorMsg,responeDataList =  ch.QueryBankAccountMoneyByFuture(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QueryBankAccountMoneyByFuture():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QueryBankAccountMoneyByFuture():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryParkedOrderAction')
def test_QryParkedOrderAction():
    '''
    测试QryParkedOrderAction
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryParkedOrderAction():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryParkedOrderActionField()
    errorID,errorMsg,responeDataList =  ch.QryParkedOrderAction(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryParkedOrderAction():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryParkedOrderAction():执行结束'
    print '----------------------------------------------------------------------'






@attr('QryExchangeMarginRate')
def test_QryExchangeMarginRate():
    '''
    测试QryExchangeMarginRate
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryExchangeMarginRate():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryExchangeMarginRateField()
    errorID,errorMsg,responeDataList =  ch.QryExchangeMarginRate(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryExchangeMarginRate():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryExchangeMarginRate():执行结束'
    print '----------------------------------------------------------------------'








@attr('QryInstrument')
def test_QryInstrument():
    '''
    测试QryInstrument
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInstrument():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInstrumentField()
    errorID,errorMsg,responeDataList =  ch.QryInstrument(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInstrument():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInstrument():执行结束'
    print '----------------------------------------------------------------------'






@attr('QryInstrumentCommissionRate')
def test_QryInstrumentCommissionRate():
    '''
    测试QryInstrumentCommissionRate
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInstrumentCommissionRate():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInstrumentCommissionRateField()
    errorID,errorMsg,responeDataList =  ch.QryInstrumentCommissionRate(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInstrumentCommissionRate():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInstrumentCommissionRate():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryInstrumentMarginRate')
def test_QryInstrumentMarginRate():
    '''
    测试QryInstrumentMarginRate
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInstrumentMarginRate():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInstrumentMarginRateField()
    errorID,errorMsg,responeDataList =  ch.QryInstrumentMarginRate(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInstrumentMarginRate():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInstrumentMarginRate():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryInvestor')
def test_QryInvestor():
    '''
    测试QryInvestor
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInvestor():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInvestorField()
    errorID,errorMsg,responeDataList =  ch.QryInvestor(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInvestor():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInvestor():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryExchangeMarginRateAdjust')
def test_QryExchangeMarginRateAdjust():
    '''
    测试QryExchangeMarginRateAdjust
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryExchangeMarginRateAdjust():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryExchangeMarginRateAdjustField()
    errorID,errorMsg,responeDataList =  ch.QryExchangeMarginRateAdjust(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryExchangeMarginRateAdjust():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryExchangeMarginRateAdjust():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryInvestorProductGroupMargin')
def test_QryInvestorProductGroupMargin():
    '''
    测试QryInvestorProductGroupMargin
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryInvestorProductGroupMargin():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryInvestorProductGroupMarginField()
    errorID,errorMsg,responeDataList =  ch.QryInvestorProductGroupMargin(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryInvestorProductGroupMargin():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryInvestorProductGroupMargin():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryEWarrantOffset')
def test_QryEWarrantOffset():
    '''
    测试QryEWarrantOffset
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryEWarrantOffset():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryEWarrantOffsetField()
    errorID,errorMsg,responeDataList =  ch.QryEWarrantOffset(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryEWarrantOffset():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryEWarrantOffset():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryDepthMarketData')
def test_QryDepthMarketData():
    '''
    测试QryDepthMarketData
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryDepthMarketData():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryDepthMarketDataField()
    errorID,errorMsg,responeDataList =  ch.QryDepthMarketData(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryDepthMarketData():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryDepthMarketData():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryTransferBank')
def test_QryTransferBank():
    '''
    测试QryTransferBank
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTransferBank():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTransferBankField()
    errorID,errorMsg,responeDataList =  ch.QryTransferBank(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTransferBank():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryTransferBank():执行结束'
    print '----------------------------------------------------------------------'






@attr('QryProduct')
def test_QryProduct():
    '''
    测试QryProduct
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryProduct():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryProductField()
    errorID,errorMsg,responeDataList =  ch.QryProduct(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryProduct():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryProduct():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryTradingCode')
def test_QryTradingCode():
    '''
    测试QryTradingCode
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTradingCode():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTradingCodeField()
    errorID,errorMsg,responeDataList =  ch.QryTradingCode(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTradingCode():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryTradingCode():执行结束'
    print '----------------------------------------------------------------------'




@attr('QrySettlementInfo')
def test_QrySettlementInfo():
    '''
    测试QrySettlementInfo
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QrySettlementInfo():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQrySettlementInfoField()
    errorID,errorMsg,responeDataList =  ch.QrySettlementInfo(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QrySettlementInfo():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QrySettlementInfo():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryAccountregister')
def test_QryAccountregister():
    '''
    测试QryAccountregister
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryAccountregister():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryAccountregisterField()
    errorID,errorMsg,responeDataList =  ch.QryAccountregister(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryAccountregister():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryAccountregister():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryParkedOrder')
def test_QryParkedOrder():
    '''
    测试QryParkedOrder
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryParkedOrder():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryParkedOrderField()
    errorID,errorMsg,responeDataList =  ch.QryParkedOrder(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryParkedOrder():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryParkedOrder():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryTransferSerial')
def test_QryTransferSerial():
    '''
    测试QryTransferSerial
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryTransferSerial():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryTransferSerialField()
    errorID,errorMsg,responeDataList =  ch.QryTransferSerial(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryTransferSerial():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryTransferSerial():执行结束'
    print '----------------------------------------------------------------------'




@attr('QryContractBank')
def test_QryContractBank():
    '''
    测试QryContractBank
    '''
    print ''
    print '----------------------------------------------------------------------'
    print 'test_QryContractBank():开始'
    sleep(1)
    ch = CTPChannel()
    data = CThostFtdcQryContractBankField()
    errorID,errorMsg,responeDataList =  ch.QryContractBank(data)
    if errorID == 0 :
        print u'共收到%d数据记录' % len(responeDataList)
        for i,responeData in enumerate(responeDataList):
            print '---------------------------------%d------------------------------------' % (i + 1)
            for k,v in responeData.toDict().iteritems():
                print k,'=',v,',',
            print ''
    else :
        print u'出错:','errorID=',errorID,'errorMsg=',errorMsg

    print 'test_QryContractBank():请求完成'

    assert errorID == 0 or errorMsg== u'CTP:无此权限',u'请求失败'

    print 'test_QryContractBank():执行结束'
    print '----------------------------------------------------------------------'



