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
