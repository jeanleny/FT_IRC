#pragma once
#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>

class InviteCommand : public ICommand
{
    
    public:

        InviteCommand();
        ~InviteCommand();
        
    private:

        void    execCmd(Client & emitter, const std::vector<std::string>& arg);
};