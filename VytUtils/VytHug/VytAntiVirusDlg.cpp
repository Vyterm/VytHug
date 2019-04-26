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
	, m_libraryOption(FALSE)
	, m_pathOption(FALSE)
{

}

VytAntiVirusDlg::~VytAntiVirusDlg()
{
}

void VytAntiVirusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AN_VIRUSLIST, m_viruses);
	DDX_Radio(pDX, IDC_AN_LIBOP1, m_libraryOption);
	DDX_Radio(pDX, IDC_AN_PATHOP1, m_pathOption);
}


BEGIN_MESSAGE_MAP(VytAntiVirusDlg, CDialogEx)
	ON_BN_CLICKED(IDC_AN_STARTSCAN, &VytAntiVirusDlg::OnBnClickedAnStartscan)
	ON_BN_CLICKED(IDC_AN_DELETEALL, &VytAntiVirusDlg::OnBnClickedAnDeleteall)
	ON_BN_CLICKED(IDC_AN_SENDTOSERVER, &VytAntiVirusDlg::OnBnClickedAnSendtoserver)
END_MESSAGE_MAP()


// VytAntiVirusDlg 消息处理程序


BOOL VytAntiVirusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytAntiVirusDlg::OnBnClickedAnStartscan()
{
	// TODO: 在此添加控件通知处理程序代码
}


void VytAntiVirusDlg::OnBnClickedAnDeleteall()
{
	// TODO: 在此添加控件通知处理程序代码
}


void VytAntiVirusDlg::OnBnClickedAnSendtoserver()
{
	// TODO: 在此添加控件通知处理程序代码
}
