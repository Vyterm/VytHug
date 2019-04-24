// VytPeDirImportDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirImportDlg.h"
#include "afxdialogex.h"


// VytPeDirImportDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirImportDlg, CDialogEx)

VytPeDirImportDlg::VytPeDirImportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_IMPORT, pParent)
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirImportDlg::~VytPeDirImportDlg()
{
}

void VytPeDirImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeDirImportDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirImportDlg 消息处理程序


BOOL VytPeDirImportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
