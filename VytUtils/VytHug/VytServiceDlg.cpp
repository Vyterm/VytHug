// VytServiceDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytServiceDlg.h"
#include "afxdialogex.h"
#include "VytRegeditUtils.hpp"
using namespace vyt;

// VytServiceDlg 对话框

IMPLEMENT_DYNAMIC(VytServiceDlg, CDialogEx)

VytServiceDlg::VytServiceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVICE, pParent)
{

}

VytServiceDlg::~VytServiceDlg()
{
}

inline CString ServiceCurrentStatusToString(DWORD currentState)
{
	switch (currentState)
	{
	case SERVICE_STOPPED:
		return Str(IDS_CLOSED);
	case SERVICE_STOP_PENDING:
		return Str(IDS_CLOSEING);
	case SERVICE_START_PENDING:
		return Str(IDS_STARTING);
	case SERVICE_RUNNING:
		return Str(IDS_RUNNING);
	case SERVICE_PAUSED:
		return Str(IDS_SUSPENDED);
	case SERVICE_PAUSE_PENDING:
		return Str(IDS_STOPPING);
	case SERVICE_CONTINUE_PENDING:
		return Str(IDS_CONTINUING);
	default:
		return _T("");
	}
}

inline CString ServiceStartTypeToString(DWORD startType)
{
	switch (startType)
	{
	case SERVICE_AUTO_START:
		return Str(IDS_AUTO);
	case SERVICE_BOOT_START:
		return Str(IDS_SERVICE_BOOT_START);
	case SERVICE_DEMAND_START:
		return Str(IDS_MANUAL);
	case SERVICE_DISABLED:
		return Str(IDS_INVALID);
	case SERVICE_SYSTEM_START:
		return Str(IDS_SERVICE_SYSTEM_START);
	default:
		return _T("");
	}
}

inline CString ServiceTypeToString(DWORD serviceType)
{
	switch (serviceType)
	{
	case SERVICE_FILE_SYSTEM_DRIVER:
		return Str(IDS_SERVICE_SYSTEM);
	case SERVICE_KERNEL_DRIVER:
		return Str(IDS_SERVICE_DRIVER);
	case SERVICE_WIN32_OWN_PROCESS:
		return Str(IDS_SERVICE_SINGLE);
	case SERVICE_WIN32_SHARE_PROCESS:
		return Str(IDS_SERVICE_SHARED);
	default:
		return _T("");
	}
}

void VytServiceDlg::UpdateServices()
{
	m_services.DeleteAllItems();
	RegeditUtils::EnumServices([this](const ENUM_SERVICE_STATUS_PROCESS &status, const QUERY_SERVICE_CONFIG &config) {
		m_services.InsertTexts(status.lpServiceName, 4, status.lpDisplayName,
			ServiceCurrentStatusToString(status.ServiceStatusProcess.dwCurrentState),
			ServiceStartTypeToString(config.dwStartType),
			ServiceTypeToString(status.ServiceStatusProcess.dwServiceType));
	});
}

void VytServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SE_LIST, m_services);
}


BEGIN_MESSAGE_MAP(VytServiceDlg, CDialogEx)
END_MESSAGE_MAP()


// VytServiceDlg 消息处理程序


BOOL VytServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_services.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_services.InsertColumn(Str(IDS_NAME), 150);
	m_services.InsertColumn(Str(IDS_DESCRIPTION), 300);
	m_services.InsertColumn(Str(IDS_STATUS), 100);
	m_services.InsertColumn(Str(IDS_RUN_TYPE), 100);
	m_services.InsertColumn(Str(IDS_SERVICE_TYPE), 150);
	UpdateServices();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
