#pragma once
#include "SmartList.hpp"
#include "VytRegeditUtils.hpp"
#include <deque>

// VytSoftwareDlg 对话框

class VytSoftwareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytSoftwareDlg)

public:
	VytSoftwareDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytSoftwareDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOFTWARE };
#endif

private:
	std::deque<vyt::RegeditUtils::SoftwareInfo> m_softwareInfos;
	int m_selectSoftwareIndex;
private:
	void UpdateSoftwares();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vyt::SmartList m_softwares;
	virtual BOOL OnInitDialog();
	afx_msg void TrackSoftwareMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSoUninstall();
	afx_msg void OnSoExplorer();
	afx_msg void OnSoUpdate();
};
