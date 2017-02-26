#1.���ļ������õ�Python�ļ�Ϊ��������
#2.���ļ������õĿ��ļ�Quicklib CTP�ڻ��ʹܽ��׿�ͽ��׿���ѭ ��ԴЭ��GPL v3
#�򵥵�˵���Ի���GPL v3Э���Դ���룬�����˻�����������Լ�ʹ�ã�����Ա�Դ��
#�����ڸÿ�Դ���룬�����������������Ʒ������ҵ��Ϊ��Ҳ���뿪Դ��

#Quciklib Python��ܺ͹�����ѭGPL v3Э�������
#��1��Quicklib CTP   �ڻ������
#��2��Quicklib CTP   �ڻ����׿�
#��3��Quicklib CTP2  A�������
#��4��Quicklib MOMģʽ  �����ʹܽ��׿�
#�����ڽ����ʹ�Ͷ��ϵͳ��MOMģʽ��ʵ��˽ļ����Ͷ�˵�ѡ�ο��ˣ���ͨ���Լ��ķ��ϵͳ����ʵ�̣�

#Quciklib Python��ܺ͹����ݲ���ѭ��ԴЭ�������
#��5��Quicklib ������⣨Ԥ������ء������ź����ݸ��ơ�����������������ã�

#��Quciklib��Դ���������׵ģ����õ�ԭʼ���߿϶��ģ���������http://www.quciklib.cn��վ�ϣ�
#������ڡ���Դ˵���͸�л.txt�����������ļ����ϸ��·���ÿһ���°汾��Quicklib���

#ԭʼ���ߣ�QQ 147423661 ��(���Ǹ�)
#�ٷ���վ��http://www.quicklib.cn
#�ٷ�QQȺ��5172183(1Ⱥ)��25884087(2Ⱥ)

# -*- coding=utf-8 -*-
from ctypes import *
from CTPTraderType import *
import time


class CTPTrader(object):
	def __init__(self):

		self.d2 = CDLL('QuickLibTD.dll')

		self.fLogin = self.d2.Login
		self.fLogin.argtypes = []
		self.fLogin.restype = c_int32
		
		self.fInsertOrder = self.d2.InsertOrder
		self.fInsertOrder.argtypes = [c_char_p, c_char, c_char,c_char, c_double, c_int32]
		self.fInsertOrder.restype = c_int32

		self.fInsertOrderByRate = self.d2.InsertOrderByRate
		self.fInsertOrderByRate.argtypes = [c_char_p, c_char, c_char,c_char, c_double, c_double,c_int32,c_int32]
		self.fInsertOrderByRate.restype = c_int32

		self.fDeleteOrder = self.d2.DeleteOrder
		self.fDeleteOrder.argtypes = [c_char_p, c_int32]
		self.fDeleteOrder.restype = c_int32

		self.fQryTradedVol = self.d2.QryTradedVol
		self.fQryTradedVol.argtypes = [c_int32]
		self.fQryTradedVol.restype = c_int32
		
		self.fQryPosition = self.d2.QryPosition
		self.fQryPosition.argtypes = [c_char_p,c_int32]
		self.fQryPosition.restype = c_int32		
		
		self.fQryPositionList = self.d2.QryPositionList
		self.fQryPositionList.argtypes = [c_int32]
		self.fQryPositionList.restype = c_void_p
		
		self.fQryBalance = self.d2.QryBalance
		self.fQryBalance.argtypes = [c_bool]
		self.fQryBalance.restype = c_double	
		
		self.fQryAvailable = self.d2.QryAvailable
		self.fQryAvailable.argtypes = []
		self.fQryAvailable.restype = c_double
		
		self.fSetShowPosition = self.d2.SetShowPosition
		self.fSetShowPosition.argtypes = [c_bool]
		self.fSetShowPosition.restype = c_void_p	
		
		self.fQryExchangeMarginRate = self.d2.QryExchangeMarginRate
		self.fQryExchangeMarginRate.argtypes = [c_char_p,c_int32]
		self.fQryExchangeMarginRate.restype = c_double		
		
		self.fQryUnderlyingMultiple = self.d2.QryUnderlyingMultiple
		self.fQryUnderlyingMultiple.argtypes = [c_char_p]
		self.fQryUnderlyingMultiple.restype = c_double		
		
		self.fReqFromBankToFutureByFuture = self.d2.ReqFromBankToFutureByFuture
		self.fReqFromBankToFutureByFuture.argtypes = [c_char_p,c_char_p,c_char_p,c_char_p,c_char_p,c_double,c_int32]
		self.fReqFromBankToFutureByFuture.restype = c_int32		
			
		
		self.fReqFromFutureToBankByFuture = self.d2.ReqFromFutureToBankByFuture
		self.fReqFromFutureToBankByFuture.argtypes = [c_char_p,c_char_p,c_char_p,c_char_p,c_char_p,c_double,c_int32]
		self.fReqFromFutureToBankByFuture.restype = c_int32
		
		self.fReqQryContractBank = self.d2.ReqQryContractBank
		self.fReqQryContractBank.argtypes = []
		self.fReqQryContractBank.restype = c_int32		
		
		self.fReqQueryMaxOrderVolume = self.d2.ReqQueryMaxOrderVolume
		self.fReqQueryMaxOrderVolume.argtypes = [c_char_p,c_char_p,c_char_p,c_char,c_char,c_char,c_int32]
		self.fReqQueryMaxOrderVolume.restype = c_int32				
			
		self.fOnCmd = self.d2.OnCmd
		self.fOnCmd.argtypes = []
		self.fOnCmd.restype = c_int32
	
		self.fGetCmd = self.d2.GetCmd
		self.fGetCmd.argtypes = []
		self.fGetCmd.restype = c_int32
	
		self.fGetCmdContent = self.d2.GetCmdContent
		self.fGetCmdContent.argtypes = []
		self.fGetCmdContent.restype = c_char_p
		
		
		self.fGetCmdContent_Order = self.d2.GetCmdContent_Order
		self.fGetCmdContent_Order.argtypes = []
		self.fGetCmdContent_Order.restype = c_void_p
		
		
		self.fGetCmdContent_BankToFutureByFuture = self.d2.GetCmdContent_BankToFutureByFuture
		self.fGetCmdContent_BankToFutureByFuture.argtypes = []
		self.fGetCmdContent_BankToFutureByFuture.restype = c_void_p

		self.fGetCmdContent_FutureToBankByFuture = self.d2.GetCmdContent_FutureToBankByFuture
		self.fGetCmdContent_FutureToBankByFuture.argtypes = []
		self.fGetCmdContent_FutureToBankByFuture.restype = c_void_p	
		
		
		self.fGetCmdContent_Trade = self.d2.GetCmdContent_Trade
		self.fGetCmdContent_Trade.argtypes = []
		self.fGetCmdContent_Trade.restype = c_void_p		
		
		self.fGetCmdContent_Settlement = self.d2.GetCmdContent_Settlement
		self.fGetCmdContent_Settlement.argtypes = []
		self.fGetCmdContent_Settlement.restype = c_void_p	
		
		self.fGetCmdContent_QueryMaxOrderVolume = self.d2.GetCmdContent_QueryMaxOrderVolume
		self.fGetCmdContent_QueryMaxOrderVolume.argtypes = []
		self.fGetCmdContent_QueryMaxOrderVolume.restype = c_void_p		
		
		
		self.fGetCmdContent_Error = self.d2.GetCmdContent_Error
		self.fGetCmdContent_Error.argtypes = []
		self.fGetCmdContent_Error.restype = c_void_p			
		
		#self.fGetCmdContent_Error = self.d2.GetCmdContent_Error
		#self.fGetCmdContent_Error.argtypes = []
		#self.fGetCmdContent_Error.restype = c_void_p			
		
		self.fGetCmdContent_LoginScuess = self.d2.GetCmdContent_LoginScuess
		self.fGetCmdContent_LoginScuess.argtypes = []		
		self.fGetCmdContent_LoginScuess.restype = c_int32	
		
		self.fGetCmdContent_Connected = self.d2.GetCmdContent_Connected
		self.fGetCmdContent_Connected.argtypes = []		
		self.fGetCmdContent_Connected.restype = c_int32
		
		self.fGetCmdContent_ProductGroupMargin = self.d2.GetCmdContent_ProductGroupMargin
		self.fGetCmdContent_ProductGroupMargin.argtypes = []	
		self.fGetCmdContent_ProductGroupMargin.restype = c_int32
		
		self.fGetCmdContent_CommissionRate = self.d2.GetCmdContent_CommissionRate
		self.fGetCmdContent_CommissionRate.argtypes = []		
		self.fGetCmdContent_CommissionRate.restype = c_int32				
		
	def Login(self):
		return self.fLogin()

	def InsertOrder(self, instrumentID, direction, offsetFlag, priceType, price, num):
		return self.fInsertOrder(instrumentID, direction, offsetFlag, priceType,
								 c_double(price), c_int32(num))
	
	#�����ʽ�����µ�
	def InsertOrderByRate(self, instrumentID, direction, offsetFlag, priceType, price, rate, BalanceType, multiplier):
		return self.fInsertOrderByRate(instrumentID, direction, offsetFlag, priceType,
								 c_double(price), rate, BalanceType, multiplier)


	def DeleteOrder(self, instrumentID, orderRef):
		return self.fDeleteOrder(instrumentID, orderRef)

	def QryTradedVol(self, orderRef):
		return self.fQryTradedVol(orderRef)
	
	#��ѯƷ�ֲֳ�
	def QryPosition(self, instrumentID,positiontype):
		return self.fQryPosition(instrumentID,positiontype)
	
	#��ѯ�ֲ��б�
	def QryPositionList(self, orderRef):
		return self.fQryPositionList(orderRef)


        #��ѯȨ��   BalanceType=True��̬Ȩ��    BalanceType=False��̬Ȩ��
	def QryBalance(self, BalanceType):
		return self.fQryBalance(BalanceType)
	
	#��ѯ�����ʽ�
	def QryAvailable(self):
		return self.fQryAvailable()
			
	#���ø��³ֲ�����ʱ��ʾ,���Կ���̨��Ч
	def SetShowPosition(self,showstate):
		self.fSetShowPosition(showstate)
		
 
	#��ѯ��֤�����
	def QryExchangeMarginRate(self,Instrument,Type):
		return self.fQryExchangeMarginRate(Instrument,Type)
	
	#��ѯ��Լ����
	def QryUnderlyingMultiple(self,Instrument):
		return self.fQryUnderlyingMultiple(Instrument)
	
	#�ڻ����������ʽ�ת�ڻ�����
	def ReqFromBankToFutureByFuture(self,BankID, BrokerBranchID,BankAccount,BankPassWord,AccountID, TradeAmount,nRequestID):
		return self.fReqFromBankToFutureByFuture(BankID, BrokerBranchID,BankAccount,BankPassWord,AccountID, TradeAmount,nRequestID)
	
	#�ڻ������ڻ��ʽ�ת��������
	def ReqFromFutureToBankByFuture(self,BankID, BrokerBranchID,BankAccount,BankPassWord,AccountID, TradeAmount,nRequestID):
		return self.fReqFromFutureToBankByFuture(BankID, BrokerBranchID,BankAccount,BankPassWord,AccountID, TradeAmount,nRequestID)	
	
	#��ѯReqQueryMaxOrderVolume  QryQueryMaxOrderVolume �滻��
	def ReqQueryMaxOrderVolume(self,BrokerID,InvestorID,Instrument,Direction,OffsetFlag,HedgeFlag,MaxVolume):
		return self.fReqQueryMaxOrderVolume(BrokerID,InvestorID,Instrument,Direction,OffsetFlag,HedgeFlag,MaxVolume)
	
	#�����ѯǩԼ����
	def ReqQryContractBank(self):
		return self.fReqQryContractBank()
 
	
	def OnCmd(self):
		return self.fOnCmd()

	def GetCmd(self):
		return (self.fGetCmd(),self.fGetCmdContent()) 	

	def GetUnGetCmdSize(self):
		return self.fGetUnGetCmdSize()	
	
	def GetCmdContent_Order(self):
		#�����ر��ص�
		return self.fGetCmdContent_Order()
	
	def GetCmdContent_BankToFutureByFuture(self):
		#�ڻ����������ʽ�ת�ڻ�֪ͨ
		return self.fGetCmdContent_BankToFutureByFuture()
	
	def GetCmdContent_FutureToBankByFuture(self):
		#�ڻ������ڻ��ʽ�ת����֪ͨ
		return self.fGetCmdContent_FutureToBankByFuture()		
	
	def GetCmdContent_Trade(self):
		#�����ر��ص�
		return self.fGetCmdContent_Trade()	
		
	def GetCmdContent_Settlement(self):
		#���㵥ȷ�ϻص�
		return self.fGetCmdContent_Settlement()
	
	def GetCmdContent_QueryMaxOrderVolume(self):
		#���㵥ȷ�ϻص�
		return self.fGetCmdContent_QueryMaxOrderVolume()	
	
	def GetCmdContent_Error(self):
		#������Ϣ�ص�
		return self.fGetCmdContent_Error()
	
	def GetCmdContent_LoginScuess(self):
		#��¼�ص�
		return self.fGetCmdContent_LoginScuess()
	
	def GetCmdContent_Connected(self):
		#���ӳɹ��ص�
		return self.fGetCmdContent_Connected()
	
	def GetCmdContent_ProductGroupMargin(self):
		#�����ѯ��Լ��֤������Ӧ�ص�
		return self.fGetCmdContent_ProductGroupMargin()	
	
	def GetCmdContent_CommissionRate(self):
		#�����ѯ��Լ����������Ӧ�ص�
		return self.fGetCmdContent_CommissionRate()		
	
	