#pragma once

#include "VytPeDirectoryDlg.h"
#include "SmartList.hpp"
#include <vector>
// VytPeDirImportDlg 对话框

class VytPeDirImportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeDirImportDlg)

public:
	VytPeDirImportDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeDirImportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PED_IMPORT };
#endif

private:
	VytPeDirectoryDlg *m_dirDlg;
	std::vector<PIMAGE_IMPORT_DESCRIPTOR> m_descriptors;
	int m_selectIndex;
private:
	void RefreshFunctions();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	vyt::SmartList m_modules;
	vyt::SmartList m_functions;
	BOOL m_useFirstThunk;
	afx_msg void OnLvnItemchangedPediModulelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPediUseft();
};
