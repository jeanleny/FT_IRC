#include <Server.hpp>

void	Server::ServerPlayCmd(Client &emitter, const std::vector<std::string> & arg)
{
	(void)arg;
	std::vector<std::string> lobby;

	
	lobby.push_back("#LOBBY");
	_iCommands[JOIN]->execCmd(emitter, lobby);
}
