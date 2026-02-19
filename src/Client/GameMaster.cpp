#include <GameMaster.hpp>

GameMaster::GameMaster() : Client(GMFD)
{
	setCommandId(IGNORED);
	setRegisterStatus(REGISTERED);
	setNickname("GameMaster");
}

GameMaster::~GameMaster()
{
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