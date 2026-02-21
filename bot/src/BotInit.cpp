#include <BotGameMaster.hpp>

/*
To access a paragraph in the library, syntax is : _library[ROOM]["COMMAND"][index]
Example : 	_library[CORRIDOR]["DOOR"][1]
			_library[TAVERN]["START"][0]

*/

void	BotGameMaster::createLibrary()
{
	std::vector<std::string>	startTxts;
	startTxts.push_back("start paragraph");
	std::vector<std::string>	drinkTxts;
	drinkTxts.push_back("drink paragraph");
	std::vector<std::string>	eatTxts;
	eatTxts.push_back("eat paragraph");
	std::vector<std::string>	wallTxts;
	wallTxts.push_back("wall paragraph");
	std::vector<std::string>	skeletonTxts;
	skeletonTxts.push_back("skeleton paragraph");
	std::vector<std::string>	doorTxts;
	doorTxts.push_back("door paragraph1");
	doorTxts.push_back("door paragraph2");
	std::vector<std::string>	leverTxts;
	leverTxts.push_back("lever paragraph1");
	leverTxts.push_back("lever paragraph2");
	// + room paragraphs

	std::map<std::string, std::vector<std::string> > tavern;
	tavern["START"] = startTxts;
	tavern["DRINK"] = drinkTxts;
	tavern["EAT"] = startTxts;
	std::map<std::string, std::vector<std::string> > corridor;
	corridor["WALL"] = wallTxts;
	corridor["SKELETON"] = skeletonTxts;
	corridor["DOOR"] = doorTxts;
	corridor["LEVER"] = leverTxts;
	// std::map<std::string, std::vector<std::string> > room;

	_library[TAVERN] = tavern;
	_library[CORRIDOR] = corridor;
	// _library[ROOM] = room;

}

void    BotGameMaster::createTopics()
{
    _topics.push_back("Welcome to the Tavern ! Please take a sit, and when all the daring adventurers are present, enter the command START preceded by the symbol '*'");
	_topics.push_back("A dark corridor leading to a closed door.");
	_topics.push_back("A forgotten and enigmatic room in the depths of a dungeon.");
}

void    BotGameMaster::createRoomsName()
{
    _rooms.push_back("#TAVERN");
	_rooms.push_back("#CORRIDOR");
	_rooms.push_back("#ROOM");
}

void    BotGameMaster::createMessages()
{
    _messages.push_back("Hello young adventurers! It’s me, Jean-Claude. I will be your Game Master for the duration of this game. Whenever you wish to make one of the actions available to you, you must send me the corresponding keyword preceded by the symbol ‘*’. Examples : *LOOK ; *FIGHT ; *HELP");
    _messages.push_back("Invalid command. I don’t understand a single bit of what you’re telling me.");
    _messages.push_back("Texte de présentation du corridor. 4 choix");
}

void	BotGameMaster::initBot()
{
	struct addrinfo servParam;
	
	memset(&servParam, 0, sizeof(servParam));

	servParam.ai_family = AF_UNSPEC;
	servParam.ai_socktype = SOCK_STREAM;
	servParam.ai_flags = AI_PASSIVE;
	gethostname(_hostName, sizeof(_hostName));
	if (getaddrinfo(_hostName, _servPort.c_str(), &servParam, &_servInfo) != 0)
	{
		std::cout << "getaddrinfo failed" << std::endl;
		return ;
	}
	_botFd = socket(_servInfo->ai_family, _servInfo->ai_socktype, _servInfo->ai_protocol);
	if (_botFd == -1)
	{
		freeaddrinfo(_servInfo);
		std::cout << "socket Failed" << std::endl;
		return ;
	}
}