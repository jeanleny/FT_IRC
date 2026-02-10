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

void    defineNickname(Client & client, const std::string & nickname)
{
    client.setNickname(nickname);
    if (client.getRegisterStatus() == NICK_STATUS)
    {
        client.setRegisterStatus(REGISTERED);
        Server::getInstance().sendWelcomeMessage(client);
    }
    else // Nick Command typed after registration
        Server::getInstance().sendNickMessage(client);
}


void    NickCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    if (client.getRegisterStatus() == PASS_STATUS)
        throw CustomErrorException(client);
    if (client.getRegisterStatus() == USER_STATUS)
        throw CustomErrorException(client);
    if (args.size() == 0)
        throw NotEnoughParametersException(client);
        
    const std::string nickname = args[0];
    if (parseNickname(nickname) == -1)
        throw ErroneusNicknameException(client);
    if (Server::getInstance().isUsedNickname(nickname))
        throw UsedNicknameException(client);
    defineNickname(client, nickname);
}
