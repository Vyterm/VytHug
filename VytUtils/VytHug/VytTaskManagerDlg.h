#pragma once


// VytTaskManagerDlg 对话框

class VytTaskManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaskManagerDlg)

public:
	VytTaskManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaskManagerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASKMANAGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_processes;
	virtual BOOL OnInitDialog();
};
