// VytPeDirTlsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirTlsDlg.h"
#include "afxdialogex.h"


// VytPeDirTlsDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirTlsDlg, CDialogEx)

VytPeDirTlsDlg::VytPeDirTlsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_TLS, pParent)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
	, m_edit3(_T(""))
	, m_edit4(_T(""))
	, m_edit5(_T(""))
	, m_edit6(_T(""))
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirTlsDlg::~VytPeDirTlsDlg()
{
}

void VytPeDirTlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PEDT_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_PEDT_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_PEDT_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_PEDT_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_PEDT_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_PEDT_EDIT6, m_edit6);
}


BEGIN_MESSAGE_MAP(VytPeDirTlsDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirTlsDlg 消息处理程序


BOOL VytPeDirTlsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_dirDlg->PeInfo().ForeachTlsTable([this](PIMAGE_TLS_DIRECTORY tls) {
		m_edit1.Format(_T("%08X"), tls->StartAddressOfRawData);
		m_edit2.Format(_T("%08X"), tls->EndAddressOfRawData);
		m_edit3.Format(_T("%08X"), tls->AddressOfIndex);
		m_edit4.Format(_T("%08X"), tls->AddressOfCallBacks);
		m_edit5.Format(_T("%08X"), tls->SizeOfZeroFill);
		m_edit6.Format(_T("%08X"), tls->Characteristics);
		UpdateData(FALSE);
	});

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
