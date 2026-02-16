#include <Client.hpp>

#pragma once

#define GMFD 1023


class GameMaster : public Client
{
	public :
		GameMaster();
		~GameMaster();
	private :
		std::vector<Client> players;
};
