#include <BotGameMaster.hpp>


bool    BotGameMaster::isRoomCommand(std::string command, e_roomId room)
{
    for(size_t i = 0; i < _gameCmd[room].size(); i++)
    {
        if (command == _gameCmd[room][i])
            return true;
    }
    return false;
}

bool    BotGameMaster::isPlayerInRoom(std::string nickname, e_roomId room)
{
    return (_players[nickname] == room);
}

void	displayMap(std::map<std::string, e_roomId> map)
{
	for(std::map<std::string, e_roomId >::iterator it = map.begin(); it != map.end(); it++)
	{
			std::cout << it->first << " : " << it->second << std::endl;
	}
}

void    BotGameMaster::setupPlayers(std::string command)
{
    std::cout << "INFO : " << command << std::endl;
    std::vector<std::string> playerList = split(command);
    playerList.erase(playerList.begin());
    for (size_t i = 0; i < playerList.size() - 1; i++)
    {
        _players[playerList[i]] = CORRIDOR;
    }
	displayMap(_players);

}

void    BotGameMaster::manageGameCommand(t_parse parse)
{
	std::cout << "manage cmd : " << parse.cmd << std::endl;
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
}

void    BotGameMaster::sendInvalidCommandException(std::string nickname)
{
    sendCommand("PRIVMSG " + nickname + " :Invalid Command Exception\r\n");
}
