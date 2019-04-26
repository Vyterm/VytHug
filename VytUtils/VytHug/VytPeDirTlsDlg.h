#pragma once

#include "VytPeDirectoryDlg.h"
// VytPeDirTlsDlg 对话框

class VytPeDirTlsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirTlsDlg)

public:
	VytPeDirTlsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirTlsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_TLS };
#endif

private:
	VytPeDirectoryDlg *m_dirDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_edit1;
	CString m_edit2;
	CString m_edit3;
	CString m_edit4;
	CString m_edit5;
	CString m_edit6;
};
