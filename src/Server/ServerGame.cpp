#include <Server.hpp>

void	Server::manageLobbyCommand(Client &client)
{
	std::string cmd;
	ssize_t		chan = getChannelByName("#LOBBY");
	std::vector<Client> clients = _channels[chan].getMemberList();
	std::vector<std::string> joinArg;
	std::vector<std::string> inviteArg;
	joinArg.push_back("#ROOM1");
	inviteArg.push_back("#ROOM1");
	clients.erase(clients.begin());

	cmd = client.getCmd();
	if (cmd == "START")
	{
		for (size_t i = 0; i < _channels[chan].getMemberNb() -1 ; i++)
		{
			inviteArg.insert(inviteArg.begin(), clients[i].getNickname());
			_iCommands[INVITE]->execCmd(_gm, inviteArg);
			_iCommands[JOIN]->execCmd(clients[i], joinArg);
			inviteArg.erase(inviteArg.begin());
		}
	}
	
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
			//lestgo
			//manageRoom1Command(client);
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

	
	lobby.push_back("#LOBBY");
	_iCommands[JOIN]->execCmd(emitter, lobby);
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

void	Server::gameSetup()
{
	std::string rooms[3] = {"#LOBBY", "#ROOM1", "#ROOM2"};
	
	for(size_t i = 0; i < 3; i++)
	{
		std::vector<std::string> arg;
		arg.push_back(rooms[i]);
		_iCommands[JOIN]->execCmd(_gm, arg);
		if (i != 0)
		{
			arg.push_back("+i");
			_iCommands[MODE]->execCmd(_gm, arg);
			arg.pop_back();
		}
		arg.pop_back();
	}
	gMapSetup();
}
