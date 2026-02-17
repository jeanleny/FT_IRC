#include <GameMaster.hpp>

GameMaster::GameMaster() : Client(GMFD)
{
	setCommandId(IGNORED);
	setRegisterStatus(REGISTERED);
	setNickname("GameMaster");

	_msg.push_back("Texte de presentation de la premiere piece, avec 4 choix possibles");
}

GameMaster::~GameMaster()
{
}

std::string	GameMaster::getMsg(size_t i)
{
	return (_msg[i]);
}


// void	GameMaster::wallCommand(Client & client)
// {
	
// }

// void	GameMaster::skeletonCommand(Client & client)
// {
	
// }

// void	GameMaster::deskCommand(Client & client)
// {
	
// }

// void	GameMaster::leverCommand(Client & client)
// {
	
// }

// void	GameMaster::doorCommand(Client & client)
// {

// }