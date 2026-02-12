#pragma once
#include <Server.hpp>


std::vector<std::string>	split(const std::string & str);
void						displayClients(std::vector<Client> _clients);
void	                    displayCommand(Client & client);
void	                    displayMemberList(Channel & channel);
void						eraseTrailingSpaces(std::string &str);
void						uppercaseStr(std::string &str);
bool						isEmptyCommand(std::string str);
bool                        isvalidNickname(std::string nickname);
void						sendException(int fd ,const std::exception &e);
bool 						isOneArg(std::string str);
bool						checkPrefix(std::string channelName);
bool						strIsDigit(std::string str);
bool	                    isCtrlD(char *buf);
