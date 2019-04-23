// VytTediousDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytTediousDlg.h"
#include "afxdialogex.h"
#include "VytComputerUtils.hpp"
using namespace vyt;

// VytTediousDlg 对话框
constexpr auto UpdateUtilizationTimer = WM_USER + 2;

IMPLEMENT_DYNAMIC(VytTediousDlg, CDialogEx)

VytTediousDlg::VytTediousDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEDIOUS, pParent)
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

void VytTediousDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TE_PROGRESSCPU, m_cpuProgress);
	DDX_Control(pDX, IDC_TE_PROGRESSMEMORY, m_memoryProgress);
	DDX_Control(pDX, IDC_TE_POWERRAISING, m_rootbutton);
}


BEGIN_MESSAGE_MAP(VytTediousDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TE_CLEANMEMORY, &VytTediousDlg::OnBnClickedTeCleanmemory)
	ON_BN_CLICKED(IDC_TE_POWEROFF, &VytTediousDlg::OnBnClickedTePoweroff)
	ON_BN_CLICKED(IDC_TE_RESTART, &VytTediousDlg::OnBnClickedTeRestart)
	ON_BN_CLICKED(IDC_TE_LOGOFF, &VytTediousDlg::OnBnClickedTeLogoff)
	ON_BN_CLICKED(IDC_TE_DORMANT, &VytTediousDlg::OnBnClickedTeDormant)
	ON_BN_CLICKED(IDC_TE_LOCK, &VytTediousDlg::OnBnClickedTeLock)
	ON_BN_CLICKED(IDC_TE_POWERRAISING, &VytTediousDlg::OnBnClickedTePowerraising)
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
	ComputerUtils::Cleanmemory();
}


void VytTediousDlg::OnBnClickedTePoweroff()
{
	ComputerUtils::Poweroff();
}


void VytTediousDlg::OnBnClickedTeRestart()
{
	ComputerUtils::Restart();
}


void VytTediousDlg::OnBnClickedTeLogoff()
{
	ComputerUtils::Logout();
}


void VytTediousDlg::OnBnClickedTeDormant()
{
	ComputerUtils::Dormancy();
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
