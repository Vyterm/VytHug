#include <windows.h>
#include <string>
#include "VytSnapshotUtils.hpp"

void InjectDll(LPCSTR dllPath, DWORD pid)
{
	// 1. 获取目标进程句柄
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (NULL == process)
		return;
	// 2. 从目标进程中申请一块内存(大小是DLL路径的长度)
	LPVOID buffer = VirtualAllocEx(process, nullptr, 0x1000, MEM_COMMIT, PAGE_READWRITE);
	// 3. 将dll路径写入到目标进程中
	WriteProcessMemory(process, buffer, dllPath, strlen(dllPath), nullptr);
	// 4. 创建远程线程，32位程序只能注入32位程序
	HANDLE thread = CreateRemoteThread(process, nullptr, 0/*使用默认栈大小*/,
		(LPTHREAD_START_ROUTINE)LoadLibraryA, buffer, 0, nullptr);
	// 5. 等待远程线程结束
	WaitForSingleObject(thread, INFINITE);
	// 6. 释放资源
	VirtualFreeEx(process, buffer, 0, MEM_RELEASE);
	CloseHandle(thread);
	CloseHandle(process);
}

int main()
{
	LPCSTR path = "C:\\Common Projects\\VytHug\\VytUtils\\VytProtect\\InjectHook.dll";
	vyt::SnapshotUtils::EnumProcess([path](const PROCESSENTRY32 &process) {
		std::string exepath(process.szExeFile);
		if (exepath.find("taskmgr.exe") == std::string::npos) return;
		InjectDll(path, process.th32ProcessID);
	});

	return 0;
}