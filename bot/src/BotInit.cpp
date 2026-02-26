#include <BotGameMaster.hpp>

/*
To access a paragraph in the library, syntax is : _library[ROOM]["COMMAND"][index]
Example : 	_library[CORRIDOR]["DOOR"][1]
			_library[TAVERN]["START"][0]

*/

void	BotGameMaster::createLibrary()
{
	std::vector<std::string>	startTxts;
	startTxts.push_back("You are now walking through a long, dark, and narrow corridor that leads to a wooden closed door.");
	startTxts.push_back("On the left, on the wall, a series of wooden levers seem to control a mechanism (use *WALL to examine them).");
	startTxts.push_back("On the ground, sitting near the door, lies a skeleton, probably that of an unfortunate adventurer who died in this place (use *CORPSE to search it).");
	startTxts.push_back("Finally, the wooden door in front of you seems to have different inscriptions carved directly into the wood (use *DOOR to read them).");
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
	std::vector<std::string>	wallTxts;
	wallTxts.push_back("On the wall, five levers seem to control the door mechanism's opening.");
	wallTxts.push_back("Each lever have an symbol, unfortunately worn away by time : [?][?][?][?][?]");
	wallTxts.push_back("Use the *LEVER command followed par the positions you want to activate. Example : *LEVERS 135 to activate levers 1, 3, 5.");
	std::vector<std::string>	corpseTxts;
	corpseTxts.push_back("In front of you lies the body of an unlucky adventurer, probably unable to open this cursed door.");
	corpseTxts.push_back(" Searching the pockets of his old clothes, you find a scroll with a cryptic message written on it : ");
	corpseTxts.push_back("1 = '!' ; 2 = '@' ; 3 = '#' ; 4 = '%'");
	std::vector<std::string>	doorTxts;
	doorTxts.push_back("You are facing a large wooden door which seems to be closed.");
	doorTxts.push_back( "Three stranges inscriptions are carved into the wood, which are difficult to decipher.");
	doorTxts.push_back("\"ON $ % !\" \"OFF @ #\"");
	std::vector<std::string>	leverTxts;
	leverTxts.push_back("You pull the levers, but nothing happens.");
	leverTxts.push_back("You pull the levers, and suddenly a metallic sound comes from the door. The door is unlocked!");
	std::vector<std::string>	crankTxts;
	crankTxts.push_back("The crank mechanism is blocked. It is controlled by a four-digit keypad currently displaying 0000. Each digit on the keypad is associated with a strange symbol.");
	crankTxts.push_back("Use *CODE followed by a four-digit combination (example: 1234) to enter it into the keypad.");
	crankTxts.push_back("Don't forget : use *SHOUT to communicate with the other adventurers.");
	crankTxts.push_back("Also, there's some mysterious symbols drawn above under it");
	std::vector<std::string>	codeTxts;
	codeTxts.push_back("You enter the code, but nothing happens.");
	codeTxts.push_back("You enter the code, and a green indicator light turns on. You did it! The crank is now unlocked — use *CRANK to climb out of the pit.");

	std::map<std::string, std::vector<std::string> > tavern;
	tavern["START"] = startTxts;
	tavern["DRINK"] = drinkTxts;
	tavern["EAT"] = eatTxts;
	std::map<std::string, std::vector<std::string> > corridor;
	corridor["WALL"] = wallTxts;
	corridor["CORPSE"] = corpseTxts;
	corridor["DOOR"] = doorTxts;
	corridor["LEVER"] = leverTxts;
	std::map<std::string, std::vector<std::string> > room1;
	room1["1"] = initMermaidAscii();
	room1["1"].push_back("The wonderful mermaid");
	room1["2"] = initSnakeAscii();
	room1["2"].push_back("The sneaky snake");
	room1["3"] = initSpiderAscii();
	room1["3"].push_back("The awful spider");
	room1["4"] = initCentaurAscii();
	room1["4"].push_back("The majestuous centaur");
	room1["DOOR"];
	std::map<std::string, std::vector<std::string> > pit;
	pit["CRANK"] = crankTxts;
	pit["CODE"] = codeTxts;
	pit["SHOUT"];

	std::map<std::string, std::vector<std::string> > antechamber;
	antechamber["CHEST"];
	antechamber["BOSS"];

	_library[TAVERN] = tavern;
	_library[CORRIDOR] = corridor;
	_library[PIT] = pit;
	_library[ROOM1] = room1;
	_library[ANTECHAMBER] = antechamber;
}

void    BotGameMaster::createTopics()
{
    _topics.push_back("Welcome to the Tavern ! Please take a sit. While waiting your mates, you can use the following commands to *DRINK, *EAT. When all the adventurers are present, enter the command *START to launch the game.");
	_topics.push_back("A dark corridor leading to a closed door.");
	_topics.push_back("You enter a large chamber lighted by torches fixed to the walls. At the center, a deep pit from which you can hear screams. Your companion has fallen into the pit! Maybe the surrounding paints on the walls can help you to get him out of here. Type any numbers between *1 to *4 to check if there are any clues on them");
	_topics.push_back("You fell into a pit ! You're stuck in there on your own... In this hole, if you do not shout, no one will hear you. Use *SHOUT to communicate with the other adventurers. The only thing around you is an old rusty crank used to lower a ladder. Use *CRANK to inspect");
	_topics.push_back("Topic Antechamber");
}

void    BotGameMaster::createRoomsName()
{
    _rooms.push_back("#TAVERN");
	_rooms.push_back("#CORRIDOR");
	_rooms.push_back("#ROOM1");
	_rooms.push_back("#PIT");
	_rooms.push_back("#ANTECHAMBER");
}

void    BotGameMaster::createMessages()
{
    _messages.push_back("Hello young adventurers! It’s me, Jean-Claude. I will be your Game Master for the duration of this game. Whenever you wish to make one of the actions available to you, you must send me the corresponding keyword preceded by the symbol ‘*’. Examples : *LOOK ; *FIGHT ; *HELP");
    _messages.push_back("Invalid command. I don’t understand a single bit of what you’re telling me.");
}

void	BotGameMaster::initDoors()
{
	_doors.push_back(LOCKED);
	_doors.push_back(LOCKED);
}

void	BotGameMaster::initalizeLevers()
{
	for(int i = 0; i < 5; i++)
	{
		_levers.push_back("[-]");
	}
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

void	BotGameMaster::createItems()
{
	std::string names[4] = {"The Mighty sword", "The lame stick", "The Divine staff", "The crappy spoon"};
	int			dmg[4] = {5, 1, 10, 1};

	for (size_t i = 0; i < 4; i++)
	{
		_items.push_back(Item(names[i], dmg[i]));
	}
}
