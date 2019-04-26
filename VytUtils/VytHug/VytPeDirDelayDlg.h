#pragma once

#include "VytPeDirectoryDlg.h"
// VytPeDirDelayDlg 对话框

class VytPeDirDelayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirDelayDlg)

public:
	VytPeDirDelayDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirDelayDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_DELAY };
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
	CString m_edit7;
};
