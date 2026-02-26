#include <BotGameMaster.hpp>

void    BotGameMaster::manageAntechamberCommand(t_parse parse)
{
	if (!_fight && parse.cmd == "CHEST")
	{
		if (_players[parse.player].getItemName() != "")
			sendPrivmsg(parse.player, " You already have " + _players[parse.player].getItemName());
		else
		{
			_players[parse.player].setItem(_items[_weaponCount]) ;
			sendPrivmsg("#ANTECHAMBER", parse.player + "picked up "+ _players[parse.player].getItemName());
			_weaponCount++;
		}
	}
	if (!_fight)
	{
		if (_weaponCount == _players.size())
		{
			sendPrivmsg("#ANTECHAMBER", "ENOUGH !! You find yourself clever ?");
			sendPrivmsg("#ANTECHAMBER", "Now i'll show you de quel bois je me chauffe...");
			_fight = true ;
		}
	}
	else if (_fight)
	{
		//attack oulala
	}
}
