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

void    BotGameMaster::manageRoom1Command(t_parse parse)
{
    if (parse.cmd == "WALL")
        sendPrivmsg("#CORRIDOR", _library[CORRIDOR]["WALL"][0]);
    else if (parse.cmd == "SKELETON")
        sendPrivmsg("#CORRIDOR", _library[CORRIDOR]["SKELETON"][0]);
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
