#include <WS2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT_NUMBER	7500
#define BUFFER_SIZE 4096

int main()
{
	WSADATA wsaData{};
	WORD version = MAKEWORD(2,2);
	auto ret = WSAStartup(version, &wsaData);
	if (FALSE != ret)
	{
		std::cout << "Failed to initialise winsocket api \n";
		WSACleanup();
		return -1;
	}

	SOCKET soc = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == soc)
	{
		std::cout << "Failed to create client socket \n";
		WSACleanup();
		return -1;
	}

	sockaddr_in serverAddrs{};
	serverAddrs.sin_family = AF_INET;
	serverAddrs.sin_port = htons(SERVER_PORT_NUMBER);
	inet_pton(AF_INET, SERVER_IP_ADDRESS, &serverAddrs.sin_addr);

	ret = connect(soc, reinterpret_cast<sockaddr*>(&serverAddrs), sizeof(serverAddrs));
	if (SOCKET_ERROR == ret)
	{
		std::cout << "Failed to connect to server \n";
		//WSACleanup();
		auto val =  WSAGetLastError();
		return val;
	}


	//char buffer[BUFFER_SIZE];
	std::string userInput;

	do
	{
		std::cout << "Please enter the string to send to serevr .. . \n";

		std::getline(std::cin, userInput);
		auto bytesSent = send(soc, userInput.c_str(), userInput.size()+1, 0);
		if (SOCKET_ERROR == bytesSent || 0 == bytesSent)
		{
			std::cout << "Error in sending data to server \n";
			WSACleanup();
			return WSAGetLastError();
		}

	} while (userInput.size() > 0);

	closesocket(soc);
	WSACleanup();
}