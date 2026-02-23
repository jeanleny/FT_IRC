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
    sendPrivmsg("#CORRIDOR", _library[TAVERN]["START"][0]);
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
    }
    else
        sendPrivmsg(parse.player, _library[CORRIDOR]["LEVER"][0]);
}

void    BotGameMaster::manageRoom1Command(t_parse parse)
{
    // if (parse.cmd == "DOOR" && isDoorOpen())
    //     enter in room;
    if (parse.cmd == "WALL")
    {
        sendPrivmsg(parse.player, _library[CORRIDOR]["WALL"][0]);
        sendPrivmsg("#CORRIDOR", parse.player + " is examining the wall");
    }
    else if (parse.cmd == "DOOR")
    {
        sendPrivmsg(parse.player, _library[CORRIDOR]["DOOR"][0]);
        sendPrivmsg("#CORRIDOR", parse.player + " is reading inscriptions on the door");
    }
    else if (parse.cmd == "CORPSE")
    {
        sendPrivmsg(parse.player, _library[CORRIDOR]["CORPSE"][0]);
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

void    BotGameMaster::manageGameCommand(t_parse parse)
{
    if (parse.cmd == "START" && !_gameRunning)
    {
        sendCommand("START\r\n");
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
    else if (isRoomCommand(parse.cmd, ROOM) && isPlayerInRoom(parse.player, ROOM))
    {
        //manageRoom2Command();
    }
    else if (isRoomCommand(parse.cmd, HOLE) && isPlayerInRoom(parse.player, HOLE))
    {
        //manageRoom3Command();
    }
    else
        sendPrivmsg(parse.player, _messages[INVALID]);
}

void    BotGameMaster::sendPrivmsg(std::string target, std::string message)
{
    sendCommand("PRIVMSG " + target + " :" + message + "\r\n");
}
