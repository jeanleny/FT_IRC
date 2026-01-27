#include <Server.hpp>


std::vector<std::string> split(const std::string & str)
{
	std::vector<std::string> split;
	std::string elem;
	int		start = 0;
	int		end = 0;
	for (size_t i = 0; i < str.size();)
	{
		while (isspace(str[i]))
		i++;
		start = i;
		while (!isspace(str[i]))
		i++;
		end = i;
		split.push_back(str.substr(start, end - start));
	}
	return split;
}

bool	isRegisterCommand(ssize_t cmdId)
{
	if (cmdId == USER || cmdId == NICK || cmdId == PASS)
	return (true);
	return (false);
}

//-----------------------DEBUG

void	displayClients(std::vector<Client> _clients)
{
	for(size_t i = 0; i < _clients.size(); i++)
	{
		std::cout << _clients[i].getClientFd() << std::endl;
	}
}

void	displayCommand(Client & client)
{
	std::cout << client.getCommandId() << " | ";
	for (size_t i = 0; i < client.getCommandArgs().size(); i++)
	{
		std::cout << client.getCommandArgs()[i] << " ";
	}
	std::cout << std::endl;
}