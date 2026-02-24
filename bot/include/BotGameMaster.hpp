#pragma once

#include <iostream>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>



typedef struct s_parse
{
	std::vector<std::string> args;
	std::string	content;
	std::string	player;
	std::string	cmd;
	std::string	msg;
	bool		valid;
} t_parse;

typedef enum roomId
{
	TAVERN,
	CORRIDOR,
	ROOM,
	HOLE,
} e_roomId;

typedef enum msgId
{
	PRESENTATION,
	INVALID,
	CORRIDOR_MSG,
} e_msgId;


extern volatile sig_atomic_t   g_exit;

class BotGameMaster 
{
	public :
		BotGameMaster(char *port, char *pass);
		~BotGameMaster();
		void						initBot();
		void    					setSigaction();
		void						createLibrary();
		void						createTopics();
		void						createRoomsName();
		void						createMessages();
		void						initalizeLevers();
		void						lockDoors();

		void						botConnect();
		int							servConnect();
		void						servProcess();
		std::string					parsePlayerNick(std::string content);
		std::string					getMessage(std::vector<std::string> args);
		std::string					extractGameCmd(std::string str);
		std::vector<std::string>	getArgs(std::string str);
		bool						isPrivMsg(std::vector<std::string> args);
		bool						isGameCmd(std::string str);
		void						parsePlayerCmd(std::string str, t_parse *parse);
		void						authentication();
		void						createRooms();
		void   						manageGameCommand(t_parse parse);
		void    					manageTavernCommand(t_parse parse);
		void    					manageRoom1Command(t_parse parse);
		void						manageLeverCommand(t_parse parse);
		void						switchLever(int leverPos);
		bool						isGoodLevers();
		void 						resetLevers();
		void						setupPlayers(std::string command);
		void						shutDownGame();
		bool						isRoomCommand(std::string command, e_roomId room);
		bool    					isPlayerInRoom(std::string nickname, e_roomId room);
		
		void						sendCommand(std::string msg);
		void						sendPrivmsg(std::string nickname, std::string message);
		void						sendLibraryContent(std::string player, std::vector<std::string> content);

	private :
		struct addrinfo			*_servInfo;
		std::string				_servPort;
		std::string				_pass;
		int						_botFd;
		char					_hostName[128];

		//----GAME CONTENT
		bool																	_gameRunning;
		std::vector<std::string>												_rooms;
		std::vector<std::string>												_topics;
		std::vector<std::string>												_messages;
		std::map<e_roomId, std::map<std::string, std::vector<std::string> > >	_library;
		std::map<std::string, e_roomId>											_players;
		std::vector<std::string>												_levers;
		std::vector<bool>														_doors;
};

void						parsePlayerCmd(char *str);
std::vector<std::string> 	split(const std::string & str);
std::vector<std::string> 	trailingSplit(std::string str);

