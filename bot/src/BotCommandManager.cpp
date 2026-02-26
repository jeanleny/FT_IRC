#include <BotGameMaster.hpp>


bool    BotGameMaster::isRoomCommand(std::string command, e_roomId room)
{
    std::map<std::string, std::vector<std::string> >::iterator it = _library[room].find(command);

    if (it == _library[room].end())
        return false;
    return true;
}

bool    BotGameMaster::isPlayerInRoom(std::string nickname, e_roomId room)
{
    if (_players.find(nickname) == _players.end())
        return false;
    else
        return (_players[nickname].getRoom() == room);
}

void    BotGameMaster::setupPlayers(std::string command)
{
    std::vector<std::string> playerList = split(command);
    playerList.erase(playerList.begin());
    for (size_t i = 0; i < playerList.size(); i++)
    {
        _players[playerList[i]] = Player();
    }
    sendLibraryContent("#CORRIDOR", _library[TAVERN]["START"]);
}

void	BotGameMaster::lockDoors()
{
	for (size_t i = 0; i < _doors.size() ; i++)
	{
		_doors[i] = LOCKED;
	}
}

void	BotGameMaster::shutDownGame()
{
	_gameRunning = 0;
	_players.clear();
	lockDoors();
	resetLevers();
	_firstPit = true;
	_weaponCount = 0;
	_fight = false;
	_players.clear();
	sendCommand("TOPIC " + _rooms[2] + " :" + _topics[2] + "\r\n");
}

void	BotGameMaster::sendLibraryContent(std::string target, std::vector<std::string> content)
{
	size_t c_size = content.size();
	for (size_t i = 0; i < c_size ; i++)
	{
       	sendPrivmsg(target, content[i]);
	}
}

void    BotGameMaster::manageTavernCommand(t_parse parse)
{
    std::vector<std::string>    tab = _library[TAVERN][parse.cmd];
    std::string msg = parse.player + tab[std::rand() % tab.size()];
    sendPrivmsg("#TAVERN", msg);
}

void    BotGameMaster::manageGameCommand(t_parse parse)
{
    if (parse.cmd == "START" && !_gameRunning)
    {
        sendCommand("START #TAVERN #CORRIDOR all\r\n");
        _gameRunning = true;
    }
    else if (parse.cmd == "INFO" && parse.player == "Master")
        setupPlayers(parse.content);
    else if (parse.cmd == "SHUTDOWN" && parse.player == "Master")
		    shutDownGame();
    else if (isRoomCommand(parse.cmd, TAVERN))
    {
        manageTavernCommand(parse);
    }
    else if (isRoomCommand(parse.cmd, CORRIDOR) && isPlayerInRoom(parse.player, CORRIDOR))
    {
        manageCorridorCommand(parse);
    }
    else if (isRoomCommand(parse.cmd, ROOM1) && isPlayerInRoom(parse.player, ROOM1))
    {
        manageRoom1Command(parse);
    }
    else if (isRoomCommand(parse.cmd, PIT) && isPlayerInRoom(parse.player, PIT))
    {
        managePitCommand(parse);
    }
    else if (isRoomCommand(parse.cmd, ANTECHAMBER) && isPlayerInRoom(parse.player, ANTECHAMBER))
    {
        manageAntechamberCommand(parse);
    }
    else
        sendPrivmsg(parse.player, _messages[INVALID]);
}

void    BotGameMaster::sendPrivmsg(std::string target, std::string message)
{
    sendCommand("PRIVMSG " + target + " :" + message + "\r\n");
}
