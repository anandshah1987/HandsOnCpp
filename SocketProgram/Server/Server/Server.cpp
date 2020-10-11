//#include <WinSock2.h>
//#include <WS2tcpip.h>
#include<iostream>
#include "ServerSocket.h"
#include "Service.h"

#pragma comment (lib, "Ws2_32.lib")

/*
1. https://tangentsoft.net/wskfaq/advanced.html#backlog
2. https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzab6/xacceptboth.htm
*/

/*
Improvement Todo :
***1. Object oriented
***2. Multithreaded
***3. Configurable using INI file
4. Portable
5. Make it IPV6 complient
***6. Add proper error condition so that actual error codes from socket failures call can be returned
7. All classes should be non copyable
***8. Create .cpp file for CBaseSocket
9. Currently only reading 1023 bytes of data. It should be possible to read all the data that client sends.
*/

int main()
{
	try
	{
		CServerSocket listeningSocket;
		CWinService winService(listeningSocket);
		CServiceBase& service = winService;
		service.Init();
		service.Start();
		service.ServerLoop();
		service.DeInit();
	}
	catch (const std::system_error& ex)
	{
		std::cout << "Failed to run server .. error code [" << ex.code() 
					<< "] error message " << ex.what() << '\n';
	}
	catch(const std::exception& ex)
	{
		std::cout << "Failed to run server .. error message -> " << ex.what() << '\n';
	}
	/*WSADATA wsData{};
	WORD version = MAKEWORD(2,2);

	auto ret = WSAStartup(version, &wsData);
	if (ret != FALSE)
	{
		std::cout << "Failed to create win socket api\n";
		return ret;
	}*/

	/*SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == listeningSocket)
	{
		std::cout << "Failed to create socket \n";
		WSACleanup();
		return -1;
	}

	sockaddr_in socketAddr{};
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(PORT_NUMBER);
	socketAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	ret = bind(listeningSocket, reinterpret_cast<sockaddr*>(&socketAddr), sizeof(socketAddr));
	if (ret == SOCKET_ERROR)
	{
		std::cout << "Failed to bind socket to address\n";
		return WSAGetLastError();
	}

	ret = listen(listeningSocket, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		std::cout << "Failed to bind socket to address\n";
		return WSAGetLastError();
	}

	std::cout << "Server is ready for accepting new connections ...\n";

	sockaddr_in clientAddr{};
	int sizeOfclientAddr = sizeof(clientAddr);
	SOCKET clientSocket = accept(listeningSocket, reinterpret_cast<sockaddr *>(&clientAddr), &sizeOfclientAddr);
	if (INVALID_SOCKET == clientSocket)
	{
		std::cout << "Accept failed \n";
		return WSAGetLastError();
	}

	char clientName[NI_MAXHOST]{};
	char clientPort[NI_MAXSERV]{};
	if (0 == getnameinfo(reinterpret_cast<sockaddr*>(&clientAddr), sizeOfclientAddr, clientName, NI_MAXHOST,
		clientPort, NI_MAXSERV, 0))
	{
		std::cout << clientName << " connected on port " << clientPort << '\n';
	}
	else
	{
		inet_ntop(AF_INET, &clientAddr, clientName, NI_MAXHOST);
		std::cout << clientName << " connected on port " << ntohs(clientAddr.sin_port) << '\n';
	}

	closesocket(listeningSocket);

	char buffer[DATA_SIZE_TO_READ]{};

	while (true)
	{
		auto bytesRead = recv(clientSocket, buffer, DATA_SIZE_TO_READ, 0);
		if (SOCKET_ERROR == bytesRead)
		{
			std::cout << "Failed to read data from client .. closing \n";
			break;
		}

		if (0 == bytesRead)
		{
			std::cout << "Failed to read data from client .. closing \n";
			break;
		}

		buffer[bytesRead + 1] = '\0';

		std::cout << "Received ..." << buffer << '\n';
	}

	closesocket(clientSocket);

	WSACleanup();*/
}