#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <iostream>
#include "Client.hpp"
#include "Server.hpp"

class AddrinfoFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class BindFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class SocketFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class ListenFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class RecvFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class RegisterQueryException : public std::exception
{
	public :
		const char * what() const throw();
};

class PasswordQueryException : public std::exception
{
	public :
		const char * what() const throw();
};

class UsernameQueryException : public std::exception
{
	public :
		const char * what() const throw();
};

class NicknameQueryException : public std::exception
{
	public :
		const char * what() const throw();
};

class AlreadyRegisteredException : public std::exception
{
	public :
		const char * what() const throw();
};

class WrongCommandException : public std::exception
{
	public :
		const char * what() const throw();
};

class UnvalidPasswordException : public std::exception
{
	public :
		const char * what() const throw();
};

class MissingArgumentsException : public std::exception
{
	public :
		const char * what() const throw();
};

//NICK COMMAND

class ErroneusNicknameException : public std::exception
{
	public :

		ErroneusNicknameException(Client & client);
		virtual ~ErroneusNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class UsedNicknameException : public std::exception
{
	public :

		UsedNicknameException(Client & client);
		virtual ~UsedNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

//USER COMMAND

class ErroneusUsernameException : public std::exception
{
	public :
		const char * what() const throw();
};

//PRIVMSG COMMAND

class NoRecipientException : public std::exception
{
	public :

		NoRecipientException(Client & client);
		virtual ~NoRecipientException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class NoTextToSendException : public std::exception
{
	public :

		NoTextToSendException(Client & client);
		virtual ~NoTextToSendException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class NoSuchNicknameException : public std::exception
{
	public :

		NoSuchNicknameException(Client &client);
		virtual ~NoSuchNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};



class InvalidChannelException : public std::exception
{
	public :
		const char * what() const throw();
};

class AlreadyInChannelException : public std::exception
{
	public :
		const char * what() const throw();
};

class ChannelLimitExcedeedException : public std::exception
{
	public :
		const char * what() const throw();
};

#endif
