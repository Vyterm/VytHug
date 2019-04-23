#pragma once

#include "SmartList.hpp"
// VytTaModuleDlg 对话框

class VytTaModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaModuleDlg)

public:
	VytTaModuleDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaModuleDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TA_MODULE };
#endif

public:
	void ShowModule(DWORD processID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_modules;
	virtual BOOL OnInitDialog();
};
