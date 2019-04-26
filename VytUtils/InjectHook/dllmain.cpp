// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <tchar.h>

#define DEF_PTR(name, type, value) type name = (type)((size_t)pBase + (value));

void IatHook(LPCSTR szDllName, LPCSTR funcname, LPVOID newaddr, size_t &oldaddr)
{
	// 获取当前进程基址
	LPVOID pBase = (LPVOID)GetModuleHandle(NULL);

	// 找到导入表，遍历IAT
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)pBase;
	DEF_PTR(pNt, PIMAGE_NT_HEADERS, pDos->e_lfanew);
	auto importRva = pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	DEF_PTR(pImport, PIMAGE_IMPORT_DESCRIPTOR, importRva);
	while (NULL != pImport->Name)
	{
		DEF_PTR(pDllname, LPCSTR, pImport->Name);
		// stricmp不区分大小写
		if (0 == _stricmp(szDllName, pDllname))
		{
			DEF_PTR(pINT, PIMAGE_THUNK_DATA, pImport->OriginalFirstThunk);
			DEF_PTR(pIAT, PIMAGE_THUNK_DATA, pImport->FirstThunk);
			while (NULL != pIAT->u1.AddressOfData)
			{
				DEF_PTR(fn, PIMAGE_IMPORT_BY_NAME, pINT->u1.ForwarderString);
				if (!_stricmp(fn->Name, funcname))
				{
					// 保存原API地址
					oldaddr = pIAT->u1.Function;
					// 修改成新的地址
					DWORD protect;
					VirtualProtect(pIAT, 4, PAGE_EXECUTE_READWRITE, &protect);
					pIAT->u1.Function = (size_t)newaddr;
					VirtualProtect(pIAT, 4, protect, &protect);
					return;
				}
				++pINT;
				++pIAT;
			}
		}
		++pImport;
	}
}

size_t oldaddr;

#define cp(u,l,n) (szProcessPath[i+n] == _T(#@u) || szProcessPath[i+n] == _T(#@l))

BOOL WINAPI VytTerminateProcess(_In_ HANDLE hProcess, _In_ UINT uExitCode)
{
	TCHAR szProcessPath[MAX_PATH];
	DWORD size;
	QueryFullProcessImageName(hProcess, PROCESS_NAME_NATIVE, szProcessPath, &size);
	for (DWORD i = 0; i < size - 2; ++i)
		if (cp(V, v, 0) && cp(Y, y, 1) && cp(T, t, 2))
			return FALSE;
	return ((BOOL(WINAPI *)(_In_ HANDLE hProcess, _In_ UINT uExitCode))(oldaddr))(hProcess, uExitCode);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		IatHook("kernel32.dll", "TerminateProcess", VytTerminateProcess, oldaddr);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

