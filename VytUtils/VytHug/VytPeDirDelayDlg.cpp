// VytPeDirDelayDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirDelayDlg.h"
#include "afxdialogex.h"


// VytPeDirDelayDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirDelayDlg, CDialogEx)

VytPeDirDelayDlg::VytPeDirDelayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_DELAY, pParent)
{

}

VytPeDirDelayDlg::~VytPeDirDelayDlg()
{
}

void VytPeDirDelayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeDirDelayDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirDelayDlg 消息处理程序


BOOL VytPeDirDelayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
