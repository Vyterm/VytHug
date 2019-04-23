#pragma once


// VytTaProcessDlg 对话框

class VytTaProcessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaProcessDlg)

public:
	VytTaProcessDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaProcessDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TA_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_infotab;
};
