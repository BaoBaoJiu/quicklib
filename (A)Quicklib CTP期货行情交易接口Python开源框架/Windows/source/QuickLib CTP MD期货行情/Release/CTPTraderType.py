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
class QL_CThostFtdcOrderField(Structure):
    _fields_ = [('BrokerID', 			     c_char * 11),   #���͹�˾����
                ('InvestorID',		             c_char * 13),   #Ͷ���ߴ���
                ('InstrumentID',	             c_char * 31),   #��Լ����
                ('OrderRef',		             c_char * 13),   #��������
                ('UserID',			     c_char * 16),   #�û�����
                ('OrderPriceType', 	             c_char * 1),    #�����۸�����
                ('Direction',		             c_char * 1),    #��������
                ('CombOffsetFlag',		     c_char * 5),    #��Ͽ�ƽ��־
                ('CombHedgeFlag',		     c_char * 5),    #���Ͷ���ױ���־
                ('LimitPrice',		             c_double),      #�۸�
                ('VolumeTotalOriginal',		     c_int),         #����
                ('TimeCondition',		     c_char * 1),    #��Ч������
                ('GTDDate',			     c_char * 9),    #GTD����
                ('VolumeCondition',		     c_char * 1),    #�ɽ�������
                ('MinVolume',			     c_int),         #��С�ɽ���
                ('ContingentCondition',		     c_char * 1),    #��������
                ('StopPrice',		             c_double),      #ֹ���
                ('ForceCloseReason',		     c_char * 1),    #ǿƽԭ��
                ('IsAutoSuspend',		     c_int),         #�Զ������־
                ('BusinessUnit',		     c_char * 21),   #ҵ��Ԫ
                ('RequestID',			     c_int),         #������
                ('OrderLocalID',		     c_char * 13),   #���ر������
                ('ExchangeID', 			     c_char * 9),    #����������
                ('ParticipantID',		     c_char * 11),   #��Ա����
                ('ClientID',			     c_char * 11),   #�ͻ�����
                ('ExchangeInstID',		     c_char * 31),   #��Լ�ڽ������Ĵ���
                ('TraderID',			     c_char * 21),   #����������Ա����
                ('InstallID',			     c_int32),       #��װ���
                ('OrderSubmitStatus',		     c_char * 1),    #�����ύ״̬
                ('NotifySequence',		     c_int32),       #������ʾ���
                ('TradingDay',			     c_char * 9),    #������
                ('SettlementID',		     c_int32),       #������
                ('OrderSysID',			     c_char * 21),   #�������
                ('OrderSource',			     c_char * 1),    #������Դ
                ('OrderStatus',			     c_char * 1),    #����״̬
                ('OrderType',			     c_char * 1),    #��������
                ('VolumeTraded',		     c_int32),       #��ɽ�����
                ('VolumeTotal',			     c_int32),       #ʣ������
                ('InsertDate',			     c_char * 9),    #��������
                ('InsertTime',			     c_char * 9),    #ί��ʱ��
                ('ActiveTime',			     c_char * 9),    #����ʱ��
                ('SuspendTime',			     c_char * 9),    #����ʱ��
                ('UpdateTime',			     c_char * 9),    #����޸�ʱ��
                ('CancelTime',			     c_char * 9),    #����ʱ��
                ('ActiveTraderID',		     c_char * 21),   #����޸Ľ���������Ա����
                ('ClearingPartID',		     c_char * 11),   #�����Ա���
                ('SequenceNo',			     c_int32),       #���
                ('FrontID',			     c_int32),       #ǰ�ñ��
                ('SessionID',			     c_int32),       #�Ự���
                ('UserProductInfo',		     c_char * 11),   #�û��˲�Ʒ��Ϣ
                ('StatusMsg',			     c_char * 81),   #״̬��Ϣ
                ('UserForceClose',		     c_int32),       #�û�ǿ����־
                ('ActiveUserID',		     c_char * 16),   #�����û�����
                ('BrokerOrderSeq',		     c_int32),       #���͹�˾�������          
                ('RelativeOrderSysID',		     c_char * 21),   #��ر���
                ('ZCETotalTradedVolume',	     c_int32),       #֣�����ɽ�����
                ('IsSwapOrder',		             c_int32),       #��������־
                ('BranchID',	                     c_char * 9),    #Ӫҵ�����
                ('InvestUnitID',		     c_char * 17),   #Ͷ�ʵ�Ԫ����
                ('AccountID',	                     c_char * 13),   #�ʽ��˺�
                ('CurrencyID',		             c_char * 4),    #���ִ���
                ('IPAddress',	                     c_char * 16),   # IP��ַ        
                ('MacAddress',	                     c_char * 21)    # Mac��ַ              
                ]
    pass

class QL_CThostFtdcSettlementInfoConfirmField(Structure):
    _fields_ = [('BrokerID', 			     c_char * 11),   #���͹�˾����
                ('InvestorID',		             c_char * 13),   #Ͷ���ߴ���
                ('ConfirmDate',	                     c_char * 9),    #ȷ������
                ('ConfirmTime',			     c_char * 9)     #ȷ��ʱ��
                ]
    pass

class QL_CThostFtdcQueryMaxOrderVolumeField(Structure):
    _fields_ = [('BrokerID', 			     c_char * 11),   #���͹�˾����
                ('InvestorID',		             c_char * 13),   #Ͷ���ߴ���
                ('InstrumentID',	             c_char * 31),   #��Լ����
                ('Direction',			     c_char * 1),    #��������
                ('OffsetFlag',			     c_char * 1),    #��ƽ��־
                ('HedgeFlag',			     c_char * 1),    #Ͷ���ױ���־
                ('MaxVolume',			     c_int32),       #�������������
                ]
    pass



class QL_CThostFtdcRspInfoField(Structure):
    _fields_ = [('ErrorID', 			     c_int32),       #�������
                ('ErrorMsg',		             c_char * 81)    #������Ϣ
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




QL_Long 					= 0	# ��
QL_Short 					= 1	# ��

# Direction or bsflag
QL_D_Buy 					= c_char('0')	# ��
QL_D_Sell 					= c_char('1')	# ��



# offsetFlag
QL_OF_Open 					= c_char('0')	# ����
QL_OF_Close  				= c_char('1')	# ƽ��
QL_OF_ForceClose 			= c_char('2')	# ǿƽ
QL_OF_CloseToday 			= c_char('3')	# ƽ��
QL_OF_CloseYesterday 		= c_char('4')	# ƽ��
QL_OF_ForceOff 				= c_char('5')	# ǿ��
QL_OF_LocalForceClose 		= c_char('6')	# ����ǿƽ


# price type
QL_OPT_AnyPrice  				= c_char('1')	# �����
QL_OPT_LimitPrice  				= c_char('2')	# �޼�
QL_OPT_BestPrice  				= c_char('3')	# ���ż�
QL_OPT_LastPrice  				= c_char('4')	# ���¼�
QL_OPT_LastPricePlusOneTicks  	= c_char('5')	# ���¼۸����ϸ�1��ticks
QL_OPT_LastPricePlusTwoTicks  	= c_char('6')	# ���¼۸����ϸ�2��ticks
QL_OPT_LastPricePlusThreeTicks  = c_char('7')	# ���¼۸����ϸ�3��ticks
QL_OPT_AskPrice1  				= c_char('8')	# ��һ��
QL_OPT_AskPrice1PlusOneTicks  	= c_char('9')	# ��һ�۸����ϸ�1��ticks
QL_OPT_AskPrice1PlusTwoTicks  	= c_char('A')	# ��һ�۸����ϸ�2��ticks
QL_OPT_AskPrice1PlusThreeTicks  = c_char('B')	# ��һ�۸����ϸ�3��ticks
QL_OPT_BidPrice1  				= c_char('C')	# ��һ��
QL_OPT_BidPrice1PlusOneTicks  	= c_char('D')	# ��һ�۸����ϸ�1��ticks
QL_OPT_BidPrice1PlusTwoTicks  	= c_char('E')	# ��һ�۸����ϸ�2��ticks
QL_OPT_BidPrice1PlusThreeTicks  = c_char('F')	# ��һ�۸����ϸ�3��ticks


QL_Dynamic					= 1	# ��ֹ̬��
QL_Static   				        = 2	# ��ֹ̬��


QL_Dynamic_Capital					= 0	# ��ֹ̬��
QL_Static_Capital   				        = 1	# ��ֹ̬��


QL_POSITION_Sell_Today               =9001  # ���տյ�
QL_POSITION_Buy_Today                =9002  # ���ն൥
QL_POSITION_Sell_History             =9003  # �ǽ��տյ�
QL_POSITION_Buy_History              =9004  # �ǽ��ն൥
QL_POSITION_Sell_All                 =9005  # ���пյ�
QL_POSITION_Buy_All                  =9006  # ���ж൥
