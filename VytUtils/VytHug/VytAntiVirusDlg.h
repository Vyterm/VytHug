#pragma once


// VytAntiVirusDlg 对话框

class VytAntiVirusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytAntiVirusDlg)

public:
	VytAntiVirusDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytAntiVirusDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANTIVIRUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
