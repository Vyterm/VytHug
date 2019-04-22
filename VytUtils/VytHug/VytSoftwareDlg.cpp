// VytSoftwareDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytSoftwareDlg.h"
#include "afxdialogex.h"
using namespace vyt;

// VytSoftwareDlg 对话框

IMPLEMENT_DYNAMIC(VytSoftwareDlg, CDialogEx)

VytSoftwareDlg::VytSoftwareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOFTWARE, pParent)
{

}

VytSoftwareDlg::~VytSoftwareDlg()
{
}

void VytSoftwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SO_LIST, m_softwares);
}


BEGIN_MESSAGE_MAP(VytSoftwareDlg, CDialogEx)
END_MESSAGE_MAP()


// VytSoftwareDlg 消息处理程序


BOOL VytSoftwareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_softwares.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_softwares.InsertColumn(Str(IDS_TASK), 300);
	m_softwares.InsertColumn(Str(IDS_STATUS), 200);
	m_softwares.InsertColumn(Str(IDS_INSTALLTIME), 120);
	m_softwares.InsertColumn(Str(IDS_VERSION), 180);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
