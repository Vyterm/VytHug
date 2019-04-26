#include "stdafx.h"
#include "VytPeUtils.hpp"
using namespace vyt;

LPVOID PeUtils::LoadFileToMemory(LPCTSTR path)
{
	FILE *file;
	_tfopen_s(&file, path, _T("rb"));
	if (nullptr == file)
		return nullptr;
	fseek(file, 0, SEEK_END);
	auto size = ftell(file);
	fseek(file, 0, SEEK_SET);
	LPVOID buffer = new BYTE[size];
	fread(buffer, size, 1, file);
	return buffer;
}

PeUtils::PeUtils() :
	m_pBuffer(nullptr),
	m_pNtHeader(nullptr)
{
}

PeUtils::~PeUtils()
{
	Unload();
}

bool PeUtils::IsLoad() const
{
	return nullptr != m_pBuffer;
}

#define LOAD_EXIT_FAILED { Unload(); return false; }
#define LOAD_EXIT_SUCCESS { return true; }

bool PeUtils::LoadPe(LPCTSTR path)
{
	Unload();
	m_pBuffer = LoadFileToMemory(path);
	if (nullptr == m_pBuffer)
		LOAD_EXIT_FAILED
		m_pNtHeader = nullptr;
	IMAGE_DOS_HEADER *pDosHeader = (IMAGE_DOS_HEADER*)m_pBuffer;
	if (IMAGE_DOS_SIGNATURE != pDosHeader->e_magic)
		LOAD_EXIT_FAILED
		m_pNtHeader = (IMAGE_NT_HEADERS*)((LONG)m_pBuffer + pDosHeader->e_lfanew);
	if (IMAGE_NT_SIGNATURE != m_pNtHeader->Signature)
		LOAD_EXIT_FAILED
	m_directorys[IMAGE_DIRECTORY_ENTRY_EXPORT        ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT        ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_IMPORT        ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT        ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_RESOURCE      ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE      ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_EXCEPTION     ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION     ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_SECURITY      ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY      ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_BASERELOC     ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC     ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_DEBUG         ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG         ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE  ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE  ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_GLOBALPTR     ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR     ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_TLS           ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS           ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG   ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG   ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT  ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT  ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_IAT           ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT           ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT  ] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT  ];
	m_directorys[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR] = &m_pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR];
	auto pSectionHeader = IMAGE_FIRST_SECTION(m_pNtHeader);
	for (DWORD i = 0; i < m_pNtHeader->FileHeader.NumberOfSections; ++i)
		m_sections.push_back(&pSectionHeader[i]);
	LOAD_EXIT_SUCCESS
}

void PeUtils::Unload()
{
	if (nullptr == m_pBuffer) return;
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
	m_pNtHeader = nullptr;
	m_directorys.clear();
	m_sections.clear();
}

DWORD PeUtils::RvaToFoa(DWORD rva) const
{
	for (auto &section : m_sections)
		if (rva >= section->VirtualAddress && rva <= section->VirtualAddress + section->SizeOfRawData)
			return rva - section->VirtualAddress + section->PointerToRawData;
	return 0;
}

DWORD PeUtils::FoaToRva(DWORD foa) const
{
	for (auto &section : m_sections)
		if (foa >= section->PointerToRawData && foa <= section->PointerToRawData + section->SizeOfRawData)
			return foa - section->PointerToRawData + section->VirtualAddress;
	return 0;
}

LONG vyt::PeUtils::NtOffset() const
{
	return ((PIMAGE_DOS_HEADER)m_pBuffer)->e_lfanew;
}

const IMAGE_FILE_HEADER& PeUtils::FileHeader() const
{
	return m_pNtHeader->FileHeader;
}

const IMAGE_OPTIONAL_HEADER& PeUtils::OptionalHeader() const
{
	return m_pNtHeader->OptionalHeader;
}

const std::map<WORD, PIMAGE_DATA_DIRECTORY>& PeUtils::Directorys() const
{
	return m_directorys;
}

const std::deque<PIMAGE_SECTION_HEADER>& PeUtils::Sections() const
{
	return m_sections;
}

bool vyt::PeUtils::ForeachExportTable(std::function<void(LPCSTR)> nameAction, std::function<void(FunctionField)> funcAction)
{
	auto exportRva = m_directorys[IMAGE_DIRECTORY_ENTRY_EXPORT]->VirtualAddress;
	if (NULL == exportRva)
		return false;
	PIMAGE_EXPORT_DIRECTORY pExport = RvaToPointer<PIMAGE_EXPORT_DIRECTORY>(exportRva);
	// 输出模块名
	nameAction(RvaToPointer<LPCSTR>(pExport->Name));
	// 遍历导出表
	PDWORD pFunctions = RvaToPointer<PDWORD>(pExport->AddressOfFunctions);
	PDWORD pFuncNames = RvaToPointer<PDWORD>(pExport->AddressOfNames);
	PWORD pFuncOrdins = RvaToPointer<PWORD>(pExport->AddressOfNameOrdinals);
	for (DWORD i = 0; i < pExport->NumberOfFunctions; ++i)
	{
		// 判断是否是有效的函数地址
		if (NULL == pFunctions[i]) continue;
		// 判断函数是否有名称
		LPCSTR funcname = "";
		//	 遍历序号表判断是否存在此序号
		for (DWORD in = 0; in < pExport->NumberOfNames; ++in)
		{
			// 序号表中的序号不需要加上基数，使用序号调用才会加上基数
			if (i == pFuncOrdins[in]/* + pExport->Base*/)
				funcname = RvaToPointer<LPCSTR>(pFuncNames[in]);
		}
		// 使用序号调用减去基数为函数表中的下标
		funcAction({ WORD(i + pExport->Base),funcname,pFunctions[i] });
	}
	return true;
}

bool vyt::PeUtils::ForeachImportTable(std::function<void(LPCSTR, PIMAGE_IMPORT_DESCRIPTOR)> importAction)
{
	auto importRva = m_directorys[IMAGE_DIRECTORY_ENTRY_IMPORT]->VirtualAddress;
	if (NULL == importRva)
		return false;
	PIMAGE_IMPORT_DESCRIPTOR pImport = RvaToPointer<PIMAGE_IMPORT_DESCRIPTOR>(importRva);
	for (; NULL != pImport->Name; ++pImport)
		importAction(RvaToPointer<LPCSTR>(pImport->Name), pImport);
	return true;
}

void vyt::PeUtils::ForeachImportTable(PIMAGE_IMPORT_DESCRIPTOR descriptor, std::function<void(WORD, LPCSTR)> funcAction, bool useIat/* = false*/)
{
	auto iat = RvaToPointer<PIMAGE_THUNK_DATA>(useIat ? descriptor->FirstThunk : descriptor->OriginalFirstThunk);
	while (NULL != iat->u1.AddressOfData)
	{
		if (IMAGE_SNAP_BY_ORDINAL(iat->u1.Ordinal))
			funcAction(WORD(iat->u1.Ordinal&~0x80000000), nullptr);
		else
		{
			auto pibn = RvaToPointer<PIMAGE_IMPORT_BY_NAME>(iat->u1.AddressOfData);
			funcAction(pibn->Hint, (LPCSTR)pibn->Name);
		}
		++iat;
	}
}

#define ShowResourceTable_PrintEntryName(entry, layer) {\
if (entry->NameIsString != FALSE) {\
	PIMAGE_RESOURCE_DIR_STRING_U pName = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)rootDirectory + entry->NameOffset);\
	WCHAR *pBuffer = new WCHAR[pName->Length + 1];\
	memcpy_s(pBuffer, pName->Length * 2, pName->NameString, pName->Length * 2);\
	pBuffer[pName->Length] = NULL;\
	resourceAction({pBuffer, layer});\
	delete[] pBuffer; }\
else resourceAction({ entry->Id, layer });\
}

bool vyt::PeUtils::ForeachResourceTable(std::function<void(ResourceField)> resourceAction, std::function<void(PIMAGE_RESOURCE_DATA_ENTRY)> dataAction)
{
	auto resourceRva = m_directorys[IMAGE_DIRECTORY_ENTRY_RESOURCE]->VirtualAddress;
	if (NULL == resourceRva)
		return false;

	PIMAGE_RESOURCE_DIRECTORY rootDirectory = RvaToPointer<PIMAGE_RESOURCE_DIRECTORY>(resourceRva);
	// 第一层，资源的种类
	DWORD typeCount = rootDirectory->NumberOfIdEntries + rootDirectory->NumberOfNamedEntries;
	PIMAGE_RESOURCE_DIRECTORY_ENTRY typeEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(rootDirectory + 1);
	for (DWORD typeIndex = 0; typeIndex < typeCount; ++typeIndex, ++typeEntry)
	{
		ShowResourceTable_PrintEntryName(typeEntry, ResourceField::Type);
		// 判断是否有下一层
		if (typeEntry->DataIsDirectory)
		{
			// 第二层，资源的个数
			PIMAGE_RESOURCE_DIRECTORY typeDirectory = (PIMAGE_RESOURCE_DIRECTORY)(typeEntry->OffsetToDirectory + (DWORD)rootDirectory);
			DWORD itemCount = typeDirectory->NumberOfIdEntries + typeDirectory->NumberOfNamedEntries;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY itemEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(typeDirectory + 1);
			for (DWORD itemIndex = 0; itemIndex < itemCount; ++itemIndex, ++itemEntry)
			{
				// 某个资源的每一个资源的名字
				ShowResourceTable_PrintEntryName(itemEntry, ResourceField::Item);
				if (itemEntry->DataIsDirectory)
				{
					PIMAGE_RESOURCE_DIRECTORY itemDirectory = (PIMAGE_RESOURCE_DIRECTORY)(itemEntry->OffsetToDirectory + (DWORD)rootDirectory);
					assert(1 == (itemDirectory->NumberOfIdEntries + itemDirectory->NumberOfNamedEntries));
					PIMAGE_RESOURCE_DIRECTORY_ENTRY dataEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(itemDirectory + 1);
					assert(FALSE == dataEntry->DataIsDirectory);
					PIMAGE_RESOURCE_DATA_ENTRY pData = (PIMAGE_RESOURCE_DATA_ENTRY)(dataEntry->OffsetToData + (DWORD)rootDirectory);
					dataAction(pData);
				}
			}
		}
	}
	return true;
}

bool vyt::PeUtils::ForeachRelocationTable(std::function<void(RelocationField)> relocationAction)
{
	auto relocRva = m_directorys[IMAGE_DIRECTORY_ENTRY_BASERELOC]->VirtualAddress;
	if (NULL == relocRva)
		return false;
	auto pRelocation = RvaToPointer<PIMAGE_BASE_RELOCATION>(relocRva);
	struct TypeOffset
	{
		WORD Offset : 12;
		WORD Type : 4;
	};
	while (NULL != pRelocation->SizeOfBlock)
	{
		TypeOffset *pOffset = (TypeOffset*)(pRelocation + 1);
		DWORD count = (pRelocation->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(TypeOffset);
		for (DWORD i = 0; i < count; ++i)
		{
			if (pOffset[i].Type == 3)
			{
				DWORD dataRva = pRelocation->VirtualAddress + pOffset[i].Offset;
				DWORD dataFoa = RvaToFoa(dataRva);
				PDWORD pData = RvaToPointer<PDWORD>(dataRva);
				relocationAction({ dataRva, dataFoa, pOffset[i].Type, *pData });
			}
		}
		pRelocation = (PIMAGE_BASE_RELOCATION)((DWORD)pRelocation + pRelocation->SizeOfBlock);
	}
	return true;
}

bool vyt::PeUtils::ForeachTlsTable()
{
	return false;
}

bool vyt::PeUtils::ForeachDelayTable()
{
	return false;
}
