#include <BotGameMaster.hpp>

std::string Item::randomDmg()
{
    if (std::rand() % 4 == 0)
    {
        return ("X");
    }
    int random = std::rand() % (_range + 1);
    if (std::rand() % 2 == 0)
    {
        return (toString(_damage + random));
    }
    return (toString(_damage - random));
}

int   BotGameMaster::newPlayerTurn(t_parse parse)
{   
    playersIt   it = _players.find(parse.player);
    if (it != _players.end())
    {
        it++;
        if (it != _players.end())
        {
            _fight.playerTurn = it->first;
            sendPrivmsg("#ANTECHAMBER", "It's " + it->first + " turns to attack\r\n");
            return (0);
        }
        else
        {
            _fight.playerTurn = _players.begin()->first;
            return (-1);
        }
    }
    return (0);
}

void    BotGameMaster::bossAttack()
{
    int index = std::rand() % _players.size();
    playersIt   it = _players.begin();
    std::advance(it, index);

    sendPrivmsg("#ANTECHAMBER", "Evil Master attacked " + it->first + " ...\r\n");
    usleep(500000);
    sendPrivmsg("#ANTECHAMBER", "...\r\n");
    usleep(500000);
    if (std::rand() % 3 == 0)
    {
        _players[it->first].setAlive(false);
        sendPrivmsg("#ANTECHAMBER", it->first + " is DEAD :(\r\n");
        _players.erase(it);
        if (_players.size() == 0)
        {
            sendPrivmsg("#ANTECHAMBER", "\r\n");
            _fight.run = false;
        }
    }
    else
        sendPrivmsg("#ANTECHAMBER", it->first + " survives !\r\n");
    _fight.playerTurn = _players.begin()->first;
    sendPrivmsg("#ANTECHAMBER", "It's " + _players.begin()->first + " turns to attack\r\n");
}

void    BotGameMaster::manageAntechamberCommand(t_parse parse)
{
	if (!_fight.run && parse.cmd == "CHEST")
	{
		if (_players[parse.player].getItemName() != "")
			sendPrivmsg(parse.player, " You already have " + _players[parse.player].getItemName());
		else
		{
            Item        item = _items[_weaponCount];
            std::string min = toString(item.getMinDmg());
            std::string max = toString(item.getMaxDmg());
			_players[parse.player].setItem(item) ;
			sendPrivmsg("#ANTECHAMBER", parse.player + " picked up "+ item.getName() + " (" + min + " - " + max + " damage)");
			_weaponCount++;
		}
		if (_weaponCount == _players.size())
		{
            sendCommand("TOPIC " + _rooms[4] + " :A door open and the Master arrives in the room. He seems to be very upset\r\n");
            usleep(500000);
			sendPrivmsg("#ANTECHAMBER", "ENOUGH !! You find yourself clever ?");
            usleep(500000);
			sendPrivmsg("#ANTECHAMBER", "Now i'll show you de quel bois je me chauffe...");
            usleep(500000);
            sendCommand("TOPIC " + _rooms[4] + " :The fight is starting ! When it's your turn, use *ATTACK to hit the Evil Master\r\n");
			sendPrivmsg("#ANTECHAMBER", "It's " + _players.begin()->first + " turns");
			_fight.run = true ;
		}
	}
	else if (_fight.run && parse.cmd == "ATTACK" && _fight.playerTurn == parse.player)
	{
        std::string dmg = _players[parse.player].getItem().randomDmg();
		sendPrivmsg("#ANTECHAMBER", parse.player + " attacked Evil Master with his " + _players[parse.player].getItemName());
        usleep(500000);
        if (dmg == "X")
		    sendPrivmsg("#ANTECHAMBER", parse.player + " completely misses like a bolosse");
        else
        {
		    sendPrivmsg("#ANTECHAMBER", parse.player + " inflicts " + dmg + " damage");
            _fight.bossLife -= _players[parse.player].getItemDmg();
        }
        if (_fight.bossLife <= 0)
        {
            sendPrivmsg("#ANTECHAMBER", "Well done!! You have defeated me. I will now guide you to the Tavern to regain your strength.");
            sleep(2);
            sendCommand("START #ANTECHAMBER #TAVERN all\r\n");
            _fight.run = false;
            return ;
        }
        usleep(500000);
		sendPrivmsg("#ANTECHAMBER", "Evil Master's life is now " + toString(_fight.bossLife));
        if (newPlayerTurn(parse) < 0)
            bossAttack();
	}
}
