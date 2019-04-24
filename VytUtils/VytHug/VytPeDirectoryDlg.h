#pragma once

#include "SmartTab.hpp"
#include "VytPeUtils.hpp"
// VytPeDirectoryDlg 对话框

class VytPeDirectoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirectoryDlg)

public:
	VytPeDirectoryDlg(vyt::PeUtils &peInfo, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirectoryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PE_DIRECTORY };
#endif

private:
	vyt::PeUtils &m_peInfo;
public:
	const vyt::PeUtils& PeInfo() const { return m_peInfo; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartTab m_directoryTab;
	virtual BOOL OnInitDialog();
};
