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

//#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>


#define BUF_SIZE 40960

//TCHAR szName[] = TEXT("Global\\MyFileMappingObject");
//TCHAR szMsg[] = TEXT("����");



class SharedMemoryServer
{
public:
    //static char szName[] =  ("Global\\MyFileMappingObject");
   // static char szMsg[] =  ("����");

	//char szName[20];// = ("Global\\MyFileMappingObject");
	//char szMsg[20];// = ("����");

	bool failerstate;

	HANDLE hMapFile;
	LPCTSTR pBuf;

	SharedMemoryServer(const char * code);

	~SharedMemoryServer();


	bool  CreateShareMemory(const char * data, const char * szMsg, int MsgLen);


};