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

void vyt::RegeditUtils::ServiceStart(CString serviceName)
{
	SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE service = OpenService(scm, serviceName, SERVICE_START);
	StartService(service, 0, nullptr);
	CloseServiceHandle(scm);
	CloseServiceHandle(service);
}

void vyt::RegeditUtils::ServicePause(CString serviceName)
{
	SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE service = OpenService(scm, serviceName, SERVICE_STOP);
	SERVICE_STATUS status;
	ControlService(service, SERVICE_CONTROL_STOP, &status);
	CloseServiceHandle(scm);
	CloseServiceHandle(service);
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

bool vyt::RegeditUtils::Is64BitOS()
{
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	return si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64;
}

#define EnumRegeditTemplate(token) HKEY result = NULL;\
if (ERROR_SUCCESS != RegOpenKeyEx(rootKey, subKey, 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE, &result)) return;\
DWORD index = 0;\
TCHAR keyName[MAX_PATH] = {};\
DWORD keyLen = MAX_PATH;\
while (ERROR_NO_MORE_ITEMS != RegEnum##token(result, index++, keyName, &keyLen, 0, nullptr, nullptr, nullptr)) {\
	CString keyBuffer = keyName;\
	ZeroMemory(keyName, MAX_PATH);\
	keyLen = MAX_PATH;\
	if (!keyBuffer.IsEmpty())\
		keyAction(result, keyBuffer);\
} RegCloseKey(result);

static void EnumRegeditKey(HKEY rootKey, LPCTSTR subKey, std::function<void(const HKEY&,CString&)> keyAction)
{
	EnumRegeditTemplate(KeyEx);
}

static void EnumRegeditValue(HKEY rootKey, LPCTSTR subKey, std::function<void(const HKEY&, CString&)> keyAction)
{
	EnumRegeditTemplate(Value);
}

void vyt::RegeditUtils::EnumSoftwares(std::function<void(SoftwareInfo&)> softwareAction)
{
	constexpr LPCTSTR Win32Path = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	constexpr LPCTSTR Win64Path = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	// 1. 打开注册表键
	HKEY rootKey = HKEY_LOCAL_MACHINE;
	LPCTSTR subKey = Is64BitOS() ? Win64Path : Win32Path;
	EnumRegeditKey(rootKey, subKey, [&](const HKEY &key, CString &keyBuffer) {
		// 2.1. 通过得到的子键名称重新组合成新的子键路径
		CString newBuffer;// 某些情况下使用keyBuffer.Format会抛出Buffer is too small异常，因此重新定义一个CString进行Format
		newBuffer.Format(_T("%s\\%s"), subKey, keyBuffer);
		// 2.2. 打开新的子键，获取其句柄
		HKEY softkey = NULL;
		if (ERROR_SUCCESS != RegOpenKeyEx(rootKey, newBuffer, 0, KEY_QUERY_VALUE, &softkey)) return;
		// 2.3. 获取键值
		SoftwareInfo software = {};
		DWORD nameLen = _countof(software.szSoftName);
		RegQueryValueEx(softkey, _T("DisplayName"), 0, nullptr, (LPBYTE)software.szSoftName, &nameLen);
		if (NULL == software.szSoftName[0]) return;
		nameLen = _countof(software.szSoftVersion);
		RegQueryValueEx(softkey, _T("DisplayVersion"), 0, nullptr, (LPBYTE)software.szSoftVersion, &nameLen);
		nameLen = _countof(software.szSoftInsPath);
		RegQueryValueEx(softkey, _T("InstallLocation"), 0, nullptr, (LPBYTE)software.szSoftInsPath, &nameLen);
		nameLen = _countof(software.szSoftVenRel);
		RegQueryValueEx(softkey, _T("Publisher"), 0, nullptr, (LPBYTE)software.szSoftVenRel, &nameLen);
		nameLen = _countof(software.szSoftUniPath);
		RegQueryValueEx(softkey, _T("UninstallString"), 0, nullptr, (LPBYTE)software.szSoftUniPath, &nameLen);
		nameLen = _countof(software.szSoftDate);
		RegQueryValueEx(softkey, _T("InstallDate"), 0, nullptr, (LPBYTE)software.szSoftDate, &nameLen);
		softwareAction(software);
	});
}

#define EnumBootstrapsTemplate(kr, ks) \
EnumRegeditValue(kr, _T(#ks), [&](const HKEY &key, CString &keyBuffer) {\
	vyt::RegeditUtils::BootstrapInfo bootstrapInfo;\
	bootstrapInfo.bootName = keyBuffer;\
	DWORD orderLen = MAX_PATH;\
	RegQueryValueEx(key, keyBuffer, 0, nullptr, (LPBYTE)bootstrapInfo.bootOrder.GetBuffer(orderLen), &orderLen);\
	bootstrapInfo.key = kr;\
	bootstrapInfo.bootPos = _T(#ks);\
	bootstrapInfo.bootPos_All = _T(#kr"\\"#ks);\
	bootstrapAction(bootstrapInfo);\
});

void vyt::RegeditUtils::EnumBootstraps(std::function<void(BootstrapInfo&)> bootstrapAction)
{
	EnumBootstrapsTemplate(HKEY_CURRENT_USER, SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run);
	EnumBootstrapsTemplate(HKEY_LOCAL_MACHINE, SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run);
}

bool vyt::RegeditUtils::AppendBootstrap(CString keyname, CString exepath)
{
	HKEY key;
	auto ret = RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_WRITE, &key);
	if (ret != ERROR_SUCCESS) return false;
	ret = RegSetValueEx(key, keyname, 0, REG_SZ, (PBYTE)exepath.GetString(), exepath.GetLength()*sizeof(TCHAR));
	RegCloseKey(key);
	return ret == ERROR_SUCCESS;
}

bool vyt::RegeditUtils::DeleteBootstrap(const BootstrapInfo & bootInfo)
{
	HKEY key;
	long ret = RegOpenKeyEx(bootInfo.key, bootInfo.bootPos, 0, KEY_WRITE, &key);
	if (ret != ERROR_SUCCESS) return false;
	ret = RegDeleteValue(key, bootInfo.bootName);
	RegCloseKey(key);
	return ret == ERROR_SUCCESS;
}
