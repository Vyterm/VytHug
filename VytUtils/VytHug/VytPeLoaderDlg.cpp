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
	, m_isValueUpdating(false)
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
	, m_addressOption(FALSE)
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

void VytPeLoaderDlg::UpdateOption()
{
	UpdateData(TRUE);
	m_rvaEdit.EnableWindow(m_addressOption == 0 ? TRUE : FALSE);
	m_vaEdit.EnableWindow(m_addressOption == 1 ? TRUE : FALSE);
	m_foaEdit.EnableWindow(m_addressOption == 2 ? TRUE : FALSE);
}

inline CString Hex(DWORD value)
{
	CString hex;
	hex.Format(_T("%08X"), value);
	return hex;
}

#define rva2foa() m_foa = m_peInfo.RvaToFoa(m_rva)
#define foa2rva() m_rva = m_peInfo.FoaToRva(m_foa)
#define rva2va() m_va = m_rva + m_peInfo.OptionalHeader().ImageBase
#define va2rva() m_rva = m_va - m_peInfo.OptionalHeader().ImageBase
#define foa2va() foa2rva(); rva2va();
#define va2foa() va2rva(); rva2foa();

// 第一次使用时写出了##srcEdit这样的写法导致替换失效
// 参考自 https://www.cnblogs.com/Anker/p/3418792.html 解决了该问题

#define UpdateValueTemplate(src,v1,v2) {\
CString str; \
m_##src## Edit.GetWindowText(str); \
_stscanf_s(str, _T("%X"), &m_##src); \
##src## 2##v1(); \
##src## 2##v2(); \
m_##v1## Edit.SetWindowText(Hex(m_##v1)); \
m_##v2## Edit.SetWindowText(Hex(m_##v2)); \
}

void VytPeLoaderDlg::UpdateValue()
{
	// SetWindowText会触发ON_EN_CHANGE事件，因此在更新值的时候可能意外的反复调用自身
	if (m_isValueUpdating) return;
	m_isValueUpdating = true;
	UpdateData(TRUE);
	switch (m_addressOption)
	{
	case 0: UpdateValueTemplate(rva, va, foa); break;
	case 1: UpdateValueTemplate(va, rva, foa); break;
	case 2: UpdateValueTemplate(foa, rva, va); break;
	default: break;
	}
	m_isValueUpdating = false;
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
	DDX_Radio(pDX, IDC_PE_RADIORVA, m_addressOption);
}


BEGIN_MESSAGE_MAP(VytPeLoaderDlg, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_PE_RADIORVA, &VytPeLoaderDlg::OnBnClickedPeRadiorva)
	ON_BN_CLICKED(IDC_PE_RADIOVA, &VytPeLoaderDlg::OnBnClickedPeRadiova)
	ON_BN_CLICKED(IDC_PE_RADIOFOA, &VytPeLoaderDlg::OnBnClickedPeRadiofoa)
	ON_EN_CHANGE(IDC_PE_RVAEDIT, &VytPeLoaderDlg::OnEnChangePeRvaedit)
	ON_EN_CHANGE(IDC_PE_VAEDIT, &VytPeLoaderDlg::OnEnChangePeVaedit)
	ON_EN_CHANGE(IDC_PE_FOA_EDIT, &VytPeLoaderDlg::OnEnChangePeFoaEdit)
END_MESSAGE_MAP()


// VytPeLoaderDlg 消息处理程序


BOOL VytPeLoaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x49, MSGFLT_ADD);
	m_addressOption = 0;
	UpdateData(FALSE);
	UpdateOption();

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


void VytPeLoaderDlg::OnBnClickedPeRadiorva()
{
	UpdateOption();
}


void VytPeLoaderDlg::OnBnClickedPeRadiova()
{
	UpdateOption();
}


void VytPeLoaderDlg::OnBnClickedPeRadiofoa()
{
	UpdateOption();
}


void VytPeLoaderDlg::OnEnChangePeRvaedit()
{
	UpdateValue();
}


void VytPeLoaderDlg::OnEnChangePeVaedit()
{
	UpdateValue();
}


void VytPeLoaderDlg::OnEnChangePeFoaEdit()
{
	UpdateValue();
}
