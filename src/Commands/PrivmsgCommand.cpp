#include <PrivmsgCommand.hpp>

/*TODO PRIVMG <std::string target> <std::target text>:

Parsing général : 

- text vide --> err. no text
- target vide --> err. no destinataire
- text trop long --> refuser ou tronquer

1. PRIVMG #channel <text> : envoie un message general sur le channel

Attendu : message relayé a tous les membres du canal (sauf a l'expediteur ?)

Erreurs :   - si le canal n'existe pas
            - si le client n'est pas dans le canal
            - si le client est restreint
            - si le canal est en mode modéré

2. PRIVMG #nickname <text> : envoie un message prive a l'utilisateur

Attendu : message relayé a l'utilisateur cible

Erreurs :   - si le client cible n'existe pas / pas authentifié
            - pour un message a soi meme
            - si le client cible n'est pas connecte ?

*/


PrivmsgCommand::PrivmsgCommand()
{

}
PrivmsgCommand::~PrivmsgCommand()
{

}

void parseArgs(Client & client, const std::vector<std::string>& args)
{
     if (args.size() > 2)
          throw WrongCommandException(); // *!* modifier le split
     
     if (args.size() < 2)
          throw NotEnoughParametersException(client);

     std::string     target = args[0];
     std::string     text = args[1];

     if (target[0] == '#')
     {
          if (!Server::getInstance().existChannel(target))
               throw NoSuchChannelException(client);
          else if (!Server::getInstance().isInChannel(client, target))
               throw AddrinfoFailedException(); //Not a member of this channel (a faire) 404 ERR_CANNOTSENDTOCHAN
     }
     else
     {
          if (!Server::getInstance().isUsedNickname(target))
               throw NoSuchNicknameException(client); //401
     }
}

void    PrivmsgCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    parseArgs(client, args);
    std::string     target = args[0];
    std::string     text = args[1];
    std::string     message = ":" + client.getNickname() + "!" + client.getUsername() + "@" + Server::getInstance().getHostname()
          + " PRIVMSG " + target + " " + text + "\r\n";
     const char     *msg = message.c_str();
     int            len = strlen(msg);

     if (target[0] == '#')
          Server::getInstance().sendMessageToChannel(target, msg);
     else
     {
          Client    receiver = Server::getInstance().getClientByNickname(target);
          send(receiver.getClientFd(), msg, len, 0);
     }
}
