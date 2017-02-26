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

#include "stdafx.h"
#include "QLCTPInterface.h"
#include "CTPTraderSpi.h"
using namespace std;

extern CRITICAL_SECTION g_csdata;
list <cmdcontent> cmdlist;
//list <cmdcontent>::iterator cmd_Iter;

list <CThostFtdcOrderField> orderlist;
//list <CThostFtdcOrderField>::iterator order_Iter;

list <CThostFtdcTradeField> tradelist;
//list <CThostFtdcTradeField>::iterator trade_Iter;

list <CThostFtdcAccountregisterField> qryaccountregisterlist;
//list <CThostFtdcAccountregisterField>::iterator qryaccountregister_Iter;


list <CThostFtdcRspTransferField> banktofuturebyfuturelist;
//list <CThostFtdcRspTransferField>::iterator banktofuturebyfuture_Iter;

list <CThostFtdcRspTransferField> futuretobankbyfuturelist;
//list <CThostFtdcRspTransferField>::iterator futuretobankbyfuture_Iter;


list <CThostFtdcQueryMaxOrderVolumeField>  querymaxordervolumelist;
//list <CThostFtdcQueryMaxOrderVolumeField>::iterator querymaxordervolume_Iter;


list <CThostFtdcInstrumentStatusField> InstrumentStatuslist;
//list <CThostFtdcInstrumentStatusField>::iterator InstrumentStatus_Iter;


list <CThostFtdcRspInfoField> errorlist;
//list <CThostFtdcRspInfoField>::iterator error_Iter;

list <CThostFtdcSettlementInfoConfirmField> settlementlist;
//list <CThostFtdcSettlementInfoConfirmField>::iterator settlement_Iter;

//�����ֶ�Ҫ�Լ����壬������¼״̬�Ķ���
list <CThostFtdcRspUserLoginField> loginlist;
//list <CThostFtdcRspUserLoginField>::iterator login_Iter;

list <CThostFtdcUserLogoutField> loginoutlist;
//list <CThostFtdcUserLogoutField>::iterator loginout_Iter;

list <int> connectlist;
//list <int>::iterator connect_Iter;

///�����ѯ��Լ��֤������Ӧ
list <CThostFtdcInstrumentMarginRateField> MarginRatelist;
//list <CThostFtdcInstrumentMarginRateField>::iterator MarginRate_Iter;

///�����ѯ��Լ����������Ӧ
list <CThostFtdcInstrumentCommissionRateField> CommissionRatelist;
//list <CThostFtdcInstrumentCommissionRateField>::iterator CommissionRate_Iter;

 

 

#include <process.h>
HANDLE hEvent[MAX_EVENTNUM] = { NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL };

std::string gTDFrontAddr[3];
std::string gBrokerID;
std::string gUserID;
std::string gPassword;

std::string gSN;

HANDLE ghTradedVolMutex = NULL;
std::map<int, int> gOrderRef2TradedVol;

std::string gConfigFile("QuickLibTD.ini");

QLCTPTraderSpi gTraderSpi;

bool showpositionstate=false;


//AES����
#include "Aes.h"  
#include <string>  
#include <algorithm>  
using namespace std;

//Aes�ַ�������
string OnBAesEn(char *wText, char *key, int w)
{
	//unsigned 
	char inBuff[50], ouBuff[50];
	//int strlength=50;
	//char inBuff[50],ouBuff[50];
	memset(inBuff, 0, 50);
	memset(ouBuff, 0, 50);
	//wchar_t wText[16] = {L"abc"};

	//wchar_t wText[10] = {L"����ʾ��"};
	// char sText[20]= {0};
	//WCharToMByte(wText,sText,sizeof(sText)/sizeof(sText[0]));
	//MByteToWChar(sText,wText,sizeof(wText)/sizeof(wText[0]));
	//WCharToMByte(wText,inBuff,sizeof(inBuff)/sizeof(inBuff[0]));
	//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
	//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

	//Aes aes((unsigned char*)_T("ddd0000000000000"),16);

	Aes aes((unsigned char*)key, 24);



	//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
	//if(strlen((char*)inBuff)>16)MessageBox("����ֻ�ܼ���16�ֽڵ��ַ��������ڽض�");

	aes.EncryptBlock(ouBuff, wText); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
									 //ʵ�������32����ĸ������,����ASCII��ֵ����127�Ļ������롣
	string str = "", strTmp;

	for (int i = 0; i<16; i++)
	{
		//strTmp.Format(_T("%02x"),ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���
		//strTmp.Format("%02x", ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���

		char temp[100] = { 0 };
		_snprintf_s(temp, sizeof(temp), sizeof(temp), "%02x", ouBuff[i]);
		strTmp = string(temp);


		if (ouBuff[i]<0xff)
		{
			//strTmp = strTmp.Right(2);

			strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());
		}
		str += strTmp;
		//MessageBox(strTmp,_T("���ܺ�"));
	}
	//strout=str;
	//AfxMessageBox(str);
	//BSTR bstrText = str.AllocSysString();
	//return bstrText;
	return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////


//�ַ�ASCII��ֵ���ַ�����ֵ��ת�� �� '0'ת����0�� 'a'ת����10
int char2num(TCHAR ch)
{
	if (ch >= '0' && ch <= '9')return ch - '0';
	else if (ch >= 'a' && ch <= 'f')return ch - 'a' + 10;
	return -1;
}
//Aes�ַ�������
string OnBAesDe(char *wText, char *key, int w)
{
	// TODO: Add your control notification handler code here
	//unsigned char inBuff[33],ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
	//��Ϊ�и���������

	unsigned char ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
							   //��Ϊ�и���������
	memset(ouBuff, 0, 25);
	//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
	//Aes aes((unsigned char*)_T("ddd0000000000000"),16);
	Aes aes((unsigned char*)key, 24);
	//CString theString(wText);
	string theString = (wText);
	char * inBuff = new char[theString.size() + 1];
	//_tcscpy_s(inBuff, theString.size() + 1, theString);

	strncpy_s(inBuff, sizeof(inBuff), theString.c_str(), theString.size() + 1);
	unsigned char temp[25];
	for (int j = 0; j<16; j++)
	{
		temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// ���ַ������ʾ��16����ASCII��ֵת����������ASCII��ֵ
	}
	aes.DecryptBlock(ouBuff, temp);
	//AfxMessageBox(CString(ouBuff));  
	//BSTR bstrText = CString(ouBuff).AllocSysString();
	//return bstrText;

	return  (char*)(&ouBuff);
}






BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (dwSize < dwMinSize)
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE);
	return TRUE;
}



BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	// Get the required size of the buffer that receives the Unicode 
	// string. 
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);

	if (dwSize < dwMinSize)
	{
		return FALSE;
	}


	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
	return TRUE;
}


/*
//Aes�ַ�������
string  OnBAesEn(char *wText)
{
// TODO: Add your control notification handler code here
//unsigned
char inBuff[50], ouBuff[50];
//int strlength=50;
//char inBuff[50],ouBuff[50];
memset(inBuff, 0, 50);
memset(ouBuff, 0, 50);
//wchar_t wText[16] = {L"abc"};

//wchar_t wText[10] = {L"����ʾ��"};
// char sText[20]= {0};
//WCharToMByte(wText,sText,sizeof(sText)/sizeof(sText[0]));
//MByteToWChar(sText,wText,sizeof(wText)/sizeof(wText[0]));
//WCharToMByte(wText,inBuff,sizeof(inBuff)/sizeof(inBuff[0]));
//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

Aes aes((unsigned char*)"\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10", 16);

//Aes aes((unsigned char*)key,24);



//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
//if(strlen((char*)inBuff)>16)MessageBox("����ֻ�ܼ���16�ֽڵ��ַ��������ڽض�");

//aes.EncryptBlock(ouBuff, inBuff); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
aes.EncryptBlock(ouBuff, wText); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
//ʵ�������32����ĸ������,����ASCII��ֵ����127�Ļ������롣
string str = "", strTmp;

for (int i = 0;i<16;i++)
{
//strTmp.Format(_T("%02x"),ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���
char temp[100] = {0};
sprintf_s(temp, sizeof(temp), "%02x", ouBuff[i]);
//strTmp.Format("%02x", ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���

strTmp = temp;
if (ouBuff[i]<0xff)
{
//strTmp = strTmp.Right(2);

strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());
}
str += strTmp;
//MessageBox(strTmp,_T("���ܺ�"));
}
//strout=str;
//AfxMessageBox(str);
//BSTR bstrText = str.AllocSysString();
//return bstrText;
return str;

}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes�ַ�������
string OnBAesDe(char *wText)
{
// TODO: Add your control notification handler code here
//unsigned char inBuff[33],ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
//��Ϊ�и���������

unsigned char ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
//��Ϊ�и���������
memset(ouBuff, 0, 25);
//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
// Aes aes((unsigned char*)_T("ddd0000000000000"),16);
Aes aes((unsigned char*)"\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10", 16);

//Aes aes((unsigned char*)key,24);
string theString=(wText);
LPTSTR inBuff = new TCHAR[theString.size() + 1];
strncpy_s(inBuff, sizeof(inBuff), theString.c_str(), theString.size() + 1);
unsigned char temp[25];
for (int j = 0;j<16;j++)
{
temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// ���ַ������ʾ��16����ASCII��ֵת����������ASCII��ֵ
}
aes.DecryptBlock(ouBuff, temp);
//AfxMessageBox(CString(ouBuff));
//BSTR bstrText = .AllocSysString();
//return bstrText;

return  (char*)(&ouBuff);
}



//Aes�ַ�������
string OnBAesEn2(char *wText)
{
// TODO: Add your control notification handler code here
//unsigned
char inBuff[50], ouBuff[50];
//int strlength=50;
//char inBuff[50],ouBuff[50];
memset(inBuff, 0, 50);
memset(ouBuff, 0, 50);
//wchar_t wText[16] = {L"abc"};


//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

//Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*)"\x9\xf\xa\x3\xa\x5\x15\xc\x1\xe\x13\x11\x17\x3\x11\x2", 16);

//Aes aes((unsigned char*)key,24);



//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
//if(strlen((char*)inBuff)>16)MessageBox("����ֻ�ܼ���16�ֽڵ��ַ��������ڽض�");
//aes.EncryptBlock(ouBuff, inBuff); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
aes.EncryptBlock(ouBuff, wText); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
//ʵ�������32����ĸ������,����ASCII��ֵ����127�Ļ������롣
string str = "", strTmp;

for (int i = 0;i<16;i++)
{
//strTmp.Format(_T("%02x"),ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���
char temp[100] = { 0 };
sprintf_s(temp, sizeof(temp), "%02x", ouBuff[i]);


//strTmp.Format("%02x", ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���

strTmp = temp;

if (ouBuff[i]<0xff)
{
//strTmp = strTmp.Right(2);
strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());
}
str += strTmp;
//MessageBox(strTmp,_T("���ܺ�"));
}
//strout=str;
//AfxMessageBox(str);
//BSTR bstrText = str.AllocSysString();
//return bstrText;
return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes�ַ�������
string OnBAesDe2(char *wText)
{
// TODO: Add your control notification handler code here
//unsigned char inBuff[33],ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
//��Ϊ�и���������

unsigned char ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
//��Ϊ�и���������
memset(ouBuff, 0, 25);
//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
// Aes aes((unsigned char*)_T("ddd0000000000000"),16);
//	  Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*) "\x9\xf\xa\x3\xa\x5\x15\xc\x1\xe\x13\x11\x17\x3\x11\x2", 16);
//Aes aes((unsigned char*)key,24);
string theString=(wText);
LPTSTR inBuff = new TCHAR[theString.size() + 1];
strncpy_s(inBuff, sizeof(inBuff), theString.c_str(),  theString.size() + 1);
unsigned char temp[25];
for (int j = 0;j<16;j++)
{
temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// ���ַ������ʾ��16����ASCII��ֵת����������ASCII��ֵ
}
aes.DecryptBlock(ouBuff, temp);
//AfxMessageBox(CString(ouBuff));
//BSTR bstrText = .AllocSysString();
//return bstrText;

return (char*)(&ouBuff);
}
*/
//Aes�ַ�������
/*
string OnBAesEn3(const char *wText)
{
// TODO: Add your control notification handler code here
//unsigned
char inBuff[25], ouBuff[25];
//int strlength=50;
//char inBuff[50],ouBuff[50];
memset(inBuff, 0, 25);
memset(ouBuff, 0, 25);
//wchar_t wText[16] = {L"abc"};

//wchar_t wText[10] = {L"����ʾ��"};
// char sText[20]= {0};
//WCharToMByte(wText,sText,sizeof(sText)/sizeof(sText[0]));
//MByteToWChar(sText,wText,sizeof(wText)/sizeof(wText[0]));
//WCharToMByte(wText,inBuff,sizeof(inBuff)/sizeof(inBuff[0]));
//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

//Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);

//Aes aes((unsigned char*)key,24);

strncpy_s(inBuff,sizeof(inBuff), wText,strlen(wText));


printf("inBuff %X\n", inBuff);
//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
//if(strlen((char*)inBuff)>16)MessageBox("����ֻ�ܼ���16�ֽڵ��ַ��������ڽض�");
//aes.EncryptBlock(ouBuff, inBuff); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
aes.EncryptBlock(ouBuff, inBuff); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
//ʵ�������32����ĸ������,����ASCII��ֵ����127�Ļ������롣
string str = "", strTmp;
printf("ouBuff %X\n", ouBuff);
for (int i = 0;i<16;i++)
{
//strTmp.Format(_T("%02x"),ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���
//strTmp.Format("%02x", ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���

char temp[200] = {0};
sprintf_s(temp,sizeof(temp), "%02X", ouBuff[i]);



strTmp = string(temp);
if (ouBuff[i]<0xff)
{
//strTmp = strTmp.Right(2);
//strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());

strTmp = strTmp.substr(0,16);
}
str += strTmp;
//MessageBox(strTmp,_T("���ܺ�"));
}

printf("���%s\n", str);
//strout=str;
//AfxMessageBox(str);
//BSTR bstrText = str.AllocSysString();
//return bstrText;
return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes�ַ�������
string OnBAesDe3(char *wText)
{

printf("ִ��");
// TODO: Add your control notification handler code here
//unsigned char inBuff[33],ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
//��Ϊ�и���������

unsigned char ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
//��Ϊ�и���������
memset(ouBuff, 0, 25);
//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
// Aes aes((unsigned char*)_T("ddd0000000000000"),16);
//	  Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);
//Aes aes((unsigned char*)key,24);
string  theString=(wText);
LPTSTR inBuff = new TCHAR[theString.size() + 1];
strncpy_s(inBuff, sizeof(inBuff), theString.c_str(),  theString.size() + 1);
unsigned char temp[25];
for (int j = 0;j<16;j++)
{
temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// ���ַ������ʾ��16����ASCII��ֵת����������ASCII��ֵ
}
aes.DecryptBlock(ouBuff, temp);
//AfxMessageBox(CString(ouBuff));
//BSTR bstrText = .AllocSysString();
//return bstrText;

printf("%x\n", (char*)(&ouBuff));

return  (char*)(&ouBuff);
}
*/
//NEW
//Aes�ַ�������
string  OnBAesEn(const char * strinput)
{
	// TODO: Add your control notification handler code here
	unsigned char inBuff[25], ouBuff[25];
	memset(inBuff, 0, 25);
	memset(ouBuff, 0, 25);
	//printf("c1\n");
	//Sleep(5000);
	//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17", 24);
	Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);
	//GetDlgItemText(IDC_EAesEn, (char*)inBuff, 24);

	strncpy_s((char*)inBuff, sizeof(inBuff), strinput, strlen(strinput));

	//printf("c2\n");
	//Sleep(5000);
	//if (strlen((char*)inBuff)>16)MessageBox("����ֻ�ܼ���16�ֽڵ��ַ��������ڽض�");

	aes.EncryptBlock(ouBuff, inBuff); //��Ϊ���Ϊ16���ֽڣ�ÿ���ֽ���������ĸ�����ֱ�ʾ��
	string str = "", strTmp;		//ʵ�������32����ĸ������,����ASCII��ֵ����127�Ļ������롣
	for (int i = 0; i<16; i++)
	{
		char temp[100] = { 0 };
		_snprintf_s(temp, sizeof(temp), sizeof(temp), "%02x", ouBuff[i]);
		//strTmp.Format("%02x", ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���
		strTmp = temp;


		str += strTmp;
	}

	//printf("c3\n");
	//Sleep(5000);
	//MessageBox(str,"���ܺ�");
	//SetDlgItemText(IDC_EAesEn, str);
	//printf("����1�Σ�%s\n", str.c_str());
	return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes�ַ�������
string OnBAesDe(const char * strinput)
{
	//printf("���룺 %s\n", strinput);
	// TODO: Add your control notification handler code here
	unsigned char inBuff[33], ouBuff[25];  //����Ҫע��32���ַ����ַ�����Ҫ��33���ֽ����洢��
										   //��Ϊ�и���������
	memset(inBuff, 0, 25);
	memset(ouBuff, 0, 25);
	//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17", 24);
	Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);
	//GetDlgItemText(IDC_EAesEn, (char*)inBuff, 33);
	strncpy_s((char*)inBuff, sizeof(inBuff), strinput, strlen(strinput));


	unsigned char temp[25] = { 0 };
	for (int j = 0; j<16; j++)
	{
		temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// ���ַ������ʾ��16����ASCII��ֵת����������ASCII��ֵ
	}

	aes.DecryptBlock(ouBuff, temp);//"dda97ca4......ec0d7191"

								   //printf("���ܣ�%s\n", ouBuff);

								   //SetDlgItemText(IDC_EAesDe, CString(ouBuff));
								   //Sleep(5000);
								   //return (char*)&ouBuff;
								   //string str = (char*)&ouBuff;
	return (char*)&ouBuff;
}

string MoreStrOnBAesEn(string leftstr)
{
	int StrLen = leftstr.size();
	string cutstr, Erystr;
	//printf("����%d\n", StrLen);
	int blocknum = StrLen / 16;     //������Ӣ���ַ�������������ַ�����ȡ����16�������ַ�����ÿ��ֻ����8���ַ���������8��
	int leftnum = StrLen % 16;
	printf("len[%d] blocknum[%d]\n", StrLen, blocknum);

	for (int i = 1; i <= blocknum; i++)
	{
		//printf("[%d] \n", i );
		//printf("[%d] [%d]\n", 16 * (i - 1), 16 * i);
		//printf("%s  [%d][%d]\n", leftstr.c_str(),16 * (i - 1), 16 * i);
		cutstr = leftstr.substr(16 * (i - 1), 16);
		//printf("[%d]en_p: %s\n",i, cutstr.c_str());

		Erystr = Erystr + OnBAesEn(((char*)cutstr.c_str()));

	}
	//printf("ʣ��[%d][%d]\n", 16 * (blocknum ), StrLen - 16 * (blocknum));
	cutstr = leftstr.substr(16 * (blocknum), StrLen - 16 * (blocknum));
	//printf("en_p: %s\n", cutstr.c_str());
	Erystr = Erystr + OnBAesEn((char*)(cutstr.c_str()));
	//stringת��д
	//transform(Erystr.begin(), Erystr.end(), Erystr.begin(), ::toupper);
	return Erystr;
}
bool CheckSN3()
{
	//gUserID.c_str(), gSN.c_str())
	//CString account;
	//CString content;
	//account.Format(_T("%s"), accountchar);
	//content.Format(_T("%s"), contentchar);

	//	string RSEID =;

	//RSA����
	// CString RK=RSEID;    //��Ȩ���к�
	// vl(RK.GetLength(),RK);
	// int RSTATE=0;//,RSTATE2=0;




	// AfxMessageBox(m_OUT);
	//2048λ���� 512��16�����ַ�  2048/4=512
	// theApp.SN=m_OUT;
	//RSA
	//RSA����



	// CString leftstr=_T("ABCDEF3333333345453543643tytyytg68787egUIASDGLSDKSDLKKDKKooweodoubleKASDFthakyoucitySHANHGAI7acdf323421CCAE");
	//   CString username=GetProfileString(VMProtectDecryptStringW(_T("Settings")),VMProtectDecryptStringW(_T("username")));
	//	  int usernameStrLen=username.GetLength();
	//  if(usernameStrLen>3){username=username.Left(3);}

	//AfxMessageBox(GetCPUInfo()+L"/c");
	//AfxMessageBox(GetDisplay()+L"/m");
	//AfxMessageBox(HardDiskId()+L"/m");
	//CString leftstr=GetCPUInfo()+GetMacAddress();//+username;
	//CString account = _T("68122653") ;// GetCPUInfo() + GetDisplay() + HardDiskId();//+username;






	//AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//AfxMessageBox(MoreStrOnBAesDe(MoreStrOnBAesEn(leftstr)));

	//wchar_t * dataA=VMProtectDecryptStringW(_T("20120711"));   //��Ч����ʼ����(Ӧ��Ϊ�������������)
	//AfxMessageBox(L"AAA");
	// AfxMessageBox(RK2);
	// AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//	 AfxMessageBox(L"BBB");

	//CString temp;
	//temp.Format(_T("%s"), RSEID.c_str());


	// MessageBox(NULL, RSEID.GetBuffer(RSEID.GetLength()), TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
	//AfxMessageBox(RSEID);
	string str = MoreStrOnBAesEn(gUserID);
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	//MessageBox(NULL, str.c_str(), TEXT("���"), MB_ICONINFORMATION | MB_YESNO);

	while (str == gSN)
		//while(RSEID==MoreStrOnBAesEn(leftstr))
	{
		//RSTATE=1;
		//AfxMessageBox(_T("�����Ȩb1"));
		//MessageBox(NULL, "�����Ȩb1", TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
		return 1;
	}
	//while(RK2!=GetCPUInfo() && RSTATE2!=1)
	//{
	//   RSTATE2=1;
	//	AfxMessageBox(_T("����b1"));
	//	return 0;
	//}
	////////////////////////////////////////���SN
	//   }     
	//MessageBox(NULL, "����Ȩb1", TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
	//  srand((unsigned)time(NULL));
	return 0;
	//��Ȩ״̬�ж�  ������BIOS
	//RSA����
}
//����16�ַ����ַ�������


//����16�ַ����ַ�������

string MoreStrOnBAesDe(string leftstr)
{
	////����
	//transform(strA.begin(), strA.end(), strA.begin(), ::toupper);
	leftstr = leftstr.c_str();//.MakeLower();

							  //printf("%s\n", leftstr.c_str());
	int StrLen = leftstr.size();
	string cutstr, Erystr;

	//printf("A1\n" );
	//Sleep(7000);

	int blocknum = StrLen / 32;     //������Ӣ���ַ�������������ַ�����ȡ����16�������ַ�����ÿ��ֻ����8���ַ���������8��
	int leftnum = StrLen % 32;
	//printf("A2\n");
	//Sleep(7000);
	for (int i = 1; i <= blocknum; i++)
	{
		//printf("A3\n");
		//Sleep(7000);
		cutstr = leftstr.substr(32 * (i - 1), 32);
		//printf("de_p: %s\n", cutstr.c_str());
		Erystr = Erystr + OnBAesDe((char*)(cutstr.c_str()));

		//printf("A4\n");
		//Sleep(7000);
	}
	//printf("A5\n");
	//Sleep(7000);
	//printf("DEʣ��[%d][%d]\n", 16 * (blocknum), StrLen - 16 * (blocknum));
	//cutstr = leftstr.substr(32 * (blocknum), StrLen - 32 * (blocknum));
	//printf("de_p: %s\n",   cutstr.c_str());
	//printf("A6\n");
	//Sleep(7000);

	//	printf("β�� �� %s\n", OnBAesDe((char*)(cutstr.c_str())).c_str());

	//Erystr=Erystr+OnBAesDe((char*)(cutstr.c_str()));
	// printf("���� : %s\n", Erystr.c_str());

	return Erystr;
	///����
}


//������SN
bool CheckSN()
{
	//gUserID.c_str(), gSN.c_str())
	//CString account;
	//CString content;
	//account.Format(_T("%s"), accountchar);
	//content.Format(_T("%s"), contentchar);
 
//	string RSEID =;

	//RSA����
	// CString RK=RSEID;    //��Ȩ���к�
	// vl(RK.GetLength(),RK);
	// int RSTATE=0;//,RSTATE2=0;




	// AfxMessageBox(m_OUT);
	//2048λ���� 512��16�����ַ�  2048/4=512
	// theApp.SN=m_OUT;
	//RSA
	//RSA����

 

	// CString leftstr=_T("ABCDEF3333333345453543643tytyytg68787egUIASDGLSDKSDLKKDKKooweodoubleKASDFthakyoucitySHANHGAI7acdf323421CCAE");
	//   CString username=GetProfileString(VMProtectDecryptStringW(_T("Settings")),VMProtectDecryptStringW(_T("username")));
	//	  int usernameStrLen=username.GetLength();
	//  if(usernameStrLen>3){username=username.Left(3);}

	//AfxMessageBox(GetCPUInfo()+L"/c");
	//AfxMessageBox(GetDisplay()+L"/m");
	//AfxMessageBox(HardDiskId()+L"/m");
	//CString leftstr=GetCPUInfo()+GetMacAddress();//+username;
	//CString account = _T("68122653") ;// GetCPUInfo() + GetDisplay() + HardDiskId();//+username;






																 //AfxMessageBox(MoreStrOnBAesEn(leftstr));

																 //AfxMessageBox(MoreStrOnBAesDe(MoreStrOnBAesEn(leftstr)));

																 //wchar_t * dataA=VMProtectDecryptStringW(_T("20120711"));   //��Ч����ʼ����(Ӧ��Ϊ�������������)
																 //AfxMessageBox(L"AAA");
																 // AfxMessageBox(RK2);
																 // AfxMessageBox(MoreStrOnBAesEn(leftstr));

																 //	 AfxMessageBox(L"BBB");

	//CString temp;
	//temp.Format(_T("%s"), RSEID.c_str());
	 

	// MessageBox(NULL, RSEID.GetBuffer(RSEID.GetLength()), TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
	//AfxMessageBox(RSEID);
	string str = MoreStrOnBAesEn(gUserID);
	transform(str.begin(),str.end(),str.begin(),::toupper);
	//MessageBox(NULL, str.c_str(), TEXT("���"), MB_ICONINFORMATION | MB_YESNO);

	while (str == gSN)
		//while(RSEID==MoreStrOnBAesEn(leftstr))
	{
		//RSTATE=1;
		 //AfxMessageBox(_T("�����Ȩb1"));
		// MessageBox(NULL, "�����Ȩb1", TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
		return 1;
	}
	//while(RK2!=GetCPUInfo() && RSTATE2!=1)
	//{
	//   RSTATE2=1;
	//	AfxMessageBox(_T("����b1"));
	//	return 0;
	//}
	////////////////////////////////////////���SN
	//   }     
	// MessageBox(NULL, "����Ȩb1", TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
	//  srand((unsigned)time(NULL));
	return 0;
	//��Ȩ״̬�ж�  ������BIOS
	//RSA����
}
//������SN

//������SN
bool CheckSN2()
{
	//gUserID.c_str(), gSN.c_str())
	//CString account;
	//CString content;
	//account.Format(_T("%s"), accountchar);
	//content.Format(_T("%s"), contentchar);

	//	string RSEID =;

	//RSA����
	// CString RK=RSEID;    //��Ȩ���к�
	// vl(RK.GetLength(),RK);
	// int RSTATE=0;//,RSTATE2=0;




	// AfxMessageBox(m_OUT);
	//2048λ���� 512��16�����ַ�  2048/4=512
	// theApp.SN=m_OUT;
	//RSA
	//RSA����



	// CString leftstr=_T("ABCDEF3333333345453543643tytyytg68787egUIASDGLSDKSDLKKDKKooweodoubleKASDFthakyoucitySHANHGAI7acdf323421CCAE");
	//   CString username=GetProfileString(VMProtectDecryptStringW(_T("Settings")),VMProtectDecryptStringW(_T("username")));
	//	  int usernameStrLen=username.GetLength();
	//  if(usernameStrLen>3){username=username.Left(3);}

	//AfxMessageBox(GetCPUInfo()+L"/c");
	//AfxMessageBox(GetDisplay()+L"/m");
	//AfxMessageBox(HardDiskId()+L"/m");
	//CString leftstr=GetCPUInfo()+GetMacAddress();//+username;
	//CString account = _T("68122653") ;// GetCPUInfo() + GetDisplay() + HardDiskId();//+username;






	//AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//AfxMessageBox(MoreStrOnBAesDe(MoreStrOnBAesEn(leftstr)));

	//wchar_t * dataA=VMProtectDecryptStringW(_T("20120711"));   //��Ч����ʼ����(Ӧ��Ϊ�������������)
	//AfxMessageBox(L"AAA");
	// AfxMessageBox(RK2);
	// AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//	 AfxMessageBox(L"BBB");

	//CString temp;
	//temp.Format(_T("%s"), RSEID.c_str());


	// MessageBox(NULL, RSEID.GetBuffer(RSEID.GetLength()), TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
	//AfxMessageBox(RSEID);
	string str = MoreStrOnBAesEn(gUserID);
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	//MessageBox(NULL, str.c_str(), TEXT("���"), MB_ICONINFORMATION | MB_YESNO);

	while (str == gSN)
		//while(RSEID==MoreStrOnBAesEn(leftstr))
	{
		//RSTATE=1;
		//AfxMessageBox(_T("�����Ȩb1"));
		//MessageBox(NULL, "�����Ȩb1", TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
		return 1;
	}
	//while(RK2!=GetCPUInfo() && RSTATE2!=1)
	//{
	//   RSTATE2=1;
	//	AfxMessageBox(_T("����b1"));
	//	return 0;
	//}
	////////////////////////////////////////���SN
	//   }     
	//MessageBox(NULL, "����Ȩb1", TEXT("���"), MB_ICONINFORMATION | MB_YESNO);
	//  srand((unsigned)time(NULL));
	return 0;
	//��Ȩ״̬�ж�  ������BIOS
	//RSA����
}
//������SN

void QuickLib_TD_Start()
{	//�ٽ���
	for (int i = 0; i < MAX_EVENTNUM; i++)
	{
		if (!hEvent[i])
		{
			char temp[10] = { 0 };
			_snprintf_s(temp, sizeof(temp), sizeof(temp), "hEvent%d", i);
			hEvent[i] = CreateEvent(NULL, FALSE, FALSE, temp);//TRUE�ֶ���λ
															  //hEvent = CreateEvent(NULL, FALSE, FALSE, "abc");//TRUE�Զ���λ������ResetEvent
		}

	}

	InitializeCriticalSection(&g_csdata);


	//while(!CheckSN())
	//{
	
		//return;
	//}
	    /*
		//RSA
		//m_OUT =VMProtectDecryptStringW(GetProfileString(_T("Settings"),_T("SN")));
		string SN = "16EF034A7F9785C03EDF4295020B81C3C5FC8E8776E52018F5007634BFEEBAAEA51562DFA2C44F65FBB2F69AB1550D9D98478034C8BDC689840F6ACCEEF4AB060B330FC90A5B9032CE37AEEB1EB5C58CF0575096A4CA23A4A94DE96251791854C0B8AB11DD12D4CCBD93F50678EAB073DC4D49A23D4BF7CFE291732CD2FFF6AF5D53481D8853373647BFC5FD81F58BB6E067D467E343604A4D744651D688B86B50F4F1C223CD7C1E8CD0703BF2E456E28FB16D791AD22D6DFE98A066CA45B68893750193CF1B7C7C094DEE0D67DDFA06F22299C5809DFAB5DDA65FB70265780458CB29F004E3BE9D0BDD66ECDEC256377A99E3DDBAE5C985B6309F4F3CF8E7CE1";//  (GetProfileString(_T("Settings"), _T("SN")));
		string m_OUT = SN;
		//2048λ���� 512��16�����ַ�  2048/4=512
		//RSA

		// WriteProfileString(_T("Settings"),_T("SNp2"),m_OUT);   //SN���浽ע���
		//RSA����
		RSAE rsa("123");
		rsa.OnButtonPut();
		//AfxMessageBox(OnClickDecrypt());
		//RSEID =
		//	rsa.OnClickDecrypt(); //��Ȩ���к�
		printf("RSA De: %s\n", rsa.OnClickDecrypt().c_str());

		printf("RSA En: %s\n", rsa.OnClickDecrypt().c_str());
		//RSA����
		//CString RK=RSEID;    //��Ȩ���к�
		//vl(RSEID.GetLength(), RSEID);   //��Ȩ���кţ������λȱλ��0
		*/



	std::cout << __FUNCTION__ << std::endl;
	ghTradedVolMutex = ::CreateMutex(NULL, FALSE, NULL);
	std::cout << "Init Finished." << std::endl;
}




void QuickLib_TD_End()
{
	std::cout << __FUNCTION__ << std::endl;
	//�ٽ���
	DeleteCriticalSection(&g_csdata);

	if (ghTradedVolMutex)
	{
		::CloseHandle(ghTradedVolMutex);
		ghTradedVolMutex = NULL;
	}
}

int Login()
{
	std::cout << __FUNCTION__ << std::endl;
	std::ifstream ifs(gConfigFile.c_str());
	if (ifs.is_open())
	{
		std::string fl;
		getline(ifs, fl);
		getline(ifs, gTDFrontAddr[0]);
		getline(ifs, gTDFrontAddr[1]);
		getline(ifs, gTDFrontAddr[2]);

		getline(ifs, fl);
		getline(ifs, gBrokerID);

		getline(ifs, fl);
		getline(ifs, gUserID);

		getline(ifs, fl);
		getline(ifs, gPassword);

		getline(ifs, fl);
		getline(ifs, gSN);

		ifs.close();
	}else
	{
		std::cout << "fail to open config file." << std::endl;
		return 1;
	}
	
	//while (!CheckSN2(gUserID.c_str(),gSN.c_str()))
	//{

	//	return -1;
	//}
	while(!CheckSN())
	{

	return 0;
	}
	while (!CheckSN2())
	{

		return -1;
	}
	std::cout << "Login: " << gUserID << std::endl;

	while (CheckSN3())
	{

		bool ret = gTraderSpi.Init();

		if (ret)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	return  0;
}

//���ư�
//int maxordernum2 = 6 + 8;
//int num2 = 0;
//���ư�

//����
extern std::map<std::string, double> gUnderlyingMultiple;
//��֤����
extern std::map<std::string, double> gMarginRate_long;
extern std::map<std::string, double> gMarginRate_short;
//��������
extern std::map<std::string, double> gCommissionRate;

//��ѯ��󱨵�����
extern std::map<std::string, int> gMaxOrderVolume;




extern int	Trade_dataA_Amount_B_Today[TYPE_NUM];		//�൥�ֲ�
extern int	Trade_dataA_Amount_B_History[TYPE_NUM];		//�൥�ֲ�
extern int	Trade_dataA_Amount_S_Today[TYPE_NUM];		//�յ��ֲ�
extern int	Trade_dataA_Amount_S_History[TYPE_NUM];		//�յ��ֲ�

extern double YestayAllAmount;
extern double TodayAllAmount;
extern double UserAmount;




extern std::map<std::string, int> gPosition_S;
extern std::map<std::string, int> gPosition_B;

extern std::map<std::string, int> gPosition_S_Today;
extern std::map<std::string, int> gPosition_B_Today;
extern std::map<std::string, int> gPosition_S_History;
extern std::map<std::string, int> gPosition_B_History;

extern std::map<std::string, int> gTypeCheckState_S_Today;
extern std::map<std::string, int> gTypeCheckState_B_Today;
extern std::map<std::string, int> gTypeCheckState_S_History;
extern std::map<std::string, int> gTypeCheckState_B_History;

#define POSITION_SELL_TODAY     9001
#define POSITION_BUY_TODAY      9002
#define POSITION_SELL_HISTORY   9003
#define POSITION_BUY_HISTORY    9004
#define POSITION_SELL_ALL   9005
#define POSITION_BUY_ALL    9006


#define RATETYPE_LONG     0
#define RATETYPE_SHORT    1

extern QLCTPTraderSpi *mpUserSpi;


int InsertOrderByRate(char *Instrument, char direction, char offsetFlag, char priceType, double price, double rate, bool BalanceType,int multiplier)
{
	//std::cout << __FUNCTION__ << Instrument << "\t" << direction << "\t"
	//<< offsetFlag << "\t" << priceType << "\t" << price << "\t"
	//<< num << std::endl;

	//���ư�

	//num2++;
	//while (num2 > maxordernum2)
	//{
	//	return 0;
	//	break;
	//}

	//���ư�


	int num = 0;// rate*

	if (BalanceType==0)
	{
		if (TodayAllAmount < 1e-10)
		{
			return -2;//δ����ʽ���������
		}
		num =(int)( rate* TodayAllAmount*multiplier); //��̬Ȩ��
	}
	else
	{
		if (YestayAllAmount < 1e-10)
		{
			return -2;//δ����ʽ���������
		}
		num = (int)(rate* YestayAllAmount*multiplier); //��̬Ȩ��

	}


	printf("�����ֱ���[%0.02f%%]�µ�����[%d]\n", rate,num);

	if (gTraderSpi.IsInitOK())
	{
		return gTraderSpi.InsertOrder(Instrument, direction, offsetFlag, priceType, price, num);
	}
	else
	{
		return -1;
	}
}


int InsertOrder(char *Instrument, char direction, char offsetFlag, char priceType, double price, int num)
{
	std::cout << __FUNCTION__ << Instrument << "\t" << direction << "\t"
		<< offsetFlag << "\t" << priceType << "\t" << price << "\t"
		<< num << std::endl;

	//���ư�

	//num2++;
	//while (num2 > maxordernum2)
	//{
	//	return 0;
	//	break;
	//}

	//���ư�

	printf("�µ�����[%d]\n", num);

	if (gTraderSpi.IsInitOK())
	{
		return gTraderSpi.InsertOrder(Instrument, direction, offsetFlag, priceType, price, num);
	}
	else
	{
		return -1;
	}
}
 
int DeleteOrder(char *Instrument, int OrderRef)
{
	std::cout << __FUNCTION__ << "\t" << OrderRef << std::endl;

	if (gTraderSpi.IsInitOK())
	{
		return gTraderSpi.DeleteOrder(Instrument, OrderRef);
	}
	else
	{
		return -1;
	}
}

int QryTradedVol(int OrderRef)
{
	int ret = -1;
	::WaitForSingleObject(ghTradedVolMutex, INFINITE);
	if (gOrderRef2TradedVol.find(OrderRef) != gOrderRef2TradedVol.end())
	{
		ret = gOrderRef2TradedVol[OrderRef];
	}
	::ReleaseMutex(ghTradedVolMutex);
	return ret;
}

//��ѯ����
double QryUnderlyingMultiple(char *Instrument)
{
	if (!mpUserSpi)
	{
		return -1; //δ��ʼ�����
	}
	//OnRspQryInstrument
	mpUserSpi->ReqQryInstrument(Instrument);//��λ����		

	int num = 0;
	while (num<30)
	{
 

			if (gUnderlyingMultiple.find(Instrument) != gUnderlyingMultiple.end())
			{
				//printf("����:%0.02f\n\n", gUnderlyingMultiple[Instrument]);
				return gUnderlyingMultiple[Instrument];
				//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

				//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
			}
			else
			{
				//printf("û�ҵ��ú�Լ%s\n", contract);
				return -2;
			}

 

		num++;
		Sleep(200);
	}


	return -3;//��ѯ��ʱ

}


//��ѯ��֤����
double QryExchangeMarginRate(char *Instrument,int type)
{
	if (!mpUserSpi)
	{
		return -1; //δ��ʼ�����
	}
	mpUserSpi->ReqQryInstrumentMarginRate(Instrument);//��λ����		

	//mpUserSpi->ReqQryInvestorProductGroupMargin(Instrument);//��λ����	
	
	int num = 0;
	while (num<30)
	{
		if (type == RATETYPE_LONG)
		{

			if (gMarginRate_long.find(Instrument) != gMarginRate_long.end())
			{

                return gMarginRate_long[Instrument];
				//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

				//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
			}
			else
			{
				//printf("û�ҵ��ú�Լ%s\n", contract);
				return -2;
			}

			
		}

		else
		{
			if (gMarginRate_short.find(Instrument) != gMarginRate_short.end())
			{


			    return gMarginRate_short[Instrument];

				//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

				//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
			}
			else
			{
				//printf("û�ҵ��ú�Լ%s\n", contract);
				return -2;
			}



		}


		num++;
		Sleep(200);
	}


	return -3;//��ѯ��ʱ
	/*


	//gPosition_S_Today::iterator it = gPosition_S_Today.find(contract);
	switch (positiontype)
	{
	 case POSITION_SELL_TODAY:
	 {
		// printf("POSITION_SELL_TODAY[%s][%d]\n", contract, gPosition_S_Today[contract]);
		if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		{
			//printf("%s ��ѯPOSITION_SELL_TODAY��λ%d\n", contract, gPosition_S_Today[contract]);


			return gPosition_S_Today[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("û�ҵ��ú�Լ%s\n", contract);
			return 0;
		}

	
	
	 }
	 break;
	 case POSITION_BUY_TODAY:
	 {
		// printf("POSITION_BUY_TODAY[%s][%d]\n", contract, gPosition_B_Today[contract]);

		 if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		 {
			// printf("%s ��ѯPOSITION_BUY_TODAY��λ%d\n", contract, gPosition_B_Today[contract]);
			 return gPosition_B_Today[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 else
		 {
			 //printf("û�ҵ��ú�Լ%s\n", contract);
			 return 0;
		 }

	 }
	 break;
	 case POSITION_SELL_HISTORY:
	 {
		 //printf("POSITION_SELL_HISTORY\n");
		 if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		 {
			// printf("%s ��ѯPOSITION_SELL_HISTORY��λ%d\n", contract, gPosition_S_History[contract]);
			 return gPosition_S_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 else
		 {
			//printf("û�ҵ��ú�Լ%s\n", contract);
			 return 0;
		 }

	 }
	 break;
	 case POSITION_BUY_HISTORY:
	 {
		// printf("POSITION_BUY_HISTORY\n");
		 if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		 {
			// printf("%s ��ѯPOSITION_BUY_HISTORY��λ%d\n", contract, gPosition_B_History[contract]);
			 return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 else
		 {
			//printf("û�ҵ��ú�Լ%s\n", contract);
			 return 0;
		 }

	 }
	 break;

	 case POSITION_SELL_ALL:
	 {  //  printf("POSITION_SELL_ALL\n");
		 int allnum = 0;

		 if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		 {
			// printf("%s A��ѯPOSITION_SELL_ALL��λ%d\n", contract, gPosition_S_History[contract]);
			 
			 allnum = gPosition_S_History[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		// else
		// {
			// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
			 //allnum= 0;
		// }


		 if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		 {
			// printf("%s B��ѯPOSITION_SELL_ALL��λ%d\n", contract, gPosition_S_Today[contract]);

			 allnum = allnum + gPosition_S_Today[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		// else
		// {
			// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
			// allnum = 0;
		// }

		 return allnum;
	 }
	 break;
	 case POSITION_BUY_ALL:
	 {   //printf("POSITION_BUY_ALL\n");
		 int allnum = 0;

		 if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		 {
			// printf("%s A��ѯPOSITION_BUY_ALL��λ%d\n", contract, gPosition_B_History[contract]);

			 allnum = gPosition_B_History[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 //else
		// {
			// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
			 //allnum= 0;
		// }


		 if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		 {
			// printf("%s B��ѯPOSITION_BUY_ALL��λ%d\n", contract, gPosition_B_Today[contract]);

			 allnum = allnum + gPosition_B_Today[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 //else
		// {
			// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
			// // allnum = 0;
		// }
		 return allnum;

	 }
	 break;

	 default:
		printf("err get\n");
		return 0;
	 break;
	}
	*/


	/*
	//map
	//string instrumentstr = pDepthMarketData->InstrumentID;
	QS_List::iterator it = mapTest.find(contract);
	if (it == mapTest.end())
	{
		//���ش����
		//m_pConnect->SetErrorMg("δ���ô�ȯ��!");
		//AddErrorPackage(head);
		//if (allprintfstate) {
		printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
		//}
		//return -1;
	}
	else
	{
		//WriteLog(0, 100, "qisd_jy:%d, qsid_zx:%d ", qsid, it->second);
		for (int k = 0; k < it->second.strategyfilenum; k++)
		{
			//if (it->second.strategyfile[k] != "")
			//{
			//if (true)
			//{
			printf("[%s] ��λ[%d]\n", contract, (it->second.strategyfile[k]).c_str(), it->second.position[k]);
			//strategy((it->second.strategyfile[k]).c_str(), pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);

		}
	}
	*/


	//return 1;
}


int  QUICKLIB_TD_API ReqQueryMaxOrderVolume(char * BrokerID,char * InvestorID,char * InstrumentID, char Direction, char  OffsetFlag,char  HedgeFlag, int MaxVolume)
{
	CThostFtdcQueryMaxOrderVolumeField req;
	memset(&req,0,sizeof(CThostFtdcQueryMaxOrderVolumeField));
	strncpy_s(req.BrokerID, sizeof(req.BrokerID), BrokerID, sizeof(req.BrokerID));
	strncpy_s(req.InvestorID, sizeof(req.InvestorID), InvestorID, sizeof(req.InvestorID));
	strncpy_s(req.InstrumentID, sizeof(req.InstrumentID), InstrumentID, sizeof(req.InstrumentID));
	req.Direction  = Direction ;
	req.OffsetFlag = OffsetFlag;
	req.HedgeFlag = HedgeFlag;
	req.MaxVolume = MaxVolume;
	return mpUserSpi->ReqQueryMaxOrderVolume(&req,1);//��λ����		
}


int  QUICKLIB_TD_API ReqQryContractBank()
{
	CThostFtdcQryContractBankField req;
	memset(&req,0,sizeof(CThostFtdcQryContractBankField));
	strcpy(req.BrokerID, gBrokerID.c_str());
	//strncpy_s(tn.BrokerID, sizeof(tn.BrokerID), BrokerID, sizeof(tn.BrokerID));
	return mpUserSpi->ReqQryContractBank(&req, 1);//��λ����		
}


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
	int nRequestID)
{
	 
	/*
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ת�ʽ��
	TThostFtdcTradeAmountType	TradeAmount;
	///�ڻ���ȡ���
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///����֧����־
	TThostFtdcFeePayFlagType	FeePayFlag;
	///Ӧ�տͻ�����
	TThostFtdcCustFeeType	CustFee;
	///Ӧ���ڻ���˾����
	TThostFtdcFutureFeeType	BrokerFee;
	///���ͷ������շ�����Ϣ
	TThostFtdcAddInfoType	Message;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///ת�˽���״̬
	TThostFtdcTransferStatusType	TransferStatus;
	///���ͻ�����
	TThostFtdcLongIndividualNameType	LongCustomerName;
	*/
 
	CThostFtdcReqTransferField req;
	memset(&req,0,sizeof(CThostFtdcReqTransferField));

	//req.TradeCode;  
	//req.BankID; //����  
	strcpy(req.BrokerID, gBrokerID.c_str());

	//req.BankBranchID; //����  
	if (req.BankBranchID[0] == 0)
	{
		strcpy(req.BankBranchID, "0000");
	}
	//req.BrokerID; //����  
	//req.BrokerBranchID; //����  
	//if (req.BrokerBranchID[0] == 0)
	//{
	//	strcpy(req.BrokerBranchID, "0000");
	//}
	//req.TradeDate;  
	//req.TradeTime;  
	//req.BankSerial;  
	//req.TradingDay;  
	//req.PlateSerial;  
	//req.LastFragment;  
	//req.SessionID;  
	//req.CustomerName;  
	//req.IdCardType;  
	//req.IdentifiedCardNo;  
	//req.CustType;  
	//req.BankAccount; //����  
	//req.BankPassWord; //����  
	strcpy(req.BankAccount, BankAccount);
	strcpy(req.BankPassWord, BankPassWord);
					  //req.AccountID;  
	//req.AccountID; //����  
	//req.Password; //����  
				  //req.InstallID;  
				  //req.FutureSerial;  
	//strcpy(req.UserID, m_UserID);
	strcpy(req.AccountID, gUserID.c_str());
	strcpy(req.UserID, gUserID.c_str());
	strcpy(req.Password, gPassword.c_str());


	//req.VerifyCertNoFlag;  
	//req.CurrencyID="CNY"; //����ұ���  
	strncpy_s(req.CurrencyID, sizeof(req.CurrencyID), "CNY", sizeof("CNY"));

	req.TradeAmount= TradeAmount;
	                 //����  
					 //req.FutureFetchAmount;  
					 //req.FeePayFlag;  
					 //req.CustFee;  
					 //req.BrokerFee;  
					 //req.Message;  
					 //req.Digest;  
					 //req.BankAccType;  
					 //req.DeviceID;  
					 //req.BankSecuAccType;  
					 //req.BrokerIDByBank;  
					 //req.BankSecuAcc;  
					 //req.BankPwdFlag;  
	req.SecuPwdFlag =  THOST_FTDC_BPWDF_BlankCheck;
	//req.OperNo;  
	//req.RequestID = reqInfo.nRequestID;
	req.RequestID =  nRequestID;
	//req.TID;  
	//req.TransferStatus;  
 
	//return mpUserSpi->ReqFromBankToFutureByFuture(&tn,1);//��λ����		
	return mpUserSpi->ReqFromBankToFutureByFuture(&req,nRequestID); //����ת�ڻ�  
 
}
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
	int nRequestID)
{
 
	CThostFtdcReqTransferField req;
	memset(&req, 0, sizeof(CThostFtdcReqTransferField));

	//req.TradeCode;  
	//req.BankID; //����  
	strcpy(req.BrokerID, gBrokerID.c_str());

	//req.BankBranchID; //����  
	if (req.BankBranchID[0] == 0)
	{
		strcpy(req.BankBranchID, "0000");
	}
	//req.BrokerID; //����  
	//req.BrokerBranchID; //����  
	//if (req.BrokerBranchID[0] == 0)
	//{
	//	strcpy(req.BrokerBranchID, "0000");
	//}
	//req.TradeDate;  
	//req.TradeTime;  
	//req.BankSerial;  
	//req.TradingDay;  
	//req.PlateSerial;  
	//req.LastFragment;  
	//req.SessionID;  
	//req.CustomerName;  
	//req.IdCardType;  
	//req.IdentifiedCardNo;  
	//req.CustType;  
	//req.BankAccount; //����  
	//req.BankPassWord; //����  
	strcpy(req.BankAccount, BankAccount);
	strcpy(req.BankPassWord, BankPassWord);
	//req.AccountID;  
	//req.AccountID; //����  
	//req.Password; //����  
	//req.InstallID;  
	//req.FutureSerial;  
	//strcpy(req.UserID, m_UserID);
	strcpy(req.AccountID, gUserID.c_str());
	strcpy(req.UserID, gUserID.c_str());
	strcpy(req.Password, gPassword.c_str());


	//req.VerifyCertNoFlag;  
	//req.CurrencyID="CNY"; //����ұ���  
	strncpy_s(req.CurrencyID, sizeof(req.CurrencyID), "CNY", sizeof("CNY"));

	req.TradeAmount = TradeAmount;
	//����  
	//req.FutureFetchAmount;  
	//req.FeePayFlag;  
	//req.CustFee;  
	//req.BrokerFee;  
	//req.Message;  
	//req.Digest;  
	//req.BankAccType;  
	//req.DeviceID;  
	//req.BankSecuAccType;  
	//req.BrokerIDByBank;  
	//req.BankSecuAcc;  
	//req.BankPwdFlag;  
	req.SecuPwdFlag = THOST_FTDC_BPWDF_BlankCheck;
	//req.OperNo;  
	//req.RequestID = reqInfo.nRequestID;
	req.RequestID = nRequestID;
	//req.TID;  
	//req.TransferStatus;  


	return  mpUserSpi->ReqFromFutureToBankByFuture(&req,nRequestID); //�ڻ�ת����  

}




int QryPosition(char *contract, int positiontype)
{

	//gPosition_S_Today::iterator it = gPosition_S_Today.find(contract);
	switch (positiontype)
	{
	case POSITION_SELL_TODAY:
	{
		// printf("POSITION_SELL_TODAY[%s][%d]\n", contract, gPosition_S_Today[contract]);
		if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		{
			//printf("%s ��ѯPOSITION_SELL_TODAY��λ%d\n", contract, gPosition_S_Today[contract]);


			return gPosition_S_Today[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("û�ҵ��ú�Լ%s\n", contract);
			return 0;
		}



	}
	break;
	case POSITION_BUY_TODAY:
	{
		// printf("POSITION_BUY_TODAY[%s][%d]\n", contract, gPosition_B_Today[contract]);

		if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		{
			// printf("%s ��ѯPOSITION_BUY_TODAY��λ%d\n", contract, gPosition_B_Today[contract]);
			return gPosition_B_Today[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("û�ҵ��ú�Լ%s\n", contract);
			return 0;
		}

	}
	break;
	case POSITION_SELL_HISTORY:
	{
		//printf("POSITION_SELL_HISTORY\n");
		if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		{
			// printf("%s ��ѯPOSITION_SELL_HISTORY��λ%d\n", contract, gPosition_S_History[contract]);
			return gPosition_S_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("û�ҵ��ú�Լ%s\n", contract);
			return 0;
		}

	}
	break;
	case POSITION_BUY_HISTORY:
	{
		// printf("POSITION_BUY_HISTORY\n");
		if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		{
			// printf("%s ��ѯPOSITION_BUY_HISTORY��λ%d\n", contract, gPosition_B_History[contract]);
			return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("û�ҵ��ú�Լ%s\n", contract);
			return 0;
		}

	}
	break;

	case POSITION_SELL_ALL:
	{  //  printf("POSITION_SELL_ALL\n");
		int allnum = 0;

		if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		{
			// printf("%s A��ѯPOSITION_SELL_ALL��λ%d\n", contract, gPosition_S_History[contract]);

			allnum = gPosition_S_History[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		// else
		// {
		// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
		//allnum= 0;
		// }


		if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		{
			// printf("%s B��ѯPOSITION_SELL_ALL��λ%d\n", contract, gPosition_S_Today[contract]);

			allnum = allnum + gPosition_S_Today[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		// else
		// {
		// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
		// allnum = 0;
		// }

		return allnum;
	}
	break;
	case POSITION_BUY_ALL:
	{   //printf("POSITION_BUY_ALL\n");
		int allnum = 0;

		if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		{
			// printf("%s A��ѯPOSITION_BUY_ALL��λ%d\n", contract, gPosition_B_History[contract]);

			allnum = gPosition_B_History[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		//else
		// {
		// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
		//allnum= 0;
		// }


		if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		{
			// printf("%s B��ѯPOSITION_BUY_ALL��λ%d\n", contract, gPosition_B_Today[contract]);

			allnum = allnum + gPosition_B_Today[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		//else
		// {
		// printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
		// // allnum = 0;
		// }
		return allnum;

	}
	break;
	default:
		printf("err get\n");
		return 0;
		break;
	}



	/*
	//map
	//string instrumentstr = pDepthMarketData->InstrumentID;
	QS_List::iterator it = mapTest.find(contract);
	if (it == mapTest.end())
	{
	//���ش����
	//m_pConnect->SetErrorMg("δ���ô�ȯ��!");
	//AddErrorPackage(head);
	//if (allprintfstate) {
	printf("û�ҵ��ú�Լ�Ĳ���%s\n", contract);
	//}
	//return -1;
	}
	else
	{
	//WriteLog(0, 100, "qisd_jy:%d, qsid_zx:%d ", qsid, it->second);
	for (int k = 0; k < it->second.strategyfilenum; k++)
	{
	//if (it->second.strategyfile[k] != "")
	//{
	//if (true)
	//{
	printf("[%s] ��λ[%d]\n", contract, (it->second.strategyfile[k]).c_str(), it->second.position[k]);
	//strategy((it->second.strategyfile[k]).c_str(), pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);

	}
	}
	*/


	//return 1;
}


int  ReqQryInstrument()
{

	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(CThostFtdcQryInstrumentField));

	//strcpy(req.BrokerID, gBrokerID.c_str());

	//strncpy_s(req.CurrencyID, sizeof(req.CurrencyID), "CNY", sizeof("CNY"));

	//req.TradeAmount = TradeAmount;

	//req.SecuPwdFlag = THOST_FTDC_BPWDF_BlankCheck;
	//req.OperNo;  
	//req.RequestID = reqInfo.nRequestID;
	//r//eq.RequestID = nRequestID;


	//return  mpUserSpi->ReqQryInstrument(&req, nRequestID); //�ڻ�ת����  
	return  mpUserSpi->ReqQryInstrument(&req, 1); //�ڻ�ת����  


}



void *QryPositionList(int i)


{
	/*
	if (gStatus)
	{
		return NULL;
	}
	if (i < 0 || (i >= (int)gMarket.size()))
	{
		return NULL;
	}
	else
	{
		//return data[i];
		return depthdata[i];
	}
	*/
	return NULL;
}


double QryBalance(bool BalanceType)
{
	if (BalanceType)
	{
		return TodayAllAmount; //��̬Ȩ��
	}
	else
	{
		return YestayAllAmount; //��̬Ȩ��
	
	}

 
}

double QryAvailable()
{

	return UserAmount;  //�����ʽ�
 
}
void SetShowPosition(bool showstate)
{
	showpositionstate = showstate;
	//return UserAmount;  //�����ʽ�

}
//double QryAvailable2()
//{

	//return UserAmount;  //�����ʽ�

//}
//double ShowPosition()
//{

	//showpositionstate = setstate;
	//return 1.2;
//}

int   OnCmd()
{
	//trategy1();

	//int t = 0;
	//while (t<10)
	//{
	//t++;
	//	Sleep(1000);
	//	printf("%d\n",t);
	// g_event.ResetEvent();
	/*
	if (hEvent)
	{
	ResetEvent(hEvent);
	}
	else
	{
	hEvent = CreateEvent(NULL, TRUE, FALSE, "abc");//TRUE�ֶ���λ
	//hEvent = CreateEvent(NULL, FALSE, FALSE, "abc");//TRUE�Զ���λ������ResetEvent
	}
	*/
	//HANDLE hearr[3];

	//hearr[0] = hEvent;

	//hearr[1] = hEvent;

	//hearr[2] = hEvent;

	DWORD dw = WaitForMultipleObjects(MAX_EVENTNUM, hEvent, FALSE, INFINITE);


	//printf("DW: %d\n",dw);
	switch (dw)
	{

		//case WAIT_FAILED:

		// Bad call to function (invalid handle?)

		//break;

		//case WAIT_TIMEOUT:

		// None of the objects became signaled within 5000 milliseconds.

		//break;

	case WAIT_OBJECT_0 + EID_OnFrontDisconnected:

		// The process identified by h[0] (hProcess1) terminated.
		return TD_NETCONNECT_BREAK;
		break;

	case WAIT_OBJECT_0 + EID_OnFrontConnected:

		// The process identified by h[1] (hProcess2) terminated.
		return TD_NETCONNECT_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogin_Scuess:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGIN_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogin_Failer:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGIN_DENIED;
		break;

/////////////////////////////////////////////////////////////////////////
	case WAIT_OBJECT_0 + EID_OnRspUserLoginout_Scuess:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGINOUT_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLoginout_Failer:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGINOUT_DENIED;
		break;


///////////////////////////////////////////////////////////////////

	//case WAIT_OBJECT_0 + EID_OnRtnDepthMarketData:

		// The process identified by h[2] (hProcess3) terminated.
		//return 0;
		//break;
	case WAIT_OBJECT_0 + EID_IsErrorRspInfo:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_SYSTEM_ERROR;
		break;
	//case WAIT_OBJECT_0 + EID_OnRspSubMarketData:

		// The process identified by h[2] (hProcess3) terminated.
	//	return 
	//	break;
	//case WAIT_OBJECT_0 + EID_OnRspUnSubMarketData:

		// The process identified by h[2] (hProcess3) terminated.

	//	break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogout:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGINOUT_SCUESS;
		break;

	case WAIT_OBJECT_0 + EID_OnRspOrder:
		return TD_ORDER_INFO;
		break;

	case WAIT_OBJECT_0 + EID_OnRspTrade:
		return TD_TRADE_INFO;
		break;


	case WAIT_OBJECT_0 + EID_OnRspQryAccountregister:
		return TD_QUERY_ACCOUNTREGISTER;
		break;


	case WAIT_OBJECT_0 + EID_OnRtnFromBankToFutureByFuture:
		return TD_BYFUTURE_BANKTOFUTURE;
		break;

	case WAIT_OBJECT_0 + EID_OnRtnFromFutureToBankByFuture:
		return TD_BYFUTURE_FUTURETOBANK;
		break;



	case WAIT_OBJECT_0 + EID_OnRspQueryMaxOrderVolume:
		return TD_QUERY_MAXORDERVOLUME;
		break;

		

	case WAIT_OBJECT_0 + EID_OnRtnInstrumentStatus:
		return TD_INSTRUMENT_STATUS;
		break;


	case WAIT_OBJECT_0 + EID_OnRspSettlementInfoConfirm:

		return TD_SETTLEMENTINFOCONFIRM;

		break;
	}
	//ResetEvent(hEvent);
	//SetEvent(hEvent);
	return TD_SYSTEM_NONE;
	//int t = 0;

	//while (t > 10)
	//{
	//}
	//	t++;

	//PulseEvent(hEvent);
	//printf("Wait for a New Tick\n");
	//::WaitForSingleObject(hEvent, INFINITE);
	//printf("A New Tick...\n");
	//SetEvent(hEvent);

	//Sleep(500);
	//}
	//printf("End \n");
	//return true;
	/*
	Py_Initialize();

	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("Test0010");	    //Test001:Python�ļ���
	pFunc = PyObject_GetAttrString(pModule, "add");	//Add:Python�ļ��еĺ�����
	PyObject *pArgs = PyTuple_New(2);               //�������õĲ������ݾ�����Ԫ�����ʽ�����,2��ʾ��������
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 5));//0---���  i��ʾ����int�ͱ���
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));//1---���
	//����ֵ
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFunc, pArgs);	    //���ú���
	//������ֵת��Ϊint����
	int result;
	PyArg_Parse(pReturn, "i", &result);    //i��ʾת����int�ͱ���
	cout << "5+7 = " << result << endl;

	//Py_Finalize();
	*/
}

//bool   OnTick()
//{
//trategy1();

//int t = 0;
//while (t<10)
//{
//t++;
//	Sleep(1000);
//	printf("%d\n",t);
// g_event.ResetEvent();
/*
if (hEvent)
{
ResetEvent(hEvent);
}
else
{
hEvent = CreateEvent(NULL, TRUE, FALSE, "abc");//TRUE�ֶ���λ
//hEvent = CreateEvent(NULL, FALSE, FALSE, "abc");//TRUE�Զ���λ������ResetEvent
}
*/

//ResetEvent(hEvent);
//SetEvent(hEvent);

//int t = 0;

//while (t > 10)
//{
//}
//	t++;

//PulseEvent(hEvent);
//printf("Wait for a New Tick\n");
//::WaitForSingleObject(hEvent[EID_OnRtnDepthMarketData], INFINITE);
//printf("A New Tick...\n");
//SetEvent(hEvent);

//Sleep(500);
//}
//printf("End \n");
//return true;
/*
Py_Initialize();

PyObject * pModule = NULL;
PyObject * pFunc = NULL;
pModule = PyImport_ImportModule("Test0010");	    //Test001:Python�ļ���
pFunc = PyObject_GetAttrString(pModule, "add");	//Add:Python�ļ��еĺ�����
PyObject *pArgs = PyTuple_New(2);               //�������õĲ������ݾ�����Ԫ�����ʽ�����,2��ʾ��������
PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 5));//0---���  i��ʾ����int�ͱ���
PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));//1---���
//����ֵ
PyObject *pReturn = NULL;
pReturn = PyEval_CallObject(pFunc, pArgs);	    //���ú���
//������ֵת��Ϊint����
int result;
PyArg_Parse(pReturn, "i", &result);    //i��ʾת����int�ͱ���
cout << "5+7 = " << result << endl;

//Py_Finalize();
*/
//}
/*
char listname[31] = { 0 };
char *   GetTickInstrument()
{
if (cmdlist.size() <= 0)
{
return "";
}
//memcpy_s(StockData[stockid], sizeof(CSecurityFtdcL2TradeField), &(*cmdlist.begin()), sizeof(CSecurityFtdcL2TradeField));
//printf("stockid:[%d]\n", stockid)
//memcpy_s(&(StockData[stockid]->data), sizeof(CSecurityFtdcL2TradeField_S), &cmdlist.begin(), sizeof(CSecurityFtdcL2TradeField_S));
//StockData[stockid]->data.ExchangeID
//printf("ԭʼ���� InstrumentID[%s] price[%0.02f]\n", cmdlist.begin()->InstrumentID, cmdlist.begin()->Price);
//char temp[200] = { 0 };
//_snprintf_s(temp,sizeof(temp),sizeof(temp),"%s||%d",)
//printf("�������allow[%d] InstrumentID[%s] price[%0.02f]\n", StockData[stockid]->allow, StockData[stockid]->data.InstrumentID, StockData[stockid]->data.Price);
//char * newdata = new char[31];
//memset
//_snprintf_s(&listname, sizeof(listname), sizeof(listname), "%s",cmdlist.begin()->Instrument);


memset(&listname, 0, sizeof(listname));
memcpy_s(&listname, sizeof(listname), cmdlist.begin()->content, sizeof(listname));

//�ٽ���
EnterCriticalSection(&g_csdata);
cmdlist.erase(cmdlist.begin());
//�ٽ���
LeaveCriticalSection(&g_csdata);
return listname;
}
*/
int GetUnGetCmdSize()
{
	return cmdlist.size()+ orderlist.size();
}

int  GetCmd()
{

	//return 
	//memcpy_s(StockData[stockid], sizeof(CSecurityFtdcL2TradeField), &(*cmdlist.begin()), sizeof(CSecurityFtdcL2TradeField));

	//printf("stockid:[%d]\n", stockid);
	

	//memcpy_s(&(StockData[stockid]->data), sizeof(CSecurityFtdcL2TradeField_S), &cmdlist.begin(), sizeof(CSecurityFtdcL2TradeField_S));

	//StockData[stockid]->data.ExchangeID

	//printf("ԭʼ���� InstrumentID[%s] price[%0.02f]\n", cmdlist.begin()->InstrumentID, cmdlist.begin()->Price);


	//char temp[200] = { 0 };
	//_snprintf_s(temp,sizeof(temp),sizeof(temp),"%s||%d",)
	//printf("�������allow[%d] InstrumentID[%s] price[%0.02f]\n", StockData[stockid]->allow, StockData[stockid]->data.InstrumentID, StockData[stockid]->data.Price);
	//char * newdata = new char[31];
	//memset
	//_snprintf_s(&listname, sizeof(listname), sizeof(listname), "%s",cmdlist.begin()->Instrument);

	if (cmdlist.size() > 0)
	{
		//printf("aaaaaaaaaaaaaaaaaaa\n");
		//�ٽ���
	   //EnterCriticalSection(&g_csdata);
	   return cmdlist.begin()->cmd;
	   //�ٽ���
	   //EnterCriticalSection(&g_csdata);
	   //cmdlist.erase(cmdlist.begin());
	   //LeaveCriticalSection(&g_csdata);
	   //�ٽ���
	}
	else if (orderlist.size() > 0)
	{
		return TD_ORDER_INFO;
	}	
 	else
	{
		return  TD_SYSTEM_NONE;
	}
}

char listcmd[31] = { 0 };
char *   GetCmdContent2()
{
	if (cmdlist.size() <= 0)
	{
		return "";
	}
	//memcpy_s(StockData[stockid], sizeof(CSecurityFtdcL2TradeField), &(*cmdlist.begin()), sizeof(CSecurityFtdcL2TradeField));

	//printf("stockid:[%d]\n", stockid);


	//memcpy_s(&(StockData[stockid]->data), sizeof(CSecurityFtdcL2TradeField_S), &cmdlist.begin(), sizeof(CSecurityFtdcL2TradeField_S));

	//StockData[stockid]->data.ExchangeID

	//printf("ԭʼ���� InstrumentID[%s] price[%0.02f]\n", cmdlist.begin()->InstrumentID, cmdlist.begin()->Price);


	//char temp[200] = { 0 };
	//_snprintf_s(temp,sizeof(temp),sizeof(temp),"%s||%d",)
	//printf("�������allow[%d] InstrumentID[%s] price[%0.02f]\n", StockData[stockid]->allow, StockData[stockid]->data.InstrumentID, StockData[stockid]->data.Price);
	//char * newdata = new char[31];
	//memset
	//_snprintf_s(&listname, sizeof(listname), sizeof(listname), "%s",cmdlist.begin()->Instrument);


	memset(&listcmd, 0, sizeof(listcmd));
	memcpy_s(&listcmd, sizeof(listcmd), cmdlist.begin()->content, sizeof(listcmd));

	//�ٽ���
	//EnterCriticalSection(&g_csdata);
	cmdlist.erase(cmdlist.begin());
	//�ٽ���
	LeaveCriticalSection(&g_csdata);

	return listcmd;

}

void *GetCmdContent()
{
	if (cmdlist.size() <= 0)
	{
		return NULL;
	}
	else
	{
		memset(&listcmd, 0, sizeof(listcmd));
		memcpy_s(&listcmd, sizeof(listcmd), cmdlist.begin()->content, sizeof(listcmd));

		//�ٽ���
		//EnterCriticalSection(&g_csdata);
		cmdlist.erase(cmdlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);

		return listcmd;
	}
}

//�����ر�
CThostFtdcOrderField * orderdata =  new CThostFtdcOrderField;
void *GetCmdContent_Order()
{		
	if(orderlist.size() > 0)
	{
		memset(orderdata, 0, sizeof(CThostFtdcOrderField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		/*
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�����ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������Դ
	TThostFtdcOrderSourceType	OrderSource;
	///����״̬
	TThostFtdcOrderStatusType	OrderStatus;
	///��������
	TThostFtdcOrderTypeType	OrderType;
	///��ɽ�����
	TThostFtdcVolumeType	VolumeTraded;
	///ʣ������
	TThostFtdcVolumeType	VolumeTotal;
	///��������
	TThostFtdcDateType	InsertDate;
	///ί��ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	ActiveTime;
	///����ʱ��
	TThostFtdcTimeType	SuspendTime;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����޸Ľ���������Ա����
	TThostFtdcTraderIDType	ActiveTraderID;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�û�ǿ����־
	TThostFtdcBoolType	UserForceClose;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///��ر���
	TThostFtdcOrderSysIDType	RelativeOrderSysID;
	///֣�����ɽ�����
	TThostFtdcVolumeType	ZCETotalTradedVolume;
	///��������־
	TThostFtdcBoolType	IsSwapOrder;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
 */
		//orderdata->cmd = orderlist.begin()->cmd;
		memcpy_s(orderdata-> BrokerID, sizeof(TThostFtdcBrokerIDType), orderlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(orderdata-> InvestorID, sizeof(TThostFtdcInvestorIDType), orderlist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		
		
		memcpy_s(orderdata->InstrumentID, sizeof(TThostFtdcInstrumentIDType), orderlist.begin()->InstrumentID, sizeof(TThostFtdcInstrumentIDType));
		memcpy_s(orderdata->OrderRef, sizeof(TThostFtdcOrderRefType), orderlist.begin()->OrderRef, sizeof(TThostFtdcOrderRefType));
		memcpy_s(orderdata->UserID, sizeof(TThostFtdcUserIDType), orderlist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		orderdata->OrderPriceType = orderlist.begin()->OrderPriceType;
		orderdata->Direction = orderlist.begin()->Direction;
		memcpy_s(orderdata->CombOffsetFlag, sizeof(TThostFtdcCombOffsetFlagType), orderlist.begin()->CombOffsetFlag, sizeof(TThostFtdcCombOffsetFlagType));
		memcpy_s(orderdata->CombHedgeFlag, sizeof(TThostFtdcCombHedgeFlagType)  , orderlist.begin()->CombHedgeFlag, sizeof(TThostFtdcCombHedgeFlagType));
		orderdata->LimitPrice = orderlist.begin()->LimitPrice;
		orderdata->VolumeTotalOriginal = orderlist.begin()->VolumeTotalOriginal;
		orderdata->TimeCondition= orderlist.begin()->TimeCondition;
		memcpy_s(orderdata->GTDDate, sizeof(TThostFtdcDateType), orderlist.begin()->GTDDate, sizeof(TThostFtdcDateType));
		orderdata->VolumeCondition= orderlist.begin()->VolumeCondition;
		orderdata->MinVolume = orderlist.begin()->MinVolume;
		orderdata->ContingentCondition = orderlist.begin()->ContingentCondition;
		orderdata->StopPrice = orderlist.begin()->StopPrice;
		orderdata->ForceCloseReason = orderlist.begin()->ForceCloseReason;
		orderdata->IsAutoSuspend = orderlist.begin()->IsAutoSuspend;
		memcpy_s(orderdata->BusinessUnit, sizeof(TThostFtdcBusinessUnitType), orderlist.begin()->BusinessUnit, sizeof(TThostFtdcBusinessUnitType));
		

		orderlist.erase(orderlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return orderdata;
	}
	else
	{
		return NULL;
	}
}


//�ɽ��ر�
CThostFtdcTradeField tradedata;
void *GetCmdContent_Trade()
{
	if (tradelist.size() > 0)
	{
		memset(&tradedata, 0, sizeof(CThostFtdcTradeField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		memcpy_s(tradedata.BrokerID, sizeof(TThostFtdcBrokerIDType), tradelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(tradedata.InvestorID, sizeof(TThostFtdcInvestorIDType), tradelist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		memcpy_s(tradedata.InstrumentID, sizeof(TThostFtdcInstrumentIDType), tradelist.begin()->InstrumentID, sizeof(TThostFtdcInstrumentIDType));
		memcpy_s(tradedata.OrderRef, sizeof(TThostFtdcOrderRefType), tradelist.begin()->OrderRef, sizeof(TThostFtdcOrderRefType));
		memcpy_s(tradedata.UserID, sizeof(TThostFtdcUserIDType), tradelist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		memcpy_s(tradedata.ExchangeID, sizeof(TThostFtdcExchangeIDType), tradelist.begin()->ExchangeID, sizeof(TThostFtdcExchangeIDType));  // b
		memcpy_s(tradedata.TradeID, sizeof(TThostFtdcTradeIDType), tradelist.begin()->TradeID, sizeof(TThostFtdcTradeIDType));  //b
		tradedata.Direction = tradelist.begin()->Direction;  //b
		memcpy_s(tradedata.OrderSysID, sizeof(TThostFtdcOrderSysIDType), tradelist.begin()->OrderSysID, sizeof(TThostFtdcOrderSysIDType));  //b
		memcpy_s(tradedata.ParticipantID, sizeof(TThostFtdcParticipantIDType), tradelist.begin()->ParticipantID, sizeof(TThostFtdcParticipantIDType));  //b
		memcpy_s(tradedata.ClientID, sizeof(TThostFtdcClientIDType), tradelist.begin()->ClientID, sizeof(TThostFtdcClientIDType));  //b	
		tradedata.TradingRole = tradelist.begin()->TradingRole;  //b
		memcpy_s(tradedata.ExchangeInstID, sizeof(TThostFtdcExchangeInstIDType), tradelist.begin()->ExchangeInstID, sizeof(TThostFtdcExchangeInstIDType));  //b
		tradedata.OffsetFlag = tradelist.begin()->OffsetFlag;  //b
		tradedata.HedgeFlag = tradelist.begin()->HedgeFlag;  //b
		tradedata.Price = tradelist.begin()->Price;  //b
		tradedata.Volume = tradelist.begin()->Volume;  //b
		memcpy_s(tradedata.TradeDate, sizeof(TThostFtdcDateType), tradelist.begin()->TradeDate, sizeof(TThostFtdcDateType));  //b
		memcpy_s(tradedata.TradeTime, sizeof(TThostFtdcTimeType), tradelist.begin()->TradeTime, sizeof(TThostFtdcTimeType));  //b
		tradedata.TradeType = tradelist.begin()->TradeType;  //b
		tradedata.PriceSource = tradelist.begin()->PriceSource;  //b
		memcpy_s(tradedata.TraderID, sizeof(TThostFtdcTraderIDType), tradelist.begin()->TraderID, sizeof(TThostFtdcTraderIDType));  //b
		memcpy_s(tradedata.OrderLocalID, sizeof(TThostFtdcOrderLocalIDType), tradelist.begin()->OrderLocalID, sizeof(TThostFtdcOrderLocalIDType));  //b
		memcpy_s(tradedata.ClearingPartID, sizeof(TThostFtdcParticipantIDType), tradelist.begin()->ClearingPartID, sizeof(TThostFtdcParticipantIDType));  //b
		memcpy_s(tradedata.BusinessUnit, sizeof(TThostFtdcBusinessUnitType), tradelist.begin()->BusinessUnit, sizeof(TThostFtdcBusinessUnitType));  //b
		tradedata.SequenceNo = tradelist.begin()->SequenceNo;  //b
		memcpy_s(tradedata.TradingDay, sizeof(TThostFtdcDateType), tradelist.begin()->TradingDay, sizeof(TThostFtdcDateType));  //b
		tradedata.SettlementID = tradelist.begin()->SettlementID;  //b
		tradedata.BrokerOrderSeq = tradelist.begin()->BrokerOrderSeq;  //b
		tradedata.TradeSource = tradelist.begin()->TradeSource;  //b

		tradelist.erase(tradelist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		//orderlist.begin()->AccountID
		//�ٽ���
		//EnterCriticalSection(&g_csdata);
		//orderlist.erase(orderlist.begin());
		//�ٽ���
		//LeaveCriticalSection(&g_csdata);

		//printf("c++[%d] BranchID[%s] InvestorID[%s]\n",
		//	orderdata->cmd, orderdata->content.BrokerID, orderdata->content.InvestorID);
		
		return &tradedata;
	}
	else
	{
		return NULL;
	}
}






//�ڻ����������ʽ�ת�ڻ�֪ͨ
CThostFtdcRspTransferField  banktofuturebyfuturedata;// = new CThostFtdcRspTransferField;
void *GetCmdContent_BankToFutureByFuture()
{
	if (banktofuturebyfuturelist.size() > 0)
	{
		memset(&banktofuturebyfuturedata, 0, sizeof(CThostFtdcTradeField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		memcpy_s(banktofuturebyfuturedata.TradeCode, sizeof(TThostFtdcTradeCodeType), banktofuturebyfuturelist.begin()->TradeCode, sizeof(TThostFtdcTradeCodeType));
		memcpy_s(banktofuturebyfuturedata.BankID, sizeof(TThostFtdcBankIDType), banktofuturebyfuturelist.begin()->BankID, sizeof(TThostFtdcBankIDType));
		memcpy_s(banktofuturebyfuturedata.BankBranchID, sizeof(TThostFtdcBankBrchIDType), banktofuturebyfuturelist.begin()->BankBranchID, sizeof(TThostFtdcBankBrchIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerID, sizeof(TThostFtdcBrokerIDType), banktofuturebyfuturelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType), banktofuturebyfuturelist.begin()->BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType));
		memcpy_s(banktofuturebyfuturedata.TradeDate, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradeDate, sizeof(TThostFtdcTradeDateType));
		memcpy_s(banktofuturebyfuturedata.TradeTime, sizeof(TThostFtdcTradeTimeType), banktofuturebyfuturelist.begin()->TradeTime, sizeof(TThostFtdcTradeTimeType));
		memcpy_s(banktofuturebyfuturedata.BankSerial, sizeof(TThostFtdcBankSerialType), banktofuturebyfuturelist.begin()->BankSerial, sizeof(TThostFtdcBankSerialType));
		memcpy_s(banktofuturebyfuturedata.TradingDay, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradingDay, sizeof(TThostFtdcTradeDateType));
		banktofuturebyfuturedata.PlateSerial = banktofuturebyfuturelist.begin()->PlateSerial;
		banktofuturebyfuturedata.LastFragment = banktofuturebyfuturelist.begin()->LastFragment;
		banktofuturebyfuturedata.SessionID = banktofuturebyfuturelist.begin()->SessionID;
		memcpy_s(banktofuturebyfuturedata.CustomerName, sizeof(TThostFtdcIndividualNameType), banktofuturebyfuturelist.begin()->CustomerName, sizeof(TThostFtdcIndividualNameType));
		banktofuturebyfuturedata.IdCardType = banktofuturebyfuturelist.begin()->IdCardType;
		memcpy_s(banktofuturebyfuturedata.IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType), banktofuturebyfuturelist.begin()->IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType));
		banktofuturebyfuturedata.CustType = banktofuturebyfuturelist.begin()->CustType;
		memcpy_s(banktofuturebyfuturedata.BankAccount, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankAccount, sizeof(TThostFtdcBankAccountType));
		memcpy_s(banktofuturebyfuturedata.BankPassWord, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->BankPassWord, sizeof(TThostFtdcPasswordType));
		memcpy_s(banktofuturebyfuturedata.AccountID, sizeof(TThostFtdcAccountIDType), banktofuturebyfuturelist.begin()->AccountID, sizeof(TThostFtdcAccountIDType));
		memcpy_s(banktofuturebyfuturedata.Password, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->Password, sizeof(TThostFtdcPasswordType));
		banktofuturebyfuturedata.InstallID = banktofuturebyfuturelist.begin()->InstallID;
		banktofuturebyfuturedata.FutureSerial = banktofuturebyfuturelist.begin()->FutureSerial;
		memcpy_s(banktofuturebyfuturedata.UserID, sizeof(TThostFtdcUserIDType), banktofuturebyfuturelist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		banktofuturebyfuturedata.VerifyCertNoFlag = banktofuturebyfuturelist.begin()->VerifyCertNoFlag;
		memcpy_s(banktofuturebyfuturedata.CurrencyID, sizeof(TThostFtdcCurrencyIDType), banktofuturebyfuturelist.begin()->CurrencyID, sizeof(TThostFtdcCurrencyIDType));
		banktofuturebyfuturedata.TradeAmount = banktofuturebyfuturelist.begin()->TradeAmount;
		banktofuturebyfuturedata.FutureFetchAmount = banktofuturebyfuturelist.begin()->FutureFetchAmount;
		banktofuturebyfuturedata.FeePayFlag = banktofuturebyfuturelist.begin()->FeePayFlag;
		banktofuturebyfuturedata.CustFee = banktofuturebyfuturelist.begin()->CustFee;
		banktofuturebyfuturedata.BrokerFee = banktofuturebyfuturelist.begin()->BrokerFee;
		memcpy_s(banktofuturebyfuturedata.Message, sizeof(TThostFtdcAddInfoType), banktofuturebyfuturelist.begin()->Message, sizeof(TThostFtdcAddInfoType));
		memcpy_s(banktofuturebyfuturedata.Digest, sizeof(TThostFtdcDigestType), banktofuturebyfuturelist.begin()->Digest, sizeof(TThostFtdcDigestType));
		banktofuturebyfuturedata.BankAccType = banktofuturebyfuturelist.begin()->BankAccType;
		memcpy_s(banktofuturebyfuturedata.DeviceID, sizeof(TThostFtdcDeviceIDType), banktofuturebyfuturelist.begin()->DeviceID, sizeof(TThostFtdcDeviceIDType));
		banktofuturebyfuturedata.BankSecuAccType = banktofuturebyfuturelist.begin()->BankSecuAccType;
		memcpy_s(banktofuturebyfuturedata.BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType), banktofuturebyfuturelist.begin()->BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType));
		memcpy_s(banktofuturebyfuturedata.BankSecuAcc, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankSecuAcc, sizeof(TThostFtdcBankAccountType));
		banktofuturebyfuturedata.BankPwdFlag = banktofuturebyfuturelist.begin()->BankPwdFlag;
		banktofuturebyfuturedata.SecuPwdFlag = banktofuturebyfuturelist.begin()->SecuPwdFlag;
		memcpy_s(banktofuturebyfuturedata.OperNo, sizeof(TThostFtdcOperNoType), banktofuturebyfuturelist.begin()->OperNo, sizeof(TThostFtdcOperNoType));
		banktofuturebyfuturedata.RequestID = banktofuturebyfuturelist.begin()->RequestID;
		banktofuturebyfuturedata.TID= banktofuturebyfuturelist.begin()->TID;
		banktofuturebyfuturedata.TransferStatus = banktofuturebyfuturelist.begin()->TransferStatus;
		banktofuturebyfuturedata.ErrorID = banktofuturebyfuturelist.begin()->ErrorID;
		memcpy_s(banktofuturebyfuturedata.ErrorMsg, sizeof(TThostFtdcErrorMsgType), banktofuturebyfuturelist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));
//		memcpy_s(banktofuturebyfuturedata.LongCustomerName, sizeof(TThostFtdcLongIndividualNameType), banktofuturebyfuturelist.begin()->LongCustomerName, sizeof(TThostFtdcLongIndividualNameType));
		
	
		banktofuturebyfuturelist.erase(banktofuturebyfuturelist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		//orderlist.begin()->AccountID
		//�ٽ���
		//EnterCriticalSection(&g_csdata);
		//orderlist.erase(orderlist.begin());
		//�ٽ���
		//LeaveCriticalSection(&g_csdata);

		return &banktofuturebyfuturedata;
		//return &(orderlist.begin());
	}
	else
	{
		return NULL;
	}
}


//�ڻ����������ʽ�ת�ڻ�֪ͨ
CThostFtdcRspTransferField  futuretobankbyfuturedata;
void *GetCmdContent_FutureToBankByFuture()
{
	if (futuretobankbyfuturelist.size() > 0)
	{
		memset(&futuretobankbyfuturedata, 0, sizeof(CThostFtdcTradeField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		memcpy_s(banktofuturebyfuturedata.TradeCode, sizeof(TThostFtdcTradeCodeType), banktofuturebyfuturelist.begin()->TradeCode, sizeof(TThostFtdcTradeCodeType));
		memcpy_s(banktofuturebyfuturedata.BankID, sizeof(TThostFtdcBankIDType), banktofuturebyfuturelist.begin()->BankID, sizeof(TThostFtdcBankIDType));
		memcpy_s(banktofuturebyfuturedata.BankBranchID, sizeof(TThostFtdcBankBrchIDType), banktofuturebyfuturelist.begin()->BankBranchID, sizeof(TThostFtdcBankBrchIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerID, sizeof(TThostFtdcBrokerIDType), banktofuturebyfuturelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType), banktofuturebyfuturelist.begin()->BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType));
		memcpy_s(banktofuturebyfuturedata.TradeDate, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradeDate, sizeof(TThostFtdcTradeDateType));
		memcpy_s(banktofuturebyfuturedata.TradeTime, sizeof(TThostFtdcTradeTimeType), banktofuturebyfuturelist.begin()->TradeTime, sizeof(TThostFtdcTradeTimeType));
		memcpy_s(banktofuturebyfuturedata.BankSerial, sizeof(TThostFtdcBankSerialType), banktofuturebyfuturelist.begin()->BankSerial, sizeof(TThostFtdcBankSerialType));
		memcpy_s(banktofuturebyfuturedata.TradingDay, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradingDay, sizeof(TThostFtdcTradeDateType));
		banktofuturebyfuturedata.PlateSerial = banktofuturebyfuturelist.begin()->PlateSerial;
		banktofuturebyfuturedata.LastFragment = banktofuturebyfuturelist.begin()->LastFragment;
		banktofuturebyfuturedata.SessionID = banktofuturebyfuturelist.begin()->SessionID;
		memcpy_s(banktofuturebyfuturedata.CustomerName, sizeof(TThostFtdcIndividualNameType), banktofuturebyfuturelist.begin()->CustomerName, sizeof(TThostFtdcIndividualNameType));
		banktofuturebyfuturedata.IdCardType = banktofuturebyfuturelist.begin()->IdCardType;
		memcpy_s(banktofuturebyfuturedata.IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType), banktofuturebyfuturelist.begin()->IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType));
		banktofuturebyfuturedata.CustType = banktofuturebyfuturelist.begin()->CustType;
		memcpy_s(banktofuturebyfuturedata.BankAccount, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankAccount, sizeof(TThostFtdcBankAccountType));
		memcpy_s(banktofuturebyfuturedata.BankPassWord, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->BankPassWord, sizeof(TThostFtdcPasswordType));
		memcpy_s(banktofuturebyfuturedata.AccountID, sizeof(TThostFtdcAccountIDType), banktofuturebyfuturelist.begin()->AccountID, sizeof(TThostFtdcAccountIDType));
		memcpy_s(banktofuturebyfuturedata.Password, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->Password, sizeof(TThostFtdcPasswordType));
		banktofuturebyfuturedata.InstallID = banktofuturebyfuturelist.begin()->InstallID;
		banktofuturebyfuturedata.FutureSerial = banktofuturebyfuturelist.begin()->FutureSerial;
		memcpy_s(banktofuturebyfuturedata.UserID, sizeof(TThostFtdcUserIDType), banktofuturebyfuturelist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		banktofuturebyfuturedata.VerifyCertNoFlag = banktofuturebyfuturelist.begin()->VerifyCertNoFlag;
		memcpy_s(banktofuturebyfuturedata.CurrencyID, sizeof(TThostFtdcCurrencyIDType), banktofuturebyfuturelist.begin()->CurrencyID, sizeof(TThostFtdcCurrencyIDType));
		banktofuturebyfuturedata.TradeAmount = banktofuturebyfuturelist.begin()->TradeAmount;
		banktofuturebyfuturedata.FutureFetchAmount = banktofuturebyfuturelist.begin()->FutureFetchAmount;
		banktofuturebyfuturedata.FeePayFlag = banktofuturebyfuturelist.begin()->FeePayFlag;
		banktofuturebyfuturedata.CustFee = banktofuturebyfuturelist.begin()->CustFee;
		banktofuturebyfuturedata.BrokerFee = banktofuturebyfuturelist.begin()->BrokerFee;
		memcpy_s(banktofuturebyfuturedata.Message, sizeof(TThostFtdcAddInfoType), banktofuturebyfuturelist.begin()->Message, sizeof(TThostFtdcAddInfoType));
		memcpy_s(banktofuturebyfuturedata.Digest, sizeof(TThostFtdcDigestType), banktofuturebyfuturelist.begin()->Digest, sizeof(TThostFtdcDigestType));
		banktofuturebyfuturedata.BankAccType = banktofuturebyfuturelist.begin()->BankAccType;
		memcpy_s(banktofuturebyfuturedata.DeviceID, sizeof(TThostFtdcDeviceIDType), banktofuturebyfuturelist.begin()->DeviceID, sizeof(TThostFtdcDeviceIDType));
		banktofuturebyfuturedata.BankSecuAccType = banktofuturebyfuturelist.begin()->BankSecuAccType;
		memcpy_s(banktofuturebyfuturedata.BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType), banktofuturebyfuturelist.begin()->BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType));
		memcpy_s(banktofuturebyfuturedata.BankSecuAcc, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankSecuAcc, sizeof(TThostFtdcBankAccountType));
		banktofuturebyfuturedata.BankPwdFlag = banktofuturebyfuturelist.begin()->BankPwdFlag;
		banktofuturebyfuturedata.SecuPwdFlag = banktofuturebyfuturelist.begin()->SecuPwdFlag;
		memcpy_s(banktofuturebyfuturedata.OperNo, sizeof(TThostFtdcOperNoType), banktofuturebyfuturelist.begin()->OperNo, sizeof(TThostFtdcOperNoType));
		banktofuturebyfuturedata.RequestID = banktofuturebyfuturelist.begin()->RequestID;
		banktofuturebyfuturedata.TID = banktofuturebyfuturelist.begin()->TID;
		banktofuturebyfuturedata.TransferStatus = banktofuturebyfuturelist.begin()->TransferStatus;
		banktofuturebyfuturedata.ErrorID = banktofuturebyfuturelist.begin()->ErrorID;
		memcpy_s(banktofuturebyfuturedata.ErrorMsg, sizeof(TThostFtdcErrorMsgType), banktofuturebyfuturelist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));
//		memcpy_s(banktofuturebyfuturedata.LongCustomerName, sizeof(TThostFtdcLongIndividualNameType), banktofuturebyfuturelist.begin()->LongCustomerName, sizeof(TThostFtdcLongIndividualNameType));



		futuretobankbyfuturelist.erase(futuretobankbyfuturelist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		//orderlist.begin()->AccountID
		//�ٽ���
		//EnterCriticalSection(&g_csdata);
		//orderlist.erase(orderlist.begin());
		//�ٽ���
		//LeaveCriticalSection(&g_csdata);

		return &futuretobankbyfuturedata;
		//return &(orderlist.begin());
	}
	else
	{
		return NULL;
	}
}



//�ڻ����������ʽ�ת�ڻ�֪ͨ
CThostFtdcQueryMaxOrderVolumeField  querymaxordervolumedata;;
void *GetCmdContent_QueryMaxOrderVolume()
{
	if (querymaxordervolumelist.size() > 0)
	{
		memset(&querymaxordervolumedata, 0, sizeof(CThostFtdcQueryMaxOrderVolumeField));
		EnterCriticalSection(&g_csdata);
		memcpy_s(querymaxordervolumedata.BrokerID, sizeof(TThostFtdcBrokerIDType), querymaxordervolumelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(querymaxordervolumedata.InvestorID, sizeof(TThostFtdcInvestorIDType), querymaxordervolumelist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		memcpy_s(querymaxordervolumedata.InstrumentID, sizeof(TThostFtdcInstrumentIDType), querymaxordervolumelist.begin()->InstrumentID, sizeof(TThostFtdcInstrumentIDType));
		querymaxordervolumedata.Direction = querymaxordervolumelist.begin()->Direction;
		querymaxordervolumedata.OffsetFlag = querymaxordervolumelist.begin()->OffsetFlag;
		querymaxordervolumedata.HedgeFlag = querymaxordervolumelist.begin()->HedgeFlag;
		querymaxordervolumedata.MaxVolume = querymaxordervolumelist.begin()->MaxVolume;
		querymaxordervolumelist.erase(querymaxordervolumelist.begin());
		LeaveCriticalSection(&g_csdata);
		return &querymaxordervolumedata;
	}
	else
	{
		return NULL;
	}
}




//����ȷ��
CThostFtdcSettlementInfoConfirmField settlementdata;// = new CThostFtdcSettlementInfoConfirmField;
void *GetCmdContent_Settlement()
{
	if (settlementlist.size() > 0)
	{
		memset(&settlementdata, 0, sizeof(CThostFtdcSettlementInfoConfirmField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		
		memcpy_s(settlementdata.BrokerID,    sizeof(TThostFtdcBrokerIDType), settlementlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(settlementdata.InvestorID,  sizeof(TThostFtdcInvestorIDType), settlementlist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		memcpy_s(settlementdata.ConfirmDate, sizeof(TThostFtdcDateType), settlementlist.begin()->ConfirmDate, sizeof(TThostFtdcDateType));
		memcpy_s(settlementdata.ConfirmTime, sizeof(TThostFtdcTimeType), settlementlist.begin()->ConfirmTime, sizeof(TThostFtdcTimeType));

		settlementlist.erase(settlementlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);


		return &settlementdata;
	}
	else
	{
		return NULL;
	}
}


//��������
CThostFtdcRspInfoField errdata;// = new  CThostFtdcRspInfoField;
void *GetCmdContent_Error()
{
	if (errorlist.size() > 0)
	{
		memset(&errdata, 0, sizeof(CThostFtdcRspInfoField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		errdata.ErrorID = errorlist.begin()->ErrorID;
		memcpy_s(errdata.ErrorMsg, sizeof(TThostFtdcErrorMsgType), errorlist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		errorlist.erase(errorlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return &errdata;
	}
	else
	{
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
 



//��¼
CThostFtdcRspUserLoginField logindata;// = new CThostFtdcRspUserLoginField;
void *GetCmdContent_LoginScuess()
{
	if (loginlist.size() > 0)
	{
		memset(&logindata, 0, sizeof(CThostFtdcRspUserLoginField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = loginlist.begin()->ErrorID;
		memcpy_s(logindata.TradingDay, sizeof(TThostFtdcDateType), loginlist.begin()->TradingDay, sizeof(TThostFtdcDateType));
		memcpy_s(logindata.LoginTime,  sizeof(TThostFtdcTimeType), loginlist.begin()->LoginTime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.BrokerID,   sizeof(TThostFtdcBrokerIDType), loginlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(logindata.UserID, sizeof(TThostFtdcUserIDType), loginlist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		memcpy_s(logindata.SystemName, sizeof(TThostFtdcSystemNameType), loginlist.begin()->SystemName, sizeof(TThostFtdcSystemNameType));
		logindata.FrontID = loginlist.begin()->FrontID;
		logindata.SessionID = loginlist.begin()->SessionID;
		memcpy_s(logindata.MaxOrderRef, sizeof(TThostFtdcOrderRefType), loginlist.begin()->MaxOrderRef, sizeof(TThostFtdcOrderRefType));
		
		memcpy_s(logindata.SHFETime, sizeof(TThostFtdcTimeType), loginlist.begin()->SHFETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.DCETime, sizeof(TThostFtdcTimeType), loginlist.begin()->DCETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.CZCETime, sizeof(TThostFtdcTimeType), loginlist.begin()->CZCETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.FFEXTime, sizeof(TThostFtdcTimeType), loginlist.begin()->FFEXTime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.INETime, sizeof(TThostFtdcTimeType), loginlist.begin()->INETime, sizeof(TThostFtdcTimeType));
		loginlist.erase(loginlist.begin());

		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return &logindata;
	}
	else
	{
		return NULL;
	}
}



//����
int * connectdata = new int;
void *GetCmdContent_Connected()
{
	if (connectlist.size() > 0)
	{
		memset(connectdata, 0, sizeof(int));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = connectlist.begin()->ErrorID;
		//memcpy_s(errdata->ErrorMsg, sizeof(TThostFtdcErrorMsgType), connectlist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		connectlist.erase(connectlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return connectdata;
	}
	else
	{
		return NULL;
	}
}

//�����ѯ��Լ��֤������Ӧ
CThostFtdcInstrumentMarginRateField * GroupMargindata = new CThostFtdcInstrumentMarginRateField;
void *GetCmdContent_ProductGroupMargin()
{
	if (MarginRatelist.size() > 0)
	{
		memset(GroupMargindata, 0, sizeof(CThostFtdcInstrumentMarginRateField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = ProductGroupMarginlist.begin()->ErrorID;
		////memcpy_s(errdata->ErrorMsg, sizeof(TThostFtdcErrorMsgType), ProductGroupMarginlist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		MarginRatelist.erase(MarginRatelist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return GroupMargindata;
	}
	else
	{
		return NULL;
	}
}



//�����ֶ�Ҫ�Լ����壬������¼״̬�Ķ���
//list <CThostFtdcRspUserLoginField> loginlist;
//list <CThostFtdcRspUserLoginField>::iterator login_Iter;

//list <CThostFtdcSettlementInfoConfirmField> connectlist;
//list <CThostFtdcSettlementInfoConfirmField>::iterator connect_Iter;

///�����ѯ��Լ��֤������Ӧ
//list <CThostFtdcInstrumentMarginRateField> MarginRatelist;
//list <CThostFtdcInstrumentMarginRateField>::iterator MarginRate_Iter;

///�����ѯ��Լ����������Ӧ
//list <CThostFtdcInstrumentCommissionRateField> CommissionRatelist;
//list <CThostFtdcInstrumentCommissionRateField>::iterator CommissionRate_Iter;



//�����ѯ��Լ����������Ӧ
CThostFtdcInstrumentCommissionRateField * CommissionRatedata = new CThostFtdcInstrumentCommissionRateField;
void *GetCmdContent_CommissionRate()
{
	if (CommissionRatelist.size() > 0)
	{
		memset(CommissionRatedata, 0, sizeof(CThostFtdcInstrumentCommissionRateField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = CommissionRatelist.begin()->ErrorID;
		//memcpy_s(errdata->ErrorMsg, sizeof(TThostFtdcErrorMsgType), CommissionRatelist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		CommissionRatelist.erase(CommissionRatelist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return CommissionRatedata;
	}
	else
	{
		return NULL;
	}
}



