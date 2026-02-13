#pragma once
#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>



class TopicCommand : public ICommand
{
    
    public:

        TopicCommand();
        ~TopicCommand();
        
    private:
    
        void    execCmd(Client & emitter, const std::vector<std::string>& arg);
};