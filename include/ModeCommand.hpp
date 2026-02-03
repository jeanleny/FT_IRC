#pragma once

#include <ICommand.hpp>
#include <Server.hpp>

class ModeCommand : public ICommand
{
	public :
		ModeCommand();
		~ModeCommand();
		void	execCmd(Client & emitter, const std::vector<std::string>& arg);
		void	modeCommand(Client &emitter, std::string chanName, std::string arg);
	private :
		
};
