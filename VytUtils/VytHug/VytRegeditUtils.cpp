#include "stdafx.h"
#include "VytRegeditUtils.hpp"

void vyt::RegeditUtils::EnumServices(std::function<void(const ENUM_SERVICE_STATUS_PROCESS&, const QUERY_SERVICE_CONFIG&)> serviceAction)
{
	// 1. 打开远程计算机服务控制管理器
	SC_HANDLE scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
	// 2. 获取所有服务状态
	DWORD serviceCount = 0, size = 0;
	EnumServicesStatusEx(scm, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL, nullptr, 0, &size, &serviceCount, nullptr, nullptr);
	PBYTE serviceStatusBuffer = new BYTE[size];
	EnumServicesStatusEx(scm, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL, serviceStatusBuffer, size, &size, &serviceCount, nullptr, nullptr);
	// 3. 遍历服务信息
	LPENUM_SERVICE_STATUS_PROCESS serviceStatus = (LPENUM_SERVICE_STATUS_PROCESS)serviceStatusBuffer;
	for (DWORD i = 0; i < serviceCount; ++i, ++serviceStatus)
	{
		SC_HANDLE service = OpenService(scm, serviceStatus->lpServiceName, SERVICE_QUERY_CONFIG);
		QueryServiceConfig(service, nullptr, 0, &size);
		auto serviceConfigBuffer = new BYTE[size];
		QueryServiceConfig(service, (LPQUERY_SERVICE_CONFIG)serviceConfigBuffer, size, &size);
		serviceAction(*serviceStatus, *(LPQUERY_SERVICE_CONFIG)serviceConfigBuffer);
		delete[] serviceConfigBuffer;
		// 这个句柄关闭后将导致服务管理器句柄失效
		//CloseServiceHandle(service);
	}
	delete[] serviceStatusBuffer;
	CloseServiceHandle(scm);
}

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	auto &action = *(std::function<void(HWND)>*)lParam;
	action(hwnd);
	return TRUE;
}

void vyt::RegeditUtils::EnumWindows(std::function<void(HWND)> windowAction)
{
	::EnumWindows(&EnumWindowsProc, (LPARAM)&windowAction);
}
