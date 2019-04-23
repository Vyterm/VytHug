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

void VytTaskManagerDlg::UpdateProcesses()
{
	m_processes.DeleteAllItems();
	vyt::EnumProcess([&](PROCESSENTRY32 processInfo) {
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
