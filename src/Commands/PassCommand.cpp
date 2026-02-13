#include <PassCommand.hpp>

PassCommand::PassCommand()
{

}
PassCommand::~PassCommand()
{

}

void    PassCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (client.getRegisterStatus() == USER_STATUS || client.getRegisterStatus() == NICK_STATUS)
        throw CustomErrorException(client);
    if (client.getRegisterStatus() == REGISTERED)
        throw AlreadyRegisteredException(client);
    if (args.size() == 0)
        throw NotEnoughParametersException(client);

    std::string pass = args[0];
    if (!Server::getInstance().validPassword(pass))
        throw PasswordMismatchException(client);
    client.setRegisterStatus(USER_STATUS);
}
