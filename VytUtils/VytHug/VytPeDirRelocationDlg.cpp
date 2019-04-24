// VytPeDirRelocationDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirRelocationDlg.h"
#include "afxdialogex.h"


// VytPeDirRelocationDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirRelocationDlg, CDialogEx)

VytPeDirRelocationDlg::VytPeDirRelocationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_RELOCATION, pParent)
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirRelocationDlg::~VytPeDirRelocationDlg()
{
}

void VytPeDirRelocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeDirRelocationDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirRelocationDlg 消息处理程序


BOOL VytPeDirRelocationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
