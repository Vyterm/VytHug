#pragma once
#include "SmartList.hpp"

// VytServiceDlg 对话框

class VytServiceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytServiceDlg)

public:
	VytServiceDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytServiceDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVICE };
#endif

private:
	void UpdateServices();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_services;
	virtual BOOL OnInitDialog();
};
