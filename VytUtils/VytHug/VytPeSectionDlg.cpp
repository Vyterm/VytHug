// VytPeSectionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeSectionDlg.h"
#include "afxdialogex.h"


// VytPeSectionDlg 对话框

IMPLEMENT_DYNAMIC(VytPeSectionDlg, CDialogEx)

VytPeSectionDlg::VytPeSectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PE_SECTION, pParent)
{

}

VytPeSectionDlg::~VytPeSectionDlg()
{
}

void VytPeSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VytPeSectionDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeSectionDlg 消息处理程序


BOOL VytPeSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
