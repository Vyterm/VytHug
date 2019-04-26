#include "VytSnapshotUtils.hpp"

void vyt::SnapshotUtils::EnumProcess(std::function<void(const PROCESSENTRY32&)> processAction)
{
	HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 processInfo = { sizeof(PROCESSENTRY32) };
	if (Process32First(processSnapshot, &processInfo))
	{
		do
		{
			processAction(processInfo);
		} while (Process32Next(processSnapshot, &processInfo));
	}
	CloseHandle(processSnapshot);
}

void vyt::SnapshotUtils::EnumThread(std::function<void(const THREADENTRY32&)> threadAction)
{
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	THREADENTRY32 threadInfo = { sizeof(THREADENTRY32) };
	if (Thread32First(snapshot, &threadInfo))
	{
		do
		{
			threadAction(threadInfo);
		} while (Thread32Next(snapshot, &threadInfo));
	}
	CloseHandle(snapshot);
}

void vyt::SnapshotUtils::EnumModule(DWORD processID, std::function<void(const MODULEENTRY32&)> moduleAction)
{
	HANDLE moduleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
	MODULEENTRY32 moduleInfo = { sizeof(MODULEENTRY32) };
	if (Module32First(moduleSnapshot, &moduleInfo))
	{
		do
		{
			moduleAction(moduleInfo);
		} while (Module32Next(moduleSnapshot, &moduleInfo));
	}
	CloseHandle(moduleSnapshot);
}

void vyt::SnapshotUtils::EnumHeap(DWORD processID, std::function<void(const HEAPENTRY32&)> heapAction)
{
	HANDLE moduleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, processID);
	HEAPLIST32 heapList = { sizeof(HEAPLIST32) };
	if (Heap32ListFirst(moduleSnapshot, &heapList))
	{
		do
		{
			HEAPENTRY32 heapInfo = { sizeof(HEAPENTRY32) };
			Heap32First(&heapInfo, processID, heapList.th32HeapID);
			heapAction(heapInfo);
		} while (Heap32ListNext(moduleSnapshot, &heapList));
	}
	CloseHandle(moduleSnapshot);
}
