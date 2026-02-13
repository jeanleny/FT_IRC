#pragma once
#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>



class PrivmsgCommand : public ICommand
{
    
    public:

        PrivmsgCommand();
        ~PrivmsgCommand();
        
    private:
    
        void    execCmd(Client & emitter, const std::vector<std::string>& arg);
};