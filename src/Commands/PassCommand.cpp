#include "PassCommand.hpp"

PassCommand::PassCommand()
{

}
PassCommand::~PassCommand()
{

}

void    PassCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (client.getRegisterStatus() == REGISTERED)
        throw AlreadyRegisteredException();
    if (args.size() == 0 || args.size() > 1)
        throw WrongCommandException();

    std::string pass = args[0];
    if (Server::getInstance().validPassword(pass) == true)
        client.setRegisterStatus(USER_STATUS);

    //else
    //  send "Invalid Password", return

}