#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <string>

typedef enum registeredStatus
{
	PASS_STATUS,
	USER_STATUS,
	NICK_STATUS,
	REGISTERED
} e_registeredStatus;

typedef enum commandId
{
	PASS,
	NICK,
	USER,
	KICK,
	PRIVMSG,
	TOPIC,
	MODE,
	JOIN,
	INVITE,
	UNKNOWN
} e_commandId;

class Client
{
	private :
		int							_clientFd;
		int							_registerStatus;
		size_t						_commandId;
		std::string					_commandArg;
		//ssize_t						_cmdId;
		//struct	sockaddr_storage	_clientAddr;
		//socklen_t					_clientAddrSize;
	
	public :
		int							getClientFd() const;
		int							getRegisterStatus() const;
		size_t						getCommandId() const;
		std::string					getCommandArg() const;
		void						setCommandId(size_t id);
		void						setCommandArg(std::string arg);
		void						setRegisterStatus(int status);


		Client(int fd);
		~Client();
};

#endif
