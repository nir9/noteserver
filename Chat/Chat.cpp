#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

void CheckForErrors(int info, char* error)
{
	if (info != 0) {
		printf("Failure: %s\n", error);
		WSACleanup(); // stop using winsock 2 dll
		ExitProcess(1);
	}
}

// Broadcast
void main()
{
	WSADATA wsData;
	int init = WSAStartup(MAKEWORD(2, 2), &wsData);
	CheckForErrors(init, "Init");
	
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (s == INVALID_SOCKET)
	{
		printf("Error:(\n");
		return;
	}

	BOOL setting = TRUE;
	// Setting up the socket for broadcast
	int options = setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&setting, sizeof(setting));
	CheckForErrors(options, "Socket Options");

	/* Go over the code from here */
	struct sockaddr_in sender_addr;
	sender_addr.sin_family = AF_INET;
	sender_addr.sin_port = htons(4728);
	//sender_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
	sender_addr.sin_addr.s_addr = InetPton(AF_INET, "255.255.255.255", 0);
	/* To here */

	int i = sendto(s, "asdasd", 6, 0, (sockaddr*)&sender_addr, sizeof(sender_addr));

	printf("Hey sup %d\n", i);


	

	getchar();
}