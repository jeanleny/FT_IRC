#include <GameMaster.hpp>

GameMaster::GameMaster() : Client(GMFD)
{
	setRegisterStatus(REGISTERED);
	setNickname("GameMaster");
}

GameMaster::~GameMaster()
{
}
