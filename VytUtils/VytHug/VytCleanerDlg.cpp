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

void VytCleanerDlg::RefreshFiles(std::function<bool(const CString&, WIN32_FIND_DATA&)> fileFilter/* = nullptr*/, bool isDeeply/* = false*/)
{
	m_filelist.DeleteAllItems();
	FileUtils::EnumFiles(m_path, [&](const CString &path, WIN32_FIND_DATA &filedata) {
		if (nullptr != fileFilter && !fileFilter(path, filedata)) return;
		CString filename, fileattr, createtime, visittime, modifytime, filesize, filemd5;
		FileUtils::QueryFileAttributes(path, filedata, filename, fileattr, createtime, visittime, modifytime, filesize, filemd5);
		m_filelist.InsertTexts(filedata.cFileName, 7, fileattr, createtime, visittime, modifytime, filesize, filemd5, path + filedata.cFileName);
	}, isDeeply);
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
	m_filelist.InsertColumn(vyt::Str(IDS_FILENAME), 90);
	m_filelist.InsertColumn(vyt::Str(IDS_FILEATTRIBUTE), 90);
	m_filelist.InsertColumn(vyt::Str(IDS_CREATETIME), 130);
	m_filelist.InsertColumn(vyt::Str(IDS_LASTVISITTIME), 130);
	m_filelist.InsertColumn(vyt::Str(IDS_LASTMODIFYTIME), 130);
	m_filelist.InsertColumn(vyt::Str(IDS_FILESIZE), 70);
	m_filelist.InsertColumn(vyt::Str(IDS_MD5), 200);
	m_filelist.InsertColumn(vyt::Str(IDS_PATHABSOLUTE), 500);
	SetDlgItemText(IDC_CL_HELPTEXT, vyt::Str(IDS_CL_HELPTEXT));
	SetDlgItemText(IDC_CL_SCANSYS, vyt::Str(IDS_CL_SCANSYS));
	SetDlgItemText(IDC_CL_SCANEXP, vyt::Str(IDS_CL_SCANEXP));
	SetDlgItemText(IDC_CL_DROPTRASH, vyt::Str(IDS_CL_DROPTRASH));
	SetDlgItemText(IDC_CL_PATHHINT, vyt::Str(IDS_PATHHINT));
	SetDlgItemText(IDC_CL_VIEWPATHBUTTON, vyt::Str(IDS_CL_VIEWPATH));
	SetDlgItemText(IDC_CL_INFOLIST, _T(""));
	// 使管理员权限运行时也可以接收文件拖拽
	// 参考自: https://blog.csdn.net/learner198461/article/details/42223835
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x49, MSGFLT_ADD);

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
	SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}


void VytCleanerDlg::OnBnClickedClScanexp()
{
	FileUtils::CleanupDirectory(_T("C:\\Users\\Vyterm\\AppData\\Local\\Google\\Chrome\\User Data"));
}


void VytCleanerDlg::OnBnClickedClDroptrash()
{
	for (int i = 0; i < m_filelist.GetItemCount(); ++i)
		DeleteFile(m_filelist.GetItemText(i, 7));
	m_filelist.DeleteAllItems();
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
	}, true);

	CDialogEx::OnDropFiles(hDropInfo);
}
