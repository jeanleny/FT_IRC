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

void    BotGameMaster::manageGameCommand(std::string nickname, std::string command)
{
    if (command == "START")
    {
        if (_gameRunning)
            //throw InvalidCommand
        _gameRunning = true;
            //startGame(); + s'envoyer un PRIVMSG avec les nickname des joueurs
    }
    // else if (command == "INFO")
    // {

    // }
    else
    {
        if (isRoomCommand(command, CORRIDOR) && isPlayerInRoom(nickname, CORRIDOR))
        {
            //manageRoom1Command();
        }
        if (isRoomCommand(command, ROOM) && isPlayerInRoom(nickname, ROOM))
        {
            //manageRoom2Command();
        }
        if (isRoomCommand(command, HOLE) && isPlayerInRoom(nickname, HOLE))
        {
            //manageRoom3Command();
        }
    }
}