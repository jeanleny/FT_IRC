#include <ModeCommand.hpp>

ModeCommand::ModeCommand()
{

}

ModeCommand::~ModeCommand()
{

}

bool	validModeFlag(char a)
{
	if (a == 't' || a == 'i' || a == 'k' || a == 'o' || a == 'l')
		return (true);
	return (false);
}

bool	isAddSub(char a, bool & disable)
{
	if (a == '-' || a == '+')
	{
		if (a == '-')
			disable = true;
		return (true);
	}
	return (false);
}

void	sendModeError(Client client, char arg)
{
	std::string msg = ":" + Server::getInstance().getHostname() + " 472 " + client.getNickname() + arg + ":is not a recognised channel mode.\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	ModeCommand::modeCommand(Client &emitter, std::string chanName, std::string arg)
{
	bool disable = false;
	std::string flags;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (isAddSub(arg[i], disable))
			i++;
		if (!validModeFlag(arg[i]))
		{
			sendModeError(emitter, arg[i]);
			continue ;
		}
		else
			flags += arg[i];
	}
	if (flags.size() > 0)
		Server::getInstance().changeChannelMode(emitter, chanName, flags, disable);
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
		modeCommand(emitter, arg[0], arg[1]);
}
