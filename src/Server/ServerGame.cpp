#include <Server.hpp>

void	Server::startCommand(Client &client)
{
	std::string cmd;
	std::string	cor = "#CORRIDOR";
	std::string	i_list = "*INFO";
	ssize_t		chan = getChannelByName("#TAVERN");
	std::vector<Client> clients = _channels[chan].getMemberList();
	std::vector<std::string> joinArg, inviteArg, privmsgArg;

	joinArg.push_back(cor);
	inviteArg.push_back(cor);
	clients.erase(clients.begin());
	cmd = client.getCmd();
	for (size_t i = 0; i < _channels[chan].getMemberNb() - 1 ; i++)
	{
		inviteArg.insert(inviteArg.begin(), clients[i].getNickname());
		_iCommands[INVITE]->execCmd(client, inviteArg);
		usleep(100000);
		_iCommands[JOIN]->execCmd(clients[i], joinArg);
		usleep(100000);
		inviteArg.erase(inviteArg.begin());
		i_list += " ";
		i_list += clients[i].getNickname();
	}
	privmsgArg.push_back("Master");
	privmsgArg.push_back(i_list);
	// usleep(100000);
	_iCommands[PRIVMSG]->execCmd(client, privmsgArg);
}

void	Server::manageRoom1Command(Client &client)
{
	std::string	cmd = client.getCmd();

	// if (cmd == "DOOR")
	// 	_gm.doorCommand();
	// else if (cmd == "WALL")
	// 	_gm.wallCommand();
	// else if (cmd == "SKELETON")
	// 	_gm.skeletonCommand();
	// else if (cmd == "DESK")
	// 	_gm.deskCommand();
	// else if (cmd == "LEVER")
	// 	_gm.leverCommand();

}

void	Server::manageGameCommand(Client &client)
{
	std::string cmd = client.getCmd();
	std::string	nick = client.getNickname();
	if (cmd == "START" && nick == "Master")
	{
		startCommand(client);
	}

}

void	Server::ServerPlayCmd(Client &emitter, const std::vector<std::string> & arg)
{
	(void)arg;
	std::vector<std::string> lobby;

	if (!Server::getInstance().isInChannel(emitter, "#TAVERN"))
	{
		lobby.push_back("#TAVERN");
		_iCommands[JOIN]->execCmd(emitter, lobby);
	}
}

bool	Server::isRunningGameRoom(std::string chanName)
{
	std::string rooms[2] = {"#ROOM1", "#ROOM2"};

	for (size_t i = 0; i < 2; i++)
	{
		if (chanName == rooms[i])
			return true;
	}
	return false;
}

bool	Server::isGameChannel(std::string chanName)
{
	std::string rooms[3] = {"#TAVERN", "#CORRIDOR", "#ROOM"};

	for (size_t i = 0; i < 3; i++)
	{
		if (chanName == rooms[i])
			return true;
	}
	return false;
}

bool	Server::isGameCommand(Client & client)
{
	const std::string g_array[NB_GCMD]= {"START", "INFO", "CMD3", "CMD4"};

	for (size_t i = 0; i < NB_GCMD; i++)
	{
		if (client.getCmd() == g_array[i])
			return true;
	}
	return false;
}

void	Server::gMapSetup()
{
	std::vector<std::string> lobby;
	lobby.push_back("START");
	lobby.push_back("cmd2");
	std::vector<std::string> room1;
	room1.push_back("cmd1");
	room1.push_back("cmd2");
	std::vector<std::string> room2;
	room2.push_back("cmd1");
	room2.push_back("cmd2");
	_gmcmd["#LOBBY"] = lobby;
	_gmcmd["#ROOM1"] = room1;
	_gmcmd["#ROOM2"] = room2;
}



void	Server::callPartCommand(std::string chanName)
{
	std::vector<std::string>arg;
	size_t cId = getChannelByName(chanName);
	size_t memberNb = _channels[cId].getMemberNb();
	std::vector<Client> clients = _channels[cId].getMemberList();
	arg.push_back(chanName);
	for (size_t i = 0; i < memberNb; i++)
	{
		if (clients[i].getNickname() != "GameMaster" && isInChannel(clients[i], chanName))
			_iCommands[PART]->execCmd(clients[i], arg);
	}
}

void	Server::gClear()
{
	std::string				rooms[3] = {"#LOBBY", "#ROOM1", "#ROOM2"};

	for (size_t i = 0; i < 2; i++)
	{
		callPartCommand(rooms[i]);
	}
}

void	Server::gameSetup()
{
	gMapSetup();
}
