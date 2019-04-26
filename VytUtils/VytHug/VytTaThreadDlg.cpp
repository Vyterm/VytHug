// VytTaThreadDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaThreadDlg.h"
#include "afxdialogex.h"
#include "VytSnapshotUtils.hpp"
using namespace vyt;

// VytTaThreadDlg 对话框

IMPLEMENT_DYNAMIC(VytTaThreadDlg, CDialogEx)

VytTaThreadDlg::VytTaThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_THREAD, pParent)
{

}

VytTaThreadDlg::~VytTaThreadDlg()
{
}

CString VytTaThreadDlg::GetThreadStatus(DWORD threadID)
{
	CString threadStatus;
	DWORD status = 0;
	HANDLE thread = OpenThread(THREAD_QUERY_INFORMATION | THREAD_QUERY_LIMITED_INFORMATION, FALSE, threadID);
	GetExitCodeThread(thread, &status);
	threadStatus = status == STILL_ACTIVE ? Str(IDS_THREADRUNNING) : Str(IDS_THREADSUSPENDED);
	CloseHandle(thread);
	return threadStatus;
}

void VytTaThreadDlg::ShowThread(DWORD processID)
{
	m_threads.DeleteAllItems();
	vyt::SnapshotUtils::EnumThread([&](THREADENTRY32 threadInfo) {
		if (threadInfo.th32OwnerProcessID == processID)
		{
			CString tid;
			tid.Format(_T("%6d"), threadInfo.th32ThreadID);
			CString priority;
			priority.Format(_T("%2d"), threadInfo.tpBasePri);
			m_threads.InsertTexts(tid, 2, priority, GetThreadStatus(threadInfo.th32ThreadID));
		}
	});
}

void VytTaThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_THREADS, m_threads);
}


BEGIN_MESSAGE_MAP(VytTaThreadDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_TA_THREADS, &VytTaThreadDlg::TrackThreadCommand)
	ON_COMMAND(ID_TAT_SUSPEND, &VytTaThreadDlg::OnTatSuspend)
	ON_COMMAND(ID_TAT_RESUME, &VytTaThreadDlg::OnTatResume)
	ON_COMMAND(ID_TAT_TERMINATE, &VytTaThreadDlg::OnTatTerminate)
END_MESSAGE_MAP()


// VytTaThreadDlg 消息处理程序


BOOL VytTaThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_threads.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_threads.InsertColumn(Str(IDS_TID), 100);
	m_threads.InsertColumn(Str(IDS_PRIORITY), 50);
	m_threads.InsertColumn(Str(IDS_THREADSTATUS), 200);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytTaThreadDlg::TrackThreadCommand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if (-1 == pNMItemActivate->iItem) return;
	m_activeThreadIndex = pNMItemActivate->iItem;
	TrackMenu(IDR_TA_TRACKMENU, 1);
}

#define TidOpen(name, access, error) DWORD name## ID = _ttoi(m_threads.GetItemText(m_activeThreadIndex, 0));\
HANDLE name = OpenThread(access, FALSE, threadID);\
if (NULL == thread) {\
	MessageBox(Str(error), Str(IDS_ACCESS_FAILED), MB_ICONERROR);\
	return;\
}

void VytTaThreadDlg::OnTatSuspend()
{
	TidOpen(thread, THREAD_SUSPEND_RESUME, IDS_SUSPEND_FAILED);

	SuspendThread(thread);
	m_threads.SetItemText(m_activeThreadIndex, 2, GetThreadStatus(threadID));
	CloseHandle(thread);
}


void VytTaThreadDlg::OnTatResume()
{
	TidOpen(thread, THREAD_SUSPEND_RESUME, IDS_RESUME_FAILED);

	ResumeThread(thread);
	m_threads.SetItemText(m_activeThreadIndex, 2, GetThreadStatus(threadID));
	CloseHandle(thread);
}


void VytTaThreadDlg::OnTatTerminate()
{
	TidOpen(thread, THREAD_TERMINATE, IDS_TERMINATET_FAILED);

	TerminateThread(thread, 0);
	m_threads.DeleteItem(m_activeThreadIndex);
	CloseHandle(thread);
}
