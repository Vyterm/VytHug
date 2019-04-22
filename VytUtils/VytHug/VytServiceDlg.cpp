// VytServiceDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytServiceDlg.h"
#include "afxdialogex.h"
using namespace vyt;

// VytServiceDlg 对话框

IMPLEMENT_DYNAMIC(VytServiceDlg, CDialogEx)

VytServiceDlg::VytServiceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVICE, pParent)
{

}

VytServiceDlg::~VytServiceDlg()
{
}

void VytServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SE_LIST, m_services);
}


BEGIN_MESSAGE_MAP(VytServiceDlg, CDialogEx)
END_MESSAGE_MAP()


// VytServiceDlg 消息处理程序


BOOL VytServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_services.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_services.InsertColumn(Str(IDS_NAME), 150);
	m_services.InsertColumn(Str(IDS_DESCRIPTION), 300);
	m_services.InsertColumn(Str(IDS_STATUS), 100);
	m_services.InsertColumn(Str(IDS_RUN_TYPE), 100);
	m_services.InsertColumn(Str(IDS_SERVICE_TYPE), 150);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
