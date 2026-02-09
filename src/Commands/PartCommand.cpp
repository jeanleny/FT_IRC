#include <PartCommand.hpp>


PartCommand::PartCommand()
{

}
PartCommand::~PartCommand()
{

}

void    PartCommand::execCmd(Client & emitter, const std::vector<std::string>& arg)
{
    (void) arg;
    (void) emitter;
}
