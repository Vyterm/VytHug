#ifndef VYTERM_SNAPSHOT_UTILS_HPP_INCLUDED
#define VYTERM_SNAPSHOT_UTILS_HPP_INCLUDED

#include <functional>
#include <TlHelp32.h>

namespace vyt
{
	class SnapshotUtils
	{
	public:
		static void EnumProcess(std::function<void(const PROCESSENTRY32&)> processAction);
		static void EnumThread(std::function<void(const THREADENTRY32&)> threadAction);
		static void EnumModule(DWORD processID, std::function<void(const MODULEENTRY32&)> moduleAction);
		static void EnumHeap(DWORD processID, std::function<void(const HEAPENTRY32&)> heapAction);
	};
}

#endif