// VytTaProcessDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaProcessDlg.h"
#include "afxdialogex.h"
#include "VytTaThreadDlg.h"
#include "VytTaModuleDlg.h"
#include "VytTaHeapDlg.h"
using namespace vyt;
// VytTaProcessDlg 对话框

IMPLEMENT_DYNAMIC(VytTaProcessDlg, CDialogEx)

VytTaProcessDlg::VytTaProcessDlg(DWORD processID, E_ProcessInfo info/* = E_ProcessInfo::Thread*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_PROCESS, pParent), m_processID(processID), m_info(info)
{

}

VytTaProcessDlg::~VytTaProcessDlg()
{
}

void VytTaProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAM_TAB, m_infotab);
}


BEGIN_MESSAGE_MAP(VytTaProcessDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTaProcessDlg 消息处理程序


BOOL VytTaProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_infotab.SetDlg<VytTaThreadDlg>(IDD_TA_THREAD, Str(IDS_THREAD));
	m_infotab.SetDlg<VytTaModuleDlg>(IDD_TA_MODULE, Str(IDS_MODULE));
	m_infotab.SetDlg<VytTaHeapDlg>(IDD_TA_HEAP, Str(IDS_HEAP));
	m_infotab.GetDlg<VytTaThreadDlg>()->ShowThread(m_processID);
	m_infotab.GetDlg<VytTaModuleDlg>()->ShowModule(m_processID);
	m_infotab.GetDlg<VytTaHeapDlg>()->ShowHeap(m_processID);
	m_infotab.SeeDlg(size_t(m_info));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
