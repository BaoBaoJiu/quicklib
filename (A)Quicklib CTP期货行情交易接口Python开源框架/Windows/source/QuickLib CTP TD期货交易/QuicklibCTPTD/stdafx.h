/*
1.���ļ�ΪQuicklib �ڻ����׿�ײ����
2.���ļ������õĿ��ļ�Quicklib CTP�ڻ������ͽ��׿���ѭ ��ԴЭ��GPL v3
�򵥵�˵���Ի���GPL v3Э���Դ���룬�����˻�����������Լ�ʹ�ã�����Ա�Դ��
�����ڸÿ�Դ���룬�����������������Ʒ������ҵ��Ϊ��Ҳ���뿪Դ��

Quciklib Python��ܺ͹�����ѭGPL v3Э�������
��1��Quicklib CTP   �ڻ������
��2��Quicklib CTP   �ڻ����׿�
��3��Quicklib CTP2  A�������
��4��Quicklib MOMģʽ  �����ʹܽ��׿�
�����ڽ����ʹ�Ͷ��ϵͳ��MOMģʽ��ʵ��˽ļ����Ͷ�˵�ѡ�ο��ˣ���ͨ���Լ��ķ��ϵͳ����ʵ�̣�

Quciklib Python��ܺ͹����ݲ���ѭ��ԴЭ�������
��5��Quicklib ������⣨Ԥ������ء������ź����ݸ��ơ�����������������ã�

��Quciklib��Դ���������׵ģ����õ�ԭʼ���߿϶��ģ���������http://www.quciklib.cn��վ�ϣ�
������ڡ���Դ˵���͸�л.txt�����������ļ����ϸ��·���ÿһ���°汾��Quicklib���

ԭʼ���ߣ�QQ 147423661 ��(���Ǹ�)
�ٷ���վ��http://www.quicklib.cn
�ٷ�QQȺ��5172183(1Ⱥ)��25884087(2Ⱥ)
*/

#pragma once

#undef UNICODE
#undef _UNICODE

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
#include "ThostTraderApi/ThostFtdcUserApiDataType.h"
#include "ThostTraderApi/ThostFtdcUserApiStruct.h"
#include "ThostTraderApi/ThostFtdcTraderApi.h"

#include <string>
#include <iostream>
#include <map>
#include <fstream>

#define PYCTPTRADER_EXPORTS

#define TYPE_NUM 20  //Ʒ������Ӧ����MD ����һ��

#include <list>
struct cmdcontent
{
	int cmd;
	char content[31];
};
struct TT
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

//MAX_EVENTNUMȡ�������ûص��¼���������ֵ64�������64��ָ����ø���Ϊ����64��ֵ
#define MAX_EVENTNUM  64
//�ص��¼�����"EID_Function"��ʽ,����"EID_"��ͷ��"Function"�ǽ��յ��˻ص��¼��ص�����������
#define  EID_OnFrontDisconnected      0
#define  EID_OnFrontConnected         1
#define  EID_OnRspUserLogin_Scuess    2
#define  EID_OnRspUserLogin_Failer    3
#define  EID_OnRspUserLoginout_Scuess 4
#define  EID_OnRspUserLoginout_Failer 5
#define  EID_OnRtnDepthMarketData     6
#define  EID_IsErrorRspInfo           7
#define  EID_OnRspSubMarketData       8
#define  EID_OnRspUnSubMarketData     9
#define  EID_OnRspUserLogout          10

//trader
#define  EID_OnRspOrder                     11
#define  EID_OnRspTrade                     12     //add  2016.12.28
#define  EID_OnRtnInstrumentStatus          13     //add
#define  EID_OnRspQryAccountregister        14     //add ǩԼ��ϵ��Ӧ

#define  EID_OnRtnFromBankToFutureByFuture  15     //add
#define  EID_OnRtnFromFutureToBankByFuture  16     //add
#define  EID_OnRspQueryMaxOrderVolume       17     //add
#define  EID_OnRspSettlementInfoConfirm     18    //add

//�ص�����
#define TD_SYSTEM_NONE                8000 //��
#define TD_LOGIN_SCUESS               8001 //��¼�ɹ�
#define TD_LOGIN_DENIED               8002 //��¼���ܾ�
#define TD_LOGIN_ERRORPASSWORD        8003 //������� ??
#define TD_LOGINOUT_SCUESS            8004 //�ǳ��ɹ�
#define TD_LOGINOUT_DENIED            8005 //��¼���ܾ�    //ADD 2016.12.28
#define TD_NETCONNECT_SCUESS          8006 //���ӳɹ�
#define TD_NETCONNECT_BREAK           8007 //�Ͽ�����
#define TD_NETCONNECT_FAILER          8008 //����ʧ�� ??
//#define SYSTEM_SUBCRIBE_SCUESS  8008 //���ĳɹ�
//#define SYSTEM_UNSUBCRIBE_SCUESS  8009 //ȡ�����ĳɹ�
//#define SYSTEM_NEWTICK  8010 //��Tick����
#define TD_SYSTEM_ERROR  8011 //����Ӧ��

#define TD_ORDER_INFO                 8012 //ORDER
#define TD_TRADE_INFO                 8013 //TRADER
#define TD_INSTRUMENT_STATUS          8014 //��Լ����״̬

#define TD_QUERY_ACCOUNTREGISTER      8015 //ǩԼ��ϵ��Ӧ
#define TD_BYFUTURE_BANKTOFUTURE      8016 //�ڻ����������ʽ�ת�ڻ�֪ͨ
#define TD_BYFUTURE_FUTURETOBANK      8017 //�ڻ������ڻ��ʽ�ת����֪ͨ
#define TD_QUERY_MAXORDERVOLUME       8018 //

#define TD_SETTLEMENTINFOCONFIRM      8019