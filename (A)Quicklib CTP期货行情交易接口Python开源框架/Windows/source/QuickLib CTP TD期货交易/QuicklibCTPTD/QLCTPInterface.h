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

#ifdef PYCTPTRADER_EXPORTS
#	define QUICKLIB_TD_API __declspec(dllexport)
#else
#	define QUICKLIB_TD_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

int QUICKLIB_TD_API Login();

int QUICKLIB_TD_API InsertOrderByRate(char *Instrument, char direction, char offsetFlag, char priceType, double price,double rate, bool BalanceType,int multiplier);
int QUICKLIB_TD_API InsertOrder(char *Instrument,char direction, char offsetFlag, char priceType, double price, int num);
int QUICKLIB_TD_API DeleteOrder(char *Instrument, int OrderRef);
int QUICKLIB_TD_API QryTradedVol(int OrderRef);
int QUICKLIB_TD_API QryPosition(char *Instrument,int positiontype);   

int QUICKLIB_TD_API ReqQueryMaxOrderVolume(char * BrokerID, char * InvestorID, char * InstrumentID, char Direction, char  OffsetFlag, char  HedgeFlag, int MaxVolume);

int  QUICKLIB_TD_API ReqQryContractBank();
double  QUICKLIB_TD_API QryExchangeMarginRate(char *Instrument, int positiontype);    //��֤����
double  QUICKLIB_TD_API QryUnderlyingMultiple(char *Instrument);    //����

///�ڻ����������ʽ�ת�ڻ�����
//int  QUICKLIB_TD_API  ReqFromBankToFutureByFuture(int nRequestID);  //ADD

int  QUICKLIB_TD_API  ReqFromBankToFutureByFuture(
	char * BankID,
	//char * BankBranchID,
	//char * BrokerID,
	char *  BrokerBranchID,
	char *BankAccount,
	char * BankPassWord,
	char * AccountID,
	//char *Password,
	//char * CurrencyID,
	double  TradeAmount,
	int nRequestID);

///�ڻ������ڻ��ʽ�ת��������
int  QUICKLIB_TD_API  ReqFromFutureToBankByFuture(
	char * BankID,
	//char * BankBranchID,
	//char * BrokerID,
	char *  BrokerBranchID,
	char *BankAccount,
	char * BankPassWord,
	char * AccountID,
	//char *Password,
	//char * CurrencyID,
	double  TradeAmount,
	int nRequestID);  //ADD



int QUICKLIB_TD_API ReqQryInstrument();



void QUICKLIB_TD_API *QryPositionList(int i);
double QUICKLIB_TD_API QryBalance(bool BalanceType);     //1��̬Ȩ�� 0��̬Ȩ�� �Լ�����
double QUICKLIB_TD_API QryAvailable();   //�����ʽ�
void QUICKLIB_TD_API SetShowPosition(bool showstate);   //�����ʽ�

int QUICKLIB_TD_API GetCmd();
QUICKLIB_TD_API char * GetCmdContent2();

void QUICKLIB_TD_API * GetCmdContent();

void QUICKLIB_TD_API * GetCmdContent_Order();
void QUICKLIB_TD_API * GetCmdContent_Trade();


void QUICKLIB_TD_API * GetCmdContent_BankToFutureByFuture();
void QUICKLIB_TD_API * GetCmdContent_FutureToBankByFuture();

void QUICKLIB_TD_API * GetCmdContent_QueryMaxOrderVolume();


void QUICKLIB_TD_API * GetCmdContent_Settlement();
void QUICKLIB_TD_API * GetCmdContent_Error();

void QUICKLIB_TD_API * GetCmdContent_LoginScuess();
void QUICKLIB_TD_API * GetCmdContent_Connected();
void QUICKLIB_TD_API * GetCmdContent_ProductGroupMargin();
void QUICKLIB_TD_API * GetCmdContent_CommissionRate();


void QUICKLIB_TD_API * GetCmdContent_AccountRegist();

void QUICKLIB_TD_API * GetCmdContent_BankToFutureByFuture();
void QUICKLIB_TD_API * GetCmdContent_FutureToBankByFuture();
 


int QUICKLIB_TD_API OnCmd();
int QUICKLIB_TD_API GetUnGetCmdSize();

//double QUICKLIB_TD_API QryAvailable2();   //�����ʽ�
#ifdef __cplusplus
}
#endif