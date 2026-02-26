#include <BotGameMaster.hpp>

void    BotGameMaster::bossAttack()
{
    int index = std::rand() % _players.size();
    playersIt   it = _players.begin();
    std::advance(it, index);

    if (std::rand() % 3 == 0)
    {
        _players[it->first].setAlive(false);
        sendPrivmsg("#ANTICHAMBER", "Evil Master attacked " + it->first + " who died. Aïe.\r\n");
        _players.erase(it->first);
        if (_players.size() == 0)
        {
            sendPrivmsg("#ANTICHAMBER", "Message de défaite\r\n");
            _fight.run = false;
        }
    }
    else
        sendPrivmsg("#ANTICHAMBER", "Evil Master attacked " + it->first + ", but he survives.\r\n");
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
			_fight.run = true ;
		}
	}
	else if (_fight.run && parse.cmd == "ATTACK" && _fight.playerTurn == parse.player)
	{
		sendPrivmsg("#ANTICHAMBER", parse.player + " attacked Evil Master\r\n"); // with item
        _fight.bossLife -= 1;
        if (_fight.bossLife <= 0)
        {
            sendPrivmsg("#ANTICHAMBER", "Message de victoire\r\n");
            _fight.run = false;
        }

        playersIt   it = _players.find(parse.player);
        if (it != _players.end())
        {
            it++;
            if (it != _players.end())
                sendPrivmsg("#ANTICHAMBER", "It's " + it->first + " turns to attack\r\n");
            else
                bossAttack();
        }
	}
	//else if (parse.cmd == "REST")
}
