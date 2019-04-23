// VytTaHeapDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTaHeapDlg.h"
#include "afxdialogex.h"
#include "VytSnapshotUtils.hpp"
using namespace vyt;

// VytTaHeapDlg 对话框

IMPLEMENT_DYNAMIC(VytTaHeapDlg, CDialogEx)

VytTaHeapDlg::VytTaHeapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TA_HEAP, pParent)
{

}

VytTaHeapDlg::~VytTaHeapDlg()
{
}

void VytTaHeapDlg::ShowHeap(DWORD processID)
{
	m_heaps.DeleteAllItems();
	vyt::SnapshotUtils::EnumHeap(processID, [&](HEAPENTRY32 heapInfo) {
		CString heapID;
		heapID.Format(_T("%d"), heapInfo.th32HeapID);
		CString heapSize;
		heapSize.Format(_T("0x%06X"), heapInfo.dwBlockSize);
		CString heapImage;
		heapImage.Format(_T("0x%08X"), heapInfo.dwAddress);
		CString heapStatus;
		if (heapInfo.dwFlags == LF32_FIXED)
			heapStatus.LoadStringW(IDS_HEAP_USED);
		else if (heapInfo.dwFlags == LF32_MOVEABLE)
			heapStatus.LoadStringW(IDS_HEAP_MOVEABLE);
		else
			heapStatus.LoadStringW(IDS_HEAP_FREE);
		m_heaps.InsertTexts(heapID, 3, heapSize, heapImage, heapStatus);
	});
}

void VytTaHeapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TA_HEAPS, m_heaps);
}


BEGIN_MESSAGE_MAP(VytTaHeapDlg, CDialogEx)
END_MESSAGE_MAP()


// VytTaHeapDlg 消息处理程序


BOOL VytTaHeapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_heaps.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_heaps.InsertColumn(Str(IDS_HID), 100);
	m_heaps.InsertColumn(Str(IDS_HEAPSIZE), 100);
	m_heaps.InsertColumn(Str(IDS_HEAPIMAGE), 100);
	m_heaps.InsertColumn(Str(IDS_HEAPSTATUS), 100);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
