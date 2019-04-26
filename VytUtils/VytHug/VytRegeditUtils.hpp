#ifndef VYTERM_REGEDIT_HPP_INCLUDED
#define VYTERM_REGEDIT_HPP_INCLUDED

#include <winsvc.h>
#include <functional>

namespace vyt
{
	class RegeditUtils
	{
	public:
		static void EnumServices(std::function<void(const ENUM_SERVICE_STATUS_PROCESS&, const QUERY_SERVICE_CONFIG&)> serviceAction);
		static void ServiceStart(CString serviceName);
		static void ServicePause(CString serviceName);
		static void EnumWindows(std::function<void(HWND)> windowAction);
		static bool Is64BitOS();
		struct SoftwareInfo
		{
			TCHAR szSoftName[50];
			TCHAR szSoftVersion[50];
			TCHAR szSoftDate[20];
			TCHAR szSoftSize[MAX_PATH];
			TCHAR szSoftInsPath[MAX_PATH];
			TCHAR szSoftUniPath[MAX_PATH];
			TCHAR szSoftVenRel[50];
			TCHAR szSoftIcon[MAX_PATH];
		};
		static void EnumSoftwares(std::function<void(SoftwareInfo&)> softwareAction);
	};
}

#endif