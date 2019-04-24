// VytPeDirTlsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirTlsDlg.h"
#include "afxdialogex.h"


// VytPeDirTlsDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirTlsDlg, CDialogEx)

VytPeDirTlsDlg::VytPeDirTlsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_TLS, pParent)
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirTlsDlg::~VytPeDirTlsDlg()
{
}

void VytPeDirTlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeDirTlsDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirTlsDlg 消息处理程序


BOOL VytPeDirTlsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
