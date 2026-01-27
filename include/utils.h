#pragma once
#include <Server.hpp>


std::vector<std::string>	split(const std::string & str);
bool						isRegisterCommand(ssize_t cmdId);
void						displayClients(std::vector<Client> _clients);
