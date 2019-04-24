// VytPeDirResourceDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeDirResourceDlg.h"
#include "afxdialogex.h"


// VytPeDirResourceDlg 对话框

IMPLEMENT_DYNAMIC(VytPeDirResourceDlg, CDialogEx)

VytPeDirResourceDlg::VytPeDirResourceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PED_RESOURCE, pParent)
{
	m_dirDlg = dynamic_cast<VytPeDirectoryDlg*>(pParent->GetParent());
	ASSERT(nullptr != m_dirDlg);
}

VytPeDirResourceDlg::~VytPeDirResourceDlg()
{
}

void VytPeDirResourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PEDR_RESTREE, m_resources);
}


BEGIN_MESSAGE_MAP(VytPeDirResourceDlg, CDialogEx)
END_MESSAGE_MAP()


// VytPeDirResourceDlg 消息处理程序


BOOL VytPeDirResourceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HTREEITEM typeTree, itemTree;
	m_dirDlg->PeInfo().ForeachResourceTable([&](vyt::ResourceField resource) {
		CString node;
		if (resource.NameIsString)
			node.SetString(resource.u.Name);
		else
			node.Format(_T("%d"), resource.u.Id);
		if (resource.Layer == vyt::ResourceField::Type)
			typeTree = m_resources.InsertItem(node);
		//else if (resource.Layer == vyt::ResourceField::Item)
		else
			itemTree = m_resources.InsertItem(node, typeTree);
	}, [&](PIMAGE_RESOURCE_DATA_ENTRY entry) {
		CString rva, foa, size;
		rva.Format(_T("Rva: %08X"), entry->OffsetToData);
		foa.Format(_T("Foa: %08X"), m_dirDlg->PeInfo().RvaToFoa(entry->OffsetToData));
		size.Format(_T("Size: %d"), entry->Size);
		m_resources.InsertItem(rva, itemTree);
		m_resources.InsertItem(foa, itemTree);
		m_resources.InsertItem(size, itemTree);
	});

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
