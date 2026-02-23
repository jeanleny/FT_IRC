#include <PassCommand.hpp>

PassCommand::PassCommand()
{

}
PassCommand::~PassCommand()
{

}

void    PassCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (client.getRegisterStatus() == REGISTERED)
        throw AlreadyRegisteredException(client);
    if (args.size() == 0)
        throw NotEnoughParametersException(client);

    std::string pass = args[0];
    if (!Server::getInstance().validPassword(pass))
        throw PasswordMismatchException(client);
    client.setRegisterStatus(NICK_STATUS);
    Server::getInstance().sendNickQuery(client);
}
