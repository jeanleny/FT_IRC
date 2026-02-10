#include <PartCommand.hpp>


PartCommand::PartCommand()
{

}
PartCommand::~PartCommand()
{

}

void    PartCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (args.size() > 1)
        throw CustomErrorException(client);
    if (args.size() == 0)
        throw NotEnoughParametersException(client);

    std::string chanName = args[0];

    if (!Server::getInstance().existChannel(chanName))
        throw NoSuchChannelException(client);

    if (!Server::getInstance().isInChannel(client, chanName))
        throw NotInThisChannelException(client);

    Server::getInstance().removeChannelMember(client, chanName);
}
