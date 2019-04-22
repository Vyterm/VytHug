// VytPeLoaderDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeLoaderDlg.h"
#include "afxdialogex.h"


// VytPeLoaderDlg 对话框

IMPLEMENT_DYNAMIC(VytPeLoaderDlg, CDialogEx)

VytPeLoaderDlg::VytPeLoaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PELOADER, pParent)
{

}

VytPeLoaderDlg::~VytPeLoaderDlg()
{
}

void VytPeLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeLoaderDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeLoaderDlg 消息处理程序


BOOL VytPeLoaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
