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
		const	std::string			getList();
		const	std::string			getTopic();
		
		bool				isChannelMember(int fd);
		void				addMember(Client &client);
		void				removeMember(Client &client);
		void				removeInvitedMember(Client &client);
		void				removeFromListString(Client &client);
		void				inviteMember(Client &client);
		bool				isInvited(int fd);

		
		void				displayMode(Client &emitter);
		void				displayTopic(Client &client);
		void				changeTopic(Client & client, std::string newTopic);
		void				changeMode(size_t mode, bool disable);
		void				changeKey(std::string key);
		void				changeLimit(size_t limit);
		bool				checkMode(size_t mode, bool state);
		bool				checkOperator(Client client);
		bool				checkKey(std::string key);
		void				addOperator(Client target);
		void				rmOperator(Client target);

	private :
		std::vector<int>		_operators;
		std::vector<int>		_invitedList;
		std::vector<Client>		_memberList;
		std::string				_list;
		std::string 			_name;
		std::string				_topic;
		std::string				_keyword;
		size_t					_memberNb;
		size_t					_memberLimit;
		bool 					_mode[MODE_NB];
};
