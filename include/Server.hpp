#ifndef SERVER_HPP
# define SERVER_HPP

#include <Exception.hpp>
#include <Client.hpp>
#include <GameMaster.hpp>
#include <Channel.hpp>
#include <ICommand.hpp>
#include <PlayCommand.hpp>
#include <PassCommand.hpp>
#include <NickCommand.hpp>
#include <UserCommand.hpp>
#include <JoinCommand.hpp>
#include <ModeCommand.hpp>
#include <PrivmsgCommand.hpp>
#include <KickCommand.hpp>
#include <TopicCommand.hpp>
#include <InviteCommand.hpp>
#include <PartCommand.hpp>
#include <GameMaster.hpp>
#include <utils.h>
#include <iostream>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <stdlib.h>
#include <algorithm>
#include <map>


#define MAX_EVENTS 10
#define NB_CMD 11
#define NB_GCMD 4
#define ERROR -1
#define GAME "#LOBBY"

extern volatile sig_atomic_t   g_exit;

class Server
{
	public :
	
		Server(char *port, char *password);
		~Server();
		
		static Server&			getInstance();
		std::string				getHostname() const;
		void					initServer();
		void					runningServer();
		void				    setSigaction();

		
		void					createChannel(Client &emitter, std::string chanName);
		void					addChannelMember(Client &client, std::string chanName);
		bool					isInChannel(Client &client, std::string chanName);
		bool					isInvitedInChannel(Client &client, std::string chanName);
		bool					existChannel(std::string name);
		bool					isUsedNickname(std::string nickname);
		bool					isInServer(Client &client);
		Client					getClientByNickname(std::string nickname) const;
		
		//----MODE METHODS------------------------------------------------------------------------------
	
		void					changeChannelTopic(Client & client, std::string chanName, std::string newTopic);
		void					changeChannelMode(std::string chanName, size_t mode, bool disable);
		void					changeChannelKey(std::string chanName, std::string key);
		void					changeChannelLimit(std::string chanName, size_t limit);
		void					changeChannelNickList(Client client);
		void					addChannelOperator(std::string chanName, Client target);
		void					rmChannelOperator(std::string chanName, Client target);
		bool					checkChannelMode(std::string chanName, size_t mode, bool state);
		bool					checkChannelOperator(std::string chanName, Client client);
		bool					checkChannelKey(std::string chanName, std::string key);
		void					removeChannelMember(Client &client, std::string chanName);
		void					inviteChannelMember(Client & client, Client &kicked, std::string chanName);
		void					kickChannelMember(Client & client, Client &kicked, std::string chanName);

		
		//----MESSAGES METHODS-------------------------------------------------------------------------------
		
		bool					validPassword(std::string pass);
		void					sendPassQuery(Client & client);
		void					sendUserQuery(Client & client);
		void					sendNickQuery(Client & client);
		void 					sendMessageToChannel(Client & client, std::string & chanName, const char *msg);
		void					sendWelcomeMessage(Client & client);
		void					sendNickMessage(Client & client);
		void 					sendJoinMessage(Client & client, std::string & chanName);
		void					displayChannelMode(Client emitter, std::string arg);
		void 					displayChannelTopic(Client & client, std::string chanName);
		
		//----BONUS METHODS------------------------------------------------------------------------------------

		bool					isRunningGameRoom(std::string chanName);
		bool					isCommandFromGame(std::string chanName);
		bool					isGameChannel(std::string chanName);
    	void					ServerPlayCmd(Client &emitter, const std::vector<std::string> &arg);
		void					manageGameCommand(Client &client);
		void					gMapSetup();
		void					gClear();
		void					callPartCommand(std::string chanName);
		void					displayMap();
		bool					isGameCommand(Client & client);
		void					startCommand(Client &client);
		void					manageRoom1Command(Client &client);


		private :
		
		static	Server									*_instance;
		struct epoll_event								_userEvents;
		struct epoll_event								_queuedEvents[MAX_EVENTS];
		struct addrinfo									*_servInfo;
		int												_servFd;
		int												_epollFd;
		std::string										_servPort;
		std::string										_password;
		char											_hostName[128];
		
		std::vector<Client>								_clients;
		std::vector<int>								_clientsFds;
		std::vector<Channel>							_channels;
		// std::vector<Channel>							_gChannels;
		ICommand*										_iCommands[NB_CMD];

		std::map<std::string, std::vector<std::string> >	_gmcmd;
		GameMaster											_gm;


		
		
		//----SERVER METHODS------------------------------------------------------------------------------
		
		void					initEpoll();
		void					initICommands();
		void					gameSetup();
		void					serverClosing();
		void					parseBuffer(Client &client, int currFd);
		void					manageEvents(struct epoll_event &currentEvent);
		void					manageWrongEvents(int bytes, ssize_t removeIndex, int eventFd);
		void					clearWrongEvent(size_t rmIndex);
		void					manageCommand(Client & client);
		void					addClient();
		
		//----PARSING METHODS------------------------------------------------------------------------------
		
		int						extractCommand(std::string str, Client & client);
		void					extractCommandId(Client & ref, std::string id);
		void					serverRegistration(Client & emitter);
		bool					isRegisterCommand(ssize_t cmdId);
		void					entryParsing(std::string password, std::string portEntry);
		
		//----CHANNELS METHODS------------------------------------------------------------------------------
		
		ssize_t					getChannelByName(std::string chanName);
		bool					findChannel(std::string chanName);
		
		
		//----UTILS METHODS----------------------------------------------------------------------------------
		
		ssize_t					findClient(int clientFd);
};

#endif
