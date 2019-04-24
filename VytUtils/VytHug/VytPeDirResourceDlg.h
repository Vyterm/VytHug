#pragma once

#include "VytPeDirectoryDlg.h"
// VytPeDirResourceDlg 对话框

class VytPeDirResourceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirResourceDlg)

public:
	VytPeDirResourceDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirResourceDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_RESOURCE };
#endif

private:
	VytPeDirectoryDlg *m_dirDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
