#include "ManagedWinsock.h"
#include <winsock2.h>
#include <exception>
#include <iostream>
#include <string>
#include "Utils.h"

#pragma comment(lib, "Ws2_32.lib") // Indicate to the linker that Ws2_32.lib file is needed

using namespace std;

ManagedWinsock::ManagedWinsock()
{
	WSADATA wsData;
	std::cout << "Initializing Winsock" << std::endl;
	int result = WSAStartup(MAKEWORD(2, 2), &wsData);
	CheckForErrors(GENERAL_ERROR, result, "Failed to initialze Winsock :(");
}

ManagedWinsock::~ManagedWinsock()
{

	std::cout << "Calling WSACleanup" << std::endl;
	int result = WSACleanup();
	CheckForErrors(GENERAL_ERROR, result, "Falied to terminate use of Winsock :(");
}