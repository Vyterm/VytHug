#pragma once
#include "SmartList.hpp"

// VytWindowsDlg 对话框

class VytWindowsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytWindowsDlg)

public:
	VytWindowsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytWindowsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWS };
#endif

private:
	void UpdateWindows();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_windows;
	virtual BOOL OnInitDialog();
};
