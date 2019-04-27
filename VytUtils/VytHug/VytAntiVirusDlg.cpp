// VytAntiVirusDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytAntiVirusDlg.h"
#include "afxdialogex.h"
#include "VytNetCmds.hpp"
#include "VytNetClientPeer.hpp"
#include "VytFileUtils.hpp"
#include "md5.h"
using namespace vyt;

// VytAntiVirusDlg 对话框

IMPLEMENT_DYNAMIC(VytAntiVirusDlg, CDialogEx)

VytAntiVirusDlg::VytAntiVirusDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANTIVIRUS, pParent)
	, m_libraryOption(FALSE)
	, m_pathOption(FALSE)
{
	Listen(OpCommand::Virus, VirusCommand::Check);
	Listen(OpCommand::Virus, VirusCommand::Over);
	Listen(OpCommand::Virus, VirusCommand::Submit);
}

VytAntiVirusDlg::~VytAntiVirusDlg()
{
}

struct ScanProcParameter
{
	VytAntiVirusDlg *antiVirusDlg;
	CString path;
};

#define DEF_SCAN_PROC(filter) static DWORD WINAPI filter## ScanDeeplyProc(LPVOID lpThreadParameter) {\
ScanProcParameter *parameter = (ScanProcParameter*)lpThreadParameter;\
FileUtils::EnumFiles(parameter->path, [parameter](const CString &p, WIN32_FIND_DATA &filedata) {\
	if (FileUtils::IsDirectory(filedata)) return;\
	parameter->antiVirusDlg->filter## Scan(p + filedata.cFileName);\
}, true); parameter->antiVirusDlg->filter## ScanOver(); delete parameter; return 0; }

DEF_SCAN_PROC(Local)
DEF_SCAN_PROC(Net)

#define ScanDeeply(filter) { HANDLE thread = CreateThread(nullptr, 0, filter## ScanDeeplyProc,\
new ScanProcParameter{ this, path }, 0, nullptr);\
CloseHandle(thread); } // 关闭句柄让线程结束后自动释放，避免内核内存泄漏

#define ScanRefresh() { if (!m_isScaning) return; else RefreshScan(path); }

#define ConnectionCheck() { if (!ClientPeer::Get().IsConnected()) {\
	if (!ClientPeer::Get().Connect(_T("127.0.0.1"), short(38564))) {\
		MessageBox(Str(IDS_NOTCONNECTED), Str(IDS_ACCESS_FAILED), MB_ICONERROR);\
		OverRefresh();\
		return; } } }

void VytAntiVirusDlg::ComeRefresh()
{
	m_viruses.DeleteAllItems();
	m_md5ToFiles.clear();
	m_isScaning = true;
}

void VytAntiVirusDlg::RefreshScan(CString path)
{
	if (!m_isScaning) return;
	path.Format(_T("%s%s"), Str(IDS_SCANING), path);
	m_scanState.SetWindowText(path);
}

void VytAntiVirusDlg::AppendVirus(CString path)
{
	if (m_whiteFiles.find(path) != m_whiteFiles.end()) return;
	m_viruses.InsertTexts(FileUtils::FileNameByPath(path), 2, FileUtils::FileSizeByPath(path), path);
}

void VytAntiVirusDlg::OverRefresh()
{
	CString hint;
	hint.Format(Str(IDS_SCANEND), m_viruses.GetItemCount());
	m_scanState.SetWindowText(hint);

	m_isScaning = false;
}

void VytAntiVirusDlg::LocalScan(CString path)
{
	ScanRefresh();
	auto md5 = md5FileValue(path);
	if (_T("19c3c70a1e4273fce91586b2cd758f43") == md5)
		AppendVirus(path);
}

void VytAntiVirusDlg::LocalScanDeeply(CString path)
{
	ScanDeeply(Local);
}

void VytAntiVirusDlg::LocalScanOver()
{
	OverRefresh();
}

void VytAntiVirusDlg::NetScan(CString path)
{
	ScanRefresh();
	ConnectionCheck();
	ClientPeer::Get().Send(_Packet(command(OpCommand::Virus), command(VirusCommand::Check), "ss", md5FileValue(path), path));
}

void VytAntiVirusDlg::NetScanDeeply(CString path)
{
	ScanDeeply(Net);
}

void VytAntiVirusDlg::NetScanOver()
{
	ClientPeer::Get().Send(_Packet(command(OpCommand::Virus), command(VirusCommand::Over)));
}

void VytAntiVirusDlg::HandlePacket(vyt::Packet & packet)
{
	if (packet->getOpCommand() == command(OpCommand::Virus))
	{
		if (packet->getSubCommand() == command(VirusCommand::Check))
		{
			CString path;
			packet->Decode("s", &path);
			AppendVirus(path);
		}
		else if (packet->getSubCommand() == command(VirusCommand::Over))
			OverRefresh();
		else if (packet->getSubCommand() == command(VirusCommand::Submit))
			MessageBox(Str(IDS_VIRUS_SUBMIT_SUCCESS), Str(IDS_ORDER), MB_OK);
	}
}

void VytAntiVirusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AN_VIRUSLIST, m_viruses);
	DDX_Radio(pDX, IDC_AN_LIBOP1, m_libraryOption);
	DDX_Radio(pDX, IDC_AN_PATHOP1, m_pathOption);
	DDX_Control(pDX, IDC_AN_SCANSTATE, m_scanState);
}


BEGIN_MESSAGE_MAP(VytAntiVirusDlg, CDialogEx)
	ON_BN_CLICKED(IDC_AN_STARTSCAN, &VytAntiVirusDlg::StartScan)
	ON_BN_CLICKED(IDC_AN_DELETEALL, &VytAntiVirusDlg::DeleteAllViruses)
	ON_BN_CLICKED(IDC_AN_SENDTOSERVER, &VytAntiVirusDlg::SubmitVirus)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_AN_VIRUSLIST, &VytAntiVirusDlg::TrackVirusCommand)
	ON_COMMAND(ID_AN_DELETE, &VytAntiVirusDlg::OnAnDelete)
	ON_COMMAND(ID_AN_WHITEIT, &VytAntiVirusDlg::OnAnWhiteit)
END_MESSAGE_MAP()


// VytAntiVirusDlg 消息处理程序


BOOL VytAntiVirusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_viruses.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_viruses.InsertColumn(Str(IDS_NAME), 200);
	m_viruses.InsertColumn(Str(IDS_SIZE), 100);
	m_viruses.InsertColumn(Str(IDS_PATHABSOLUTE), 600);
	SetTimer(WM_USER, 1000, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

#define SmartScan(filter) { useDir ? filter## ScanDeeply(path) : filter## Scan(path);\
if (!useDir) filter## ScanOver(); }

void VytAntiVirusDlg::StartScan()
{
	if (m_isScaning) return;
	UpdateData(TRUE);
	bool useNet = m_libraryOption != 0, useDir = m_pathOption != 0;
	CString path = useDir ? FileUtils::SelectDirectoryPath() : FileUtils::SelectFilePath();
	if (path.IsEmpty()) return;
	ComeRefresh();
	if (useNet)
		SmartScan(Net)
	else
		SmartScan(Local)
}


void VytAntiVirusDlg::DeleteAllViruses()
{
	for (int i = 0; i < m_viruses.GetItemCount(); ++i)
		DeleteFile(m_viruses.GetItemText(i, 2));
	m_viruses.DeleteAllItems();
}


void VytAntiVirusDlg::SubmitVirus()
{
	auto path = FileUtils::SelectFilePath();
	if (path.IsEmpty()) return;
	ConnectionCheck();
	auto md5 = md5FileValue(path);
	ClientPeer::Get().Send(_Packet(command(OpCommand::Virus), command(VirusCommand::Submit), "s", md5));
}


void VytAntiVirusDlg::OnTimer(UINT_PTR nIDEvent)
{
	__super::OnTimer(nIDEvent);
	DispatchLoop();
}


void VytAntiVirusDlg::TrackVirusCommand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	m_virusIndex = pNMItemActivate->iItem;
	if (-1 == m_virusIndex) return;
	TrackMenu(IDR_AN_TRACKMENU, 0);
}


void VytAntiVirusDlg::OnAnDelete()
{
	DeleteFile(m_viruses.GetItemText(m_virusIndex, 2));
	m_viruses.DeleteItem(m_virusIndex);
}


void VytAntiVirusDlg::OnAnWhiteit()
{
	m_whiteFiles.emplace(m_viruses.GetItemText(m_virusIndex, 2));
	m_viruses.DeleteItem(m_virusIndex);
}
