/*
1.���ļ�ΪQuicklib �ڻ�����API�ʹܽ��׿�ײ����
2.���ļ������õĿ��ļ�Quicklib ����API(����CTP��ֻ�Ƕ�һ���������)�ڻ����׿�ͽ��׿���ѭ ��ԴЭ��GPL v3
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

//��Ȩ����
#include "SharedMemoryServer.h"
#define MAX_MAP_NUM   3000  //�ڴ湲������
#define MAX_PROCESS_NUM   300  //�ڴ湲��

 
//RSA
#include <atlstr.h> 
//#include "RSABigInt.h"
//RSA

//HANDLE hMapFileHash[MAX_PROCESS_NUM];//��������CRC32ֵ
class QLCTPTraderSpi: public CThostFtdcTraderSpi
{
public:

	//��Ȩ����

	//�ڴ湲��
	bool CheckMemoryExit();
	HANDLE hMapFile[MAX_MAP_NUM];
	LPCTSTR pBuf;
	//void WriteToMemory(const char *mdata, int id);
	//void WriteToMemoryProcess(const char *mdata, int id);
	//void WriteToMemoryProcessID(const char *mdata, int id);
	//�ڴ湲��

	int id = -1;
	int licnum = 5; //��Ȩ����
	int processid = MAX_MAP_NUM; //�����ױ�ռ��

	HANDLE hMapFileMaxProcessID;//�������IDֵ������

	bool CheckMemoryExit2();
	//bool ExitCheckState;
	//��Ȩ����

	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason); //��ӵ�

	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);//�ͻ�����֤��Ӧ //need


	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//�ǳ�������Ӧ 
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast); //need



	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, 
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);  //ADD 2016.12.28

	//��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);//ADD


	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);	//�Լ����� 

 


	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);





	virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///�����ѯ��Լ��֤������Ӧ
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///�����ѯ��Լ����������Ӧ
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXӦ�úϲ�һ��
	///�����ѯ��Լ��Ӧ					
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspQryInstrument2(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	///��ѯ��󱨵�������Ӧ
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//�����ӵ�


	///�����ѯ����ǩԼ��ϵ��Ӧ
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ڻ����������ʽ�ת�ڻ�֪ͨ
	virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);

	///�ڻ������ڻ��ʽ�ת����֪ͨ
	virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);


 public: //����Ϊpublic
		///�����ѯ�ʽ��˻�
	void ReqQryTradingAccount();
	///�����ѯͶ���ֲ߳�
	void ReqQryInvestorPosition();
 	///�����ѯ��Լ(����)
	void ReqQryInstrument(char *Instrument);

	///��ѯ��󱨵���������
	int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID);
 
	//��ѯ��֤���ʣ�����
	void  ReqQryInvestorProductGroupMargin(char *Instrument);
	void  ReqQryInstrumentMarginRate(char *Instrument);
	//void ReqQryInvestorPosition();


	///�����ѯ��Լ
	int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);

	///�����ѯת����ˮ
	//virtual int ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID);

	///�����ѯ����ǩԼ��ϵ
	//virtual int ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID);

	///�����ѯǩԼ����
	virtual int ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID);


	///�ڻ����������ʽ�ת�ڻ�����
	int ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID);

	///�ڻ������ڻ��ʽ�ת��������
	int ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID);







	HANDLE hSyncObj;
	int iRequestID;
	int iOrderRef;
	bool bInitOK;

	int FRONT_ID;
	int SESSION_ID;

public:

	int InsertOrder(char *InstrumentID, TThostFtdcDirectionType dir,char offsetFlag, char priceType, double price, int num);

	int DeleteOrder(char *InstrumentID, DWORD orderRef);

	void ReqUserLogin();

	void ReqSettlementInfoConfirm();

	QLCTPTraderSpi();
	~QLCTPTraderSpi();

	bool Init();
	bool IsInitOK(){return bInitOK;}
};