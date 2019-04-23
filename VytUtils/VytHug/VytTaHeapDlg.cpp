// VytTaHeapDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaHeapDlg.h"
#include "afxdialogex.h"


// VytTaHeapDlg 对话框

IMPLEMENT_DYNAMIC(VytTaHeapDlg, CDialogEx)

VytTaHeapDlg::VytTaHeapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_HEAP, pParent)
{

}

VytTaHeapDlg::~VytTaHeapDlg()
{
}

void VytTaHeapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_HEAPS, m_heaps);
}


BEGIN_MESSAGE_MAP(VytTaHeapDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTaHeapDlg 消息处理程序
