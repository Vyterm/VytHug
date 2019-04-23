#pragma once

#include "SmartTab.hpp"

enum class E_ProcessInfo
{
	Thread,
	Module,
	Heap,
};

class VytTaProcessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytTaProcessDlg)

public:
	VytTaProcessDlg(DWORD processID, E_ProcessInfo info = E_ProcessInfo::Thread, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytTaProcessDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TA_PROCESS };
#endif

private:
	DWORD m_processID;
	E_ProcessInfo m_info;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartTab m_infotab;
	virtual BOOL OnInitDialog();
};
