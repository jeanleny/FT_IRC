#include <Server.hpp>

std::vector<Client>	Server::startPlayersList(std::string oldRoom, std::vector<std::string> args)
{
	std::vector<Client>	players;
	ssize_t        chan = getChannelByName(oldRoom);
    std::vector<Client>	memberList = _channels[chan].getMemberList();
	if (args[0] == "all")
	{
		players = memberList;
		players.erase(players.begin());
	}
	else
	{
		for(size_t i = 0; i < args.size(); i++)
		{
			for(size_t j = 0; j < memberList.size(); j++)
			{
				if (memberList[j].getNickname() == args[i])
					players.push_back(memberList[j]);
			}
		}
	}
	return (players);
}

void	Server::sendInfoMessage(Client & client, std::vector<Client> players)
{
	std::vector<std::string> privmsgArg;
	privmsgArg.push_back("Master");
	std::string	i_list = "*INFO";
	for (size_t i = 0; i < players.size(); i++)
	{
		i_list += " ";
		i_list += players[i].getNickname();
		_playerFd.push_back(players[i].getClientFd());
	}
	privmsgArg.push_back(i_list);
	_iCommands[PRIVMSG]->execCmd(client, privmsgArg);
}


// cmd = "START #oldRoom #newRoom" nick1 nick2 nick3 etc;
// cmd = "START #oldRoom #newRoom" all;
void	Server::startCommand(Client &client, std::vector<std::string> args)
{
	std::string	oldRoom = args[0];
	std::string	newRoom = args[1];
	args.erase(args.begin());
	args.erase(args.begin());
	
	std::vector<Client> players = startPlayersList(oldRoom, args);
	std::vector<std::string> joinArg, inviteArg, partArg, limitArg;
	if (oldRoom == "#TAVERN" && (players.size() < 2 || players.size() > 4))
	{
		limitArg.push_back("#TAVERN");
		limitArg.push_back("The game needs at least 2 players and can be played up to 4 players");
		_iCommands[PRIVMSG]->execCmd(players[i], limitArg);
		return ;
	}
	partArg.push_back(oldRoom);
	joinArg.push_back(newRoom);
	inviteArg.push_back(newRoom);
	for (size_t i = 0; i < players.size(); i++)
	{
		inviteArg.insert(inviteArg.begin(), players[i].getNickname());
		_iCommands[INVITE]->execCmd(client, inviteArg);
		_iCommands[JOIN]->execCmd(players[i], joinArg);
		_iCommands[PART]->execCmd(players[i], partArg);
		inviteArg.erase(inviteArg.begin());
	}
	if (oldRoom == "#TAVERN")
		sendInfoMessage(client, players);
}

void	Server::manageGameCommand(Client &client)
{
	std::string cmd = client.getCmd();
	std::string	nick = client.getNickname();
	if (cmd == "START" && nick == "Master")
	{
		std::vector<std::string>	args = client.getCommandArgs();
		startCommand(client, args);
	}
}

void	Server::ServerPlayCmd(Client &emitter, const std::vector<std::string> & arg)
{
	(void)arg;
	std::vector<std::string> lobby;

	if (!isInChannel(emitter, "#TAVERN"))
	{
		lobby.push_back("#TAVERN");
		_iCommands[JOIN]->execCmd(emitter, lobby);
	}
}

bool	Server::isRunningGameRoom(std::string chanName)
{
	std::string rooms[NB_RUNGROOM] = {"#CORRIDOR", "#ROOM1", "#PIT", "#ANTECHAMBER"};

	for (size_t i = 0; i < NB_RUNGROOM; i++)
	{
		if (chanName == rooms[i])
			return true;
	}
	return false;
}

bool	Server::leavingGameSession(Client & client)
{
	std::vector<std::string>	cmdArgs = client.getCommandArgs();
	if (client.getCommandId() == PART && cmdArgs.size() > 0)
	{
		if (client.getNickname() == "Master")
		{
			if (isGameChannel(cmdArgs[0]))
				return (true);
		}
		else if (isRunningGameRoom(cmdArgs[0]))
			return (true);
	}
	return (false);
}

bool	Server::isGameChannel(std::string chanName)
{
	std::string rooms[NB_GROOM] = {"#TAVERN", "#CORRIDOR", "#ROOM1", "#PIT", "#ANTECHAMBER"};

	for (size_t i = 0; i < NB_GROOM; i++)
	{
		if (chanName == rooms[i])
			return true;
	}
	return false;
}

bool	Server::isGameCommand(Client & client)
{
	const std::string g_array[NB_GCMD]= {"START", "INFO", "SHUTDOWN"};

	for (size_t i = 0; i < NB_GCMD; i++)
	{
		if (client.getCmd() == g_array[i])
			return true;
	}
	return false;
}



void	Server::callPartCommand(std::string chanName)
{
	std::vector<std::string>arg;
	ssize_t cId = getChannelByName(chanName);
	if (cId < 0)
		return ;
	size_t memberNb = _channels[cId].getMemberNb();
	std::vector<Client> clients = _channels[cId].getMemberList();
	arg.push_back(chanName);
	for (size_t i = 0; i < memberNb; i++)
	{
		if (clients[i].getNickname() != "Master" && isInChannel(clients[i], chanName))
			_iCommands[PART]->execCmd(clients[i], arg);
	}
}

void	Server::gClear()
{
	Client					gm = getClientByNickname("Master");
	std::vector<std::string>arg;
	std::string				rooms[NB_GROOM] = {"#TAVERN","#CORRIDOR", "#ROOM1", "#PIT", "#ANTECHAMBER"};
	std::string				msg = "*SHUTDOWN";

	arg.push_back("Master");
	arg.push_back(msg);
	for (size_t i = 0; i < NB_GROOM; i++)
	{
		callPartCommand(rooms[i]);
	}
	_playerFd.clear();
	_iCommands[PRIVMSG]->execCmd(gm, arg);
}

bool	Server::isPlayerFd(int fd)
{
	std::vector<int>::iterator it = find(_playerFd.begin(), _playerFd.end(), fd);
	return (it != _playerFd.end());
}
