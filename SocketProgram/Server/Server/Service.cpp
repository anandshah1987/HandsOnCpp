#include "Service.h"
#include <iostream>
#include <thread>
#include <vector>

//https://www.tenouk.com/Module41.html

#define BYTES_TO_READ 1023

#define INI_FILE_NAME ".\\server.ini"


void CServiceBase::ReadConfig()
{
	std::cout << "Reading base service config ...\n";

	m_addressFamily=GetPrivateProfileIntA(INI_CONFIG_SECTION, "AddressFamily", AF_INET, INI_FILE_NAME);
	m_type = GetPrivateProfileIntA(INI_CONFIG_SECTION, "SocketType", SOCK_STREAM, INI_FILE_NAME);
	m_portNumber = GetPrivateProfileIntA(INI_CONFIG_SECTION, "Port", DEFAULT_SERVER_PORT, INI_FILE_NAME);
	m_protocol = GetPrivateProfileIntA(INI_CONFIG_SECTION, "Protocol", DEFAULT_SOCKET_PROTOCOL, INI_FILE_NAME);
	m_backLogSiz = GetPrivateProfileIntA(INI_CONFIG_SECTION, "BacklogSize", SOMAXCONN, INI_FILE_NAME);

	std::cout << "=========== Server configuration start ========= \n";
	std::cout << "AddressFamily = " << m_addressFamily << '\n';
	std::cout << "SocketType = " << m_type << '\n';
	std::cout << "Port = " << m_portNumber << '\n';
	std::cout << "Protocol = " << m_protocol << '\n';
	std::cout << "BacklogSize = " << m_backLogSiz << '\n';
	std::cout << "=========== Server configuration ends ========= \n";

}

void CServiceBase::Init()
{
	ReadConfig();
	m_listeningSocket.Init(m_portNumber, m_addressFamily, m_type, m_protocol, m_backLogSiz);
}



void CWinService::Init()
{
	std::cout << "Initializing windows server ...\n";

	WORD version = MAKEWORD(2,2);
	WSADATA data{};
	auto ret = WSAStartup(version, &data);
	if (FALSE != ret)
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to initialize winsocket api module. \n");
	}

	CServiceBase::Init();
}

void CWinService::ReadConfig()
{
	std::cout << "Reading service config ...\n";

	CServiceBase::ReadConfig();
}

void CWinService::Start()
{
	std::cout << "Starting windows server ...\n";

	m_listeningSocket.Create();
	m_listeningSocket.Bind();
	m_listeningSocket.Listen();

	// Start connection monitor thread
	StartConnectionMonitor();
}


void CWinService::DeInit()
{
	std::cout << "De-Initializing windows server ...\n";

	closesocket(m_listeningSocket.GetSocket());
	
	auto ret = WSACleanup();
	if (FALSE != ret)
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to de-initialize winsocket api module. \n");
	}
	m_wsaCleanUpDone = true;
}

void CWinService::StartConnectionMonitor()
{
	std::thread  monitor(&CWinService::ConnectionMonitorThread, this);
	// todo : should not detach instead join in main
	monitor.detach();
}

void CWinService::ConnectionMonitorThread()
{
	std::cout << "Started to monitor listening socket for new connections ... \n";
	fd_set masterReadSet;
	std::vector<ServerBaseSocketPtr> socketList{};

	// todo : handle termination of this loop
	while (true)
	{
		FD_ZERO(&masterReadSet);
		FD_SET(m_listeningSocket.GetSocket(), &masterReadSet);
		for (const auto& socket : socketList)
		{
			FD_SET(socket->GetSocket(), &masterReadSet);
		}

		auto noOfSockets = select(0, &masterReadSet, nullptr, nullptr, nullptr);
		for (int sockCount=0; sockCount < noOfSockets; sockCount++)
		{
			SOCKET sock = masterReadSet.fd_array[sockCount];
			if (sock == m_listeningSocket.GetSocket())
			{
				// Accept New connection
				auto clientSocket = m_listeningSocket.Accept();
				socketList.emplace_back(clientSocket);
				std::cout << "Received connection request from " << clientSocket->GetIpAddress() << "." << clientSocket->GetPortNumber() << '\n';
			}
			else
			{
				for (const auto& clientSocket : socketList)
				{
					if (sock == clientSocket->GetSocket())
					{
						// Launch new thread for processing client request
						std::thread requestThread(&CWinService::RequestProcessingThread, this, clientSocket);
						requestThread.detach();
					}
				}
			}
		}
	}
}

void CWinService::RequestProcessingThread(ServerBaseSocketPtr clientSocket)
{
	std::cout << "Received data from " << clientSocket->GetIpAddress() << "." << clientSocket->GetPortNumber() << '\n';

	char data[BYTES_TO_READ]{};
	auto bytesRead = clientSocket->Recv(data, BYTES_TO_READ);
	//data[bytesRead + 1] = '\0';

	std::cout << "Received --->>>> [" << data << "] \n";
	//closesocket(clientSocket->GetSocket());
}

CWinService::~CWinService()
{
	if (!m_wsaCleanUpDone)
	{
		auto ret = WSACleanup();
		if (FALSE != ret)
		{
			throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to de-initialize winsocket api module. \n");
		}
	}
}