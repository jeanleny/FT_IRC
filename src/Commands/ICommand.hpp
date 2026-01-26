#pragma once

#include <string>
#include "../Client/Client.hpp"

class ICommand
{
    public:

        virtual void    execCmd(Client & emitter, std::string arg) = 0;
};