// VytPeLoaderDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VytHug.h"
#include "VytPeLoaderDlg.h"
#include "afxdialogex.h"


// VytPeLoaderDlg 对话框

IMPLEMENT_DYNAMIC(VytPeLoaderDlg, CDialogEx)

VytPeLoaderDlg::VytPeLoaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PELOADER, pParent)
	, m_lfanew(_T(""))
	, m_machine(_T(""))
	, m_sectionNumber(_T(""))
	, m_timestamp(_T(""))
	, m_optionalHeaderSize(_T(""))
	, m_fileCharacteristics(_T(""))
	, m_magic(_T(""))
	, m_entryPoint(_T(""))
	, m_imageBase(_T(""))
	, m_sectionAlignment(_T(""))
	, m_fileAlignment(_T(""))
	, m_majorSubsystem(_T(""))
	, m_imageSize(_T(""))
	, m_headerSize(_T(""))
	, m_fileSystem(_T(""))
	, m_dllCharacteristics(_T(""))
	, m_directoryNumber(_T(""))
{

}

VytPeLoaderDlg::~VytPeLoaderDlg()
{
}

void VytPeLoaderDlg::DisplayPeInfo()
{
	UpdateData(TRUE);

	m_lfanew.Format(_T("%04X"), m_peInfo.NtOffset());
	// 文件头信息
	m_machine.Format(_T("%04X"), m_peInfo.FileHeader().Machine);
	m_sectionNumber.Format(_T("%04X"), m_peInfo.FileHeader().NumberOfSections);
	m_timestamp.Format(_T("%08X"), m_peInfo.FileHeader().TimeDateStamp);
	m_fileCharacteristics.Format(_T("%04X"), m_peInfo.FileHeader().Characteristics);
	m_optionalHeaderSize.Format(_T("%04X"), m_peInfo.FileHeader().SizeOfOptionalHeader);

	// 扩展头信息
	m_magic.Format(_T("%04X"), m_peInfo.OptionalHeader().Magic);
	m_entryPoint.Format(_T("%08X"), m_peInfo.OptionalHeader().AddressOfEntryPoint);
	m_imageBase.Format(_T("%08X"), m_peInfo.OptionalHeader().ImageBase);
	m_sectionAlignment.Format(_T("%08X"), m_peInfo.OptionalHeader().SectionAlignment);
	m_fileAlignment.Format(_T("%08X"), m_peInfo.OptionalHeader().FileAlignment);
	m_majorSubsystem.Format(_T("%02X"), m_peInfo.OptionalHeader().MajorSubsystemVersion);
	m_imageSize.Format(_T("%08X"), m_peInfo.OptionalHeader().SizeOfImage);
	m_headerSize.Format(_T("%08X"), m_peInfo.OptionalHeader().SizeOfHeaders);
	m_fileSystem.Format(_T("%04X"), m_peInfo.OptionalHeader().Subsystem);
	m_dllCharacteristics.Format(_T("%08X"), m_peInfo.OptionalHeader().DllCharacteristics);
	m_directoryNumber.Format(_T("%d"), m_peInfo.OptionalHeader().NumberOfRvaAndSizes);

	UpdateData(FALSE);
}

void VytPeLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PE_LFANEW, m_lfanew);
	DDX_Text(pDX, IDC_PE_MACHINE, m_machine);
	DDX_Text(pDX, IDC_PE_SECTIONNUM, m_sectionNumber);
	DDX_Text(pDX, IDC_PE_TIMESTAMP, m_timestamp);
	DDX_Text(pDX, IDC_PE_OPHSIZE, m_optionalHeaderSize);
	DDX_Text(pDX, IDC_PE_FILECHAR, m_fileCharacteristics);
	DDX_Text(pDX, IDC_PE_MAGIC, m_magic);
	DDX_Text(pDX, IDC_PE_ENTRYPOINT, m_entryPoint);
	DDX_Text(pDX, IDC_PE_IMAGEBASE, m_imageBase);
	DDX_Text(pDX, IDC_PE_SECALIGN, m_sectionAlignment);
	DDX_Text(pDX, IDC_PE_FILEALIGN, m_fileAlignment);
	DDX_Text(pDX, IDC_PE_MAJORSUBSYS, m_majorSubsystem);
	DDX_Text(pDX, IDC_PE_IMAGESIZE, m_imageSize);
	DDX_Text(pDX, IDC_PE_HEADERSIZE, m_headerSize);
	DDX_Text(pDX, IDC_PE_FILESUBSYS, m_fileSystem);
	DDX_Text(pDX, IDC_PE_DLLCHAR, m_dllCharacteristics);
	DDX_Text(pDX, IDC_PE_DIRNUM, m_directoryNumber);
	DDX_Control(pDX, IDC_PE_RVAEDIT, m_rvaEdit);
	DDX_Control(pDX, IDC_PE_VAEDIT, m_vaEdit);
	DDX_Control(pDX, IDC_PE_FOA_EDIT, m_foaEdit);
	DDX_Control(pDX, IDC_PE_DIRBTN, m_dirBtn);
	DDX_Control(pDX, IDC_PE_SECBTN, m_secBtn);
}


BEGIN_MESSAGE_MAP(VytPeLoaderDlg, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// VytPeLoaderDlg 消息处理程序


BOOL VytPeLoaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x49, MSGFLT_ADD);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VytPeLoaderDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[MAX_PATH] = {};
	DragQueryFile(hDropInfo, 0, (TCHAR*)szFileName, MAX_PATH);
	if (!m_peInfo.LoadPe(szFileName))
		MessageBox(_T("错误的PE文件"), _T("提示"), MB_OK);
	else
		DisplayPeInfo();

	CDialogEx::OnDropFiles(hDropInfo);
}
