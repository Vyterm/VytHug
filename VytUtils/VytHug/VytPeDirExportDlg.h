#pragma once

#include "VytPeDirectoryDlg.h"
// VytPeDirExportDlg 对话框

class VytPeDirExportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirExportDlg)

public:
	VytPeDirExportDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirExportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_EXPORT };
#endif

private:
	VytPeDirectoryDlg *m_dirDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
