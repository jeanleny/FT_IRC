#pragma once
#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>



class PrivmsgCommand : public ICommand
{
    
    public:

        PrivmsgCommand();
        ~PrivmsgCommand();
        void    execCmd(Client & emitter, const std::vector<std::string>& arg);

    private:
};