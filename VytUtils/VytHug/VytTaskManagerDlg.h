#pragma once

#include "SmartList.hpp"
#include "VytTaProcessDlg.h"
// VytTaskManagerDlg 对话框

class VytTaskManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaskManagerDlg)

public:
	VytTaskManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaskManagerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASKMANAGER };
#endif

private:
	int m_activeProcessIndex;
private:
	void ShowProcessInfo(E_ProcessInfo info = E_ProcessInfo::Thread);
	void UpdateProcesses();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_processes;
	virtual BOOL OnInitDialog();
	afx_msg void OnShowProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTrackProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTapThread();
	afx_msg void OnTapModule();
	afx_msg void OnTapHeap();
	afx_msg void OnTapTerminate();
	afx_msg void OnTapRefresh();
};
