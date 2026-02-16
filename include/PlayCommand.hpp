#pragma once
#include <ICommand.hpp>
#include <Server.hpp>
#include <Exception.hpp>

class PlayCommand : public ICommand
{
	public :
		PlayCommand();
		~PlayCommand();

	private :
		void	execCmd(Client &emitter, const std::vector<std::string> & arg);
};
