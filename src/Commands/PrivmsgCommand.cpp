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
          throw WrongCommandException();
     
     if (args.size() == 0)
          throw NoRecipientException(client);

     if (args.size() == 1)
          throw NoTextToSendException(client);

     std::string     target = args[0];
     std::string     text = args[1];

     if (target[0] == '#')
     {
          if (!Server::getInstance().existChannel(target))
               throw AddrinfoFailedException(); //403 - No such Channel
     }
     else
     {
          if (!Server::getInstance().isUsedNickname(target))
               throw NoSuchNicknameException(client);
     }
}

void    PrivmsgCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
     //PRIVMSG #channel :text
    (void)client;

    parseArgs(client, args);
    std::string     target = args[0];
    std::string     text = args[1];

}