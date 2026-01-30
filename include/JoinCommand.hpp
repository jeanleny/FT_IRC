#pragma once

#include <ICommand.hpp>
#include <Exception.hpp>
#include <Server.hpp>

class JoinCommand : public ICommand
{
	public :
		JoinCommand();
		~JoinCommand();
		void	execCmd(Client & emitter, const std::vector<std::string>& arg);
};
