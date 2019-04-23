// VytTaModuleDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaModuleDlg.h"
#include "afxdialogex.h"


// VytTaModuleDlg 对话框

IMPLEMENT_DYNAMIC(VytTaModuleDlg, CDialogEx)

VytTaModuleDlg::VytTaModuleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_MODULE, pParent)
{

}

VytTaModuleDlg::~VytTaModuleDlg()
{
}

void VytTaModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_MODULES, m_modules);
}


BEGIN_MESSAGE_MAP(VytTaModuleDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTaModuleDlg 消息处理程序
