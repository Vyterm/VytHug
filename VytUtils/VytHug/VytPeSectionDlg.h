#pragma once

#include "SmartList.hpp"
#include "VytPeUtils.hpp"
// VytPeSectionDlg 对话框

class VytPeSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeSectionDlg)

public:
	VytPeSectionDlg(vyt::PeUtils &peInfo, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeSectionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PE_SECTION };
#endif

private:
	vyt::PeUtils &m_peInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	vyt::SmartList m_sections;
};
