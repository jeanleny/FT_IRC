#pragma once

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
	private :
		std::string 	_name;
		std::string		_topic;
		size_t			_memberNb;
		size_t			_memberLimit;
		bool 			_mode[MODE_NB];	
};
