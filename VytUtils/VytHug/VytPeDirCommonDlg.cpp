// VytPeDirCommonDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirCommonDlg.h"
#include "afxdialogex.h"


// VytPeDirCommonDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirCommonDlg, CDialogEx)

VytPeDirCommonDlg::VytPeDirCommonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_COMMON, pParent)
{

}

VytPeDirCommonDlg::~VytPeDirCommonDlg()
{
}

void VytPeDirCommonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PEDC_LIST, m_directorys);
}


BEGIN_MESSAGE_MAP(VytPeDirCommonDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirCommonDlg 消息处理程序


BOOL VytPeDirCommonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
