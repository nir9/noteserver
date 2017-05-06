/* Save referer option!! Also maybe move this eventually to linux for rpi */
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
#include <iostream>
#include "ManagedWinsock.h"
#include "ManagedSocket.h"
#include "Utils.h"

#pragma comment(lib, "Ws2_32.lib") // Indicate to the linker that Ws2_32.lib file is needed
using namespace std;

// read about constexpr
static const int BUF_LEN = 1024;
static const string PORT = "80";
static const string HEADER = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

string notes;


void HandleConnection(ManagedSocket& client);



void StartServer()
{
	const ManagedWinsock ws;

	ADDRINFOA hint;
	PADDRINFOA hostInfo;

	ZeroMemory(&hint, sizeof(ADDRINFOA));

	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	hint.ai_flags = AI_PASSIVE;

	int res = getaddrinfo(NULL, PORT.c_str(), &hint, &hostInfo);
	CheckForErrors(GENERAL_ERROR, res, "GetAddrInfo");

	// SOCKET rawSocket = socket(...)
	// auto managedSocket = ManagedSocket(rawSocket)
	// CR:The above
	ManagedSocket mServerSocket(INVALID_SOCKET);
	
	mServerSocket.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mServerSocket.socket == INVALID_SOCKET)
	{
		// CR: throw exception("Error") instead of printf and the return
		printf("Error:(\n");
		return;
	}
	
	// CR: Avoid doing complicated one-liners. bind and then in another line, check for errors
	// CR: Instead of CheckForErrors, wrapping each api function is better. Like we did with bind.
	//	That way. We can call the function without worring about error checking. Just like writing
	//	high level programming languages. So fun!
	CheckForErrors(GENERAL_ERROR, 
		bind(mServerSocket.socket, hostInfo->ai_addr, (int)hostInfo->ai_addrlen), "Bind Error");

	freeaddrinfo(hostInfo); // clean up

	// Now after all these lets start listening shall we
	if (listen(mServerSocket.socket, SOMAXCONN) == SOCKET_ERROR) {
		// CR: throw
		printf("Error Listening!\n");
		return;
	}

	cout << "Listening on port " << PORT << endl;

	// Accept connections
	while (1) {
		ManagedSocket client(INVALID_SOCKET);
		
		client.Accept(mServerSocket);
		
		// CR: Move this to a new thread. Try out std::thread :)
		HandleConnection(client);

		cout << "Got connection!" << endl;
	}
}

void HandleConnection(ManagedSocket& client)
{	
	vector<char> buffer(BUF_LEN);

	string recieved;
	int msg_len = 0;
	/*while(msg_len != 0)
	{*/
	
	msg_len = client.Recieve(buffer.data(), BUF_LEN);
	recieved.append(buffer.cbegin(), buffer.cend());
	cout << recieved << endl;

	string str(recieved.begin(), recieved.end());
	vector<string> splitted;
	char delimiter = ' ';
	Split(str, delimiter, splitted);
	
	if(splitted.size() > 2) {
		cout << splitted[1] << endl;
		string note = splitted[1];
		if (note.find("/?") == 0) {
			// its a note
			
			string whattoreplace = "/?";
			string withwhat = "";
			ReplaceByString(note, whattoreplace, withwhat);
			// CR: Consider using a global logger. Log("Note!"). ILogger for example
			cout << "Note!!" << endl;
			notes = notes + "<br/>" + note;
		}
	}

	// Send back
	string my_msg(HEADER);
	my_msg = my_msg + "<b align='center'>Welcome to the notes server!<br/><br/>" + notes + "</b>";
	client.Send(my_msg);
}

void main()
{
	try
	{
		StartServer();
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
}