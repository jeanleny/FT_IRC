#include <BotGameMaster.hpp>

void	BotGameMaster::manageRoom1Command(t_parse parse)
{
    if (parse.cmd == "DOOR" && _doors[1] == UNLOCKED)
    {
        sendCommand("START #ROOM1 #ANTECHAMBER " + parse.player + "\r\n");
        _players[parse.player].setRoom(ANTECHAMBER);
    }
	if (parse.cmd == "1")
		sendLibraryContent(parse.player, _library[ROOM1]["1"]);
	else if (parse.cmd == "2")
		sendLibraryContent(parse.player, _library[ROOM1]["2"]);
	else if (parse.cmd == "3")
		sendLibraryContent(parse.player, _library[ROOM1]["3"]);
	else if (parse.cmd == "4")
		sendLibraryContent(parse.player, _library[ROOM1]["4"]);
}

void	BotGameMaster::managePitCommand(t_parse parse)
{
    if (parse.cmd == "CRANK")
    {
        if (_doors[1] == UNLOCKED)
        {
            sendCommand("TOPIC #ROOM1 :Well done ! You are now together again. You can use" + colorText("*DOOR", ORANGE, NONE) + " to enter the next room.\r\n");
            sendCommand("START #PIT #ROOM1 " + parse.player + "\r\n");
            _players[parse.player].setRoom(ROOM1);
        }
        else
		{
            sendLibraryContent("#PIT", _library[PIT]["CRANK"]);
            sendLibraryContent("#PIT", initClueAscii());
		}
    }
    else if (parse.cmd == "CODE")
    {
        std::string    code = "";
		if (parse.content.length() > 6)
			code = parse.content.substr(6);
        if (code == CODE)
        {
            sendPrivmsg("#PIT", _library[PIT]["CODE"][1]);
            _doors[1] = 1;
        }
        else
            sendPrivmsg("#PIT", _library[PIT]["CODE"][0]);
    }
    else if (parse.cmd == "SHOUT")
    { 
	  std::string msg = "";
      parse.content = strToUpper(parse.content);
	  if (parse.content.length() > 8)
	  {
    	msg = "You hear " + parse.player + " yelling : " + parse.content.erase(0, 7) + "!!";
      	sendPrivmsg("#ROOM1", msg);
	  }
    }
}
