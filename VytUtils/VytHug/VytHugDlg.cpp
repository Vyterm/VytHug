
// VytHugDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytHugDlg.h"
#include "afxdialogex.h"
#include "VytCleanerDlg.h"
#include "VytAntiVirusDlg.h"
#include "VytServiceDlg.h"
#include "VytSoftwareDlg.h"
#include "VytWindowsDlg.h"
#include "VytTaskManagerDlg.h"
#include "VytTediousDlg.h"
#include "VytPeLoaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

constexpr int HideShowHotKey = WM_USER + 1;
constexpr int QuickQuitHotKey = WM_USER + 2;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVytHugDlg 对话框



CVytHugDlg::CVytHugDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VYTHUG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVytHugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOME_TAB, m_hometab);
}

void CVytHugDlg::InitUI()
{
	m_hometab.SetDlg<VytCleanerDlg>(IDD_CLEANER, vyt::Str(IDS_CLEANER));
	m_hometab.SetDlg<VytAntiVirusDlg>(IDD_ANTIVIRUS, vyt::Str(IDS_ANTIVIRUS));
	m_hometab.SetDlg<VytServiceDlg>(IDD_SERVICE, vyt::Str(IDS_SERVICEMGR));
	m_hometab.SetDlg<VytSoftwareDlg>(IDD_SOFTWARE, vyt::Str(IDS_SOFTMGR));
	m_hometab.SetDlg<VytWindowsDlg>(IDD_WINDOWS, vyt::Str(IDS_WINDOWMGR));
	m_hometab.SetDlg<VytTaskManagerDlg>(IDD_TASKMANAGER, vyt::Str(IDS_TASKMGR));
	m_hometab.SetDlg<VytTediousDlg>(IDD_TEDIOUS, vyt::Str(IDS_TEDIOUS));
	m_hometab.SetDlg<VytPeLoaderDlg>(IDD_PELOADER, vyt::Str(IDS_PELOADER));
	m_hometab.SeeDlg(0);
	RegisterHotKey(GetSafeHwnd(), HideShowHotKey, MOD_CONTROL | MOD_ALT, 'H');
	RegisterHotKey(GetSafeHwnd(), QuickQuitHotKey, MOD_CONTROL | MOD_ALT, 'Q');
}

BEGIN_MESSAGE_MAP(CVytHugDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CVytHugDlg 消息处理程序

BOOL CVytHugDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	InitUI();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVytHugDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVytHugDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVytHugDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVytHugDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
	if (nHotKeyId == HideShowHotKey)
	{
		if (IsWindowVisible())
			ShowWindow(SW_HIDE);
		else
			ShowWindow(SW_SHOW);
	}
	else if (nHotKeyId == QuickQuitHotKey)
		PostQuitMessage(0);
}
