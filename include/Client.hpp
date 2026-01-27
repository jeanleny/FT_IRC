#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include <vector>

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
		std::vector<std::string>	_commandArgs;
		//ssize_t						_cmdId;
		//struct	sockaddr_storage	_clientAddr;
		//socklen_t					_clientAddrSize;
	
	public :
		int							getClientFd() const;
		int							getRegisterStatus() const;
		size_t						getCommandId() const;
		std::vector<std::string>	getCommandArgs() const;
		void						setCommandId(size_t id);
		void						setCommandArgs(std::vector<std::string> args);
		void						setRegisterStatus(int status);


		Client(int fd);
		~Client();
};

#endif
