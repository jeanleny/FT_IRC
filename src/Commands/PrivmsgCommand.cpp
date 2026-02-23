#include <PrivmsgCommand.hpp>

PrivmsgCommand::PrivmsgCommand()
{

}
PrivmsgCommand::~PrivmsgCommand()
{

}

void parsePrivmsgArgs(Client & client, const std::vector<std::string>& args)
{
     if (args.size() < 2)
          throw NotEnoughParametersException(client);
     std::string     target = args[0];
     std::string     text = args[1];

     if (target[0] == '#')
     {
          if (!Server::getInstance().existChannel(target))
               throw NoSuchChannelException(client);
          else if (!Server::getInstance().isInChannel(client, target))
               throw CannotSendToChannelException(client);
     }
     else
     {
          if (!Server::getInstance().isUsedNickname(target))
               throw NoSuchNicknameException(client);
     }
}

void    PrivmsgCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    parsePrivmsgArgs(client, args);
    std::string     target = args[0];
    std::string     text = args[1];

     if (Server::getInstance().isGameChannel(target) && text[0]== '*')
          target = "Master";

     std::string     message = ":" + client.getNickname() + "!" + client.getUsername() + "@" + Server::getInstance().getHostname()
          + " PRIVMSG " + target + " :" + text + "\r\n";

     const char     *msg = message.c_str();
     int            len = strlen(msg);

     if (target[0] == '#')
     {
          Server::getInstance().sendMessageToChannel(client, target, msg);
     }
     else
     {
          Client    receiver = Server::getInstance().getClientByNickname(target);
          send(receiver.getClientFd(), msg, len, MSG_NOSIGNAL);
     }
}
