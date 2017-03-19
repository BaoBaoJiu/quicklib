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

#ifdef PYCTPMARKET_EXPORTS
#define QUCIKLIB_MD_API __declspec(dllexport)
#else
#define QUCIKLIB_MD_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif 
	//��ȡӲ����Ϣ
	//QUCIKLIB_MD_API char *  GetHardDiskId();
	//QUCIKLIB_MD_API char *  GetCPUInfo();
	//QUCIKLIB_MD_API char *  GetMacAddress();


	QUCIKLIB_MD_API char *  GetApiVersion();
	QUCIKLIB_MD_API char *  GetTradingDay();
	void QUCIKLIB_MD_API RegisterFront(char *pszFrontAddress);
	void QUCIKLIB_MD_API RegisterNameServer(char *pszNsAddress);

	
	QUCIKLIB_MD_API char *  GetCmdContent_Tick();
	QUCIKLIB_MD_API void *  GetCmdContent_Error();

	QUCIKLIB_MD_API void *  GetCmdContent_SubMarketData();
	QUCIKLIB_MD_API void *  GetCmdContent_UnSubMarketData();

	QUCIKLIB_MD_API void *  GetCmdContent_LoginScuess();
	QUCIKLIB_MD_API void *  GetCmdContent_LoginFailer();
	QUCIKLIB_MD_API void *  GetCmdContent_LoginOut();

	QUCIKLIB_MD_API void *  GetCmdContent_Forquote();
	/*

	 ///��ʼ��
	 ///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	 void QUCIKLIB_MD_API Init();

	///����ѯ�ۡ�
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	int QUCIKLIB_MD_API SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount);

	///�˶�ѯ�ۡ�
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	int QUCIKLIB_MD_API UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount);

	///ע�����ַ������û���Ϣ
	///@param pFensUserInfo���û���Ϣ��
	void QUCIKLIB_MD_API RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo);

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	 void QUCIKLIB_MD_API Release();



	 ///ע��ص��ӿ�
	 ///@param pSpi �����Իص��ӿ����ʵ��
	 void QUCIKLIB_MD_API RegisterSpi(CThostFtdcMdSpi *pSpi);
	 */
	 /////////////////////////////////////////
	//�û���¼����
	int QUCIKLIB_MD_API ReqUserLogin();
	//�û��ǳ�����
	int QUCIKLIB_MD_API ReqUserLogout();
	//ȡ������
	void QUCIKLIB_MD_API UnSubscribeMarketData(const char *InstrumentID);

	void QUCIKLIB_MD_API Subscribe(const char *InstrumentID);
	void QUCIKLIB_MD_API Subscribe1(const char *InstrumentID, int periodtype1);
	void QUCIKLIB_MD_API Subscribe2(const char *InstrumentID, int periodtype1, int periodtype2);
	void QUCIKLIB_MD_API Subscribe3(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3);
	void QUCIKLIB_MD_API Subscribe4(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4);
	void QUCIKLIB_MD_API Subscribe5(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5);
	void QUCIKLIB_MD_API Subscribe6(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6);
	void QUCIKLIB_MD_API Subscribe7(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6, int periodtype7);
	void QUCIKLIB_MD_API Subscribe8(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6, int periodtype7, int periodtype8);

    //ѯ��
	void QUCIKLIB_MD_API SubscribeForQuoteRsp(char *InstrumentID);


	

	////////////////////////////////////////////////////////////////////////
	void QUCIKLIB_MD_API SetPrintState(bool printfstate);

	int QUCIKLIB_MD_API GetCmd();
	QUCIKLIB_MD_API char * GetCmdContent();
	int QUCIKLIB_MD_API OnCmd();
	int QUCIKLIB_MD_API GetUnGetCmdSize();


	int QUCIKLIB_MD_API GetUnGetLogSize();
	QUCIKLIB_MD_API char * GetLog(); //�����־����

	void QUCIKLIB_MD_API SetRejectdataTime(double  begintime1,double endtime1,double begintime2,double endtime2, double begintime3, double endtime3, double begintime4, double endtime4);


	//void  QUCIKLIB_MD_API strategy1();

	//void QUCIKLIB_MD_API TestArr(int &numbers, int a);

	void QUCIKLIB_MD_API TestArr(char** pIpAddList);
	 


	void QUCIKLIB_MD_API SetTitle(const char * title);
	void QUCIKLIB_MD_API Log(const char * filename, const char * content);

	bool QUCIKLIB_MD_API ReadInstrument();



	void QUCIKLIB_MD_API SaveTick(int index);

 
 //QUCIKLIB_MD_API char * Read_Ini(const char * filename, const char * option, const char * key);


	//char  QUCIKLIB_MD_API Read_Ini(const char * filename, const char * option, const char * key);


	 

	//void QUCIKLIB_MD_API Log(const char *name,const char *content);



	//bool QUCIKLIB_MD_API SetInstrumentNumber(int number);//ȡ����

 
	void QUCIKLIB_MD_API AddPeriod(const char *InstrumentID, int periodtype, bool printfdata);

	void QUCIKLIB_MD_API AddStopMonitor(const char *InstrumentID, int OrderRef,int mode,double percent);

	void QUCIKLIB_MD_API DeleteStopMonitor(const char *InstrumentID, int OrderRef, int mode, double percent);
	
	double QUCIKLIB_MD_API GetPeriodData(const char *InstrumentID, int periodtype, int PriceType, int ref);

 

	double QUCIKLIB_MD_API MA(const char *InstrumentID, int periodtype,int PriceType,int ref,int number);
	double QUCIKLIB_MD_API RSI(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	//double QUCIKLIB_MD_API SAR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	double QUCIKLIB_MD_API SAR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number, double step, double maxvalue);

	double QUCIKLIB_MD_API MACD(const char *InstrumentID, int periodtype, int PriceType, int ref, int number1,int number2,int number3); 

	double QUCIKLIB_MD_API CCI(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	double QUCIKLIB_MD_API ATR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	//double QUCIKLIB_MD_API SAR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);



	//bool QUCIKLIB_MD_API CROSSUP(int price_Small0, int priceLong0, int priceSmall1, int priceLong1);

	//bool QUCIKLIB_MD_API CROSSDOWN(int priceSmall0, int priceLong0, int priceSmall1, int priceLong1);


	bool QUCIKLIB_MD_API CROSSUP(const char *InstrumentID, int indicators,int periodtype, int PriceType, int period1, int period2, bool printstate);

	bool QUCIKLIB_MD_API CROSSDOWN(const char *InstrumentID, int indicators, int periodtype, int PriceType, int period1, int period2, bool printstate);


    //����
	bool QUCIKLIB_MD_API CROSSUP_S(int strategyid, int periodtype, int PriceType, int period1, int period2);
	bool QUCIKLIB_MD_API CROSSDOWN_S(int strategyid, int periodtype, int PriceType, int period1, int period2);






	void QUCIKLIB_MD_API *GetData(int index);
	
	int QUCIKLIB_MD_API GetInstrumentNum();

	int QUCIKLIB_MD_API IsInitOK();

#ifdef __cplusplus
}
#endif