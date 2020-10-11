#pragma once

#include "ClientSocket.h"

class CClient
{
public :

	CClient(CClientSocket& clientSocket) : m_clientSocket(clientSocket)
	{}

	void Init();
	void Start();
	void DeInit();
	void ReadConfig();
	void StartSendingDataBlocking();

private :
	bool m_wsaInitialized{};
	CClientSocket m_clientSocket;

	int m_addressFamily{};
	int m_type{};
	int m_protocol{};
	int m_portNumber{};
	std::string m_serverIp{};
};