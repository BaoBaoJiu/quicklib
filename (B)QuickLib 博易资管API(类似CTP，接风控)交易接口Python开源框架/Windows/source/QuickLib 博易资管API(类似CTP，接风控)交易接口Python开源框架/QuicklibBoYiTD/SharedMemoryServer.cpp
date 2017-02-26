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
//���س������ݹ���
#include "SharedMemoryServer.h"


SharedMemoryServer::SharedMemoryServer(const char * code)
{

	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		code);                 // name of mapping object

	if (hMapFile == NULL)
	{
		//_tprintf(TEXT("Could not create file mapping object (%d).\n"),
		//	GetLastError());


		//CString temp;
		//temp.Format("Could not create file mapping object %d", GetLastError());
		//AfxMessageBox(temp);
		printf("Could not create file mapping object %d", GetLastError());
		failerstate = true;
		return;// true;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		//_tprintf(TEXT("Could not map view of file (%d).\n"),
		//	GetLastError());


		//CString temp;
		//temp.Format("Could not map view of file %d", GetLastError());
		//AfxMessageBox(temp);

		printf("Could not map view of file %d", GetLastError());

		CloseHandle(hMapFile);
		failerstate = true;
		return;// true;
	}

}


SharedMemoryServer::~SharedMemoryServer()
{

}





bool  SharedMemoryServer::CreateShareMemory(const char * code, const char * szMsg,int MsgLen)
{
	

	//CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	CopyMemory((PVOID)pBuf, szMsg, (MsgLen * sizeof(char)));
	//_getch();

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);
	 
	//printf("finish\n");

	//CString temp;
	//temp.Format("%s %s",code,szMsg);
	//AfxMessageBox(temp);

	//system("pause");
	printf("%s %s", code, szMsg);
 

	return false;
}