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
	};
}

#endif