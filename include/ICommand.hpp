#pragma once

#include <string>
#include <Client.hpp>

class ICommand
{
    public:

        virtual         ~ICommand() {};
        virtual void    execCmd(Client & emitter, const std::string & arg) = 0;
};
