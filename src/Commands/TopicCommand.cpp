#include <TopicCommand.hpp>

TopicCommand::TopicCommand()
{

}
TopicCommand::~TopicCommand()
{

}


void    parseTopicArgs(Client & client, std::vector<std::string> args)
{
    if (args.size() < 1)
        throw NotEnoughParametersException(client);

    if (!Server::getInstance().existChannel(args[0]))
        throw NoSuchChannelException(client);
}

void    TopicCommand::execCmd(Client & client, const std::vector<std::string>& args)
{
    parseTopicArgs(client, args);

    std::string chanName = args[0];
    if (!Server::getInstance().isInChannel(client, chanName))
        throw UserNotInChannelException(client);

    if (args.size() == 1) // --> DISPLAY TOPIC
        Server::getInstance().displayChannelTopic(client, chanName);
    else // --> CHANGE TOPIC
    {
        if(Server::getInstance().checkChannelMode(chanName, t, true) 
            && !Server::getInstance().checkChannelOperator(chanName, client))
            throw NotAnOperatorException(client);

        std::string newTopic = args[1];
        if (isEmptyCommand(newTopic))
            newTopic = "Topic is not set";
        Server::getInstance().changeChannelTopic(client, chanName, newTopic);
    }
}