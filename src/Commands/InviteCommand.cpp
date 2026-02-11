#include <InviteCommand.hpp>

InviteCommand::InviteCommand()
{

}
InviteCommand::~InviteCommand()
{

}

void    parseInviteArgs(Client & client, const std::vector<std::string>& args)
{
    if (args.size() < 2)
        throw NotEnoughParametersException(client);

    if (!Server::getInstance().isUsedNickname(args[0]))
        throw NoSuchNicknameException(client);
    if (!Server::getInstance().existChannel(args[1]))
        throw NoSuchChannelException(client);
}

void    InviteCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    parseInviteArgs(client, args);

    std::string     nickname = args[0];
    std::string     chanName = args[1];

    if (!Server::getInstance().isInChannel(client, chanName))
        throw NotInThisChannelException(client);

    if(!Server::getInstance().checkChannelOperator(chanName, client))
        throw NotAnOperatorException(client);

    Client  invited = Server::getInstance().getClientByNickname(nickname);
    if(Server::getInstance().isInChannel(invited, chanName))
       throw AlreadyInChannelException(client);

    Server::getInstance().inviteChannelMember(client, invited, chanName);
}