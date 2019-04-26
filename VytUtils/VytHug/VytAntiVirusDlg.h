#pragma once

#include "SmartList.hpp"
#include "VytNetHandler.hpp"
#include <map>
// VytAntiVirusDlg 对话框

class VytAntiVirusDlg : public CDialogEx, public vyt::IHandler
{
	DECLARE_DYNAMIC(VytAntiVirusDlg)

public:
	VytAntiVirusDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytAntiVirusDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANTIVIRUS };
#endif

private:
	bool m_isScaning;
	std::map<CString, CString> m_md5ToFiles;
private:
	void ComeRefresh();
	void RefreshScan(CString path = nullptr);
	void AppendVirus(CString path);
	void OverRefresh();
public:
	void LocalScan(CString path);
	void LocalScanDeeply(CString path);
	void LocalScanOver();
	void NetScan(CString path);
	void NetScanDeeply(CString path);
	void NetScanOver();
public:
	void HandlePacket(vyt::Packet &packet) override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	vyt::SmartList m_viruses;
	BOOL m_libraryOption;
	BOOL m_pathOption;
	CEdit m_scanState;
	afx_msg void OnBnClickedAnStartscan();
	afx_msg void DeleteAllViruses();
	afx_msg void OnBnClickedAnSendtoserver();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
