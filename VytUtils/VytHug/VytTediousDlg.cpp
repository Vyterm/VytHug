// VytTediousDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTediousDlg.h"
#include "afxdialogex.h"


// VytTediousDlg 对话框

IMPLEMENT_DYNAMIC(VytTediousDlg, CDialogEx)

VytTediousDlg::VytTediousDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEDIOUS, pParent)
{

}

VytTediousDlg::~VytTediousDlg()
{
}

void VytTediousDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytTediousDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTediousDlg 消息处理程序


BOOL VytTediousDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
