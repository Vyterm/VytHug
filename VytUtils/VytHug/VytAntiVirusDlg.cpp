// VytAntiVirusDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytAntiVirusDlg.h"
#include "afxdialogex.h"


// VytAntiVirusDlg 对话框

IMPLEMENT_DYNAMIC(VytAntiVirusDlg, CDialogEx)

VytAntiVirusDlg::VytAntiVirusDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANTIVIRUS, pParent)
{

}

VytAntiVirusDlg::~VytAntiVirusDlg()
{
}

void VytAntiVirusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytAntiVirusDlg, CDialogEx)
END_MESSAGE_MAP()


// VytAntiVirusDlg 消息处理程序


BOOL VytAntiVirusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
