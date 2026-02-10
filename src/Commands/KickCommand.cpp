#include <KickCommand.hpp>

KickCommand::KickCommand()
{

}
KickCommand::~KickCommand()
{

}

void    parseKickArgs(Client & client, const std::vector<std::string>& args)
{
    if (args.size() > 2)
        throw CustomErrorException(client);
    if (args.size() < 2)
        throw NotEnoughParametersException(client);

    if (!Server::getInstance().existChannel(args[0]))
        throw NoSuchChannelException(client);
    if (!Server::getInstance().isUsedNickname(args[1]))
        throw NoSuchNicknameException(client);
}

void    KickCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    parseKickArgs(client, args);

    std::string     chanName = args[0];
    std::string     nickname = args[1];

    if(!Server::getInstance().checkChannelOperator(chanName, client))
        throw NotAnOperatorException(client);

    Client  kicked = Server::getInstance().getClientByNickname(nickname);
    if (!Server::getInstance().isInChannel(kicked, chanName))
        throw UserNotInChannelException(client);

    Server::getInstance().kickChannelMember(client, kicked, chanName);
}
