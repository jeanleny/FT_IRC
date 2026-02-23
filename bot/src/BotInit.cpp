#include <BotGameMaster.hpp>

/*
To access a paragraph in the library, syntax is : _library[ROOM]["COMMAND"][index]
Example : 	_library[CORRIDOR]["DOOR"][1]
			_library[TAVERN]["START"][0]

*/

void	BotGameMaster::createLibrary()
{
	std::vector<std::string>	startTxts;
	startTxts.push_back("Presentation du Corridor. Choix : WALL | SKELETON | DOOR");
	std::vector<std::string>	drinkTxts;
	drinkTxts.push_back(" drinks a Pina Colada and start zouking avec Magic System ça c'est le son qu'on aime.");
	drinkTxts.push_back(" drinks a big chug of water with Salmonelles inside.");
	drinkTxts.push_back(" takes a sip of old whisky while drawing deeply on his Cuban cigar.");
	drinkTxts.push_back(" drinks a Coca-Cola Zero.");
	drinkTxts.push_back(" drinks a tisane Nuit Tranquille.");
	drinkTxts.push_back(" drinks some hydro-alcoolic gel.");
	drinkTxts.push_back(" drinks 14 egg whites to reach his daily protein intake.");
	std::vector<std::string>	eatTxts;
	eatTxts.push_back(" eat a creamy mushroom and leek soup.");
	eatTxts.push_back(" eat some big rognons de veau.");
	eatTxts.push_back(" eat a menu maxi best of iced tea potates.");
	eatTxts.push_back(" eat a crouton de pain.");
	eatTxts.push_back(" eat a big slice of old cheddar.");
	eatTxts.push_back(" eat 1 pound of salami.");
	eatTxts.push_back(" eat a motherf****n caille en sarcophage.");
	std::vector<std::string>	chatTxts;
	chatTxts.push_back(" : \"Cette armure en obsidienne elfique me fait un mal de chien, je savais que j'aurais pas du l'acheter sur Ali Express, elle est meme pas garantie\"");
	chatTxts.push_back(" : \"Vous avez vu, il pleut. Alors qu'hier il faisait beau. C'est fou il y a plus de saisons en vrai, vous ne trouvez pas ?\"");
	chatTxts.push_back(" : \"Comme mon grand-père dit toujours avant de commencer une nouvelle aventure : Macron EXPLOSION!!!! hahaa vous avez la ref ?\"");
	chatTxts.push_back(" : \"Je trouve que Costa-Gavras fait un cinema très Lynchien comparé a son père qui s'est toujours cantonné a des plans rapprochés en focale courte. Non ? Allô ? Quelqu'un pour interagir avec moi ? S'il vous plait, j'ai besoin d'attention.\"");
	chatTxts.push_back(" : \"PAYS DE GALLES INDEPENDANT ! Pardon je l'ai dit à voix haute ça ?\"");
	chatTxts.push_back(" : \"Qu'est ce qui est jaune et qui attend ?\"");
	chatTxts.push_back(" : \"Je pense que je serai le premier a sortir du donjon. Je dit ça parce que j'ai extrêmement confiance en moi et que mon père m'a donné beaucoup d'attention étant jeune, contrairement a mon frère qu'on a vendu la semaine dernière sur le marché aux esclaves.\"");
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
	tavern["EAT"] = eatTxts;
	tavern["CHAT"] = chatTxts;
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
    _topics.push_back("Welcome to the Tavern ! Please take a sit. While waiting your mates, you can use the following commands to *DRINK, *EAT, or *CHAT. When all the adventurers are present, enter the command *START to launch the game.");
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
	std::srand(std::time(NULL));
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