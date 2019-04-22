#pragma once


// VytTediousDlg 对话框

class VytTediousDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTediousDlg)

public:
	VytTediousDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTediousDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEDIOUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
