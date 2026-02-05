#include <KickCommand.hpp>

KickCommand::KickCommand()
{

}
KickCommand::~KickCommand()
{

}

void    parseKickArgs(Client & client, const std::vector<std::string>& args)
{
    if (args.size() < 2)
        throw NotEnoughParametersException(client);

    std::string     chanName = args[0];
    std::string     nickname = args[1];
    
    if (!Server::getInstance().existChannel(chanName))
    throw NoSuchChannelException(client);
    if (!Server::getInstance().isUsedNickname(nickname))
    throw NoSuchNicknameException(client);
}

void    KickCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    //verif que client est bien operator (checkOperator de leny)
    parseKickArgs(client, args);

    std::string     chanName = args[0];
    std::string     nickname = args[1];

    Client  kicked = Server::getInstance().getClientByNickname(nickname);
    if (!Server::getInstance().isInChannel(kicked, chanName))
        throw UserNotInChannelException(client);

    Server::getInstance().kickChannelMember(client, kicked, chanName);
}