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
    for (size_t i = 0; i < playerList.size() - 1; i++)
    {
        _players[playerList[i]] = CORRIDOR;
    }
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
    else if (isRoomCommand(parse.cmd, CORRIDOR) && isPlayerInRoom(parse.player, CORRIDOR))
    {
        //manageRoom1Command();
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
	{
        sendInvalidCommandMessage(parse.player);
	}
}

void    BotGameMaster::sendInvalidCommandMessage(std::string nickname)
{
    sendCommand("PRIVMSG " + nickname + " :Invalid Command Exception\r\n");
}
