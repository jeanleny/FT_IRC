#include <UserCommand.hpp>

UserCommand::UserCommand()
{

}
UserCommand::~UserCommand()
{

}

bool     validUsername(const std::vector<std::string>& args)
{
    if (args.size() > 1 || args[0].size() < 1 || args[0].size() > 9)
        return false;
    return true;
}

void    UserCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (client.getRegisterStatus() == PASS_STATUS)
        throw CustomErrorException(client);
    if (client.getRegisterStatus() == NICK_STATUS)
        throw CustomErrorException(client);
    if (client.getRegisterStatus() == REGISTERED)
        throw AlreadyRegisteredException(client);
    if (args.size() == 0)
        throw NotEnoughParametersException(client);

    if (!validUsername(args))
        throw CustomErrorException(client);
    const std::string username = args[0];
    client.setUsername(username);
    client.setRegisterStatus(NICK_STATUS);
}
