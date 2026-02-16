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
