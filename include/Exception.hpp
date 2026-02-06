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

class ErroneusNicknameException : public std::exception //432
{
	public :

		ErroneusNicknameException(Client & client);
		virtual ~ErroneusNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class UsedNicknameException : public std::exception //433
{
	public :

		UsedNicknameException(Client & client);
		virtual ~UsedNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class UserNotInChannelException : public std::exception //441
{
	public :

		UserNotInChannelException(Client & client);
		virtual ~UserNotInChannelException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class NotInThisChannelException : public std::exception //442
{
	public :

		NotInThisChannelException(Client & client);
		virtual ~NotInThisChannelException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class AlreadyInChannelException : public std::exception //443
{
	public :

		AlreadyInChannelException(Client & client);
		virtual ~AlreadyInChannelException() throw() {}
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

class NoRecipientException : public std::exception //411
{
	public :

		NoRecipientException(Client & client);
		virtual ~NoRecipientException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class NoTextToSendException : public std::exception //412
{
	public :

		NoTextToSendException(Client & client);
		virtual ~NoTextToSendException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class CannotSendToChannelException : public std::exception //404
{
	public :

		CannotSendToChannelException(Client & client);
		virtual ~CannotSendToChannelException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class NoSuchNicknameException : public std::exception //401
{
	public :

		NoSuchNicknameException(Client &client);
		virtual ~NoSuchNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};



class InvalidChannelException : public std::exception //476
{
	public :

		InvalidChannelException(Client & client);
		virtual ~InvalidChannelException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :
		std::string	_msg;
};

class NotAnOperatorException : public std::exception //476
{
	public :

		NotAnOperatorException(Client & client);
		virtual ~NotAnOperatorException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :
		std::string	_msg;
};

class ChannelLimitExcedeedException : public std::exception
{
	public :
		const char * what() const throw();
};

class NoSuchChannelException : public std::exception //403
{
	public :

		NoSuchChannelException(Client & client);
		virtual ~NoSuchChannelException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class NotEnoughParametersException : public std::exception //461
{
	public :

		NotEnoughParametersException(Client & client);
		virtual ~NotEnoughParametersException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class InviteOnlyException : public std::exception //473
{
	public :

		InviteOnlyException(Client & client);
		virtual ~InviteOnlyException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

#endif
