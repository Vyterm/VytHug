#ifndef VYTERM_NET_HANDLER_H_INCLUDED
#define VYTERM_NET_HANDLER_H_INCLUDED

#include "VytNetPacket.hpp"
#include "VytNetClientPeer.hpp"
#include <map>
#include <set>
#include <afxwin.h>

namespace vyt
{
	class IHandler
	{
		std::set<std::pair<vyt::command, vyt::command>> m_listeningCommands;
	protected:
		IHandler();
		virtual ~IHandler();
		template <typename TCmd1, typename TCmd2>
		bool Listen(TCmd1 cmd1, TCmd2 cmd2) { return Listen(command(cmd1), command(cmd2)); }
		bool Listen(vyt::command opCommand, vyt::command subCommand);
	public:
		virtual void HandlePacket(vyt::Packet &packet) = NULL {};
	};

	class NetHandler
	{
		inline void LogInvalidPacket(const vyt::Packet &packet);
	private:
		NetHandler() {}
		static NetHandler m_instance;
	public:
		static NetHandler& Get() { return m_instance; }
	private:
		std::map<vyt::command, std::map<vyt::command, std::set<IHandler*>>> m_handlers;
	public:
		void DispatchPacket(Packet &packet);
		void RegisterHandler(vyt::command opCommand, vyt::command subCommand, IHandler &handler);
		void UnregisterHandler(vyt::command opCommand, vyt::command subCommand, IHandler &handler);
	};
	// Call this method in any callback to dispatch packet!!!
	inline void DispatchLoop()
	{
		if (!vyt::ClientPeer::Get().IsConnected()) return;
		bool remainPacket = true;
		do
		{
			vyt::Packet packet = vyt::ClientPeer::Get().Recv();
			if (nullptr != packet)
				vyt::NetHandler::Get().DispatchPacket(packet);
			else
				remainPacket = false;
		} while (remainPacket);
	}
}

#endif