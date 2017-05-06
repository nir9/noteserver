#pragma once

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

class ManagedSocket {
public:
	// CR:Members should be private
	SOCKET socket;
	int debugLevel = 1;
	ManagedSocket();
	ManagedSocket(SOCKET);
	/**/
	void Send(std::string buffer);
	int Recieve(char* buffer, int bufferLen);
	void Accept(ManagedSocket& listeningSocket);
	/**/
	~ManagedSocket();

};