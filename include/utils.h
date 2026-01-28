#pragma once
#include <Server.hpp>


std::vector<std::string>	split(const std::string & str);
bool						isRegisterCommand(ssize_t cmdId);
void						displayClients(std::vector<Client> _clients);
void	                    displayCommand(Client & client);
void						eraseTrailingSpaces(std::string &str);
bool						isEmptyCommand(std::string str);
void						sendException(int fd ,const std::exception &e);
bool 						isOneArg(std::string str);
