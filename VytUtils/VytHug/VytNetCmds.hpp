#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

enum class OpCommand
{
	Kernel = 0,
	Virus = 1,
};


enum class KernelCommand
{
	Version = 0,
};


enum class VirusCommand
{
	Check = 0,
	Over = 1,
	Submit = 2,
};

#endif