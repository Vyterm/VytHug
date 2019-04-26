#include "stdafx.h"
#include "VytNetHandler.hpp"

vyt::IHandler::IHandler()
{
}

vyt::IHandler::~IHandler()
{
	for (auto &cmd : m_listeningCommands)
		vyt::NetHandler::Get().UnregisterHandler(cmd.first, cmd.second, *this);
}

bool vyt::IHandler::Listen(vyt::command opCommand, vyt::command subCommand)
{
	for (auto &cmd : m_listeningCommands)
		if (cmd.first == opCommand && cmd.second == subCommand)
			return false;
	m_listeningCommands.emplace(std::pair<vyt::command, vyt::command>(opCommand, subCommand));
	vyt::NetHandler::Get().RegisterHandler(opCommand, subCommand, *this);
	return true;
}

vyt::NetHandler vyt::NetHandler::m_instance;

inline void vyt::NetHandler::LogInvalidPacket(const vyt::Packet & packet)
{
	CString error;
	error.Format(_T("未定义的操作码，主操作码为 %d ，副操作码为 %d ，本消息包的内容将被抛弃\n"), packet->getOpCommand(), packet->getSubCommand());
	OutputDebugString(error);
}

void vyt::NetHandler::DispatchPacket(Packet & packet)
{
	if (m_handlers.end() != m_handlers.find(packet->getOpCommand()))
	{
		auto &subHandlers = m_handlers[packet->getOpCommand()];
		if (subHandlers.end() != subHandlers.find(packet->getSubCommand()))
		{
			for (auto &pHandler : subHandlers[packet->getSubCommand()])
				pHandler->HandlePacket(packet);
		}
		else
			LogInvalidPacket(packet);
	}
	else
		LogInvalidPacket(packet);
}

void vyt::NetHandler::RegisterHandler(vyt::command opCommand, vyt::command subCommand, IHandler & handler)
{
	m_handlers[opCommand][subCommand].emplace(&handler);
}

void vyt::NetHandler::UnregisterHandler(vyt::command opCommand, vyt::command subCommand, IHandler & handler)
{
	auto &handlers = m_handlers[opCommand][subCommand];
	auto pHandler = handlers.find(&handler);
	if (handlers.end() != pHandler)
		handlers.erase(pHandler);
}
