#pragma once

#include "SmartList.hpp"
// VytTaHeapDlg 对话框

class VytTaHeapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaHeapDlg)

public:
	VytTaHeapDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaHeapDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TA_HEAP };
#endif

public:
	void ShowHeap(DWORD processID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_heaps;
	virtual BOOL OnInitDialog();
};
