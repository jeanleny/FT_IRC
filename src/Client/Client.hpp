#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <sys/socket.h>
#include <sys/types.h>

class Client
{
	private :
		int							_clientFd;
		//struct	sockaddr_storage	_clientAddr;
		//socklen_t					_clientAddrSize;
	
	public :
		int							getClientFd();
		Client(int fd);
		~Client();
};

#endif
