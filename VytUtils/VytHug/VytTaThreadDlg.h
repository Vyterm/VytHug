#pragma once


// VytTaThreadDlg 对话框

class VytTaThreadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaThreadDlg)

public:
	VytTaThreadDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaThreadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TA_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_threads;
};
