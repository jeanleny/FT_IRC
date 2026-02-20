#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <map>

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

typedef enum gameCmd
{
	START,
	WALL,
	SKELETON,
	DOOR,
	LEVER,
} e_gameCmd;

class BotGameMaster 
{
	public :
		BotGameMaster(char *port, char *pass);
		~BotGameMaster();
		void						initBot();
		void						botConnect();
		int							servConnect();
		void						servProcess();
		void						sendCommand(std::string msg);
		std::string					parsePlayerNick(std::string content);
		std::string					getMessage(std::vector<std::string> args);
		std::string					extractGameCmd(std::string str);
		std::vector<std::string>	getArgs(std::string str);
		bool						isPrivMsg(std::vector<std::string> args);
		bool						isGameCmd(std::string str);
		void						parsePlayerCmd(char *str, t_parse *parse);
		void						authentication();
		void						createRooms();
		void   						manageGameCommand(t_parse parse);
		void						setupPlayers(std::string command);
		bool						isRoomCommand(std::string command, e_roomId room);
		bool    					isPlayerInRoom(std::string nickname, e_roomId room);

		void						sendInvalidCommandException(std::string nickname);

	private :
		struct addrinfo			*_servInfo;
		std::string				_servPort;
		std::string				_pass;
		int						_botFd;
		char					_hostName[128];

		//----GAME CONTENT
		bool												_gameRunning;
		std::vector<std::string>							_rooms;
		std::vector<std::string>							_topics;
		std::map<e_roomId, std::vector<std::string> >		_gameCmd;
		std::map<std::string, e_roomId>						_players;
};
void						parsePlayerCmd(char *str);
std::vector<std::string> 	split(const std::string & str);

