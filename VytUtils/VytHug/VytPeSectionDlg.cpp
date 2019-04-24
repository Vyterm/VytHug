// VytPeSectionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeSectionDlg.h"
#include "afxdialogex.h"
using namespace vyt;

// VytPeSectionDlg 对话框

IMPLEMENT_DYNAMIC(VytPeSectionDlg, CDialogEx)

VytPeSectionDlg::VytPeSectionDlg(vyt::PeUtils &peInfo, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PE_SECTION, pParent), m_peInfo(peInfo)
{

}

VytPeSectionDlg::~VytPeSectionDlg()
{
}

void VytPeSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PES_LIST, m_sections);
}


BEGIN_MESSAGE_MAP(VytPeSectionDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeSectionDlg 消息处理程序


BOOL VytPeSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sections.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_sections.InsertColumn(Str(IDS_NAME), 100);
	m_sections.InsertColumn(Str(IDS_VIRTUALADDRESS), 100);
	m_sections.InsertColumn(Str(IDS_VIRTUALSIZE), 100);
	m_sections.InsertColumn(Str(IDS_FILEOFFSET), 100);
	m_sections.InsertColumn(Str(IDS_FILESIZE), 100);
	m_sections.InsertColumn(Str(IDS_FLAG), 100);
	for (auto &section : m_peInfo.Sections())
	{
#ifdef UNICODE
		auto pName = new wchar_t[9];
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)section->Name, -1, pName, 9);
#else
		auto pName = (LPCSTR)section->Name;
#endif
		CString voffset;
		voffset.Format(_T("%08X"), section->VirtualAddress);
		CString vsize;
		vsize.Format(_T("%08X"), section->Misc.VirtualSize);
		CString foffset;
		foffset.Format(_T("%08X"), section->PointerToRawData);
		CString fsize;
		fsize.Format(_T("%08X"), section->SizeOfRawData);
		CString flags;
		flags.Format(_T("%08X"), section->Characteristics);
		m_sections.InsertTexts(pName, 5, voffset, vsize, foffset, fsize, flags);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
