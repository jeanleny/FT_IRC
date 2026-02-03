#pragma once

#include <Client.hpp>
#include <iostream>

#define MODE_NB 5

typedef enum mode
{
	t,
	i,
	k,
	o,
	l
} e_mode;

class	Channel 
{
	public :
		Channel(std::string name);
		~Channel();

		const std::string			getName();
		size_t 						getMemberNb();
		const std::vector<Client>	getMemberList();
		const bool					*getMode();
		
		bool				isChannelMember(std::string nickname);
		void				addMember(Client &client);
		
		void				displayMode(Client &emitter);
		void				changeMode(Client client, std::string flags, bool disable, std::string chanName);

	private :
		std::vector<Client>		_memberList;
		std::string 			_name;
		std::string				_topic;
		size_t					_memberNb;
		size_t					_memberLimit;
		bool 					_mode[MODE_NB];
};
