/*
1.���ļ�ΪQuicklib �ڻ������ײ����
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
#include <map>
#include <string>
#include <algorithm>
#include "iostream"

#include <iostream> 
#include <windows.h>
using namespace std;
struct InstrumentInfo
{
	string strategyfile[300];
	//int strategy[100];
	int strategyfilenum;
	int position[100];
	bool tradestate;
};

#include "def.h"
/*
class CStrategy : public CWinThread
{
public:
	//CStrategy();
	void strategy();

};
 */

class CMdSpi : public CThostFtdcMdSpi
{

public:

	double begintime1;
	double begintime2;
	double begintime3;
	double begintime4;

	double endtime1;
	double endtime2;
	double endtime3;
	double endtime4;
	//void  strategy();
	//CStrategy *m_pCStrategyThread;


	BOOL mInitOK;
	HANDLE mhSyncObj;
	CThostFtdcMdApi *mpUserApi;

	int RequestID;
	//void strategy();

	//int savetickstate;

	void WirteTick_Detail(const char * InstrumentID, const CThostFtdcDepthMarketDataField *pDepthMarketData);
	void WirteTick_Simple(const char * InstrumentID, const char * ticktime, double price);


	CMdSpi();
	~CMdSpi();
	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);


 
	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///ѯ��֪ͨ
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	// class CthostMdApi::Init()
	BOOL Init();

	BOOL IsInitOK(){return mInitOK;}

    //ѯ��
	void SubscribeForQuoteRsp(char * InstrumentID);

	void SubscribeMarketData();
	void UnSubscribeMarketData();

	int ReqUserLogin();

	int ReqUserLogout();

	char * GetApiVersion();

	char *  GetTradingDay();
	void   RegisterFront(char *pszFrontAddress);
	void   RegisterNameServer(char *pszNsAddress);
private:

	// 
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);

};
