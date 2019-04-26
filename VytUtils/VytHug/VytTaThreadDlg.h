#pragma once

#include "SmartList.hpp"
// VytTaThreadDlg 对话框

class VytTaThreadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaThreadDlg)

public:
	VytTaThreadDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaThreadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TA_THREAD };
#endif

private:
	int m_activeThreadIndex;

public:
	CString GetThreadStatus(DWORD threadID);
	void ShowThread(DWORD processID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_threads;
	virtual BOOL OnInitDialog();
	afx_msg void TrackThreadCommand(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTatSuspend();
	afx_msg void OnTatResume();
	afx_msg void OnTatTerminate();
};
