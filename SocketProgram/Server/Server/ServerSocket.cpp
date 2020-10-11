#include "ServerSocket.h"


void CServerSocket::Create()
{
	CBaseSocket::Create();
}

void CServerSocket::Bind()
{
	sockaddr_in socketAddr{};
	socketAddr.sin_family = GetAddressFamily();
	socketAddr.sin_port = htons(GetPortNumber());
	// todo : this should be configured from outside (at least for IPV6).
	socketAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == (bind(GetSocket(), reinterpret_cast<sockaddr*>(&socketAddr), sizeof(sockaddr_in))))
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to bind socket.");
	}
}

void CServerSocket::Listen()
{
	if (SOCKET_ERROR == (listen(GetSocket(), GetBacklogSize())))
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to listen on socket.");
	}
}

ServerBaseSocketPtr CServerSocket::Accept()
{
	sockaddr_in clientAddr{};
	int sizeOfclientAddr=sizeof(clientAddr);
	auto soc = accept(GetSocket(), reinterpret_cast<sockaddr*>(&clientAddr), &sizeOfclientAddr);
	if (INVALID_SOCKET == soc)
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to create client socket.");
	}
	int clientPort = ntohs(clientAddr.sin_port);
	// We could use clientAddr details but it's ok
	char clientName[NI_MAXHOST]{};
	inet_ntop(GetAddressFamily(), &(clientAddr.sin_addr), clientName, NI_MAXHOST);
	ServerBaseSocketPtr clientSocket = new CServerSocket(clientPort, GetAddressFamily(), GetType(), GetProtocol(),
		GetBacklogSize());
	clientSocket->SetSocket(soc);
	clientSocket->SetIpAddress(clientName);
	return clientSocket;
}

int CServerSocket::Recv(char* data, int bytesToRead)
{
	auto bytesRead = recv(GetSocket(), data, bytesToRead, 0);
	if (SOCKET_ERROR == bytesRead || 0 == bytesRead)
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to read data from client ...");
	}
	return bytesRead;
}