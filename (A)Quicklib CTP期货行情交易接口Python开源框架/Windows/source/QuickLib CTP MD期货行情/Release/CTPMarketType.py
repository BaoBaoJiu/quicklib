#1.���ļ������õ�Python�ļ�Ϊ��������
#2.���ļ������õĿ��ļ�Quicklib CTP�ڻ������ͽ��׿���ѭ ��ԴЭ��GPL v3
#Quciklib Python��ܺ͹�����ѭGPL v3Э�������
#��1��Quicklib CTP   �ڻ������
#��2��Quicklib CTP   �ڻ����׿�
#��3��Quicklib CTP2  A�������
#Quciklib Python��ܺ͹����ݲ���ѭ��ԴЭ�������
#��4��Quicklib ������⣨Ԥ������ء������ź����ݸ��ơ�����������������ã�
#ԭʼ���ߣ�QQ 147423661 ��(���Ǹ�)
#��Quciklib��Դ���������׵ģ����õ�ԭʼ���߿϶��ģ���������http://www.quciklib.cn��վ��
#�ٷ���վ��http://www.quicklib.cn
#�ٷ�QQȺ��5172183(1Ⱥ)��25884087(2Ⱥ)

# -*- coding=utf-8 -*-
from ctypes import *
class sDepMarketData(Structure):
	_fields_ = [('TradingDay', 			c_char * 9),
				('InstrumentID',		c_char * 31),
				('ExchangeID',			c_char * 9),
				('ExchangeInstID',		c_char * 31),
				('LastPrice',			c_double),
				('PreSettlementPrice', 	c_double),
				('PreClosePrice',		c_double),
				('PreOpenInterest',		c_double),
				('OpenPrice',			c_double),
				('HighestPrice',		c_double),
				('LowestPrice',			c_double),
				('Volume',				c_int),
				('Turnover',			c_double),
				('OpenInterest',		c_double),
				('ClosePrice',			c_double),
				('SettlementPrice',		c_double),
				('UpperLimitPrice',		c_double),
				('LowerLimitPrice',		c_double),
				('PreDelta',			c_double),
				('CurrDelta',			c_double),
				('UpdateTime',			c_char * 9),
				('UpdateMillisec',		c_int32),
				('BidPrice1', 			c_double),
				('BidVolume1',			c_int32),
				('AskPrice1',			c_double),
				('AskVolume1',			c_int32),
				('BidPrice2',			c_double),
				('BidVolume2',			c_int32),
				('AskPrice2',			c_double),
				('AskVolume2',			c_int32),
				('BidPrice3',			c_double),
				('BidVolume3',			c_int32),
				('AskPrice3',			c_double),
				('AskVolume3',			c_int32),
				('BidPrice4',			c_double),
				('BidVolume4',			c_int32),
				('AskPrice4',			c_double),
				('AskVolume4',			c_int32),
				('BidPrice5',			c_double),
				('BidVolume5',			c_int32),
				('AskPrice5',			c_double),
				('AskVolume5',			c_int32),
				('AveragePrice',		c_double)
	]
	pass


class QL_CThostFtdcRspUserLoginField(Structure):
	_fields_ = [('TradingDay', 			     c_char * 9),       #������
	            ('LoginTime',		             c_char * 9),       #��¼�ɹ�ʱ��
	            ('BrokerID',		             c_char * 11),      #���͹�˾����                
	            ('UserID',		             c_char * 16),      #�û�����                
	            ('SystemName',		             c_char * 41),      #����ϵͳ����
	            ('FrontID',		             c_int32),          #ǰ�ñ��
	            ('SessionID',		             c_int32),          #�Ự���                
	            ('MaxOrderRef',		             c_char * 13),      #��󱨵�����                
	            ('SHFETime',		             c_char * 9),       #������ʱ��                
	            ('DCETime',		             c_char * 9),       #������ʱ��                
	            ('CZCETime',		             c_char * 9),       #֣����ʱ��
	            ('FFEXTime',		             c_char * 9),       #�н���ʱ��                
	            ('INETime',		             c_char * 9)        #��Դ����ʱ��                
	            ]
	pass


class QL_Instrument(Structure):
	_fields_ = [('InstrumentID',c_char * 31)]
	pass


class QL_CThostFtdcRspInfoField(Structure):
	_fields_ = [('ErrorID', 			     c_int32),       #�������
	            ('ErrorMsg',		             c_char * 81)    #������Ϣ
	            ]
	pass

class QL_CThostFtdcForQuoteRspField(Structure):
	_fields_ = [('TradingDay', 			     c_char * 9),    #������
	            ('InstrumentID',		             c_char * 31),   #��Լ����
	            ('ForQuoteSysID',		             c_char * 21),   #ѯ�۱��
	            ('ForQuoteTime',		             c_char * 9),    #ѯ��ʱ��
	            ('ActionDay',		             c_char * 9),    #ҵ������
	            ('ExchangeID',		             c_char * 9)     #����������
	            ]
	pass

NULL    =100

# ���ڶ���
YT_ALL			                        = 10000  	# ��������
YT_M1 					        = 10001  	# M1   1����
YT_M3 					        = 10002  	# M3   3����
YT_M5 					        = 10003  	# M5   5����
YT_M10 					        = 10004  	# M10  10����
YT_M15 					        = 10005  	# M15  15����
YT_M30 					        = 10006  	# M30  30����
YT_M60 					        = 10007  	# M60  60����
YT_M120 			                = 10008  	# M120 120����
YT_D1			                        = 10009  	# D1   1��



# PRICE TYPE
YT_CLOSE 					= 10010 #c_char('0')	# ���̼�
YT_OPEN 					= 10011 #c_char('1')	# ���̼�
YT_HIGH 					= 10012 #c_char('2')	# ��߼�
YT_LOW 					        = 10013 #c_char('3')	# ��ͼ�


