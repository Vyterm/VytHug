// VytPeDirExportDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirExportDlg.h"
#include "afxdialogex.h"


// VytPeDirExportDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirExportDlg, CDialogEx)

VytPeDirExportDlg::VytPeDirExportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_EXPORT, pParent)
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirExportDlg::~VytPeDirExportDlg()
{
}

void VytPeDirExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeDirExportDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirExportDlg 消息处理程序


BOOL VytPeDirExportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
