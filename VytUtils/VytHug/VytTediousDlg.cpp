// VytTediousDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTediousDlg.h"
#include "afxdialogex.h"
#include "VytComputerUtils.hpp"
#include "VytFileUtils.hpp"
#include "VytRegeditUtils.hpp"
using namespace vyt;

// VytTediousDlg 对话框
constexpr auto UpdateUtilizationTimer = WM_USER + 2;

IMPLEMENT_DYNAMIC(VytTediousDlg, CDialogEx)

VytTediousDlg::VytTediousDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEDIOUS, pParent)
	, m_cleanHint(_T(""))
{

}

VytTediousDlg::~VytTediousDlg()
{
}

void VytTediousDlg::CheckAdmin()
{
	// 根据权限的不同控制按钮的显示
	if (!ComputerUtils::CheckAdmin())
		Button_SetElevationRequiredState(m_rootbutton.GetSafeHwnd(), TRUE);
	else
		m_rootbutton.ShowWindow(SW_HIDE);
}

void VytTediousDlg::UpdateUtilization()
{
	auto cpuUtilization = ComputerUtils::CpuUtilization();
	auto memoryUtilization = ComputerUtils::MemoryUtilization();
	m_cpuProgress.SetPos(cpuUtilization);
	m_memoryProgress.SetPos(memoryUtilization);
	CString cpuString;
	cpuString.Format(_T("%d%%"), cpuUtilization);
	CString memoryString;
	memoryString.Format(_T("%d%%"), memoryUtilization);
	SetDlgItemText(IDC_TE_CPUTEXT, cpuString);
	SetDlgItemText(IDC_TE_MEMORYTEXT, memoryString);
}

void VytTediousDlg::UpdateBootInfos()
{
	m_startups.DeleteAllItems();
	m_bootstrapInfos.clear();
	RegeditUtils::EnumBootstraps([this](vyt::RegeditUtils::BootstrapInfo &bootInfo) {
		m_startups.InsertTexts(bootInfo.bootName, 2, bootInfo.bootOrder, bootInfo.bootPos_All);
		m_bootstrapInfos.push_back(std::move(bootInfo));
	});
}

void VytTediousDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TE_PROGRESSCPU, m_cpuProgress);
	DDX_Control(pDX, IDC_TE_PROGRESSMEMORY, m_memoryProgress);
	DDX_Control(pDX, IDC_TE_POWERRAISING, m_rootbutton);
	DDX_Text(pDX, IDC_TE_CLEANHINT, m_cleanHint);
	DDX_Control(pDX, IDC_TE_STARTUPLIST, m_startups);
}


BEGIN_MESSAGE_MAP(VytTediousDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TE_CLEANMEMORY, &VytTediousDlg::OnBnClickedTeCleanmemory)
	ON_BN_CLICKED(IDC_TE_POWEROFF, &VytTediousDlg::OnBnClickedTePoweroff)
	ON_BN_CLICKED(IDC_TE_RESTART, &VytTediousDlg::OnBnClickedTeRestart)
	ON_BN_CLICKED(IDC_TE_LOGOFF, &VytTediousDlg::OnBnClickedTeLogoff)
	ON_BN_CLICKED(IDC_TE_DORMANT, &VytTediousDlg::OnBnClickedTeDormant)
	ON_BN_CLICKED(IDC_TE_SLEEP, &VytTediousDlg::OnBnClickedTeSleep)
	ON_BN_CLICKED(IDC_TE_LOCK, &VytTediousDlg::OnBnClickedTeLock)
	ON_BN_CLICKED(IDC_TE_POWERRAISING, &VytTediousDlg::OnBnClickedTePowerraising)
	ON_NOTIFY(NM_RCLICK, IDC_TE_STARTUPLIST, &VytTediousDlg::OnRclickTeStartuplist)
	ON_COMMAND(ID_TE_INSERTBOOT, &VytTediousDlg::OnTeInsertboot)
	ON_COMMAND(ID_TE_DELETEBOOT, &VytTediousDlg::OnTeDeleteboot)
	ON_COMMAND(ID_TE_REFRESHBOOT, &VytTediousDlg::OnTeRefreshboot)
END_MESSAGE_MAP()


// VytTediousDlg 消息处理程序


BOOL VytTediousDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CheckAdmin();
	SetDlgItemText(IDC_TE_GROUPCPU, Str(IDS_CPU));
	SetDlgItemText(IDC_TE_GROUPMEMORY, Str(IDS_MEMORY));
	SetTimer(UpdateUtilizationTimer, 1000, nullptr);
	m_cpuProgress.SetRange(0, 100);
	m_memoryProgress.SetRange(0, 100);
	UpdateUtilization();
	m_startups.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_startups.InsertColumn(3, Str(IDS_TASK), 200, Str(IDS_ORDER), 300, Str(IDS_POSITION), 300);
	UpdateBootInfos();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytTediousDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent = UpdateUtilizationTimer)
		UpdateUtilization();

	CDialogEx::OnTimer(nIDEvent);
}


void VytTediousDlg::OnBnClickedTeCleanmemory()
{
	auto freesize = ComputerUtils::Cleanmemory();
	m_cleanHint.Format(Str(IDS_CLEANHINT), FileUtils::FileSizeToString(freesize >> 32, freesize & 0xFFFFFFFF));
	UpdateData(FALSE);
}


void VytTediousDlg::OnBnClickedTePoweroff()
{
	ComputerUtils::Poweroff();
}


void VytTediousDlg::OnBnClickedTeRestart()
{
	ComputerUtils::Reboot();
}


void VytTediousDlg::OnBnClickedTeLogoff()
{
	ComputerUtils::Logoff();
}


void VytTediousDlg::OnBnClickedTeDormant()
{
	ComputerUtils::Dormancy();
}


void VytTediousDlg::OnBnClickedTeSleep()
{
	ComputerUtils::Sleep();
}


void VytTediousDlg::OnBnClickedTeLock()
{
	ComputerUtils::LockScreen();
}


void VytTediousDlg::OnBnClickedTePowerraising()
{
	AfxGetMainWnd()->ShowWindow(SW_HIDE);
	// 防止在隐藏动画播放到一半时卡住
	Sleep(500);
	if (ComputerUtils::RunasAdmin())
		exit(0);
	else
		AfxGetMainWnd()->ShowWindow(SW_SHOW);
}


void VytTediousDlg::OnRclickTeStartuplist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	m_bootstrapIndex = pNMItemActivate->iItem;
	DefTrackMenu(bootMenu, IDR_TE_TRACKMENU, 0);
	if (-1 == m_bootstrapIndex)
		bootMenu->DeleteMenu(ID_TE_DELETEBOOT, MF_BYCOMMAND);
	DefTrackMenu_Show(bootMenu);
}


void VytTediousDlg::OnTeInsertboot()
{
	auto path = FileUtils::SelectFilePath();
	if (_tcscmp(_T(".exe"), PathFindExtension(path)))
	{
		MessageBox(Str(IDS_ACCESS_FAILED));
		return;
	}
	// 去除路径及拓展名
	auto keyname = FileUtils::FileNameByName(FileUtils::FileNameByPath(path));
	if (!RegeditUtils::AppendBootstrap(keyname, path))
		MessageBox(Str(IDS_BOOTSTRAPFAILED), Str(IDS_ACCESS_FAILED));
	else
	{
		MessageBox(Str(IDS_BOOTSTRAPSUCCESS), Str(IDS_STATUS));
		UpdateBootInfos();
	}
}


void VytTediousDlg::OnTeDeleteboot()
{
	if (!RegeditUtils::DeleteBootstrap(m_bootstrapInfos[m_bootstrapIndex]))
		MessageBox(Str(IDS_BOOTSTRAPFAILED), Str(IDS_ACCESS_FAILED));
	else
	{
		MessageBox(Str(IDS_BOOTSTRAPSUCCESS), Str(IDS_STATUS));
		UpdateBootInfos();
	}
}


void VytTediousDlg::OnTeRefreshboot()
{
	UpdateBootInfos();
}
