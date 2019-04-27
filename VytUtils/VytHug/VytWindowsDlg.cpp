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
	ON_NOTIFY(NM_RCLICK, IDC_WI_LIST, &VytWindowsDlg::TrackWindowCommand)
	ON_COMMAND(ID_WI_CLOSE, &VytWindowsDlg::OnWiClose)
	ON_COMMAND(ID_WI_REFRESH, &VytWindowsDlg::OnWiRefresh)
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


void VytWindowsDlg::TrackWindowCommand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	m_windowIndex = pNMItemActivate->iItem;
	if (-1 == m_windowIndex) return;
	TrackMenu(IDR_WI_TRACKMENU, 0);
}


void VytWindowsDlg::OnWiClose()
{
	HWND hWnd;
	_stscanf_s(m_windows.GetItemText(m_windowIndex, 0), _T("%p"), &hWnd);
	::PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
	UpdateWindows();
}


void VytWindowsDlg::OnWiRefresh()
{
	UpdateWindows();
}
