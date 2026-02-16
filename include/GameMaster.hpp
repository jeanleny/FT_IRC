#include <Client.hpp>
#include <Server.hpp>

#pragma once

class GameMaster : public Client
{
	public :
		GameMaster();
		~GameMaster();
	private :
		std::vector<Client> players;
};
