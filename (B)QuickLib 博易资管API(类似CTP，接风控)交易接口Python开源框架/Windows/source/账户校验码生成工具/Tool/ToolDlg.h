
// ReportToolDlg.h : ͷ�ļ�
//

#pragma once
#include "Aes.h"

class CReportToolDlg : public CDialogEx
{
// ����
public:

 

	//AES����
	int char2num(TCHAR ch);
	BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
	BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
	BSTR OnBAesEn(wchar_t *wText);
	BSTR OnBAesDe(wchar_t *wText);
	BSTR MoreStrOnBAesEn(CString leftstr);
	BSTR MoreStrOnBAesDe(CString leftstr);
	//AES����





	BOOL ReadConfigFile();

	CReportToolDlg(CWnd* pParent = NULL);	// ��׼���캯��
 
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORTTOOL_DIALOG };
#endif

	void OnTimer(UINT_PTR nIDEvent);


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	//bool DLL_Create();
 
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
