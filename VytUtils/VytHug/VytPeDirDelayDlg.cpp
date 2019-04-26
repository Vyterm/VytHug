// VytPeDirDelayDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirDelayDlg.h"
#include "afxdialogex.h"


// VytPeDirDelayDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirDelayDlg, CDialogEx)

VytPeDirDelayDlg::VytPeDirDelayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_DELAY, pParent)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
	, m_edit3(_T(""))
	, m_edit4(_T(""))
	, m_edit5(_T(""))
	, m_edit6(_T(""))
	, m_edit7(_T(""))
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirDelayDlg::~VytPeDirDelayDlg()
{
}

void VytPeDirDelayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PEDD_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_PEDD_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_PEDD_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_PEDD_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_PEDD_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_PEDD_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_PEDD_EDIT7, m_edit7);
}


BEGIN_MESSAGE_MAP(VytPeDirDelayDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirDelayDlg 消息处理程序


BOOL VytPeDirDelayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_dirDlg->PeInfo().ForeachDelayTable([this](PIMAGE_DELAYLOAD_DESCRIPTOR delayLoad) {
		m_edit1.Format(_T("%08X"), delayLoad->Attributes);
		m_edit2.Format(_T("%08X"), delayLoad->DllNameRVA);
		m_edit3.Format(_T("%08X"), delayLoad->ModuleHandleRVA);
		m_edit4.Format(_T("%08X"), delayLoad->ImportAddressTableRVA);
		m_edit5.Format(_T("%08X"), delayLoad->ImportNameTableRVA);
		m_edit6.Format(_T("%08X"), delayLoad->BoundImportAddressTableRVA);
		m_edit7.Format(_T("%08X"), delayLoad->UnloadInformationTableRVA);
		UpdateData(FALSE);
	});

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
