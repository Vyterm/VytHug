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

bool vyt::ComputerUtils::CheckAdmin()
{
	// 1. 获取本进程的令牌
	HANDLE token = NULL;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
		return false;
	// 2. 获取提升类型
	TOKEN_ELEVATION_TYPE elevationType = TokenElevationTypeDefault;
	BOOL isAdmin = FALSE;
	DWORD size = 0;
	if (GetTokenInformation(token, TokenElevationType, &elevationType, sizeof(TOKEN_ELEVATION_TYPE), &size))
	{
		// 2.1. 创建管理员组的对应SID
		BYTE adminSID[SECURITY_MAX_SID_SIZE];
		size = sizeof(adminSID);
		CreateWellKnownSid(WinBuiltinAdministratorsSid, nullptr, &adminSID, &size);
		// 2.2. 判断当前进程运行用户角色是否为管理员
		if (elevationType == TokenElevationTypeLimited)
		{
			// a. 获取连接令牌的句柄
			HANDLE unfilteredToken = NULL;
			GetTokenInformation(token, TokenLinkedToken, (LPVOID)&unfilteredToken, sizeof(HANDLE), &size);
			// b. 检查这个原始的令牌是否包含管理员的SID
			if (!CheckTokenMembership(unfilteredToken, &adminSID, &isAdmin))
				return false;
			CloseHandle(unfilteredToken);
		}
		else
			isAdmin = IsUserAnAdmin();
		CloseHandle(token);
	}
	// 3. 判断具体的权限情况
	bool fullToken = false;
	switch (elevationType)
	{
		// 默认的用户或UAC被禁用，则默认用户有管理员权限或默认用户不是管理员组
	case TokenElevationTypeDefault:
		// 已经成功提高进程权限，则当前以管理员权限运行或当前未以管理员权限运行
	case TokenElevationTypeFull:
		fullToken = IsUserAnAdmin();
		break;
		// 进程在以有限的权限运行
	case TokenElevationTypeLimited:
		fullToken = false;
		break;
	}
	return fullToken;
}

bool vyt::ComputerUtils::RunasAdmin()
{
	// 1. 获取当前程序路径
	TCHAR szApplication[MAX_PATH] = {};
	DWORD cchLength = _countof(szApplication);
	QueryFullProcessImageName(GetCurrentProcess(), 0, szApplication, &cchLength);
	// 2. 以管理员权限重新打开进程
	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = _T("runas");
	sei.lpFile = szApplication;
	sei.lpParameters = nullptr;
	sei.nShow = SW_SHOWNORMAL;
	if (ShellExecuteEx(&sei))
		return true;
	else
		return false;
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
