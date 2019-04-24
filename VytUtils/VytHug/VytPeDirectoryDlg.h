#pragma once

#include "SmartTab.hpp"
// VytPeDirectoryDlg 对话框

class VytPeDirectoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirectoryDlg)

public:
	VytPeDirectoryDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirectoryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PE_DIRECTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartTab m_directoryTab;
	virtual BOOL OnInitDialog();
};
