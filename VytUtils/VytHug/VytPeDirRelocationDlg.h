﻿#pragma once

#include "VytPeDirectoryDlg.h"
// VytPeDirRelocationDlg 对话框

class VytPeDirRelocationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirRelocationDlg)

public:
	VytPeDirRelocationDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirRelocationDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_RELOCATION };
#endif

private:
	VytPeDirectoryDlg *m_dirDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_logedit;
	afx_msg void OnBnClickedPedrBeginprint();
};
