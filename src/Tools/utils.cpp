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
		if (str[i] == ':')
		{
			start = i + 1;
			end = str.size();
			split.push_back(str.substr(start, end - start));
			return split;
		}
		else
		{
			start = i;
			while (!isspace(str[i]) && str[i])
				i++;
			end = i;
			split.push_back(str.substr(start, end - start));
		}
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

void	uppercaseStr(std::string &str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (islower(str[i]))
			str[i] -= 32;
	}
}

bool	isCtrlD(char *buf)
{
	int i = 0;
	while (buf[i])
	{
		if (buf[i + 1] != '\0')
		{
			if (buf[i] == '\r' && buf[i + 1] == '\n')
				return (false);
		}
		i++;
	}
	return (true);
} 
