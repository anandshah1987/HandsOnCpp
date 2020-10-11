#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include "Client.h"

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT_NUMBER	7500
#define BUFFER_SIZE 1023


void CClient::Init()
{
	std::cout << "Initializing client ... \n";

	WSADATA wsaData{};
	WORD version = MAKEWORD(2, 2);
	auto ret = WSAStartup(version, &wsaData);
	if (FALSE != ret)
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to initialize WSA library ...");
	}
	m_wsaInitialized = true;

	ReadConfig();
}

void CClient::ReadConfig()
{
	std::cout << "Reading client config ...\n";

	m_addressFamily = GetPrivateProfileIntA(INI_CONFIG_SECTION, "AddressFamily", AF_INET, CLIENT_INI_FILE_NAME);
	m_type = GetPrivateProfileIntA(INI_CONFIG_SECTION, "SocketType", SOCK_STREAM, CLIENT_INI_FILE_NAME);
	m_portNumber = GetPrivateProfileIntA(INI_CONFIG_SECTION, "Port", DEFAULT_SERVER_PORT, CLIENT_INI_FILE_NAME);
	m_protocol = GetPrivateProfileIntA(INI_CONFIG_SECTION, "Protocol", DEFAULT_SOCKET_PROTOCOL, CLIENT_INI_FILE_NAME);
	char serverIp[15]{};
	GetPrivateProfileStringA(INI_CONFIG_SECTION, "ServerIp", SERVER_IP_DEFAULT,
		serverIp, 15, CLIENT_INI_FILE_NAME);
	m_serverIp = serverIp;

	std::cout << "=========== Client configuration start ========= \n";
	std::cout << "AddressFamily = " << m_addressFamily << '\n';
	std::cout << "SocketType = " << m_type << '\n';
	std::cout << "Port = " << m_portNumber << '\n';
	std::cout << "Protocol = " << m_protocol << '\n';
	std::cout << "Server Ip = " << m_serverIp << '\n';
	std::cout << "=========== Client configuration ends ========= \n";
}

void CClient::Start()
{
	std::cout << "Creating client socket ... \n";

	m_clientSocket.Init(m_portNumber, m_addressFamily, m_type, m_protocol, m_serverIp);
	m_clientSocket.Create();
	m_clientSocket.Connect();
}

void CClient::DeInit()
{
	std::cout << "De-Initializing client ... \n";
	if (m_wsaInitialized)
	{
		WSACleanup();
	}
	closesocket(m_clientSocket.GetSocket());
}

void CClient::StartSendingDataBlocking()
{
	m_clientSocket.SendBlocking();
}

int main()
{
	CClientSocket clientSocket;
	CClient client(clientSocket);
	try
	{
		client.Init();
		client.Start();
		client.StartSendingDataBlocking();
		client.DeInit();
	}
	catch (const std::system_error& ex)
	{
		std::cout << "Failed to run client .. error code [" << ex.code()
			<< "] error message " << ex.what() << '\n';
		client.DeInit();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Failed to run client .. error message -> " << ex.what() << '\n';
		client.DeInit();
	}

	//SOCKET soc = socket(AF_INET, SOCK_STREAM, 0);
	//if (INVALID_SOCKET == soc)
	//{
	//	std::cout << "Failed to create client socket \n";
	//	WSACleanup();
	//	return -1;
	//}

	//sockaddr_in serverAddrs{};
	//serverAddrs.sin_family = AF_INET;
	//serverAddrs.sin_port = htons(SERVER_PORT_NUMBER);
	//inet_pton(AF_INET, SERVER_IP_ADDRESS, &serverAddrs.sin_addr);

	//auto ret = connect(soc, reinterpret_cast<sockaddr*>(&serverAddrs), sizeof(serverAddrs));
	//if (SOCKET_ERROR == ret)
	//{
	//	std::cout << "Failed to connect to server \n";
	//	//WSACleanup();
	//	auto val = WSAGetLastError();
	//	return val;
	//}


	////char buffer[BUFFER_SIZE];
	//std::string userInput;

	//do
	//{
	//	std::cout << "Please enter the string to send to serevr .. . \n";

	//	std::getline(std::cin, userInput);
	//	auto bytesSent = send(soc, userInput.c_str(), userInput.size() + 1, 0);
	//	if (SOCKET_ERROR == bytesSent || 0 == bytesSent)
	//	{
	//		std::cout << "Error in sending data to server \n";
	//		WSACleanup();
	//		return WSAGetLastError();
	//	}

	//} while (userInput.size() > 0);

	//closesocket(soc);
	//WSACleanup();
}