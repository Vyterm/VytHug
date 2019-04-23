#ifndef VYTERM_COMPUTER_UTILS_HPP_INCLUDED
#define VYTERM_COMPUTER_UTILS_HPP_INCLUDED

namespace vyt
{
	class ComputerUtils
	{
	public:
		using sizetype = unsigned __int64;
		static int CpuUtilization();
		static int MemoryUtilization(); 
		static sizetype Cleanmemory();
		static bool CheckAdmin();
		static bool RunasAdmin();
		static void Poweroff();
		static void Reboot();
		static void Logoff();
		static void Dormancy();
		static void Sleep();
		static void LockScreen();
	};
}

#endif