#pragma once


// VytPeDirCommonDlg 对话框

class VytPeDirCommonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirCommonDlg)

public:
	VytPeDirCommonDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirCommonDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_COMMON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_directorys;
};
