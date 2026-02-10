#pragma once
#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>



class UserCommand : public ICommand
{
    
    public:

        UserCommand();
        ~UserCommand();
        
        void    execCmd(Client & client, const std::vector<std::string>& arg);

    private:
};