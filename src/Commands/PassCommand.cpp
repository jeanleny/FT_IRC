#include "PassCommand.hpp"

PassCommand::PassCommand()
{

}
PassCommand::~PassCommand()
{

}

int     PassCommand::parseArg(const std::string & arg) const
{
    (void)arg;
    return 0;
}

void    PassCommand::execCmd(Client & emitter, const std::string & arg)
{
    if (parseArg(arg) == -1)
        throw WrongCommandException();
    if (emitter.getRegisterStatus() == REGISTERED)
        throw AlreadyRegisteredException();

    if (Server::getInstance().validPassword(arg) == true)
        emitter.setRegisterStatus(USER_STATUS);
    //else
    //  send "Invalid Password", return

}