#include <windows.h>
#include <string>
#include "VytSnapshotUtils.hpp"

void InjectDll(LPCSTR dllPath, DWORD pid)
{
	// 1. ��ȡĿ����̾��
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (NULL == process)
		return;
	// 2. ��Ŀ�����������һ���ڴ�(��С��DLL·���ĳ���)
	LPVOID buffer = VirtualAllocEx(process, nullptr, 0x1000, MEM_COMMIT, PAGE_READWRITE);
	// 3. ��dll·��д�뵽Ŀ�������
	WriteProcessMemory(process, buffer, dllPath, strlen(dllPath), nullptr);
	// 4. ����Զ���̣߳�32λ����ֻ��ע��32λ����
	HANDLE thread = CreateRemoteThread(process, nullptr, 0/*ʹ��Ĭ��ջ��С*/,
		(LPTHREAD_START_ROUTINE)LoadLibraryA, buffer, 0, nullptr);
	// 5. �ȴ�Զ���߳̽���
	WaitForSingleObject(thread, INFINITE);
	// 6. �ͷ���Դ
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