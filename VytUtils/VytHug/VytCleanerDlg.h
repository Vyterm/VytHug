﻿#pragma once
#include "SmartList.hpp"
#include <functional>
// VytCleanerDlg 对话框

class VytCleanerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytCleanerDlg)

public:
	VytCleanerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytCleanerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLEANER };
#endif

private:
	void RefreshFiles(std::function<bool(const CString&, WIN32_FIND_DATA&)> fileFilter = nullptr);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_path;
	vyt::SmartList m_filelist;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClViewpathbutton();
	afx_msg void OnBnClickedClScansys();
	afx_msg void OnBnClickedClScanexp();
	afx_msg void OnBnClickedClDroptrash();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
