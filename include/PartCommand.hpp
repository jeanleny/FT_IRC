#pragma once

#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>



class PartCommand : public ICommand
{
    
    public:

        PartCommand();
        ~PartCommand();
        void    execCmd(Client & emitter, const std::vector<std::string>& arg);

    private:
};