﻿#pragma once

#include "VytPeUtils.hpp"
// VytPeLoaderDlg 对话框

class VytPeLoaderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VytPeLoaderDlg)

public:
	VytPeLoaderDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VytPeLoaderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PELOADER };
#endif

private:
	vyt::PeUtils m_peInfo;
	DWORD m_rva, m_va, m_foa;
	bool m_isValueUpdating;
private:
	void DisplayPeInfo();
	void UpdateOption();
	void UpdateValue();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString m_lfanew;
	CString m_machine;
	CString m_sectionNumber;
	CString m_timestamp;
	CString m_optionalHeaderSize;
	CString m_fileCharacteristics;
	CString m_magic;
	CString m_entryPoint;
	CString m_imageBase;
	CString m_sectionAlignment;
	CString m_fileAlignment;
	CString m_majorSubsystem;
	CString m_imageSize;
	CString m_headerSize;
	CString m_fileSystem;
	CString m_dllCharacteristics;
	CString m_directoryNumber;
	CEdit m_rvaEdit;
	CEdit m_vaEdit;
	CEdit m_foaEdit;
	CButton m_dirBtn;
	CButton m_secBtn;
	BOOL m_addressOption;
	afx_msg void OnBnClickedPeRadiorva();
	afx_msg void OnBnClickedPeRadiova();
	afx_msg void OnBnClickedPeRadiofoa();
	afx_msg void OnEnChangePeRvaedit();
	afx_msg void OnEnChangePeVaedit();
	afx_msg void OnEnChangePeFoaEdit();
	afx_msg void OnBnClickedPeDirbtn();
	afx_msg void OnBnClickedPeSecbtn();
};
