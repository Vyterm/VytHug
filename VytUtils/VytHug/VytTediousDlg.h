#pragma once

#include "SmartList.hpp"
#include "VytRegeditUtils.hpp"
#include <deque>
// VytTediousDlg 对话框

class VytTediousDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTediousDlg)

public:
	VytTediousDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTediousDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEDIOUS };
#endif

private:
	std::deque<vyt::RegeditUtils::BootstrapInfo> m_bootstrapInfos;
	int m_bootstrapIndex;
private:
	void CheckAdmin();
	void UpdateUtilization();
	void UpdateBootInfos();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CProgressCtrl m_cpuProgress;
	CProgressCtrl m_memoryProgress;
	CButton m_rootbutton;
	CString m_cleanHint;
	vyt::SmartList m_startups;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedTeCleanmemory();
	afx_msg void OnBnClickedTePoweroff();
	afx_msg void OnBnClickedTeRestart();
	afx_msg void OnBnClickedTeLogoff();
	afx_msg void OnBnClickedTeDormant();
	afx_msg void OnBnClickedTeSleep();
	afx_msg void OnBnClickedTeLock();
	afx_msg void OnBnClickedTePowerraising();
	afx_msg void OnRclickTeStartuplist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTeInsertboot();
	afx_msg void OnTeDeleteboot();
	afx_msg void OnTeRefreshboot();
};
