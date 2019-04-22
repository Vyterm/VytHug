// VytCleanerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytCleanerDlg.h"
#include "afxdialogex.h"


// VytCleanerDlg 对话框

IMPLEMENT_DYNAMIC(VytCleanerDlg, CDialogEx)

VytCleanerDlg::VytCleanerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLEANER, pParent)
	, m_path(_T(""))
{

}

VytCleanerDlg::~VytCleanerDlg()
{
}

void VytCleanerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CL_PATHEDIT, m_path);
	DDX_Control(pDX, IDC_CL_FILELIST, m_filelist);
}


BEGIN_MESSAGE_MAP(VytCleanerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CL_VIEWPATHBUTTON, &VytCleanerDlg::OnBnClickedClViewpathbutton)
	ON_BN_CLICKED(IDC_CL_SCANSYS, &VytCleanerDlg::OnBnClickedClScansys)
	ON_BN_CLICKED(IDC_CL_SCANEXP, &VytCleanerDlg::OnBnClickedClScanexp)
	ON_BN_CLICKED(IDC_CL_DROPTRASH, &VytCleanerDlg::OnBnClickedClDroptrash)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


BOOL VytCleanerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_filelist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_filelist.InsertColumn(vyt::Str(IDS_FILENAME), 100);
	m_filelist.InsertColumn(vyt::Str(IDS_FILEATTRIBUTE), 100);
	m_filelist.InsertColumn(vyt::Str(IDS_CREATETIME), 100);
	m_filelist.InsertColumn(vyt::Str(IDS_LASTVISITTIME), 100);
	m_filelist.InsertColumn(vyt::Str(IDS_LASTMODIFYTIME), 100);
	m_filelist.InsertColumn(vyt::Str(IDS_FILESIZE), 100);
	m_filelist.InsertColumn(vyt::Str(IDS_MD5), 280);
	SetDlgItemText(IDC_CL_HELPTEXT, vyt::Str(IDS_CL_HELPTEXT));
	SetDlgItemText(IDC_CL_SCANSYS, vyt::Str(IDS_CL_SCANSYS));
	SetDlgItemText(IDC_CL_SCANEXP, vyt::Str(IDS_CL_SCANEXP));
	SetDlgItemText(IDC_CL_DROPTRASH, vyt::Str(IDS_CL_DROPTRASH));
	SetDlgItemText(IDC_CL_PATHHINT, vyt::Str(IDS_PATHHINT));
	SetDlgItemText(IDC_CL_VIEWPATHBUTTON, vyt::Str(IDS_CL_VIEWPATH));
	SetDlgItemText(IDC_CL_INFOLIST, _T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytCleanerDlg::OnBnClickedClViewpathbutton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void VytCleanerDlg::OnBnClickedClScansys()
{
	// TODO: 在此添加控件通知处理程序代码
}


void VytCleanerDlg::OnBnClickedClScanexp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void VytCleanerDlg::OnBnClickedClDroptrash()
{
	// TODO: 在此添加控件通知处理程序代码
}


void VytCleanerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnDropFiles(hDropInfo);
}
