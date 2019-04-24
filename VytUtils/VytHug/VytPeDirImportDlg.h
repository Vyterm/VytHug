#pragma once


// VytPeDirImportDlg 对话框

class VytPeDirImportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirImportDlg)

public:
	VytPeDirImportDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirImportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_IMPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
