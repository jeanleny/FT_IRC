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
    return (_players[nickname] == room);
}

void    BotGameMaster::setupPlayers(std::string command)
{
    std::vector<std::string> playerList = split(command);
    playerList.erase(playerList.begin());
    for (size_t i = 0; i < playerList.size(); i++)
    {
        _players[playerList[i]] = CORRIDOR;
    }
    sendLibraryContent("#CORRIDOR", _library[TAVERN]["START"]);
}

void	BotGameMaster::shutDownGame()
{
	_gameRunning = 0;
	_players.clear();
}

void BotGameMaster::switchLever(int pos)
{
    if (_levers[pos] == "[-]")
        _levers[pos] = "[o]";
    else
        _levers[pos] = "[-]";
}

void BotGameMaster::resetLevers()
{
    for (size_t i = 0; i < _levers.size(); i++)
    {
        _levers[i] = "[-]";
    }
}

bool    BotGameMaster::isGoodLevers()
{
    return (_levers[0] == "[o]" && _levers[1] == "[-]" && _levers[2] == "[-]" && _levers[3] == "[o]" && _levers[4] == "[o]");
}

void    BotGameMaster::manageLeverCommand(t_parse parse)
{
    std::string leverCmd = parse.args[3];
    for(size_t i = 0; i < leverCmd.size(); i++)
    {
        if (leverCmd == "*lever")
        {
            resetLevers();
            break ;
        }
        if (leverCmd[i] >= '1' && leverCmd[i] <= '5')
        {
            int pos = leverCmd[i] - 48;
            switchLever(pos - 1);
        }
    }
    std::string levers = _levers[0] + _levers[1] + _levers[2] + _levers[3] + _levers[4];
    sendPrivmsg(parse.player, levers);
    if (isGoodLevers())
    {
        sendPrivmsg(parse.player, _library[CORRIDOR]["LEVER"][1]);
        _doors[0] = 1;
        sendPrivmsg("#CORRIDOR", "The door is open !!! Use *DOOR to enter the next room\r\n");
    }
    else
        sendPrivmsg(parse.player, _library[CORRIDOR]["LEVER"][0]);
}

void	BotGameMaster::sendLibraryContent(std::string player, std::vector<std::string> content)
{
	size_t c_size = content.size();
	for (size_t i = 0; i < c_size ; i++)
	{
       	sendPrivmsg(player, content[i]);
	}
}

void    BotGameMaster::manageRoom1Command(t_parse parse)
{
    static bool first = true;
    if (parse.cmd == "DOOR" && _doors[0] == 1)
    {
        if (first == true)
        {
            sendCommand("START #CORRIDOR #PIT " + parse.player + "\r\n");
            _players[parse.player] = PIT;
			sendLibraryContent("#PIT", _library[PIT]["ENTRY"]);
            first = false;
        }
        else
        {
            sendCommand("START #CORRIDOR #ROOM1 " + parse.player + "\r\n");
            _players[parse.player] = ROOM1;
        }
    }
    else if (parse.cmd == "WALL")
    {
		sendLibraryContent(parse.player, _library[CORRIDOR]["WALL"]);
        sendPrivmsg("#CORRIDOR", parse.player + " is examining the wall");
    }
    else if (parse.cmd == "DOOR")
    {
		sendLibraryContent(parse.player, _library[CORRIDOR]["DOOR"]);
        sendPrivmsg("#CORRIDOR", parse.player + " is reading inscriptions on the door");
    }
    else if (parse.cmd == "CORPSE")
    {
		sendLibraryContent(parse.player, _library[CORRIDOR]["CORPSE"]);
        sendPrivmsg("#CORRIDOR", parse.player + " is searching the dead adventurer");
    }
    else if (parse.cmd == "LEVER")
        manageLeverCommand(parse);
}

void    BotGameMaster::manageTavernCommand(t_parse parse)
{
    std::vector<std::string>    tab = _library[TAVERN][parse.cmd];
    std::string msg = parse.player + tab[std::rand() % tab.size()];
    sendPrivmsg("#TAVERN", msg);
}

void	BotGameMaster::managePitCommand(t_parse parse)
{
	if (parse.cmd == "1")
	{
		sendLibraryContent("#PIT", _library[PIT]["1"]);
	}
	else if (parse.cmd == "2")
	{
		sendLibraryContent("#PIT", _library[PIT]["2"]);
	}
	else if (parse.cmd == "3")
	{
		sendLibraryContent("#PIT", _library[PIT]["3"]);
	}
	else if (parse.cmd == "4")
	{
		sendLibraryContent("#PIT", _library[PIT]["4"]);
	}
	else if (parse.cmd == "SHOUT")
	{
		std::string msg = "You hear " + parse.player + " yelling : " + parse.content.erase(0, 7);
		sendPrivmsg("#ROOM1", msg);
	}
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
    else if (isRoomCommand(parse.cmd, TAVERN) && isPlayerInRoom(parse.player, TAVERN))
    {
        manageTavernCommand(parse);
    }
    else if (isRoomCommand(parse.cmd, CORRIDOR) && isPlayerInRoom(parse.player, CORRIDOR))
    {
        manageRoom1Command(parse);
    }
    else if (isRoomCommand(parse.cmd, ROOM1) && isPlayerInRoom(parse.player, ROOM1))
    {
        //manageRoom2Command();
    }
    else if (isRoomCommand(parse.cmd, PIT) && isPlayerInRoom(parse.player, PIT))
    {
        managePitCommand(parse);
    }
    else
        sendPrivmsg(parse.player, _messages[INVALID]);
}

void    BotGameMaster::sendPrivmsg(std::string target, std::string message)
{
    sendCommand("PRIVMSG " + target + " :" + message + "\r\n");
}
