// VytPeDirImportDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirImportDlg.h"
#include "afxdialogex.h"
using namespace vyt;

// VytPeDirImportDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirImportDlg, CDialogEx)

VytPeDirImportDlg::VytPeDirImportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_IMPORT, pParent)
	, m_useFirstThunk(FALSE)
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirImportDlg::~VytPeDirImportDlg()
{
}

void VytPeDirImportDlg::RefreshFunctions()
{
	m_functions.DeleteAllItems();
	if (-1 == m_selectIndex) return;
	m_dirDlg->PeInfo().ForeachImportTable(m_descriptors[m_selectIndex], [this](WORD ordinal, LPCSTR name) {
		DefConvertA2W(szFuncname, name);
		CString ord;
		ord.Format(_T("%04X"), ordinal);
		m_functions.InsertTexts(ord, 1, szFuncname);
	}, TRUE == m_useFirstThunk);
}

void VytPeDirImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PEDI_MODULELIST, m_modules);
	DDX_Control(pDX, IDC_PEDI_FUNCLIST, m_functions);
	DDX_Check(pDX, IDC_PEDI_USEFT, m_useFirstThunk);
}


BEGIN_MESSAGE_MAP(VytPeDirImportDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PEDI_MODULELIST, &VytPeDirImportDlg::OnLvnItemchangedPediModulelist)
	ON_BN_CLICKED(IDC_PEDI_USEFT, &VytPeDirImportDlg::OnBnClickedPediUseft)
END_MESSAGE_MAP()


// VytPeDirImportDlg 消息处理程序


BOOL VytPeDirImportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_modules.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_modules.InsertColumn(Str(IDS_NAME), 200);
	m_modules.InsertColumn(Str(IDS_PED_INT), 200);
	m_modules.InsertColumn(Str(IDS_PED_IAT), 200);
	m_dirDlg->PeInfo().ForeachImportTable([&](LPCSTR modulename, PIMAGE_IMPORT_DESCRIPTOR descriptor) {
		DefConvertA2W(szModuleName, modulename);
		CString intAddr, iatAddr;
		intAddr.Format(_T("%08X"), descriptor->OriginalFirstThunk);
		iatAddr.Format(_T("%08X"), descriptor->FirstThunk);
		m_descriptors.push_back(descriptor);
		m_modules.InsertTexts(szModuleName, 2, intAddr, iatAddr);
	});
	m_functions.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_functions.InsertColumn(Str(IDS_ORDINAL), 100);
	m_functions.InsertColumn(Str(IDS_NAME), 500);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytPeDirImportDlg::OnLvnItemchangedPediModulelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	m_selectIndex = pNMLV->iItem;
	RefreshFunctions();
}


void VytPeDirImportDlg::OnBnClickedPediUseft()
{
	UpdateData(TRUE);
	RefreshFunctions();
}
