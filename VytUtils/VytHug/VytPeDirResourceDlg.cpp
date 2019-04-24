// VytPeDirResourceDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirResourceDlg.h"
#include "afxdialogex.h"


// VytPeDirResourceDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirResourceDlg, CDialogEx)

VytPeDirResourceDlg::VytPeDirResourceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_RESOURCE, pParent)
{

}

VytPeDirResourceDlg::~VytPeDirResourceDlg()
{
}

void VytPeDirResourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeDirResourceDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirResourceDlg 消息处理程序


BOOL VytPeDirResourceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
