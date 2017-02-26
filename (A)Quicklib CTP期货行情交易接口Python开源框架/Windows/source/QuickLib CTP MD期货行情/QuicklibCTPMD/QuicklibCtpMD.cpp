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
#include "stdafx.h"
//talib
#include "talib/include/ta_libc.h"
//talib
#include "GetHardSoftInfo.h"
#include "ThostTraderApi/ThostFtdcUserApiStruct.h"
#include "QLCTPMDInterface.h"
#include "MdSpi.h"
#include "IniFile.h"
#include "mapdef.h"
#include <hash_map>
#include <map>
#include <string>
#include <algorithm>
#include "iostream"
#include "QuicklibCtpMD.h"
#include <iostream> 
#include <windows.h>
using namespace std;
typedef map<string, PERIODTYPE> QS_Strategy_Map2;
QS_Strategy_Map2 * mapInstrument = new QS_Strategy_Map2;
extern CRITICAL_SECTION g_csdata;
list <cmdcontent> cmdlist;
list <cmdcontent>::iterator cmd_Iter;

list <TThostFtdcInstrumentIDTypeStruct> ticknamelist;
list <TThostFtdcInstrumentIDTypeStruct>::iterator tickname_Iter;

list <CThostFtdcRspInfoField> errorlist;
list <CThostFtdcRspInfoField>::iterator error_Iter;

list <CThostFtdcRspUserLoginField> loginlist;
list <CThostFtdcRspUserLoginField>::iterator login_Iter;

list <CThostFtdcRspUserLoginField> loginfailelist;
list <CThostFtdcRspUserLoginField>::iterator loginfaile_Iter;

list <CThostFtdcUserLogoutField> loginoutlist;
list <CThostFtdcUserLogoutField>::iterator loginout_Iter;

list <int> connectlist;
list <int>::iterator connect_Iter;

list <CThostFtdcSpecificInstrumentField> subMarketlist;
list <CThostFtdcSpecificInstrumentField>::iterator subMarket_Iter;

list <CThostFtdcSpecificInstrumentField> unsubMarketlist;
list <CThostFtdcSpecificInstrumentField>::iterator unsubMarket_Iter;

list <CThostFtdcForQuoteRspField> forquotelist;
list <CThostFtdcForQuoteRspField>::iterator forquote_Iter;

#include <process.h>
HANDLE hEvent[MAX_EVENTNUM] = { NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL };
//PYTHON
#include "include_Python/Python.h"

//����PYTHON�ļ��ĺ������"Hello World"����
void strategy1()
{

	Py_Initialize();	          //ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��
	PyObject * pModule = NULL;	  //��������
	PyObject * pFunc = NULL;	  //��������

	
	pModule = PyImport_ImportModule("Test001");	            //������Ҫ���õ�Python�ļ���
		pFunc = PyObject_GetAttrString(pModule, "HelloWorld");	//������Ҫ���õĺ�����
		PyEval_CallObject(pFunc, NULL);	                        //���ú���,NULL��ʾ����Ϊ��
	//Py_Finalize();	              //����Py_Finalize,�����Py_Initialize���Ӧ��.
	//���û����
	
}

//����Add����,������int�Ͳ���
void strategy2(int a,int b)
{
	Py_Initialize();

	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("Test001");	    //Test001:Python�ļ���
	pFunc = PyObject_GetAttrString(pModule, "add");	//Add:Python�ļ��еĺ�����
													//��������:
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
}

//�������ݵ�����Ϊ�ֵ�
void TestTransferDict()
{
	Py_Initialize();

	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("Test001");	    //Test001:Python�ļ���
	pFunc = PyObject_GetAttrString(pModule, "TestDict");	//Add:Python�ļ��еĺ�����
															//��������:
	PyObject *pArgs = PyTuple_New(1);
	PyObject *pDict = PyDict_New();   //�����ֵ����ͱ���
	PyDict_SetItemString(pDict, "Name", Py_BuildValue("s", "WangYao")); //���ֵ����ͱ������������
	PyDict_SetItemString(pDict, "Age", Py_BuildValue("i", 25));         //���ֵ����ͱ������������
	PyTuple_SetItem(pArgs, 0, pDict);//0---���  ���ֵ����ͱ�����ӵ�����Ԫ����
									 //����ֵ
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFunc, pArgs);	    //���ú���
													//������ֵ:
	int size = PyDict_Size(pReturn);
	cout << "�����ֵ�Ĵ�СΪ: " << size << endl;
	PyObject *pNewAge = PyDict_GetItemString(pReturn, "Age");
	int newAge;
	PyArg_Parse(pNewAge, "i", &newAge);
	cout << "True Age: " << newAge << endl;

	//Py_Finalize();
}

//������
void TestClass()
{
	Py_Initialize();

	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("Test001");	    //Test001:Python�ļ���
	pFunc = PyObject_GetAttrString(pModule, "TestDict");	//Add:Python�ļ��еĺ�����
															//��ȡPerson��
	PyObject *pClassPerson = PyObject_GetAttrString(pModule, "Person");
	//����Person���ʵ��
	PyObject *pInstancePerson = PyInstance_New(pClassPerson, NULL, NULL);
	//���÷���
	PyObject_CallMethod(pInstancePerson, "greet", "s", "Hello Kitty");   //s��ʾ���ݵ����ַ���,ֵΪ"Hello Kitty"

	//Py_Finalize();
}

//PYTHON����


//WMI��ѯ�������к�
#include <iostream>
#include <iomanip>
#include <atlstr.h>
#include <comutil.h>
#include <comdef.h>
using namespace std;
#pragma comment(lib,"comsuppw.lib")


#include <Wbemidl.h>

# pragma comment(lib, "wbemuuid.lib")
//WMI��ѯ�������к�

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>
#include <iosfwd>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
using std::vector;
using std::string;
using std::wstring;
using std::iterator;
#ifdef UNICODE 
typedef wstring tstring;
#define lsprintf_s swprintf_s 
#else
typedef string tstring;
#define lsprintf_s sprintf_s 
#endif

#include<Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#include<Winsock2.h>
#pragma comment(lib,"Ws2_32.lib")


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#include <atlbase.h>
#include <atlstr.h>
#include "ResetMacClass\public\cwindowsexception.h"
#include "ResetMacClass\dev\CSetupComDi.h"
#include "ResetMacClass\public\mydebug.h"
#include "ResetMacClass\public\CConvertString.h"
#include "ResetMacClass\CGetPath.h"
#include "ResetMacClass\CChangeMac.h"
using std::cout;
using std::wcout;
using std::endl;
using std::cin;
using std::wcin;
#ifdef UNICODE
#define tcout wcout
#define tcin wcin
#else
#define tcout cout
#define tcin cin
#endif

strategys * its;
Instructment * it;
bool FindId2(const char *Instrument, const char * str)
{
	//char *pdest1;// , *pdest2;
	//int  result1;// , result2;
	char * pdest1 = strstr((char*)Instrument, (char*)str);
	int  result1 = pdest1 - Instrument + 1;

	if (pdest1 != NULL)
	{		//printf("��%s����%s\n", InstrumentID_n[id],str );
		return true;
	}
	else
	{
		//printf("%s û����%s����\n", str, InstrumentID_n[id]);
		return false;
	}
}

int GetType(const char * InstrumentID)
{

	int TYPEID = -1;

	if (FindId2(InstrumentID, "ni"))
	{
		TYPEID = TYPE_NI;
	}
	else if (FindId2(InstrumentID, "zn"))
	{
		TYPEID = TYPE_ZN;
	}
	else if (FindId2(InstrumentID, "al"))
	{
		TYPEID = TYPE_AL;
	}
	else if (FindId2(InstrumentID, "cu"))
	{
		TYPEID = TYPE_CU;
	}
	else if (FindId2(InstrumentID, "au"))
	{
		TYPEID = TYPE_AU;
	}
	else if (FindId2(InstrumentID, "ag"))
	{
		TYPEID = TYPE_AG;
	}
	else if (FindId2(InstrumentID, "i"))
	{
		TYPEID = TYPE_I;
	}
	else if (FindId2(InstrumentID, "ru"))
	{
		TYPEID = TYPE_RU;
	}
	else if (FindId2(InstrumentID, "ta"))
	{
		TYPEID = TYPE_TA;
	}
	else if (FindId2(InstrumentID, "a"))
	{
		TYPEID = TYPE_A;
	}
	else if (FindId2(InstrumentID, "m"))
	{
		TYPEID = TYPE_M;
	}
	else if (FindId2(InstrumentID, "y"))
	{
		TYPEID = TYPE_Y;
	}
	else if (FindId2(InstrumentID, "p"))
	{
		TYPEID = TYPE_P;
	}
	else if (FindId2(InstrumentID, "rb"))
	{
		TYPEID = TYPE_RB;
	}
	else if (FindId2(InstrumentID, "ma"))
	{
		TYPEID = TYPE_MA;
	}
	else if (FindId2(InstrumentID, "pp"))
	{
		TYPEID = TYPE_PP;
	}
	else if (FindId2(InstrumentID, "cs"))
	{
		TYPEID = TYPE_CS;
	}
	else if (FindId2(InstrumentID, "jd"))
	{
		TYPEID = TYPE_JD;
	}
	else if (FindId2(InstrumentID, "bu"))
	{
		TYPEID = TYPE_BU;
	}
	else if (FindId2(InstrumentID, "fg"))
	{
		TYPEID = TYPE_FG;
	}
	else if (FindId2(InstrumentID, "l"))
	{
		TYPEID = TYPE_L;
	}
	else if (FindId2(InstrumentID, "v"))
	{
		TYPEID = TYPE_V;
	}
	else if (FindId2(InstrumentID, "sr"))
	{
		TYPEID = TYPE_SR;
	}
	else if (FindId2(InstrumentID, "rm"))
	{
		TYPEID = TYPE_RM;
	}
	else if (FindId2(InstrumentID, "cf"))
	{
		TYPEID = TYPE_CF;
	}
	else if (FindId2(InstrumentID, "c"))
	{
		TYPEID = TYPE_C;
	}
	else if (FindId2(InstrumentID, "wh"))
	{
		TYPEID = TYPE_WH;
	}
	else if (FindId2(InstrumentID, "sm"))
	{
		TYPEID = TYPE_SM;
	}
	else if (FindId2(InstrumentID, "sf"))
	{
		TYPEID = TYPE_SF;
	}
	else if (FindId2(InstrumentID, "ic"))
	{
		TYPEID = TYPE_IC;
	}
	else if (FindId2(InstrumentID, "if"))
	{
		TYPEID = TYPE_IF;
	}
	else if (FindId2(InstrumentID, "ih"))
	{
		TYPEID = TYPE_IH;
	}
	else if (FindId2(InstrumentID, "t"))
	{
		TYPEID = TYPE_T;
	}
	else if (FindId2(InstrumentID, "tf"))
	{
		TYPEID = TYPE_TF;
	}

	else if (FindId2(InstrumentID, "new1"))
	{
		TYPEID = TYPE_NEW1;
	}
	else if (FindId2(InstrumentID, "new2"))
	{
		TYPEID = TYPE_NEW2;
	}
	else if (FindId2(InstrumentID, "new3"))
	{
		TYPEID = TYPE_NEW3;
	}
	else if (FindId2(InstrumentID, "new4"))
	{
		TYPEID = TYPE_NEW4;
	}
	else if (FindId2(InstrumentID, "new5"))
	{
		TYPEID = TYPE_NEW5;
	}
	else if (FindId2(InstrumentID, "new6"))
	{
		TYPEID = TYPE_NEW6;
	}
	else if (FindId2(InstrumentID, "new7"))
	{
		TYPEID = TYPE_NEW7;
	}
	else if (FindId2(InstrumentID, "new8"))
	{
		TYPEID = TYPE_NEW8;
	}
	else if (FindId2(InstrumentID, "new9"))
	{
		TYPEID = TYPE_NEW9;
	}
	else if (FindId2(InstrumentID, "new10"))
	{
		TYPEID = TYPE_NEW10;
	}

	else if (FindId2(InstrumentID, "new11"))
	{
		TYPEID = TYPE_NEW11;
	}
	else if (FindId2(InstrumentID, "new12"))
	{
		TYPEID = TYPE_NEW12;
	}
	else if (FindId2(InstrumentID, "new13"))
	{
		TYPEID = TYPE_NEW13;
	}
	else if (FindId2(InstrumentID, "new14"))
	{
		TYPEID = TYPE_NEW14;
	}
	else if (FindId2(InstrumentID, "new15"))
	{
		TYPEID = TYPE_NEW15;
	}
	else if (FindId2(InstrumentID, "new16"))
	{
		TYPEID = TYPE_NEW16;
	}
	else if (FindId2(InstrumentID, "new17"))
	{
		TYPEID = TYPE_NEW17;
	}
	else if (FindId2(InstrumentID, "new18"))
	{
		TYPEID = TYPE_NEW18;
	}
	else if (FindId2(InstrumentID, "new19"))
	{
		TYPEID = TYPE_NEW19;
	}
	else if (FindId2(InstrumentID, "new20"))
	{
		TYPEID = TYPE_NEW20;
	}

	return TYPEID;

}




typedef map<string, InstrumentInfo> QS_Strategy_Map;
typedef hash_map<string, GuestOnlineHash> QS_Data_Map;

QS_Data_Map     mapData;
QS_Strategy_Map mapStrategy;




bool ReadInstrument()
{


	printf("read Instrument.ini\n");
	CIniFile	cfgfile("./Instrument.ini");
	int num = cfgfile.ReadInteger("number:", "num", 10);



	//char qsid_id[100] = { 0 };
	char instr[100] = { 0 };
	it = new Instructment[TYPE_ARR_LEN];
	memset(it, 0, sizeof(Instructment)*TYPE_ARR_LEN);

 
	for (int j = 1; j <= num; j++)
	{

		//map


		memset(&instr, 0, sizeof(instr));  //�˴�����
											   //	char list_num[40]={0};
											   //	_snprintf(list_num, sizeof(list_num), "%d",j);
											   //	MessageBox(NULL,list_num,"j",MB_OK); 
		//_snprintf(qsid_id, sizeof(qsid_id), "qsid_%d", j);
		_snprintf_s(instr, sizeof(instr), sizeof(instr), "instrument%d", j);

		//   MessageBox(NULL,qsid_id,"qsid_id",MB_OK); 
		//int qsid_zx = ini.ReadInteger(qsid_id, "qsid_zx", 0);
		//int qsid_jy = ini.ReadInteger(qsid_id, "qsid_jy", 0)

	 //	printf("A1\n");
		// cfgfile.ReadString("��ԼƷ��", instr, "", it[i].instructment, dim(it[i].instructment));



		char temp1[31] = { 0 };
		char temp2[31] = { 0 };
		char temp3[31] = { 0 };
		cfgfile.ReadString(instr, "instrument", "", temp1, dim(temp1));

		if (0)
		{
			cfgfile.ReadString(instr, "strategy", "", temp2, dim(temp2));

			cfgfile.ReadString(instr, "positionrate", "", temp3, dim(temp3));
			InstrumentInfo iif;

			iif.tradestate = true;
			if (1)
			{
				////////////////////////////////////��ȡ�ֶ�strategy

				//1.�Լ�ʵ��,�̰߳�ȫ,֧���ַ�����Ϊ�ָ���.ȱ����ܾ��Ǵ�������.
				string str = temp2;// "google||twitter||facebook||microsoft||apple||ibmwdg";
				//printf("*************%s\n", temp2);
				//������һ���ַ�����, �����","
				//std::string temp;
				//temp = str.substr(str.length() - 1, 1);
				if (str.substr(str.length() - 1, 1) != ",")
				{
					str = str + ",";
				}
				const char* delim = ",";
				const int len = strlen(delim);
				size_t index = 0;
				size_t pos = str.find(delim, index);

				int id = -1;

				while (pos != string::npos)
				{
					id++;
					string ss = str.substr(index, pos - index);
					//cout << ss << endl;
					//cout << temp1 <<"["<< id + 1 << "] ������ID=" << ss << "�Ĳ���,�����ļ�strategy" << ss<<".py��������strategy"<<ss<<".exe���б�д����"<<endl;
					cout << temp1 << "[" << id + 1 << "] ������" << ss.c_str() << "�Ĳ���,�����ļ�" << ss.c_str() << "�б�д����" << endl;
					iif.strategyfile[id] = ss;// .c_str();// atoi(ss.c_str());//id
					index = pos + len;
					pos = str.find(delim, index);
				}


				/*
				//����ˡ��������˶ο���ʡ��
				//cout << "is last?" << " index:" << index << " str.length():" << str.length() << endl;
				if ((index + 1) < str.length())
				{
					id++;
					string ss = str.substr(index, str.length() - index);
					cout <<"["<<id<<"]" <<temp1<< "����" <<ss << endl;
					iif.strategy[id] = atoi(ss.c_str());//id

				}
				*/
				////////////////////////////////////��ȡ�ֶ�strategy
			}
			int id = -1;
			//printf("A1\n");
			if (1)
			{
				////////////////////////////////////��ȡ�ֶ�position
						//1.�Լ�ʵ��,�̰߳�ȫ,֧���ַ�����Ϊ�ָ���.ȱ����ܾ��Ǵ�������.
				string positionratestr = temp3;// "google||twitter||facebook||microsoft||apple||ibmwdg";
				//printf("*************%s\n", positionratestr.c_str());
				//printf("B2\n");
				//������һ���ַ�����, �����","
				//std::string temp;
				//temp = str.substr(str.length() - 1, 1);
				if (positionratestr.substr(positionratestr.length() - 1, 1) != ",")
				{
					//printf("B3\n");
					positionratestr = positionratestr + ",";
					//printf("B4\n");
				}
				//printf("A2\n");
				const char* delim = ",";
				const int len = strlen(delim);
				size_t index = 0;
				size_t pos = positionratestr.find(delim, index);
				//printf("A3\n");

				while (pos != string::npos)
				{
					id++;
					string ss = positionratestr.substr(index, pos - index);
					//cout << ss << endl;
					cout << temp1 << "[" << id + 1 << "] ��λ=" << ss.c_str() << "%" << endl;
					iif.position[id] = atoi(ss.c_str());//id
					index = pos + len;
					pos = positionratestr.find(delim, index);


				}
				//printf("A4\n");


				////////////////////////////////////��ȡ�ֶ�position

			}


			iif.strategyfilenum = id + 1;
			//printf("A5\n");
			if (0)
			{//��ʱ����
				printf("��[%d]������\n", iif.strategyfilenum);
			}

			pair<string, InstrumentInfo>value(temp1, iif);
			mapStrategy.insert(value);

		}


		//printf("A5\n");
		//map

		//int TYPEIDXB = j;// GetType(temp) - 100000;
	   // printf("A2\n");
		//printf("%s", temp1);
		//strncpy_s(its[TYPEIDXB].instructment, sizeof(its[TYPEIDXB].instructment), temp1, strlen(temp1));
		//printf("A3\n");

		//memset(its[TYPEIDXB].instructment,0,20);
		//_snprintf_s(its[TYPEIDXB].instructment,20,19, temp1, strlen(temp1));
		//printf("A4\n");
		if (strcmp(temp1, "") != 0)
		{		
			Subscribe(temp1);
	    }
		//printf("����[%s]\n", temp1);
		//strncpy_s(its[TYPEIDXB].instructment, sizeof(its[TYPEIDXB].instructment), temp1, strlen(temp1));
		//printf("A7\n");
		//its[TYPEIDXB].strategy[0] = 1;
		//Sleep(5000);
		//printf("A8\n");
		//printf("***************\n");
		/*

		//printf("A2\n");
		char instrument_MD[30] = { 0 };
		char instrument_TRADE[30] = { 0 };
		_snprintf_s(instrument_MD, sizeof(instrument_MD), sizeof(instrument_MD), "%s����", it[TYPEIDXB].instructment);
		_snprintf_s(instrument_TRADE, sizeof(instrument_TRADE), sizeof(instrument_TRADE), "%s����", it[TYPEIDXB].instructment);



		//	printf("%s\n", instrument_MD);

		//cfgfile.ReadString("ag", "begin1", NULL, begintime1, dim(begintime1));
		//cfgfile.ReadString("ag", "end1", NULL, endtime1, dim(endtime1));
		cfgfile.ReadString(instrument_MD, "begin1", "", begintime1, dim(begintime1));
		//printf("A30\n");
		cfgfile.ReadString(instrument_MD, "end1", "", endtime1, dim(endtime1));


		its[TYPEIDXB].MD_begin1 = cfgfile.ReadInt(instrument_MD, "begin1", 0);
		its[TYPEIDXB].MD_end1 = cfgfile.ReadInt(instrument_MD, "end1", 0);


		*/

	}


	//printf("A9\n");


	//cfgfile.ReadString();
	//cfgfile.ReadString("���", "��ǰʹ�ò��", "", dllfile, dim(dllfile));
	//cfgfile.ReadString("���", "��ǰʹ�ò��", "", dllfile, dim(dllfile));
	//cfgfile.ReadString("����", "title", "Ǯ������", titlefile, dim(titlefile));
	//	::SetWindowText(m_hWnd, titlefile);
	return true;
}




void ReadTradeTime()
{

	//char	filename[1024];
	//sprintf(filename, "%s\\qlserver.ini", m_path);
//	CProcRes*	m_ProcRes;
	//m_ProcRes->SetCfgFile("qlserver.ini");

//	char	dllfile[512];
	//char	titlefile[512];
	CIniFile	cfgfile("./TradeTime.ini");
	//char TCP[256];
	//CHAR IPX[256];
	//cfgfile.ReadString("��������", "TCP�˿�", "24929", TCP, dim(TCP));
	//cfgfile.ReadString("��������", "SPX�˿�", "", IPX, dim(IPX));

	//long m_CheckSelectStatusTime = cfgfile.ReadInteger("��������", "CheckSelectStatusTime", 100);

	int showstate = cfgfile.ReadInteger("ʱ��������ļ���ȡ��ʾ", "�Ƿ���ʾ��ȡ����", 1);

    


	int num=cfgfile.ReadInteger("��Լ����", "num",10);
	if (showstate == 1)
	{
		printf("��ȡ��Լ��������[%d]\n", num);
	}
	//it =new Instructment[num];
	//memset(it,0, sizeof(Instructment)*num);


	it = new Instructment[TYPE_ARR_LEN];
	memset(it, 0, sizeof(Instructment)*TYPE_ARR_LEN);
	//char * instr = "��Լ";
	//strncpy_s(instr,sizeof(instr),"");
	//strcat_s(instr, sizeof(inser), "%d", i);
	//printf("A1\n");
	for (int j = 0; j < num; j++)
	{
	 char instr[16] = {0};
	 if (showstate == 1)
	 {
		 _snprintf_s(instr, sizeof(instr), sizeof(instr), "��Լ%d", j + 1);
	 }
	// cfgfile.ReadString("��ԼƷ��", instr, "", it[i].instructment, dim(it[i].instructment));
	 char temp[20] = {0};
	 cfgfile.ReadString("��ԼƷ��", instr, "", temp, dim(temp));

	 int TYPEIDXB = j;// GetType(temp) - 100000;
	 strncpy_s(it[TYPEIDXB].instructment,sizeof(it[TYPEIDXB].instructment),temp,strlen(temp));
	 

	 //printf("A2\n");
	 char instrument_MD[30] = { 0 };
	 char instrument_TRADE[30] = { 0 };
	 _snprintf_s(instrument_MD, sizeof(instrument_MD), sizeof(instrument_MD), "%s����", it[TYPEIDXB].instructment);
	 _snprintf_s(instrument_TRADE, sizeof(instrument_TRADE), sizeof(instrument_TRADE), "%s����", it[TYPEIDXB].instructment);
	 char	begintime1[40] = { 0 };
	 char	endtime1[40] = { 0 };
	 char	begintime2[40] = { 0 };
	 char	endtime2[40] = { 0 };
	 char	begintime3[40] = { 0 };
	 char	endtime3[40] = { 0 };
	 char	begintime4[40] = { 0 };
	 char	endtime4[40] = { 0 };


	 //if (showstate == 1)
	// {
		// printf("%s\n", instrument_MD);
	// }
	 //cfgfile.ReadString("ag", "begin1", NULL, begintime1, dim(begintime1));
	 //cfgfile.ReadString("ag", "end1", NULL, endtime1, dim(endtime1));
	 cfgfile.ReadString(instrument_MD, "begin1", "", begintime1, dim(begintime1));
	 //printf("A30\n");
	 cfgfile.ReadString(instrument_MD, "end1", "", endtime1, dim(endtime1));
	 //printf("A31\n");
	 cfgfile.ReadString(instrument_MD, "begin2", "", begintime2, dim(begintime2));
	 cfgfile.ReadString(instrument_MD, "end2", "", endtime2, dim(endtime2));
	 //printf("A32\n");
	 cfgfile.ReadString(instrument_MD, "begin3", "", begintime3, dim(begintime3));
	 cfgfile.ReadString(instrument_MD, "end3", "", endtime3, dim(endtime3));
	 //printf("A33\n");
	 cfgfile.ReadString(instrument_MD, "begin4", "", begintime4, dim(begintime4));
	 cfgfile.ReadString(instrument_MD, "end4", "", endtime4, dim(endtime4));

	 //printf("A4\n");
	 
	 it[TYPEIDXB].MD_begin1 = cfgfile.ReadInt(instrument_MD, "begin1", 0);
	 it[TYPEIDXB].MD_end1 = cfgfile.ReadInt(instrument_MD, "end1", 0);

	 it[TYPEIDXB].MD_begin2 = cfgfile.ReadInt(instrument_MD, "begin2", 0);
	 it[TYPEIDXB].MD_end2 = cfgfile.ReadInt(instrument_MD, "end2", 0);

	 it[TYPEIDXB].MD_begin3 = cfgfile.ReadInt(instrument_MD, "begin3", 0);
	 it[TYPEIDXB].MD_end3 = cfgfile.ReadInt(instrument_MD, "end3", 0);

	 it[TYPEIDXB].MD_begin4 = cfgfile.ReadInt(instrument_MD, "begin4", 0);
	 it[TYPEIDXB].MD_end4 = cfgfile.ReadInt(instrument_MD, "end4", 0);

	 

	 if (showstate == 1)
	 { //����
		 printf("--------%s--------\n", instrument_MD);
		 //it[TYPEIDXB].instructment
		 printf("[%s ~ %s]\n",  begintime1, endtime1);
		 printf("[%s ~ %s]\n",  begintime2, endtime2);
		 printf("[%s ~ %s]\n",  begintime3, endtime3);
		 printf("[%s ~ %s]\n",  begintime4, endtime4);
	 }

	 memset(begintime1, 0, sizeof(begintime1));
	 memset(begintime2, 0, sizeof(begintime2));
	 memset(begintime3, 0, sizeof(begintime3));
	 memset(begintime4, 0, sizeof(begintime4));
	 memset(endtime1, 0, sizeof(endtime1));
	 memset(endtime2, 0, sizeof(endtime2));
	 memset(endtime3, 0, sizeof(endtime3));
	 memset(endtime4, 0, sizeof(endtime4));

	// printf("A6\n");

	 cfgfile.ReadString(instrument_TRADE, "begin1", "", begintime1, dim(begintime1));
	 cfgfile.ReadString(instrument_TRADE, "end1", "", endtime1, dim(endtime1));

	 cfgfile.ReadString(instrument_TRADE, "begin2", "", begintime2, dim(begintime2));
	 cfgfile.ReadString(instrument_TRADE, "end2", "", endtime2, dim(endtime2));

	 cfgfile.ReadString(instrument_TRADE, "begin3", "", begintime3, dim(begintime3));
	 cfgfile.ReadString(instrument_TRADE, "end3", "", endtime3, dim(endtime3));

	 cfgfile.ReadString(instrument_TRADE, "begin4", "", begintime4, dim(begintime4));
	 cfgfile.ReadString(instrument_TRADE, "end4", "", endtime4, dim(endtime4));


	 it[TYPEIDXB].TD_begin1 = cfgfile.ReadInt(instrument_TRADE, "begin1", 0);
	 it[TYPEIDXB].TD_end1 = cfgfile.ReadInt(instrument_TRADE, "end1", 0);

	 it[TYPEIDXB].TD_begin2 = cfgfile.ReadInt(instrument_TRADE, "begin2", 0);
	 it[TYPEIDXB].TD_end2 = cfgfile.ReadInt(instrument_TRADE, "end2", 0);

	 it[TYPEIDXB].TD_begin3 = cfgfile.ReadInt(instrument_TRADE, "begin3", 0);
	 it[TYPEIDXB].TD_end3 = cfgfile.ReadInt(instrument_TRADE, "end3", 0);

	 it[TYPEIDXB].TD_begin4 = cfgfile.ReadInt(instrument_TRADE, "begin4", 0);
	 it[TYPEIDXB].TD_end4 = cfgfile.ReadInt(instrument_TRADE, "end4", 0);


	 if (showstate == 1)
	 {//����
	   printf("--------%s--------\n", instrument_TRADE);
	   printf("[%s ~ %s]\n",  begintime1, endtime1);
	   printf("[%s ~ %s]\n",  begintime2, endtime2);
	   printf("[%s ~ %s]\n",  begintime3, endtime3);
	   printf("[%s ~ %s]\n",  begintime4, endtime4);
	 }

	 
	}
	if (showstate == 1)
	{
		printf("**********TradeTime.ini�����ļ���ȡ����************\n");
	}

	//cfgfile.ReadString();
	//cfgfile.ReadString("���", "��ǰʹ�ò��", "", dllfile, dim(dllfile));
	//cfgfile.ReadString("���", "��ǰʹ�ò��", "", dllfile, dim(dllfile));
	//cfgfile.ReadString("����", "title", "Ǯ������", titlefile, dim(titlefile));
//	::SetWindowText(m_hWnd, titlefile);

}




 
//TradeTime
struct TradeTimesInterval
{
	double begin1;
	double end1;
	double begin2;
	double end2;
	double begin3;
	double end3;
};
TradeTimesInterval TradeTime[100];
 



std::string gFrontAddr[3];
std::string gBrokerID;
std::string gUserID;
std::string gPassword;
std::string sn;

char* ppInstrumentID[200] = {0};	

CThostFtdcDepthMarketDataField *depthdata[200] = {0};
int size = sizeof(CThostFtdcDepthMarketDataField);
int amount = 0;
std::map<std::string, int> gMarket;

std::string gListFile("List.ini");
std::string gMDAccount("QuickLibMD.ini");

std::string gLic("Lic.ini");

std::string gTradeTime("TradeTime.ini");

int gStatus = 0;
CMdSpi gMDSpi;

///////////////////////////////mac��4�ַ���ȡMAC
#include <iostream>
using namespace std;
//��������������С
const long MAX_COMMAND_SIZE = 10000;
//��ȡMAC������
//TCHAR szFetCmd9[] = _T("ipconfig /all");
//����MAC��ַ��ǰ����Ϣ
//const string str4Search = "Physical Address. . . . . . . . . : ";
//�������з�ʽ��ȡ����MAC��ַ
TCHAR szFetCmd9[] = "getmac";
//����MAC��ַ��ǰ����Ϣ
const string str4Search = ("-");
//�������з�ʽ��ȡ����MAC��ַ
////////////////////////////////mac��4�ַ���ȡMAC

//mac��4�ַ���ȡMAC

////////////////////////////////////////////////////////////////////////////
// �������� GetMacByCmd(char *lpszMac)
// ������
//      ���룺 void
//      ����� lpszMac,���ص�MAC��ַ��
// ����ֵ��
//      TRUE:  ���MAC��ַ��
//      FALSE: ��ȡMAC��ַʧ�ܡ�
// ���̣�
//      1. ����һ�������ܵ���
//      2. ����һ��IPCONFIG �Ľ��̣���������ض��򵽹ܵ���
//      3. �ӹܵ���ȡ�����з��ص�������Ϣ���뻺����lpszBuffer��
//      4. �ӻ�����lpszBuffer�л�ó�ȡ��MAC����
//
//  ��ʾ�����Է�����ɴ˳�����IP��ַ��������Ϣ��
//        ���������Ŀ���ͨ���������ʽ�õ�����Ϣֻ��ı�strFetCmd �� 
//        str4Search�����ݼ��ɡ�
///////////////////////////////////////////////////////////////////////////
BOOL GetMacByCmd(TCHAR *lpszMac)
{
	//��ʼ������MAC��ַ������
	memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret;
	SECURITY_ATTRIBUTES sa;
	HANDLE hReadPipe, hWritePipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//�����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		return FALSE;
	}
	//���������д�����Ϣ
	STARTUPINFO si;
	//���ؽ�����Ϣ
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //���������д���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//������ȡ�����н���
	bret = CreateProcess(NULL, szFetCmd9, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	char szBuffer[MAX_COMMAND_SIZE + 1]; //�������������������
	string strBuffer;
	if (bret)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		unsigned long count;

		//CloseHandle(hWritePipe);
		memset(szBuffer, 0x00, sizeof(szBuffer));
		bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
		if (!bret)
		{
			//�ر����еľ��
			// AfxMessageBox(_T("B"));
			CloseHandle(hWritePipe);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(hReadPipe);
			return FALSE;
		}
		else
		{
			strBuffer = szBuffer;
			long ipos;
			ipos = strBuffer.find(str4Search);
			//��ȡMAC��ַ��
			strBuffer = strBuffer.substr(ipos + str4Search.length() - 3);
			//ipos = strBuffer.find("\n");
			//strBuffer = strBuffer.substr(0, ipos);
			strBuffer = strBuffer.substr(0, 17);
		}

	}
	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());
	//ȥ���м�ġ�00-50-EB-0F-27-82���м��'-'�õ�0050EB0F2782
	int j = 0;
	for (unsigned int i = 0; i<strlen(szBuffer); i++)
	{
		if (szBuffer[i] != '-')
		{
			lpszMac[j] = szBuffer[i];
			j++;
		}
	}
	//�ر����еľ��
	// AfxMessageBox(_T("C"));
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hReadPipe);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL GetMacByCmd2(TCHAR *lpszMac)
{
	//��ʼ������MAC��ַ������
	memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret;
	SECURITY_ATTRIBUTES sa;
	HANDLE hReadPipe, hWritePipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//�����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		return FALSE;
	}
	//���������д�����Ϣ
	STARTUPINFO si;
	//���ؽ�����Ϣ
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //���������д���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//������ȡ�����н���
	bret = CreateProcess(NULL, szFetCmd9, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	char szBuffer[MAX_COMMAND_SIZE + 1]; //�������������������
	string strBuffer;
	if (bret)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		unsigned long count;

		//AfxMessageBox(_T("A"));

		//CloseHandle(hWritePipe);
		memset(szBuffer, 0x00, sizeof(szBuffer));
		bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
		if (!bret)
		{
			//�ر����еľ��
			// AfxMessageBox(_T("B"));
			CloseHandle(hWritePipe);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(hReadPipe);
			return FALSE;
		}
		else
		{
			strBuffer = szBuffer;
			long ipos;
			ipos = strBuffer.find(str4Search);
			//��ȡMAC��ַ��
			//strBuffer = strBuffer.substr(ipos+str4Search.length());
			//ipos = strBuffer.find("\n");
			//strBuffer = strBuffer.substr(0, ipos);
			strBuffer = strBuffer.substr(ipos + str4Search.length() - 3);
			strBuffer = strBuffer.substr(0, 17);
		}

	}
	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());
	//ȥ���м�ġ�00-50-EB-0F-27-82���м��'-'�õ�0050EB0F2782
	int j = 0;
	for (unsigned int i = 0; i<strlen(szBuffer); i++)
	{
		if (szBuffer[i] != '-')
		{
			lpszMac[j] = szBuffer[i];
			j++;
		}
	}
	//�ر����еľ��
	// AfxMessageBox(_T("C"));
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hReadPipe);
	return TRUE;
}
////////////////////////////////////////////////////////////////////////
BOOL GetMacByCmd3(TCHAR *lpszMac)
{
	//��ʼ������MAC��ַ������
	memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret;
	SECURITY_ATTRIBUTES sa;
	HANDLE hReadPipe, hWritePipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//�����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		return FALSE;
	}
	//���������д�����Ϣ
	STARTUPINFO si;
	//���ؽ�����Ϣ
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //���������д���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//������ȡ�����н���
	bret = CreateProcess(NULL, szFetCmd9, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	char szBuffer[MAX_COMMAND_SIZE + 1]; //�������������������
	string strBuffer;
	if (bret)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		unsigned long count;

		//AfxMessageBox(_T("A"));

		//CloseHandle(hWritePipe);
		memset(szBuffer, 0x00, sizeof(szBuffer));
		bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
		if (!bret)
		{
			//�ر����еľ��
			// AfxMessageBox(_T("B"));
			CloseHandle(hWritePipe);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(hReadPipe);
			return FALSE;
		}
		else
		{
			strBuffer = szBuffer;
			long ipos;
			ipos = strBuffer.find(str4Search);
			//��ȡMAC��ַ��
			//strBuffer = strBuffer.substr(ipos+str4Search.length());
			//ipos = strBuffer.find("\n");
			//strBuffer = strBuffer.substr(0, ipos);
			strBuffer = strBuffer.substr(ipos + str4Search.length() - 3);
			strBuffer = strBuffer.substr(0, 17);
		}

	}
	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());
	//ȥ���м�ġ�00-50-EB-0F-27-82���м��'-'�õ�0050EB0F2782
	int j = 0;
	for (unsigned int i = 0; i<strlen(szBuffer); i++)
	{
		if (szBuffer[i] != '-')
		{
			lpszMac[j] = szBuffer[i];
			j++;
		}
	}
	//�ر����еľ��
	// AfxMessageBox(_T("C"));
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hReadPipe);
	return TRUE;
}
/////////////////////////////////////////////////////////////////////
BOOL GetMacByCmd4(TCHAR *lpszMac)
{
	//��ʼ������MAC��ַ������
	memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret;
	SECURITY_ATTRIBUTES sa;
	HANDLE hReadPipe, hWritePipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//�����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		return FALSE;
	}
	//���������д�����Ϣ
	STARTUPINFO si;
	//���ؽ�����Ϣ
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //���������д���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//������ȡ�����н���
	bret = CreateProcess(NULL, szFetCmd9, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	char szBuffer[MAX_COMMAND_SIZE + 1]; //�������������������
	string strBuffer;
	if (bret)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		unsigned long count;

		//AfxMessageBox(_T("A"));

		//CloseHandle(hWritePipe);
		memset(szBuffer, 0x00, sizeof(szBuffer));
		bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
		if (!bret)
		{
			//�ر����еľ��
			// AfxMessageBox(_T("B"));
			CloseHandle(hWritePipe);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(hReadPipe);
			return FALSE;
		}
		else
		{
			strBuffer = szBuffer;
			long ipos;
			ipos = strBuffer.find(str4Search);
			//��ȡMAC��ַ��
			//strBuffer = strBuffer.substr(ipos+str4Search.length());
			//ipos = strBuffer.find("\n");
			//strBuffer = strBuffer.substr(0, ipos);
			strBuffer = strBuffer.substr(ipos + str4Search.length() - 3);
			strBuffer = strBuffer.substr(0, 17);
		}

	}
	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());
	//ȥ���м�ġ�00-50-EB-0F-27-82���м��'-'�õ�0050EB0F2782
	int j = 0;
	for (unsigned int i = 0; i<strlen(szBuffer); i++)
	{
		if (szBuffer[i] != '-')
		{
			lpszMac[j] = szBuffer[i];
			j++;
		}
	}
	//�ر����еľ��
	// AfxMessageBox(_T("C"));
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hReadPipe);
	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////���к�ɾ��������
#include <ShellAPI.h> 
#include <shlobj.h>   
static void KillSelf()
//void   CAIOApp::SelfDelete() 
{
	//CTime   currTime; 
	//currTime		 =  CTime::GetCurrentTime();
	//int year		 =	currTime.GetYear();
	//int month	 =	currTime.GetMonth();
	//int day		 =	currTime.GetDay();
	// if((year>=2010)&&(month>=3))
	//{
	SHELLEXECUTEINFO sei;
	TCHAR szModule[MAX_PATH], szComspec[MAX_PATH], szParams[MAX_PATH];
	//��ȡ�ļ�·����  
	while ((GetModuleFileName(0, szModule, MAX_PATH) != 0) && (GetShortPathName(szModule, szModule, MAX_PATH) != 0) && (GetEnvironmentVariable((_T("COMSPEC")), szComspec, MAX_PATH) != 0))
	{  //���������в�����  
		lstrcpy(szParams,  (_T("/c del ")));
		lstrcat(szParams, szModule);
		lstrcat(szParams,  (_T(" > nul")));

		//��ʼ��SHELLEXECUTEINFO�ṹ��Ա  
		sei.cbSize = sizeof(sei); //�������ʹ�С��  
								  //����ڽ��̾����ShellExecuteEx����ִ��ʱ���á�  
		sei.hwnd = 0;
		sei.lpVerb =  (_T("Open"));         //ִ�ж���Ϊ����ִ�С���  
		sei.lpFile = szComspec;      //ִ�г����ļ�ȫ·�����ơ�  
		sei.lpParameters = szParams; //ִ�в�����  
		sei.lpDirectory = 0;
		//��ʾ��ʽ���˴�ʹ�����ط�ʽ��ֹ��������ڽ��档  
		sei.nShow = SW_HIDE;
		//����ΪSellExecuteEx��������������˳���  
		sei.fMask = SEE_MASK_NOCLOSEPROCESS;
		//����ִ������ڽ��̡�  
		while (ShellExecuteEx(&sei))
		{  //���������н��̵�ִ�м���Ϊ����ִ��,��ʹ���������㹻��ʱ����ڴ����˳���    
			SetPriorityClass(sei.hProcess, IDLE_PRIORITY_CLASS);
			//���ñ�������̵�ִ�м���Ϊʵʱִ�У��Ȿ�������ϻ�ȡCPUִ��Ȩ�������˳���    
			SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
			//֪ͨWindows��Դ��������������ļ��Ѿ���ɾ����  
			// while(1)
			//{
			SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szModule, 0);
			//}
			break;
			//ִ���˳�����  
			//EndDialog(0);  
		}
		break;
	}
	// }// end if((year>=2010)&&(month>=3))
	PostQuitMessage(1);
}
////////////////////////////////////////���к�ɾ��������

//CrcDllValueb.Format(_T("%d"),100*a+10*b+c+d);
//static  CString  CrcDllValue2=VMProtectDecryptStringW(_T("25A6A9C065EB00A6D5A66B228DF298AEA64B5B5EAC770E5C85E07EF0394B4D3C3706C6B9"));
//static  CString  CrcDllValue2=VMProtectDecryptStringW(_T("25A6A9C065EB00A6D5A66B228DF"));

//static  CString  CrcDllValue2b=VMProtectDecryptStringW(_T("AEA64B5B5EAC770E5C85E07EF0394B4D3C3706C6B9"));

////////////////////////////////////////���к�ɾ��������while�������
static void KillSelf2()
//void   CAIOApp::SelfDelete() 
{
	//CTime   currTime; 
	//currTime		 =  CTime::GetCurrentTime();
	//int year		 =	currTime.GetYear();
	//int month	 =	currTime.GetMonth();
	//int day		 =	currTime.GetDay();
	// if((year>=2010)&&(month>=3))
	//{
	SHELLEXECUTEINFO sei;
	TCHAR szModule[MAX_PATH], szComspec[MAX_PATH], szParams[MAX_PATH];
	//��ȡ�ļ�·����  
	while ((GetModuleFileName(0, szModule, MAX_PATH) != 0) && (GetShortPathName(szModule, szModule, MAX_PATH) != 0) && (GetEnvironmentVariable((_T("COMSPEC")), szComspec, MAX_PATH) != 0))
	{  //���������в�����  
		lstrcpy(szParams, (_T("/c del ")));
		lstrcat(szParams, szModule);
		lstrcat(szParams, (_T(" > nul")));

		//��ʼ��SHELLEXECUTEINFO�ṹ��Ա  
		sei.cbSize = sizeof(sei); //�������ʹ�С��  
								  //����ڽ��̾����ShellExecuteEx����ִ��ʱ���á�  
		sei.hwnd = 0;
		sei.lpVerb = (_T("Open"));         //ִ�ж���Ϊ����ִ�С���  
		sei.lpFile = szComspec;      //ִ�г����ļ�ȫ·�����ơ�  
		sei.lpParameters = szParams; //ִ�в�����  
		sei.lpDirectory = 0;
		//��ʾ��ʽ���˴�ʹ�����ط�ʽ��ֹ��������ڽ��档  
		sei.nShow = SW_HIDE;
		//����ΪSellExecuteEx��������������˳���  
		sei.fMask = SEE_MASK_NOCLOSEPROCESS;
		//����ִ������ڽ��̡�  
		while (ShellExecuteEx(&sei))
		{  //���������н��̵�ִ�м���Ϊ����ִ��,��ʹ���������㹻��ʱ����ڴ����˳���    
			SetPriorityClass(sei.hProcess, IDLE_PRIORITY_CLASS);
			//���ñ�������̵�ִ�м���Ϊʵʱִ�У��Ȿ�������ϻ�ȡCPUִ��Ȩ�������˳���    
			SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
			//֪ͨWindows��Դ��������������ļ��Ѿ���ɾ����  
			while (1)
			{
				SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szModule, 0);
			}
			break;
			//ִ���˳�����  
			//EndDialog(0);  
		}
		break;
	}
	// }// end if((year>=2010)&&(month>=3))
	PostQuitMessage(1);
}
////////////////////////////////////////���к�ɾ��������while�������


//AES����
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

	for (int i = 0;i<16;i++)
	{
		//strTmp.Format(_T("%02x"),ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���
		//strTmp.Format("%02x", ouBuff[i]);   //��ʵ�൱�ڰ�ouBuff��ASCIIֵ���������16���Ƶ���ʽ���
		
		char temp[100] = {0};
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
	string theString=(wText);
	char * inBuff = new char[theString.size() + 1];
	//_tcscpy_s(inBuff, theString.size() + 1, theString);

	strncpy_s(inBuff,sizeof(inBuff),theString.c_str(),theString.size() + 1 );
	unsigned char temp[25];
	for (int j = 0;j<16;j++)
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
	for (int i = 0;i<16;i++)
	{
		char temp[100] = {0};
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


	unsigned char temp[25] = {0};
	for (int j = 0;j<16;j++)
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



///////////////////

//����16�ַ����ַ�������
/*
string MoreStrOnBAesEn(string leftstr)
{
	int StrLen = leftstr.size();
	string cutstr, Erystr;
	//szs.Format(_T("%d"),StrLen);
	//AfxMessageBox(szs);
	int blocknum = StrLen / 16;     //������Ӣ���ַ�������������ַ�����ȡ����16�������ַ�����ÿ��ֻ����8���ַ���������8��
	int leftnum = StrLen % 16;
	for (int i = 1;i <= blocknum;i++)
	{
		cutstr = leftstr.substr(0, 16);
		//leftstr = leftstr.Right(leftstr.size() - 16);
		leftstr = leftstr.substr(leftstr.size() , 16- leftstr.size());

		//12345678
			//ȡ�ұ�5��
			//30-16=14

			//30��-14


		//AfxMessageBox(cutstr+_T("/")+leftstr);
		Erystr = Erystr + OnBAesEn((char*)(cutstr.c_str()));
		// wchar_t * STRV=(LPWSTR)(LPCWSTR)wholestr;

	}
	// AfxMessageBox(leftstr);
	//OnBAesEn(leftstr)
	Erystr = Erystr + OnBAesEn((char*)(leftstr.c_str()));
	//AfxMessageBox(Erystr);
	//BSTR bstrText =.AllocSysString();
	//return bstrText;

	transform(Erystr.begin(), Erystr.end(), Erystr.begin(), ::toupper);
 

	return  Erystr.c_str();
	// return Erystr;
}
//����16�ַ����ַ�������


//����16�ַ����ַ�������

string MoreStrOnBAesDe(string leftstr)
{
	////����
	leftstr = leftstr.c_str();//.MakeLower();
	// leftstr=MoreStrOnBAesDe(leftstr);
	int StrLen = leftstr.size();
	string cutstr, Erystr;

	//CString szs;
	//szs.Format(_T("%d"),StrLen);
	//AfxMessageBox(szs);
	int blocknum = StrLen / 32;     //������Ӣ���ַ�������������ַ�����ȡ����16�������ַ�����ÿ��ֻ����8���ַ���������8��
	int leftnum = StrLen % 32;
	for (int i = 1;i <= blocknum;i++)
	{
		cutstr = leftstr.substr(0, 32);
		//leftstr = leftstr.Right(leftstr.size() - 32);

		leftstr = leftstr.substr(leftstr.size(), 32 - leftstr.size());

		// AfxMessageBox(cutstr+_T("/")+leftstr);
		Erystr = Erystr + OnBAesDe( (char*)(cutstr.c_str()));
		// wchar_t * STRV=(LPWSTR)(LPCWSTR)wholestr;
	}
	//AfxMessageBox(leftstr);
	//OnBAesEn(leftstr)
	// Erystr=Erystr+OnBAesDe((LPWSTR)(LPCWSTR)leftstr);
	//AfxMessageBox(Erystr);
	//BSTR bstrText = .AllocSysString();
	//return bstrText;

	return Erystr;
	///����
}



string MoreStrOnBAesEn2(string leftstr)
{
	int StrLen = leftstr.size();
	string cutstr, Erystr;
	//szs.Format(_T("%d"),StrLen);
	//AfxMessageBox(szs);
	int blocknum = StrLen / 16;     //������Ӣ���ַ�������������ַ�����ȡ����16�������ַ�����ÿ��ֻ����8���ַ���������8��
	int leftnum = StrLen % 16;
	for (int i = 1;i <= blocknum;i++)
	{
		cutstr = leftstr.substr(0, 16);
		//leftstr = leftstr.Right(leftstr.size() - 16);
		leftstr = leftstr.substr(leftstr.size(), 16 - leftstr.size());

		//AfxMessageBox(cutstr+_T("/")+leftstr);
		Erystr = Erystr + OnBAesEn2((char*)(cutstr.c_str()));
		// wchar_t * STRV=(LPWSTR)(LPCWSTR)wholestr;

	}
	// AfxMessageBox(leftstr);
	//OnBAesEn(leftstr)
	Erystr = Erystr + OnBAesEn2((char*)(leftstr.c_str()));
	//AfxMessageBox(Erystr);
	//BSTR bstrText = .AllocSysString();
	//return bstrText;

	transform(Erystr.begin(), Erystr.end(), Erystr.begin(), ::toupper);

	return (Erystr.c_str());
	// return Erystr;
}
//����16�ַ����ַ�������


//����16�ַ����ַ�������

string MoreStrOnBAesDe2(string leftstr)
{
	////����
	leftstr = leftstr.c_str();//.MakeLower();
	// leftstr=MoreStrOnBAesDe(leftstr);
	int StrLen = leftstr.size();
	string cutstr, Erystr;

	//CString szs;
	//szs.Format(_T("%d"),StrLen);
	//AfxMessageBox(szs);
	int blocknum = StrLen / 32;     //������Ӣ���ַ�������������ַ�����ȡ����16�������ַ�����ÿ��ֻ����8���ַ���������8��
	int leftnum = StrLen % 32;
	for (int i = 1;i <= blocknum;i++)
	{
		cutstr = leftstr.substr(0, 32);
		//leftstr = leftstr.Right(leftstr.GetLength() - 32);
		//leftstr = leftstr.Right(leftstr.size() - 32);

		leftstr = leftstr.substr(leftstr.size(), 32 - leftstr.size());

		// AfxMessageBox(cutstr+_T("/")+leftstr);
		Erystr = Erystr + OnBAesDe2((char*)(cutstr.c_str()));
		// wchar_t * STRV=(LPWSTR)(LPCWSTR)wholestr;
	}
	//AfxMessageBox(leftstr);
	//OnBAesEn(leftstr)
	// Erystr=Erystr+OnBAesDe((LPWSTR)(LPCWSTR)leftstr);
	//AfxMessageBox(Erystr);
	//BSTR bstrText = .AllocSysString();
	//return bstrText;

	return Erystr;
	///����
}
*/

string MoreStrOnBAesEn(string leftstr)
{
	int StrLen = leftstr.size();
	string cutstr, Erystr;
	//printf("����%d\n", StrLen);
	int blocknum = StrLen / 16;     //������Ӣ���ַ�������������ַ�����ȡ����16�������ַ�����ÿ��ֻ����8���ַ���������8��
	int leftnum = StrLen % 16;
	printf("len[%d] blocknum[%d]\n", StrLen, blocknum);

	for (int i = 1;i <= blocknum;i++)
	{
		//printf("[%d] \n", i );
		//printf("[%d] [%d]\n", 16 * (i - 1), 16 * i);
		//printf("%s  [%d][%d]\n", leftstr.c_str(),16 * (i - 1), 16 * i);
		cutstr = leftstr.substr(16*(i-1), 16);
		//printf("[%d]en_p: %s\n",i, cutstr.c_str());

		Erystr = Erystr + OnBAesEn(((char*)cutstr.c_str()));

	}
	//printf("ʣ��[%d][%d]\n", 16 * (blocknum ), StrLen - 16 * (blocknum));
	cutstr = leftstr.substr(16 * (blocknum), StrLen- 16 * (blocknum));
	//printf("en_p: %s\n", cutstr.c_str());
	Erystr = Erystr + OnBAesEn((char*) (cutstr.c_str()));
	//stringת��д
	//transform(Erystr.begin(), Erystr.end(), Erystr.begin(), ::toupper);
	return Erystr;
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
	for (int i = 1;i <= blocknum;i++)
	{
		//printf("A3\n");
		//Sleep(7000);
		cutstr = leftstr.substr(32 * (i - 1), 32);
		//printf("de_p: %s\n", cutstr.c_str());
		Erystr = Erystr + OnBAesDe( (char*)(cutstr.c_str()));

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

//����16�ַ����ַ�������

//����16�ַ����ַ�������
//AES����



//Ӳ����Ϣ


BOOL GetMacByCmd5(TCHAR *lpszMac)
{
	//��ʼ������MAC��ַ������
	memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret;
	SECURITY_ATTRIBUTES sa;
	HANDLE hReadPipe, hWritePipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//�����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		return FALSE;
	}
	//���������д�����Ϣ
	STARTUPINFO si;
	//���ؽ�����Ϣ
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //���������д���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//������ȡ�����н���
	bret = CreateProcess(NULL, szFetCmd9, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	char szBuffer[MAX_COMMAND_SIZE + 1]; //�������������������
	string strBuffer;
	if (bret)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		unsigned long count;

		//AfxMessageBox(_T("A"));

		//CloseHandle(hWritePipe);
		memset(szBuffer, 0x00, sizeof(szBuffer));
		bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
		if (!bret)
		{
			//�ر����еľ��
			// AfxMessageBox(_T("B"));
			CloseHandle(hWritePipe);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(hReadPipe);
			return FALSE;
		}
		else
		{
			strBuffer = szBuffer;
			long ipos;
			ipos = strBuffer.find(str4Search);
			//��ȡMAC��ַ��
			//strBuffer = strBuffer.substr(ipos+str4Search.length());
			//ipos = strBuffer.find("\n");
			//strBuffer = strBuffer.substr(0, ipos);
			strBuffer = strBuffer.substr(ipos + str4Search.length() - 3);
			strBuffer = strBuffer.substr(0, 17);
		}

	}
	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());
	//ȥ���м�ġ�00-50-EB-0F-27-82���м��'-'�õ�0050EB0F2782
	int j = 0;
	for (unsigned int i = 0; i<strlen(szBuffer); i++)
	{
		if (szBuffer[i] != '-')
		{
			lpszMac[j] = szBuffer[i];
			j++;
		}
	}
	//�ر����еľ��
	// AfxMessageBox(_T("C"));
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hReadPipe);
	return TRUE;
}



////////////////////////////////////////////////////////////////////////
//mac��4�ַ���ȡMAC

#include "comutil.h"
 
//WMI��ѯ�������к�
#include "eventsink.h"

//WMI��ѯ�������к�

CString GetMainbordID()
{

	HRESULT hres;
	CString returnout;
	//COMֻ��ʼ��һ�Σ�MFC������AIO.cpp �ѳ�ʼ��
	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------

	
	hres =  CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
	//cout << "Failed to initialize COM library. Error code = 0x"
	//   << hex << hres << endl;
	//return 1;                  // Program has failed.

	//AfxMessageBox(_T("Failed to initialize COM library. Error code = 0x" ));
	printf("Failed to initialize COM library. Error code = 0x");
	//return _T("Failed to initialize COM library. Error code = 0x" )
	//returnout=
	}

	
	
	// Step 2: --------------------------------------------------
	// Set general COM security levels --------------------------
	// Note: If you are using Windows 2000, you need to specify -
	// the default authentication credentials for a user by using
	// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
	// parameter of CoInitializeSecurity ------------------------

	hres =  CoInitializeSecurity(
	NULL,
	-1,                          // COM authentication
	NULL,                        // Authentication services
	NULL,                        // Reserved
	RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
	RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
	NULL,                        // Authentication info
	EOAC_NONE,                   // Additional capabilities
	NULL                         // Reserved
	);
	if (FAILED(hres))
	{
	//cout << "Failed to initialize security. Error code = 0x"
	//   << hex << hres << endl;
	//AfxMessageBox(_T("Failed to initialize security. Error code = 0x" ));
	printf("Failed to initialize security. Error code = 0x");
	CoUninitialize();
	//return 1;                    // Program has failed.
	}

	//COMֻ��ʼ��һ�Σ�MFC������AIO.cpp �ѳ�ʼ��
	
	//printf("A1\n");
	//try
	//{

	// Step 3: ---------------------------------------------------
	// Obtain the initial locator to WMI -------------------------
	IWbemLocator *pLoc = NULL;

	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc);
	//printf("A2\n");
	if (FAILED(hres))
	{
		// cout << "Failed to create IWbemLocator object."
		//    << " Err code = 0x"
		//   << hex << hres << endl;
		//AfxMessageBox(_T("Failed to create IWbemLocator object."));
		printf("Failed to create IWbemLocator object.");

		CoUninitialize();
		// return 1;                 // Program has failed.
	}
	//printf("A2\n");
	// Step 4: -----------------------------------------------------
	// Connect to WMI through the IWbemLocator::ConnectServer method

	IWbemServices *pSvc = NULL;
	printf("A3\n");
	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (e.g. Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);
 
	if (FAILED(hres))
	{
		//cout << "Could not connect. Error code = 0x" 
		//    << hex << hres << endl;
		//AfxMessageBox(_T("Could not connect. Error code = 0x"));

		printf("Could not connect. Error code = 0x");

		pLoc->Release();
		CoUninitialize();
		// return 1;                // Program has failed.
	}

	//cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;

 
	// Step 5: --------------------------------------------------
	// Set security levels on the proxy -------------------------

	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);
	printf("A6\n");
	if (FAILED(hres))
	{
		//cout << "Could not set proxy blanket. Error code = 0x" 
		//   << hex << hres << endl;
		//AfxMessageBox(_T("Could not set proxy blanket. Error code = 0x"));
		printf("Could not set proxy blanket. Error code = 0x");

		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		//return 1;               // Program has failed.
	}
	printf("A7\n");
	// Step 6: --------------------------------------------------
	// Use the IWbemServices pointer to make requests of WMI ----

	// For example, get the name of the operating system
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_BIOS"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	printf("A8\n");
	if (FAILED(hres))
	{
		//cout << "Query for operating system name failed."
		//   << " Error code = 0x" 
		//  << hex << hres << endl;

		//AfxMessageBox(_T("Query for operating system name failed"));

		printf("Query for operating system name failed");
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		//  return 1;               // Program has failed.
	}
	printf("A9\n");
	//}
	//catch(...){}

	// Step 7: -------------------------------------------------
	// Get the data from the query in step 6 -------------------

	IWbemClassObject *pclsObj;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		VARIANT vtProp;
		VariantInit(&vtProp);

		// Get the value of the Name property
		hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		//   wcout << " Product Name : " << vtProp.bstrVal << endl;


		//AfxMessageBox( vtProp.bstrVal);
		returnout = vtProp.bstrVal;



		VariantClear(&vtProp);
	}
	printf("A10\n");
	if (returnout == (""))
	{
		returnout = ("FFFFFFFF");
	}

	// Cleanup
	// ========

	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	if (pclsObj)
		pclsObj->Release();
	CoUninitialize();

	//    return 0;   // Program successfully completed.
	return 	returnout;

}







#include <time.h>
string GetMacAddress()
{
	string macaddress;
	char lpszMac[128];
		memset(lpszMac, 0x00, sizeof(lpszMac));
		GetMacByCmd(lpszMac);
		//CString 
		macaddress = string( lpszMac);
		if (macaddress == "") { macaddress =  "000000000000"; }
		//macaddress.Remove('\r');
		//macaddress.Remove('\n');
		return macaddress;
}










//д�빲���ڴ�
//#include "SharedMemoryServer.h"
//struct Mdata
//{
	//char InstrumentID[10];


//};
#include "CRC32.h"



 

//CRC32BУ����

CRC32    m_CRC32B;
unsigned long  GetCRC32BFromBuffer2(unsigned char* pData, unsigned long DataLen)
{
	//	m_strErr = "";
	unsigned long CRCResult;
	m_CRC32B.CRCInit(CRCResult);
	m_CRC32B.CRCUpdate(pData, DataLen, CRCResult);
	m_CRC32B.CRCFinal(CRCResult);


	//char * buf  = new char[10];
	//char * buf = { 0000000000 };
	//memset(buf, 0, 10);

	//if (bUpper)
	//sprintf(buf, "%.8X", CRCResult);
	//else
	//sprintf(buf, "%.8x", Result);
	//return string(buf);
	// return buf;


	//return ResultToHex(CRCResult);
	return CRCResult;
}


//CRC32BУ����



struct Mdata
{
 int  processid;        //����ID
 char InstrumentID[10]; //Ʒ��
};



void ReadCrc32(char * input)
{




}
CRC32    m_CRC32;

unsigned long   GetCRC32BFromBuffer(unsigned char* pData, unsigned long DataLen)
{
	//	m_strErr = "";
	unsigned long CRCResult;
	m_CRC32.CRCInit(CRCResult);
	m_CRC32.CRCUpdate(pData, DataLen, CRCResult);
	m_CRC32.CRCFinal(CRCResult);


	//char * buf  = new char[10];
	//char * buf = { 0000000000 };
	//memset(buf, 0, 10);

	//if (bUpper)
	//sprintf(buf, "%.8X", CRCResult);
	//else
	//sprintf(buf, "%.8x", Result);
	//return string(buf);
	// return buf;


	//return ResultToHex(CRCResult);
	return CRCResult;
}


void inline GetCrc32Value(char *Crc32Value, char * source, int sourcelength)
{

	//char Crc32Value[9] = {0};
	//char datazip[21];
	_snprintf_s(Crc32Value, 9, 9, "%.8X", GetCRC32BFromBuffer((unsigned char *)(LPCTSTR)(source), sourcelength));
	//Crc32Value[9] = '\0';
	//printf("CRCB  %s   %d\n", zip->CrcCheck, base64len);  //strlen(zip->datazip)=0
	//printf("�ṹ�峤��B1 %d \n", sizeof(zip));  ///44
	//printf("�ṹ�峤��B2 %d \n", sizeof(zip->datazip));  ///24
	//printf("�ṹ�峤��B3 %s\n",  zip->datazip);  ///112
	//	return (LPVOID)zip;
}



//д�빲���ڴ�


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



bool QuickLib_MD_Start()
{
	printf("QuickLib(Market.CTP for Python)2.08\n");


	//HelloWorld();
	//strategy2(1,2);
	//talib();

	for (int i = 0; i < MAX_EVENTNUM; i++)
	{
		if (!hEvent[i])
	   {
		//printf("Create...\n");
		char temp[10] = { 0 };
		_snprintf_s(temp,sizeof(temp),sizeof(temp),"hEvent%d",i);
		hEvent[i] = CreateEvent(NULL, FALSE, FALSE, temp);//TRUE�ֶ���λ
														 //hEvent = CreateEvent(NULL, FALSE, FALSE, "abc");//TRUE�Զ���λ������ResetEvent
	   }
	
	}
	InitializeCriticalSection(&g_csdata);


	std::ifstream ifs(gMDAccount.c_str());
	if (ifs.is_open())
	{
		std::string fl;
		getline(ifs, fl);
		getline(ifs, gFrontAddr[0]);
		getline(ifs, gFrontAddr[1]);
		getline(ifs, gFrontAddr[2]);

		getline(ifs, fl);
		getline(ifs, gBrokerID);

		getline(ifs, fl);
		getline(ifs, gUserID);

		getline(ifs, fl);
		getline(ifs, gPassword);

		ifs.close();
	}
	else
	{
		std::cout << "fail to open " << gMDAccount << std::endl;
		gStatus = 1;
		return false;
	}






	ReadTradeTime();




//	std::ifstream ifs2(gLic.c_str());
	//if (ifs2.is_open())
	//{
		//std::string fl;
		//getline(ifs2, fl);
		//getline(ifs2, sn);


		//printf("SN:%s\n",sn.c_str());
		//getline(ifs, gFrontAddr[1]);
		//getline(ifs, gFrontAddr[2]);

		//getline(ifs, fl);
		//getline(ifs, gBrokerID);

		//getline(ifs, fl);
	//	getline(ifs, gUserID);

		//getline(ifs, fl);
		//getline(ifs, gPassword);

		//ifs2.close();
	//}
	//else
	//{
		//std::cout << "fail to open Lic:" << gLic << std::endl;
		//gStatus = 1;
		//return false;
	//}



	/*

	//��ȡ����ʱ��
	std::ifstream ifs_tradetime(gTradeTime.c_str());
	if (ifs_tradetime.is_open())
	{
		std::string fl;



		//getline(ifs, fl);
		//getline(ifs, fl);
		//TradeTime[0].begin1 = atof(f1.c_str());

		//getline(ifs.c_str(), (TradeTime[0].begin1));
		//getline(ifs, gFrontAddr[1]);
		//getline(ifs, gFrontAddr[2]);

		//getline(ifs, fl);
		//getline(ifs, gBrokerID);

		//getline(ifs, fl);
		//getline(ifs, gUserID);

		//getline(ifs, fl);
		//getline(ifs, gPassword);

		ifs_tradetime.close();
	}
	else
	{
		std::cout << "fail to open " << TradeTime << std::endl;
		gStatus = 1;
		return false;
	}
	*/

		printf("MAC��%s\n", GetMacAddress().c_str());



		printf("���壺%s\n", (LPSTR)(LPCSTR)GetMainbordID());

	
		string temp = (LPSTR)(LPCSTR)GetMainbordID() + GetMacAddress() ;
		printf("MAC: %s\n", temp.c_str());


		printf("EnSTR ��%s\n", MoreStrOnBAesEn(temp).c_str());


		printf("DeSTR ��%s\n", MoreStrOnBAesDe(MoreStrOnBAesEn(temp)).c_str());





	//strategy1();
	//strategy2(4,13);


	BOOL ret = gMDSpi.Init();
	if (ret) 
	{
		return TRUE;
	}else
	{
		return FALSE;
	}
}




void UnSubscribeMarketData(const char *InstrumentID)
{
	char * crcvalue = NULL;
	if (mapInstrument)
	{
	
		delete mapInstrument;
		mapInstrument = NULL;
	}

	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	memset(ppInstrumentID[amount],0,sizeof(TThostFtdcInstrumentIDType));

	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	memset(depthdata[amount],0,sizeof(CThostFtdcDepthMarketDataField));

	++amount;
	gMDSpi.UnSubscribeMarketData();

}

//ѯ��
void SubscribeForQuoteRsp(  char *InstrumentID)
{
	/*
	char * crcvalue = NULL;

	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	*/
	gMDSpi.SubscribeForQuoteRsp(InstrumentID);

}
//��Ӽ�¼, 
bool FindId(const char *Instrument, const char * str)
{
	char * pdest1 = strstr((char*)Instrument, (char*)str);
	int  result1 = pdest1 - Instrument + 1;

	if (pdest1 != NULL)
	{		//printf("��%s����%s\n", InstrumentID_n[id],str );
		return true;
	}
	else
	{
		//printf("%s û����%s����\n", str, InstrumentID_n[id]);
		return false;
	}
}
extern void InitGuestOnlineHash(GuestOnlineHash * q);
bool Add(const char *InstrumentID, const PERIODTYPE * pt)
{
	std::hash_map<string, GuestOnlineHash>::iterator it;
	it = mapData.find(InstrumentID);
	if (it == mapData.end())
	{
		//printf("*************û�ҵ��ú�Լ��%s\n", InstrumentID);
		//GuestOnlineHash value;
		//InitGuestOnlineHash(&value);
		//mapData.insert(std::make_pair(InstrumentID, value));
		//ClearGuestOnlineHash(&value);
		//it = mapData.find(InstrumentID);


		GuestOnlineHash pi;
		InitGuestOnlineHash(&pi);
		pair<string, GuestOnlineHash>value2(InstrumentID, pi);
		mapData.insert(value2);



	}
	it = mapData.find(InstrumentID);
	if (it != mapData.end())
	{
		GuestOnlineHash * q = &(it->second);
			if (pt)
			{

				for (int i = 0; i < PERIOD_NUM; i++)
				{


					if (pt->periodtype[i])
					{
						switch (pt->periodtype[i])
						{
						case QL_ALL:
							q->period_M1 = true;
							q->period_M3 = true;
							q->period_M5 = true;
							q->period_M10 = true;
							q->period_M15 = true;
							q->period_M30 = true;
							q->period_M60 = true;
							q->period_D1 = true;
							printf("%s����M1,M3,M5,M10,M15,M30,M60,D1����\n", InstrumentID);
							break;
						case QL_M1:
							q->period_M1 = true;
							printf("%s����M1����\n", InstrumentID);
							break;
						case QL_M3:
							q->period_M3 = true;
							printf("%s����M3����\n", InstrumentID);
							break;
						case QL_M5:
							q->period_M5 = true;
							printf("%s����M5����\n", InstrumentID);
							break;

						case QL_M10:
							q->period_M10 = true;
							printf("%s����M10����\n", InstrumentID);
							break;

						case QL_M15:
							q->period_M15 = true;
							printf("%s����M15����\n", InstrumentID);
							break;

						case QL_M30:
							q->period_M30 = true;
							printf("%s����M30����\n", InstrumentID);
							break;

						case QL_M60:
							q->period_M60 = true;
							printf("%s����M60����\n", InstrumentID);
							break;

						case QL_M120:
							q->period_M120 = true;
							printf("%s����M120����\n", InstrumentID);
							break;

						case QL_D1:
							q->period_D1 = true;
							printf("%s����D1����\n", InstrumentID);
							break;
						}

					}

				}
			}


			if (FindId(InstrumentID, "ni"))
			{
				q->TYPEID = TYPE_NI;
			}
			else if (FindId(InstrumentID, "zn"))
			{
				q->TYPEID = TYPE_ZN;
			}
			else if (FindId(InstrumentID, "al"))
			{
				q->TYPEID = TYPE_AL;
			}
			else if (FindId(InstrumentID, "cu"))
			{
				q->TYPEID = TYPE_CU;
			}
			else if (FindId(InstrumentID, "au"))
			{
				q->TYPEID = TYPE_AU;
			}
			else if (FindId(InstrumentID, "ag"))
			{
				q->TYPEID = TYPE_AG;
			}
			else if (FindId(InstrumentID, "i"))
			{
				q->TYPEID = TYPE_I;
			}
			else if (FindId(InstrumentID, "ru"))
			{
				q->TYPEID = TYPE_RU;
			}
			else if (FindId(InstrumentID, "ta"))
			{
				q->TYPEID = TYPE_TA;
			}
			else if (FindId(InstrumentID, "a"))
			{
				q->TYPEID = TYPE_A;
			}
			else if (FindId(InstrumentID, "m"))
			{
				q->TYPEID = TYPE_M;
			}
			else if (FindId(InstrumentID, "y"))
			{
				q->TYPEID = TYPE_Y;
			}
			else if (FindId(InstrumentID, "p"))
			{
				q->TYPEID = TYPE_P;
			}
			else if (FindId(InstrumentID, "rb"))
			{
				q->TYPEID = TYPE_RB;
			}
			else if (FindId(InstrumentID, "ma"))
			{
				q->TYPEID = TYPE_MA;
			}
			else if (FindId(InstrumentID, "pp"))
			{
				q->TYPEID = TYPE_PP;
			}
			else if (FindId(InstrumentID, "cs"))
			{
				q->TYPEID = TYPE_CS;
			}
			else if (FindId(InstrumentID, "jd"))
			{
				q->TYPEID = TYPE_JD;
			}
			else if (FindId(InstrumentID, "bu"))
			{
				q->TYPEID = TYPE_BU;
			}
			else if (FindId(InstrumentID, "fg"))
			{
				q->TYPEID = TYPE_FG;
			}
			else if (FindId(InstrumentID, "l"))
			{
				q->TYPEID = TYPE_L;
			}
			else if (FindId(InstrumentID, "v"))
			{
				q->TYPEID = TYPE_V;
			}
			else if (FindId(InstrumentID, "sr"))
			{
				q->TYPEID = TYPE_SR;
			}
			else if (FindId(InstrumentID, "rm"))
			{
				q->TYPEID = TYPE_RM;
			}
			else if (FindId(InstrumentID, "cf"))
			{
				q->TYPEID = TYPE_CF;
			}
			else if (FindId(InstrumentID, "c"))
			{
				q->TYPEID = TYPE_C;
			}
			else if (FindId(InstrumentID, "wh"))
			{
				q->TYPEID = TYPE_WH;
			}
			else if (FindId(InstrumentID, "sm"))
			{
				q->TYPEID = TYPE_SM;
			}
			else if (FindId(InstrumentID, "sf"))
			{
				q->TYPEID = TYPE_SF;
			}
			else if (FindId(InstrumentID, "ic"))
			{
				q->TYPEID = TYPE_IC;
			}
			else if (FindId(InstrumentID, "if"))
			{
				q->TYPEID = TYPE_IF;
			}
			else if (FindId(InstrumentID, "ih"))
			{
				q->TYPEID = TYPE_IH;
			}
			else if (FindId(InstrumentID, "t"))
			{
				q->TYPEID = TYPE_T;
			}
			else if (FindId(InstrumentID, "tf"))
			{
				q->TYPEID = TYPE_TF;
			}

			else if (FindId(InstrumentID, "new1"))
			{
				q->TYPEID = TYPE_NEW1;
			}
			else if (FindId(InstrumentID, "new2"))
			{
				q->TYPEID = TYPE_NEW2;
			}
			else if (FindId(InstrumentID, "new3"))
			{
				q->TYPEID = TYPE_NEW3;
			}
			else if (FindId(InstrumentID, "new4"))
			{
				q->TYPEID = TYPE_NEW4;
			}
			else if (FindId(InstrumentID, "new5"))
			{
				q->TYPEID = TYPE_NEW5;
			}
			else if (FindId(InstrumentID, "new6"))
			{
				q->TYPEID = TYPE_NEW6;
			}
			else if (FindId(InstrumentID, "new7"))
			{
				q->TYPEID = TYPE_NEW7;
			}
			else if (FindId(InstrumentID, "new8"))
			{
				q->TYPEID = TYPE_NEW8;
			}
			else if (FindId(InstrumentID, "new9"))
			{
				q->TYPEID = TYPE_NEW9;
			}
			else if (FindId(InstrumentID, "new10"))
			{
				q->TYPEID = TYPE_NEW10;
			}

			else if (FindId(InstrumentID, "new11"))
			{
				q->TYPEID = TYPE_NEW11;
			}
			else if (FindId(InstrumentID, "new12"))
			{
				q->TYPEID = TYPE_NEW12;
			}
			else if (FindId(InstrumentID, "new13"))
			{
				q->TYPEID = TYPE_NEW13;
			}
			else if (FindId(InstrumentID, "new14"))
			{
				q->TYPEID = TYPE_NEW14;
			}
			else if (FindId(InstrumentID, "new15"))
			{
				q->TYPEID = TYPE_NEW15;
			}
			else if (FindId(InstrumentID, "new16"))
			{
				q->TYPEID = TYPE_NEW16;
			}
			else if (FindId(InstrumentID, "new17"))
			{
				q->TYPEID = TYPE_NEW17;
			}
			else if (FindId(InstrumentID, "new18"))
			{
				q->TYPEID = TYPE_NEW18;
			}
			else if (FindId(InstrumentID, "new19"))
			{
				q->TYPEID = TYPE_NEW19;
			}
			else if (FindId(InstrumentID, "new20"))
			{
				q->TYPEID = TYPE_NEW20;
			}

			/*
			else
			{
				//WirteSingleRecordToFile8(id, "K16");
				//cout << "�޴˼�¼����Ӽ�¼\n" << endl;
				//printf("(A)��Ӽ�¼ [%d]%s  keystr:[%s] key[%d]\n", id, InstrumentID_n[id], keystr, key);
				GuestOnlineHash *temp = new GuestOnlineHash;
				//DWORD dwTick = ::GetTickCount();
				//WirteSingleRecordToFile8(id, "K17");
				//temp->LoginErrorTime=NULL;
				//temp->LoginErrorNum=0;
				//temp->dwLastActiveTime= dwTick;			 // ��¼���û��Ļʱ�䣨������ʹ�ã�

				//temp->next = HashGuestOnlineList[key]->next;
				//HashGuestOnlineList[key]->next = temp;

				if (pt)
				{

					for (int i = 0; i < PERIOD_NUM; i++)
					{
						//printf("yyyyyyyyyyyyyyyyyyyyyyy3\n");
						//printf("(%d)[%d][%d][%d][%d]\n",i, pt->periodtype[i], QL_M1, QL_M3, QL_M5);

						if (pt->periodtype[i])
						{
							switch (pt->periodtype[i])
							{
							case QL_ALL:
								temp->period_M1 = true;
								temp->period_M3 = true;
								temp->period_M5 = true;
								temp->period_M10 = true;
								temp->period_M15 = true;
								temp->period_M30 = true;
								temp->period_M60 = true;
								temp->period_D1 = true;
								printf("%s����M1,M3,M5,M10,M15,M30,M60,D1����\n", InstrumentID);
								break;
							case QL_M1:
								temp->period_M1 = true;
								printf("%s����M1����\n", InstrumentID);
								break;
							case QL_M3:
								temp->period_M3 = true;
								printf("%s����M3����\n", InstrumentID);
								break;
							case QL_M5:
								temp->period_M5 = true;
								printf("%s����M5����\n", InstrumentID);
								break;

							case QL_M10:
								temp->period_M10 = true;
								printf("%s����M10����\n", InstrumentID);
								break;

							case QL_M15:
								temp->period_M15 = true;
								printf("%s����M15����\n", InstrumentID);
								break;

							case QL_M30:
								temp->period_M30 = true;
								printf("%s����M30����\n", InstrumentID);
								break;

							case QL_M60:
								temp->period_M60 = true;
								printf("%s����M60����\n", InstrumentID);
								break;

							case QL_M120:
								temp->period_M120 = true;
								printf("%s����M120����\n", InstrumentID);
								break;

							case QL_D1:
								temp->period_D1 = true;
								printf("%s����D1����\n", InstrumentID);
								break;
							}

						}

					}
				}



				//��ӵ�
				//temp->CROSS_SINGLE_TURN[id][0] = turn;
				//temp->CROSS_SINGLE_PRICE[id][0] = NewPrice;
				//temp->CROSS_SINGLE_SPACE_VALUE[id][0] = fabs(q->CROSS_SINGLE_PRICE[id][1] - q->CROSS_SINGLE_PRICE[id][0]);
				//temp->periodtype1 = periodtype;
				//temp->CROSS_SINGLE_SPACE_PER_M1[id][0] = (q->CROSS_SINGLE_SPACE_VALUE[id][1] - q->CROSS_SINGLE_SPACE_VALUE[id][0]) / (10000 * (q->CROSS_SINGLE_TIME[id][1] - q->CROSS_SINGLE_TIME[id][0]));
				//��ӵ�
				strncpy_s(temp->InstrumentID, sizeof(temp->InstrumentID), InstrumentID, strlen(InstrumentID));
				temp->InstrumentID[strlen(InstrumentID)] = '\0';



				if (FindId(InstrumentID, "ni"))
				{
					temp->TYPEID = TYPE_NI;
				}
				else if (FindId(InstrumentID, "zn"))
				{
					temp->TYPEID = TYPE_ZN;
				}
				else if (FindId(InstrumentID, "al"))
				{
					temp->TYPEID = TYPE_AL;
				}
				else if (FindId(InstrumentID, "cu"))
				{
					temp->TYPEID = TYPE_CU;
				}
				else if (FindId(InstrumentID, "au"))
				{
					temp->TYPEID = TYPE_AU;
				}
				else if (FindId(InstrumentID, "ag"))
				{
					temp->TYPEID = TYPE_AG;
				}
				else if (FindId(InstrumentID, "i"))
				{
					temp->TYPEID = TYPE_I;
				}
				else if (FindId(InstrumentID, "ru"))
				{
					temp->TYPEID = TYPE_RU;
				}
				else if (FindId(InstrumentID, "ta"))
				{
					temp->TYPEID = TYPE_TA;
				}
				else if (FindId(InstrumentID, "a"))
				{
					temp->TYPEID = TYPE_A;
				}
				else if (FindId(InstrumentID, "m"))
				{
					temp->TYPEID = TYPE_M;
				}
				else if (FindId(InstrumentID, "y"))
				{
					temp->TYPEID = TYPE_Y;
				}
				else if (FindId(InstrumentID, "p"))
				{
					temp->TYPEID = TYPE_P;
				}
				else if (FindId(InstrumentID, "rb"))
				{
					temp->TYPEID = TYPE_RB;
				}
				else if (FindId(InstrumentID, "ma"))
				{
					temp->TYPEID = TYPE_MA;
				}
				else if (FindId(InstrumentID, "pp"))
				{
					temp->TYPEID = TYPE_PP;
				}
				else if (FindId(InstrumentID, "cs"))
				{
					temp->TYPEID = TYPE_CS;
				}
				else if (FindId(InstrumentID, "jd"))
				{
					temp->TYPEID = TYPE_JD;
				}
				else if (FindId(InstrumentID, "bu"))
				{
					temp->TYPEID = TYPE_BU;
				}
				else if (FindId(InstrumentID, "fg"))
				{
					temp->TYPEID = TYPE_FG;
				}
				else if (FindId(InstrumentID, "l"))
				{
					temp->TYPEID = TYPE_L;
				}
				else if (FindId(InstrumentID, "v"))
				{
					temp->TYPEID = TYPE_V;
				}
				else if (FindId(InstrumentID, "sr"))
				{
					temp->TYPEID = TYPE_SR;
				}
				else if (FindId(InstrumentID, "rm"))
				{
					temp->TYPEID = TYPE_RM;
				}
				else if (FindId(InstrumentID, "cf"))
				{
					temp->TYPEID = TYPE_CF;
				}
				else if (FindId(InstrumentID, "c"))
				{
					temp->TYPEID = TYPE_C;
				}
				else if (FindId(InstrumentID, "wh"))
				{
					temp->TYPEID = TYPE_WH;
				}
				else if (FindId(InstrumentID, "sm"))
				{
					temp->TYPEID = TYPE_SM;
				}
				else if (FindId(InstrumentID, "sf"))
				{
					temp->TYPEID = TYPE_SF;
				}
				else if (FindId(InstrumentID, "ic"))
				{
					temp->TYPEID = TYPE_IC;
				}
				else if (FindId(InstrumentID, "if"))
				{
					temp->TYPEID = TYPE_IF;
				}
				else if (FindId(InstrumentID, "ih"))
				{
					temp->TYPEID = TYPE_IH;
				}
				else if (FindId(InstrumentID, "t"))
				{
					temp->TYPEID = TYPE_T;
				}
				else if (FindId(InstrumentID, "tf"))
				{
					temp->TYPEID = TYPE_TF;
				}

				else if (FindId(InstrumentID, "new1"))
				{
					temp->TYPEID = TYPE_NEW1;
				}
				else if (FindId(InstrumentID, "new2"))
				{
					temp->TYPEID = TYPE_NEW2;
				}
				else if (FindId(InstrumentID, "new3"))
				{
					temp->TYPEID = TYPE_NEW3;
				}
				else if (FindId(InstrumentID, "new4"))
				{
					temp->TYPEID = TYPE_NEW4;
				}
				else if (FindId(InstrumentID, "new5"))
				{
					temp->TYPEID = TYPE_NEW5;
				}
				else if (FindId(InstrumentID, "new6"))
				{
					temp->TYPEID = TYPE_NEW6;
				}
				else if (FindId(InstrumentID, "new7"))
				{
					temp->TYPEID = TYPE_NEW7;
				}
				else if (FindId(InstrumentID, "new8"))
				{
					temp->TYPEID = TYPE_NEW8;
				}
				else if (FindId(InstrumentID, "new9"))
				{
					temp->TYPEID = TYPE_NEW9;
				}
				else if (FindId(InstrumentID, "new10"))
				{
					temp->TYPEID = TYPE_NEW10;
				}

				else if (FindId(InstrumentID, "new11"))
				{
					temp->TYPEID = TYPE_NEW11;
				}
				else if (FindId(InstrumentID, "new12"))
				{
					temp->TYPEID = TYPE_NEW12;
				}
				else if (FindId(InstrumentID, "new13"))
				{
					temp->TYPEID = TYPE_NEW13;
				}
				else if (FindId(InstrumentID, "new14"))
				{
					temp->TYPEID = TYPE_NEW14;
				}
				else if (FindId(InstrumentID, "new15"))
				{
					temp->TYPEID = TYPE_NEW15;
				}
				else if (FindId(InstrumentID, "new16"))
				{
					temp->TYPEID = TYPE_NEW16;
				}
				else if (FindId(InstrumentID, "new17"))
				{
					temp->TYPEID = TYPE_NEW17;
				}
				else if (FindId(InstrumentID, "new18"))
				{
					temp->TYPEID = TYPE_NEW18;
				}
				else if (FindId(InstrumentID, "new19"))
				{
					temp->TYPEID = TYPE_NEW19;
				}
				else if (FindId(InstrumentID, "new20"))
				{
					temp->TYPEID = TYPE_NEW20;
				}


				//strncpy_s(temp->keystr, sizeof(temp->keystr), keystr, strlen(keystr));
				//temp->keystr[strlen(keystr)] = '\0';
				//strncpy_s(temp->checkcode, sizeof(temp->checkcode), checkcode, strlen(checkcode));
				//temp->checkcode[strlen(checkcode)] = '\0';
				//WirteSingleRecordToFile8(id, "K20");
				//printf("A7\n");
			}
			*/
			return true;
		//}
	}

	return false;
	//strncpy_s(temp->InstrumentID, sizeof(temp->InstrumentID), InstrumentID, strlen(InstrumentID));
	//temp->InstrumentID[strlen(InstrumentID)] = '\0';




}

void Subscribe(const char *InstrumentID)
{
	char * crcvalue = NULL;
	Add(InstrumentID, NULL);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();
	
}

void Subscribe1(const char *InstrumentID, int periodtype1)
{
	char * crcvalue = NULL;
	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = NULL;
	pt.periodtype[2] = NULL;
	pt.periodtype[3] = NULL;
	pt.periodtype[4] = NULL;
	pt.periodtype[5] = NULL;
	pt.periodtype[6] = NULL;
	pt.periodtype[7] = NULL;
	Add(InstrumentID, &pt);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();
	printf("(��������1������)\n");
}
void Subscribe2(const char *InstrumentID, int periodtype1, int periodtype2)
{
	char * crcvalue = NULL;
	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = periodtype2;
	pt.periodtype[2] = NULL;
	pt.periodtype[3] = NULL;
	pt.periodtype[4] = NULL;
	pt.periodtype[5] = NULL;
	pt.periodtype[6] = NULL;
	pt.periodtype[7] = NULL;
	Add(InstrumentID, &pt);
	//printf("pass %s", contract);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();


	printf("(��������2������)\n");
}
void Subscribe3(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3)
{
	char * crcvalue = NULL;
	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = periodtype2;
	pt.periodtype[2] = periodtype3;
	pt.periodtype[3] = NULL;
	pt.periodtype[4] = NULL;
	pt.periodtype[5] = NULL;
	pt.periodtype[6] = NULL;
	pt.periodtype[7] = NULL;
	Add(InstrumentID, &pt);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();

	printf("(��������3������)\n");
}

void Subscribe4(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4)
{
	char * crcvalue = NULL;
	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = periodtype2;
	pt.periodtype[2] = periodtype3;
	pt.periodtype[3] = periodtype4;
	pt.periodtype[4] = NULL;
	pt.periodtype[5] = NULL;
	pt.periodtype[6] = NULL;
	pt.periodtype[7] = NULL;
	Add(InstrumentID, &pt);
	//else
	//{
	//printf("NONE ADD %s\n", contract);

	//}
	//printf("pass %s", contract);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();
	printf("(��������4������)\n");
}

void Subscribe5(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5)
{
	char * crcvalue = NULL;
	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = periodtype2;
	pt.periodtype[2] = periodtype3;
	pt.periodtype[3] = periodtype4;
	pt.periodtype[4] = periodtype5;
	pt.periodtype[5] = NULL;
	pt.periodtype[6] = NULL;
	pt.periodtype[7] = NULL;
	Add(InstrumentID, &pt);
	//else
	//{
	//printf("NONE ADD %s\n", contract);

	//}
	//printf("pass %s", contract);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();
	printf("(��������5������)\n");
}

void Subscribe6(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6)
{
	char * crcvalue = NULL;
	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = periodtype2;
	pt.periodtype[2] = periodtype3;
	pt.periodtype[3] = periodtype4;
	pt.periodtype[4] = periodtype5;
	pt.periodtype[5] = periodtype6;
	pt.periodtype[6] = NULL;
	pt.periodtype[7] = NULL;
	Add(InstrumentID, &pt);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();
	printf("(��������6������)\n");
}

void Subscribe7(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6, int periodtype7)
{
	char * crcvalue = NULL;

	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = periodtype2;
	pt.periodtype[2] = periodtype3;
	pt.periodtype[3] = periodtype4;
	pt.periodtype[4] = periodtype5;
	pt.periodtype[5] = periodtype6;
	pt.periodtype[6] = periodtype7;
	pt.periodtype[7] = NULL;
	Add(InstrumentID, &pt);
	//printf("pass %s", contract);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();
	printf("(��������7������)\n");
}


void Subscribe8(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6, int periodtype7, int periodtype8)
{
	char * crcvalue = NULL;
	PERIODTYPE pt;
	pt.periodtype[0] = periodtype1;
	pt.periodtype[1] = periodtype2;
	pt.periodtype[2] = periodtype3;
	pt.periodtype[3] = periodtype4;
	pt.periodtype[4] = periodtype5;
	pt.periodtype[5] = periodtype6;
	pt.periodtype[6] = periodtype7;
	pt.periodtype[7] = periodtype8;
	Add(InstrumentID, &pt);
	//printf("pass %s", contract);
	ppInstrumentID[amount] = new TThostFtdcInstrumentIDType;
	::strcpy(ppInstrumentID[amount], InstrumentID);
	//::strcpy_s(ppInstrumentID[amount],sizeof(ppInstrumentID[amount]), contract);
	gMarket[InstrumentID] = amount;
	//data[amount] = new CThostFtdcDepthMarketDataField;
	depthdata[amount] = new CThostFtdcDepthMarketDataField;
	++amount;
	gMDSpi.SubscribeMarketData();
	printf(",��������8������\n");
}

/*
int Test_MA()
{
	int retCode = TA_Initialize();
	if (retCode != TA_SUCCESS)
	{
		printf("\n��ʼ��ָ���ʧ��\n");
		return -1;
	}

	printf("MD����ָ�����\n");


	TA_Real    closePrice[400] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
		81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
		34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
		34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
		34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
		34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
		34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
		34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
		34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34};

	TA_Real    out[400];

	TA_Integer outBeg;

	//TA_IntegeroutNbElement;

	// ... initializeyour closing price here... 
	//double outNbElement[] = {34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56};
	int outNbElement = 0;
	retCode = TA_MA(0, 50,

		&closePrice[0],

		30, TA_MAType_SMA,

		&outBeg, &outNbElement, &out[0]);

	// The output isdisplayed here 

	for (int i = 0; i <outNbElement; i++)

		printf("�� %d �� MAֵ = %f\n", outBeg + i, out[i]);


	//int retValue = genCode(1, 1);

	retCode = TA_Shutdown();
	if (retCode != TA_SUCCESS)
	{
		printf("Shutdown failed (%d)\n", retCode);
	}
	return 1;
}
*/


bool CROSSUP(const char *InstrumentID, int indicators, int periodtype, int PriceType, int period1, int period2,bool printstate)
{
	return 0;// ���� 2017.1.1 CxHashList->GetDataCross(InstrumentID, indicators, PriceType, periodtype, period1, period2, true, printstate);
}

bool CROSSDOWN(const char *InstrumentID, int indicators, int periodtype, int PriceType, int period1, int period2,bool printstate)
{
	return 0;//����2017.1.1 CxHashList->GetDataCross(InstrumentID, indicators, PriceType, periodtype, period1, period2, false, printstate);
 
}

bool CROSSUP_S(int strategyid, int periodtype, int PriceType, int period1, int period2)
{



	return 0;
}

bool CROSSDOWN_S(int strategyid, int periodtype, int PriceType, int period1, int period2)
{



	return 0;

}


 /*

//XXXXXXXXXXɾ��
double MA(const char *InstrumentID, int periodtype, int PriceType,int ref, int number)
{
	//printf("MA���� %s periodtype[%d] PriceType[%d] number[%d]\n", contract, periodtype, PriceType, number);
	printf("MA���� [%s] number[%d]", InstrumentID,number);

 
	switch (periodtype)
	{
	//case QL_ALL:
		//break;
	case QL_M1:
		printf("���ڣ�M1 ");
		break;
	case QL_M3:
		printf("���ڣ�M3 ");
		break;
	case QL_M5:
		printf("���ڣ�M5 ");
		break;
	case QL_M10:
		printf("���ڣ�M10 ");
		break;
	case QL_M15:
		printf("���ڣ�M15 ");
		break;
	case QL_M30:
		printf("���ڣ�M30 ");
		break;
	case QL_M60:
		printf("���ڣ�M60 ");
		break;
	case QL_M120:
		printf("���ڣ�M120 ");
		break;
	case QL_D1:
		printf("���ڣ�D1 ");
		break;
	default:
		return 0;
		break;
	}




	switch (PriceType)
	{
	case QL_CLOSE:
		printf("���̼� ");
		break;
	case QL_OPEN:
		printf("���̼� ");
		break;
	case QL_HIGH:
		printf("��߼� ");
		break;
	case QL_LOW:
		printf("��ͼ� ");
		break;

	default:
		return 0;
		break;
	}
	printf("\n");


	TA_Real * DataArr=new TA_Real[number + ref];
	CxHashList->GetDataArr(InstrumentID, PriceType, periodtype, DataArr); 


	int retCode = TA_Initialize();
	if (retCode != TA_SUCCESS)
	{
		printf("\n��ʼ��ָ���ʧ��\n");
		return -1;
	}

	//printf("MD����ָ�����\n");



	TA_Real  *  out=new TA_Real[number];

	TA_Integer outBeg;

	//TA_IntegeroutNbElement;

	// ... initializeyour closing price here... 
	//double outNbElement[] = {34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56};
	int outNbElement = 0;
	//retCode = TA_MA(0, 50,&closePrice[0],30, TA_MAType_SMA,&outBeg, &outNbElement, &out[0]);
	//retCode = TA_MA(0, 50, &closePrice[0],30,TA_MAType_SMA,&outBeg, &outNbElement, out);

	                //��ʼ ���� ����ֵ   30����                   �����ʼ    ����      �����������      
	retCode = TA_MA(ref, ref+50, DataArr, number, TA_MAType_SMA, &outBeg, &outNbElement, out);

	// The output isdisplayed here 
	for (int i = 0; i <outNbElement; i++)

		printf("�� %d �� MAֵ = %f\n", outBeg + i, out[i]);


	//printf("�� %d �� MAֵ = %f\n", outBeg + i, out[i]);

	//int retValue = genCode(1, 1);

	retCode = TA_Shutdown();
	if (retCode != TA_SUCCESS)
	{
		printf("Shutdown failed (%d)\n", retCode);
	}
	return 1;
}


*/

double MA(const char *InstrumentID, int periodtype, int PriceType,int ref, int number)
{
	//printf("MA���� %s periodtype[%d] PriceType[%d] number[%d]\n", contract, periodtype, PriceType, number);
	//printf("MA���� [%s][%d]", InstrumentID, number);

	switch (periodtype)
	{
		//case QL_ALL:
		//break;
	case QL_M1:
		printf("���ڣ�M1 ");
		break;
	case QL_M3:
		printf("���ڣ�M3 ");
		break;
	case QL_M5:
		printf("���ڣ�M5 ");
		break;
	case QL_M10:
		printf("���ڣ�M10 ");
		break;
	case QL_M15:
		printf("���ڣ�M15 ");
		break;
	case QL_M30:
		printf("���ڣ�M30 ");
		break;
	case QL_M60:
		printf("���ڣ�M60 ");
		break;
	case QL_M120:
		printf("���ڣ�M120 ");
		break;
	case QL_D1:
		printf("���ڣ�D1 ");
		break;
	default:
		return 0;
		break;
	}

	switch (PriceType)
	{
	case QL_CLOSE:
		printf("���̼� ");
		break;
	case QL_OPEN:
		printf("���̼� ");
		break;
	case QL_HIGH:
		printf("��߼� ");
		break;
	case QL_LOW:
		printf("��ͼ� ");
		break;

	default:
		return 0;
		break;
	}
	printf("\n");


 

	TA_Real * DataArr = new TA_Real[number + ref];
	memset(DataArr, 0, sizeof(TA_Real)*(number + ref));



	return 0;
	/*
	����2017.1.1
	                                                             //DataArrδ���ֵ
	if (!CxHashList->GetDataArr(InstrumentID, PriceType, periodtype, DataArr))
	{
		printf("û�ж��ĸ���������\n");
		delete []DataArr;
		DataArr = NULL;
		return -1;
	}
	
	*/



	int retCode = TA_Initialize();
	if (retCode != TA_SUCCESS)
	{
		printf("\n��ʼ��ָ���ʧ��\n");
		return -1;
	}

	//printf("MD����ָ�����\n");

	// ��Զ��ʱ��
	/*TA_Real    closePrice[50] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50 };

	*/
	//0  29  1 30  15.5

    //20  49  21 50 71/2=30.5

	/*
	, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
	81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34 };

	*/
	TA_Real    indata[50] = {0};// = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		//41,42,43,44,45,46,47,48,49,50 };

	//for (int i = 0; i < 50;i++)
	//{
		//indata[i] = closePrice[50 - i-1];
	
	//}
	TA_Real  *  out = new TA_Real[number];
	memset(out,0,sizeof(TA_Real)*number);

	//TA_Real  *  out_python = new TA_Real[number];

	TA_Integer outBeg;

	//TA_IntegeroutNbElement;

	/* ... initializeyour closing price here... */
	//double outNbElement[] = {34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56};
	int outNbElement = 0;
	//retCode = TA_MA(0, 50,&closePrice[0],30, TA_MAType_SMA,&outBeg, &outNbElement, &out[0]);


	//��ʼ ���� ����ֵ   30����                   �����ʼ    ����      �����������      
	//retCode = TA_MA(ref, ref + 50, DataArr, number, TA_MAType_SMA, &outBeg, &outNbElement, out);
	//retCode = TA_MA(ref, ref + number, &closePrice[0], number, TA_MAType_SMA, &outBeg, &outNbElement, out);
	retCode = TA_MA(ref, ref + number, DataArr, number, TA_MAType_SMA, &outBeg, &outNbElement, out);


	//retCode = TA_MA(ref, ref + 50, &indata[0], 30, TA_MAType_SMA, &outBeg, &outNbElement, out);
	/* The output isdisplayed here */

	//for (int i = 0; i < outNbElement - 1; i++)
	//{
		 //���������  ���Ѿ���PYTHON����� printf("�� %d �� MAֵ = %f\n", number - (outBeg + ref + 1), out[ref]);	
	//}
	delete []DataArr;
	DataArr = NULL;


	//int retValue = genCode(1, 1);

	retCode = TA_Shutdown();
	if (retCode != TA_SUCCESS)
	{
		printf("Shutdown failed (%d)\n", retCode);
	}
	double result = (double)(out[ref]);
	delete[]out;
	out = NULL;

	return result;
}



double RSI(const char *InstrumentID, int periodtype, int PriceType, int ref, int number)
{
	//printf("MA���� %s periodtype[%d] PriceType[%d] number[%d]\n", contract, periodtype, PriceType, number);
	//printf("MA���� [%s][%d]", InstrumentID, number);

	switch (periodtype)
	{
		//case QL_ALL:
		//break;
	case QL_M1:
		printf("���ڣ�M1 ");
		break;
	case QL_M3:
		printf("���ڣ�M3 ");
		break;
	case QL_M5:
		printf("���ڣ�M5 ");
		break;
	case QL_M10:
		printf("���ڣ�M10 ");
		break;
	case QL_M15:
		printf("���ڣ�M15 ");
		break;
	case QL_M30:
		printf("���ڣ�M30 ");
		break;
	case QL_M60:
		printf("���ڣ�M60 ");
		break;
	case QL_M120:
		printf("���ڣ�M120 ");
		break;
	case QL_D1:
		printf("���ڣ�D1 ");
		break;
	default:
		return 0;
		break;
	}

	switch (PriceType)
	{
	case QL_CLOSE:
		printf("���̼� ");
		break;
	case QL_OPEN:
		printf("���̼� ");
		break;
	case QL_HIGH:
		printf("��߼� ");
		break;
	case QL_LOW:
		printf("��ͼ� ");
		break;

	default:
		return 0;
		break;
	}
	printf("\n");




	TA_Real * DataArr = new TA_Real[number + ref];
	memset(DataArr, 0, sizeof(TA_Real)*(number + ref));


	return 1;
	/*

	//����2017.1.1

	//DataArrδ���ֵ
	if (!CxHashList->GetDataArr(InstrumentID, PriceType, periodtype, DataArr))
	{
		printf("û�ж��ĸ���������\n");
		delete[]DataArr;
		DataArr = NULL;
		return -1;
	}
	*/


	int retCode = TA_Initialize();
	if (retCode != TA_SUCCESS)
	{
		printf("\n��ʼ��ָ���ʧ��\n");
		return -1;
	}

	//printf("MD����ָ�����\n");

	// ��Զ��ʱ��
	/*TA_Real    closePrice[50] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50 };

	*/
	//0  29  1 30  15.5

	//20  49  21 50 71/2=30.5

	/*
	, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
	81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34 };

	*/
	TA_Real    indata[50] = { 0 };// = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
								  //41,42,43,44,45,46,47,48,49,50 };

								  //for (int i = 0; i < 50;i++)
								  //{
								  //indata[i] = closePrice[50 - i-1];

								  //}
	TA_Real  *  out = new TA_Real[number];
	memset(out, 0, sizeof(TA_Real)*number);

	//TA_Real  *  out_python = new TA_Real[number];

	TA_Integer outBeg;

	//TA_IntegeroutNbElement;

	/* ... initializeyour closing price here... */
	//double outNbElement[] = {34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56};
	int outNbElement = 0;
	//retCode = TA_MA(0, 50,&closePrice[0],30, TA_MAType_SMA,&outBeg, &outNbElement, &out[0]);


	//��ʼ ���� ����ֵ   30����                   �����ʼ    ����      �����������      
	//retCode = TA_MA(ref, ref + 50, DataArr, number, TA_MAType_SMA, &outBeg, &outNbElement, out);
	//retCode = TA_MA(ref, ref + number, &closePrice[0], number, TA_MAType_SMA, &outBeg, &outNbElement, out);
	retCode = TA_RSI(ref, ref + number, DataArr, number, &outBeg, &outNbElement, out);

	//retCode = TA_MA(ref, ref + 50, &indata[0], 30, TA_MAType_SMA, &outBeg, &outNbElement, out);
	/* The output isdisplayed here */

	//for (int i = 0; i < outNbElement - 1; i++)
	//{
	//���������  ���Ѿ���PYTHON����� printf("�� %d �� MAֵ = %f\n", number - (outBeg + ref + 1), out[ref]);	
	//}
	delete[]DataArr;
	DataArr = NULL;


	//int retValue = genCode(1, 1);

	retCode = TA_Shutdown();
	if (retCode != TA_SUCCESS)
	{
		printf("Shutdown failed (%d)\n", retCode);
	}
	double result = (double)(out[ref]);
	delete[]out;
	out = NULL;

	return result;
}

/*
TA_RetCode TA_MA(int    startIdx,
int    endIdx,
const double inReal[],

int           optInTimePeriod, // From 1 to 100000
TA_MAType     optInMAType,

int          *outBegIdx,
int          *outNBElement,
double        outReal[]);


TA_RetCode TA_RSI(int    startIdx,
int    endIdx,

const double inReal[],

int           optInTimePeriod, // From 2 to 100000

int          *outBegIdx,
int          *outNBElement,
double        outReal[]);


TA_RetCode TA_SAR(int    startIdx,
	int    endIdx,


	const double inHigh[],
	const double inLow[],

	double        optInAcceleration, // From 0 to TA_REAL_MAX //���ٶ� 
	double        optInMaximum, // From 0 to TA_REAL_MAX  //���ٶ����ֵ


	int          *outBegIdx,
	int          *outNBElement,
	double        outReal[]);
*/

double SAR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number, double step,double maxvalue)
{
	//printf("MA���� %s periodtype[%d] PriceType[%d] number[%d]\n", contract, periodtype, PriceType, number);
	//printf("MA���� [%s][%d]", InstrumentID, number);

	//int number = max(number1, number2);

	switch (periodtype)
	{
		//case QL_ALL:
		//break;
	case QL_M1:
		printf("���ڣ�M1 ");
		break;
	case QL_M3:
		printf("���ڣ�M3 ");
		break;
	case QL_M5:
		printf("���ڣ�M5 ");
		break;
	case QL_M10:
		printf("���ڣ�M10 ");
		break;
	case QL_M15:
		printf("���ڣ�M15 ");
		break;
	case QL_M30:
		printf("���ڣ�M30 ");
		break;
	case QL_M60:
		printf("���ڣ�M60 ");
		break;
	case QL_M120:
		printf("���ڣ�M120 ");
		break;
	case QL_D1:
		printf("���ڣ�D1 ");
		break;
	default:
		return 0;
		break;
	}

	switch (PriceType)
	{
	case QL_CLOSE:
		printf("���̼� ");
		break;
	case QL_OPEN:
		printf("���̼� ");
		break;
	case QL_HIGH:
		printf("��߼� ");
		break;
	case QL_LOW:
		printf("��ͼ� ");
		break;

	default:
		return 0;
		break;
	}
	printf("\n");




	TA_Real * DataArr_High = new TA_Real[number + ref];
	memset(DataArr_High, 0, sizeof(TA_Real)*(number + ref));

	TA_Real * DataArr_Low = new TA_Real[number + ref];
	memset(DataArr_Low, 0, sizeof(TA_Real)*(number + ref));
	return 1;


	/*
	����2017.1.1
	//DataArrδ���ֵ
	if (!CxHashList->GetDataArr(InstrumentID, PriceType, periodtype, DataArr_High))
	{
		printf("û�ж��ĸ���������\n");
		delete[]DataArr_High;
		DataArr_High = NULL;
		return -1;
	}




	//DataArrδ���ֵ
	if (!CxHashList->GetDataArr(InstrumentID, PriceType, periodtype, DataArr_Low))
	{
		printf("û�ж��ĸ���������\n");
		delete[]DataArr_Low;
		DataArr_Low = NULL;
		return -1;
	}
	*/



	int retCode = TA_Initialize();
	if (retCode != TA_SUCCESS)
	{
		printf("\n��ʼ��ָ���ʧ��\n");
		return -1;
	}

	//printf("MD����ָ�����\n");

	// ��Զ��ʱ��
	/*TA_Real    closePrice[50] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50 };

	*/
	//0  29  1 30  15.5

	//20  49  21 50 71/2=30.5

	/*
	, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
	81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34 };

	*/
	TA_Real    indata[50] = { 0 };// = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
								  //41,42,43,44,45,46,47,48,49,50 };

								  //for (int i = 0; i < 50;i++)
								  //{
								  //indata[i] = closePrice[50 - i-1];

								  //}
	TA_Real  *  out = new TA_Real[number];
	memset(out, 0, sizeof(TA_Real)*number);

	//TA_Real  *  out_python = new TA_Real[number];

	TA_Integer outBeg;

	//TA_IntegeroutNbElement;

	/* ... initializeyour closing price here... */
	//double outNbElement[] = {34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56};
	int outNbElement = 0;
	//retCode = TA_MA(0, 50,&closePrice[0],30, TA_MAType_SMA,&outBeg, &outNbElement, &out[0]);


	//��ʼ ���� ����ֵ   30����                   �����ʼ    ����      �����������      
	//retCode = TA_MA(ref, ref + 50, DataArr, number, TA_MAType_SMA, &outBeg, &outNbElement, out);
	//retCode = TA_MA(ref, ref + number, &closePrice[0], number, TA_MAType_SMA, &outBeg, &outNbElement, out);
	retCode = TA_SAR(ref, ref + number, DataArr_High, DataArr_Low, step, maxvalue, &outBeg, &outNbElement, out);

	//retCode = TA_MA(ref, ref + 50, &indata[0], 30, TA_MAType_SMA, &outBeg, &outNbElement, out);
	/* The output isdisplayed here */

	//for (int i = 0; i < outNbElement - 1; i++)
	//{
	//���������  ���Ѿ���PYTHON����� printf("�� %d �� MAֵ = %f\n", number - (outBeg + ref + 1), out[ref]);	
	//}
	delete[]DataArr_High;
	DataArr_High = NULL;
	delete[]DataArr_Low;
	DataArr_Low = NULL;

	//int retValue = genCode(1, 1);

	retCode = TA_Shutdown();
	if (retCode != TA_SUCCESS)
	{
		printf("Shutdown failed (%d)\n", retCode);
	}
	double result = (double)(out[ref]);
	delete[]out;
	out = NULL;

	return result;
}


double MACD(const char *InstrumentID, int periodtype, int PriceType, int ref, int number1, int number2, int number3)
{
	//printf("MA���� %s periodtype[%d] PriceType[%d] number[%d]\n", contract, periodtype, PriceType, number);


	printf("MACD����[%s][%d][%d][%d]", InstrumentID, number1, number2, number3);

	switch (periodtype)
	{
		//case QL_ALL:
		//break;
	case QL_M1:
		printf("���ڣ�M1 ");
		break;
	case QL_M3:
		printf("���ڣ�M3 ");
		break;
	case QL_M5:
		printf("���ڣ�M5 ");
		break;
	case QL_M10:
		printf("���ڣ�M10 ");
		break;
	case QL_M15:
		printf("���ڣ�M15 ");
		break;
	case QL_M30:
		printf("���ڣ�M30 ");
		break;
	case QL_M60:
		printf("���ڣ�M60 ");
		break;
	case QL_M120:
		printf("���ڣ�M120 ");
		break;
	case QL_D1:
		printf("���ڣ�D1 ");
		break;
	default:
		return 0;
		break;
	}

	switch (PriceType)
	{
	case QL_CLOSE:
		printf("���̼� ");
		break;
	case QL_OPEN:
		printf("���̼� ");
		break;
	case QL_HIGH:
		printf("��߼� ");
		break;
	case QL_LOW:
		printf("��ͼ� ");
		break;

	default:
		return 0;
		break;
	}
	printf("\n");


	//printf("MD����ָ�����\n");

	// ��Զ��ʱ��
	//TA_Real    closePrice[50] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		//41,42,43,44,45,46,47,48,49,50 };
	int number = max(number1, number2) + number3;

	TA_Real * DataArr = new TA_Real[number + ref];
	memset(DataArr, 0, sizeof(TA_Real)*(number + ref));


	return 1;
	/*
	//����2017.1.1
	//DataArrδ���ֵ
	if (!CxHashList->GetDataArr(InstrumentID, PriceType, periodtype, DataArr))
	{
		printf("û�ж��ĸ���������\n");
		delete[]DataArr;
		DataArr = NULL;
		return -1;
	}

	*/


	int retCode = TA_Initialize();
	if (retCode != TA_SUCCESS)
	{
		printf("\n��ʼ��ָ���ʧ��\n");
		return -1;
	}
	//0  29  1 30  15.5

	//20  49  21 50 71/2=30.5

	/*
	, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
	81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34 };

	*/
	TA_Real    indata[50] = { 0 };// = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
								  //41,42,43,44,45,46,47,48,49,50 };

								  //for (int i = 0; i < 50;i++)
								  //{
								  //indata[i] = closePrice[50 - i-1];

								  //}
	TA_Real  *  outMACD = new TA_Real[number1];
	TA_Real  *  outMACDSignal = new TA_Real[number1];
	TA_Real  *  outMACDHist = new TA_Real[number1];

	memset(outMACD, 0, sizeof(TA_Real)*number1);
	memset(outMACDSignal, 0, sizeof(TA_Real)*number1);
	memset(outMACDHist, 0, sizeof(TA_Real)*number1);
	//TA_Real  *  out_python = new TA_Real[number];

	TA_Integer outBeg;

	//TA_IntegeroutNbElement;

	/* ... initializeyour closing price here... */
	//double outNbElement[] = {34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56};
	int outNbElement = 0;
	//retCode = TA_MA(0, 50,&closePrice[0],30, TA_MAType_SMA,&outBeg, &outNbElement, &out[0]);


	//��ʼ ���� ����ֵ   30����                   �����ʼ    ����      �����������      
	//retCode = TA_MA(ref, ref + 50, DataArr, number, TA_MAType_SMA, &outBeg, &outNbElement, out);
	/*
	TA_RetCode TA_MA(int    startIdx,
		int    endIdx,
		const double inReal[],
		int           optInTimePeriod, // From 1 to 100000 
		TA_MAType     optInMAType,
		int          *outBegIdx,
		int          *outNBElement,
		double        outReal[]);

	TA_RetCode TA_MACD(int    startIdx,
		int    endIdx,
		const double inReal[],
		int           optInFastPeriod, // From 2 to 100000 
		int           optInSlowPeriod, // From 2 to 100000 
		int           optInSignalPeriod, // From 1 to 100000 
		int          *outBegIdx,
		int          *outNBElement,
		double        outMACD[],
		double        outMACDSignal[],
		double        outMACDHist[]);
	*/
	//retCode = TA_MA  (ref, ref + number, &closePrice[0], number, TA_MAType_SMA, &outBeg, &outNbElement, out);

	retCode = TA_MACD(ref, ref + number1, DataArr, number1,number2,number3, &outBeg, &outNbElement, outMACD, outMACDSignal, outMACDHist);
	//retCode = TA_MA(ref, ref + 50, &indata[0], 30, TA_MAType_SMA, &outBeg, &outNbElement, out);
	/* The output isdisplayed here */

	//for (int i = 0; i < outNbElement - 1; i++)
	//{
	//���������  ���Ѿ���PYTHON����� printf("�� %d �� MAֵ = %f\n", number - (outBeg + ref + 1), out[ref]);	
	//}
	delete[]DataArr;
	DataArr = NULL;


	//int retValue = genCode(1, 1);

	retCode = TA_Shutdown();
	if (retCode != TA_SUCCESS)
	{
		printf("Shutdown failed (%d)\n", retCode);
	}
	double result = (double)(outMACD[ref]);
	delete[]outMACD;
	delete[]outMACDSignal;
	delete[]outMACDHist;
	outMACD = NULL;
	outMACDSignal = NULL;
	outMACDHist = NULL;
	return result;
}






//�������
double MAs(const char *InstrumentID, int periodtype, int PriceType, int ref, int number)
{
	//printf("MA���� %s periodtype[%d] PriceType[%d] number[%d]\n", contract, periodtype, PriceType, number);
	printf("MA���� [%s] number[%d]", InstrumentID, number);

	switch (periodtype)
	{
		//case QL_ALL:
		//break;
	case QL_M1:
		printf("���ڣ�M1 ");
		break;
	case QL_M3:
		printf("���ڣ�M3 ");
		break;
	case QL_M5:
		printf("���ڣ�M5 ");
		break;
	case QL_M10:
		printf("���ڣ�M10 ");
		break;
	case QL_M15:
		printf("���ڣ�M15 ");
		break;
	case QL_M30:
		printf("���ڣ�M30 ");
		break;
	case QL_M60:
		printf("���ڣ�M60 ");
		break;
	case QL_M120:
		printf("���ڣ�M120 ");
		break;
	case QL_D1:
		printf("���ڣ�D1 ");
		break;
	default:
		return 0;
		break;
	}

	switch (PriceType)
	{
	case QL_CLOSE:
		printf("���̼� ");
		break;
	case QL_OPEN:
		printf("���̼� ");
		break;
	case QL_HIGH:
		printf("��߼� ");
		break;
	case QL_LOW:
		printf("��ͼ� ");
		break;

	default:
		return 0;
		break;
	}
	printf("\n");





	int retCode = TA_Initialize();
	if (retCode != TA_SUCCESS)
	{
		printf("\n��ʼ��ָ���ʧ��\n");
		return -1;
	}

	printf("MD����ָ�����\n");

	// ��Զ��ʱ��
	TA_Real    closePrice[50] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50 };


	//0  29  1 30  15.5

	//20  49  21 50 71/2=30.5

	/*
	, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
	81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34,
	34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56,34,34,32,34,34 };

	*/
	TA_Real    indata[50] = { 0 };// = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
								  //41,42,43,44,45,46,47,48,49,50 };

	for (int i = 0; i < 50; i++)
	{
		indata[i] = closePrice[50 - i - 1];

	}



	TA_Real  *  out = new TA_Real[number];

	TA_Real  *  out_python = new TA_Real[number];

	TA_Integer outBeg;

	//TA_IntegeroutNbElement;

	/* ... initializeyour closing price here... */
	//double outNbElement[] = {34,34,56,21,33,45,567,78,8,9,12,34,55,66,89,111,34,56,78,22,0,34,35,36,37,78,34,34,33,22,345,64,3,34,56};
	int outNbElement = 0;
	//retCode = TA_MA(0, 50,&closePrice[0],30, TA_MAType_SMA,&outBeg, &outNbElement, &out[0]);
	retCode = TA_MA(0, 50, indata, 30, TA_MAType_SMA, &outBeg, &outNbElement, out);
	/* The output isdisplayed here */
	//printf("new��");
	for (int i = 0; i < outNbElement - 1; i++)
	{

		//printf("�� %d �� MAֵ = %f\n", 50 - (outBeg + i + 1), out[i]);

		printf("�� %d �� MAֵ = %f\n", 50 - (outBeg + outNbElement - 1 - i), out[outNbElement - 2 - i]);

		out_python[50 - (outBeg + outNbElement - 1 - i)] = out[outNbElement - 2 - i];

	}



	//int retValue = genCode(1, 1);

	retCode = TA_Shutdown();
	if (retCode != TA_SUCCESS)
	{
		printf("Shutdown failed (%d)\n", retCode);
	}
	return 1;
}





bool QuickLib_MD_End()
{

	//�ٽ���
	DeleteCriticalSection(&g_csdata);
	for (int i = 0; i < amount; ++i)
	{
		delete [](ppInstrumentID[i]);
		//delete data[i];
		delete depthdata[i];
	}
	return true;
}


void *GetData(int i)
{
	if (gStatus)
	{
		return NULL;
	}
	if (i < 0 || (i >= (int)gMarket.size()))
	{
		return NULL;
	}else
	{
		//return data[i];
		return depthdata[i];
	}
}

int GetInstrumentNum()
{
	return gMarket.size();
}

int IsInitOK()
{
	return gMDSpi.IsInitOK();
}



char *  GetApiVersion()
{

	return gMDSpi.GetApiVersion();

}


TThostFtdcInstrumentIDTypeStruct InstrumentStruct;
char *  GetCmdContent_Tick()
{
	//_snprintf_s(ins, sizeof(ins), sizeof(ins), "%s", "ag1706");
	//return ins;
	if (ticknamelist.size() > 0)
	{
		memset(&InstrumentStruct, 0, sizeof(TThostFtdcInstrumentIDTypeStruct));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = errlist.begin()->ErrorID;
		memcpy_s(InstrumentStruct.Instrument, sizeof(TThostFtdcInstrumentIDTypeStruct), ticknamelist.begin()->Instrument, sizeof(TThostFtdcInstrumentIDType));

		ticknamelist.erase(ticknamelist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return InstrumentStruct.Instrument;
	}
	else
	{
		return NULL;
	}

}


CThostFtdcRspInfoField Error;
void *  GetCmdContent_Error()
{
	if (errorlist.size() > 0)
	{
		memset(&Error, 0, sizeof(CThostFtdcRspInfoField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		Error.ErrorID = errorlist.begin()->ErrorID;
		memcpy_s(Error.ErrorMsg, sizeof(Error.ErrorMsg), errorlist.begin()->ErrorMsg, sizeof(Error.ErrorMsg));
		errorlist.erase(errorlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return  &Error;
	}
	else
	{
		return NULL;
	}
}

//���Ļص�
CThostFtdcSpecificInstrumentField submarket;
void *  GetCmdContent_SubMarketData()
{
	if (subMarketlist.size() > 0)
	{
		memset(&submarket, 0, sizeof(CThostFtdcSpecificInstrumentField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		memcpy_s(submarket.InstrumentID, sizeof(submarket.InstrumentID), subMarketlist.begin()->InstrumentID, sizeof(submarket.InstrumentID));
		subMarketlist.erase(subMarketlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return  &submarket;
	}
	else
	{
		return NULL;
	}
}
//�˶��Ļص�
CThostFtdcSpecificInstrumentField unsubmarket;
void *  GetCmdContent_UnSubMarketData()
{
	if (unsubMarketlist.size() > 0)
	{
		memset(&unsubmarket, 0, sizeof(CThostFtdcSpecificInstrumentField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);
		memcpy_s(unsubmarket.InstrumentID, sizeof(unsubmarket.InstrumentID), unsubMarketlist.begin()->InstrumentID, sizeof(unsubmarket.InstrumentID));
		unsubMarketlist.erase(unsubMarketlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return  &unsubmarket;
	}
	else
	{
		return NULL;
	}
}

//��¼�ɹ�
CThostFtdcRspUserLoginField  logindata;
void *GetCmdContent_LoginScuess()
{
	if (loginlist.size() > 0)
	{
		memset(&logindata, 0, sizeof(CThostFtdcRspUserLoginField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//TD��ֲ���ģ�Ҫ����ֶ��Ƿ��Ǻ�
		memcpy_s(logindata.TradingDay, sizeof(TThostFtdcDateType), loginlist.begin()->TradingDay, sizeof(TThostFtdcDateType));
		memcpy_s(logindata.LoginTime, sizeof(TThostFtdcTimeType), loginlist.begin()->LoginTime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.BrokerID, sizeof(TThostFtdcBrokerIDType), loginlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
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


		//printf("rc++ %s [%s][%s][%s][%d]\n",
		//logindata->BrokerID, logindata->CZCETime, logindata->DCETime, logindata->FFEXTime, logindata->FrontID

		//);

		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return &logindata;
	}
	else
	{
		return NULL;
	}
}


//��¼ʧ��
CThostFtdcRspUserLoginField   logindatafailer;// = new CThostFtdcRspUserLoginField;
void *GetCmdContent_LoginFailer()
{
	if (loginfailelist.size() > 0)
	{
		memset(&logindata, 0, sizeof(CThostFtdcRspUserLoginField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//TD��ֲ���ģ�Ҫ����ֶ��Ƿ��Ǻ�
		memcpy_s(logindatafailer.TradingDay, sizeof(TThostFtdcDateType), loginfailelist.begin()->TradingDay, sizeof(TThostFtdcDateType));
		memcpy_s(logindatafailer.LoginTime, sizeof(TThostFtdcTimeType), loginfailelist.begin()->LoginTime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindatafailer.BrokerID, sizeof(TThostFtdcBrokerIDType), loginfailelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(logindatafailer.UserID, sizeof(TThostFtdcUserIDType), loginfailelist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		memcpy_s(logindatafailer.SystemName, sizeof(TThostFtdcSystemNameType), loginfailelist.begin()->SystemName, sizeof(TThostFtdcSystemNameType));
		logindatafailer.FrontID = loginfailelist.begin()->FrontID;
		logindatafailer.SessionID = loginfailelist.begin()->SessionID;
		memcpy_s(logindatafailer.MaxOrderRef, sizeof(TThostFtdcOrderRefType), loginfailelist.begin()->MaxOrderRef, sizeof(TThostFtdcOrderRefType));

		memcpy_s(logindatafailer.SHFETime, sizeof(TThostFtdcTimeType), loginfailelist.begin()->SHFETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindatafailer.DCETime, sizeof(TThostFtdcTimeType), loginfailelist.begin()->DCETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindatafailer.CZCETime, sizeof(TThostFtdcTimeType), loginfailelist.begin()->CZCETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindatafailer.FFEXTime, sizeof(TThostFtdcTimeType), loginfailelist.begin()->FFEXTime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindatafailer.INETime, sizeof(TThostFtdcTimeType), loginfailelist.begin()->INETime, sizeof(TThostFtdcTimeType));
		loginfailelist.erase(loginfailelist.begin());


		//printf("rc++ %s [%s][%s][%s][%d]\n",
		//logindata->BrokerID, logindata->CZCETime, logindata->DCETime, logindata->FFEXTime, logindata->FrontID

		//);

		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return &logindatafailer;
	}
	else
	{
		return NULL;
	}
}

//�ǳ�
CThostFtdcUserLogoutField   loginoutdata;// = new CThostFtdcRspUserLoginField;
void *GetCmdContent_LoginOut()
{
	if (loginoutlist.size() > 0)
	{
		memset(&loginoutdata, 0, sizeof(CThostFtdcUserLogoutField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//TD��ֲ���ģ�Ҫ����ֶ��Ƿ��Ǻ�
		memcpy_s(loginoutdata.BrokerID, sizeof(TThostFtdcBrokerIDType), loginoutlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(loginoutdata.UserID, sizeof(TThostFtdcUserIDType), loginoutlist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		loginoutlist.erase(loginoutlist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return &loginoutdata;
	}
	else
	{
		return NULL;
	}
}

//ѯ��
CThostFtdcForQuoteRspField   forquotedata;// = new CThostFtdcRspUserLoginField;
void *GetCmdContent_Forquote()
{
	if (forquotelist.size() > 0)
	{
		memset(&forquotedata, 0, sizeof(CThostFtdcForQuoteRspField));
		//�ٽ���
		EnterCriticalSection(&g_csdata);

		//TD��ֲ���ģ�Ҫ����ֶ��Ƿ��Ǻ�
		memcpy_s(forquotedata.TradingDay, sizeof(TThostFtdcDateType), forquotelist.begin()->TradingDay, sizeof(TThostFtdcDateType));
		memcpy_s(forquotedata.InstrumentID, sizeof(TThostFtdcInstrumentIDType), forquotelist.begin()->InstrumentID, sizeof(TThostFtdcInstrumentIDType));
		memcpy_s(forquotedata.ForQuoteSysID, sizeof(TThostFtdcOrderSysIDType), forquotelist.begin()->ForQuoteSysID, sizeof(TThostFtdcOrderSysIDType));
		memcpy_s(forquotedata.ForQuoteTime, sizeof(TThostFtdcTimeType), forquotelist.begin()->ForQuoteTime, sizeof(TThostFtdcTimeType));
		memcpy_s(forquotedata.ActionDay, sizeof(TThostFtdcDateType), forquotelist.begin()->ActionDay, sizeof(TThostFtdcDateType));
		memcpy_s(forquotedata.ExchangeID, sizeof(TThostFtdcExchangeIDType), forquotelist.begin()->ExchangeID, sizeof(TThostFtdcExchangeIDType));
		forquotelist.erase(forquotelist.begin());
		//�ٽ���
		LeaveCriticalSection(&g_csdata);
		return &forquotedata;
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

char *  GetTradingDay()
{
	return gMDSpi.GetTradingDay();
}
void   RegisterFront(char *pszFrontAddress)
{
	return gMDSpi.RegisterFront(pszFrontAddress);
}

void QUCIKLIB_MD_API RegisterNameServer(char *pszNsAddress)
{
	return gMDSpi.RegisterNameServer(pszNsAddress);
}

int ReqUserLogin()
{
	return gMDSpi.ReqUserLogin();
}

int ReqUserLogout()
{
	return gMDSpi.ReqUserLogout();
}

bool  AddPeriodType2(const char *InstrumentID, int  periodtype)
{
	std::hash_map<string, GuestOnlineHash>::iterator it;
	it = mapData.find(InstrumentID);
	if (it == mapData.end())
	{
		printf("*************û�ҵ��ú�Լ��%s\n", InstrumentID);
		//GuestOnlineHash value;
		//InitGuestOnlineHash(&value);
		//mapData.insert(std::make_pair(InstrumentID, value));
		//ClearGuestOnlineHash(&value);
		//it = mapData.find(InstrumentID);
		return 0;
	}
	else
	{
		GuestOnlineHash * q = &(it->second);
		switch (periodtype)
		{
		case QL_ALL:
			q->period_M1 = true;
			q->period_M3 = true;
			q->period_M5 = true;
			q->period_M10 = true;
			q->period_M15 = true;
			q->period_M30 = true;
			q->period_M60 = true;
			q->period_D1 = true;
			printf("%s����M1,M3,M5,M10,M15,M30,M60,D1����\n", InstrumentID);
			break;
		case QL_M1:
			q->period_M1 = true;
			printf("%s����M1����\n", InstrumentID);
			break;
		case QL_M3:
			q->period_M3 = true;
			printf("%s����M3����\n", InstrumentID);
			break;
		case QL_M5:
			q->period_M5 = true;
			printf("%s����M5����\n", InstrumentID);
			break;

		case QL_M10:
			q->period_M10 = true;
			printf("%s����M10����\n", InstrumentID);
			break;

		case QL_M15:
			q->period_M15 = true;
			printf("%s����M15����\n", InstrumentID);
			break;

		case QL_M30:
			q->period_M30 = true;
			printf("%s����M30����\n", InstrumentID);
			break;

		case QL_M60:
			q->period_M60 = true;
			printf("%s����M60����\n", InstrumentID);
			break;

		case QL_M120:
			q->period_M120 = true;
			printf("%s����M120����\n", InstrumentID);
			break;

		case QL_D1:
			q->period_D1 = true;
			printf("%s����D1����\n", InstrumentID);
			break;
		}
	}
	return true;
}

void AddPeriod(const char *InstrumentID, int periodtype,bool printfdata)
{

	if (printfdata)
	{
		printf("���[%s]����(��Tick�����������ݹ�ָ�����)��", InstrumentID);
	
	   switch (periodtype)
	  {
	  case QL_ALL:
		  printf("M1��M3��M5��M10��M15��M30��M60��M120��D1 ");
		  break;
	  case QL_M1:
		  printf("M1 ");
		  break;
	  case QL_M3:
		  printf("M3 ");
		  //gM3data = new double[500];
		  //memset(gM3data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gM3;
		  break;
	  case QL_M5:
		  printf("M5 ");
		  //gM5data = new double[500];
		  //memset(gM5data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gM5;
		  break;
	  case QL_M10:
		  printf("M10 ");
		  //gM10data = new double[500];
		  //memset(gM10data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gM10;
		  break;
	  case QL_M15:
		  printf("M15 ");
		  //gM15data = new double[500];
		  //memset(gM15data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gM15;
		  break;
	  case QL_M30:
		  printf("M30 ");
		  //gM30data = new double[500];
		  //memset(gM30data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gM30;
		  break;
	  case QL_M60:
		  printf("M60 ");
		  //gM60data = new double[500];
		  //memset(gM60data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gM60;
		  break;
	  case QL_M120:
		  printf("M120 ");
		  //gM120data = new double[500];
		  //memset(gM120data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gM120;
		  break;
	  case QL_D1:
		  printf("���ڣ�D1 ");
		  //gD1data = new double[500];
		  //memset(gD1data, 0, 500 * sizeof(double));
		  //std::map<std::string, int> gD1;
		  break;
	  default:
		  return;
		  break;
	  }
	}
	AddPeriodType2(InstrumentID, periodtype);
}


void   AddStopMonitor(const char *InstrumentID, int OrderRef, int mode, double percent)
{
	printf("������ֹ����(������δ��ʾ�����ڷ�װ)������ %s ���� %d ģʽ %d ֹ����ֵ�ٷֱ�%0.02f\n", InstrumentID, OrderRef, mode, percent);
}


void   DeleteStopMonitor(const char *InstrumentID, int OrderRef, int mode, double percent)
{
	printf("ɾ��ֹ����(������δ��ʾ�����ڷ�װ)������ %s ���� %d ģʽ %d ֹ����ֵ�ٷֱ�%0.02f\n", InstrumentID, OrderRef, mode, percent);
}

double GetPeriodData(const char *InstrumentID, int periodtype, int PriceType, int ref)
{
	ref ++;
	std::hash_map<string, GuestOnlineHash>::iterator it;
	it = mapData.find(InstrumentID);
	if (it == mapData.end())
	{	    printf("*************û�ҵ��ú�Լ��%s\n", InstrumentID);
		//GuestOnlineHash value;
		//InitGuestOnlineHash(&value);
		//mapData.insert(std::make_pair(InstrumentID, value));
		//ClearGuestOnlineHash(&value);
		//it = mapData.find(InstrumentID);
	        return -1;
	}
	else
	{

		GuestOnlineHash * q = &(it->second);

		double dataarr = -1;
		 printf("�ҵ���Լ����%s %d %d %d\n",InstrumentID,   periodtype,   PriceType,   ref);
		{
			//printf("MA�ҵ�����\n");
			//if (pt)
			//{
			//for (int i = 0; i < PERIOD_NUM; i++)
			//{
			switch (periodtype)
				//switch (q->periodtype)
			{
			case QL_M1:
				//pstate = true;
				dataarr = (q->M1_close[ref]);
				break;
			case QL_M3:
				//pstate = true;
				dataarr = (q->M3_close[ref]);
				break;
			case QL_M5:
				//pstate = true;
				dataarr = (q->M5_close[ref]);
				break;

			case QL_M10:
				//pstate = true;
				dataarr = (q->M10_close[ref]);
				break;

			case QL_M15:
				//pstate = true;
				dataarr = (q->M15_close[ref]);
				break;

			case QL_M30:
				//pstate = true;
				dataarr = (q->M30_close[ref]);
				break;

			case QL_M60:
				//pstate = true;
				dataarr = (q->M60_close[ref]);
				break;

				//case QL_M120:
				//	pstate = true;
				//	dataarr = q->M120_close;
				//break;

				//case QL_D1:
				///	pstate = true;
				//	dataarr = q->D1_close;
				//	break;
			}
		}
		return dataarr;
	}
}

/*
void Log(const char *filename, const char *content)
{


	char str[256] = { 0 };
	strcat_s(str, 256, filename);

	//����ļ��Ƿ���ڣ��Ƿ���Ҫ�½��ı��ļ�
	ifstream inf;
	ofstream ouf;
	//inf.open(TickFileWritepaths[i], ios::out);
	inf.open(str, ios::out);
	//}

	//��¼TICK����
	ofstream o_file(content, ios::app);
	//if ( RunMode && ( check0 || check1 || check2) )

	//printf("xxxxxxxxxxxxxx%.06f\n",dbtoch(tick_data[id][1]));

	o_file << content << "\t" << endl;

	//else
	//{
	//o_file << dbtoch(tick_data[i][1]) << "\t" << tick_data[2] << "\t" << Millisecs << "\t" << tick_AskPrice1[i][0] << "\t" << tick_AskVolume1[i][0] << "\t" << tick_BidPrice1[i][0] << "\t" << tick_BidVolume1[i][0] << "\t" << tick_data[i][4] << "\t" << dbtoch(tick_Volume[i][0]) << "\t" << dbtoch(tick_OpenInterest[i][0])<< endl; //������д�뵽�ı��ļ���
	//}
	o_file.close();						//�ر��ļ�
}
*/

extern int savetickstate;// = 0;
void SaveTick(int index)
{
	if (index == 2)
	{
		CreateDirectoryA("TickData_Detail", NULL); //�����ļ���
		//gMDSpi.
			savetickstate = 2;
	}
	else if (index == 1)
	{
		CreateDirectoryA("TickData_Simple", NULL); //�����ļ���
		//gMDSpi.
			savetickstate = 1;
	}
}


/*
char * Read_Ini(const char * filename, const char * option, const char * key)
{

	char * temp = new char[50];
	//char temp[50] = {0};
	_snprintf_s(temp, sizeof(*temp), sizeof(*temp),"%s","zn1609");

	return  temp;
}

*/


void SetTitle(const char * title)
{

/*
CIniFile	cfgfile("./AllowSetTitle.ini");

int allow = cfgfile.ReadInteger("option", "allow", 1);
if (allow == 0)
{
	printf("AllowSetTitle.ini���ڣ���ֹ����title\n");
	return;
}

*/

//while(IsInDebugger())
//{
//return;
//break;
//}
 


	char newtitle[200] = {0};
	_snprintf_s(newtitle,sizeof(newtitle), sizeof(newtitle),"%s%s"," QuickLib_",title);

 
		SetConsoleTitle(newtitle);
 

}




void Log(const char * filename, const char * content)
{
	/*
	char str[200] = { 0 };
	strcat_s(str, 200, "TickData_Simple\\TickData_");
	strcat_s(str, 200, InstrumentID);
	strcat_s(str, 200, ".csv");

	*/



	//����ļ��Ƿ���ڣ��Ƿ���Ҫ�½��ı��ļ�
	ifstream inf;
	ofstream ouf;
	//inf.open(TickFileWritepaths[i], ios::out);
	inf.open(filename, ios::out);
	//}

	//��¼TICK����
	ofstream o_file(filename, ios::app);
	//if ( RunMode && ( check0 || check1 || check2) )

	//printf("xxxxxxxxxxxxxx%.06f\n",dbtoch(tick_data[id][1]));

	o_file << content <<  endl;

	//else
	//{
	//o_file << dbtoch(tick_data[i][1]) << "\t" << tick_data[2] << "\t" << Millisecs << "\t" << tick_AskPrice1[i][0] << "\t" << tick_AskVolume1[i][0] << "\t" << tick_BidPrice1[i][0] << "\t" << tick_BidVolume1[i][0] << "\t" << tick_data[i][4] << "\t" << dbtoch(tick_Volume[i][0]) << "\t" << dbtoch(tick_OpenInterest[i][0])<< endl; //������д�뵽�ı��ļ���
	//}
	o_file.close();						//�ر��ļ�
}


/*
void TestArr(int &numbers, int a)
{
	int *i = &(*&numbers);
	for (int j = 0; j<a; j++)
	{
		*i += j;
		i++;
	}
}
*/


void TestArr(char** pIpAddList)
{

	for (int i = 0; i < 10; i++)
	{
		char temp[20] = {0};
		sprintf_s(temp,20,"%d",i);
		strcpy(pIpAddList[i], temp);
	    //ipAddressΪIP��ַ
	
	}

}



void  SetRejectdataTime(double  begintime1, double endtime1, double begintime2, double endtime2, double begintime3, double endtime3, double begintime4, double endtime4)
{
	if (begintime1 < 0 || endtime1 < 0 || begintime2 < 0 || endtime2 < 0 || begintime3 < 0 || endtime3 < 0 || begintime4 < 0 || endtime4 < 0)
	{
		printf("���þ��������ʱ��α�����ڵ���0\n");
	}

	if (begintime1 != 100 && endtime1 != 100)
	{
		printf("[%0.06f ~ %0.06f]�������ݵ�ʱ���\n", begintime1, endtime1);
		gMDSpi.begintime1 = begintime1;
		gMDSpi.endtime1 = endtime1;
	}

	if (begintime2 != 100 && endtime2 != 100)
	{
		printf("[%0.06f ~ %0.06f]�������ݵ�ʱ���\n", begintime2, endtime2);
	    gMDSpi.begintime2 = begintime2;
	    gMDSpi.endtime2 = endtime2;
	}

	if (begintime3 != 100 && endtime3 != 100)
	{
		printf("[%0.06f ~ %0.06f]�������ݵ�ʱ���\n", begintime3, endtime3);
	  gMDSpi.begintime3 = begintime3;
	  gMDSpi.endtime3 = endtime3;

	}

	if (begintime3 != 100 && endtime3 != 100)
	{
		printf("[%0.06f ~ %0.06f]�������ݵ�ʱ���\n", begintime4, endtime4);
	  gMDSpi.begintime4 = begintime4;
	  gMDSpi.endtime4 = endtime4;
	}

}


 
bool allprintfstate = false; //�Ƿ��ӡ tick����

//bool allprintfstate = false; //�Ƿ��ӡ tick����
void QUCIKLIB_MD_API SetPrintState(bool printfstate)
{
	allprintfstate = printfstate;

}


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
		return SYSTEM_NETCONNECT_BREAK;
		break;

	case WAIT_OBJECT_0 + EID_OnFrontConnected:

		// The process identified by h[1] (hProcess2) terminated.
		return SYSTEM_NETCONNECT_SCUESS;
		break;

	case WAIT_OBJECT_0 + EID_OnRspUserLogin_Failer:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_LOGIN_DENIED;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogin_Scuess:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_LOGIN_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRtnDepthMarketData:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_NEWTICK;
		break;
	case WAIT_OBJECT_0 + EID_IsErrorRspInfo:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_SYSTEM_ERROR;
		break;
	case WAIT_OBJECT_0 + EID_OnRspSubMarketData:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_SUBCRIBE_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUnSubMarketData:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_UNSUBCRIBE_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogout:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_LOGINOUT_SCUESS;
		break;

	case WAIT_OBJECT_0 + EID_OnRspForQuote:

		// The process identified by h[2] (hProcess3) terminated.
		return SYSTEM_QRY_FORQUOTE;
		break;

		
	}
	//ResetEvent(hEvent);
	//SetEvent(hEvent);

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
	//SetEvent(hEvent);
	return SYSTEM_EMPTY;
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
	return cmdlist.size();
}

//int GetUnGetTickSize()
//{
	//return cmdlist.size();
//}

int  GetCmd()
{
	if (cmdlist.size() <= 0)
	{
		return  SYSTEM_EMPTY;
	}
	//return 
	//memcpy_s(StockData[stockid], sizeof(CSecurityFtdcL2TradeField), &(*cmdlist.begin()), sizeof(CSecurityFtdcL2TradeField));

	//printf("stockid:[%d]\n", stockid);
	/*
	///�ɽ���
	StockData[stockid]->TradeGroupID = cmdlist.begin()->TradeGroupID;
	///�ɽ����
	StockData[stockid]->TradeIndex = cmdlist.begin()->TradeIndex;
	///��ί�����
	StockData[stockid]->BuyIndex = cmdlist.begin()->BuyIndex;
	///����ί�����
	StockData[stockid]->SellIndex = cmdlist.begin()->SellIndex;
	///�ɽ�ʱ�䣨�룩
	_snprintf_s(StockData[stockid]->TradeTime, sizeof(TSecurityFtdcTimeType), sizeof(TSecurityFtdcTimeType), "%s", cmdlist.begin()->TradeTime);
	///����������
	_snprintf_s(StockData[stockid]->ExchangeID, sizeof(TSecurityFtdcExchangeIDType), sizeof(TSecurityFtdcExchangeIDType), "%s", cmdlist.begin()->ExchangeID);
	///��Լ����
	_snprintf_s(StockData[stockid]->InstrumentID, sizeof(TSecurityFtdcInstrumentIDType), sizeof(TSecurityFtdcInstrumentIDType), "%s", cmdlist.begin()->InstrumentID);
	///�ɽ��۸�
	StockData[stockid]->Price = cmdlist.begin()->Price;
	///�ɽ�����
	StockData[stockid]->Volume = cmdlist.begin()->Volume;
	///��������
	_snprintf_s(StockData[stockid]->OrderKind, sizeof(TSecurityFtdcOrderKindType), sizeof(TSecurityFtdcOrderKindType), "%s", cmdlist.begin()->OrderKind);
	///������
	_snprintf_s(StockData[stockid]->FunctionCode, sizeof(TSecurityFtdcFunctionCodeType), sizeof(TSecurityFtdcFunctionCodeType), "%s", cmdlist.begin()->FunctionCode);
	*/

	//memcpy_s(&(StockData[stockid]->data), sizeof(CSecurityFtdcL2TradeField_S), &cmdlist.begin(), sizeof(CSecurityFtdcL2TradeField_S));

	//StockData[stockid]->data.ExchangeID

	//printf("ԭʼ���� InstrumentID[%s] price[%0.02f]\n", cmdlist.begin()->InstrumentID, cmdlist.begin()->Price);


	//char temp[200] = { 0 };
	//_snprintf_s(temp,sizeof(temp),sizeof(temp),"%s||%d",)
	//printf("�������allow[%d] InstrumentID[%s] price[%0.02f]\n", StockData[stockid]->allow, StockData[stockid]->data.InstrumentID, StockData[stockid]->data.Price);
	//char * newdata = new char[31];
	//memset
	//_snprintf_s(&listname, sizeof(listname), sizeof(listname), "%s",cmdlist.begin()->Instrument);


	//memset(&listcmd, 0, sizeof(listcmd));
	//memcpy_s(&listcmd, sizeof(listcmd), cmdlist.begin()->cmd, sizeof(listcmd));
	//�ٽ���
	EnterCriticalSection(&g_csdata);
	int cmdtype = cmdlist.begin()->cmd;
	//�ٽ���
	//EnterCriticalSection(&g_csdata);
	//cmdlist.erase(cmdlist.begin());
	//LeaveCriticalSection(&g_csdata);
	//�ٽ���


	return cmdtype;

}



char listcmd[31] = { 0 };
char *   GetCmdContent()
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

