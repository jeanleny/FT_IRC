#ifndef SERVER_HPP
# define SERVER_HPP

#include <Exception.hpp>
#include <Client.hpp>
#include <Channel.hpp>
#include <ICommand.hpp>
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
#include <ServerUtils.h>
#include <Signals.hpp>
#include <utils.h>

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <stdlib.h>
#include <algorithm>


#define MAX_EVENTS 10
#define NB_CMD 10
#define ERROR -1

extern volatile sig_atomic_t   g_exit;

class Server
{
	public :

		Server(char *port, char *password);
		~Server();

		static Server&			getInstance();
		std::string				getHostname() const;

		void					initServer();
		void					initICommands();
		void					runningServer();
		void					serverClosing();
		void					manageEvents(struct epoll_event &currentEvent);
		void					manageWrongEvents(int bytes, ssize_t removeIndex, int eventFd);
		void					clearWrongEvent(size_t rmIndex);
		void					manageCommand(Client & client);
		void					serverRegistration(Client & emitter);
		void					identifyCommand(char *buf, int clientIndex);
		void					extractCommandId(Client & ref, std::string id);
		void					commandSwitch(Client & client);
		ssize_t					findClient(int clientFd);
		Client					getClientByNickname(std::string nickname) const;
		bool					validPassword(std::string pass);
		bool					isUsedNickname(std::string nickname);
		int						extractCommand(char *buf, Client & client);
	
		bool					isInServer(Client &client);
		bool					isInChannel(Client &client, std::string chanName);
		bool					isInvitedInChannel(Client &client, std::string chanName);
		ssize_t					getChannelByName(std::string chanName);
		bool					existChannel(std::string name);
		void					createChannel(Client &emitter, std::string chanName);
		void					addChannelMember(Client &client, std::string chanName);
		void					removeChannelMember(Client &client, std::string chanName);
		void					kickChannelMember(Client & client, Client &kicked, std::string chanName);
		void					inviteChannelMember(Client & client, Client &kicked, std::string chanName);
		bool					findChannel(std::string chanName);
		void 					sendMessageToChannel(Client & client, std::string & chanName, const char *msg);
		void 					sendJoinMessage(Client & client, std::string & chanName);
		void 					displayChannelTopic(Client & client, std::string chanName);
		void					changeChannelTopic(Client & client, std::string chanName, std::string newTopic);

		void					sendWelcomeMessage(Client & client);
		void					sendNickMessage(Client & client);
		void					displayChannelMode(Client emitter, std::string arg);
		void					changeChannelMode(std::string chanName, size_t mode, bool disable);
		void					changeChannelKey(std::string chanName, std::string key);
		void					changeChannelLimit(std::string chanName, size_t limit);
		void					changeChannelNickList(Client client);
		bool					checkChannelMode(std::string chanName, size_t mode, bool state);
		bool					checkChannelOperator(std::string chanName, Client client);
		bool					checkChannelKey(std::string chanName, std::string key);
		void					addChannelOperator(std::string chanName, Client target);
		void					rmChannelOperator(std::string chanName, Client target);
		void					presentMode(std::string chanName, std::string mode);

	private :

		static	Server			*_instance;
		std::vector<Client>		_clients;
		std::vector<Channel>	_channels;
		std::vector<int>		_clientsFds;
		ICommand*				_iCommands[NB_CMD];
		struct epoll_event		_userEvents;
		struct epoll_event		_queuedEvents[MAX_EVENTS];
		struct addrinfo			*_servInfo;
		int						_servFd;
		int						_epollFd;
		std::string				_servPort;
		std::string				_password;
		char					_hostName[128];
		void					initEpoll();
		void					addClient();
};

#endif
