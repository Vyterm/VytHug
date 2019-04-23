// VytTaProcessDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaProcessDlg.h"
#include "afxdialogex.h"


// VytTaProcessDlg 对话框

IMPLEMENT_DYNAMIC(VytTaProcessDlg, CDialogEx)

VytTaProcessDlg::VytTaProcessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_PROCESS, pParent)
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
