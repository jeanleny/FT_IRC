#include <Server.hpp>

bool	Server::existChannel(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (name == _channels[i].getName())
			return (true);
	}
	return (false);
}

/*bool	Server::isInChannel(Client &client)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		for (size_t j = 0; j < _channels[i].getMemberNb(); j++)
		{
			if (client.NickName() == _channels[i].memberList[j].getNickName)
				return (true);
		}
	}
}*/
