#pragma once
#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>



class NickCommand : public ICommand
{
    
    public:

        NickCommand();
        ~NickCommand();
        
        void    execCmd(Client & emitter, const std::vector<std::string>& arg);

    private:
};