#include <UserCommand.hpp>

UserCommand::UserCommand()
{

}
UserCommand::~UserCommand()
{

}

bool     UserCommand::validUsername(const std::string & username) const
{
    if (username.size() < 1 || username.size() > 9)
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

    const std::string username = args[0];
    if (!validUsername(username))
        throw CustomErrorException(client);
    client.setUsername(username);
    client.setRegisterStatus(NICK_STATUS);
}
