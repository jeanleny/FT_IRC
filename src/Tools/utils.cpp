#include <Server.hpp>


std::vector<std::string> split(const std::string & str)
{
	std::vector<std::string> split;
	std::string elem;
	int		start = 0;
	int		end = 0;
	for (size_t i = 0; i < str.size();)
	{
		while (isspace(str[i]) && str[i])
		i++;
		start = i;
		while (!isspace(str[i]) && str[i])
		i++;
		end = i;
		split.push_back(str.substr(start, end - start));
	}
	return split;
}

bool    isvalidNickname(std::string nickname)
{
    std::string charset = "`|^_-{}[]\\";

	size_t pos;
	for (size_t i = 0; i < nickname.size(); i++)
    {
		pos = charset.find(nickname[i]);
        if (!isalnum(nickname[i]) && pos == std::string::npos)
			return false;
    }
    return true;
}

bool	isEmptyCommand(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isspace(str[i]))
			return (false);
	}
	return (true);
}

void	eraseTrailingSpaces(std::string &str)
{
	std::string trailing(" \r\n");
	std::size_t found = str.find_last_not_of(trailing);
	if (found != std::string::npos)
		str.erase(found + 1);
	else
		str.clear();
}
void	displayCommand(Client & client)
{
	std::cout << client.getCommandId() << " | ";
	for (size_t i = 0; i < client.getCommandArgs().size(); i++)
	{
		std::cout << client.getCommandArgs()[i] << " ";
		std::cout << "|" << std::endl; 
	}
	std::cout << std::endl;
}

bool	strIsDigit(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

bool isOneArg(std::string str)
{
	int	i = 0;
	while (isspace(str[i]) && str[i])
		i++;
	while (!isspace(str[i]) && str[i])
		i++;
	while (isspace(str[i]) && str[i])
		i++;
	return (str[i] == '\0');
}

void	sendException(int fd ,const std::exception &e)
{
	const char	*msg = e.what();
	size_t		len = strlen(msg);

	send(fd, msg, len, 0);
}

bool	checkPrefix(std::string channelName)
{
	return (channelName[0] == '#');
}

//-----------------------DEBUG

void	displayClients(std::vector<Client> _clients)
{
	for(size_t i = 0; i < _clients.size(); i++)
	{
		std::cout << _clients[i].getClientFd() << std::endl;
	}
}

void	displayMemberList(Channel & channel)
{

	std::vector<Client>	memberList = channel.getMemberList();
	for(size_t i = 0; i < memberList.size(); i++)
	{
		std::cout << i << " | " << memberList[i].getNickname() << std::endl;
	}
}
