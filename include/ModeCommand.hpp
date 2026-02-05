#pragma once

#include <ICommand.hpp>
#include <Server.hpp>

class ModeCommand : public ICommand
{
	public :
		ModeCommand();
		~ModeCommand();
		void	execCmd(Client & emitter, const std::vector<std::string>& arg);
		void	modeCommand(Client &emitter);
		void	addFlags(Client emitter, std::string arg);
		void	initMode(Client emitter, std::vector<std::string> arg);
		void	modeParam(Client emitter);
		void	addSendArgs();
		void	sendModeMessage(Client client);
		bool	manageParamMode(char flag, Client client);
		bool	manageLimitMode(Client client);
		bool	manageOpMode(Client client);
		bool	manageKeyMode();
		bool	presentClient(Client client, Client target);

	private :
		std::vector<std::string>	_paramArg;
		std::string					_flags;
		std::string					_param;
		std::string					_sign;
		std::string					_chanName;
		std::string					_sendArgs;
		size_t						_mode;
		size_t						_id;
		bool						_disable;
		
};
