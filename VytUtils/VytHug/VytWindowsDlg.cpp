// VytWindowsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytWindowsDlg.h"
#include "afxdialogex.h"
#include "VytRegeditUtils.hpp"
using namespace vyt;

// VytWindowsDlg 对话框

IMPLEMENT_DYNAMIC(VytWindowsDlg, CDialogEx)

VytWindowsDlg::VytWindowsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOWS, pParent)
{

}

VytWindowsDlg::~VytWindowsDlg()
{
}

void VytWindowsDlg::UpdateWindows()
{
	m_windows.DeleteAllItems();
	RegeditUtils::EnumWindows([this](HWND hWnd) {
		CString handle;
		handle.Format(_T("%p"), hWnd);
		TCHAR szTitle[MAXBYTE], szClass[MAXBYTE];
		::GetWindowText(hWnd, szTitle, MAXBYTE);
		::GetClassName(hWnd, szClass, MAXBYTE);
		m_windows.InsertTexts(handle, 2, szTitle, szClass);
	});
}

void VytWindowsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WI_LIST, m_windows);
}


BEGIN_MESSAGE_MAP(VytWindowsDlg, CDialogEx)
END_MESSAGE_MAP()


// VytWindowsDlg 消息处理程序


BOOL VytWindowsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_windows.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_windows.InsertColumn(Str(IDS_WINDOW_HANDLE), 120);
	m_windows.InsertColumn(Str(IDS_WINDOW_TITLE), 340);
	m_windows.InsertColumn(Str(IDS_WINDOW_CLASS), 340);
	UpdateWindows();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
