// VytCleanerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytCleanerDlg.h"
#include "afxdialogex.h"
#include "VytFileUtils.hpp"
using namespace vyt;

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

void VytCleanerDlg::RefreshFiles(std::function<bool(const CString&, WIN32_FIND_DATA&)> fileFilter/* = nullptr*/)
{
	m_filelist.DeleteAllItems();
	FileUtils::EnumFiles(m_path, [&](const CString &path, WIN32_FIND_DATA &filedata) {
		if (nullptr != fileFilter && !fileFilter(path, filedata)) return;
		CString filename, fileattr, createtime, visittime, modifytime, filesize, filemd5;
		FileUtils::QueryFileAttributes(path, filedata, filename, fileattr, createtime, visittime, modifytime, filesize, filemd5);
		m_filelist.InsertTexts(filedata.cFileName, 6, fileattr, createtime, visittime, modifytime, filesize, filemd5);
	});
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
	m_filelist.InsertColumn(vyt::Str(IDS_FILEATTRIBUTE), 90);
	m_filelist.InsertColumn(vyt::Str(IDS_CREATETIME), 130);
	m_filelist.InsertColumn(vyt::Str(IDS_LASTVISITTIME), 130);
	m_filelist.InsertColumn(vyt::Str(IDS_LASTMODIFYTIME), 130);
	m_filelist.InsertColumn(vyt::Str(IDS_FILESIZE), 70);
	m_filelist.InsertColumn(vyt::Str(IDS_MD5), 200);
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
	UpdateData(TRUE);
	RefreshFiles();
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
	UpdateData(TRUE);
	TCHAR path[MAX_PATH];
	DragQueryFile(hDropInfo, 0, path, MAX_PATH);
	m_path = path;
	UpdateData(FALSE);
	CString m_trashSuffix = _T("\\.obj\\.tlog\\.lastbuildstate\\.idb\\.pdb\\.pch\\.res\\.ilk\\.exe\\.sdf\\.ipch\\.log\\");
	RefreshFiles([&](const CString &path, WIN32_FIND_DATA &filedata) {
		CString extension = PathFindExtension(filedata.cFileName);
		return _T("") != extension && -1 != m_trashSuffix.Find(extension, 0);
	});

	CDialogEx::OnDropFiles(hDropInfo);
}
