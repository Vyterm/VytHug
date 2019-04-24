// VytPeDirExportDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirExportDlg.h"
#include "afxdialogex.h"
using namespace vyt;

// VytPeDirExportDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirExportDlg, CDialogEx)

VytPeDirExportDlg::VytPeDirExportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_EXPORT, pParent)
	, m_namestr(_T(""))
	, m_funcCount(_T(""))
	, m_nameCount(_T(""))
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirExportDlg::~VytPeDirExportDlg()
{
}

void VytPeDirExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PEDE_NAMESTR, m_namestr);
	DDX_Text(pDX, IDC_PEDE_NUMFUNC, m_funcCount);
	DDX_Text(pDX, IDC_PEDE_NUMNAME, m_nameCount);
	DDX_Control(pDX, IDC_PEDE_LIST, m_funclist);
}


BEGIN_MESSAGE_MAP(VytPeDirExportDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirExportDlg 消息处理程序


BOOL VytPeDirExportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_funclist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_funclist.InsertColumn(Str(IDS_ORDINAL), 100);
	m_funclist.InsertColumn(Str(IDS_RVA), 200);
	m_funclist.InsertColumn(Str(IDS_NAME), 300);
	DWORD funcCount = 0, nameCount = 0;
	m_dirDlg->PeInfo().ForeachExportTable([this](LPCSTR exportName) { m_namestr = exportName; }, [&](vyt::FunctionField function) {
		CString ordinal, rva;
		ordinal.Format(_T("%04d"), function.Ordinal);
		rva.Format(_T("%08X"), function.Rva);
		DefConvertA2W(szFuncname, function.Name);
		CString name = szFuncname;
		if (!name.IsEmpty())
			++nameCount;
		++funcCount;
		m_funclist.InsertTexts(ordinal, 2, rva, szFuncname);
	});
	m_funcCount.Format(_T("%d"), funcCount);
	m_nameCount.Format(_T("%d"), nameCount);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
