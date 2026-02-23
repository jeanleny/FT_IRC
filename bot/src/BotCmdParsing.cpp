#include <BotGameMaster.hpp>

std::vector<std::string> trailingSplit(std::string  str)
{
	std::vector<std::string> full;
	std::string res;
	size_t i = str.find("\r\n", 0);

	while (i != std::string::npos)
	{
		res = str.substr(0, i);
		full.push_back(res);
		str.erase(0, 0 + i + 2);
		i = str.find("\r\n", 0);
	}
	return (full);
}

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

std::string	BotGameMaster::parsePlayerNick(std::string content)
{
	std::string result;
	size_t del = content.find("!");

	result = content.substr(0, del);
	result.erase(result.begin());
	return (result);
}

std::string	BotGameMaster::getMessage(std::vector<std::string> args)
{
	size_t pos = args.size() - 1;

	return (args[pos]);
}


bool BotGameMaster::isPrivMsg(std::vector<std::string> args)
{
	if (args.size() > 1)
		return (args[1] == "PRIVMSG");
	return (false);
}

std::vector<std::string>	BotGameMaster::getArgs(std::string str)
{
	std::vector<std::string> args;

	str.erase(str.begin());
	args = split(str);
	return (args);	
}

bool BotGameMaster::isGameCmd(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isspace(str[i]))
		{
			if (str[i] == '*')
				return (true);
		}
	}
	return (false);
}

std::string BotGameMaster::extractGameCmd(std::string str)
{
	std::vector<std::string> splitted = split(str);

	splitted[0].erase(splitted[0].begin());
	for (size_t i = 0; i < splitted[0].length(); i++)
	{
		splitted[0][i] = toupper(splitted[0][i]);
	}
	return (splitted[0]);
}

void	BotGameMaster::parsePlayerCmd(std::string str, t_parse *parse)
{
	parse->valid = false;
	parse->player = parsePlayerNick(str);
	parse->args = getArgs(str);
	if (!isPrivMsg(parse->args))
		return ;
	parse->content = getMessage(parse->args);
	if (parse->content.size() > 0)
	{
		if (isGameCmd(parse->content))
		{
			parse->cmd = extractGameCmd(parse->content);
			parse->valid = true;
			parse->msg = "PRIVMSG " + parse->player + " :GameCommand received\r\n";
			sendCommand(parse->msg);
		}
	}
}
