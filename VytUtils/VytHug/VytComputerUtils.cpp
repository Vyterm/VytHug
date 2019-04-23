#include "stdafx.h"
#include "VytComputerUtils.hpp"
#include "VytSnapshotUtils.hpp"
#include <Psapi.h>
using namespace vyt;

inline double FileTimeToDouble(const FILETIME &fileTime)
{
	return double(fileTime.dwHighDateTime*4.294967296e9) + double(fileTime.dwLowDateTime);
}

int vyt::ComputerUtils::CpuUtilization()
{
	static FILETIME idleTime = {}, kernelTime = {}, userTime = {};
	FILETIME newIdleTime, newKernelTime, newUserTime;
	GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);
	double idleDelta = FileTimeToDouble(newIdleTime) - FileTimeToDouble(idleTime);
	idleTime = newIdleTime;
	double kernelDelta = FileTimeToDouble(newKernelTime) - FileTimeToDouble(kernelTime);
	kernelTime = newKernelTime;
	double userDelta = FileTimeToDouble(newUserTime) - FileTimeToDouble(userTime);
	userTime = newUserTime;
	return int(100.0 - idleDelta / (kernelDelta + userDelta)*100.0);
}

int vyt::ComputerUtils::MemoryUtilization()
{
	MEMORYSTATUS memoryStatus;
	GlobalMemoryStatus(&memoryStatus);
	return int(double(memoryStatus.dwTotalPhys - memoryStatus.dwAvailPhys) / memoryStatus.dwTotalPhys * 100.0);
}

unsigned __int64 vyt::ComputerUtils::Cleanmemory()
{
	// 获取清理前的可用内存
	MEMORYSTATUSEX status = { sizeof(MEMORYSTATUSEX) };
	GlobalMemoryStatusEx(&status);
	auto preUsed = status.ullTotalPhys - status.ullAvailPhys;
	// 遍历进程进行清理
	SnapshotUtils::EnumProcess([](const PROCESSENTRY32& processInfo) {
		HANDLE process = OpenProcess(PROCESS_SET_QUOTA, FALSE, processInfo.th32ProcessID);
		if (NULL != process)
		{
			SetProcessWorkingSetSize(process, -1, -1);
			EmptyWorkingSet(process);
			CloseHandle(process);
		}
	});
	// 获取清理后的可用内存
	GlobalMemoryStatusEx(&status);
	auto afterUsed = status.ullTotalPhys - status.ullAvailPhys;
	return preUsed - afterUsed;
}

void vyt::ComputerUtils::Poweroff()
{
}

void vyt::ComputerUtils::Restart()
{
}

void vyt::ComputerUtils::Logout()
{
}

void vyt::ComputerUtils::Dormancy()
{
}

void vyt::ComputerUtils::LockScreen()
{
}
