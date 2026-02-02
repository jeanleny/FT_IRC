#include <ModeCommand.hpp>

ModeCommand::ModeCommand()
{

}

ModeCommand::~ModeCommand()
{

}

void	ModeCommand::execCmd(Client &emitter, const std::vector<std::string>& arg)
{
	if (arg.size() < 1)
		throw NotEnoughParametersException(emitter);
	if (!checkPrefix(arg[0]))
		throw InvalidChannelException(emitter);
	if (!Server::getInstance().existChannel(arg[0]))
		throw NoSuchChannelException(emitter);
	if (arg.size() == 1)
	  Server::getInstance().displayChannelMode(emitter, arg[0]);
	else
		Server::getInstance().changeChannelMode(emitter, arg);
}
