#include <Server.hpp>

void	Server::manageLobbyCommand(Client &client)
{
	std::string cmd;
	ssize_t		chan = getChannelByName("#TAVERN");
	std::vector<Client> clients = _channels[chan].getMemberList();
	std::vector<std::string> joinArg;
	std::vector<std::string> inviteArg;
	std::vector<std::string> privmsgArg;
	joinArg.push_back("#CORRIDOR");
	inviteArg.push_back("#CORRIDOR");
	privmsgArg.push_back("#CORRIDOR");
	clients.erase(clients.begin());

	cmd = client.getCmd();
	if (cmd == "START")
	{
		for (size_t i = 0; i < _channels[chan].getMemberNb() - 1 ; i++)
		{
			inviteArg.insert(inviteArg.begin(), clients[i].getNickname());
			_iCommands[INVITE]->execCmd(_gm, inviteArg);
			_iCommands[JOIN]->execCmd(clients[i], joinArg);
			inviteArg.erase(inviteArg.begin());
			// ajouter clients[i].getNickname() au message pour GM
		}
		//envoyer un privmsg "*INFO" au GM
		// _iCommands[PRIVMSG]->execCmd(_gm, privmsgArg);
	}
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
	std::string rooms[3] = {"#LOBBY", "#ROOM1", "#ROOM2"};
	std::string	channel = client.getIncomingChannel();
	size_t i = 0;

	for (;i < 3; i++)
	{
		if (channel == rooms[i])
			break ;
	}
	switch (i)
	{
		case 0 :
		{
			manageLobbyCommand(client);
			break ;
		}
		case 1 :
		{
			manageRoom1Command(client);
			break ;
		}
		case 2 :
			//manageRoom2Command(client);
			break ;
	}
	/*for (size_t i = 0; i < _gmcmd[client.getIncomingChannel].size(); i++)
	{
	
	}*/
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

bool	Server::isCommandFromGame(std::string chanName)
{
	std::string rooms[3] = {"#LOBBY", "#ROOM1", "#ROOM2"};

	for (size_t i = 0; i < 3; i++)
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
	const std::string g_array[NB_GCMD]= {"START", "CMD2", "CMD3", "CMD4"};

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

void	Server::displayMap()
{
	for(std::map<std::string, std::vector<std::string> >::iterator it = _gmcmd.begin(); it != _gmcmd.end(); it++)
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			std::cout << it->first << " : " << it->second[i] << std::endl;
		}
	}
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
