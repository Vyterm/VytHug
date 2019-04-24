// VytPeDirCommonDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirCommonDlg.h"
#include "afxdialogex.h"
using namespace vyt;

// VytPeDirCommonDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirCommonDlg, CDialogEx)

VytPeDirCommonDlg::VytPeDirCommonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_COMMON, pParent)
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
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

	m_directorys.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_directorys.InsertColumn(Str(IDS_NAME), 100);
	m_directorys.InsertColumn(Str(IDS_RVA), 100);
	m_directorys.InsertColumn(Str(IDS_SIZE), 100);
	std::map<WORD, CString> directoryNames = {
		{ IMAGE_DIRECTORY_ENTRY_EXPORT        , Str(IDS_PED_EXPORT) },
		{ IMAGE_DIRECTORY_ENTRY_IMPORT        , Str(IDS_PED_IMPORT) },
		{ IMAGE_DIRECTORY_ENTRY_RESOURCE      , Str(IDS_PED_RESOURCE) },
		{ IMAGE_DIRECTORY_ENTRY_EXCEPTION     , Str(IDS_PED_EXCEPTION) },
		{ IMAGE_DIRECTORY_ENTRY_SECURITY      , Str(IDS_PED_SECURITY) },
		{ IMAGE_DIRECTORY_ENTRY_BASERELOC     , Str(IDS_PED_RELOCATION) },
		{ IMAGE_DIRECTORY_ENTRY_DEBUG         , Str(IDS_PED_DEBUG) },
		{ IMAGE_DIRECTORY_ENTRY_ARCHITECTURE  , Str(IDS_PED_ARCHITECTURE) },
		{ IMAGE_DIRECTORY_ENTRY_GLOBALPTR     , Str(IDS_PED_GLOBALPTR) },
		{ IMAGE_DIRECTORY_ENTRY_TLS           , Str(IDS_PED_TLS) },
		{ IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG   , Str(IDS_PED_LOADCONFIG) },
		{ IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT  , Str(IDS_PED_BOUNDIMPORT) },
		{ IMAGE_DIRECTORY_ENTRY_IAT           , Str(IDS_PED_IAT) },
		{ IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT  , Str(IDS_PED_DELAY) },
		{ IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, Str(IDS_PED_COM) },
	};
	for (auto &directory : m_dirDlg->PeInfo().Directorys())
	{
		if (NULL == directory.second->VirtualAddress) continue;
		CString rva, size;
		rva.Format(_T("%08X"), directory.second->VirtualAddress);
		size.Format(_T("%08X"), directory.second->Size);
		m_directorys.InsertTexts(directoryNames[directory.first], 2, rva, size);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
