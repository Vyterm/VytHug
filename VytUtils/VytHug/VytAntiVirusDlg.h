#pragma once

#include "SmartList.hpp"
#include "VytNetHandler.hpp"
#include <map>
#include <set>
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
	int m_virusIndex;
	std::set<CString> m_whiteFiles;
	std::set<CString> m_virusLibrary;
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
	afx_msg void StartScan();
	afx_msg void DeleteAllViruses();
	afx_msg void SubmitVirus();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void TrackVirusCommand(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAnDelete();
	afx_msg void OnAnWhiteit();
};
