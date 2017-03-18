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
#include "stdafx.h"
#include "CTPTraderSpi.h"
CRITICAL_SECTION g_csdata;

//CRITICAL_SECTION g_csdata;

using namespace std;
extern list <cmdcontent> cmdlist;
//extern list <cmdcontent>::iterator cmd_Iter;

extern list <CThostFtdcOrderField> orderlist;
//extern list <CThostFtdcOrderField>::iterator order_Iter;

extern list <CThostFtdcTradeField> tradelist;
//extern list <CThostFtdcTradeField>::iterator trade_Iter;

extern list <CThostFtdcAccountregisterField> qryaccountregisterlist;
//extern list <CThostFtdcAccountregisterField>::iterator qryaccountregister_Iter;

extern list <CThostFtdcRspTransferField> banktofuturebyfuturelist;
//extern list <CThostFtdcRspTransferField>::iterator banktofuturebyfuture_Iter;

extern list <CThostFtdcRspTransferField> futuretobankbyfuturelist;
//extern list <CThostFtdcRspTransferField>::iterator futuretobankbyfuture_Iter;

extern list <CThostFtdcQueryMaxOrderVolumeField>  querymaxordervolumelist;
//extern list <CThostFtdcQueryMaxOrderVolumeField>::iterator querymaxordervolume_Iter;

extern list <CThostFtdcInstrumentStatusField> InstrumentStatuslist;
//extern list <CThostFtdcInstrumentStatusField>::iterator InstrumentStatus_Iter;

extern list <CThostFtdcRspInfoField> errorlist;
//extern list <CThostFtdcRspInfoField>::iterator error_Iter;

extern list <CThostFtdcSettlementInfoConfirmField> settlementlist;
//extern list <CThostFtdcSettlementInfoConfirmField>::iterator settlement_Iter;

extern list <CThostFtdcRspUserLoginField> loginlist;
//extern list <CThostFtdcRspUserLoginField>::iterator login_Iter;

extern list <CThostFtdcUserLogoutField> loginoutlist;
//extern list <CThostFtdcUserLogoutField>::iterator loginout_Iter;

extern list <int> connectlist;
//extern list <int>::iterator connect_Iter;

///�����ѯ��Լ��֤������Ӧ
extern list <CThostFtdcInstrumentMarginRateField> MarginRatelist;
//extern list <CThostFtdcInstrumentMarginRateField>::iterator MarginRate_Iter;

///�����ѯ��Լ����������Ӧ
extern list <CThostFtdcInstrumentCommissionRateField> CommissionRatelist;
//extern list <CThostFtdcInstrumentCommissionRateField>::iterator CommissionRate_Iter;


#include <process.h>
extern HANDLE hEvent[MAX_EVENTNUM];


extern std::string gTDFrontAddr[3];
extern std::string gBrokerID;
extern std::string gUserID;
extern std::string gPassword;

extern HANDLE ghTradedVolMutex;
extern std::map<int, int> gOrderRef2TradedVol;

//����
std::map<std::string, double> gUnderlyingMultiple;


//��֤����
std::map<std::string, double> gMarginRate_long;
std::map<std::string, double> gMarginRate_short;
//��������
std::map<std::string, double> gCommissionRate;

//��ѯ��󱨵�����
std::map<std::string, int> gMaxOrderVolume;
  


//�ֲ�map
std::map<std::string, int> gPosition_S;
std::map<std::string, int> gPosition_B;

std::map<std::string, int> gPosition_S_Today;
std::map<std::string, int> gPosition_B_Today;
std::map<std::string, int> gPosition_S_History;
std::map<std::string, int> gPosition_B_History;


std::map<std::string, int> gTypeCheckState_S_Today;
std::map<std::string, int> gTypeCheckState_B_Today;
std::map<std::string, int> gTypeCheckState_S_History;
std::map<std::string, int> gTypeCheckState_B_History;




//��Ȩ����
CThostFtdcTraderApi *mpUserApi;
//�Լ�����
QLCTPTraderSpi *mpUserSpi;


QLCTPTraderSpi::QLCTPTraderSpi()
{
	bInitOK = false;
	iRequestID = 0;
	iOrderRef = 0;
	FRONT_ID = 0;
	SESSION_ID = 0;

	mpUserApi = NULL;

	hSyncObj = ::CreateEvent(NULL, FALSE, FALSE, NULL);
}

QLCTPTraderSpi::~QLCTPTraderSpi()
{
	std::cout << "-->" << __FUNCTION__ << std::endl;
	if (mpUserApi)
	{
// 		mpUserApi->Release();
// 		mpUserApi = NULL;
	}
	::CloseHandle(hSyncObj);
	std::cout << "<--" << __FUNCTION__ << std::endl;
}

#include <ShellApi.h> //ShellExecute
#include <iostream> 
#include <fstream> 
using namespace std;
void  WirteUpdateNotice()
{
	/*
	char str[200] = { 0 };
	strcat_s(str, 200, "QuickLib���¿������ʾ.txt");
	//����ļ��Ƿ���ڣ��Ƿ���Ҫ�½��ı��ļ�
	ifstream inf;
	ofstream ouf;
	inf.open(str, ios::out);
	//}
	if (inf)
	{
		ofstream o_file(str, ios::app);
	}
	//��¼TICK����
	ofstream o_file(str, ios::app);
	//if ( RunMode && ( check0 || check1 || check2) )

	//printf("xxxxxxxxxxxxxx%.06f\n",dbtoch(tick_data[id][1]));

	//<<
	//ticktime << "," 
	//<< price 


	//o_file << "�����Ѿ����ڣ���ȥ�ٷ���վhttp://www.quicklib.cn �������°汾" << endl;



	o_file.close();						//�ر��ļ�
	*/
}


bool GState = true;
DWORD WINAPI PositionThreadProc(void* p)	//��������
{
	while (true)
	{
		//CxHashList[0].HashSortUpdata();
		//mpUserApi->
		GState = !GState;
		if (GState)
		{
			//mpUserApi->ReqQryInvestorPosition
			//mpUserApi->
				mpUserSpi->ReqQryInvestorPosition();//��λ����		

				         //mpUserSpi->ReqQryInvestorPositionDetail();
		}
		else
		{
			//mpUserApi->
				mpUserSpi->ReqQryTradingAccount(); //�ʽ�

		}

		Sleep(3000);
	}

}

DWORD WINAPI ReqQryInstrumentMarginRateThreadProc(void* p)	//��������
{

	 	mpUserSpi->ReqQryInstrumentMarginRate("rb1701");//��λ����		
		return 1;
}  



/*
void QLCTPTraderSpi::ReqQryInvestorPosition()
{

	if (mpUserApi == NULL)
	{
		//cout << "--->>>ReqQryInvestorPositionָ�����" << endl;			  //ָ����
		//WirteTradeRecordToFileMainThread(0, "ReqQryInvestorPositionָ�����");
		return;
	}


	// WirteTradeRecordToFileMainThread(0, "ReqQryInvestorPosition");


	//CThostFtdcQryInvestorPositionField req = { 0 };
	//strcpy(req.BrokerID, m_BrokerID);
	//strcpy(req.InvestorID, m_InvestorInfos[reqInfo.lAccIdx].InvestorID);
	//req.InstrumentID; //ָ����Լ�Ļ������ǲ�ѯ�ض���Լ�ĳֲ���Ϣ��������ǲ�ѯ���гֲ�  
	//ReqQryInvestorPosition(&req, reqInfo.nRequestID);


	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	//strcpy(req.BrokerID, BROKER_ID);
	//strcpy(req.InvestorID, INVESTOR_ID);
	//strcpy(req.InstrumentID, INSTRUMENT_ID);
	//printf("ָ���ֲ�%s", INSTRUMENT_ID);
	int iResult = mpUserApi->ReqQryInvestorPosition(&req, ++iRequestID);
	cerr << "--->>> �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

*/

bool QLCTPTraderSpi::Init()
{
	printf("QuickLib(Trader.CTP for Python)2.09\n");
	char dir[256] = {0};
	//::ZeroMemory(dir, 256);
	::GetCurrentDirectory(255, dir);
	std::string tempDir = std::string(dir).append(".\\CTP\\");
	::CreateDirectory(tempDir.c_str(), NULL);

	mpUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(".\\CTP\\");

	mpUserSpi = this;//�Լ�����
	mpUserApi->RegisterSpi(this);
	mpUserApi->SubscribePublicTopic(THOST_TERT_QUICK);
	mpUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	mpUserApi->RegisterFront((char *)gTDFrontAddr[0].c_str());
	mpUserApi->RegisterFront((char *)gTDFrontAddr[1].c_str());
	mpUserApi->RegisterFront((char *)gTDFrontAddr[2].c_str());

	std::cout << "Init..." << std::endl;
	mpUserApi->Init();
	DWORD err = ::WaitForSingleObject(hSyncObj, 10000);

	if (err == WAIT_OBJECT_0)
	{
		bInitOK = true;
	}

	//��Ȩ״̬
	//ExitCheckState =CheckMemoryExit2();


	//��ѯ�ֲ��߳�
	HANDLE hThread3 = ::CreateThread(NULL, 0, PositionThreadProc, NULL, 0, NULL);
	HANDLE hThread4 = ::CreateThread(NULL, 0, ReqQryInstrumentMarginRateThreadProc, NULL, 0, NULL);

	return bInitOK;
}

void QLCTPTraderSpi::OnFrontConnected()
{
	std::cout << __FUNCTION__ << std::endl;
	CThostFtdcReqUserLoginField req;
	::ZeroMemory(&req, sizeof(req));
	strcpy(req.BrokerID, gBrokerID.c_str());
	strcpy(req.UserID, gUserID.c_str());
	strcpy(req.Password, gPassword.c_str());

	int re = mpUserApi->ReqUserLogin(&req, ++iRequestID);

	cmdcontent tn;
	memset(&tn, 0, sizeof(cmdcontent));
	strncpy_s(tn.content, sizeof(tn.content), "���ӽ��׷������ɹ�", sizeof("���ӽ��׷������ɹ�"));
	tn.cmd = TD_NETCONNECT_SCUESS;
	EnterCriticalSection(&g_csdata);
	cmdlist.push_back(tn);
	LeaveCriticalSection(&g_csdata);
	SetEvent(hEvent[EID_OnFrontConnected]);
}

void QLCTPTraderSpi::OnFrontDisconnected(int nReason)
{
	SYSTEMTIME t;
	::GetLocalTime(&t);
	std::cout << t.wHour << ":" << t.wMinute << ":" << t.wSecond << std::endl;
	std::cout << "--->>> " << __FUNCTION__ << std::endl;
	std::cout << "--->>> Reason = " << nReason << std::endl;
	::Beep(450, 10000);
	//��ϮMD��
	cmdcontent tn;
	memset(&tn, 0, sizeof(cmdcontent));
	strncpy_s(tn.content, sizeof(tn.content), "�뽻�׷������Ͽ�����", sizeof("�뽻�׷������Ͽ�����"));
	tn.cmd = TD_NETCONNECT_BREAK;
	EnterCriticalSection(&g_csdata);
	cmdlist.push_back(tn);
	LeaveCriticalSection(&g_csdata);
	//LeaveCriticalSection(&g_csdata);
	SetEvent(hEvent[EID_OnFrontDisconnected]);
}

//�ͻ�����֤��Ӧ
void QLCTPTraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//SYSTEMTIME t;
	//::GetLocalTime(&t);
	//std::cout << t.wHour << ":" << t.wMinute << ":" << t.wSecond << std::endl;
	//std::cout << "--->>> " << __FUNCTION__ << std::endl;
	//std::cout << "--->>> Reason = " << nReason << std::endl;
	//::Beep(450, 10000);
	//��ϮMD��
	//cmdcontent tn;
	//memset(&tn, 0, sizeof(cmdcontent));
	//strncpy_s(tn.content, sizeof(tn.content), "�뽻�׷������Ͽ�����", sizeof("�뽻�׷������Ͽ�����"));
	//tn.cmd = TD_NETCONNECT_BREAK;
	//EnterCriticalSection(&g_csdata);
	//cmdlist.push_back(tn);
	//LeaveCriticalSection(&g_csdata);
	//LeaveCriticalSection(&g_csdata);
	//SetEvent(hEvent[EID_OnFrontDisconnected]);
}




void QLCTPTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspUserLogin==NULL)
	{
		return;
	}

	std::cout << __FUNCTION__ << std::endl;
	FRONT_ID = pRspUserLogin->FrontID;
	SESSION_ID = pRspUserLogin->SessionID;
	//if (bIsLast)
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
		{
			printf("Failer:��¼ʧ��,ErrorID=0x%04x, ErrMsg=%s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

			CThostFtdcRspUserLoginField tn;
			memset(&tn, 0, sizeof(CThostFtdcRspUserLoginField));
			memcpy_s(&tn,sizeof(CThostFtdcRspUserLoginField), pRspUserLogin,sizeof(CThostFtdcRspUserLoginField));
			//strncpy_s(tn.content, sizeof(tn.content), "��¼���������ʧ��", sizeof("��¼���������ʧ��"));
			//tn.cmd = TD_LOGIN_DENIED;
			EnterCriticalSection(&g_csdata);
			loginlist.push_back(tn);
			LeaveCriticalSection(&g_csdata);
			SetEvent(hEvent[EID_OnRspUserLogin_Failer]);

		}
		else
		{
			printf("Scuess:��¼�ɹ�\n");

			CThostFtdcRspUserLoginField tn;
			memset(&tn, 0, sizeof(CThostFtdcRspUserLoginField));
			memcpy_s(&tn, sizeof(CThostFtdcRspUserLoginField), pRspUserLogin, sizeof(CThostFtdcRspUserLoginField));
			//strncpy_s(tn.content, sizeof(tn.content), "��¼����������ɹ�", sizeof("��¼����������ɹ�"));
			//tn.cmd = TD_LOGIN_SCUESS;
			//printf("c++ %s [%s][%s][%s][%d]\n",
				//pRspUserLogin->BrokerID, pRspUserLogin->CZCETime, pRspUserLogin->DCETime, pRspUserLogin->FFEXTime, pRspUserLogin->FrontID
				
				//);
			EnterCriticalSection(&g_csdata);
			loginlist.push_back(tn);
			LeaveCriticalSection(&g_csdata);
			//LeaveCriticalSection(&g_csdata);
			SetEvent(hEvent[EID_OnRspUserLogin_Scuess]);
		   // std::cout << "Scuess:Settlement Info Confirm." << std::endl;
		    ReqSettlementInfoConfirm();
			Sleep(3000);
		}
	}
}
 
void QLCTPTraderSpi::OnRspQryInstrument2(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

	if (pInstrument==NULL)
	{
		return;
	}

	std::cout << __FUNCTION__ << std::endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
		{

			CThostFtdcInstrumentField tn;
			memset(&tn, 0, sizeof(CThostFtdcInstrumentField));
			memcpy_s(&tn, sizeof(CThostFtdcInstrumentField), pInstrument, sizeof(CThostFtdcInstrumentField));
			//strncpy_s(tn.content, sizeof(tn.content), "��¼���������ʧ��", sizeof("��¼���������ʧ��"));

		//	EnterCriticalSection(&g_csdata);
		//	loginoutlist.push_back(tn);
		//	LeaveCriticalSection(&g_csdata);
		//	SetEvent(hEvent[EID_OnRspUserLoginout_Failer]);

		}
		
	}
}

void QLCTPTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pUserLogout==NULL)
	{
		return;
	}

	std::cout << __FUNCTION__ << std::endl;
	//FRONT_ID = pUserLogout->FrontID;
	//SESSION_ID = pUserLogout->SessionID;
	//if (bIsLast)
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
		{
			printf("�ǳ�ʧ��,ErrorID=0x%04x, ErrMsg=%s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

			CThostFtdcUserLogoutField tn;
			memset(&tn, 0, sizeof(CThostFtdcUserLogoutField));
			memcpy_s(&tn, sizeof(CThostFtdcUserLogoutField), pUserLogout, sizeof(CThostFtdcUserLogoutField));
			//strncpy_s(tn.content, sizeof(tn.content), "��¼���������ʧ��", sizeof("��¼���������ʧ��"));
 
			EnterCriticalSection(&g_csdata);
			loginoutlist.push_back(tn);
			LeaveCriticalSection(&g_csdata);
			SetEvent(hEvent[EID_OnRspUserLoginout_Failer]);

		}
		else
		{
			printf("�ǳ��ɹ�\n");

			CThostFtdcUserLogoutField tn;
			memset(&tn, 0, sizeof(CThostFtdcUserLogoutField));
			memcpy_s(&tn, sizeof(CThostFtdcUserLogoutField), pUserLogout, sizeof(CThostFtdcUserLogoutField));
			//strncpy_s(tn.content, sizeof(tn.content), "��¼����������ɹ�", sizeof("��¼����������ɹ�"));
			//printf("c++ %s [%s][%s][%s][%d]\n",
			//pUserLogout->BrokerID, pUserLogout->CZCETime, pUserLogout->DCETime, pUserLogout->FFEXTime, pUserLogout->FrontID

			//);
			EnterCriticalSection(&g_csdata);
			loginoutlist.push_back(tn);
			LeaveCriticalSection(&g_csdata);
 
			SetEvent(hEvent[EID_OnRspUserLoginout_Scuess]);
			//std::cout << "--> Settlement Info Confirm." << std::endl;
			//ReqSettlementInfoConfirm();
			//Sleep(3000);
		}
	}
}

void QLCTPTraderSpi::ReqSettlementInfoConfirm()
{
	std::cout << __FUNCTION__ << std::endl;
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(CThostFtdcSettlementInfoConfirmField));
	strcpy_s(req.BrokerID,sizeof(req.BrokerID), gBrokerID.c_str());
	strcpy_s(req.InvestorID,sizeof(req.InvestorID), gUserID.c_str());
	int iResult=mpUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
	if (iResult != 0)
		cerr << "Failer: Ͷ���߽�����ȷ��: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: Ͷ���߽�����ȷ��: �ɹ�" << endl;
}

void QLCTPTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
 	std::cout << __FUNCTION__ << std::endl;
	if (bIsLast)
	{
		::SetEvent(hSyncObj);
		cmdcontent tn;
		memset(&tn, 0, sizeof(cmdcontent));
		strncpy_s(tn.content, sizeof(tn.content), "ȷ�Ͻ��㵥�ɹ�", sizeof("ȷ�Ͻ��㵥�ɹ�"));
		tn.cmd = TD_SETTLEMENTINFOCONFIRM;
		EnterCriticalSection(&g_csdata);
		cmdlist.push_back(tn);
		LeaveCriticalSection(&g_csdata);
		SetEvent(hEvent[EID_OnRspSettlementInfoConfirm]);
	}
}

bool QLCTPTraderSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
	{
		SYSTEMTIME t;
		::GetLocalTime(&t);
		std::cout << t.wHour << ":" << t.wMinute << ":" << t.wSecond << std::endl;
		std::cout << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
		::Beep(800, 10000);

		CThostFtdcRspInfoField tn;
		memset(&tn, 0, sizeof(CThostFtdcRspInfoField));
		tn.ErrorID = pRspInfo->ErrorID;
		strncpy_s(tn.ErrorMsg, sizeof(tn.ErrorMsg), pRspInfo->ErrorMsg, sizeof(pRspInfo->ErrorMsg));
		EnterCriticalSection(&g_csdata);
		errorlist.push_back(tn);
		LeaveCriticalSection(&g_csdata);
		SetEvent(hEvent[EID_IsErrorRspInfo]);
	}
	return bResult;
}


void QLCTPTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//std::cerr << pRspInfo->ErrorID << "\t" << pRspInfo->ErrorMsg << std::endl;

	IsErrorRspInfo(pRspInfo);

}

void QLCTPTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	if (!pOrder)
	{
		return;
	}
	std::cout << __FUNCTION__ << std::endl;
		int orderRef = ::atoi(pOrder->OrderRef);
		::WaitForSingleObject(ghTradedVolMutex, INFINITE);
		gOrderRef2TradedVol[orderRef] = pOrder->VolumeTraded;
		::ReleaseMutex(ghTradedVolMutex);
	
        CThostFtdcOrderField tn;
		memset(&tn, 0, sizeof(CThostFtdcOrderField));
		memcpy_s(&tn,sizeof(tn), pOrder,sizeof(CThostFtdcOrderField));
		//strncpy_s(tn.content.BrokerID, sizeof(tn.content.BrokerID), pOrder->BrokerID, sizeof(pOrder->BrokerID));
		//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
		//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
		//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));

		//strncpy_s(tn.content.UserID, sizeof(tn.content.UserID), pOrder->UserID, sizeof(pOrder->UserID));
		//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
		//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
		//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
		//tn.cmd = TD_ORDER_INFO;
		EnterCriticalSection(&g_csdata);
		orderlist.push_back(tn);
		LeaveCriticalSection(&g_csdata);
		//LeaveCriticalSection(&g_csdata);
		SetEvent(hEvent[EID_OnRspOrder]);
		

        /*
		ordercontent tn;
		memset(&tn, 0, sizeof(ordercontent));
		//(tn.content, sizeof(tn.content), pRspInfo->ErrorMsg, sizeof(pRspInfo->ErrorMsg));
		tn.cmd = TD_ORDER_INFO;
		EnterCriticalSection(&g_csdata);
		orderlist.push_back(tn);
		LeaveCriticalSection(&g_csdata);
		//LeaveCriticalSection(&g_csdata);
		SetEvent(hEvent[EID_OnRspOrder]);
		*/
	//}
}

void QLCTPTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
 
	if (!pTrade)
	{
		return;
	}
	std::cout << __FUNCTION__ << std::endl;
	//int orderRef = ::atoi(pTrade->OrderRef);
	/*
	::WaitForSingleObject(ghTradedVolMutex, INFINITE);
	gOrderRef2TradedVol[orderRef] = pTrade->VolumeTraded;
	::ReleaseMutex(ghTradedVolMutex);
	*/
	///�ɽ�
	CThostFtdcTradeField tn;
	memset(&tn, 0, sizeof(CThostFtdcTradeField));
	memcpy_s(&tn, sizeof(CThostFtdcTradeField), pTrade, sizeof(CThostFtdcTradeField));
	//strncpy_s(tn.content.BrokerID, sizeof(tn.content.BrokerID), pOrder->BrokerID, sizeof(pOrder->BrokerID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
	//strncpy_s(tn.content.UserID, sizeof(tn.content.UserID), pOrder->UserID, sizeof(pOrder->UserID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
	EnterCriticalSection(&g_csdata);
	tradelist.push_back(tn);
	LeaveCriticalSection(&g_csdata);
	SetEvent(hEvent[EID_OnRspTrade]);

}

//��Լ����״̬֪ͨ
 
void  QLCTPTraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	if (!pInstrumentStatus)
	{
		return;
	}
	///�ɽ�
	
	CThostFtdcInstrumentStatusField tn;
	memset(&tn, 0, sizeof(CThostFtdcInstrumentStatusField));
	memcpy_s(&tn, sizeof(CThostFtdcInstrumentStatusField), pInstrumentStatus, sizeof(CThostFtdcInstrumentStatusField));
	//strncpy_s(tn.content.BrokerID, sizeof(tn.content.BrokerID), pOrder->BrokerID, sizeof(pOrder->BrokerID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
	//strncpy_s(tn.content.UserID, sizeof(tn.content.UserID), pOrder->UserID, sizeof(pOrder->UserID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
	EnterCriticalSection(&g_csdata);
	InstrumentStatuslist.push_back(tn);
	LeaveCriticalSection(&g_csdata);
	SetEvent(hEvent[EID_OnRtnInstrumentStatus]);
}





int QLCTPTraderSpi::DeleteOrder(char *InstrumentID, DWORD orderRef)
{
	//���󷵻�-1�Ǻ�������ͻ����
	if (!InstrumentID)
	{
		return -1;
	}
	std::cout << __FUNCTION__ << std::endl;
	CThostFtdcInputOrderActionField ReqDel;
	::ZeroMemory(&ReqDel, sizeof(ReqDel));
	strcpy(ReqDel.BrokerID, gBrokerID.c_str());
	strcpy(ReqDel.InvestorID, gUserID.c_str());
	strcpy(ReqDel.InstrumentID, InstrumentID);
	::sprintf(ReqDel.OrderRef, "%012d", orderRef);
	ReqDel.FrontID = FRONT_ID;
	ReqDel.SessionID = SESSION_ID;
	ReqDel.ActionFlag = THOST_FTDC_AF_Delete;
	int iResult = mpUserApi->ReqOrderAction(&ReqDel, ++(iRequestID));

	if (iResult != 0)
		cerr << "Failer: ���� : " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: ���� : �ɹ�" << endl;

	return iResult;
}

VOID MakeOrder(CThostFtdcInputOrderField *pOrder)
{
	memset(pOrder, 0, sizeof(*pOrder));
	///���͹�˾����
	strcpy(pOrder->BrokerID, gBrokerID.c_str());
	///Ͷ���ߴ���
	strcpy(pOrder->InvestorID, gUserID.c_str());
	///�û�����
	//TThostFtdcUserIDType	UserID;
	///���Ͷ���ױ���־
	pOrder->CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;	
	///�޼۵�
	pOrder->OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///��������: ����
	pOrder->ContingentCondition = THOST_FTDC_CC_Immediately;
	///��Ч������: ������Ч
	pOrder->TimeCondition = THOST_FTDC_TC_GFD;
	///GTD����
	//	TThostFtdcDateType	GTDDate;
	///�ɽ�������: �κ�����
	pOrder->VolumeCondition = THOST_FTDC_VC_AV;
	///��С�ɽ���: 1
	pOrder->MinVolume = 1;
	///ֹ���
	//	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��: ��ǿƽ
	pOrder->ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///�Զ������־: ��
	pOrder->IsAutoSuspend = 0;
	///ҵ��Ԫ
	//	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	//	TThostFtdcRequestIDType	RequestID;
	///�û�ǿ����־: ��
	pOrder->UserForceClose = 0;
}







//��Ȩ����

bool QLCTPTraderSpi::CheckMemoryExit()
{
	int i = 0;

	for (int id = 0; id < MAX_MAP_NUM; id++)
	{
		while (i > licnum - 1)
		{
			printf("�ﵽ��Ȩ���� [%d] [%d]\n", i, licnum);
			return true;
		}
		bool exitstate = true;
		//HANDLE hMapFile[id];
		//LPCTSTR pBuf;

		char ids[10] = { 0 };
		_snprintf_s(ids, sizeof(ids), sizeof(ids), "%d", id);

		char szName[50] = { 0 };
		strncpy_s(szName, sizeof(szName), "Global\\", strlen("Global\\"));
		//strcat_s(szName, sizeof(szName), InstrumentID[id]);
		strcat_s(szName, sizeof(szName), ids);

		//printf("%s\n", szName);
		// printf("A2\n");
		hMapFile[id] = OpenFileMapping(
			FILE_MAP_ALL_ACCESS,   // read/write access
			FALSE,                 // do not inherit the name
			szName);               // name of mapping object

		if (hMapFile[id] == NULL)
		{
			//_tprintf(TEXT("Could not open file mapping object (%d).\n"),
			//GetLastError());
			exitstate = false;
		}
		else
		{
			pBuf = (LPTSTR)MapViewOfFile(hMapFile[id], // handle to map object
				FILE_MAP_ALL_ACCESS,  // read/write permission
				0, 0, BUF_SIZE);
			if (pBuf == NULL)
			{
				//_tprintf(TEXT("Could not map view of file (%d).\n"),
				//	GetLastError());
				CloseHandle(hMapFile[id]);
				exitstate = false;
			}
		}

		if (exitstate)
		{
			i++;
			printf("[%d]�ڴ����� [%s]\n", id, pBuf);
		}
		//printf("[%d]�ڴ����� [%s]\n", id, pBuf);
		UnmapViewOfFile(pBuf);  //���ã�����
		CloseHandle(hMapFile);  //����???
	}

	//WriteToMemory(mdata, i);
	return false;
}
bool QLCTPTraderSpi::CheckMemoryExit2()
{
	int i = 0;

	for (int id = 0; id < MAX_MAP_NUM; id++)
	{
		while (i > licnum - 1)
		{
			printf("�ﵽ��Ȩ���� [%d] [%d]\n", i, licnum);
			return true;
		}
		bool exitstate = true;
		//HANDLE hMapFile[id];
		//LPCTSTR pBuf;

		char ids[10] = { 0 };
		_snprintf_s(ids, sizeof(ids), sizeof(ids), "%d", id);

		char szName[50] = { 0 };
		strncpy_s(szName, sizeof(szName), "Global\\", strlen("Global\\"));
		//strcat_s(szName, sizeof(szName), InstrumentID[id]);
		strcat_s(szName, sizeof(szName), ids);

		//printf("%s\n", szName);
		// printf("A2\n");
		hMapFile[id] = OpenFileMapping(
			FILE_MAP_ALL_ACCESS,   // read/write access
			FALSE,                 // do not inherit the name
			szName);               // name of mapping object

		if (hMapFile[id] == NULL)
		{
			//_tprintf(TEXT("Could not open file mapping object (%d).\n"),
			//GetLastError());
			exitstate = false;
		}
		else
		{
			pBuf = (LPTSTR)MapViewOfFile(hMapFile[id], // handle to map object
				FILE_MAP_ALL_ACCESS,  // read/write permission
				0, 0, BUF_SIZE);
			if (pBuf == NULL)
			{
				//_tprintf(TEXT("Could not map view of file (%d).\n"),
				//	GetLastError());
				CloseHandle(hMapFile[id]);
				exitstate = false;
			}
		}

		if (exitstate)
		{
			i++;
			printf("[%d]�ڴ����� [%s]\n", id, pBuf);
		}
		//printf("[%d]�ڴ����� [%s]\n", id, pBuf);
		UnmapViewOfFile(pBuf);  //���ã�����
		CloseHandle(hMapFile);  //����???
	}
	//printf("A2\n");

	//WriteToMemory(mdata, i);
	return false;
}

//��Ȩ����



//���ư�
//int maxordernum = 5 + 9;
//int num = 0;
//���ư�

int QLCTPTraderSpi:: InsertOrder(char *InstrumentID, char dir,char offsetFlag, char priceType, double price, int num)
{
	//���ư�
	//num++;
	/*
	while (num > maxordernum)
	{
		return 0;
		break;
	}
	*/
	//���ư�


	//��Ȩ����
	/*	while(ExitCheckState)
	{
		return 0;
		break;
	}


	while (CheckMemoryExit())
	{
		return 0;
		break;
	}
	*/
	//��Ȩ����


	CThostFtdcInputOrderField req;
	MakeOrder(&req);
	::strcpy(req.InstrumentID, InstrumentID);

	req.CombOffsetFlag[0] = offsetFlag;
	req.Direction = dir;
	req.VolumeTotalOriginal = num;
	req.LimitPrice = price;
	req.OrderPriceType = priceType;

	++(iOrderRef);
	::sprintf(req.OrderRef, "%012d", iOrderRef);
	int iResult = mpUserApi->ReqOrderInsert(&req, ++(iRequestID));
	if (iResult != 0)
		cerr << "Failer: �µ�" << InstrumentID << price << num << ": " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �µ�"<< InstrumentID  << price << num <<": �ɹ�" << endl;

	return iOrderRef;
}


///////////////////////////////////////////////////////////////////////////////�Լ�����



void QLCTPTraderSpi::ReqQryInvestorPosition()
{

	if (mpUserApi == NULL)
	{
		return;
	}


	// WirteTradeRecordToFileMainThread(0, "ReqQryInvestorPosition");


	//CThostFtdcQryInvestorPositionField req = { 0 };
	//strcpy(req.BrokerID, m_BrokerID);
	//strcpy(req.InvestorID, m_InvestorInfos[reqInfo.lAccIdx].InvestorID);
	//req.InstrumentID; //ָ����Լ�Ļ������ǲ�ѯ�ض���Լ�ĳֲ���Ϣ��������ǲ�ѯ���гֲ�  
	//ReqQryInvestorPosition(&req, reqInfo.nRequestID);


	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(CThostFtdcQryInvestorPositionField));
	//strcpy(req.BrokerID, BROKER_ID);
	//strcpy(req.InvestorID, INVESTOR_ID);

	strcpy(req.BrokerID, gBrokerID.c_str());
	strcpy(req.InvestorID, gUserID.c_str());
	//strcpy(req.InstrumentID, INSTRUMENT_ID);
	//printf("ָ���ֲ�%s", INSTRUMENT_ID);
	int iResult = mpUserApi->ReqQryInvestorPosition(&req, ++iRequestID);
	//cerr << "--->>> �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
	if (iResult != 0)
		cerr << "Failer: �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �����ѯͶ���ֲ߳�: �ɹ�" << endl;

}

///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
void QLCTPTraderSpi::ReqQryInvestorProductGroupMargin(char *Instrument)
{

	if (mpUserApi == NULL)
	{
		return;
	}


	//CThostFtdcQryInvestorPositionField req = { 0 };
	//strcpy(req.BrokerID, m_BrokerID);
	//strcpy(req.InvestorID, m_InvestorInfos[reqInfo.lAccIdx].InvestorID);
	//req.InstrumentID; //ָ����Լ�Ļ������ǲ�ѯ�ض���Լ�ĳֲ���Ϣ��������ǲ�ѯ���гֲ�  
	//ReqQryInvestorPosition(&req, reqInfo.nRequestID);
	//CThostFtdcQryInvestorProductGroupMarginField
	/*
	///��ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
	struct CThostFtdcQryInvestorProductGroupMarginField
	{
		///���͹�˾����
		TThostFtdcBrokerIDType	BrokerID;
		///Ͷ���ߴ���
		TThostFtdcInvestorIDType	InvestorID;
		///Ʒ��/��Ʒ�ֱ�ʾ
		TThostFtdcInstrumentIDType	ProductGroupID;
		///Ͷ���ױ���־
		TThostFtdcHedgeFlagType	HedgeFlag;
	};
	*/
	CThostFtdcQryInvestorProductGroupMarginField req;
	//CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(CThostFtdcQryInvestorProductGroupMarginField));

	strcpy(req.BrokerID, gBrokerID.c_str());
	strcpy(req.InvestorID, gUserID.c_str());
	req.HedgeFlag = '1';

	//printf("��ѯ��֤��[%s]   [%s]  [%s]", req.BrokerID, req.InvestorID);
	//1>CTPTraderSpi.cpp(654) : error C2664 : ��int CThostFtdcTraderApi::ReqQryInstrumentMarginRate(
	//CThostFtdcQryInstrumentMarginRateField *, int)�� : �޷������� 1 �ӡ�
	//CThostFtdcInstrumentMarginRateField *��ת��Ϊ��CThostFtdcQryInstrumentMarginRateField *��


	//strcpy(req.InstrumentID, INSTRUMENT_ID);
	//printf("ָ���ֲ�%s", INSTRUMENT_ID);
	int iResult = mpUserApi->ReqQryInvestorProductGroupMargin(&req, ++iRequestID);
	//cerr << "--->>> �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;

	if (iResult != 0)
		cerr << "Failer: �����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��: �ɹ�" << endl;
}


int QLCTPTraderSpi::ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID)
{

	int iResult = mpUserApi->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, ++iRequestID);
	if (iResult != 0)
		cerr << "Failer: ��ѯ�µ����ֵ: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: ��ѯ�µ����ֵ: �ɹ�" << endl;

	return iResult;
}

///�ڻ����������ʽ�ת�ڻ�����
int QLCTPTraderSpi::ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{

	int iResult = mpUserApi->ReqFromBankToFutureByFuture(pReqTransfer, ++iRequestID);

	if (iResult != 0)
		cerr << "Failer: �ڻ����������ʽ�ת�ڻ�����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �ڻ����������ʽ�ת�ڻ�����: �ɹ�" << endl;

	return iResult;
}

///�ڻ������ڻ��ʽ�ת��������
int QLCTPTraderSpi::ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{

	int iResult = mpUserApi->ReqFromFutureToBankByFuture(pReqTransfer, ++iRequestID);

	if (iResult != 0)
		cerr << "Failer: �ڻ������ڻ��ʽ�ת��������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �ڻ������ڻ��ʽ�ת��������: �ɹ�" << endl;

	return iResult;
}


void QLCTPTraderSpi::ReqQryInstrument(char *Instrument)
{
	if (mpUserApi == NULL)
	{
		return;
	}

	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(CThostFtdcQryInstrumentField));
	strcpy(req.ExchangeID, "DCE");
	strcpy(req.ExchangeInstID, "");
	strcpy(req.ProductID, "");
	//strcpy(req.BrokerID, gBrokerID.c_str());
	//strcpy(req.InvestorID, gUserID.c_str());
	strcpy(req.InstrumentID, Instrument);

	//printf("��ѯ����[%s]   [%s]  [%s]", req.ExchangeID, req.ProductID, req.InstrumentID);

	int iResult = mpUserApi->ReqQryInstrument(&req, ++iRequestID);
	//cerr << "--->>> �����ѯ��Լ: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;

	if (iResult != 0)
		cerr << "Failer: �����ѯ��Լ: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �����ѯ��Լ: �ɹ�" << endl;
}

void QLCTPTraderSpi::ReqQryInstrumentMarginRate(char *Instrument)
{
	if (mpUserApi == NULL)
	{
		return;
	}

	//CThostFtdcQryInvestorPositionField req = { 0 };
	//strcpy(req.BrokerID, m_BrokerID);
	//strcpy(req.InvestorID, m_InvestorInfos[reqInfo.lAccIdx].InvestorID);
	//req.InstrumentID; //ָ����Լ�Ļ������ǲ�ѯ�ض���Լ�ĳֲ���Ϣ��������ǲ�ѯ���гֲ�  
	//ReqQryInvestorPosition(&req, reqInfo.nRequestID);

	CThostFtdcQryInstrumentMarginRateField req;
	memset(&req, 0, sizeof(CThostFtdcQryInstrumentMarginRateField));

	strcpy(req.BrokerID, gBrokerID.c_str());
	strcpy(req.InvestorID, gUserID.c_str());
	strcpy(req.InstrumentID, Instrument);
	req.HedgeFlag = '1';

	printf("��ѯ��֤��[%s] Ͷ�����˻�[%s]��Լ[%s]\n",req.BrokerID, req.InvestorID, req.InstrumentID);
	//1>CTPTraderSpi.cpp(654) : error C2664 : ��int CThostFtdcTraderApi::ReqQryInstrumentMarginRate(
		//CThostFtdcQryInstrumentMarginRateField *, int)�� : �޷������� 1 �ӡ�
		//CThostFtdcInstrumentMarginRateField *��ת��Ϊ��CThostFtdcQryInstrumentMarginRateField *��
	//printf("\n----------------------------------------\n");

	//strcpy(req.InstrumentID, INSTRUMENT_ID);
	//printf("ָ���ֲ�%s", INSTRUMENT_ID);
	int iResult = mpUserApi->ReqQryInstrumentMarginRate(&req, ++iRequestID);
	//cerr << "--->>> �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;


	if (iResult != 0)
		cerr << "Failer: �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �����ѯͶ���ֲ߳�: �ɹ�" << endl;
}



///�����ѯ��Լ
int QLCTPTraderSpi::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{

	//if (pQryInstrument == NULL)
	//{
	//	return 0;
	//}
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(CThostFtdcQryInstrumentField));

	/*
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	*/
	//strcpy(req.BrokerID, gBrokerID.c_str());
	//strcpy(req.InvestorID, gUserID.c_str());
	//strcpy(req.InstrumentID, Instrument);
	int iResult = mpUserApi->ReqQryInstrument(&req, ++iRequestID);
	if (iResult != 0)
		cerr << "Failer: �����ѯ��Լ: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �����ѯ��Լ: �ɹ�" << endl;
	return iResult;
}

int QLCTPTraderSpi::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID)
{
	if (pQryContractBank == NULL)
	{
		return -1;
	}
	CThostFtdcQryContractBankField req;
	memset(&req, 0, sizeof(CThostFtdcQryContractBankField));

 
	//strcpy(req.BrokerID, gBrokerID.c_str());
	//strcpy(req.InvestorID, gUserID.c_str());
	//strcpy(req.InstrumentID, Instrument);
	int iResult = mpUserApi->ReqQryContractBank(&req, ++iRequestID);
	// cerr << "Failer: �����ѯ����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult<<")"<<endl;
	if(iResult!=0)
	    cerr << "Failer: �����ѯ����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult<<")"<<endl;
	else
		cerr << "Scuess: �����ѯ����: �ɹ�" <<endl;
	return iResult;
}



void QLCTPTraderSpi::ReqQryTradingAccount()
{
	if (mpUserApi == NULL)
	{
		return;
	}
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(CThostFtdcQryTradingAccountField));
	strcpy(req.BrokerID, gBrokerID.c_str());
	strcpy(req.InvestorID, gUserID.c_str());
	int iResult = mpUserApi->ReqQryTradingAccount(&req, ++iRequestID);
 	//cerr << "--->>> �����ѯ�ʽ��˻�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;


	if (iResult != 0)
		cerr << "Failer: �����ѯ�ʽ��˻�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��(") << iResult << ")" << endl;
	else
		cerr << "Scuess: �����ѯ�ʽ��˻�: �ɹ�" << endl;
}


char	InstrumentID_n[TYPE_NUM][10] =
{
	"ni1701", "rb1701","ag1612","m1701","y1701","zn1611","bu1612","ru1701","cs1701","jd1701","pp1701","i1701","al1611","au1612","p1701","CF701","TA701","MA701","FG701" ,"a1701"
};

bool FindStr(int id, char * str)
{

	//char * pdest1 = strstr(InstrumentID_n[id], str);
	//int  result1 = pdest1 - InstrumentID_n[id] + 1;
	//printf("%s  %s\n", InstrumentID_n[id], str);

	if (stricmp(InstrumentID_n[id], str) == 0)
		//if (pdest1 != NULL)
	{	//printf("��%s����%s\n", InstrumentID_n[id],str );
		return true;
	}
	else
	{
		//printf("%s û����%s����\n", str, InstrumentID_n[id]);
		return false;
	}
}

int SaveInstrumentID = { 0 };
bool  checkstate = false;
bool  TypeCheckState_B_Today[TYPE_NUM] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
bool  TypeCheckState_S_Today[TYPE_NUM] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

bool  TypeCheckState_B_History[TYPE_NUM] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
bool  TypeCheckState_S_History[TYPE_NUM] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
///�����ѯͶ���ֲ߳���Ӧ

int errnum = 0;

extern bool showpositionstate;
void QLCTPTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

	if (pInvestorPosition == NULL)
	{
		errnum++;
		if (errnum > 10)
		{
			printf("��β�ѯ�ֲ�ָ�����,���������ļ���ѡ��Ͽ�Ľ��׷�����\n");
		}
		return;
	}
	errnum = 0;



	//WirteTradeRecordToFileMainThread(0, "�����ѯͶ���ֲ߳���ӦOnRspQryInvestorPosition");

	//cerr << "--->>> " << "Ͷ���ֲ߳�����:" << endl;
	// if (bIsLast && !IsErrorRspInfo(pRspInfo))
	//if (bIsLast)
	//{


	/*
	cout << "OnRspQryInvestorPosition  ID: " << nRequestID << endl;
	cout << "��Լ����  ID: " << pInvestorPosition->InstrumentID << endl;
	//cout << "������룺" << pRspInfo->ErrorID << "������Ϣ:" << pRspInfo->ErrorMsg;
	cout << "�ֲֶ�շ���:" << pInvestorPosition->PosiDirection << endl;  //2�൥��3�յ�
	cout << "��λ:" << pInvestorPosition->Position << endl;
	*/

/*
	cout << "[ID]" << nRequestID << "��Լ:"
		<< pInvestorPosition->InstrumentID
		<< "�ֲַ���:" << pInvestorPosition->PosiDirection
		<< "��λ:" << pInvestorPosition->Position
		<< "BrokerID:" << pInvestorPosition->AbandonFrozen
		<< "AbandonFrozen:" << pInvestorPosition->BrokerID
		<< "CashIn:" << pInvestorPosition->CashIn
		<< "a:" << pInvestorPosition->CloseAmount
		<< "b:" << pInvestorPosition->CloseProfit
		<< "c:" << pInvestorPosition->CloseProfitByDate
		<< "d:" << pInvestorPosition->CloseProfitByTrade
		<< "e:" << pInvestorPosition->CloseVolume
		<< "f:" << pInvestorPosition->CombLongFrozen
		<< "g:" << pInvestorPosition->CombPosition
		<< "h:" << pInvestorPosition->CombShortFrozen
		<< "i:" << pInvestorPosition->Commission
		<< "j:" << pInvestorPosition->ExchangeMargin
		<< "k:" << pInvestorPosition->FrozenCash
		<< "l:" << pInvestorPosition->FrozenCommission
		<< "cc:" << pInvestorPosition->FrozenMargin
		<< "m:" << pInvestorPosition->HedgeFlag
		<< "n:" << pInvestorPosition->InstrumentID
		<< "o:" << pInvestorPosition->InvestorID
		<< "p:" << pInvestorPosition->LongFrozen
		<< "q:" << pInvestorPosition->LongFrozenAmount
		<< "r:" << pInvestorPosition->MarginRateByMoney
		<< "s:" << pInvestorPosition->MarginRateByVolume
		<< "t:" << pInvestorPosition->OpenAmount
		<< "u:" << pInvestorPosition->OpenCost
		<< "v:" << pInvestorPosition->OpenVolume
		<< "w:" << pInvestorPosition->PosiDirection
		<< "x:" << pInvestorPosition->Position
		<< "y:" << pInvestorPosition->PositionCost
		<< "z:" << pInvestorPosition->PositionDate
		<< "1:" << pInvestorPosition->PositionProfit
		<< "2:" << pInvestorPosition->PreMargin
		<< "3:" << pInvestorPosition->PreSettlementPrice
		<< "4:" << pInvestorPosition->SettlementID
		<< "5:" << pInvestorPosition->SettlementPrice
		<< "6:" << pInvestorPosition->ShortFrozen
		<< "7:" << pInvestorPosition->ShortFrozenAmount
		<< "8:" << pInvestorPosition->StrikeFrozen
		<< "9:" << pInvestorPosition->StrikeFrozenAmount
		<< "10:" << pInvestorPosition->StrikeFrozen
		<< "11:" << pInvestorPosition->StrikeFrozenAmount
		<< "12:" << pInvestorPosition->TodayPosition
		<< "13:" << pInvestorPosition->TradingDay
		<< "14:" << pInvestorPosition->UseMargin
		<< "15:" << pInvestorPosition->YdPosition

		<< endl;
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	*/

	/*
	[ID]22��Լ:m1609�ֲַ���:2��λ : 0BrokerID : 0AbandonFrozen : 8016CashIn : 0
	a : 162540
	b : 780
	c : 780
	d : 120
	e : 6
	f : 0
	g : 0
	h : 0
	i : 9.71378
	j : 0
	k : 0l : 0cc : 0
	m : 1
	n : m1609
	o : 13100293
	p : 0
	q : 0
	r : 0.1
	s : 0
	t : 0
	u : 0
	v : 0
	w : 2
	x : 0
	y : 0
	z :
	11 : 0
	2 : 0
	3 : 2696
	4 : 1
	5 : 2709
	6 : 0
	7 : 0
	8:0
	9:0
	10:0
	11 : 0
	12 : 0
	13 : 20160504
	14 : 0
	15 : 6
	*/


	while (nRequestID != SaveInstrumentID)
	{
		SaveInstrumentID = nRequestID;

		/*
		for (int i = 0; i < TYPE_NUM; i++)
		{
			TypeCheckState_B_Today[i] = false;
			TypeCheckState_S_Today[i] = false;
			TypeCheckState_B_History[i] = false;
			TypeCheckState_S_History[i] = false;
		}
		*/

		gTypeCheckState_B_History[pInvestorPosition->InstrumentID] = false;
		gTypeCheckState_B_Today[pInvestorPosition->InstrumentID] = false;
		gTypeCheckState_S_History[pInvestorPosition->InstrumentID] = false;
		gTypeCheckState_S_Today[pInvestorPosition->InstrumentID] = false;
		//printf("�²�ѯ��ʼ��\n");
	}

	//printf("\n");
	//for (int i = 0; i <TYPE_NUM; i++)
	//{
		//if (FindStr(i, pInvestorPosition->InstrumentID))
		//{
	
			if (pInvestorPosition->PosiDirection == '2' &&  pInvestorPosition->Position != 0) //ע���İ汾Ҫ�޸�
			{
				if (pInvestorPosition->TodayPosition == 0) //���
				{
					//TypeCheckState_B_History[i] = true;
					gTypeCheckState_B_History[pInvestorPosition->InstrumentID] = true;
					//Trade_dataA_Amount_B_History[i] = pInvestorPosition->Position;

					//�ֲ�map
					gPosition_B_History[pInvestorPosition->InstrumentID] = pInvestorPosition->Position;

					//printf("��ʷ�� [%d]\n", gPosition_B_History[pInvestorPosition->InstrumentID]);

				}
				else
				{
					//TypeCheckState_B_Today[i] = true;
					gTypeCheckState_B_Today[pInvestorPosition->InstrumentID] = true;
					//Trade_dataA_Amount_B_Today[i] = pInvestorPosition->Position;

					//�ֲ�map
					gPosition_B_Today[pInvestorPosition->InstrumentID] = pInvestorPosition->Position;

					//printf("����� [%d]\n", gPosition_B_Today[pInvestorPosition->InstrumentID]);
				}
			}
			else if (pInvestorPosition->PosiDirection == '3' &&  pInvestorPosition->Position != 0)  //ע���İ汾Ҫ�޸�
			{
				if (pInvestorPosition->TodayPosition == 0) //���
				{
					//TypeCheckState_S_History[i] = true;
					gTypeCheckState_S_History[pInvestorPosition->InstrumentID] = true;
					//Trade_dataA_Amount_S_History[i] = pInvestorPosition->Position;

					//�ֲ�map
					gPosition_S_History[pInvestorPosition->InstrumentID] = (pInvestorPosition->Position);

					//printf("��ʷ���� [%d]\n", gPosition_S_History[pInvestorPosition->InstrumentID]);
				}
				else
				{
					//TypeCheckState_S_Today[i] = true;
					gTypeCheckState_S_Today[pInvestorPosition->InstrumentID] = true;
					//Trade_dataA_Amount_S_Today[i] = pInvestorPosition->Position;

					//�ֲ�map
					gPosition_S_Today[pInvestorPosition->InstrumentID] = (pInvestorPosition->Position);

					//printf("������� [%d]\n", gPosition_S_Today[pInvestorPosition->InstrumentID]);
				}
			}

		//}



	//}


	if (bIsLast)
	{
		for (int i = 0; i < TYPE_NUM; i++)
		{
			if(!gTypeCheckState_B_History[pInvestorPosition->InstrumentID])
			//if (!TypeCheckState_B_History[i])
			{
				//Trade_dataA_Amount_B_History[i] = 0;
				//�ֲ�map
				gPosition_B_History[pInvestorPosition->InstrumentID] = 0;
				//printf("��ʷ���0 [%d]\n", gPosition_B_History[pInvestorPosition->InstrumentID]);
			}


			if(!gTypeCheckState_B_Today[pInvestorPosition->InstrumentID])
			//if (!TypeCheckState_B_Today[i])
			{
				//Trade_dataA_Amount_B_Today[i] = 0;
				//�ֲ�map
				gPosition_B_Today[pInvestorPosition->InstrumentID] = 0;

				//printf("�������0 [%d]\n", gPosition_B_Today[pInvestorPosition->InstrumentID]);
			}

			if(!gTypeCheckState_S_History[pInvestorPosition->InstrumentID])
			//if (!TypeCheckState_S_History[i])
			{
				//Trade_dataA_Amount_S_History[i] = 0;
				//�ֲ�map
				gPosition_S_History[pInvestorPosition->InstrumentID] = 0;

				//printf("��ʷ����0 [%d]\n", gPosition_S_History[pInvestorPosition->InstrumentID]);

			}

			if(!gTypeCheckState_S_Today[pInvestorPosition->InstrumentID])
			//if (!TypeCheckState_S_Today[i])
			{
				//Trade_dataA_Amount_S_Today[i] = 0;
				//�ֲ�map
				gPosition_S_Today[pInvestorPosition->InstrumentID] = 0;

				//printf("��������0 [%d]\n", gPosition_S_Today[pInvestorPosition->InstrumentID]);
			}
			if (1)
			{
			//	printf("Ʒ�֣�%s  BUY�ֲ�(���)[%d] BUY�ֲ�(��ʷ��)[%d] SELL�ֲ�(���)[%d] SELL�ֲ�(��ʷ)[%d]\n", InstrumentID_n[i], Trade_dataA_Amount_B_Today[i], Trade_dataA_Amount_B_History[i], Trade_dataA_Amount_S_Today[i], Trade_dataA_Amount_S_History[i]);
			}

		}



	}

	gPosition_S[pInvestorPosition->InstrumentID] = gPosition_S_Today[pInvestorPosition->InstrumentID] + gPosition_S_History[pInvestorPosition->InstrumentID];
	gPosition_B[pInvestorPosition->InstrumentID] = gPosition_B_Today[pInvestorPosition->InstrumentID] + gPosition_B_History[pInvestorPosition->InstrumentID];

	if (showpositionstate)
	{
		printf("%s ��������[%d] ������[%d] �ǽ�������[%d] ����[%d] ����[%d] �ǽ�����[%d]\n", pInvestorPosition->InstrumentID,
		gPosition_S[pInvestorPosition->InstrumentID], gPosition_S_Today[pInvestorPosition->InstrumentID], gPosition_S_History[pInvestorPosition->InstrumentID],
		gPosition_B[pInvestorPosition->InstrumentID], gPosition_B_Today[pInvestorPosition->InstrumentID] , gPosition_B_History[pInvestorPosition->InstrumentID]);
	}



	//TypeNumber[nRequestID] = pInvestorPosition->Position;
	//printf("��� ��%d\n",  pInvestorPosition->Position);

	//printf("Ʒ�֣�%s\n", InstrumentID_n[nRequestID]);

	//printf("*******************************************************************\n");
	///��Լ��֤���Լ������Ѳ�ѯ����
	//for (int i = 0; i < 20; i++)
	//{
	//strcpy(INSTRUMENT_ID,InstrumentID_n[3]);	
	//strcpy(INSTRUMENT_ID, InstrumentID_n[nRequestID]);
	//ReqQryInstrumentMarginRate();
	//ReqQryInstrumentCommissionRate();
	//	Sleep(0);
	//}

	//}

	//END

}




bool  IsErrorRspInfo222(CThostFtdcRspInfoField *pRspInfo)
{
	/*
	cerr << "--->>> " << "IsErrorRspInfo\n" << "0" << endl;	  //ָ����
															  // ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
 
	if (bResult)
	{
		cerr << "--->>> \nErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
		char errmsg[200] = { 0 };
		_snprintf_s(errmsg, sizeof(errmsg), sizeof(errmsg), "OnRspError ErrorID:%d ErrorMsg:%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		//WirteTradeRecordToFileMainThread(0, errmsg);
	}
 

	return bResult;
	*/

	return  ((pRspInfo) && (pRspInfo->ErrorID != 0));
}

double YestayAllAmount=-999999999;

double TodayAllAmount=-999999999;

double UserAmount=-999999999;
void QLCTPTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pTradingAccount == NULL)
	{
		return;
	}


	//cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//cerr << "--->>> ������: " << pTradingAccount->TradingDay << "\n" << endl;
		//cerr << "--->>> \n�����ʽ�: " << (int)(pTradingAccount->Available / 10000) << "��\n" << endl;
		//cerr << "--->>> ��ȡ�ʽ�: " << pTradingAccount->WithdrawQuota  << endl;
		//��̬Ȩ��=���ս���-������+�����
		double preBalance = pTradingAccount->PreBalance - pTradingAccount->Withdraw + pTradingAccount->Deposit;
		//cerr << "--->>> ��̬Ȩ��: " << preBalance  << endl;
		//��̬Ȩ��=��̬Ȩ��+ ƽ��ӯ��+ �ֲ�ӯ��- ������
		double current = preBalance + pTradingAccount->CloseProfit + pTradingAccount->PositionProfit - pTradingAccount->Commission;
		//cerr << "--->>> ��̬Ȩ��: " << current  << endl;

		YestayAllAmount = preBalance; //��̬Ȩ��
		TodayAllAmount = current; //��̬Ȩ��
		UserAmount = pTradingAccount->Available;  //�����ʽ�
		/*
		//��齻����־�ļ��Ƿ���ڣ��Ƿ���Ҫ�½��ı��ļ�
		if (LogFilePaths[0] == '\0')
		{
			strcpy(LogFilePaths, "./AutoTrade/");
			strcat_s(LogFilePaths, pTradingAccount->TradingDay);
			strcat_s(LogFilePaths, ".txt");

			//����ļ��Ƿ���ڣ��Ƿ���Ҫ�½��ı��ļ�
			ifstream inf;
			ofstream ouf;
			inf.open(LogFilePaths, ios::out);
		}
		*/
		///�����ѯͶ���ֲ߳�
		//for (int i = 0; i < 20; i++)
		//{
		//strcpy(INSTRUMENT_ID, InstrumentID_n[3]);
		//ReqQryInvestorPosition();
		//}
	}
}


//����
///�����ѯ��Լ��Ӧ
void QLCTPTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInstrument == NULL)
	{
		return;
	}


	//cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///��Լ
		/*
		struct CThostFtdcInstrumentField
		{
			///��Լ����
			TThostFtdcInstrumentIDType	InstrumentID;
			///����������
			TThostFtdcExchangeIDType	ExchangeID;
			///��Լ����
			TThostFtdcInstrumentNameType	InstrumentName;
			///��Լ�ڽ������Ĵ���
			TThostFtdcExchangeInstIDType	ExchangeInstID;
			///��Ʒ����
			TThostFtdcInstrumentIDType	ProductID;
			///��Ʒ����
			TThostFtdcProductClassType	ProductClass;
			///�������
			TThostFtdcYearType	DeliveryYear;
			///������
			TThostFtdcMonthType	DeliveryMonth;
			///�м۵�����µ���
			TThostFtdcVolumeType	MaxMarketOrderVolume;
			///�м۵���С�µ���
			TThostFtdcVolumeType	MinMarketOrderVolume;
			///�޼۵�����µ���
			TThostFtdcVolumeType	MaxLimitOrderVolume;
			///�޼۵���С�µ���
			TThostFtdcVolumeType	MinLimitOrderVolume;
			///��Լ��������
			TThostFtdcVolumeMultipleType	VolumeMultiple;
			///��С�䶯��λ
			TThostFtdcPriceType	PriceTick;
			///������
			TThostFtdcDateType	CreateDate;
			///������
			TThostFtdcDateType	OpenDate;
			///������
			TThostFtdcDateType	ExpireDate;
			///��ʼ������
			TThostFtdcDateType	StartDelivDate;
			///����������
			TThostFtdcDateType	EndDelivDate;
			///��Լ��������״̬
			TThostFtdcInstLifePhaseType	InstLifePhase;
			///��ǰ�Ƿ���
			TThostFtdcBoolType	IsTrading;
			///�ֲ�����
			TThostFtdcPositionTypeType	PositionType;
			///�ֲ���������
			TThostFtdcPositionDateTypeType	PositionDateType;
			///��ͷ��֤����
			TThostFtdcRatioType	LongMarginRatio;
			///��ͷ��֤����
			TThostFtdcRatioType	ShortMarginRatio;
			///�Ƿ�ʹ�ô��߱�֤���㷨
			TThostFtdcMaxMarginSideAlgorithmType	MaxMarginSideAlgorithm;
			///������Ʒ����
			TThostFtdcInstrumentIDType	UnderlyingInstrID;
			///ִ�м�
			TThostFtdcPriceType	StrikePrice;
			///��Ȩ����
			TThostFtdcOptionsTypeType	OptionsType;
			///��Լ������Ʒ����
			TThostFtdcUnderlyingMultipleType	UnderlyingMultiple;
			///�������
			TThostFtdcCombinationTypeType	CombinationType;
		}
		*/
 
 
	//	printf("VVV���� InstrumentID[%s] UnderlyingMultiple[%d]\n\n", pInstrument->InstrumentID, pInstrument->UnderlyingMultiple  );
 

       gUnderlyingMultiple[pInstrument->InstrumentID] =  pInstrument->UnderlyingMultiple;// LongMarginRatioByMoney;// gPosition_S_Today[pInstrumentMarginRate->InstrumentID] + gPosition_S_History[pInstrumentMarginRate->InstrumentID];
 
	    
	}
 
}

void QLCTPTraderSpi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInvestorProductGroupMargin == NULL)
	{
		return;
	}

 	/*
 
///Ͷ����Ʒ��/��Ʒ�ֱ�֤��
struct CThostFtdcInvestorProductGroupMarginField
{

	///Ʒ��/��Ʒ�ֱ�ʾ
	TThostFtdcInstrumentIDType	ProductGroupID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///����ı�֤��
	TThostFtdcMoneyType	FrozenMargin;
	///��ͷ����ı�֤��
	TThostFtdcMoneyType	LongFrozenMargin;
	///��ͷ����ı�֤��
	TThostFtdcMoneyType	ShortFrozenMargin;
	///ռ�õı�֤��
	TThostFtdcMoneyType	UseMargin;
	///��ͷ��֤��
	TThostFtdcMoneyType	LongUseMargin;
	///��ͷ��֤��
	TThostFtdcMoneyType	ShortUseMargin;
	///��������֤��
	TThostFtdcMoneyType	ExchMargin;
	///��������ͷ��֤��
	TThostFtdcMoneyType	LongExchMargin;
	///��������ͷ��֤��
	TThostFtdcMoneyType	ShortExchMargin;
	///ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfit;
	///�����������
	TThostFtdcMoneyType	FrozenCommission;
	///������
	TThostFtdcMoneyType	Commission;
	///������ʽ�
	TThostFtdcMoneyType	FrozenCash;
	///�ʽ���
	TThostFtdcMoneyType	CashIn;
	///�ֲ�ӯ��
	TThostFtdcMoneyType	PositionProfit;
	///�۵��ܽ��
	TThostFtdcMoneyType	OffsetAmount;
	///��ͷ�۵��ܽ��
	TThostFtdcMoneyType	LongOffsetAmount;
	///��ͷ�۵��ܽ��
	TThostFtdcMoneyType	ShortOffsetAmount;
	///�������۵��ܽ��
	TThostFtdcMoneyType	ExchOffsetAmount;
	///��������ͷ�۵��ܽ��
	TThostFtdcMoneyType	LongExchOffsetAmount;
	///��������ͷ�۵��ܽ��
	TThostFtdcMoneyType	ShortExchOffsetAmount;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
};
	*/

	printf("\n$$$BrokerID[%s]  UseMargin[%0.04f] LongUseMargin[%0.04f]  ShortUseMargin[%0.04f] ExchMargin[%0.08f] LongExchMargin[%0.08f] ShortExchMargin[%0.08f] Commission[%0.08f]\n",
		pInvestorProductGroupMargin->BrokerID,
		pInvestorProductGroupMargin->UseMargin,
		pInvestorProductGroupMargin->LongUseMargin,
		pInvestorProductGroupMargin->ShortUseMargin,
		pInvestorProductGroupMargin->ExchMargin,
		pInvestorProductGroupMargin->LongExchMargin,
		pInvestorProductGroupMargin->ShortExchMargin,
		pInvestorProductGroupMargin->Commission);

}

void QLCTPTraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInstrumentMarginRate == NULL)
	{
		//cout << "--->>>ָ�����OnRspQryTradingAccount" << endl;			  //ָ����
		//WirteTradeRecordToFileMainThread(0, "OnRspQryTradingAccountָ�����");
		return;
	}

	//WirteTradeRecordToFileMainThread(0, "OnRspQryTradingAccount");

	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
         /*
		///��Լ��֤����
         struct CThostFtdcInstrumentMarginRateField
       {
	    ///��Լ����
	    TThostFtdcInstrumentIDType	InstrumentID;
	    ///Ͷ���߷�Χ
	    TThostFtdcInvestorRangeType	InvestorRange;
	    ///���͹�˾����
	    TThostFtdcBrokerIDType	BrokerID;
	    ///Ͷ���ߴ���
	    TThostFtdcInvestorIDType	InvestorID;
	    ///Ͷ���ױ���־
	    TThostFtdcHedgeFlagType	HedgeFlag;
	    ///��ͷ��֤����
	    TThostFtdcRatioType	LongMarginRatioByMoney;
	   ///��ͷ��֤���
	     TThostFtdcMoneyType	LongMarginRatioByVolume;
	    ///��ͷ��֤����
	    TThostFtdcRatioType	ShortMarginRatioByMoney;
	   ///��ͷ��֤���
	    TThostFtdcMoneyType	ShortMarginRatioByVolume;
	    ///�Ƿ���Խ�������ȡ
	    TThostFtdcBoolType	IsRelative;
        };
         */
		////pInstrumentMarginRate->BrokerID;
		//pInstrumentMarginRate->HedgeFlag;
	//	pInstrumentMarginRate->InstrumentID;
		//pInstrumentMarginRate->InvestorID;
		//pInstrumentMarginRate->InvestorRange;
		//pInstrumentMarginRate->IsRelative;
		//pInstrumentMarginRate->LongMarginRatioByMoney;
		//pInstrumentMarginRate->LongMarginRatioByVolume;
		//pInstrumentMarginRate->ShortMarginRatioByMoney;
		//pInstrumentMarginRate->ShortMarginRatioByVolume;
		// if(printfstate)
		 /*
		printf("BrokerID[%s] HedgeFlag[%c]InstrumentID[%s] InvestorID[%s] InvestorRange[%s] IsRelative[%d] LongMarginRatioByMoney[%0.02f] LongMarginRatioByVolume[%0.02f] ShortMarginRatioByMoney[%0.02f] ShortMarginRatioByVolume[%0.02f]\n",pInstrumentMarginRate->BrokerID,
		pInstrumentMarginRate->HedgeFlag,
		pInstrumentMarginRate->InstrumentID,
		pInstrumentMarginRate->InvestorID,
		pInstrumentMarginRate->InvestorRange,
		pInstrumentMarginRate->IsRelative,

		pInstrumentMarginRate->LongMarginRatioByMoney,
		pInstrumentMarginRate->LongMarginRatioByVolume,
		pInstrumentMarginRate->ShortMarginRatioByMoney,
		pInstrumentMarginRate->ShortMarginRatioByVolume);

		 printf("BrokerID[%s]  instrumentID[%s] InvestorRange[%c]  HedgeFlag[%c] LongMarginRatioByMoney[%0.08f] LongMarginRatioByVolume[%0.08f] ShortMarginRatioByMoney[%0.08f] ShortMarginRatioByVolume[%0.08f]\n", 
			 pInstrumentMarginRate->BrokerID,
			 pInstrumentMarginRate->InstrumentID,
			 pInstrumentMarginRate->InvestorRange,
			 pInstrumentMarginRate->HedgeFlag,
			 pInstrumentMarginRate->LongMarginRatioByMoney,
			 pInstrumentMarginRate->LongMarginRatioByVolume,
			 pInstrumentMarginRate->ShortMarginRatioByMoney,
			 pInstrumentMarginRate->ShortMarginRatioByVolume);
		*/
		 gMarginRate_long[pInstrumentMarginRate->InstrumentID] = pInstrumentMarginRate->LongMarginRatioByMoney;// LongMarginRatioByMoney;// gPosition_S_Today[pInstrumentMarginRate->InstrumentID] + gPosition_S_History[pInstrumentMarginRate->InstrumentID];
		 gMarginRate_short[pInstrumentMarginRate->InstrumentID] = pInstrumentMarginRate->ShortMarginRatioByMoney;// gPosition_S_Today[pInstrumentMarginRate->InstrumentID] + gPosition_S_History[pInstrumentMarginRate->InstrumentID];

		//cerr << "--->>> ������: " << pTradingAccount->TradingDay << "\n" << endl;
		//cerr << "--->>> \n�����ʽ�: " << (int)(pTradingAccount->Available / 10000) << "��\n" << endl;
		//cerr << "--->>> ��ȡ�ʽ�: " << pTradingAccount->WithdrawQuota  << endl;
		//��̬Ȩ��=���ս���-������+�����
		//double preBalance = pTradingAccount->PreBalance - pTradingAccount->Withdraw + pTradingAccount->Deposit;
		//cerr << "--->>> ��̬Ȩ��: " << preBalance  << endl;
		//��̬Ȩ��=��̬Ȩ��+ ƽ��ӯ��+ �ֲ�ӯ��- ������
		//double current = preBalance + pTradingAccount->CloseProfit + pTradingAccount->PositionProfit - pTradingAccount->Commission;
		//cerr << "--->>> ��̬Ȩ��: " << current  << endl;

		//YestayAllAmount = preBalance; //��̬Ȩ��
		//TodayAllAmount = current; //��̬Ȩ��
		//UserAmount = pTradingAccount->Available;  //�����ʽ�
												  /*
												  //��齻����־�ļ��Ƿ���ڣ��Ƿ���Ҫ�½��ı��ļ�
												  if (LogFilePaths[0] == '\0')
												  {
												  strcpy(LogFilePaths, "./AutoTrade/");
												  strcat_s(LogFilePaths, pTradingAccount->TradingDay);
												  strcat_s(LogFilePaths, ".txt");

												  //����ļ��Ƿ���ڣ��Ƿ���Ҫ�½��ı��ļ�
												  ifstream inf;
												  ofstream ouf;
												  inf.open(LogFilePaths, ios::out);
												  }
												  */
												  ///�����ѯͶ���ֲ߳�
												  //for (int i = 0; i < 20; i++)
												  //{
												  //strcpy(INSTRUMENT_ID, InstrumentID_n[3]);
												  //ReqQryInvestorPosition();
												  //}
	}
}



void QLCTPTraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInstrumentCommissionRate == NULL)
	{
		return;
	}

	 cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{

		/*
		///��Լ��������
		struct CThostFtdcInstrumentCommissionRateField
		{
			///��Լ����
			TThostFtdcInstrumentIDType	InstrumentID;
			///Ͷ���߷�Χ
			TThostFtdcInvestorRangeType	InvestorRange;
			///���͹�˾����
			TThostFtdcBrokerIDType	BrokerID;
			///Ͷ���ߴ���
			TThostFtdcInvestorIDType	InvestorID;
			///������������
			TThostFtdcRatioType	OpenRatioByMoney;
			///����������
			TThostFtdcRatioType	OpenRatioByVolume;
			///ƽ����������
			TThostFtdcRatioType	CloseRatioByMoney;
			///ƽ��������
			TThostFtdcRatioType	CloseRatioByVolume;
			///ƽ����������
			TThostFtdcRatioType	CloseTodayRatioByMoney;
			///ƽ��������
			TThostFtdcRatioType	CloseTodayRatioByVolume;
		};
          */
		pInstrumentCommissionRate->BrokerID;
		pInstrumentCommissionRate->CloseRatioByMoney;
		pInstrumentCommissionRate->CloseRatioByVolume;
		pInstrumentCommissionRate->CloseTodayRatioByMoney;
		pInstrumentCommissionRate->CloseTodayRatioByVolume;
		pInstrumentCommissionRate->InstrumentID;
		pInstrumentCommissionRate->InvestorID;
		pInstrumentCommissionRate->InvestorRange;
		pInstrumentCommissionRate->OpenRatioByMoney;



	}




}


///��ѯ��󱨵�������Ӧ
void QLCTPTraderSpi::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pQueryMaxOrderVolume == NULL)
	{
		//cout << "--->>>ָ�����OnRspQryTradingAccount" << endl;			  //ָ����
		//WirteTradeRecordToFileMainThread(0, "OnRspQryTradingAccountָ�����");
		return;
	}

	//WirteTradeRecordToFileMainThread(0, "OnRspQryTradingAccount");

	 cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{

		CThostFtdcQueryMaxOrderVolumeField tn;
		memset(&tn, 0, sizeof(CThostFtdcQueryMaxOrderVolumeField));
		memcpy_s(&tn, sizeof(tn), pQueryMaxOrderVolume, sizeof(CThostFtdcQueryMaxOrderVolumeField));
		//strncpy_s(tn.content.BrokerID, sizeof(tn.content.BrokerID), pOrder->BrokerID, sizeof(pOrder->BrokerID));
		//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
		//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
		//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));

		//strncpy_s(tn.content.UserID, sizeof(tn.content.UserID), pOrder->UserID, sizeof(pOrder->UserID));
		//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
		//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
		//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
		//tn.cmd = TD_ORDER_INFO;
		EnterCriticalSection(&g_csdata);
		querymaxordervolumelist.push_back(tn);
		LeaveCriticalSection(&g_csdata);
		//LeaveCriticalSection(&g_csdata);
		SetEvent(hEvent[EID_OnRspQueryMaxOrderVolume]);

	}


}




void QLCTPTraderSpi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

	if (pAccountregister == NULL)
	{
		return;
	}




	/*
	///��������
	TThostFtdcTradeDateType	TradeDay;
	///���б���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///�ڻ���˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�ڻ���˾��֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���������
	TThostFtdcOpenOrDestroyType	OpenOrDestroy;
	///ǩԼ����
	TThostFtdcTradeDateType	RegDate;
	///��Լ����
	TThostFtdcTradeDateType	OutDate;
	///����ID
	TThostFtdcTIDType	TID;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///���ͻ�����
	TThostFtdcLongIndividualNameType	LongCustomerName;
	*/


	printf("�������ڣ�%s\n", pAccountregister->TradeDay);
	printf("���б��룺%s\n", pAccountregister->BankID);
	printf("���з�֧�������룺%s\n", pAccountregister->BankBranchID);
	printf("�����ʺţ�%s\n", pAccountregister->BankAccount);
	printf("�ڻ���˾���룺%s\n", pAccountregister->BrokerID);
	printf("�ڻ���˾��֧�������룺%s\n", pAccountregister->BrokerBranchID);
	printf("Ͷ�����ʺţ�%s\n", pAccountregister->AccountID);
	printf("֤�����ͣ�%c\n", pAccountregister->IdCardType);
	printf("֤�����룺%s\n", pAccountregister->IdentifiedCardNo);

	printf("�ͻ�������%s\n", pAccountregister->CustomerName);
	printf("���ִ��룺%s\n", pAccountregister->CurrencyID);
	printf("���������%c\n", pAccountregister->OpenOrDestroy);



	CThostFtdcAccountregisterField tn;
	memset(&tn, 0, sizeof(CThostFtdcAccountregisterField));
	memcpy_s(&tn, sizeof(tn), pAccountregister, sizeof(CThostFtdcAccountregisterField));
	//strncpy_s(tn.content.BrokerID, sizeof(tn.content.BrokerID), pOrder->BrokerID, sizeof(pOrder->BrokerID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));

	//strncpy_s(tn.content.UserID, sizeof(tn.content.UserID), pOrder->UserID, sizeof(pOrder->UserID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
	//tn.cmd = TD_ORDER_INFO;
	EnterCriticalSection(&g_csdata);
	qryaccountregisterlist.push_back(tn);
	LeaveCriticalSection(&g_csdata);
	//LeaveCriticalSection(&g_csdata);
	SetEvent(hEvent[EID_OnRspQryAccountregister]);
}






///�ڻ����������ʽ�ת�ڻ�֪ͨ
void QLCTPTraderSpi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
	if (pRspTransfer == NULL)
	{
		return;
	}

	CThostFtdcRspTransferField tn;
	memset(&tn, 0, sizeof(CThostFtdcRspTransferField));
	memcpy_s(&tn, sizeof(tn), pRspTransfer, sizeof(CThostFtdcRspTransferField));
	//strncpy_s(tn.content.BrokerID, sizeof(tn.content.BrokerID), pOrder->BrokerID, sizeof(pOrder->BrokerID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));

	//strncpy_s(tn.content.UserID, sizeof(tn.content.UserID), pOrder->UserID, sizeof(pOrder->UserID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
	//tn.cmd = TD_ORDER_INFO;
	EnterCriticalSection(&g_csdata);
	banktofuturebyfuturelist.push_back(tn);
	LeaveCriticalSection(&g_csdata);
	//LeaveCriticalSection(&g_csdata);
	SetEvent(hEvent[EID_OnRtnFromBankToFutureByFuture]);

 
}


///�ڻ������ڻ��ʽ�ת����֪ͨ
void QLCTPTraderSpi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
	if (pRspTransfer == NULL)
	{
		return;
	}

	CThostFtdcRspTransferField tn;
	memset(&tn, 0, sizeof(CThostFtdcRspTransferField));
	memcpy_s(&tn, sizeof(tn), pRspTransfer, sizeof(CThostFtdcRspTransferField));
	//strncpy_s(tn.content.BrokerID, sizeof(tn.content.BrokerID), pOrder->BrokerID, sizeof(pOrder->BrokerID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));

	//strncpy_s(tn.content.UserID, sizeof(tn.content.UserID), pOrder->UserID, sizeof(pOrder->UserID));
	//strncpy_s(tn.content.InvestorID, sizeof(tn.content.InvestorID), pOrder->InvestorID, sizeof(pOrder->InvestorID));
	//strncpy_s(tn.content.InstrumentID, sizeof(tn.content.InstrumentID), pOrder->InstrumentID, sizeof(pOrder->InstrumentID));
	//strncpy_s(tn.content.OrderRef, sizeof(tn.content.OrderRef), pOrder->OrderRef, sizeof(pOrder->OrderRef));
	//tn.cmd = TD_ORDER_INFO;
	EnterCriticalSection(&g_csdata);
	futuretobankbyfuturelist.push_back(tn);
	LeaveCriticalSection(&g_csdata);
	//LeaveCriticalSection(&g_csdata);
	SetEvent(hEvent[EID_OnRtnFromFutureToBankByFuture]);


}

