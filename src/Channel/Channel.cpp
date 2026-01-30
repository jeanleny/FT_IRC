#include <Channel.hpp>

Channel::Channel(std::string name) : _name(name), _memberNb(0), _memberLimit(10)
{
	//Unused variables to compile
	(void)_memberNb;
	(void)_memberLimit;
	for (size_t i = 0; i < MODE_NB ; i++)
		_mode[i] = false;
};

Channel::~Channel(){};

const std::string Channel::getName()
{
	return (_name);
}

size_t Channel::getMemberNb()
{
	return (_memberNb);
}

bool	Channel::isChannelMember(std::string nickname)
{
	for (size_t i = 0; i < _memberList.size(); i++)
	{
		if (_memberList[i].getNickname() == nickname)
			return (true);
	}
	return (false);
}
