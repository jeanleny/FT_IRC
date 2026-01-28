#pragma once
#include <Server.hpp>


std::vector<std::string>	split(const std::string & str);
void						displayClients(std::vector<Client> _clients);
void	                    displayCommand(Client & client);
void						eraseTrailingSpaces(std::string &str);
bool						isEmptyCommand(std::string str);
bool                        isvalidNickname(std::string nickname);
