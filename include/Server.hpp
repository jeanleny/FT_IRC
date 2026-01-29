#ifndef SERVER_HPP
# define SERVER_HPP

#include <Exception.hpp>
#include <Client.hpp>
#include <ICommand.hpp>
#include <PassCommand.hpp>
#include <NickCommand.hpp>
#include <UserCommand.hpp>
#include <ServerUtils.h>
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


#define MAX_EVENTS 10
#define NB_CMD 9

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
		void					manageEvents(struct epoll_event currentEvent);
		void					manageWrongEvents(int bytes, ssize_t removeIndex, int eventFd);
		void					manageCommand(int recvBytes, Client & client);
		void					serverRegistration(Client & emitter);
		void					identifyCommand(char *buf, int clientIndex);
		void					extractCommandId(Client & ref, std::string id);
		void					commandSwitch(Client & client);
		ssize_t					findClient(int clientFd);
		bool					validPassword(std::string pass);
		bool					isUsedNickname(std::string nickname);
		int						extractCommand(char *buf, Client & client);

	private :

		static	Server			*_instance;
		std::vector<Client>		_clients;
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
