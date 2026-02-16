#include <PlayCommand.hpp>

PlayCommand::PlayCommand()
{
	
}

PlayCommand::~PlayCommand()
{
	
}

void	PlayCommand::execCmd(Client &emitter, const std::vector<std::string> & arg)
{
	Server::getInstance().ServerPlayCmd(emitter, arg);
}
