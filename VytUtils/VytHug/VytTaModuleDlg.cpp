// VytTaModuleDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaModuleDlg.h"
#include "afxdialogex.h"
#include "VytSnapshotUtils.hpp"
using namespace vyt;

// VytTaModuleDlg 对话框

IMPLEMENT_DYNAMIC(VytTaModuleDlg, CDialogEx)

VytTaModuleDlg::VytTaModuleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_MODULE, pParent)
{

}

VytTaModuleDlg::~VytTaModuleDlg()
{
}

void VytTaModuleDlg::ShowModule(DWORD processID)
{
	m_modules.DeleteAllItems();
	vyt::EnumModule(processID, [&](auto moduleInfo) {
		CString moduleImage;
		moduleImage.Format(_T("0x%08X"), moduleInfo.hModule);
		CString moduleSize;
		moduleSize.Format(_T("0x%06X"), moduleInfo.modBaseSize);
		m_modules.InsertTexts(moduleInfo.szModule, 2, moduleSize, moduleImage);
	});
}

void VytTaModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_MODULES, m_modules);
}


BEGIN_MESSAGE_MAP(VytTaModuleDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTaModuleDlg 消息处理程序


BOOL VytTaModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_modules.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_modules.InsertColumn(Str(IDS_MODULENAME), 300);
	m_modules.InsertColumn(Str(IDS_MODULESIZE), 100);
	m_modules.InsertColumn(Str(IDS_MODULEPATH), 100);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
