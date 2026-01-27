#pragma once
#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>



class PassCommand : public ICommand
{
    
    public:

        PassCommand();
        ~PassCommand();
        void    execCmd(Client & emitter, const std::vector<std::string>& arg);

    private:

        int     parseArg(const std::string & arg) const;

};
