# -*- coding: utf-8 -*-



class CThostFtdcTransferQryDetailRspField:
    '''
    查询银行交易明细请求响应
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        TradeCode 交易代码 char[7] 
        
        FutureSerial 期货流水号 int
        
        FutureID 期货公司代码 char[11] 
        
        FutureAccount 资金帐号 char[22] 
        
        BankSerial 银行流水号 int
        
        BankID 银行代码 char[4] 
        
        BankBrchID 银行分中心代码 char[5] 
        
        BankAccount 银行账号 char[41] 
        
        CertCode 证件号码 char[21] 
        
        CurrencyCode 货币代码 char[4] 
        
        TxAmount 发生金额 double
        
        Flag 有效标志 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''交易代码'''
        self.TradeCode = None
    
        '''期货流水号'''
        self.FutureSerial = None
    
        '''期货公司代码'''
        self.FutureID = None
    
        '''资金帐号'''
        self.FutureAccount = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分中心代码'''
        self.BankBrchID = None
    
        '''银行账号'''
        self.BankAccount = None
    
        '''证件号码'''
        self.CertCode = None
    
        '''货币代码'''
        self.CurrencyCode = None
    
        '''发生金额'''
        self.TxAmount = None
    
        '''有效标志'''
        self.Flag = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorAccountField:
    '''
    投资者账户
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        AccountID 投资者帐号 char[13] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcNoticeField:
    '''
    客户通知
        
        BrokerID 经纪公司代码 char[11] 
        
        Content 消息正文 char[501] 
        
        SequenceLabel 经纪公司通知内容序列号 char[2] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''消息正文'''
        self.Content = None
    
        '''经纪公司通知内容序列号'''
        self.SequenceLabel = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryCommRateModelField:
    '''
    请求查询投资者手续费率模板
        
        BrokerID 经纪公司代码 char[11] 
        
        CommModelID 手续费率模板代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''手续费率模板代码'''
        self.CommModelID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcOpenAccountField:
    '''
    银期开户信息
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        Gender 性别 char
        
        CountryCode 国家代码 char[21] 
        
        CustType 客户类型 char
        
        Address 地址 char[101] 
        
        ZipCode 邮编 char[7] 
        
        Telephone 电话号码 char[41] 
        
        MobilePhone 手机 char[21] 
        
        Fax 传真 char[41] 
        
        EMail 电子邮件 char[41] 
        
        MoneyAccountStatus 资金账户状态 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        CashExchangeCode 汇钞标志 char
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        TID 交易ID int
        
        UserID 用户标识 char[16] 
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''性别'''
        self.Gender = None
    
        '''国家代码'''
        self.CountryCode = None
    
        '''客户类型'''
        self.CustType = None
    
        '''地址'''
        self.Address = None
    
        '''邮编'''
        self.ZipCode = None
    
        '''电话号码'''
        self.Telephone = None
    
        '''手机'''
        self.MobilePhone = None
    
        '''传真'''
        self.Fax = None
    
        '''电子邮件'''
        self.EMail = None
    
        '''资金账户状态'''
        self.MoneyAccountStatus = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''汇钞标志'''
        self.CashExchangeCode = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''交易ID'''
        self.TID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerSyncField:
    '''
    经纪公司同步
        
        BrokerID 经纪公司代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInvestorPositionField:
    '''
    查询投资者持仓
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarginModelField:
    '''
    投资者保证金率模板
        
        BrokerID 经纪公司代码 char[11] 
        
        MarginModelID 保证金率模板代码 char[13] 
        
        MarginModelName 模板名称 char[161] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''保证金率模板代码'''
        self.MarginModelID = None
    
        '''模板名称'''
        self.MarginModelName = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspAuthenticateField:
    '''
    客户端认证响应
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        UserProductInfo 用户端产品信息 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInstrumentField:
    '''
    合约
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        InstrumentName 合约名称 char[21] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        ProductID 产品代码 char[31] 
        
        ProductClass 产品类型 char
        
        DeliveryYear 交割年份 int
        
        DeliveryMonth 交割月 int
        
        MaxMarketOrderVolume 市价单最大下单量 int
        
        MinMarketOrderVolume 市价单最小下单量 int
        
        MaxLimitOrderVolume 限价单最大下单量 int
        
        MinLimitOrderVolume 限价单最小下单量 int
        
        VolumeMultiple 合约数量乘数 int
        
        PriceTick 最小变动价位 double
        
        CreateDate 创建日 char[9] 
        
        OpenDate 上市日 char[9] 
        
        ExpireDate 到期日 char[9] 
        
        StartDelivDate 开始交割日 char[9] 
        
        EndDelivDate 结束交割日 char[9] 
        
        InstLifePhase 合约生命周期状态 char
        
        IsTrading 当前是否交易 int
        
        PositionType 持仓类型 char
        
        PositionDateType 持仓日期类型 char
        
        LongMarginRatio 多头保证金率 double
        
        ShortMarginRatio 空头保证金率 double
        
        MaxMarginSideAlgorithm 是否使用大额单边保证金算法 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约名称'''
        self.InstrumentName = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''产品代码'''
        self.ProductID = None
    
        '''产品类型'''
        self.ProductClass = None
    
        '''交割年份'''
        self.DeliveryYear = None
    
        '''交割月'''
        self.DeliveryMonth = None
    
        '''市价单最大下单量'''
        self.MaxMarketOrderVolume = None
    
        '''市价单最小下单量'''
        self.MinMarketOrderVolume = None
    
        '''限价单最大下单量'''
        self.MaxLimitOrderVolume = None
    
        '''限价单最小下单量'''
        self.MinLimitOrderVolume = None
    
        '''合约数量乘数'''
        self.VolumeMultiple = None
    
        '''最小变动价位'''
        self.PriceTick = None
    
        '''创建日'''
        self.CreateDate = None
    
        '''上市日'''
        self.OpenDate = None
    
        '''到期日'''
        self.ExpireDate = None
    
        '''开始交割日'''
        self.StartDelivDate = None
    
        '''结束交割日'''
        self.EndDelivDate = None
    
        '''合约生命周期状态'''
        self.InstLifePhase = None
    
        '''当前是否交易'''
        self.IsTrading = None
    
        '''持仓类型'''
        self.PositionType = None
    
        '''持仓日期类型'''
        self.PositionDateType = None
    
        '''多头保证金率'''
        self.LongMarginRatio = None
    
        '''空头保证金率'''
        self.ShortMarginRatio = None
    
        '''是否使用大额单边保证金算法'''
        self.MaxMarginSideAlgorithm = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingAccountReserveField:
    '''
    资金账户基本准备金
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        Reserve 基本准备金 double
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''基本准备金'''
        self.Reserve = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorGroupField:
    '''
    投资者组
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorGroupID 投资者分组代码 char[13] 
        
        InvestorGroupName 投资者分组名称 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者分组代码'''
        self.InvestorGroupID = None
    
        '''投资者分组名称'''
        self.InvestorGroupName = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcDiscountField:
    '''
    会员资金折扣
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorRange 投资者范围 char
        
        InvestorID 投资者代码 char[13] 
        
        Discount 资金折扣比例 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''资金折扣比例'''
        self.Discount = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcFensUserInfoField:
    '''
    Fens用户信息
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        LoginMode 登录模式 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''登录模式'''
        self.LoginMode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerUserField:
    '''
    经纪公司用户
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        UserName 用户名称 char[81] 
        
        UserType 用户类型 char
        
        IsActive 是否活跃 int
        
        IsUsingOTP 是否使用令牌 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''用户名称'''
        self.UserName = None
    
        '''用户类型'''
        self.UserType = None
    
        '''是否活跃'''
        self.IsActive = None
    
        '''是否使用令牌'''
        self.IsUsingOTP = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryOrderField:
    '''
    查询报单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        InsertTimeStart 开始时间 char[9] 
        
        InsertTimeEnd 结束时间 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''开始时间'''
        self.InsertTimeStart = None
    
        '''结束时间'''
        self.InsertTimeEnd = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeField:
    '''
    交易所
        
        ExchangeID 交易所代码 char[9] 
        
        ExchangeName 交易所名称 char[61] 
        
        ExchangeProperty 交易所属性 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''交易所名称'''
        self.ExchangeName = None
    
        '''交易所属性'''
        self.ExchangeProperty = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcLoginForbiddenUserField:
    '''
    禁止登录用户
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCancelAccountField:
    '''
    银期销户信息
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        Gender 性别 char
        
        CountryCode 国家代码 char[21] 
        
        CustType 客户类型 char
        
        Address 地址 char[101] 
        
        ZipCode 邮编 char[7] 
        
        Telephone 电话号码 char[41] 
        
        MobilePhone 手机 char[21] 
        
        Fax 传真 char[41] 
        
        EMail 电子邮件 char[41] 
        
        MoneyAccountStatus 资金账户状态 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        CashExchangeCode 汇钞标志 char
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        TID 交易ID int
        
        UserID 用户标识 char[16] 
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''性别'''
        self.Gender = None
    
        '''国家代码'''
        self.CountryCode = None
    
        '''客户类型'''
        self.CustType = None
    
        '''地址'''
        self.Address = None
    
        '''邮编'''
        self.ZipCode = None
    
        '''电话号码'''
        self.Telephone = None
    
        '''手机'''
        self.MobilePhone = None
    
        '''传真'''
        self.Fax = None
    
        '''电子邮件'''
        self.EMail = None
    
        '''资金账户状态'''
        self.MoneyAccountStatus = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''汇钞标志'''
        self.CashExchangeCode = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''交易ID'''
        self.TID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferHeaderField:
    '''
    银期转帐报文头
        
        Version 版本号，常量，1.0 char[4] 
        
        TradeCode 交易代码，必填 char[7] 
        
        TradeDate 交易日期，必填，格式：yyyymmdd char[9] 
        
        TradeTime 交易时间，必填，格式：hhmmss char[9] 
        
        TradeSerial 发起方流水号，N/A char[9] 
        
        FutureID 期货公司代码，必填 char[11] 
        
        BankID 银行代码，根据查询银行得到，必填 char[4] 
        
        BankBrchID 银行分中心代码，根据查询银行得到，必填 char[5] 
        
        OperNo 操作员，N/A char[17] 
        
        DeviceID 交易设备类型，N/A char[3] 
        
        RecordNum 记录数，N/A char[7] 
        
        SessionID 会话编号，N/A int
        
        RequestID 请求编号，N/A int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''版本号，常量，1.0'''
        self.Version = None
    
        '''交易代码，必填'''
        self.TradeCode = None
    
        '''交易日期，必填，格式：yyyymmdd'''
        self.TradeDate = None
    
        '''交易时间，必填，格式：hhmmss'''
        self.TradeTime = None
    
        '''发起方流水号，N/A'''
        self.TradeSerial = None
    
        '''期货公司代码，必填'''
        self.FutureID = None
    
        '''银行代码，根据查询银行得到，必填'''
        self.BankID = None
    
        '''银行分中心代码，根据查询银行得到，必填'''
        self.BankBrchID = None
    
        '''操作员，N/A'''
        self.OperNo = None
    
        '''交易设备类型，N/A'''
        self.DeviceID = None
    
        '''记录数，N/A'''
        self.RecordNum = None
    
        '''会话编号，N/A'''
        self.SessionID = None
    
        '''请求编号，N/A'''
        self.RequestID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcFrontStatusField:
    '''
    前置状态
        
        FrontID 前置编号 int
        
        LastReportDate 上次报告日期 char[9] 
        
        LastReportTime 上次报告时间 char[9] 
        
        IsActive 是否活跃 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''前置编号'''
        self.FrontID = None
    
        '''上次报告日期'''
        self.LastReportDate = None
    
        '''上次报告时间'''
        self.LastReportTime = None
    
        '''是否活跃'''
        self.IsActive = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorPositionField:
    '''
    投资者持仓
        
        InstrumentID 合约代码 char[31] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        PosiDirection 持仓多空方向 char
        
        HedgeFlag 投机套保标志 char
        
        PositionDate 持仓日期 char
        
        YdPosition 上日持仓 int
        
        Position 今日持仓 int
        
        LongFrozen 多头冻结 int
        
        ShortFrozen 空头冻结 int
        
        LongFrozenAmount 开仓冻结金额 double
        
        ShortFrozenAmount 开仓冻结金额 double
        
        OpenVolume 开仓量 int
        
        CloseVolume 平仓量 int
        
        OpenAmount 开仓金额 double
        
        CloseAmount 平仓金额 double
        
        PositionCost 持仓成本 double
        
        PreMargin 上次占用的保证金 double
        
        UseMargin 占用的保证金 double
        
        FrozenMargin 冻结的保证金 double
        
        FrozenCash 冻结的资金 double
        
        FrozenCommission 冻结的手续费 double
        
        CashIn 资金差额 double
        
        Commission 手续费 double
        
        CloseProfit 平仓盈亏 double
        
        PositionProfit 持仓盈亏 double
        
        PreSettlementPrice 上次结算价 double
        
        SettlementPrice 本次结算价 double
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        OpenCost 开仓成本 double
        
        ExchangeMargin 交易所保证金 double
        
        CombPosition 组合成交形成的持仓 int
        
        CombLongFrozen 组合多头冻结 int
        
        CombShortFrozen 组合空头冻结 int
        
        CloseProfitByDate 逐日盯市平仓盈亏 double
        
        CloseProfitByTrade 逐笔对冲平仓盈亏 double
        
        TodayPosition 今日持仓 int
        
        MarginRateByMoney 保证金率 double
        
        MarginRateByVolume 保证金率(按手数) double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''持仓多空方向'''
        self.PosiDirection = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''持仓日期'''
        self.PositionDate = None
    
        '''上日持仓'''
        self.YdPosition = None
    
        '''今日持仓'''
        self.Position = None
    
        '''多头冻结'''
        self.LongFrozen = None
    
        '''空头冻结'''
        self.ShortFrozen = None
    
        '''开仓冻结金额'''
        self.LongFrozenAmount = None
    
        '''开仓冻结金额'''
        self.ShortFrozenAmount = None
    
        '''开仓量'''
        self.OpenVolume = None
    
        '''平仓量'''
        self.CloseVolume = None
    
        '''开仓金额'''
        self.OpenAmount = None
    
        '''平仓金额'''
        self.CloseAmount = None
    
        '''持仓成本'''
        self.PositionCost = None
    
        '''上次占用的保证金'''
        self.PreMargin = None
    
        '''占用的保证金'''
        self.UseMargin = None
    
        '''冻结的保证金'''
        self.FrozenMargin = None
    
        '''冻结的资金'''
        self.FrozenCash = None
    
        '''冻结的手续费'''
        self.FrozenCommission = None
    
        '''资金差额'''
        self.CashIn = None
    
        '''手续费'''
        self.Commission = None
    
        '''平仓盈亏'''
        self.CloseProfit = None
    
        '''持仓盈亏'''
        self.PositionProfit = None
    
        '''上次结算价'''
        self.PreSettlementPrice = None
    
        '''本次结算价'''
        self.SettlementPrice = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''开仓成本'''
        self.OpenCost = None
    
        '''交易所保证金'''
        self.ExchangeMargin = None
    
        '''组合成交形成的持仓'''
        self.CombPosition = None
    
        '''组合多头冻结'''
        self.CombLongFrozen = None
    
        '''组合空头冻结'''
        self.CombShortFrozen = None
    
        '''逐日盯市平仓盈亏'''
        self.CloseProfitByDate = None
    
        '''逐笔对冲平仓盈亏'''
        self.CloseProfitByTrade = None
    
        '''今日持仓'''
        self.TodayPosition = None
    
        '''保证金率'''
        self.MarginRateByMoney = None
    
        '''保证金率(按手数)'''
        self.MarginRateByVolume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySyncFundMortgageField:
    '''
    查询货币质押流水
        
        BrokerID 经纪公司代码 char[11] 
        
        MortgageSeqNo 货币质押流水号 char[15] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''货币质押流水号'''
        self.MortgageSeqNo = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryExchangeSequenceField:
    '''
    查询交易所状态
        
        ExchangeID 交易所代码 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryLinkManField:
    '''
    查询联系人
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTransferSerialField:
    '''
    请求查询转帐流水
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        BankID 银行编码 char[4] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''银行编码'''
        self.BankID = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeOrderActionErrorField:
    '''
    交易所报单操作失败
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ActionLocalID 操作本地编号 char[13] 
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''操作本地编号'''
        self.ActionLocalID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqAuthenticateField:
    '''
    客户端认证请求
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        UserProductInfo 用户端产品信息 char[11] 
        
        AuthCode 认证码 char[17] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
    
        '''认证码'''
        self.AuthCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryHisOrderField:
    '''
    查询报单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        InsertTimeStart 开始时间 char[9] 
        
        InsertTimeEnd 结束时间 char[9] 
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''开始时间'''
        self.InsertTimeStart = None
    
        '''结束时间'''
        self.InsertTimeEnd = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingInstrumentTradingRightField:
    '''
    正在同步中的合约交易权限
        
        InstrumentID 合约代码 char[31] 
        
        InvestorRange 投资者范围 char
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        TradingRight 交易权限 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易权限'''
        self.TradingRight = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTradingCodeField:
    '''
    查询交易编码
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ExchangeID 交易所代码 char[9] 
        
        ClientID 客户代码 char[11] 
        
        ClientIDType 交易编码类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''交易编码类型'''
        self.ClientIDType = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspUserLoginField:
    '''
    用户登录应答
        
        TradingDay 交易日 char[9] 
        
        LoginTime 登录成功时间 char[9] 
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        SystemName 交易系统名称 char[41] 
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        MaxOrderRef 最大报单引用 char[13] 
        
        SHFETime 上期所时间 char[9] 
        
        DCETime 大商所时间 char[9] 
        
        CZCETime 郑商所时间 char[9] 
        
        FFEXTime 中金所时间 char[9] 
        
        INETime 能源中心时间 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''登录成功时间'''
        self.LoginTime = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''交易系统名称'''
        self.SystemName = None
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''最大报单引用'''
        self.MaxOrderRef = None
    
        '''上期所时间'''
        self.SHFETime = None
    
        '''大商所时间'''
        self.DCETime = None
    
        '''郑商所时间'''
        self.CZCETime = None
    
        '''中金所时间'''
        self.FFEXTime = None
    
        '''能源中心时间'''
        self.INETime = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCommPhaseField:
    '''
    通讯阶段
        
        TradingDay 交易日 char[9] 
        
        CommPhaseNo 通讯时段编号 short
        
        SystemID 系统编号 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''通讯时段编号'''
        self.CommPhaseNo = None
    
        '''系统编号'''
        self.SystemID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcLoginInfoField:
    '''
    登录信息
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        LoginDate 登录日期 char[9] 
        
        LoginTime 登录时间 char[9] 
        
        IPAddress IP地址 char[16] 
        
        UserProductInfo 用户端产品信息 char[11] 
        
        InterfaceProductInfo 接口端产品信息 char[11] 
        
        ProtocolInfo 协议信息 char[11] 
        
        SystemName 系统名称 char[41] 
        
        Password 密码 char[41] 
        
        MaxOrderRef 最大报单引用 char[13] 
        
        SHFETime 上期所时间 char[9] 
        
        DCETime 大商所时间 char[9] 
        
        CZCETime 郑商所时间 char[9] 
        
        FFEXTime 中金所时间 char[9] 
        
        MacAddress Mac地址 char[21] 
        
        OneTimePassword 动态密码 char[41] 
        
        INETime 能源中心时间 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''登录日期'''
        self.LoginDate = None
    
        '''登录时间'''
        self.LoginTime = None
    
        '''IP地址'''
        self.IPAddress = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
    
        '''接口端产品信息'''
        self.InterfaceProductInfo = None
    
        '''协议信息'''
        self.ProtocolInfo = None
    
        '''系统名称'''
        self.SystemName = None
    
        '''密码'''
        self.Password = None
    
        '''最大报单引用'''
        self.MaxOrderRef = None
    
        '''上期所时间'''
        self.SHFETime = None
    
        '''大商所时间'''
        self.DCETime = None
    
        '''郑商所时间'''
        self.CZCETime = None
    
        '''中金所时间'''
        self.FFEXTime = None
    
        '''Mac地址'''
        self.MacAddress = None
    
        '''动态密码'''
        self.OneTimePassword = None
    
        '''能源中心时间'''
        self.INETime = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySecAgentACIDMapField:
    '''
    二级代理操作员银期权限查询
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        AccountID 资金账户 char[13] 
        
        CurrencyID 币种 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''资金账户'''
        self.AccountID = None
    
        '''币种'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInvestorPositionDetailField:
    '''
    查询投资者持仓明细
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorPositionDetailField:
    '''
    投资者持仓明细
        
        InstrumentID 合约代码 char[31] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        HedgeFlag 投机套保标志 char
        
        Direction 买卖 char
        
        OpenDate 开仓日期 char[9] 
        
        TradeID 成交编号 char[21] 
        
        Volume 数量 int
        
        OpenPrice 开仓价 double
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        TradeType 成交类型 char
        
        CombInstrumentID 组合合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        CloseProfitByDate 逐日盯市平仓盈亏 double
        
        CloseProfitByTrade 逐笔对冲平仓盈亏 double
        
        PositionProfitByDate 逐日盯市持仓盈亏 double
        
        PositionProfitByTrade 逐笔对冲持仓盈亏 double
        
        Margin 投资者保证金 double
        
        ExchMargin 交易所保证金 double
        
        MarginRateByMoney 保证金率 double
        
        MarginRateByVolume 保证金率(按手数) double
        
        LastSettlementPrice 昨结算价 double
        
        SettlementPrice 结算价 double
        
        CloseVolume 平仓量 int
        
        CloseAmount 平仓金额 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''买卖'''
        self.Direction = None
    
        '''开仓日期'''
        self.OpenDate = None
    
        '''成交编号'''
        self.TradeID = None
    
        '''数量'''
        self.Volume = None
    
        '''开仓价'''
        self.OpenPrice = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''成交类型'''
        self.TradeType = None
    
        '''组合合约代码'''
        self.CombInstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''逐日盯市平仓盈亏'''
        self.CloseProfitByDate = None
    
        '''逐笔对冲平仓盈亏'''
        self.CloseProfitByTrade = None
    
        '''逐日盯市持仓盈亏'''
        self.PositionProfitByDate = None
    
        '''逐笔对冲持仓盈亏'''
        self.PositionProfitByTrade = None
    
        '''投资者保证金'''
        self.Margin = None
    
        '''交易所保证金'''
        self.ExchMargin = None
    
        '''保证金率'''
        self.MarginRateByMoney = None
    
        '''保证金率(按手数)'''
        self.MarginRateByVolume = None
    
        '''昨结算价'''
        self.LastSettlementPrice = None
    
        '''结算价'''
        self.SettlementPrice = None
    
        '''平仓量'''
        self.CloseVolume = None
    
        '''平仓金额'''
        self.CloseAmount = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeOrderField:
    '''
    交易所报单
        
        OrderPriceType 报单价格条件 char
        
        Direction 买卖方向 char
        
        CombOffsetFlag 组合开平标志 char[5] 
        
        CombHedgeFlag 组合投机套保标志 char[5] 
        
        LimitPrice 价格 double
        
        VolumeTotalOriginal 数量 int
        
        TimeCondition 有效期类型 char
        
        GTDDate GTD日期 char[9] 
        
        VolumeCondition 成交量类型 char
        
        MinVolume 最小成交量 int
        
        ContingentCondition 触发条件 char
        
        StopPrice 止损价 double
        
        ForceCloseReason 强平原因 char
        
        IsAutoSuspend 自动挂起标志 int
        
        BusinessUnit 业务单元 char[21] 
        
        RequestID 请求编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderSubmitStatus 报单提交状态 char
        
        NotifySequence 报单提示序号 int
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        OrderSysID 报单编号 char[21] 
        
        OrderSource 报单来源 char
        
        OrderStatus 报单状态 char
        
        OrderType 报单类型 char
        
        VolumeTraded 今成交数量 int
        
        VolumeTotal 剩余数量 int
        
        InsertDate 报单日期 char[9] 
        
        InsertTime 委托时间 char[9] 
        
        ActiveTime 激活时间 char[9] 
        
        SuspendTime 挂起时间 char[9] 
        
        UpdateTime 最后修改时间 char[9] 
        
        CancelTime 撤销时间 char[9] 
        
        ActiveTraderID 最后修改交易所交易员代码 char[21] 
        
        ClearingPartID 结算会员编号 char[11] 
        
        SequenceNo 序号 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''报单价格条件'''
        self.OrderPriceType = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''组合开平标志'''
        self.CombOffsetFlag = None
    
        '''组合投机套保标志'''
        self.CombHedgeFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量'''
        self.VolumeTotalOriginal = None
    
        '''有效期类型'''
        self.TimeCondition = None
    
        '''GTD日期'''
        self.GTDDate = None
    
        '''成交量类型'''
        self.VolumeCondition = None
    
        '''最小成交量'''
        self.MinVolume = None
    
        '''触发条件'''
        self.ContingentCondition = None
    
        '''止损价'''
        self.StopPrice = None
    
        '''强平原因'''
        self.ForceCloseReason = None
    
        '''自动挂起标志'''
        self.IsAutoSuspend = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''报单提交状态'''
        self.OrderSubmitStatus = None
    
        '''报单提示序号'''
        self.NotifySequence = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''报单来源'''
        self.OrderSource = None
    
        '''报单状态'''
        self.OrderStatus = None
    
        '''报单类型'''
        self.OrderType = None
    
        '''今成交数量'''
        self.VolumeTraded = None
    
        '''剩余数量'''
        self.VolumeTotal = None
    
        '''报单日期'''
        self.InsertDate = None
    
        '''委托时间'''
        self.InsertTime = None
    
        '''激活时间'''
        self.ActiveTime = None
    
        '''挂起时间'''
        self.SuspendTime = None
    
        '''最后修改时间'''
        self.UpdateTime = None
    
        '''撤销时间'''
        self.CancelTime = None
    
        '''最后修改交易所交易员代码'''
        self.ActiveTraderID = None
    
        '''结算会员编号'''
        self.ClearingPartID = None
    
        '''序号'''
        self.SequenceNo = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspQueryAccountField:
    '''
    查询账户信息响应
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        FutureSerial 期货公司流水号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        BankUseAmount 银行可用金额 double
        
        BankFetchAmount 银行可取金额 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''银行可用金额'''
        self.BankUseAmount = None
    
        '''银行可取金额'''
        self.BankFetchAmount = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySettlementInfoConfirmField:
    '''
    查询结算信息确认域
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorProductGroupMarginField:
    '''
    投资者品种/跨品种保证金
        
        ProductGroupID 品种/跨品种标示 char[31] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        FrozenMargin 冻结的保证金 double
        
        LongFrozenMargin 多头冻结的保证金 double
        
        ShortFrozenMargin 空头冻结的保证金 double
        
        UseMargin 占用的保证金 double
        
        LongUseMargin 多头保证金 double
        
        ShortUseMargin 空头保证金 double
        
        ExchMargin 交易所保证金 double
        
        LongExchMargin 交易所多头保证金 double
        
        ShortExchMargin 交易所空头保证金 double
        
        CloseProfit 平仓盈亏 double
        
        FrozenCommission 冻结的手续费 double
        
        Commission 手续费 double
        
        FrozenCash 冻结的资金 double
        
        CashIn 资金差额 double
        
        PositionProfit 持仓盈亏 double
        
        OffsetAmount 折抵总金额 double
        
        LongOffsetAmount 多头折抵总金额 double
        
        ShortOffsetAmount 空头折抵总金额 double
        
        ExchOffsetAmount 交易所折抵总金额 double
        
        LongExchOffsetAmount 交易所多头折抵总金额 double
        
        ShortExchOffsetAmount 交易所空头折抵总金额 double
        
        HedgeFlag 投机套保标志 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''品种/跨品种标示'''
        self.ProductGroupID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''冻结的保证金'''
        self.FrozenMargin = None
    
        '''多头冻结的保证金'''
        self.LongFrozenMargin = None
    
        '''空头冻结的保证金'''
        self.ShortFrozenMargin = None
    
        '''占用的保证金'''
        self.UseMargin = None
    
        '''多头保证金'''
        self.LongUseMargin = None
    
        '''空头保证金'''
        self.ShortUseMargin = None
    
        '''交易所保证金'''
        self.ExchMargin = None
    
        '''交易所多头保证金'''
        self.LongExchMargin = None
    
        '''交易所空头保证金'''
        self.ShortExchMargin = None
    
        '''平仓盈亏'''
        self.CloseProfit = None
    
        '''冻结的手续费'''
        self.FrozenCommission = None
    
        '''手续费'''
        self.Commission = None
    
        '''冻结的资金'''
        self.FrozenCash = None
    
        '''资金差额'''
        self.CashIn = None
    
        '''持仓盈亏'''
        self.PositionProfit = None
    
        '''折抵总金额'''
        self.OffsetAmount = None
    
        '''多头折抵总金额'''
        self.LongOffsetAmount = None
    
        '''空头折抵总金额'''
        self.ShortOffsetAmount = None
    
        '''交易所折抵总金额'''
        self.ExchOffsetAmount = None
    
        '''交易所多头折抵总金额'''
        self.LongExchOffsetAmount = None
    
        '''交易所空头折抵总金额'''
        self.ShortExchOffsetAmount = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTradingNoticeField:
    '''
    查询交易事件通知
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryErrOrderField:
    '''
    查询错误报单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcManualSyncBrokerUserOTPField:
    '''
    手工同步用户动态令牌
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        OTPType 动态令牌类型 char
        
        FirstOTP 第一个动态密码 char[41] 
        
        SecondOTP 第二个动态密码 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''动态令牌类型'''
        self.OTPType = None
    
        '''第一个动态密码'''
        self.FirstOTP = None
    
        '''第二个动态密码'''
        self.SecondOTP = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcDepthMarketDataField:
    '''
    深度行情
        
        TradingDay 交易日 char[9] 
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        LastPrice 最新价 double
        
        PreSettlementPrice 上次结算价 double
        
        PreClosePrice 昨收盘 double
        
        PreOpenInterest 昨持仓量 double
        
        OpenPrice 今开盘 double
        
        HighestPrice 最高价 double
        
        LowestPrice 最低价 double
        
        Volume 数量 int
        
        Turnover 成交金额 double
        
        OpenInterest 持仓量 double
        
        ClosePrice 今收盘 double
        
        SettlementPrice 本次结算价 double
        
        UpperLimitPrice 涨停板价 double
        
        LowerLimitPrice 跌停板价 double
        
        PreDelta 昨虚实度 double
        
        CurrDelta 今虚实度 double
        
        UpdateTime 最后修改时间 char[9] 
        
        UpdateMillisec 最后修改毫秒 int
        
        BidPrice1 申买价一 double
        
        BidVolume1 申买量一 int
        
        AskPrice1 申卖价一 double
        
        AskVolume1 申卖量一 int
        
        BidPrice2 申买价二 double
        
        BidVolume2 申买量二 int
        
        AskPrice2 申卖价二 double
        
        AskVolume2 申卖量二 int
        
        BidPrice3 申买价三 double
        
        BidVolume3 申买量三 int
        
        AskPrice3 申卖价三 double
        
        AskVolume3 申卖量三 int
        
        BidPrice4 申买价四 double
        
        BidVolume4 申买量四 int
        
        AskPrice4 申卖价四 double
        
        AskVolume4 申卖量四 int
        
        BidPrice5 申买价五 double
        
        BidVolume5 申买量五 int
        
        AskPrice5 申卖价五 double
        
        AskVolume5 申卖量五 int
        
        AveragePrice 当日均价 double
        
        ActionDay 业务日期 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''最新价'''
        self.LastPrice = None
    
        '''上次结算价'''
        self.PreSettlementPrice = None
    
        '''昨收盘'''
        self.PreClosePrice = None
    
        '''昨持仓量'''
        self.PreOpenInterest = None
    
        '''今开盘'''
        self.OpenPrice = None
    
        '''最高价'''
        self.HighestPrice = None
    
        '''最低价'''
        self.LowestPrice = None
    
        '''数量'''
        self.Volume = None
    
        '''成交金额'''
        self.Turnover = None
    
        '''持仓量'''
        self.OpenInterest = None
    
        '''今收盘'''
        self.ClosePrice = None
    
        '''本次结算价'''
        self.SettlementPrice = None
    
        '''涨停板价'''
        self.UpperLimitPrice = None
    
        '''跌停板价'''
        self.LowerLimitPrice = None
    
        '''昨虚实度'''
        self.PreDelta = None
    
        '''今虚实度'''
        self.CurrDelta = None
    
        '''最后修改时间'''
        self.UpdateTime = None
    
        '''最后修改毫秒'''
        self.UpdateMillisec = None
    
        '''申买价一'''
        self.BidPrice1 = None
    
        '''申买量一'''
        self.BidVolume1 = None
    
        '''申卖价一'''
        self.AskPrice1 = None
    
        '''申卖量一'''
        self.AskVolume1 = None
    
        '''申买价二'''
        self.BidPrice2 = None
    
        '''申买量二'''
        self.BidVolume2 = None
    
        '''申卖价二'''
        self.AskPrice2 = None
    
        '''申卖量二'''
        self.AskVolume2 = None
    
        '''申买价三'''
        self.BidPrice3 = None
    
        '''申买量三'''
        self.BidVolume3 = None
    
        '''申卖价三'''
        self.AskPrice3 = None
    
        '''申卖量三'''
        self.AskVolume3 = None
    
        '''申买价四'''
        self.BidPrice4 = None
    
        '''申买量四'''
        self.BidVolume4 = None
    
        '''申卖价四'''
        self.AskPrice4 = None
    
        '''申卖量四'''
        self.AskVolume4 = None
    
        '''申买价五'''
        self.BidPrice5 = None
    
        '''申买量五'''
        self.BidVolume5 = None
    
        '''申卖价五'''
        self.AskPrice5 = None
    
        '''申卖量五'''
        self.AskVolume5 = None
    
        '''当日均价'''
        self.AveragePrice = None
    
        '''业务日期'''
        self.ActionDay = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTraderOfferField:
    '''
    交易所交易员报盘机
        
        ExchangeID 交易所代码 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
        
        ParticipantID 会员代码 char[11] 
        
        Password 密码 char[41] 
        
        InstallID 安装编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        TraderConnectStatus 交易所交易员连接状态 char
        
        ConnectRequestDate 发出连接请求的日期 char[9] 
        
        ConnectRequestTime 发出连接请求的时间 char[9] 
        
        LastReportDate 上次报告日期 char[9] 
        
        LastReportTime 上次报告时间 char[9] 
        
        ConnectDate 完成连接日期 char[9] 
        
        ConnectTime 完成连接时间 char[9] 
        
        StartDate 启动日期 char[9] 
        
        StartTime 启动时间 char[9] 
        
        TradingDay 交易日 char[9] 
        
        BrokerID 经纪公司代码 char[11] 
        
        MaxTradeID 本席位最大成交编号 char[21] 
        
        MaxOrderMessageReference 本席位最大报单备拷 char[7] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''交易所交易员连接状态'''
        self.TraderConnectStatus = None
    
        '''发出连接请求的日期'''
        self.ConnectRequestDate = None
    
        '''发出连接请求的时间'''
        self.ConnectRequestTime = None
    
        '''上次报告日期'''
        self.LastReportDate = None
    
        '''上次报告时间'''
        self.LastReportTime = None
    
        '''完成连接日期'''
        self.ConnectDate = None
    
        '''完成连接时间'''
        self.ConnectTime = None
    
        '''启动日期'''
        self.StartDate = None
    
        '''启动时间'''
        self.StartTime = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''本席位最大成交编号'''
        self.MaxTradeID = None
    
        '''本席位最大报单备拷'''
        self.MaxOrderMessageReference = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCFMMCBrokerKeyField:
    '''
    保证金监管系统经纪公司密钥
        
        BrokerID 经纪公司代码 char[11] 
        
        ParticipantID 经纪公司统一编码 char[11] 
        
        CreateDate 密钥生成日期 char[9] 
        
        CreateTime 密钥生成时间 char[9] 
        
        KeyID 密钥编号 int
        
        CurrentKey 动态密钥 char[21] 
        
        KeyKind 动态密钥类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''经纪公司统一编码'''
        self.ParticipantID = None
    
        '''密钥生成日期'''
        self.CreateDate = None
    
        '''密钥生成时间'''
        self.CreateTime = None
    
        '''密钥编号'''
        self.KeyID = None
    
        '''动态密钥'''
        self.CurrentKey = None
    
        '''动态密钥类型'''
        self.KeyKind = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryDepthMarketDataField:
    '''
    查询行情
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferQryDetailReqField:
    '''
    查询银行交易明细请求，TradeCode=204999
        
        FutureAccount 期货资金账户 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''期货资金账户'''
        self.FutureAccount = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerWithdrawAlgorithmField:
    '''
    经纪公司可提资金算法表
        
        BrokerID 经纪公司代码 char[11] 
        
        WithdrawAlgorithm 可提资金算法 char
        
        UsingRatio 资金使用率 double
        
        IncludeCloseProfit 可提是否包含平仓盈利 char
        
        AllWithoutTrade 本日无仓且无成交客户是否受可提比例限制 char
        
        AvailIncludeCloseProfit 可用是否包含平仓盈利 char
        
        IsBrokerUserEvent 是否启用用户事件 int
        
        CurrencyID 币种代码 char[4] 
        
        FundMortgageRatio 货币质押比率 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''可提资金算法'''
        self.WithdrawAlgorithm = None
    
        '''资金使用率'''
        self.UsingRatio = None
    
        '''可提是否包含平仓盈利'''
        self.IncludeCloseProfit = None
    
        '''本日无仓且无成交客户是否受可提比例限制'''
        self.AllWithoutTrade = None
    
        '''可用是否包含平仓盈利'''
        self.AvailIncludeCloseProfit = None
    
        '''是否启用用户事件'''
        self.IsBrokerUserEvent = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''货币质押比率'''
        self.FundMortgageRatio = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataExchangeField:
    '''
    行情交易所代码属性
        
        ExchangeID 交易所代码 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeOrderInsertErrorField:
    '''
    交易所报单插入失败
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqQueryAccountField:
    '''
    查询账户信息请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        FutureSerial 期货公司流水号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySuperUserFunctionField:
    '''
    查询管理用户功能权限
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspRepealField:
    '''
    冲正响应
        
        RepealTimeInterval 冲正时间间隔 int
        
        RepealedTimes 已经冲正次数 int
        
        BankRepealFlag 银行冲正标志 char
        
        BrokerRepealFlag 期商冲正标志 char
        
        PlateRepealSerial 被冲正平台流水号 int
        
        BankRepealSerial 被冲正银行流水号 char[13] 
        
        FutureRepealSerial 被冲正期货流水号 int
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        FutureSerial 期货公司流水号 int
        
        UserID 用户标识 char[16] 
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        TradeAmount 转帐金额 double
        
        FutureFetchAmount 期货可取金额 double
        
        FeePayFlag 费用支付标志 char
        
        CustFee 应收客户费用 double
        
        BrokerFee 应收期货公司费用 double
        
        Message 发送方给接收方的消息 char[129] 
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        TransferStatus 转账交易状态 char
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''冲正时间间隔'''
        self.RepealTimeInterval = None
    
        '''已经冲正次数'''
        self.RepealedTimes = None
    
        '''银行冲正标志'''
        self.BankRepealFlag = None
    
        '''期商冲正标志'''
        self.BrokerRepealFlag = None
    
        '''被冲正平台流水号'''
        self.PlateRepealSerial = None
    
        '''被冲正银行流水号'''
        self.BankRepealSerial = None
    
        '''被冲正期货流水号'''
        self.FutureRepealSerial = None
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''用户标识'''
        self.UserID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''转帐金额'''
        self.TradeAmount = None
    
        '''期货可取金额'''
        self.FutureFetchAmount = None
    
        '''费用支付标志'''
        self.FeePayFlag = None
    
        '''应收客户费用'''
        self.CustFee = None
    
        '''应收期货公司费用'''
        self.BrokerFee = None
    
        '''发送方给接收方的消息'''
        self.Message = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''转账交易状态'''
        self.TransferStatus = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTradeField:
    '''
    查询成交
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        TradeID 成交编号 char[21] 
        
        TradeTimeStart 开始时间 char[9] 
        
        TradeTimeEnd 结束时间 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''成交编号'''
        self.TradeID = None
    
        '''开始时间'''
        self.TradeTimeStart = None
    
        '''结束时间'''
        self.TradeTimeEnd = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingNoticeInfoField:
    '''
    用户事件通知信息
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        SendTime 发送时间 char[9] 
        
        FieldContent 消息正文 char[501] 
        
        SequenceSeries 序列系列号 short
        
        SequenceNo 序列号 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''发送时间'''
        self.SendTime = None
    
        '''消息正文'''
        self.FieldContent = None
    
        '''序列系列号'''
        self.SequenceSeries = None
    
        '''序列号'''
        self.SequenceNo = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcErrOrderField:
    '''
    错误报单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        OrderRef 报单引用 char[13] 
        
        UserID 用户代码 char[16] 
        
        OrderPriceType 报单价格条件 char
        
        Direction 买卖方向 char
        
        CombOffsetFlag 组合开平标志 char[5] 
        
        CombHedgeFlag 组合投机套保标志 char[5] 
        
        LimitPrice 价格 double
        
        VolumeTotalOriginal 数量 int
        
        TimeCondition 有效期类型 char
        
        GTDDate GTD日期 char[9] 
        
        VolumeCondition 成交量类型 char
        
        MinVolume 最小成交量 int
        
        ContingentCondition 触发条件 char
        
        StopPrice 止损价 double
        
        ForceCloseReason 强平原因 char
        
        IsAutoSuspend 自动挂起标志 int
        
        BusinessUnit 业务单元 char[21] 
        
        RequestID 请求编号 int
        
        UserForceClose 用户强评标志 int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
        
        IsSwapOrder 互换单标志 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''用户代码'''
        self.UserID = None
    
        '''报单价格条件'''
        self.OrderPriceType = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''组合开平标志'''
        self.CombOffsetFlag = None
    
        '''组合投机套保标志'''
        self.CombHedgeFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量'''
        self.VolumeTotalOriginal = None
    
        '''有效期类型'''
        self.TimeCondition = None
    
        '''GTD日期'''
        self.GTDDate = None
    
        '''成交量类型'''
        self.VolumeCondition = None
    
        '''最小成交量'''
        self.MinVolume = None
    
        '''触发条件'''
        self.ContingentCondition = None
    
        '''止损价'''
        self.StopPrice = None
    
        '''强平原因'''
        self.ForceCloseReason = None
    
        '''自动挂起标志'''
        self.IsAutoSuspend = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''用户强评标志'''
        self.UserForceClose = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
    
        '''互换单标志'''
        self.IsSwapOrder = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcContractBankField:
    '''
    查询签约银行响应
        
        BrokerID 经纪公司代码 char[11] 
        
        BankID 银行代码 char[4] 
        
        BankBrchID 银行分中心代码 char[5] 
        
        BankName 银行名称 char[101] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分中心代码'''
        self.BankBrchID = None
    
        '''银行名称'''
        self.BankName = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryParkedOrderActionField:
    '''
    查询预埋撤单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcProductField:
    '''
    产品
        
        ProductID 产品代码 char[31] 
        
        ProductName 产品名称 char[21] 
        
        ExchangeID 交易所代码 char[9] 
        
        ProductClass 产品类型 char
        
        VolumeMultiple 合约数量乘数 int
        
        PriceTick 最小变动价位 double
        
        MaxMarketOrderVolume 市价单最大下单量 int
        
        MinMarketOrderVolume 市价单最小下单量 int
        
        MaxLimitOrderVolume 限价单最大下单量 int
        
        MinLimitOrderVolume 限价单最小下单量 int
        
        PositionType 持仓类型 char
        
        PositionDateType 持仓日期类型 char
        
        CloseDealType 平仓处理类型 char
        
        TradeCurrencyID 交易币种类型 char[4] 
        
        MortgageFundUseRange 质押资金可用范围 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''产品代码'''
        self.ProductID = None
    
        '''产品名称'''
        self.ProductName = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''产品类型'''
        self.ProductClass = None
    
        '''合约数量乘数'''
        self.VolumeMultiple = None
    
        '''最小变动价位'''
        self.PriceTick = None
    
        '''市价单最大下单量'''
        self.MaxMarketOrderVolume = None
    
        '''市价单最小下单量'''
        self.MinMarketOrderVolume = None
    
        '''限价单最大下单量'''
        self.MaxLimitOrderVolume = None
    
        '''限价单最小下单量'''
        self.MinLimitOrderVolume = None
    
        '''持仓类型'''
        self.PositionType = None
    
        '''持仓日期类型'''
        self.PositionDateType = None
    
        '''平仓处理类型'''
        self.CloseDealType = None
    
        '''交易币种类型'''
        self.TradeCurrencyID = None
    
        '''质押资金可用范围'''
        self.MortgageFundUseRange = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryCFMMCBrokerKeyField:
    '''
    查询保证金监管系统经纪公司密钥
        
        BrokerID 经纪公司代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerTradingAlgosField:
    '''
    经纪公司交易算法
        
        BrokerID 经纪公司代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
        
        InstrumentID 合约代码 char[31] 
        
        HandlePositionAlgoID 持仓处理算法编号 char
        
        FindMarginRateAlgoID 寻找保证金率算法编号 char
        
        HandleTradingAccountAlgoID 资金处理算法编号 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''持仓处理算法编号'''
        self.HandlePositionAlgoID = None
    
        '''寻找保证金率算法编号'''
        self.FindMarginRateAlgoID = None
    
        '''资金处理算法编号'''
        self.HandleTradingAccountAlgoID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferQryBankReqField:
    '''
    查询银行资金请求，TradeCode=204002
        
        FutureAccount 期货资金账户 char[13] 
        
        FuturePwdFlag 密码标志 char
        
        FutureAccPwd 密码 char[17] 
        
        CurrencyCode 币种：RMB-人民币 USD-美圆 HKD-港元 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''期货资金账户'''
        self.FutureAccount = None
    
        '''密码标志'''
        self.FuturePwdFlag = None
    
        '''密码'''
        self.FutureAccPwd = None
    
        '''币种：RMB-人民币 USD-美圆 HKD-港元'''
        self.CurrencyCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqChangeAccountField:
    '''
    变更银行账户请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        Gender 性别 char
        
        CountryCode 国家代码 char[21] 
        
        CustType 客户类型 char
        
        Address 地址 char[101] 
        
        ZipCode 邮编 char[7] 
        
        Telephone 电话号码 char[41] 
        
        MobilePhone 手机 char[21] 
        
        Fax 传真 char[41] 
        
        EMail 电子邮件 char[41] 
        
        MoneyAccountStatus 资金账户状态 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        NewBankAccount 新银行帐号 char[41] 
        
        NewBankPassWord 新银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        BankAccType 银行帐号类型 char
        
        InstallID 安装编号 int
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        TID 交易ID int
        
        Digest 摘要 char[36] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''性别'''
        self.Gender = None
    
        '''国家代码'''
        self.CountryCode = None
    
        '''客户类型'''
        self.CustType = None
    
        '''地址'''
        self.Address = None
    
        '''邮编'''
        self.ZipCode = None
    
        '''电话号码'''
        self.Telephone = None
    
        '''手机'''
        self.MobilePhone = None
    
        '''传真'''
        self.Fax = None
    
        '''电子邮件'''
        self.EMail = None
    
        '''资金账户状态'''
        self.MoneyAccountStatus = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''新银行帐号'''
        self.NewBankAccount = None
    
        '''新银行密码'''
        self.NewBankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易ID'''
        self.TID = None
    
        '''摘要'''
        self.Digest = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMulticastGroupInfoField:
    '''
    UDP组播组信息
        
        GroupIP 组播组IP地址 char[16] 
        
        GroupPort 组播组IP端口 int
        
        SourceIP 源地址 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''组播组IP地址'''
        self.GroupIP = None
    
        '''组播组IP端口'''
        self.GroupPort = None
    
        '''源地址'''
        self.SourceIP = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcAuthenticationInfoField:
    '''
    客户端认证信息
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        UserProductInfo 用户端产品信息 char[11] 
        
        AuthInfo 认证信息 char[129] 
        
        IsResult 是否为认证结果 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
    
        '''认证信息'''
        self.AuthInfo = None
    
        '''是否为认证结果'''
        self.IsResult = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferFutureToBankReqField:
    '''
    期货资金转银行请求，TradeCode=202002
        
        FutureAccount 期货资金账户 char[13] 
        
        FuturePwdFlag 密码标志 char
        
        FutureAccPwd 密码 char[17] 
        
        TradeAmt 转账金额 double
        
        CustFee 客户手续费 double
        
        CurrencyCode 币种：RMB-人民币 USD-美圆 HKD-港元 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''期货资金账户'''
        self.FutureAccount = None
    
        '''密码标志'''
        self.FuturePwdFlag = None
    
        '''密码'''
        self.FutureAccPwd = None
    
        '''转账金额'''
        self.TradeAmt = None
    
        '''客户手续费'''
        self.CustFee = None
    
        '''币种：RMB-人民币 USD-美圆 HKD-港元'''
        self.CurrencyCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqCancelAccountField:
    '''
    转帐销户请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        Gender 性别 char
        
        CountryCode 国家代码 char[21] 
        
        CustType 客户类型 char
        
        Address 地址 char[101] 
        
        ZipCode 邮编 char[7] 
        
        Telephone 电话号码 char[41] 
        
        MobilePhone 手机 char[21] 
        
        Fax 传真 char[41] 
        
        EMail 电子邮件 char[41] 
        
        MoneyAccountStatus 资金账户状态 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        CashExchangeCode 汇钞标志 char
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        TID 交易ID int
        
        UserID 用户标识 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''性别'''
        self.Gender = None
    
        '''国家代码'''
        self.CountryCode = None
    
        '''客户类型'''
        self.CustType = None
    
        '''地址'''
        self.Address = None
    
        '''邮编'''
        self.ZipCode = None
    
        '''电话号码'''
        self.Telephone = None
    
        '''手机'''
        self.MobilePhone = None
    
        '''传真'''
        self.Fax = None
    
        '''电子邮件'''
        self.EMail = None
    
        '''资金账户状态'''
        self.MoneyAccountStatus = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''汇钞标志'''
        self.CashExchangeCode = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''交易ID'''
        self.TID = None
    
        '''用户标识'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataLastMatchField:
    '''
    行情最新成交属性
        
        LastPrice 最新价 double
        
        Volume 数量 int
        
        Turnover 成交金额 double
        
        OpenInterest 持仓量 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''最新价'''
        self.LastPrice = None
    
        '''数量'''
        self.Volume = None
    
        '''成交金额'''
        self.Turnover = None
    
        '''持仓量'''
        self.OpenInterest = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSuperUserFunctionField:
    '''
    管理用户功能权限
        
        UserID 用户代码 char[16] 
        
        FunctionCode 功能代码 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''用户代码'''
        self.UserID = None
    
        '''功能代码'''
        self.FunctionCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcParkedOrderActionField:
    '''
    输入预埋单操作
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        OrderActionRef 报单操作引用 int
        
        OrderRef 报单引用 char[13] 
        
        RequestID 请求编号 int
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        ActionFlag 操作标志 char
        
        LimitPrice 价格 double
        
        VolumeChange 数量变化 int
        
        UserID 用户代码 char[16] 
        
        InstrumentID 合约代码 char[31] 
        
        ParkedOrderActionID 预埋撤单单编号 char[13] 
        
        UserType 用户类型 char
        
        Status 预埋撤单状态 char
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''报单操作引用'''
        self.OrderActionRef = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''操作标志'''
        self.ActionFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量变化'''
        self.VolumeChange = None
    
        '''用户代码'''
        self.UserID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''预埋撤单单编号'''
        self.ParkedOrderActionID = None
    
        '''用户类型'''
        self.UserType = None
    
        '''预埋撤单状态'''
        self.Status = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcUserSessionField:
    '''
    用户会话
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        LoginDate 登录日期 char[9] 
        
        LoginTime 登录时间 char[9] 
        
        IPAddress IP地址 char[16] 
        
        UserProductInfo 用户端产品信息 char[11] 
        
        InterfaceProductInfo 接口端产品信息 char[11] 
        
        ProtocolInfo 协议信息 char[11] 
        
        MacAddress Mac地址 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''登录日期'''
        self.LoginDate = None
    
        '''登录时间'''
        self.LoginTime = None
    
        '''IP地址'''
        self.IPAddress = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
    
        '''接口端产品信息'''
        self.InterfaceProductInfo = None
    
        '''协议信息'''
        self.ProtocolInfo = None
    
        '''Mac地址'''
        self.MacAddress = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQueryMaxOrderVolumeWithPriceField:
    '''
    根据价格查询最大报单数量
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        Direction 买卖方向 char
        
        OffsetFlag 开平标志 char
        
        HedgeFlag 投机套保标志 char
        
        MaxVolume 最大允许报单数量 int
        
        Price 报单价格 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''开平标志'''
        self.OffsetFlag = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''最大允许报单数量'''
        self.MaxVolume = None
    
        '''报单价格'''
        self.Price = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferBankToFutureReqField:
    '''
    银行资金转期货请求，TradeCode=202001
        
        FutureAccount 期货资金账户 char[13] 
        
        FuturePwdFlag 密码标志 char
        
        FutureAccPwd 密码 char[17] 
        
        TradeAmt 转账金额 double
        
        CustFee 客户手续费 double
        
        CurrencyCode 币种：RMB-人民币 USD-美圆 HKD-港元 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''期货资金账户'''
        self.FutureAccount = None
    
        '''密码标志'''
        self.FuturePwdFlag = None
    
        '''密码'''
        self.FutureAccPwd = None
    
        '''转账金额'''
        self.TradeAmt = None
    
        '''客户手续费'''
        self.CustFee = None
    
        '''币种：RMB-人民币 USD-美圆 HKD-港元'''
        self.CurrencyCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInstrumentStatusField:
    '''
    合约状态
        
        ExchangeID 交易所代码 char[9] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        SettlementGroupID 结算组代码 char[9] 
        
        InstrumentID 合约代码 char[31] 
        
        InstrumentStatus 合约交易状态 char
        
        TradingSegmentSN 交易阶段编号 int
        
        EnterTime 进入本状态时间 char[9] 
        
        EnterReason 进入本状态原因 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''结算组代码'''
        self.SettlementGroupID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''合约交易状态'''
        self.InstrumentStatus = None
    
        '''交易阶段编号'''
        self.TradingSegmentSN = None
    
        '''进入本状态时间'''
        self.EnterTime = None
    
        '''进入本状态原因'''
        self.EnterReason = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSecAgentACIDMapField:
    '''
    二级代理操作员银期权限
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        AccountID 资金账户 char[13] 
        
        CurrencyID 币种 char[4] 
        
        BrokerSecAgentID 境外中介机构资金帐号 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''资金账户'''
        self.AccountID = None
    
        '''币种'''
        self.CurrencyID = None
    
        '''境外中介机构资金帐号'''
        self.BrokerSecAgentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryContractBankField:
    '''
    查询签约银行请求
        
        BrokerID 经纪公司代码 char[11] 
        
        BankID 银行代码 char[4] 
        
        BankBrchID 银行分中心代码 char[5] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分中心代码'''
        self.BankBrchID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcNotifyFutureSignInField:
    '''
    期商签到通知
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Digest 摘要 char[36] 
        
        CurrencyID 币种代码 char[4] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
        
        PinKey PIN密钥 char[129] 
        
        MacKey MAC密钥 char[129] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''摘要'''
        self.Digest = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
    
        '''PIN密钥'''
        self.PinKey = None
    
        '''MAC密钥'''
        self.MacKey = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingTradingCodeField:
    '''
    正在同步中的交易代码
        
        InvestorID 投资者代码 char[13] 
        
        BrokerID 经纪公司代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
        
        ClientID 客户代码 char[11] 
        
        IsActive 是否活跃 int
        
        ClientIDType 交易编码类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''是否活跃'''
        self.IsActive = None
    
        '''交易编码类型'''
        self.ClientIDType = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryEWarrantOffsetField:
    '''
    查询仓单折抵信息
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ExchangeID 交易所代码 char[9] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryBrokerTradingParamsField:
    '''
    查询经纪公司交易参数
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryLoginForbiddenUserField:
    '''
    查询禁止登录用户
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingTradingAccountField:
    '''
    正在同步中的交易账号
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        PreMortgage 上次质押金额 double
        
        PreCredit 上次信用额度 double
        
        PreDeposit 上次存款额 double
        
        PreBalance 上次结算准备金 double
        
        PreMargin 上次占用的保证金 double
        
        InterestBase 利息基数 double
        
        Interest 利息收入 double
        
        Deposit 入金金额 double
        
        Withdraw 出金金额 double
        
        FrozenMargin 冻结的保证金 double
        
        FrozenCash 冻结的资金 double
        
        FrozenCommission 冻结的手续费 double
        
        CurrMargin 当前保证金总额 double
        
        CashIn 资金差额 double
        
        Commission 手续费 double
        
        CloseProfit 平仓盈亏 double
        
        PositionProfit 持仓盈亏 double
        
        Balance 期货结算准备金 double
        
        Available 可用资金 double
        
        WithdrawQuota 可取资金 double
        
        Reserve 基本准备金 double
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        Credit 信用额度 double
        
        Mortgage 质押金额 double
        
        ExchangeMargin 交易所保证金 double
        
        DeliveryMargin 投资者交割保证金 double
        
        ExchangeDeliveryMargin 交易所交割保证金 double
        
        ReserveBalance 保底期货结算准备金 double
        
        CurrencyID 币种代码 char[4] 
        
        PreFundMortgageIn 上次货币质入金额 double
        
        PreFundMortgageOut 上次货币质出金额 double
        
        FundMortgageIn 货币质入金额 double
        
        FundMortgageOut 货币质出金额 double
        
        FundMortgageAvailable 货币质押余额 double
        
        MortgageableFund 可质押货币金额 double
        
        SpecProductMargin 特殊产品占用保证金 double
        
        SpecProductFrozenMargin 特殊产品冻结保证金 double
        
        SpecProductCommission 特殊产品手续费 double
        
        SpecProductFrozenCommission 特殊产品冻结手续费 double
        
        SpecProductPositionProfit 特殊产品持仓盈亏 double
        
        SpecProductCloseProfit 特殊产品平仓盈亏 double
        
        SpecProductPositionProfitByAlg 根据持仓盈亏算法计算的特殊产品持仓盈亏 double
        
        SpecProductExchangeMargin 特殊产品交易所保证金 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''上次质押金额'''
        self.PreMortgage = None
    
        '''上次信用额度'''
        self.PreCredit = None
    
        '''上次存款额'''
        self.PreDeposit = None
    
        '''上次结算准备金'''
        self.PreBalance = None
    
        '''上次占用的保证金'''
        self.PreMargin = None
    
        '''利息基数'''
        self.InterestBase = None
    
        '''利息收入'''
        self.Interest = None
    
        '''入金金额'''
        self.Deposit = None
    
        '''出金金额'''
        self.Withdraw = None
    
        '''冻结的保证金'''
        self.FrozenMargin = None
    
        '''冻结的资金'''
        self.FrozenCash = None
    
        '''冻结的手续费'''
        self.FrozenCommission = None
    
        '''当前保证金总额'''
        self.CurrMargin = None
    
        '''资金差额'''
        self.CashIn = None
    
        '''手续费'''
        self.Commission = None
    
        '''平仓盈亏'''
        self.CloseProfit = None
    
        '''持仓盈亏'''
        self.PositionProfit = None
    
        '''期货结算准备金'''
        self.Balance = None
    
        '''可用资金'''
        self.Available = None
    
        '''可取资金'''
        self.WithdrawQuota = None
    
        '''基本准备金'''
        self.Reserve = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''信用额度'''
        self.Credit = None
    
        '''质押金额'''
        self.Mortgage = None
    
        '''交易所保证金'''
        self.ExchangeMargin = None
    
        '''投资者交割保证金'''
        self.DeliveryMargin = None
    
        '''交易所交割保证金'''
        self.ExchangeDeliveryMargin = None
    
        '''保底期货结算准备金'''
        self.ReserveBalance = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''上次货币质入金额'''
        self.PreFundMortgageIn = None
    
        '''上次货币质出金额'''
        self.PreFundMortgageOut = None
    
        '''货币质入金额'''
        self.FundMortgageIn = None
    
        '''货币质出金额'''
        self.FundMortgageOut = None
    
        '''货币质押余额'''
        self.FundMortgageAvailable = None
    
        '''可质押货币金额'''
        self.MortgageableFund = None
    
        '''特殊产品占用保证金'''
        self.SpecProductMargin = None
    
        '''特殊产品冻结保证金'''
        self.SpecProductFrozenMargin = None
    
        '''特殊产品手续费'''
        self.SpecProductCommission = None
    
        '''特殊产品冻结手续费'''
        self.SpecProductFrozenCommission = None
    
        '''特殊产品持仓盈亏'''
        self.SpecProductPositionProfit = None
    
        '''特殊产品平仓盈亏'''
        self.SpecProductCloseProfit = None
    
        '''根据持仓盈亏算法计算的特殊产品持仓盈亏'''
        self.SpecProductPositionProfitByAlg = None
    
        '''特殊产品交易所保证金'''
        self.SpecProductExchangeMargin = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryExchangeOrderField:
    '''
    查询交易所报单
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcChangeAccountField:
    '''
    银期变更银行账号信息
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        Gender 性别 char
        
        CountryCode 国家代码 char[21] 
        
        CustType 客户类型 char
        
        Address 地址 char[101] 
        
        ZipCode 邮编 char[7] 
        
        Telephone 电话号码 char[41] 
        
        MobilePhone 手机 char[21] 
        
        Fax 传真 char[41] 
        
        EMail 电子邮件 char[41] 
        
        MoneyAccountStatus 资金账户状态 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        NewBankAccount 新银行帐号 char[41] 
        
        NewBankPassWord 新银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        BankAccType 银行帐号类型 char
        
        InstallID 安装编号 int
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        TID 交易ID int
        
        Digest 摘要 char[36] 
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''性别'''
        self.Gender = None
    
        '''国家代码'''
        self.CountryCode = None
    
        '''客户类型'''
        self.CustType = None
    
        '''地址'''
        self.Address = None
    
        '''邮编'''
        self.ZipCode = None
    
        '''电话号码'''
        self.Telephone = None
    
        '''手机'''
        self.MobilePhone = None
    
        '''传真'''
        self.Fax = None
    
        '''电子邮件'''
        self.EMail = None
    
        '''资金账户状态'''
        self.MoneyAccountStatus = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''新银行帐号'''
        self.NewBankAccount = None
    
        '''新银行密码'''
        self.NewBankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易ID'''
        self.TID = None
    
        '''摘要'''
        self.Digest = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcDepositResultInformField:
    '''
    验证期货资金密码和客户信息
        
        DepositSeqNo 出入金流水号，该流水号为银期报盘返回的流水号 char[15] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        Deposit 入金金额 double
        
        RequestID 请求编号 int
        
        ReturnCode 返回代码 char[7] 
        
        DescrInfoForReturnCode 返回码描述 char[129] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''出入金流水号，该流水号为银期报盘返回的流水号'''
        self.DepositSeqNo = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''入金金额'''
        self.Deposit = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''返回代码'''
        self.ReturnCode = None
    
        '''返回码描述'''
        self.DescrInfoForReturnCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryBrokerTradingAlgosField:
    '''
    查询经纪公司交易算法
        
        BrokerID 经纪公司代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqTransferField:
    '''
    转账请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        FutureSerial 期货公司流水号 int
        
        UserID 用户标识 char[16] 
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        TradeAmount 转帐金额 double
        
        FutureFetchAmount 期货可取金额 double
        
        FeePayFlag 费用支付标志 char
        
        CustFee 应收客户费用 double
        
        BrokerFee 应收期货公司费用 double
        
        Message 发送方给接收方的消息 char[129] 
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        TransferStatus 转账交易状态 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''用户标识'''
        self.UserID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''转帐金额'''
        self.TradeAmount = None
    
        '''期货可取金额'''
        self.FutureFetchAmount = None
    
        '''费用支付标志'''
        self.FeePayFlag = None
    
        '''应收客户费用'''
        self.CustFee = None
    
        '''应收期货公司费用'''
        self.BrokerFee = None
    
        '''发送方给接收方的消息'''
        self.Message = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''转账交易状态'''
        self.TransferStatus = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcVerifyFuturePasswordAndCustInfoField:
    '''
    验证期货资金密码和客户信息
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryExchangeMarginRateAdjustField:
    '''
    查询交易所调整保证金率
        
        BrokerID 经纪公司代码 char[11] 
        
        InstrumentID 合约代码 char[31] 
        
        HedgeFlag 投机套保标志 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcLogoutAllField:
    '''
    登录信息
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        SystemName 系统名称 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''系统名称'''
        self.SystemName = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataStaticField:
    '''
    行情静态属性
        
        OpenPrice 今开盘 double
        
        HighestPrice 最高价 double
        
        LowestPrice 最低价 double
        
        ClosePrice 今收盘 double
        
        UpperLimitPrice 涨停板价 double
        
        LowerLimitPrice 跌停板价 double
        
        SettlementPrice 本次结算价 double
        
        CurrDelta 今虚实度 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''今开盘'''
        self.OpenPrice = None
    
        '''最高价'''
        self.HighestPrice = None
    
        '''最低价'''
        self.LowestPrice = None
    
        '''今收盘'''
        self.ClosePrice = None
    
        '''涨停板价'''
        self.UpperLimitPrice = None
    
        '''跌停板价'''
        self.LowerLimitPrice = None
    
        '''本次结算价'''
        self.SettlementPrice = None
    
        '''今虚实度'''
        self.CurrDelta = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCFMMCTradingAccountTokenField:
    '''
    监控中心用户令牌
        
        BrokerID 经纪公司代码 char[11] 
        
        ParticipantID 经纪公司统一编码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        KeyID 密钥编号 int
        
        Token 动态令牌 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''经纪公司统一编码'''
        self.ParticipantID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''密钥编号'''
        self.KeyID = None
    
        '''动态令牌'''
        self.Token = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingCodeField:
    '''
    交易编码
        
        InvestorID 投资者代码 char[13] 
        
        BrokerID 经纪公司代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
        
        ClientID 客户代码 char[11] 
        
        IsActive 是否活跃 int
        
        ClientIDType 交易编码类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''是否活跃'''
        self.IsActive = None
    
        '''交易编码类型'''
        self.ClientIDType = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspInfoField:
    '''
    响应信息
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySuperUserField:
    '''
    查询管理用户
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInstrumentMarginRateField:
    '''
    查询合约保证金率
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        HedgeFlag 投机套保标志 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInvestorGroupField:
    '''
    查询投资者组
        
        BrokerID 经纪公司代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqRepealField:
    '''
    冲正请求
        
        RepealTimeInterval 冲正时间间隔 int
        
        RepealedTimes 已经冲正次数 int
        
        BankRepealFlag 银行冲正标志 char
        
        BrokerRepealFlag 期商冲正标志 char
        
        PlateRepealSerial 被冲正平台流水号 int
        
        BankRepealSerial 被冲正银行流水号 char[13] 
        
        FutureRepealSerial 被冲正期货流水号 int
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        FutureSerial 期货公司流水号 int
        
        UserID 用户标识 char[16] 
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        TradeAmount 转帐金额 double
        
        FutureFetchAmount 期货可取金额 double
        
        FeePayFlag 费用支付标志 char
        
        CustFee 应收客户费用 double
        
        BrokerFee 应收期货公司费用 double
        
        Message 发送方给接收方的消息 char[129] 
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        TransferStatus 转账交易状态 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''冲正时间间隔'''
        self.RepealTimeInterval = None
    
        '''已经冲正次数'''
        self.RepealedTimes = None
    
        '''银行冲正标志'''
        self.BankRepealFlag = None
    
        '''期商冲正标志'''
        self.BrokerRepealFlag = None
    
        '''被冲正平台流水号'''
        self.PlateRepealSerial = None
    
        '''被冲正银行流水号'''
        self.BankRepealSerial = None
    
        '''被冲正期货流水号'''
        self.FutureRepealSerial = None
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''用户标识'''
        self.UserID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''转帐金额'''
        self.TradeAmount = None
    
        '''期货可取金额'''
        self.FutureFetchAmount = None
    
        '''费用支付标志'''
        self.FeePayFlag = None
    
        '''应收客户费用'''
        self.CustFee = None
    
        '''应收期货公司费用'''
        self.BrokerFee = None
    
        '''发送方给接收方的消息'''
        self.Message = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''转账交易状态'''
        self.TransferStatus = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingAccountPasswordUpdateV1Field:
    '''
    资金账户口令变更域
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        OldPassword 原来的口令 char[41] 
        
        NewPassword 新的口令 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''原来的口令'''
        self.OldPassword = None
    
        '''新的口令'''
        self.NewPassword = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeTradeField:
    '''
    交易所成交
        
        ExchangeID 交易所代码 char[9] 
        
        TradeID 成交编号 char[21] 
        
        Direction 买卖方向 char
        
        OrderSysID 报单编号 char[21] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        TradingRole 交易角色 char
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        OffsetFlag 开平标志 char
        
        HedgeFlag 投机套保标志 char
        
        Price 价格 double
        
        Volume 数量 int
        
        TradeDate 成交时期 char[9] 
        
        TradeTime 成交时间 char[9] 
        
        TradeType 成交类型 char
        
        PriceSource 成交价来源 char
        
        TraderID 交易所交易员代码 char[21] 
        
        OrderLocalID 本地报单编号 char[13] 
        
        ClearingPartID 结算会员编号 char[11] 
        
        BusinessUnit 业务单元 char[21] 
        
        SequenceNo 序号 int
        
        TradeSource 成交来源 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''成交编号'''
        self.TradeID = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''交易角色'''
        self.TradingRole = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''开平标志'''
        self.OffsetFlag = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''价格'''
        self.Price = None
    
        '''数量'''
        self.Volume = None
    
        '''成交时期'''
        self.TradeDate = None
    
        '''成交时间'''
        self.TradeTime = None
    
        '''成交类型'''
        self.TradeType = None
    
        '''成交价来源'''
        self.PriceSource = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''结算会员编号'''
        self.ClearingPartID = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''序号'''
        self.SequenceNo = None
    
        '''成交来源'''
        self.TradeSource = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryUserSessionField:
    '''
    查询用户会话
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingNoticeField:
    '''
    用户事件通知
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorRange 投资者范围 char
        
        InvestorID 投资者代码 char[13] 
        
        SequenceSeries 序列系列号 short
        
        UserID 用户代码 char[16] 
        
        SendTime 发送时间 char[9] 
        
        SequenceNo 序列号 int
        
        FieldContent 消息正文 char[501] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''序列系列号'''
        self.SequenceSeries = None
    
        '''用户代码'''
        self.UserID = None
    
        '''发送时间'''
        self.SendTime = None
    
        '''序列号'''
        self.SequenceNo = None
    
        '''消息正文'''
        self.FieldContent = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqSyncKeyField:
    '''
    交易核心向银期报盘发出密钥同步请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Message 交易核心给银期报盘的消息 char[129] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''交易核心给银期报盘的消息'''
        self.Message = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryBrokerUserField:
    '''
    查询经纪公司用户
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCurrTransferIdentityField:
    '''
    当前银期所属交易中心
        
        IdentityID 交易中心代码 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易中心代码'''
        self.IdentityID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryExchangeMarginRateField:
    '''
    查询交易所保证金率
        
        BrokerID 经纪公司代码 char[11] 
        
        InstrumentID 合约代码 char[31] 
        
        HedgeFlag 投机套保标志 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingInstrumentCommissionRateField:
    '''
    正在同步中的合约手续费率
        
        InstrumentID 合约代码 char[31] 
        
        InvestorRange 投资者范围 char
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        OpenRatioByMoney 开仓手续费率 double
        
        OpenRatioByVolume 开仓手续费 double
        
        CloseRatioByMoney 平仓手续费率 double
        
        CloseRatioByVolume 平仓手续费 double
        
        CloseTodayRatioByMoney 平今手续费率 double
        
        CloseTodayRatioByVolume 平今手续费 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''开仓手续费率'''
        self.OpenRatioByMoney = None
    
        '''开仓手续费'''
        self.OpenRatioByVolume = None
    
        '''平仓手续费率'''
        self.CloseRatioByMoney = None
    
        '''平仓手续费'''
        self.CloseRatioByVolume = None
    
        '''平今手续费率'''
        self.CloseTodayRatioByMoney = None
    
        '''平今手续费'''
        self.CloseTodayRatioByVolume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingAccountField:
    '''
    资金账户
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        PreMortgage 上次质押金额 double
        
        PreCredit 上次信用额度 double
        
        PreDeposit 上次存款额 double
        
        PreBalance 上次结算准备金 double
        
        PreMargin 上次占用的保证金 double
        
        InterestBase 利息基数 double
        
        Interest 利息收入 double
        
        Deposit 入金金额 double
        
        Withdraw 出金金额 double
        
        FrozenMargin 冻结的保证金 double
        
        FrozenCash 冻结的资金 double
        
        FrozenCommission 冻结的手续费 double
        
        CurrMargin 当前保证金总额 double
        
        CashIn 资金差额 double
        
        Commission 手续费 double
        
        CloseProfit 平仓盈亏 double
        
        PositionProfit 持仓盈亏 double
        
        Balance 期货结算准备金 double
        
        Available 可用资金 double
        
        WithdrawQuota 可取资金 double
        
        Reserve 基本准备金 double
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        Credit 信用额度 double
        
        Mortgage 质押金额 double
        
        ExchangeMargin 交易所保证金 double
        
        DeliveryMargin 投资者交割保证金 double
        
        ExchangeDeliveryMargin 交易所交割保证金 double
        
        ReserveBalance 保底期货结算准备金 double
        
        CurrencyID 币种代码 char[4] 
        
        PreFundMortgageIn 上次货币质入金额 double
        
        PreFundMortgageOut 上次货币质出金额 double
        
        FundMortgageIn 货币质入金额 double
        
        FundMortgageOut 货币质出金额 double
        
        FundMortgageAvailable 货币质押余额 double
        
        MortgageableFund 可质押货币金额 double
        
        SpecProductMargin 特殊产品占用保证金 double
        
        SpecProductFrozenMargin 特殊产品冻结保证金 double
        
        SpecProductCommission 特殊产品手续费 double
        
        SpecProductFrozenCommission 特殊产品冻结手续费 double
        
        SpecProductPositionProfit 特殊产品持仓盈亏 double
        
        SpecProductCloseProfit 特殊产品平仓盈亏 double
        
        SpecProductPositionProfitByAlg 根据持仓盈亏算法计算的特殊产品持仓盈亏 double
        
        SpecProductExchangeMargin 特殊产品交易所保证金 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''上次质押金额'''
        self.PreMortgage = None
    
        '''上次信用额度'''
        self.PreCredit = None
    
        '''上次存款额'''
        self.PreDeposit = None
    
        '''上次结算准备金'''
        self.PreBalance = None
    
        '''上次占用的保证金'''
        self.PreMargin = None
    
        '''利息基数'''
        self.InterestBase = None
    
        '''利息收入'''
        self.Interest = None
    
        '''入金金额'''
        self.Deposit = None
    
        '''出金金额'''
        self.Withdraw = None
    
        '''冻结的保证金'''
        self.FrozenMargin = None
    
        '''冻结的资金'''
        self.FrozenCash = None
    
        '''冻结的手续费'''
        self.FrozenCommission = None
    
        '''当前保证金总额'''
        self.CurrMargin = None
    
        '''资金差额'''
        self.CashIn = None
    
        '''手续费'''
        self.Commission = None
    
        '''平仓盈亏'''
        self.CloseProfit = None
    
        '''持仓盈亏'''
        self.PositionProfit = None
    
        '''期货结算准备金'''
        self.Balance = None
    
        '''可用资金'''
        self.Available = None
    
        '''可取资金'''
        self.WithdrawQuota = None
    
        '''基本准备金'''
        self.Reserve = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''信用额度'''
        self.Credit = None
    
        '''质押金额'''
        self.Mortgage = None
    
        '''交易所保证金'''
        self.ExchangeMargin = None
    
        '''投资者交割保证金'''
        self.DeliveryMargin = None
    
        '''交易所交割保证金'''
        self.ExchangeDeliveryMargin = None
    
        '''保底期货结算准备金'''
        self.ReserveBalance = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''上次货币质入金额'''
        self.PreFundMortgageIn = None
    
        '''上次货币质出金额'''
        self.PreFundMortgageOut = None
    
        '''货币质入金额'''
        self.FundMortgageIn = None
    
        '''货币质出金额'''
        self.FundMortgageOut = None
    
        '''货币质押余额'''
        self.FundMortgageAvailable = None
    
        '''可质押货币金额'''
        self.MortgageableFund = None
    
        '''特殊产品占用保证金'''
        self.SpecProductMargin = None
    
        '''特殊产品冻结保证金'''
        self.SpecProductFrozenMargin = None
    
        '''特殊产品手续费'''
        self.SpecProductCommission = None
    
        '''特殊产品冻结手续费'''
        self.SpecProductFrozenCommission = None
    
        '''特殊产品持仓盈亏'''
        self.SpecProductPositionProfit = None
    
        '''特殊产品平仓盈亏'''
        self.SpecProductCloseProfit = None
    
        '''根据持仓盈亏算法计算的特殊产品持仓盈亏'''
        self.SpecProductPositionProfitByAlg = None
    
        '''特殊产品交易所保证金'''
        self.SpecProductExchangeMargin = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingInstrumentMarginRateField:
    '''
    正在同步中的合约保证金率
        
        InstrumentID 合约代码 char[31] 
        
        InvestorRange 投资者范围 char
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        HedgeFlag 投机套保标志 char
        
        LongMarginRatioByMoney 多头保证金率 double
        
        LongMarginRatioByVolume 多头保证金费 double
        
        ShortMarginRatioByMoney 空头保证金率 double
        
        ShortMarginRatioByVolume 空头保证金费 double
        
        IsRelative 是否相对交易所收取 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''多头保证金率'''
        self.LongMarginRatioByMoney = None
    
        '''多头保证金费'''
        self.LongMarginRatioByVolume = None
    
        '''空头保证金率'''
        self.ShortMarginRatioByMoney = None
    
        '''空头保证金费'''
        self.ShortMarginRatioByVolume = None
    
        '''是否相对交易所收取'''
        self.IsRelative = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcForceUserLogoutField:
    '''
    强制交易员退出
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcNotifySyncKeyField:
    '''
    交易核心向银期报盘发出密钥同步处理结果的通知
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Message 交易核心给银期报盘的消息 char[129] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''交易核心给银期报盘的消息'''
        self.Message = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataBid45Field:
    '''
    行情申买四、五属性
        
        BidPrice4 申买价四 double
        
        BidVolume4 申买量四 int
        
        BidPrice5 申买价五 double
        
        BidVolume5 申买量五 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''申买价四'''
        self.BidPrice4 = None
    
        '''申买量四'''
        self.BidVolume4 = None
    
        '''申买价五'''
        self.BidPrice5 = None
    
        '''申买量五'''
        self.BidVolume5 = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryExchangeRateField:
    '''
    查询汇率
        
        BrokerID 经纪公司代码 char[11] 
        
        FromCurrencyID 源币种 char[4] 
        
        ToCurrencyID 目标币种 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''源币种'''
        self.FromCurrencyID = None
    
        '''目标币种'''
        self.ToCurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcLinkManField:
    '''
    联系人
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        PersonType 联系人类型 char
        
        IdentifiedCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        PersonName 名称 char[81] 
        
        Telephone 联系电话 char[41] 
        
        Address 通讯地址 char[101] 
        
        ZipCode 邮政编码 char[7] 
        
        Priority 优先级 int
        
        UOAZipCode 开户邮政编码 char[11] 
        
        PersonFullName 全称 char[101] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''联系人类型'''
        self.PersonType = None
    
        '''证件类型'''
        self.IdentifiedCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''名称'''
        self.PersonName = None
    
        '''联系电话'''
        self.Telephone = None
    
        '''通讯地址'''
        self.Address = None
    
        '''邮政编码'''
        self.ZipCode = None
    
        '''优先级'''
        self.Priority = None
    
        '''开户邮政编码'''
        self.UOAZipCode = None
    
        '''全称'''
        self.PersonFullName = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCommRateModelField:
    '''
    投资者手续费率模板
        
        BrokerID 经纪公司代码 char[11] 
        
        CommModelID 手续费率模板代码 char[13] 
        
        CommModelName 模板名称 char[161] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''手续费率模板代码'''
        self.CommModelID = None
    
        '''模板名称'''
        self.CommModelName = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryExchangeField:
    '''
    查询交易所
        
        ExchangeID 交易所代码 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQueryMaxOrderVolumeField:
    '''
    查询最大报单数量
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        Direction 买卖方向 char
        
        OffsetFlag 开平标志 char
        
        HedgeFlag 投机套保标志 char
        
        MaxVolume 最大允许报单数量 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''开平标志'''
        self.OffsetFlag = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''最大允许报单数量'''
        self.MaxVolume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataUpdateTimeField:
    '''
    行情更新时间属性
        
        InstrumentID 合约代码 char[31] 
        
        UpdateTime 最后修改时间 char[9] 
        
        UpdateMillisec 最后修改毫秒 int
        
        ActionDay 业务日期 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''最后修改时间'''
        self.UpdateTime = None
    
        '''最后修改毫秒'''
        self.UpdateMillisec = None
    
        '''业务日期'''
        self.ActionDay = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCombinationLegField:
    '''
    组合交易合约的单腿
        
        CombInstrumentID 组合合约代码 char[31] 
        
        LegID 单腿编号 int
        
        LegInstrumentID 单腿合约代码 char[31] 
        
        Direction 买卖方向 char
        
        LegMultiple 单腿乘数 int
        
        ImplyLevel 派生层数 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''组合合约代码'''
        self.CombInstrumentID = None
    
        '''单腿编号'''
        self.LegID = None
    
        '''单腿合约代码'''
        self.LegInstrumentID = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''单腿乘数'''
        self.LegMultiple = None
    
        '''派生层数'''
        self.ImplyLevel = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeSequenceField:
    '''
    交易所状态
        
        ExchangeID 交易所代码 char[9] 
        
        SequenceNo 序号 int
        
        MarketStatus 合约交易状态 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''序号'''
        self.SequenceNo = None
    
        '''合约交易状态'''
        self.MarketStatus = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSettlementInfoField:
    '''
    投资者结算结果
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        SequenceNo 序号 int
        
        Content 消息正文 char[501] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''序号'''
        self.SequenceNo = None
    
        '''消息正文'''
        self.Content = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMDTraderOfferField:
    '''
    交易所行情报盘机
        
        ExchangeID 交易所代码 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
        
        ParticipantID 会员代码 char[11] 
        
        Password 密码 char[41] 
        
        InstallID 安装编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        TraderConnectStatus 交易所交易员连接状态 char
        
        ConnectRequestDate 发出连接请求的日期 char[9] 
        
        ConnectRequestTime 发出连接请求的时间 char[9] 
        
        LastReportDate 上次报告日期 char[9] 
        
        LastReportTime 上次报告时间 char[9] 
        
        ConnectDate 完成连接日期 char[9] 
        
        ConnectTime 完成连接时间 char[9] 
        
        StartDate 启动日期 char[9] 
        
        StartTime 启动时间 char[9] 
        
        TradingDay 交易日 char[9] 
        
        BrokerID 经纪公司代码 char[11] 
        
        MaxTradeID 本席位最大成交编号 char[21] 
        
        MaxOrderMessageReference 本席位最大报单备拷 char[7] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''交易所交易员连接状态'''
        self.TraderConnectStatus = None
    
        '''发出连接请求的日期'''
        self.ConnectRequestDate = None
    
        '''发出连接请求的时间'''
        self.ConnectRequestTime = None
    
        '''上次报告日期'''
        self.LastReportDate = None
    
        '''上次报告时间'''
        self.LastReportTime = None
    
        '''完成连接日期'''
        self.ConnectDate = None
    
        '''完成连接时间'''
        self.ConnectTime = None
    
        '''启动日期'''
        self.StartDate = None
    
        '''启动时间'''
        self.StartTime = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''本席位最大成交编号'''
        self.MaxTradeID = None
    
        '''本席位最大报单备拷'''
        self.MaxOrderMessageReference = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInstrumentStatusField:
    '''
    查询合约状态
        
        ExchangeID 交易所代码 char[9] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataAsk23Field:
    '''
    行情申卖二、三属性
        
        AskPrice2 申卖价二 double
        
        AskVolume2 申卖量二 int
        
        AskPrice3 申卖价三 double
        
        AskVolume3 申卖量三 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''申卖价二'''
        self.AskPrice2 = None
    
        '''申卖量二'''
        self.AskVolume2 = None
    
        '''申卖价三'''
        self.AskPrice3 = None
    
        '''申卖量三'''
        self.AskVolume3 = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryOrderActionField:
    '''
    查询报单操作
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ExchangeID 交易所代码 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易所代码'''
        self.ExchangeID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcUserRightsAssignField:
    '''
    灾备中心交易权限
        
        BrokerID 应用单元代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        DRIdentityID 交易中心代码 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''应用单元代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''交易中心代码'''
        self.DRIdentityID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcDisseminationField:
    '''
    //////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file ThostFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////
///信息分发
        
        SequenceSeries 序列系列号 short
        
        SequenceNo 序列号 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''序列系列号'''
        self.SequenceSeries = None
    
        '''序列号'''
        self.SequenceNo = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcUserLogoutField:
    '''
    用户登出请求
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCurrentTimeField:
    '''
    当前时间
        
        CurrDate 当前日期 char[9] 
        
        CurrTime 当前时间 char[9] 
        
        CurrMillisec 当前时间（毫秒） int
        
        ActionDay 业务日期 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''当前日期'''
        self.CurrDate = None
    
        '''当前时间'''
        self.CurrTime = None
    
        '''当前时间（毫秒）'''
        self.CurrMillisec = None
    
        '''业务日期'''
        self.ActionDay = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcErrOrderActionField:
    '''
    错误报单操作
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        OrderActionRef 报单操作引用 int
        
        OrderRef 报单引用 char[13] 
        
        RequestID 请求编号 int
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        ActionFlag 操作标志 char
        
        LimitPrice 价格 double
        
        VolumeChange 数量变化 int
        
        ActionDate 操作日期 char[9] 
        
        ActionTime 操作时间 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ActionLocalID 操作本地编号 char[13] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        BusinessUnit 业务单元 char[21] 
        
        OrderActionStatus 报单操作状态 char
        
        UserID 用户代码 char[16] 
        
        StatusMsg 状态信息 char[81] 
        
        InstrumentID 合约代码 char[31] 
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''报单操作引用'''
        self.OrderActionRef = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''操作标志'''
        self.ActionFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量变化'''
        self.VolumeChange = None
    
        '''操作日期'''
        self.ActionDate = None
    
        '''操作时间'''
        self.ActionTime = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''操作本地编号'''
        self.ActionLocalID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''报单操作状态'''
        self.OrderActionStatus = None
    
        '''用户代码'''
        self.UserID = None
    
        '''状态信息'''
        self.StatusMsg = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTraderOfferField:
    '''
    查询交易员报盘机
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        TraderID 交易所交易员代码 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataBid23Field:
    '''
    行情申买二、三属性
        
        BidPrice2 申买价二 double
        
        BidVolume2 申买量二 int
        
        BidPrice3 申买价三 double
        
        BidVolume3 申买量三 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''申买价二'''
        self.BidPrice2 = None
    
        '''申买量二'''
        self.BidVolume2 = None
    
        '''申买价三'''
        self.BidPrice3 = None
    
        '''申买量三'''
        self.BidVolume3 = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryMarginModelField:
    '''
    请求查询投资者保证金率模板
        
        BrokerID 经纪公司代码 char[11] 
        
        MarginModelID 保证金率模板代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''保证金率模板代码'''
        self.MarginModelID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataBaseField:
    '''
    行情基础属性
        
        TradingDay 交易日 char[9] 
        
        PreSettlementPrice 上次结算价 double
        
        PreClosePrice 昨收盘 double
        
        PreOpenInterest 昨持仓量 double
        
        PreDelta 昨虚实度 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''上次结算价'''
        self.PreSettlementPrice = None
    
        '''昨收盘'''
        self.PreClosePrice = None
    
        '''昨持仓量'''
        self.PreOpenInterest = None
    
        '''昨虚实度'''
        self.PreDelta = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradeField:
    '''
    成交
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        OrderRef 报单引用 char[13] 
        
        UserID 用户代码 char[16] 
        
        ExchangeID 交易所代码 char[9] 
        
        TradeID 成交编号 char[21] 
        
        Direction 买卖方向 char
        
        OrderSysID 报单编号 char[21] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        TradingRole 交易角色 char
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        OffsetFlag 开平标志 char
        
        HedgeFlag 投机套保标志 char
        
        Price 价格 double
        
        Volume 数量 int
        
        TradeDate 成交时期 char[9] 
        
        TradeTime 成交时间 char[9] 
        
        TradeType 成交类型 char
        
        PriceSource 成交价来源 char
        
        TraderID 交易所交易员代码 char[21] 
        
        OrderLocalID 本地报单编号 char[13] 
        
        ClearingPartID 结算会员编号 char[11] 
        
        BusinessUnit 业务单元 char[21] 
        
        SequenceNo 序号 int
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        BrokerOrderSeq 经纪公司报单编号 int
        
        TradeSource 成交来源 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''用户代码'''
        self.UserID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''成交编号'''
        self.TradeID = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''交易角色'''
        self.TradingRole = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''开平标志'''
        self.OffsetFlag = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''价格'''
        self.Price = None
    
        '''数量'''
        self.Volume = None
    
        '''成交时期'''
        self.TradeDate = None
    
        '''成交时间'''
        self.TradeTime = None
    
        '''成交类型'''
        self.TradeType = None
    
        '''成交价来源'''
        self.PriceSource = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''结算会员编号'''
        self.ClearingPartID = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''序号'''
        self.SequenceNo = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''经纪公司报单编号'''
        self.BrokerOrderSeq = None
    
        '''成交来源'''
        self.TradeSource = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryParkedOrderField:
    '''
    查询预埋单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryBrokerUserEventField:
    '''
    查询经纪公司用户事件
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        UserEventType 用户事件类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''用户事件类型'''
        self.UserEventType = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInstrumentCommissionRateField:
    '''
    查询手续费率
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReturnResultField:
    '''
    返回结果
        
        ReturnCode 返回代码 char[7] 
        
        DescrInfoForReturnCode 返回码描述 char[129] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''返回代码'''
        self.ReturnCode = None
    
        '''返回码描述'''
        self.DescrInfoForReturnCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRemoveParkedOrderActionField:
    '''
    删除预埋撤单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ParkedOrderActionID 预埋撤单编号 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''预埋撤单编号'''
        self.ParkedOrderActionID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTraderField:
    '''
    查询交易员
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        TraderID 交易所交易员代码 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcCFMMCTradingAccountKeyField:
    '''
    保证金监管系统经纪公司资金账户密钥
        
        BrokerID 经纪公司代码 char[11] 
        
        ParticipantID 经纪公司统一编码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        KeyID 密钥编号 int
        
        CurrentKey 动态密钥 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''经纪公司统一编码'''
        self.ParticipantID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''密钥编号'''
        self.KeyID = None
    
        '''动态密钥'''
        self.CurrentKey = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeRateField:
    '''
    汇率
        
        BrokerID 经纪公司代码 char[11] 
        
        FromCurrencyID 源币种 char[4] 
        
        FromCurrencyUnit 源币种单位数量 double
        
        ToCurrencyID 目标币种 char[4] 
        
        ExchangeRate 汇率 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''源币种'''
        self.FromCurrencyID = None
    
        '''源币种单位数量'''
        self.FromCurrencyUnit = None
    
        '''目标币种'''
        self.ToCurrencyID = None
    
        '''汇率'''
        self.ExchangeRate = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySyncDepositField:
    '''
    查询出入金流水
        
        BrokerID 经纪公司代码 char[11] 
        
        DepositSeqNo 出入金流水号 char[15] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''出入金流水号'''
        self.DepositSeqNo = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqUserLoginField:
    '''
    用户登录请求
        
        TradingDay 交易日 char[9] 
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        Password 密码 char[41] 
        
        UserProductInfo 用户端产品信息 char[11] 
        
        InterfaceProductInfo 接口端产品信息 char[11] 
        
        ProtocolInfo 协议信息 char[11] 
        
        MacAddress Mac地址 char[21] 
        
        OneTimePassword 动态密码 char[41] 
        
        ClientIPAddress 终端IP地址 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''密码'''
        self.Password = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
    
        '''接口端产品信息'''
        self.InterfaceProductInfo = None
    
        '''协议信息'''
        self.ProtocolInfo = None
    
        '''Mac地址'''
        self.MacAddress = None
    
        '''动态密码'''
        self.OneTimePassword = None
    
        '''终端IP地址'''
        self.ClientIPAddress = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInstrumentTradingRightField:
    '''
    投资者合约交易权限
        
        InstrumentID 合约代码 char[31] 
        
        InvestorRange 投资者范围 char
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        TradingRight 交易权限 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易权限'''
        self.TradingRight = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcVerifyCustInfoField:
    '''
    验证客户信息
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInputOrderActionField:
    '''
    输入报单操作
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        OrderActionRef 报单操作引用 int
        
        OrderRef 报单引用 char[13] 
        
        RequestID 请求编号 int
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        ActionFlag 操作标志 char
        
        LimitPrice 价格 double
        
        VolumeChange 数量变化 int
        
        UserID 用户代码 char[16] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''报单操作引用'''
        self.OrderActionRef = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''操作标志'''
        self.ActionFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量变化'''
        self.VolumeChange = None
    
        '''用户代码'''
        self.UserID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorPositionCombineDetailField:
    '''
    投资者组合持仓明细
        
        TradingDay 交易日 char[9] 
        
        OpenDate 开仓日期 char[9] 
        
        ExchangeID 交易所代码 char[9] 
        
        SettlementID 结算编号 int
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ComTradeID 组合编号 char[21] 
        
        TradeID 撮合编号 char[21] 
        
        InstrumentID 合约代码 char[31] 
        
        HedgeFlag 投机套保标志 char
        
        Direction 买卖 char
        
        TotalAmt 持仓量 int
        
        Margin 投资者保证金 double
        
        ExchMargin 交易所保证金 double
        
        MarginRateByMoney 保证金率 double
        
        MarginRateByVolume 保证金率(按手数) double
        
        LegID 单腿编号 int
        
        LegMultiple 单腿乘数 int
        
        CombInstrumentID 组合持仓合约编码 char[31] 
        
        TradeGroupID 成交组号 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''开仓日期'''
        self.OpenDate = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''组合编号'''
        self.ComTradeID = None
    
        '''撮合编号'''
        self.TradeID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''买卖'''
        self.Direction = None
    
        '''持仓量'''
        self.TotalAmt = None
    
        '''投资者保证金'''
        self.Margin = None
    
        '''交易所保证金'''
        self.ExchMargin = None
    
        '''保证金率'''
        self.MarginRateByMoney = None
    
        '''保证金率(按手数)'''
        self.MarginRateByVolume = None
    
        '''单腿编号'''
        self.LegID = None
    
        '''单腿乘数'''
        self.LegMultiple = None
    
        '''组合持仓合约编码'''
        self.CombInstrumentID = None
    
        '''成交组号'''
        self.TradeGroupID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryBrokerUserFunctionField:
    '''
    查询经纪公司用户权限
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcParkedOrderField:
    '''
    预埋单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        OrderRef 报单引用 char[13] 
        
        UserID 用户代码 char[16] 
        
        OrderPriceType 报单价格条件 char
        
        Direction 买卖方向 char
        
        CombOffsetFlag 组合开平标志 char[5] 
        
        CombHedgeFlag 组合投机套保标志 char[5] 
        
        LimitPrice 价格 double
        
        VolumeTotalOriginal 数量 int
        
        TimeCondition 有效期类型 char
        
        GTDDate GTD日期 char[9] 
        
        VolumeCondition 成交量类型 char
        
        MinVolume 最小成交量 int
        
        ContingentCondition 触发条件 char
        
        StopPrice 止损价 double
        
        ForceCloseReason 强平原因 char
        
        IsAutoSuspend 自动挂起标志 int
        
        BusinessUnit 业务单元 char[21] 
        
        RequestID 请求编号 int
        
        UserForceClose 用户强评标志 int
        
        ExchangeID 交易所代码 char[9] 
        
        ParkedOrderID 预埋报单编号 char[13] 
        
        UserType 用户类型 char
        
        Status 预埋单状态 char
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
        
        IsSwapOrder 互换单标志 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''用户代码'''
        self.UserID = None
    
        '''报单价格条件'''
        self.OrderPriceType = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''组合开平标志'''
        self.CombOffsetFlag = None
    
        '''组合投机套保标志'''
        self.CombHedgeFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量'''
        self.VolumeTotalOriginal = None
    
        '''有效期类型'''
        self.TimeCondition = None
    
        '''GTD日期'''
        self.GTDDate = None
    
        '''成交量类型'''
        self.VolumeCondition = None
    
        '''最小成交量'''
        self.MinVolume = None
    
        '''触发条件'''
        self.ContingentCondition = None
    
        '''止损价'''
        self.StopPrice = None
    
        '''强平原因'''
        self.ForceCloseReason = None
    
        '''自动挂起标志'''
        self.IsAutoSuspend = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''用户强评标志'''
        self.UserForceClose = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''预埋报单编号'''
        self.ParkedOrderID = None
    
        '''用户类型'''
        self.UserType = None
    
        '''预埋单状态'''
        self.Status = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
    
        '''互换单标志'''
        self.IsSwapOrder = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerUserRightAssignField:
    '''
    经济公司是否有在本标示的交易权限
        
        BrokerID 应用单元代码 char[11] 
        
        DRIdentityID 交易中心代码 int
        
        Tradeable 能否交易 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''应用单元代码'''
        self.BrokerID = None
    
        '''交易中心代码'''
        self.DRIdentityID = None
    
        '''能否交易'''
        self.Tradeable = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcOrderActionField:
    '''
    报单操作
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        OrderActionRef 报单操作引用 int
        
        OrderRef 报单引用 char[13] 
        
        RequestID 请求编号 int
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        ActionFlag 操作标志 char
        
        LimitPrice 价格 double
        
        VolumeChange 数量变化 int
        
        ActionDate 操作日期 char[9] 
        
        ActionTime 操作时间 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ActionLocalID 操作本地编号 char[13] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        BusinessUnit 业务单元 char[21] 
        
        OrderActionStatus 报单操作状态 char
        
        UserID 用户代码 char[16] 
        
        StatusMsg 状态信息 char[81] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''报单操作引用'''
        self.OrderActionRef = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''操作标志'''
        self.ActionFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量变化'''
        self.VolumeChange = None
    
        '''操作日期'''
        self.ActionDate = None
    
        '''操作时间'''
        self.ActionTime = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''操作本地编号'''
        self.ActionLocalID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''报单操作状态'''
        self.OrderActionStatus = None
    
        '''用户代码'''
        self.UserID = None
    
        '''状态信息'''
        self.StatusMsg = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcPartBrokerField:
    '''
    会员编码和经纪公司编码对照表
        
        BrokerID 经纪公司代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        IsActive 是否活跃 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''是否活跃'''
        self.IsActive = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqOpenAccountField:
    '''
    转帐开户请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        Gender 性别 char
        
        CountryCode 国家代码 char[21] 
        
        CustType 客户类型 char
        
        Address 地址 char[101] 
        
        ZipCode 邮编 char[7] 
        
        Telephone 电话号码 char[41] 
        
        MobilePhone 手机 char[21] 
        
        Fax 传真 char[41] 
        
        EMail 电子邮件 char[41] 
        
        MoneyAccountStatus 资金账户状态 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        CashExchangeCode 汇钞标志 char
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        TID 交易ID int
        
        UserID 用户标识 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''性别'''
        self.Gender = None
    
        '''国家代码'''
        self.CountryCode = None
    
        '''客户类型'''
        self.CustType = None
    
        '''地址'''
        self.Address = None
    
        '''邮编'''
        self.ZipCode = None
    
        '''电话号码'''
        self.Telephone = None
    
        '''手机'''
        self.MobilePhone = None
    
        '''传真'''
        self.Fax = None
    
        '''电子邮件'''
        self.EMail = None
    
        '''资金账户状态'''
        self.MoneyAccountStatus = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''汇钞标志'''
        self.CashExchangeCode = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''交易ID'''
        self.TID = None
    
        '''用户标识'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInvestorProductGroupMarginField:
    '''
    查询投资者品种/跨品种保证金
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ProductGroupID 品种/跨品种标示 char[31] 
        
        HedgeFlag 投机套保标志 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''品种/跨品种标示'''
        self.ProductGroupID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcVerifyInvestorPasswordField:
    '''
    校验投资者密码
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        Password 密码 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''密码'''
        self.Password = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQueryBrokerDepositField:
    '''
    查询经纪公司资金
        
        BrokerID 经纪公司代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''交易所代码'''
        self.ExchangeID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSuperUserField:
    '''
    管理用户
        
        UserID 用户代码 char[16] 
        
        UserName 用户名称 char[81] 
        
        Password 密码 char[41] 
        
        IsActive 是否活跃 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''用户代码'''
        self.UserID = None
    
        '''用户名称'''
        self.UserName = None
    
        '''密码'''
        self.Password = None
    
        '''是否活跃'''
        self.IsActive = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryProductField:
    '''
    查询产品
        
        ProductID 产品代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''产品代码'''
        self.ProductID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorField:
    '''
    投资者
        
        InvestorID 投资者代码 char[13] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorGroupID 投资者分组代码 char[13] 
        
        InvestorName 投资者名称 char[81] 
        
        IdentifiedCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        IsActive 是否活跃 int
        
        Telephone 联系电话 char[41] 
        
        Address 通讯地址 char[101] 
        
        OpenDate 开户日期 char[9] 
        
        Mobile 手机 char[41] 
        
        CommModelID 手续费率模板代码 char[13] 
        
        MarginModelID 保证金率模板代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者分组代码'''
        self.InvestorGroupID = None
    
        '''投资者名称'''
        self.InvestorName = None
    
        '''证件类型'''
        self.IdentifiedCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''是否活跃'''
        self.IsActive = None
    
        '''联系电话'''
        self.Telephone = None
    
        '''通讯地址'''
        self.Address = None
    
        '''开户日期'''
        self.OpenDate = None
    
        '''手机'''
        self.Mobile = None
    
        '''手续费率模板代码'''
        self.CommModelID = None
    
        '''保证金率模板代码'''
        self.MarginModelID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncStatusField:
    '''
    数据同步状态
        
        TradingDay 交易日 char[9] 
        
        DataSyncStatus 数据同步状态 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''数据同步状态'''
        self.DataSyncStatus = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInvestorWithdrawAlgorithmField:
    '''
    经纪公司可提资金算法表
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorRange 投资者范围 char
        
        InvestorID 投资者代码 char[13] 
        
        UsingRatio 可提资金比例 double
        
        CurrencyID 币种代码 char[4] 
        
        FundMortgageRatio 货币质押比率 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''可提资金比例'''
        self.UsingRatio = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''货币质押比率'''
        self.FundMortgageRatio = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferQryBankRspField:
    '''
    查询银行资金请求响应
        
        RetCode 响应代码 char[5] 
        
        RetInfo 响应信息 char[129] 
        
        FutureAccount 资金账户 char[13] 
        
        TradeAmt 银行余额 double
        
        UseAmt 银行可用余额 double
        
        FetchAmt 银行可取余额 double
        
        CurrencyCode 币种 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''响应代码'''
        self.RetCode = None
    
        '''响应信息'''
        self.RetInfo = None
    
        '''资金账户'''
        self.FutureAccount = None
    
        '''银行余额'''
        self.TradeAmt = None
    
        '''银行可用余额'''
        self.UseAmt = None
    
        '''银行可取余额'''
        self.FetchAmt = None
    
        '''币种'''
        self.CurrencyCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcAccountregisterField:
    '''
    客户开销户信息表
        
        TradeDay 交易日期 char[9] 
        
        BankID 银行编码 char[4] 
        
        BankBranchID 银行分支机构编码 char[5] 
        
        BankAccount 银行帐号 char[41] 
        
        BrokerID 期货公司编码 char[11] 
        
        BrokerBranchID 期货公司分支机构编码 char[31] 
        
        AccountID 投资者帐号 char[13] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustomerName 客户姓名 char[51] 
        
        CurrencyID 币种代码 char[4] 
        
        OpenOrDestroy 开销户类别 char
        
        RegDate 签约日期 char[9] 
        
        OutDate 解约日期 char[9] 
        
        TID 交易ID int
        
        CustType 客户类型 char
        
        BankAccType 银行帐号类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日期'''
        self.TradeDay = None
    
        '''银行编码'''
        self.BankID = None
    
        '''银行分支机构编码'''
        self.BankBranchID = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''期货公司编码'''
        self.BrokerID = None
    
        '''期货公司分支机构编码'''
        self.BrokerBranchID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''开销户类别'''
        self.OpenOrDestroy = None
    
        '''签约日期'''
        self.RegDate = None
    
        '''解约日期'''
        self.OutDate = None
    
        '''交易ID'''
        self.TID = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号类型'''
        self.BankAccType = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerDepositField:
    '''
    经纪公司资金
        
        TradingDay 交易日期 char[9] 
        
        BrokerID 经纪公司代码 char[11] 
        
        ParticipantID 会员代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
        
        PreBalance 上次结算准备金 double
        
        CurrMargin 当前保证金总额 double
        
        CloseProfit 平仓盈亏 double
        
        Balance 期货结算准备金 double
        
        Deposit 入金金额 double
        
        Withdraw 出金金额 double
        
        Available 可提资金 double
        
        Reserve 基本准备金 double
        
        FrozenMargin 冻结的保证金 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日期'''
        self.TradingDay = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''上次结算准备金'''
        self.PreBalance = None
    
        '''当前保证金总额'''
        self.CurrMargin = None
    
        '''平仓盈亏'''
        self.CloseProfit = None
    
        '''期货结算准备金'''
        self.Balance = None
    
        '''入金金额'''
        self.Deposit = None
    
        '''出金金额'''
        self.Withdraw = None
    
        '''可提资金'''
        self.Available = None
    
        '''基本准备金'''
        self.Reserve = None
    
        '''冻结的保证金'''
        self.FrozenMargin = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcErrorConditionalOrderField:
    '''
    查询错误报单操作
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        OrderRef 报单引用 char[13] 
        
        UserID 用户代码 char[16] 
        
        OrderPriceType 报单价格条件 char
        
        Direction 买卖方向 char
        
        CombOffsetFlag 组合开平标志 char[5] 
        
        CombHedgeFlag 组合投机套保标志 char[5] 
        
        LimitPrice 价格 double
        
        VolumeTotalOriginal 数量 int
        
        TimeCondition 有效期类型 char
        
        GTDDate GTD日期 char[9] 
        
        VolumeCondition 成交量类型 char
        
        MinVolume 最小成交量 int
        
        ContingentCondition 触发条件 char
        
        StopPrice 止损价 double
        
        ForceCloseReason 强平原因 char
        
        IsAutoSuspend 自动挂起标志 int
        
        BusinessUnit 业务单元 char[21] 
        
        RequestID 请求编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderSubmitStatus 报单提交状态 char
        
        NotifySequence 报单提示序号 int
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        OrderSysID 报单编号 char[21] 
        
        OrderSource 报单来源 char
        
        OrderStatus 报单状态 char
        
        OrderType 报单类型 char
        
        VolumeTraded 今成交数量 int
        
        VolumeTotal 剩余数量 int
        
        InsertDate 报单日期 char[9] 
        
        InsertTime 委托时间 char[9] 
        
        ActiveTime 激活时间 char[9] 
        
        SuspendTime 挂起时间 char[9] 
        
        UpdateTime 最后修改时间 char[9] 
        
        CancelTime 撤销时间 char[9] 
        
        ActiveTraderID 最后修改交易所交易员代码 char[21] 
        
        ClearingPartID 结算会员编号 char[11] 
        
        SequenceNo 序号 int
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        UserProductInfo 用户端产品信息 char[11] 
        
        StatusMsg 状态信息 char[81] 
        
        UserForceClose 用户强评标志 int
        
        ActiveUserID 操作用户代码 char[16] 
        
        BrokerOrderSeq 经纪公司报单编号 int
        
        RelativeOrderSysID 相关报单 char[21] 
        
        ZCETotalTradedVolume 郑商所成交数量 int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
        
        IsSwapOrder 互换单标志 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''用户代码'''
        self.UserID = None
    
        '''报单价格条件'''
        self.OrderPriceType = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''组合开平标志'''
        self.CombOffsetFlag = None
    
        '''组合投机套保标志'''
        self.CombHedgeFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量'''
        self.VolumeTotalOriginal = None
    
        '''有效期类型'''
        self.TimeCondition = None
    
        '''GTD日期'''
        self.GTDDate = None
    
        '''成交量类型'''
        self.VolumeCondition = None
    
        '''最小成交量'''
        self.MinVolume = None
    
        '''触发条件'''
        self.ContingentCondition = None
    
        '''止损价'''
        self.StopPrice = None
    
        '''强平原因'''
        self.ForceCloseReason = None
    
        '''自动挂起标志'''
        self.IsAutoSuspend = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''报单提交状态'''
        self.OrderSubmitStatus = None
    
        '''报单提示序号'''
        self.NotifySequence = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''报单来源'''
        self.OrderSource = None
    
        '''报单状态'''
        self.OrderStatus = None
    
        '''报单类型'''
        self.OrderType = None
    
        '''今成交数量'''
        self.VolumeTraded = None
    
        '''剩余数量'''
        self.VolumeTotal = None
    
        '''报单日期'''
        self.InsertDate = None
    
        '''委托时间'''
        self.InsertTime = None
    
        '''激活时间'''
        self.ActiveTime = None
    
        '''挂起时间'''
        self.SuspendTime = None
    
        '''最后修改时间'''
        self.UpdateTime = None
    
        '''撤销时间'''
        self.CancelTime = None
    
        '''最后修改交易所交易员代码'''
        self.ActiveTraderID = None
    
        '''结算会员编号'''
        self.ClearingPartID = None
    
        '''序号'''
        self.SequenceNo = None
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
    
        '''状态信息'''
        self.StatusMsg = None
    
        '''用户强评标志'''
        self.UserForceClose = None
    
        '''操作用户代码'''
        self.ActiveUserID = None
    
        '''经纪公司报单编号'''
        self.BrokerOrderSeq = None
    
        '''相关报单'''
        self.RelativeOrderSysID = None
    
        '''郑商所成交数量'''
        self.ZCETotalTradedVolume = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
    
        '''互换单标志'''
        self.IsSwapOrder = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcDRTransferField:
    '''
    灾备交易转换报文
        
        OrigDRIdentityID 原交易中心代码 int
        
        DestDRIdentityID 目标交易中心代码 int
        
        OrigBrokerID 原应用单元代码 char[11] 
        
        DestBrokerID 目标易用单元代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''原交易中心代码'''
        self.OrigDRIdentityID = None
    
        '''目标交易中心代码'''
        self.DestDRIdentityID = None
    
        '''原应用单元代码'''
        self.OrigBrokerID = None
    
        '''目标易用单元代码'''
        self.DestBrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncFundMortgageField:
    '''
    货币质押同步
        
        MortgageSeqNo 货币质押流水号 char[15] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        FromCurrencyID 源币种 char[4] 
        
        MortgageAmount 质押金额 double
        
        ToCurrencyID 目标币种 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''货币质押流水号'''
        self.MortgageSeqNo = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''源币种'''
        self.FromCurrencyID = None
    
        '''质押金额'''
        self.MortgageAmount = None
    
        '''目标币种'''
        self.ToCurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerTradingParamsField:
    '''
    经纪公司交易参数
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        MarginPriceType 保证金价格类型 char
        
        Algorithm 盈亏算法 char
        
        AvailIncludeCloseProfit 可用是否包含平仓盈利 char
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''保证金价格类型'''
        self.MarginPriceType = None
    
        '''盈亏算法'''
        self.Algorithm = None
    
        '''可用是否包含平仓盈利'''
        self.AvailIncludeCloseProfit = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRemoveParkedOrderField:
    '''
    删除预埋单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ParkedOrderID 预埋报单编号 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''预埋报单编号'''
        self.ParkedOrderID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerUserPasswordField:
    '''
    经纪公司用户口令
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        Password 密码 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''密码'''
        self.Password = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcOrderField:
    '''
    报单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        OrderRef 报单引用 char[13] 
        
        UserID 用户代码 char[16] 
        
        OrderPriceType 报单价格条件 char
        
        Direction 买卖方向 char
        
        CombOffsetFlag 组合开平标志 char[5] 
        
        CombHedgeFlag 组合投机套保标志 char[5] 
        
        LimitPrice 价格 double
        
        VolumeTotalOriginal 数量 int
        
        TimeCondition 有效期类型 char
        
        GTDDate GTD日期 char[9] 
        
        VolumeCondition 成交量类型 char
        
        MinVolume 最小成交量 int
        
        ContingentCondition 触发条件 char
        
        StopPrice 止损价 double
        
        ForceCloseReason 强平原因 char
        
        IsAutoSuspend 自动挂起标志 int
        
        BusinessUnit 业务单元 char[21] 
        
        RequestID 请求编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderSubmitStatus 报单提交状态 char
        
        NotifySequence 报单提示序号 int
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        OrderSysID 报单编号 char[21] 
        
        OrderSource 报单来源 char
        
        OrderStatus 报单状态 char
        
        OrderType 报单类型 char
        
        VolumeTraded 今成交数量 int
        
        VolumeTotal 剩余数量 int
        
        InsertDate 报单日期 char[9] 
        
        InsertTime 委托时间 char[9] 
        
        ActiveTime 激活时间 char[9] 
        
        SuspendTime 挂起时间 char[9] 
        
        UpdateTime 最后修改时间 char[9] 
        
        CancelTime 撤销时间 char[9] 
        
        ActiveTraderID 最后修改交易所交易员代码 char[21] 
        
        ClearingPartID 结算会员编号 char[11] 
        
        SequenceNo 序号 int
        
        FrontID 前置编号 int
        
        SessionID 会话编号 int
        
        UserProductInfo 用户端产品信息 char[11] 
        
        StatusMsg 状态信息 char[81] 
        
        UserForceClose 用户强评标志 int
        
        ActiveUserID 操作用户代码 char[16] 
        
        BrokerOrderSeq 经纪公司报单编号 int
        
        RelativeOrderSysID 相关报单 char[21] 
        
        ZCETotalTradedVolume 郑商所成交数量 int
        
        IsSwapOrder 互换单标志 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''用户代码'''
        self.UserID = None
    
        '''报单价格条件'''
        self.OrderPriceType = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''组合开平标志'''
        self.CombOffsetFlag = None
    
        '''组合投机套保标志'''
        self.CombHedgeFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量'''
        self.VolumeTotalOriginal = None
    
        '''有效期类型'''
        self.TimeCondition = None
    
        '''GTD日期'''
        self.GTDDate = None
    
        '''成交量类型'''
        self.VolumeCondition = None
    
        '''最小成交量'''
        self.MinVolume = None
    
        '''触发条件'''
        self.ContingentCondition = None
    
        '''止损价'''
        self.StopPrice = None
    
        '''强平原因'''
        self.ForceCloseReason = None
    
        '''自动挂起标志'''
        self.IsAutoSuspend = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''报单提交状态'''
        self.OrderSubmitStatus = None
    
        '''报单提示序号'''
        self.NotifySequence = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''报单来源'''
        self.OrderSource = None
    
        '''报单状态'''
        self.OrderStatus = None
    
        '''报单类型'''
        self.OrderType = None
    
        '''今成交数量'''
        self.VolumeTraded = None
    
        '''剩余数量'''
        self.VolumeTotal = None
    
        '''报单日期'''
        self.InsertDate = None
    
        '''委托时间'''
        self.InsertTime = None
    
        '''激活时间'''
        self.ActiveTime = None
    
        '''挂起时间'''
        self.SuspendTime = None
    
        '''最后修改时间'''
        self.UpdateTime = None
    
        '''撤销时间'''
        self.CancelTime = None
    
        '''最后修改交易所交易员代码'''
        self.ActiveTraderID = None
    
        '''结算会员编号'''
        self.ClearingPartID = None
    
        '''序号'''
        self.SequenceNo = None
    
        '''前置编号'''
        self.FrontID = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''用户端产品信息'''
        self.UserProductInfo = None
    
        '''状态信息'''
        self.StatusMsg = None
    
        '''用户强评标志'''
        self.UserForceClose = None
    
        '''操作用户代码'''
        self.ActiveUserID = None
    
        '''经纪公司报单编号'''
        self.BrokerOrderSeq = None
    
        '''相关报单'''
        self.RelativeOrderSysID = None
    
        '''郑商所成交数量'''
        self.ZCETotalTradedVolume = None
    
        '''互换单标志'''
        self.IsSwapOrder = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySyncStatusField:
    '''
    查询组合合约分腿
        
        TradingDay 交易日 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryErrOrderActionField:
    '''
    查询错误报单操作
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerUserOTPParamField:
    '''
    用户动态令牌参数
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        OTPVendorsID 动态令牌提供商 char[2] 
        
        SerialNumber 动态令牌序列号 char[17] 
        
        AuthKey 令牌密钥 char[41] 
        
        LastDrift 漂移值 int
        
        LastSuccess 成功值 int
        
        OTPType 动态令牌类型 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''动态令牌提供商'''
        self.OTPVendorsID = None
    
        '''动态令牌序列号'''
        self.SerialNumber = None
    
        '''令牌密钥'''
        self.AuthKey = None
    
        '''漂移值'''
        self.LastDrift = None
    
        '''成功值'''
        self.LastSuccess = None
    
        '''动态令牌类型'''
        self.OTPType = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInstrumentMarginRateAdjustField:
    '''
    合约保证金率调整
        
        InstrumentID 合约代码 char[31] 
        
        InvestorRange 投资者范围 char
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        HedgeFlag 投机套保标志 char
        
        LongMarginRatioByMoney 多头保证金率 double
        
        LongMarginRatioByVolume 多头保证金费 double
        
        ShortMarginRatioByMoney 空头保证金率 double
        
        ShortMarginRatioByVolume 空头保证金费 double
        
        IsRelative 是否相对交易所收取 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''多头保证金率'''
        self.LongMarginRatioByMoney = None
    
        '''多头保证金费'''
        self.LongMarginRatioByVolume = None
    
        '''空头保证金率'''
        self.ShortMarginRatioByMoney = None
    
        '''空头保证金费'''
        self.ShortMarginRatioByVolume = None
    
        '''是否相对交易所收取'''
        self.IsRelative = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInvestorField:
    '''
    查询投资者
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSpecificInstrumentField:
    '''
    指定的合约
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataAsk45Field:
    '''
    行情申卖四、五属性
        
        AskPrice4 申卖价四 double
        
        AskVolume4 申卖量四 int
        
        AskPrice5 申卖价五 double
        
        AskVolume5 申卖量五 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''申卖价四'''
        self.AskPrice4 = None
    
        '''申卖量四'''
        self.AskVolume4 = None
    
        '''申卖价五'''
        self.AskPrice5 = None
    
        '''申卖量五'''
        self.AskVolume5 = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingAccountPasswordUpdateField:
    '''
    资金账户口令变更域
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        OldPassword 原来的口令 char[41] 
        
        NewPassword 新的口令 char[41] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''原来的口令'''
        self.OldPassword = None
    
        '''新的口令'''
        self.NewPassword = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspQueryTradeResultBySerialField:
    '''
    查询指定流水号的交易结果响应
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
        
        Reference 流水号 int
        
        RefrenceIssureType 本流水号发布者的机构类型 char
        
        RefrenceIssure 本流水号发布者机构编码 char[36] 
        
        OriginReturnCode 原始返回代码 char[7] 
        
        OriginDescrInfoForReturnCode 原始返回码描述 char[129] 
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        CurrencyID 币种代码 char[4] 
        
        TradeAmount 转帐金额 double
        
        Digest 摘要 char[36] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
    
        '''流水号'''
        self.Reference = None
    
        '''本流水号发布者的机构类型'''
        self.RefrenceIssureType = None
    
        '''本流水号发布者机构编码'''
        self.RefrenceIssure = None
    
        '''原始返回代码'''
        self.OriginReturnCode = None
    
        '''原始返回码描述'''
        self.OriginDescrInfoForReturnCode = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''转帐金额'''
        self.TradeAmount = None
    
        '''摘要'''
        self.Digest = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInstrumentCommissionRateField:
    '''
    合约手续费率
        
        InstrumentID 合约代码 char[31] 
        
        InvestorRange 投资者范围 char
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        OpenRatioByMoney 开仓手续费率 double
        
        OpenRatioByVolume 开仓手续费 double
        
        CloseRatioByMoney 平仓手续费率 double
        
        CloseRatioByVolume 平仓手续费 double
        
        CloseTodayRatioByMoney 平今手续费率 double
        
        CloseTodayRatioByVolume 平今手续费 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''开仓手续费率'''
        self.OpenRatioByMoney = None
    
        '''开仓手续费'''
        self.OpenRatioByVolume = None
    
        '''平仓手续费率'''
        self.CloseRatioByMoney = None
    
        '''平仓手续费'''
        self.CloseRatioByVolume = None
    
        '''平今手续费率'''
        self.CloseTodayRatioByMoney = None
    
        '''平今手续费'''
        self.CloseTodayRatioByVolume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQueryCFMMCTradingAccountTokenField:
    '''
    查询监控中心用户令牌
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInvestorPositionCombineDetailField:
    '''
    查询组合持仓明细
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        CombInstrumentID 组合持仓合约编码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''组合持仓合约编码'''
        self.CombInstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTransferBankField:
    '''
    查询转帐银行
        
        BankID 银行代码 char[4] 
        
        BankBrchID 银行分中心代码 char[5] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分中心代码'''
        self.BankBrchID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferSerialField:
    '''
    银期转账交易流水表
        
        PlateSerial 平台流水号 int
        
        TradeDate 交易发起方日期 char[9] 
        
        TradingDay 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        TradeCode 交易代码 char[7] 
        
        SessionID 会话编号 int
        
        BankID 银行编码 char[4] 
        
        BankBranchID 银行分支机构编码 char[5] 
        
        BankAccType 银行帐号类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankSerial 银行流水号 char[13] 
        
        BrokerID 期货公司编码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        FutureAccType 期货公司帐号类型 char
        
        AccountID 投资者帐号 char[13] 
        
        InvestorID 投资者代码 char[13] 
        
        FutureSerial 期货公司流水号 int
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CurrencyID 币种代码 char[4] 
        
        TradeAmount 交易金额 double
        
        CustFee 应收客户费用 double
        
        BrokerFee 应收期货公司费用 double
        
        AvailabilityFlag 有效标志 char
        
        OperatorCode 操作员 char[17] 
        
        BankNewAccount 新银行帐号 char[41] 
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''平台流水号'''
        self.PlateSerial = None
    
        '''交易发起方日期'''
        self.TradeDate = None
    
        '''交易日期'''
        self.TradingDay = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''交易代码'''
        self.TradeCode = None
    
        '''会话编号'''
        self.SessionID = None
    
        '''银行编码'''
        self.BankID = None
    
        '''银行分支机构编码'''
        self.BankBranchID = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''期货公司编码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''期货公司帐号类型'''
        self.FutureAccType = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''交易金额'''
        self.TradeAmount = None
    
        '''应收客户费用'''
        self.CustFee = None
    
        '''应收期货公司费用'''
        self.BrokerFee = None
    
        '''有效标志'''
        self.AvailabilityFlag = None
    
        '''操作员'''
        self.OperatorCode = None
    
        '''新银行帐号'''
        self.BankNewAccount = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeMarginRateAdjustField:
    '''
    交易所保证金率调整
        
        BrokerID 经纪公司代码 char[11] 
        
        InstrumentID 合约代码 char[31] 
        
        HedgeFlag 投机套保标志 char
        
        LongMarginRatioByMoney 跟随交易所投资者多头保证金率 double
        
        LongMarginRatioByVolume 跟随交易所投资者多头保证金费 double
        
        ShortMarginRatioByMoney 跟随交易所投资者空头保证金率 double
        
        ShortMarginRatioByVolume 跟随交易所投资者空头保证金费 double
        
        ExchLongMarginRatioByMoney 交易所多头保证金率 double
        
        ExchLongMarginRatioByVolume 交易所多头保证金费 double
        
        ExchShortMarginRatioByMoney 交易所空头保证金率 double
        
        ExchShortMarginRatioByVolume 交易所空头保证金费 double
        
        NoLongMarginRatioByMoney 不跟随交易所投资者多头保证金率 double
        
        NoLongMarginRatioByVolume 不跟随交易所投资者多头保证金费 double
        
        NoShortMarginRatioByMoney 不跟随交易所投资者空头保证金率 double
        
        NoShortMarginRatioByVolume 不跟随交易所投资者空头保证金费 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''跟随交易所投资者多头保证金率'''
        self.LongMarginRatioByMoney = None
    
        '''跟随交易所投资者多头保证金费'''
        self.LongMarginRatioByVolume = None
    
        '''跟随交易所投资者空头保证金率'''
        self.ShortMarginRatioByMoney = None
    
        '''跟随交易所投资者空头保证金费'''
        self.ShortMarginRatioByVolume = None
    
        '''交易所多头保证金率'''
        self.ExchLongMarginRatioByMoney = None
    
        '''交易所多头保证金费'''
        self.ExchLongMarginRatioByVolume = None
    
        '''交易所空头保证金率'''
        self.ExchShortMarginRatioByMoney = None
    
        '''交易所空头保证金费'''
        self.ExchShortMarginRatioByVolume = None
    
        '''不跟随交易所投资者多头保证金率'''
        self.NoLongMarginRatioByMoney = None
    
        '''不跟随交易所投资者多头保证金费'''
        self.NoLongMarginRatioByVolume = None
    
        '''不跟随交易所投资者空头保证金率'''
        self.NoShortMarginRatioByMoney = None
    
        '''不跟随交易所投资者空头保证金费'''
        self.NoShortMarginRatioByVolume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryFrontStatusField:
    '''
    查询前置状态
        
        FrontID 前置编号 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''前置编号'''
        self.FrontID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryNoticeField:
    '''
    查询客户通知
        
        BrokerID 经纪公司代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingInvestorGroupField:
    '''
    正在同步中的投资者分组
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorGroupID 投资者分组代码 char[13] 
        
        InvestorGroupName 投资者分组名称 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者分组代码'''
        self.InvestorGroupID = None
    
        '''投资者分组名称'''
        self.InvestorGroupName = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTraderField:
    '''
    交易所交易员
        
        ExchangeID 交易所代码 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
        
        ParticipantID 会员代码 char[11] 
        
        Password 密码 char[41] 
        
        InstallCount 安装数量 int
        
        BrokerID 经纪公司代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''密码'''
        self.Password = None
    
        '''安装数量'''
        self.InstallCount = None
    
        '''经纪公司代码'''
        self.BrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcNotifyFutureSignOutField:
    '''
    期商签退通知
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Digest 摘要 char[36] 
        
        CurrencyID 币种代码 char[4] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''摘要'''
        self.Digest = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeOrderActionField:
    '''
    交易所报单操作
        
        ExchangeID 交易所代码 char[9] 
        
        OrderSysID 报单编号 char[21] 
        
        ActionFlag 操作标志 char
        
        LimitPrice 价格 double
        
        VolumeChange 数量变化 int
        
        ActionDate 操作日期 char[9] 
        
        ActionTime 操作时间 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
        
        InstallID 安装编号 int
        
        OrderLocalID 本地报单编号 char[13] 
        
        ActionLocalID 操作本地编号 char[13] 
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        BusinessUnit 业务单元 char[21] 
        
        OrderActionStatus 报单操作状态 char
        
        UserID 用户代码 char[16] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''报单编号'''
        self.OrderSysID = None
    
        '''操作标志'''
        self.ActionFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量变化'''
        self.VolumeChange = None
    
        '''操作日期'''
        self.ActionDate = None
    
        '''操作时间'''
        self.ActionTime = None
    
        '''交易所交易员代码'''
        self.TraderID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''本地报单编号'''
        self.OrderLocalID = None
    
        '''操作本地编号'''
        self.ActionLocalID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''报单操作状态'''
        self.OrderActionStatus = None
    
        '''用户代码'''
        self.UserID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingInvestorField:
    '''
    正在同步中的投资者
        
        InvestorID 投资者代码 char[13] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorGroupID 投资者分组代码 char[13] 
        
        InvestorName 投资者名称 char[81] 
        
        IdentifiedCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        IsActive 是否活跃 int
        
        Telephone 联系电话 char[41] 
        
        Address 通讯地址 char[101] 
        
        OpenDate 开户日期 char[9] 
        
        Mobile 手机 char[41] 
        
        CommModelID 手续费率模板代码 char[13] 
        
        MarginModelID 保证金率模板代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者分组代码'''
        self.InvestorGroupID = None
    
        '''投资者名称'''
        self.InvestorName = None
    
        '''证件类型'''
        self.IdentifiedCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''是否活跃'''
        self.IsActive = None
    
        '''联系电话'''
        self.Telephone = None
    
        '''通讯地址'''
        self.Address = None
    
        '''开户日期'''
        self.OpenDate = None
    
        '''手机'''
        self.Mobile = None
    
        '''手续费率模板代码'''
        self.CommModelID = None
    
        '''保证金率模板代码'''
        self.MarginModelID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcLoadSettlementInfoField:
    '''
    装载结算信息
        
        BrokerID 经纪公司代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTradingAccountPasswordField:
    '''
    资金账户口令域
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 密码 char[41] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''密码'''
        self.Password = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSettlementInfoConfirmField:
    '''
    投资者结算结果确认信息
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ConfirmDate 确认日期 char[9] 
        
        ConfirmTime 确认时间 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''确认日期'''
        self.ConfirmDate = None
    
        '''确认时间'''
        self.ConfirmTime = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspTransferField:
    '''
    银行发起银行资金转期货响应
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        InstallID 安装编号 int
        
        FutureSerial 期货公司流水号 int
        
        UserID 用户标识 char[16] 
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        TradeAmount 转帐金额 double
        
        FutureFetchAmount 期货可取金额 double
        
        FeePayFlag 费用支付标志 char
        
        CustFee 应收客户费用 double
        
        BrokerFee 应收期货公司费用 double
        
        Message 发送方给接收方的消息 char[129] 
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        TransferStatus 转账交易状态 char
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''用户标识'''
        self.UserID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''转帐金额'''
        self.TradeAmount = None
    
        '''期货可取金额'''
        self.FutureFetchAmount = None
    
        '''费用支付标志'''
        self.FeePayFlag = None
    
        '''应收客户费用'''
        self.CustFee = None
    
        '''应收期货公司费用'''
        self.BrokerFee = None
    
        '''发送方给接收方的消息'''
        self.Message = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''转账交易状态'''
        self.TransferStatus = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryExchangeOrderActionField:
    '''
    查询交易所报单操作
        
        ParticipantID 会员代码 char[11] 
        
        ClientID 客户代码 char[11] 
        
        ExchangeID 交易所代码 char[9] 
        
        TraderID 交易所交易员代码 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''客户代码'''
        self.ClientID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferBankToFutureRspField:
    '''
    银行资金转期货请求响应
        
        RetCode 响应代码 char[5] 
        
        RetInfo 响应信息 char[129] 
        
        FutureAccount 资金账户 char[13] 
        
        TradeAmt 转帐金额 double
        
        CustFee 应收客户手续费 double
        
        CurrencyCode 币种 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''响应代码'''
        self.RetCode = None
    
        '''响应信息'''
        self.RetInfo = None
    
        '''资金账户'''
        self.FutureAccount = None
    
        '''转帐金额'''
        self.TradeAmt = None
    
        '''应收客户手续费'''
        self.CustFee = None
    
        '''币种'''
        self.CurrencyCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncDepositField:
    '''
    出入金同步
        
        DepositSeqNo 出入金流水号 char[15] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        Deposit 入金金额 double
        
        IsForce 是否强制进行 int
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''出入金流水号'''
        self.DepositSeqNo = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''入金金额'''
        self.Deposit = None
    
        '''是否强制进行'''
        self.IsForce = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspFutureSignOutField:
    '''
    期商签退响应
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Digest 摘要 char[36] 
        
        CurrencyID 币种代码 char[4] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''摘要'''
        self.Digest = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcFutureSignIOField:
    '''
    期商签到签退
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Digest 摘要 char[36] 
        
        CurrencyID 币种代码 char[4] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''摘要'''
        self.Digest = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerField:
    '''
    经纪公司
        
        BrokerID 经纪公司代码 char[11] 
        
        BrokerAbbr 经纪公司简称 char[9] 
        
        BrokerName 经纪公司名称 char[81] 
        
        IsActive 是否活跃 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''经纪公司简称'''
        self.BrokerAbbr = None
    
        '''经纪公司名称'''
        self.BrokerName = None
    
        '''是否活跃'''
        self.IsActive = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInstrumentTradingRightField:
    '''
    查询合约交易权限
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryAccountregisterField:
    '''
    请求查询银期签约关系
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        BankID 银行编码 char[4] 
        
        BankBranchID 银行分支机构编码 char[5] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''银行编码'''
        self.BankID = None
    
        '''银行分支机构编码'''
        self.BankBranchID = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerUserEventField:
    '''
    查询经纪公司用户事件
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        UserEventType 用户事件类型 char
        
        EventSequenceNo 用户事件序号 int
        
        EventDate 事件发生日期 char[9] 
        
        EventTime 事件发生时间 char[9] 
        
        UserEventInfo 用户事件信息 char[1025] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''用户事件类型'''
        self.UserEventType = None
    
        '''用户事件序号'''
        self.EventSequenceNo = None
    
        '''事件发生日期'''
        self.EventDate = None
    
        '''事件发生时间'''
        self.EventTime = None
    
        '''用户事件信息'''
        self.UserEventInfo = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcBrokerUserFunctionField:
    '''
    经纪公司用户功能权限
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        BrokerFunctionCode 经纪公司功能代码 char
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''经纪公司功能代码'''
        self.BrokerFunctionCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryCFMMCTradingAccountKeyField:
    '''
    请求查询保证金监管系统经纪公司资金账户密钥
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferBankField:
    '''
    转帐银行
        
        BankID 银行代码 char[4] 
        
        BankBrchID 银行分中心代码 char[5] 
        
        BankName 银行名称 char[101] 
        
        IsActive 是否活跃 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分中心代码'''
        self.BankBrchID = None
    
        '''银行名称'''
        self.BankName = None
    
        '''是否活跃'''
        self.IsActive = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspSyncKeyField:
    '''
    交易核心向银期报盘发出密钥同步响应
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Message 交易核心给银期报盘的消息 char[129] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''交易核心给银期报盘的消息'''
        self.Message = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcPositionProfitAlgorithmField:
    '''
    浮动盈亏算法
        
        BrokerID 经纪公司代码 char[11] 
        
        AccountID 投资者帐号 char[13] 
        
        Algorithm 盈亏算法 char
        
        Memo 备注 char[161] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''盈亏算法'''
        self.Algorithm = None
    
        '''备注'''
        self.Memo = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInstrumentMarginRateField:
    '''
    合约保证金率
        
        InstrumentID 合约代码 char[31] 
        
        InvestorRange 投资者范围 char
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        HedgeFlag 投机套保标志 char
        
        LongMarginRatioByMoney 多头保证金率 double
        
        LongMarginRatioByVolume 多头保证金费 double
        
        ShortMarginRatioByMoney 空头保证金率 double
        
        ShortMarginRatioByVolume 空头保证金费 double
        
        IsRelative 是否相对交易所收取 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投资者范围'''
        self.InvestorRange = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''多头保证金率'''
        self.LongMarginRatioByMoney = None
    
        '''多头保证金费'''
        self.LongMarginRatioByVolume = None
    
        '''空头保证金率'''
        self.ShortMarginRatioByMoney = None
    
        '''空头保证金费'''
        self.ShortMarginRatioByVolume = None
    
        '''是否相对交易所收取'''
        self.IsRelative = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataAveragePriceField:
    '''
    成交均价
        
        AveragePrice 当日均价 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''当日均价'''
        self.AveragePrice = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryMDTraderOfferField:
    '''
    查询行情报盘机
        
        ExchangeID 交易所代码 char[9] 
        
        ParticipantID 会员代码 char[11] 
        
        TraderID 交易所交易员代码 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''会员代码'''
        self.ParticipantID = None
    
        '''交易所交易员代码'''
        self.TraderID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqQueryTradeResultBySerialField:
    '''
    查询指定流水号的交易结果请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        Reference 流水号 int
        
        RefrenceIssureType 本流水号发布者的机构类型 char
        
        RefrenceIssure 本流水号发布者机构编码 char[36] 
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        CurrencyID 币种代码 char[4] 
        
        TradeAmount 转帐金额 double
        
        Digest 摘要 char[36] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''流水号'''
        self.Reference = None
    
        '''本流水号发布者的机构类型'''
        self.RefrenceIssureType = None
    
        '''本流水号发布者机构编码'''
        self.RefrenceIssure = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''转帐金额'''
        self.TradeAmount = None
    
        '''摘要'''
        self.Digest = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcUserPasswordUpdateField:
    '''
    用户口令变更
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        OldPassword 原来的口令 char[41] 
        
        NewPassword 新的口令 char[41] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''原来的口令'''
        self.OldPassword = None
    
        '''新的口令'''
        self.NewPassword = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcNotifyQueryAccountField:
    '''
    查询账户信息通知
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        CustomerName 客户姓名 char[51] 
        
        IdCardType 证件类型 char
        
        IdentifiedCardNo 证件号码 char[51] 
        
        CustType 客户类型 char
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        FutureSerial 期货公司流水号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        VerifyCertNoFlag 验证客户证件号码标志 char
        
        CurrencyID 币种代码 char[4] 
        
        Digest 摘要 char[36] 
        
        BankAccType 银行帐号类型 char
        
        DeviceID 渠道标志 char[3] 
        
        BankSecuAccType 期货单位帐号类型 char
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        BankSecuAcc 期货单位帐号 char[41] 
        
        BankPwdFlag 银行密码标志 char
        
        SecuPwdFlag 期货资金密码核对标志 char
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        BankUseAmount 银行可用金额 double
        
        BankFetchAmount 银行可取金额 double
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''客户姓名'''
        self.CustomerName = None
    
        '''证件类型'''
        self.IdCardType = None
    
        '''证件号码'''
        self.IdentifiedCardNo = None
    
        '''客户类型'''
        self.CustType = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''期货公司流水号'''
        self.FutureSerial = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''验证客户证件号码标志'''
        self.VerifyCertNoFlag = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''摘要'''
        self.Digest = None
    
        '''银行帐号类型'''
        self.BankAccType = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货单位帐号类型'''
        self.BankSecuAccType = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''期货单位帐号'''
        self.BankSecuAcc = None
    
        '''银行密码标志'''
        self.BankPwdFlag = None
    
        '''期货资金密码核对标志'''
        self.SecuPwdFlag = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''银行可用金额'''
        self.BankUseAmount = None
    
        '''银行可取金额'''
        self.BankFetchAmount = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataField:
    '''
    市场行情
        
        TradingDay 交易日 char[9] 
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        LastPrice 最新价 double
        
        PreSettlementPrice 上次结算价 double
        
        PreClosePrice 昨收盘 double
        
        PreOpenInterest 昨持仓量 double
        
        OpenPrice 今开盘 double
        
        HighestPrice 最高价 double
        
        LowestPrice 最低价 double
        
        Volume 数量 int
        
        Turnover 成交金额 double
        
        OpenInterest 持仓量 double
        
        ClosePrice 今收盘 double
        
        SettlementPrice 本次结算价 double
        
        UpperLimitPrice 涨停板价 double
        
        LowerLimitPrice 跌停板价 double
        
        PreDelta 昨虚实度 double
        
        CurrDelta 今虚实度 double
        
        UpdateTime 最后修改时间 char[9] 
        
        UpdateMillisec 最后修改毫秒 int
        
        ActionDay 业务日期 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''最新价'''
        self.LastPrice = None
    
        '''上次结算价'''
        self.PreSettlementPrice = None
    
        '''昨收盘'''
        self.PreClosePrice = None
    
        '''昨持仓量'''
        self.PreOpenInterest = None
    
        '''今开盘'''
        self.OpenPrice = None
    
        '''最高价'''
        self.HighestPrice = None
    
        '''最低价'''
        self.LowestPrice = None
    
        '''数量'''
        self.Volume = None
    
        '''成交金额'''
        self.Turnover = None
    
        '''持仓量'''
        self.OpenInterest = None
    
        '''今收盘'''
        self.ClosePrice = None
    
        '''本次结算价'''
        self.SettlementPrice = None
    
        '''涨停板价'''
        self.UpperLimitPrice = None
    
        '''跌停板价'''
        self.LowerLimitPrice = None
    
        '''昨虚实度'''
        self.PreDelta = None
    
        '''今虚实度'''
        self.CurrDelta = None
    
        '''最后修改时间'''
        self.UpdateTime = None
    
        '''最后修改毫秒'''
        self.UpdateMillisec = None
    
        '''业务日期'''
        self.ActionDay = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcEWarrantOffsetField:
    '''
    仓单折抵信息
        
        TradingDay 交易日期 char[9] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        ExchangeID 交易所代码 char[9] 
        
        InstrumentID 合约代码 char[31] 
        
        Direction 买卖方向 char
        
        HedgeFlag 投机套保标志 char
        
        Volume 数量 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日期'''
        self.TradingDay = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''数量'''
        self.Volume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcUserIPField:
    '''
    用户IP
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        IPAddress IP地址 char[16] 
        
        IPMask IP地址掩码 char[16] 
        
        MacAddress Mac地址 char[21] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''IP地址'''
        self.IPAddress = None
    
        '''IP地址掩码'''
        self.IPMask = None
    
        '''Mac地址'''
        self.MacAddress = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryBrokerField:
    '''
    查询经纪公司
        
        BrokerID 经纪公司代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryPartBrokerField:
    '''
    查询经纪公司会员代码
        
        ExchangeID 交易所代码 char[9] 
        
        BrokerID 经纪公司代码 char[11] 
        
        ParticipantID 会员代码 char[11] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''会员代码'''
        self.ParticipantID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSettlementRefField:
    '''
    结算引用
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqFutureSignOutField:
    '''
    期商签退请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Digest 摘要 char[36] 
        
        CurrencyID 币种代码 char[4] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''摘要'''
        self.Digest = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcTransferFutureToBankRspField:
    '''
    期货资金转银行请求响应
        
        RetCode 响应代码 char[5] 
        
        RetInfo 响应信息 char[129] 
        
        FutureAccount 资金账户 char[13] 
        
        TradeAmt 转帐金额 double
        
        CustFee 应收客户手续费 double
        
        CurrencyCode 币种 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''响应代码'''
        self.RetCode = None
    
        '''响应信息'''
        self.RetInfo = None
    
        '''资金账户'''
        self.FutureAccount = None
    
        '''转帐金额'''
        self.TradeAmt = None
    
        '''应收客户手续费'''
        self.CustFee = None
    
        '''币种'''
        self.CurrencyCode = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryCombinationLegField:
    '''
    查询组合合约分腿
        
        CombInstrumentID 组合合约代码 char[31] 
        
        LegID 单腿编号 int
        
        LegInstrumentID 单腿合约代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''组合合约代码'''
        self.CombInstrumentID = None
    
        '''单腿编号'''
        self.LegID = None
    
        '''单腿合约代码'''
        self.LegInstrumentID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcExchangeMarginRateField:
    '''
    交易所保证金率
        
        BrokerID 经纪公司代码 char[11] 
        
        InstrumentID 合约代码 char[31] 
        
        HedgeFlag 投机套保标志 char
        
        LongMarginRatioByMoney 多头保证金率 double
        
        LongMarginRatioByVolume 多头保证金费 double
        
        ShortMarginRatioByMoney 空头保证金率 double
        
        ShortMarginRatioByVolume 空头保证金费 double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''多头保证金率'''
        self.LongMarginRatioByMoney = None
    
        '''多头保证金费'''
        self.LongMarginRatioByVolume = None
    
        '''空头保证金率'''
        self.ShortMarginRatioByMoney = None
    
        '''空头保证金费'''
        self.ShortMarginRatioByVolume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcReqDayEndFileReadyField:
    '''
    日终文件就绪请求
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        FileBusinessCode 文件业务功能 char
        
        Digest 摘要 char[36] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''文件业务功能'''
        self.FileBusinessCode = None
    
        '''摘要'''
        self.Digest = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryTradingAccountField:
    '''
    查询资金账户
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcUserRightField:
    '''
    用户权限
        
        BrokerID 经纪公司代码 char[11] 
        
        UserID 用户代码 char[16] 
        
        UserRightType 客户权限类型 char
        
        IsForbidden 是否禁止 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''用户代码'''
        self.UserID = None
    
        '''客户权限类型'''
        self.UserRightType = None
    
        '''是否禁止'''
        self.IsForbidden = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcInputOrderField:
    '''
    输入报单
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        InstrumentID 合约代码 char[31] 
        
        OrderRef 报单引用 char[13] 
        
        UserID 用户代码 char[16] 
        
        OrderPriceType 报单价格条件 char
        
        Direction 买卖方向 char
        
        CombOffsetFlag 组合开平标志 char[5] 
        
        CombHedgeFlag 组合投机套保标志 char[5] 
        
        LimitPrice 价格 double
        
        VolumeTotalOriginal 数量 int
        
        TimeCondition 有效期类型 char
        
        GTDDate GTD日期 char[9] 
        
        VolumeCondition 成交量类型 char
        
        MinVolume 最小成交量 int
        
        ContingentCondition 触发条件 char
        
        StopPrice 止损价 double
        
        ForceCloseReason 强平原因 char
        
        IsAutoSuspend 自动挂起标志 int
        
        BusinessUnit 业务单元 char[21] 
        
        RequestID 请求编号 int
        
        UserForceClose 用户强评标志 int
        
        IsSwapOrder 互换单标志 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''报单引用'''
        self.OrderRef = None
    
        '''用户代码'''
        self.UserID = None
    
        '''报单价格条件'''
        self.OrderPriceType = None
    
        '''买卖方向'''
        self.Direction = None
    
        '''组合开平标志'''
        self.CombOffsetFlag = None
    
        '''组合投机套保标志'''
        self.CombHedgeFlag = None
    
        '''价格'''
        self.LimitPrice = None
    
        '''数量'''
        self.VolumeTotalOriginal = None
    
        '''有效期类型'''
        self.TimeCondition = None
    
        '''GTD日期'''
        self.GTDDate = None
    
        '''成交量类型'''
        self.VolumeCondition = None
    
        '''最小成交量'''
        self.MinVolume = None
    
        '''触发条件'''
        self.ContingentCondition = None
    
        '''止损价'''
        self.StopPrice = None
    
        '''强平原因'''
        self.ForceCloseReason = None
    
        '''自动挂起标志'''
        self.IsAutoSuspend = None
    
        '''业务单元'''
        self.BusinessUnit = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''用户强评标志'''
        self.UserForceClose = None
    
        '''互换单标志'''
        self.IsSwapOrder = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcVerifyFuturePasswordField:
    '''
    验证期货资金密码
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        AccountID 投资者帐号 char[13] 
        
        Password 期货密码 char[41] 
        
        BankAccount 银行帐号 char[41] 
        
        BankPassWord 银行密码 char[41] 
        
        InstallID 安装编号 int
        
        TID 交易ID int
        
        CurrencyID 币种代码 char[4] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''投资者帐号'''
        self.AccountID = None
    
        '''期货密码'''
        self.Password = None
    
        '''银行帐号'''
        self.BankAccount = None
    
        '''银行密码'''
        self.BankPassWord = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''交易ID'''
        self.TID = None
    
        '''币种代码'''
        self.CurrencyID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcSyncingInvestorPositionField:
    '''
    正在同步中的投资者持仓
        
        InstrumentID 合约代码 char[31] 
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        PosiDirection 持仓多空方向 char
        
        HedgeFlag 投机套保标志 char
        
        PositionDate 持仓日期 char
        
        YdPosition 上日持仓 int
        
        Position 今日持仓 int
        
        LongFrozen 多头冻结 int
        
        ShortFrozen 空头冻结 int
        
        LongFrozenAmount 开仓冻结金额 double
        
        ShortFrozenAmount 开仓冻结金额 double
        
        OpenVolume 开仓量 int
        
        CloseVolume 平仓量 int
        
        OpenAmount 开仓金额 double
        
        CloseAmount 平仓金额 double
        
        PositionCost 持仓成本 double
        
        PreMargin 上次占用的保证金 double
        
        UseMargin 占用的保证金 double
        
        FrozenMargin 冻结的保证金 double
        
        FrozenCash 冻结的资金 double
        
        FrozenCommission 冻结的手续费 double
        
        CashIn 资金差额 double
        
        Commission 手续费 double
        
        CloseProfit 平仓盈亏 double
        
        PositionProfit 持仓盈亏 double
        
        PreSettlementPrice 上次结算价 double
        
        SettlementPrice 本次结算价 double
        
        TradingDay 交易日 char[9] 
        
        SettlementID 结算编号 int
        
        OpenCost 开仓成本 double
        
        ExchangeMargin 交易所保证金 double
        
        CombPosition 组合成交形成的持仓 int
        
        CombLongFrozen 组合多头冻结 int
        
        CombShortFrozen 组合空头冻结 int
        
        CloseProfitByDate 逐日盯市平仓盈亏 double
        
        CloseProfitByTrade 逐笔对冲平仓盈亏 double
        
        TodayPosition 今日持仓 int
        
        MarginRateByMoney 保证金率 double
        
        MarginRateByVolume 保证金率(按手数) double
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''持仓多空方向'''
        self.PosiDirection = None
    
        '''投机套保标志'''
        self.HedgeFlag = None
    
        '''持仓日期'''
        self.PositionDate = None
    
        '''上日持仓'''
        self.YdPosition = None
    
        '''今日持仓'''
        self.Position = None
    
        '''多头冻结'''
        self.LongFrozen = None
    
        '''空头冻结'''
        self.ShortFrozen = None
    
        '''开仓冻结金额'''
        self.LongFrozenAmount = None
    
        '''开仓冻结金额'''
        self.ShortFrozenAmount = None
    
        '''开仓量'''
        self.OpenVolume = None
    
        '''平仓量'''
        self.CloseVolume = None
    
        '''开仓金额'''
        self.OpenAmount = None
    
        '''平仓金额'''
        self.CloseAmount = None
    
        '''持仓成本'''
        self.PositionCost = None
    
        '''上次占用的保证金'''
        self.PreMargin = None
    
        '''占用的保证金'''
        self.UseMargin = None
    
        '''冻结的保证金'''
        self.FrozenMargin = None
    
        '''冻结的资金'''
        self.FrozenCash = None
    
        '''冻结的手续费'''
        self.FrozenCommission = None
    
        '''资金差额'''
        self.CashIn = None
    
        '''手续费'''
        self.Commission = None
    
        '''平仓盈亏'''
        self.CloseProfit = None
    
        '''持仓盈亏'''
        self.PositionProfit = None
    
        '''上次结算价'''
        self.PreSettlementPrice = None
    
        '''本次结算价'''
        self.SettlementPrice = None
    
        '''交易日'''
        self.TradingDay = None
    
        '''结算编号'''
        self.SettlementID = None
    
        '''开仓成本'''
        self.OpenCost = None
    
        '''交易所保证金'''
        self.ExchangeMargin = None
    
        '''组合成交形成的持仓'''
        self.CombPosition = None
    
        '''组合多头冻结'''
        self.CombLongFrozen = None
    
        '''组合空头冻结'''
        self.CombShortFrozen = None
    
        '''逐日盯市平仓盈亏'''
        self.CloseProfitByDate = None
    
        '''逐笔对冲平仓盈亏'''
        self.CloseProfitByTrade = None
    
        '''今日持仓'''
        self.TodayPosition = None
    
        '''保证金率'''
        self.MarginRateByMoney = None
    
        '''保证金率(按手数)'''
        self.MarginRateByVolume = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQrySettlementInfoField:
    '''
    查询投资者结算结果
        
        BrokerID 经纪公司代码 char[11] 
        
        InvestorID 投资者代码 char[13] 
        
        TradingDay 交易日 char[9] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''经纪公司代码'''
        self.BrokerID = None
    
        '''投资者代码'''
        self.InvestorID = None
    
        '''交易日'''
        self.TradingDay = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcRspFutureSignInField:
    '''
    期商签到响应
        
        TradeCode 业务功能码 char[7] 
        
        BankID 银行代码 char[4] 
        
        BankBranchID 银行分支机构代码 char[5] 
        
        BrokerID 期商代码 char[11] 
        
        BrokerBranchID 期商分支机构代码 char[31] 
        
        TradeDate 交易日期 char[9] 
        
        TradeTime 交易时间 char[9] 
        
        BankSerial 银行流水号 char[13] 
        
        TradingDay 交易系统日期 char[9] 
        
        PlateSerial 银期平台消息流水号 int
        
        LastFragment 最后分片标志 char
        
        SessionID 会话号 int
        
        InstallID 安装编号 int
        
        UserID 用户标识 char[16] 
        
        Digest 摘要 char[36] 
        
        CurrencyID 币种代码 char[4] 
        
        DeviceID 渠道标志 char[3] 
        
        BrokerIDByBank 期货公司银行编码 char[33] 
        
        OperNo 交易柜员 char[17] 
        
        RequestID 请求编号 int
        
        TID 交易ID int
        
        ErrorID 错误代码 int
        
        ErrorMsg 错误信息 char[81] 
        
        PinKey PIN密钥 char[129] 
        
        MacKey MAC密钥 char[129] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''业务功能码'''
        self.TradeCode = None
    
        '''银行代码'''
        self.BankID = None
    
        '''银行分支机构代码'''
        self.BankBranchID = None
    
        '''期商代码'''
        self.BrokerID = None
    
        '''期商分支机构代码'''
        self.BrokerBranchID = None
    
        '''交易日期'''
        self.TradeDate = None
    
        '''交易时间'''
        self.TradeTime = None
    
        '''银行流水号'''
        self.BankSerial = None
    
        '''交易系统日期'''
        self.TradingDay = None
    
        '''银期平台消息流水号'''
        self.PlateSerial = None
    
        '''最后分片标志'''
        self.LastFragment = None
    
        '''会话号'''
        self.SessionID = None
    
        '''安装编号'''
        self.InstallID = None
    
        '''用户标识'''
        self.UserID = None
    
        '''摘要'''
        self.Digest = None
    
        '''币种代码'''
        self.CurrencyID = None
    
        '''渠道标志'''
        self.DeviceID = None
    
        '''期货公司银行编码'''
        self.BrokerIDByBank = None
    
        '''交易柜员'''
        self.OperNo = None
    
        '''请求编号'''
        self.RequestID = None
    
        '''交易ID'''
        self.TID = None
    
        '''错误代码'''
        self.ErrorID = None
    
        '''错误信息'''
        self.ErrorMsg = None
    
        '''PIN密钥'''
        self.PinKey = None
    
        '''MAC密钥'''
        self.MacKey = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcQryInstrumentField:
    '''
    查询合约
        
        InstrumentID 合约代码 char[31] 
        
        ExchangeID 交易所代码 char[9] 
        
        ExchangeInstID 合约在交易所的代码 char[31] 
        
        ProductID 产品代码 char[31] 
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''合约代码'''
        self.InstrumentID = None
    
        '''交易所代码'''
        self.ExchangeID = None
    
        '''合约在交易所的代码'''
        self.ExchangeInstID = None
    
        '''产品代码'''
        self.ProductID = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}



class CThostFtdcMarketDataBestPriceField:
    '''
    行情最优价属性
        
        BidPrice1 申买价一 double
        
        BidVolume1 申买量一 int
        
        AskPrice1 申卖价一 double
        
        AskVolume1 申卖量一 int
    '''

    def __init__(self,**fields):
        ''' '''
    
        '''申买价一'''
        self.BidPrice1 = None
    
        '''申买量一'''
        self.BidVolume1 = None
    
        '''申卖价一'''
        self.AskPrice1 = None
    
        '''申卖量一'''
        self.AskVolume1 = None
        
        self.__dict__.update(entries)

    def toDict(self):
        ''' '''
        return {k:v for k,v in self.__dict__.iteritems() if v != None}

