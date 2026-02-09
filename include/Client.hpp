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
	USER,
	NICK,
	KICK,
	PRIVMSG,
	TOPIC,
	MODE,
	JOIN,
	INVITE,
	PART,
	UNKNOWN
} e_commandId;

class Client
{
	private :
		int							_clientFd;
		int							_registerStatus;
		size_t						_commandId;
		std::vector<std::string>	_commandArgs;
		std::string					_nickname;
		std::string					_oldNickname;
		std::string					_username;
		std::string					_cmd;
		//ssize_t						_cmdId;
		//struct	sockaddr_storage	_clientAddr;
		//socklen_t					_clientAddrSize;
	
	public :
		int							getClientFd() const;
		int							getRegisterStatus() const;
		size_t						getCommandId() const;
		std::string					getNickname() const;
		std::string					getOldNickname() const;
		std::string					getUsername() const;
		std::string					getCmd() const;
		std::vector<std::string>	getCommandArgs() const;
		void						setCommandId(size_t id);
		void						setCmd(std::string);
		void						setCommandArgs(std::vector<std::string> args);
		void						setRegisterStatus(int status);
		void						setNickname(std::string nickname);
		void						setUsername(std::string username);
		void						clearCommandArgs();

		Client(int fd);
		~Client();
};

#endif
