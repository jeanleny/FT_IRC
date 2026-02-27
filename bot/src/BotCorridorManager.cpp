#include <BotGameMaster.hpp>

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
        _doors[0] = UNLOCKED;
        sendPrivmsg("#CORRIDOR", "The door is open !!! Use " + colorText("*DOOR", ORANGE, NONE) + " to enter the next room\r\n");
    }
    else
        sendPrivmsg(parse.player, _library[CORRIDOR]["LEVER"][0]);
}

void    BotGameMaster::manageCorridorCommand(t_parse parse)
{
    if (parse.cmd == "DOOR" && _doors[0] == UNLOCKED)
    {
        if (_firstPit == true)
        {
            sendCommand("START #CORRIDOR #PIT " + parse.player + "\r\n");
            _players[parse.player].setRoom(PIT);
            _firstPit = false;
        }
        else
        {
            sendCommand("START #CORRIDOR #ROOM1 " + parse.player + "\r\n");
            _players[parse.player].setRoom(ROOM1);
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
