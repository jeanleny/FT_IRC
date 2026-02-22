#include <NickCommand.hpp>

NickCommand::NickCommand()
{

}
NickCommand::~NickCommand()
{

}

int     parseNickname(const std::vector<std::string>& args)
{
    if (args[0].size() < 1 || args[0].size() > 9)
        return -1;

    std::string nickname = args[0];
    if (isdigit(nickname[0]) || !isvalidNickname(nickname))
        return -1;
    return 0;
}

void    defineNickname(Client & client, const std::string & nickname)
{
    client.setNickname(nickname);
    if (client.getRegisterStatus() == NICK_STATUS)
    {
        client.setRegisterStatus(USER);
        Server::getInstance().sendUserQuery(client);
    }
    else // Nick Command typed after registration
	{
        Server::getInstance().changeChannelNickList(client);
        Server::getInstance().sendNickMessage(client);
	}
}


void    NickCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (args.size() == 0)
        throw NotEnoughParametersException(client);
    if (parseNickname(args) == -1)
        throw ErroneusNicknameException(client);
    const std::string nickname = args[0];
    if (Server::getInstance().isUsedNickname(nickname))
        throw UsedNicknameException(client);
    defineNickname(client, nickname);
}
