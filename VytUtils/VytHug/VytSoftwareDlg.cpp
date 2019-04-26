// VytSoftwareDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytSoftwareDlg.h"
#include "afxdialogex.h"
using namespace vyt;

// VytSoftwareDlg 对话框

IMPLEMENT_DYNAMIC(VytSoftwareDlg, CDialogEx)

VytSoftwareDlg::VytSoftwareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOFTWARE, pParent)
{

}

VytSoftwareDlg::~VytSoftwareDlg()
{
}

void VytSoftwareDlg::UpdateSoftwares()
{
	m_softwareInfos.clear();
	m_softwares.DeleteAllItems();
	RegeditUtils::EnumSoftwares([this](RegeditUtils::SoftwareInfo &info) {
		m_softwareInfos.push_back(RegeditUtils::SoftwareInfo(info));
		m_softwares.InsertTexts(info.szSoftName, 3, info.szSoftVenRel, info.szSoftDate, info.szSoftVersion);
	});
}

void VytSoftwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SO_LIST, m_softwares);
}


BEGIN_MESSAGE_MAP(VytSoftwareDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_SO_LIST, &VytSoftwareDlg::TrackSoftwareMenu)
	ON_COMMAND(ID_SO_UNINSTALL, &VytSoftwareDlg::OnSoUninstall)
	ON_COMMAND(ID_SO_EXPLORER, &VytSoftwareDlg::OnSoExplorer)
	ON_COMMAND(ID_SO_UPDATE, &VytSoftwareDlg::OnSoUpdate)
END_MESSAGE_MAP()


// VytSoftwareDlg 消息处理程序


BOOL VytSoftwareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_softwares.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_softwares.InsertColumn(Str(IDS_TASK), 300);
	m_softwares.InsertColumn(Str(IDS_STATUS), 200);
	m_softwares.InsertColumn(Str(IDS_INSTALLTIME), 120);
	m_softwares.InsertColumn(Str(IDS_VERSION), 180);
	UpdateSoftwares();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytSoftwareDlg::TrackSoftwareMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	m_selectSoftwareIndex = pNMItemActivate->iItem;
	if (-1 == m_selectSoftwareIndex) return;
	TrackMenu(IDR_SO_TRACKMENU, 0);
}


void VytSoftwareDlg::OnSoUninstall()
{
	ShellExecute(NULL, _T("open"), m_softwareInfos[m_selectSoftwareIndex].szSoftUniPath, NULL, NULL, SW_SHOWNORMAL);
}


void VytSoftwareDlg::OnSoExplorer()
{
	CString path = m_softwareInfos[m_selectSoftwareIndex].szSoftInsPath;
	path.Format(_T("/select, %s"), path);
	ShellExecute(NULL, _T("open"), _T("Explorer.exe"), path, NULL, SW_SHOWDEFAULT);
}


void VytSoftwareDlg::OnSoUpdate()
{
	UpdateSoftwares();
}
