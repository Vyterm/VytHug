#pragma once


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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
