#include "BotGameMaster.hpp"

std::string toString(size_t n)
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

std::string colorText(std::string txt, std::string color, std::string back)
{
	if (back == NONE)
		return("\x03" + color + txt + "\x03");
	return("\x03" + color + "," + back + txt + "\x03");
}

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

std::string strToUpper(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}
	return (str);
}
