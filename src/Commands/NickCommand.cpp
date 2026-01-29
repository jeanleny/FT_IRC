#include <NickCommand.hpp>

/*TO-DO

- [OK] Parsing : 9 caractères, 1er char : pas de chiffres. Reste : lettres, chiffres, caractères spéciaux (- [ ] \ ` ^ { }) (ERR_ERRONEUSNICKNAME)
- [OK] During registration, set the nickname :
        - [OK] si il n'est pas deja utilisé (ERR_NICKNAMEINUSE (433))
        -->si validé, send : :WiZ!jto@tolsun.oulu.fi NICK Kilroy
        -->envoie le message de welcome
- After registration, remplace le nickname si il est différent et pas deja utilisé ERR_NICKNAMEINUSE (433)
    + send un message a tous les clients du channel pour avertir du changement de nickname
*/


NickCommand::NickCommand()
{

}
NickCommand::~NickCommand()
{

}

int     NickCommand::parseNickname(const std::string & nickname)
{
    if (nickname.size() < 1 || nickname.size() > 9)
        return -1;
    if (isdigit(nickname[0]) || !isvalidNickname(nickname))
        return -1;
    return 0;
}


void    NickCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (client.getRegisterStatus() == PASS_STATUS)
        throw PasswordQueryException();
    if (client.getRegisterStatus() == USER_STATUS)
        throw UsernameQueryException();
    if (args.size() == 0)
        throw MissingArgumentsException();
    if (args.size() > 1)
        throw WrongCommandException();
        
    const std::string nickname = args[0];
    if (parseNickname(nickname) == -1)
        throw ErroneusNicknameException();
    if (Server::getInstance().isUsedNickname(nickname))
        throw UsedNicknameException();
    if (client.getRegisterStatus() == NICK_STATUS)
    {
        client.setNickname(nickname);
        client.setRegisterStatus(REGISTERED);
        // ++ message de welcome;
    }
    // ++ NICK command after registration 
    // if (client.getRegisterStatus() == REGISTERED)
    // {
    //     client.setNickname(nickname);
    //     std::string msg = ":" + client.getNickname() + "!" + client.getUsername() + "@"
    //             + Server::getInstance().getHostname() + "NICK" + nickname;
    //     std::cout << msg << std::endl;
    //     send(client.getClientFd(), msg.c_str(), msg.size(), 0);
    // }
}