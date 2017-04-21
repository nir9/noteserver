#include "ManagedSocket.h"
#include <iostream>
#include <string>
#include "Utils.h"

using namespace std;
ManagedSocket::ManagedSocket()
{
}

// if the socket has been create outside
ManagedSocket::ManagedSocket(SOCKET socket)
{
	this->socket = socket;
}


void ManagedSocket::Send(std::string buffer)
{
	int result = send(this->socket, buffer.c_str(), buffer.length(), 0);
	CheckForErrors(SOCKET_ERR, result, "Sending Error"); // Perhaps get last error..
	if (debugLevel >= 1) {
		cout << "Sent " << result << endl;
	}
}

// Note for future: upgrade to let it get list and recieve ALL
int ManagedSocket::Recieve(char* buffer, int bufferLen)
{
	int result = recv(this->socket, buffer, bufferLen, 0);

	CheckForErrors(SOCKET_ERR, result, "Recieving Error");
	if (result == 0 && debugLevel >= 1) {
		// Connection closed
		cout << "Connection closed!" << endl;
	}
	if (debugLevel >= 1) {
		cout << "Recieved " << result << " bytes" << endl;
	}
	if (debugLevel >= 2) {
		cout << "Message Received: " << buffer << endl;
	}
	return result;
}

void ManagedSocket::Accept(ManagedSocket& listeningSocket)
{
	this->socket = accept(listeningSocket.socket, 0, 0);
	if (this->socket == INVALID_SOCKET) {
		CheckForErrors(SOCKET_ERR, this->socket, "Accept Problem");
	}
}



ManagedSocket::~ManagedSocket()
{
	// This disables sending perhaps move elsewhere to be more logical..
	CheckForErrors(GENERAL_ERROR, shutdown(this->socket, SD_SEND), "Shutdown socket error");

	CheckForErrors(GENERAL_ERROR, closesocket(this->socket), "Close socket error");
}
