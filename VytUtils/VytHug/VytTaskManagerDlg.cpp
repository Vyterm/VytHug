// VytTaskManagerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaskManagerDlg.h"
#include "afxdialogex.h"
#include "VytSnapshotUtils.hpp"
using namespace vyt;

// VytTaskManagerDlg 对话框

IMPLEMENT_DYNAMIC(VytTaskManagerDlg, CDialogEx)

VytTaskManagerDlg::VytTaskManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASKMANAGER, pParent)
{

}

VytTaskManagerDlg::~VytTaskManagerDlg()
{
}

void VytTaskManagerDlg::ShowProcessInfo(E_ProcessInfo info)
{
	if (-1 == m_activeProcessIndex) return;
	auto pid = _ttoi(m_processes.GetItemText(m_activeProcessIndex, 0));
	VytTaProcessDlg processInfo(pid, info, this);
	processInfo.DoModal();
}

void VytTaskManagerDlg::UpdateProcesses()
{
	m_processes.DeleteAllItems();
	vyt::SnapshotUtils::EnumProcess([&](PROCESSENTRY32 processInfo) {
		CString processText;
		processText.Format(_T("%6d"), processInfo.th32ProcessID);
		m_processes.InsertTexts(processText, 1, CString(processInfo.szExeFile));
	});
}

void VytTaskManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_LIST, m_processes);
}


BEGIN_MESSAGE_MAP(VytTaskManagerDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_TA_LIST, &VytTaskManagerDlg::OnShowProcess)
	ON_NOTIFY(NM_RCLICK, IDC_TA_LIST, &VytTaskManagerDlg::OnTrackProcess)
	ON_COMMAND(ID_TAP_THREAD, &VytTaskManagerDlg::OnTapThread)
	ON_COMMAND(ID_TAP_MODULE, &VytTaskManagerDlg::OnTapModule)
	ON_COMMAND(ID_TAP_HEAP, &VytTaskManagerDlg::OnTapHeap)
	ON_COMMAND(ID_TAP_TERMINATE, &VytTaskManagerDlg::OnTapTerminate)
	ON_COMMAND(ID_TAP_REFRESH, &VytTaskManagerDlg::OnTapRefresh)
END_MESSAGE_MAP()


// VytTaskManagerDlg 消息处理程序


BOOL VytTaskManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_processes.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_processes.InsertColumn(Str(IDS_PID), 100);
	m_processes.InsertColumn(Str(IDS_PROCESSPATH), 700);
	UpdateProcesses();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytTaskManagerDlg::OnShowProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	m_activeProcessIndex = pNMItemActivate->iItem;
	ShowProcessInfo();

	*pResult = 0;
}


void VytTaskManagerDlg::OnTrackProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	m_activeProcessIndex = pNMItemActivate->iItem;
	CMenu menu;
	menu.LoadMenuW(IDR_TA_TRACKMENU);
	CMenu *pSubMenu = menu.GetSubMenu(0);
	if (-1 == m_activeProcessIndex)
	{
		pSubMenu->DeleteMenu(ID_TAP_THREAD, MF_BYCOMMAND);
		pSubMenu->DeleteMenu(ID_TAP_MODULE, MF_BYCOMMAND);
		pSubMenu->DeleteMenu(ID_TAP_HEAP, MF_BYCOMMAND);
		pSubMenu->DeleteMenu(ID_TAP_TERMINATE, MF_BYCOMMAND);
	}

	POINT pos;
	GetCursorPos(&pos);

	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);

	*pResult = 0;
}


void VytTaskManagerDlg::OnTapThread()
{
	ShowProcessInfo(E_ProcessInfo::Thread);
}


void VytTaskManagerDlg::OnTapModule()
{
	ShowProcessInfo(E_ProcessInfo::Module);
}


void VytTaskManagerDlg::OnTapHeap()
{
	ShowProcessInfo(E_ProcessInfo::Heap);
}


void VytTaskManagerDlg::OnTapTerminate()
{
	HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, _ttoi(m_processes.GetItemText(m_activeProcessIndex, 0)));
	if (NULL == process)
		MessageBox(Str(IDS_TERMINATEP_FAILED), Str(IDS_ACCESS_FAILED), MB_ICONERROR);
	else
	{
		TerminateProcess(process, 0);
		m_processes.DeleteItem(m_activeProcessIndex);
		CloseHandle(process);
	}
}


void VytTaskManagerDlg::OnTapRefresh()
{
	UpdateProcesses();
}
