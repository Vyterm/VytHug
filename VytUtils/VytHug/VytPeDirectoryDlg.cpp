// VytPeDirectoryDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirectoryDlg.h"
#include "afxdialogex.h"
#include "VytPeDirCommonDlg.h"
#include "VytPeDirExportDlg.h"
#include "VytPeDirImportDlg.h"
#include "VytPeDirResourceDlg.h"
#include "VytPeDirRelocationDlg.h"
#include "VytPeDirTlsDlg.h"
#include "VytPeDirDelayDlg.h"
using namespace vyt;
// VytPeDirectoryDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirectoryDlg, CDialogEx)

VytPeDirectoryDlg::VytPeDirectoryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PE_DIRECTORY, pParent)
{

}

VytPeDirectoryDlg::~VytPeDirectoryDlg()
{
}

void VytPeDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PED_TAB, m_directoryTab);
}


BEGIN_MESSAGE_MAP(VytPeDirectoryDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirectoryDlg 消息处理程序


BOOL VytPeDirectoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_directoryTab.SetDlg<VytPeDirCommonDlg>(IDD_PED_COMMON, Str(IDS_COMMON));
	m_directoryTab.SetDlg<VytPeDirExportDlg>(IDD_PED_EXPORT, Str(IDS_PED_EXPORT));
	m_directoryTab.SetDlg<VytPeDirImportDlg>(IDD_PED_IMPORT, Str(IDS_PED_IMPORT));
	m_directoryTab.SetDlg<VytPeDirResourceDlg>(IDD_PED_RESOURCE, Str(IDS_PED_RESOURCE));
	m_directoryTab.SetDlg<VytPeDirRelocationDlg>(IDD_PED_RELOCATION, Str(IDS_PED_RELOCATION));
	m_directoryTab.SetDlg<VytPeDirTlsDlg>(IDD_PED_TLS, Str(IDS_PED_TLS));
	m_directoryTab.SetDlg<VytPeDirDelayDlg>(IDD_PED_DELAY, Str(IDS_PED_DELAY));
	m_directoryTab.SeeDlg(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
