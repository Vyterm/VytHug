// VytTaThreadDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaThreadDlg.h"
#include "afxdialogex.h"


// VytTaThreadDlg 对话框

IMPLEMENT_DYNAMIC(VytTaThreadDlg, CDialogEx)

VytTaThreadDlg::VytTaThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_THREAD, pParent)
{

}

VytTaThreadDlg::~VytTaThreadDlg()
{
}

void VytTaThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_THREADS, m_threads);
}


BEGIN_MESSAGE_MAP(VytTaThreadDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTaThreadDlg 消息处理程序
