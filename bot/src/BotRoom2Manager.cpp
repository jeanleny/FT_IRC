#include <BotGameMaster.hpp>

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

    if (std::rand() % 3 == 0)
    {
        _players[it->first].setAlive(false);
        sendPrivmsg("#ANTECHAMBER", "Evil Master attacked " + it->first + " who died. Aïe.\r\n");
        _players.erase(it->first);
        if (_players.size() == 0)
        {
            sendPrivmsg("#ANTECHAMBER", "Message de défaite\r\n");
            _fight.run = false;
        }
    }
    else
        sendPrivmsg("#ANTECHAMBER", "Evil Master attacked " + it->first + ", but he survives.\r\n");
}

void    BotGameMaster::manageAntechamberCommand(t_parse parse)
{
	if (!_fight.run && parse.cmd == "CHEST")
	{
		if (_players[parse.player].getItemName() != "")
			sendPrivmsg(parse.player, " You already have " + _players[parse.player].getItemName());
		else
		{
			_players[parse.player].setItem(_items[_weaponCount]) ;
			sendPrivmsg("#ANTECHAMBER", parse.player + "picked up "+ _players[parse.player].getItemName());
			_weaponCount++;
		}
		if (_weaponCount == _players.size())
		{
			sendPrivmsg("#ANTECHAMBER", "ENOUGH !! You find yourself clever ?");
			sendPrivmsg("#ANTECHAMBER", "Now i'll show you de quel bois je me chauffe...");
			sendPrivmsg("#ANTECHAMBER", "The fight is starting ! When it's your turn, use *ATTACK to hit the Evil Master");
			sendPrivmsg("#ANTECHAMBER", "It's " + _players.begin()->first + " turns\r\n");
			_fight.run = true ;
		}
	}
	else if (_fight.run && parse.cmd == "ATTACK" && _fight.playerTurn == parse.player)
	{
		sendPrivmsg("#ANTECHAMBER", parse.player + " attacked Evil Master\r\n"); // with item
        _fight.bossLife -= 1;
        if (_fight.bossLife <= 0)
        {
            sendPrivmsg("#ANTECHAMBER", "Message de victoire\r\n");
            _fight.run = false;
        }
        if (newPlayerTurn(parse) < 0)
            bossAttack();
        
	}
	//else if (parse.cmd == "REST")
}
