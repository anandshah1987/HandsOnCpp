#include "ClientSocket.h"
#include <iostream>



void CClientSocket::Init(const int portNumber, const int addressFamily, const int socketType,
	const int protocol, const std::string& serverIp)
{
	m_serverIp = serverIp;
	CBaseSocket::Init(portNumber, addressFamily, socketType, protocol, 0);
}


void CClientSocket::Connect()
{
	std::cout << "Connecting to server on " << m_serverIp << "::" << GetPortNumber() << "... \n";

	sockaddr_in serverAddrs{};
	serverAddrs.sin_family = GetAddressFamily();
	serverAddrs.sin_port = htons(GetPortNumber());
	inet_pton(GetAddressFamily(), m_serverIp.c_str(), &serverAddrs.sin_addr);

	auto ret = connect(GetSocket(), reinterpret_cast<sockaddr*>(&serverAddrs), sizeof(serverAddrs));
	if (SOCKET_ERROR == ret)
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to connect to server.");
	}
}

void CClientSocket::SendBlocking()
{
	std::string userInput;
	do
	{
		std::cout << "Please enter the string to send to server ... \n";
		std::cout << "Enter STOP to stop and disconnect client \n";

		std::getline(std::cin, userInput);
		auto bytesSent = send(GetSocket(), userInput.c_str(), userInput.size() + 1, 0);
		if (SOCKET_ERROR == bytesSent || 0 == bytesSent)
		{
			throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Error in sending data to server.");;
		}

	} while (userInput != "STOP");
}
