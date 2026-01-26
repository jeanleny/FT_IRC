#ifndef SERVER_HPP
# define SERVER_HPP

#include "../Exception/Exception.hpp"
#include "../Client/Client.hpp"
#include "../Commands/ICommand.hpp"

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

class Server
{
	public :
		Server(char *port, char *password);
		~Server();
		void						initServer();
		void						initICommands();
		void						runningServer();
		void						manageEvents(struct epoll_event currentEvent);
		void						manageWrongEvents(int bytes, ssize_t removeIndex, int eventFd);
		void						manageCommand(int recvBytes, ssize_t index);
		void						serverRegistration(int index);
		void						identifyCommand(char *buf, int clientIndex);
		void						extractCommandId(char *buf, int clientIndex);
		void						commandSwitch(int index);
		ssize_t						findClient(int clientFd);
		static Server&				getInstance();
		void						poussememe();

	private :
		static	Server			*_instance;
		std::vector<Client>		_clients;
		std::vector<ICommand>	_iCommands[9];
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
