#include <winsock2.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

void CheckForErrors(int errorType, int result, std::string log)
{
	BOOL error = FALSE;
	if (errorType == GENERAL_ERROR && result != 0) {
		error = TRUE;
	}

	else if (errorType == SOCKET_ERR && result == SOCKET_ERROR) {
		error = TRUE;
	}

	else if (errorType == SOCKET_ERR && result == INVALID_SOCKET) {
		error = TRUE;
	}

	if(error) {
		throw std::exception(log.c_str());
	}
}

void Split(string& str, char delimiter, vector<string>& splitted) {
	size_t pos = 0, found_pos;
	

	while (pos <= str.size()) {
		if ((found_pos=str.find_first_of(delimiter, pos)) != string::npos) {
			//cout << "found a match! " << endl;
			splitted.push_back(str.substr(pos, found_pos-pos));
			pos = found_pos + 1;
		}
		else {
			break;
		}
	}
}

void ReplaceByString(std::string& str, std::string& findstr, std::string& replacement)
{
	size_t pos = str.find(findstr);
	if (pos == string::npos) {
		cout << "Can't replace.." << endl;
		return;
	}

 
	str.replace(pos, findstr.size(), replacement);
}
