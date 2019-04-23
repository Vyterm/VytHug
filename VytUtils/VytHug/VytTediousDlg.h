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

private:
	void CheckAdmin();
	void UpdateUtilization();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CProgressCtrl m_cpuProgress;
	CProgressCtrl m_memoryProgress;
	CButton m_rootbutton;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedTeCleanmemory();
	afx_msg void OnBnClickedTePoweroff();
	afx_msg void OnBnClickedTeRestart();
	afx_msg void OnBnClickedTeLogoff();
	afx_msg void OnBnClickedTeDormant();
	afx_msg void OnBnClickedTeSleep();
	afx_msg void OnBnClickedTeLock();
	afx_msg void OnBnClickedTePowerraising();
};
