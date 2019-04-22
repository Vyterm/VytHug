// VytTaskManagerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaskManagerDlg.h"
#include "afxdialogex.h"


// VytTaskManagerDlg 对话框

IMPLEMENT_DYNAMIC(VytTaskManagerDlg, CDialogEx)

VytTaskManagerDlg::VytTaskManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASKMANAGER, pParent)
{

}

VytTaskManagerDlg::~VytTaskManagerDlg()
{
}

void VytTaskManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_LIST, m_processes);
}


BEGIN_MESSAGE_MAP(VytTaskManagerDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTaskManagerDlg 消息处理程序


BOOL VytTaskManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
