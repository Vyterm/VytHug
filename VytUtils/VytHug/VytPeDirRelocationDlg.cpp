// VytPeDirRelocationDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirRelocationDlg.h"
#include "afxdialogex.h"


// VytPeDirRelocationDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirRelocationDlg, CDialogEx)

VytPeDirRelocationDlg::VytPeDirRelocationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_RELOCATION, pParent)
	, m_logedit(_T(""))
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirRelocationDlg::~VytPeDirRelocationDlg()
{
}

void VytPeDirRelocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PEDR_LOGEDIT, m_logedit);
}


BEGIN_MESSAGE_MAP(VytPeDirRelocationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PEDR_BEGINPRINT, &VytPeDirRelocationDlg::OnBnClickedPedrBeginprint)
END_MESSAGE_MAP()


// VytPeDirRelocationDlg 消息处理程序


BOOL VytPeDirRelocationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytPeDirRelocationDlg::OnBnClickedPedrBeginprint()
{
	m_dirDlg->PeInfo().ForeachRelocationTable([this](vyt::RelocationField relocation) {
		CString log;
		log.Format(_T("RVA: %08X    FOA: %08X    Type: %2d    Data: %08X\r\n"),
			relocation.Rva, relocation.Foa, relocation.Type, relocation.Data);
		m_logedit += log;
		UpdateData(FALSE);
	});
}
