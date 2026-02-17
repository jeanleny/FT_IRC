#include <Client.hpp>

#pragma once

#define GMFD 1023

typedef enum gameMsg
{
	ROOM1,
} e_gameMsg;

class GameMaster : public Client
{
	public :
		GameMaster();
		~GameMaster();

		std::string	getMsg(size_t);

		void	doorCommand(Client & client);
		void	wallCommand(Client & client);
		void	skeletonCommand(Client & client);
		void	deskCommand(Client & client);
		void	leverCommand(Client & client);



	private :

		std::vector<Client> 		players;
		std::vector<std::string>	_msg;

};
