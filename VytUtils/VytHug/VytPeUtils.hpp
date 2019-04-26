#ifndef VYTERM_PORTABLE_EXECUTABLE_UTILS_HPP_INCLUDED
#define VYTERM_PORTABLE_EXECUTABLE_UTILS_HPP_INCLUDED

#include <map>
#include <deque>
#include <functional>

namespace vyt
{
	struct FunctionField
	{
		WORD Ordinal;
		LPCSTR Name;
		DWORD Rva;
	};

	struct ResourceField
	{
		union {
			WORD Id;
			LPCWSTR Name;
		} u;
		enum E_Layer { Type, Item } Layer;
		bool NameIsString;
		ResourceField(WORD id, E_Layer layer) : NameIsString(false), Layer(layer) { u.Id = id; }
		ResourceField(LPCWSTR name, E_Layer layer) : NameIsString(true), Layer(layer) { u.Name = name; }
	};

	struct RelocationField
	{
		DWORD Rva;
		DWORD Foa;
		WORD Type;
		DWORD Data;
	};

	class PeUtils
	{
		LPVOID m_pBuffer;
		PIMAGE_NT_HEADERS m_pNtHeader;
		std::map<WORD, PIMAGE_DATA_DIRECTORY> m_directorys;
		std::deque<PIMAGE_SECTION_HEADER> m_sections;
	private:
		static LPVOID LoadFileToMemory(LPCTSTR path);
		template <typename TPointer>
		inline TPointer RvaToPointer(DWORD rva) { return (TPointer)((DWORD)m_pBuffer + RvaToFoa(rva)); }
	public:
		PeUtils();
		~PeUtils();
		bool IsLoad() const;
		bool LoadPe(LPCTSTR path);
		void Unload();

		DWORD RvaToFoa(DWORD rva) const;
		DWORD FoaToRva(DWORD foa) const;
		LONG NtOffset() const;
		const IMAGE_FILE_HEADER& FileHeader() const;
		const IMAGE_OPTIONAL_HEADER& OptionalHeader() const;
		const std::map<WORD, PIMAGE_DATA_DIRECTORY>& Directorys() const;
		const std::deque<PIMAGE_SECTION_HEADER>& Sections() const;
		bool ForeachExportTable(std::function<void(LPCSTR)> nameAction, std::function<void(FunctionField)> funcAction);
		bool ForeachImportTable(std::function<void(LPCSTR, PIMAGE_IMPORT_DESCRIPTOR)> importAction);
		void ForeachImportTable(PIMAGE_IMPORT_DESCRIPTOR descriptor, std::function<void(WORD, LPCSTR)> funcAction, bool useIat = false);
		bool ForeachResourceTable(std::function<void(ResourceField)> resourceAction, std::function<void(PIMAGE_RESOURCE_DATA_ENTRY)> dataAction);
		bool ForeachRelocationTable(std::function<void(RelocationField)> relocationAction);
		bool ForeachTlsTable(std::function<void(PIMAGE_TLS_DIRECTORY)> tlsAction);
		bool ForeachDelayTable();
	};
}

#endif