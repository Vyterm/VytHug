#pragma once
#include "SmartList.hpp"

// VytSoftwareDlg 对话框

class VytSoftwareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytSoftwareDlg)

public:
	VytSoftwareDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytSoftwareDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOFTWARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_softwares;
	virtual BOOL OnInitDialog();
};
