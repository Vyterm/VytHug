#pragma once


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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
