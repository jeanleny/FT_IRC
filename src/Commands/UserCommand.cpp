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
        throw PasswordQueryException();
    if (client.getRegisterStatus() == NICK_STATUS)
        throw NicknameQueryException();
    if (client.getRegisterStatus() == REGISTERED)
        throw AlreadyRegisteredException();
    if (args.size() == 0)
        throw MissingArgumentsException();
    if (args.size() > 1)
        throw WrongCommandException();

    const std::string username = args[0];
    if (!validUsername(username))
        throw ErroneusUsernameException();
    client.setUsername(username);
    client.setRegisterStatus(NICK_STATUS);
}
