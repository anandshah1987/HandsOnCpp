#include "Service.h"
#include <iostream>


void CServiceBase::ReadConfig()
{
	// Todo : Read from INI file
	m_addressFamily=AF_INET;
	m_type=SOCK_STREAM;
	m_protocol = 0;
	m_portNumber=7500;
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
}

void CWinService::ReadConfig()
{
	std::cout << "Reading config files ...\n";

	CServiceBase::ReadConfig();
	
}


void CWinService::DeInit()
{
	std::cout << "De-Initializing windows server ...\n";

	auto ret = WSACleanup();
	if (FALSE != ret)
	{
		throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to de-initialize winsocket api module. \n");
	}
}