#pragma once

#include <winsock2.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

const int GENERAL_ERROR = 0;
const int SOCKET_ERR = 1;
void CheckForErrors(int errorType, int result, std::string log);
void Split(std::string& str, char delimiter, std::vector<std::string>& splitted);
void ReplaceByString(std::string& str, std::string& findstr, std::string& replacement);