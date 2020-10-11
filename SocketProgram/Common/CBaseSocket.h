#pragma once
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <memory>
#include <system_error>

#define INVALID_VALUE -99

#define CLIENT_INI_FILE_NAME "client.ini"
#define INI_CONFIG_SECTION "CONFIG"
#define DEFAULT_SERVER_PORT 7500
#define DEFAULT_SOCKET_PROTOCOL 0
#define SERVER_IP_DEFAULT "127.0.0.1"

class CServerSocketBase;
using ServerBaseSocketPtr = CServerSocketBase *;

class CBaseSocket
{
public :
	CBaseSocket(const int portNumber, const int addressFamily, const int type, const int protocol, 
				const int backLogSize)
	{
		Init(portNumber, addressFamily, type, protocol, backLogSize);
	}

	CBaseSocket()=default;

	const int GetAddressFamily() const
	{
		return m_addressFamily;
	}

	const int GetType() const
	{
		return m_type;
	}

	const int GetProtocol() const
	{
		return m_protocol;
	}

	const int GetPortNumber() const
	{
		return m_portNumber;
	}

	const int GetBacklogSize() const
	{
		return m_backLogSize;
	}

	const SOCKET GetSocket() const
	{
		return m_socket;
	}

	std::string GetIpAddress() const
	{
		return m_ipAddress;
	}

	void SetSocket(SOCKET socketCreated)
	{
		m_socket = socketCreated;
	}

	void SetIpAddress(const std::string ipaddress)
	{
		m_ipAddress = ipaddress;
	}

	void Create()
	{
		m_socket = socket(m_addressFamily, m_type, m_protocol);
		if (INVALID_SOCKET == m_socket)
		{
			throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to create new socket.");
		}
	}

	void Init(const int portNumber, const int addressFamily, const int type, const int protocol, const int backLogSize)
	{
		m_portNumber = portNumber;
		m_addressFamily = addressFamily;
		m_type = type;
		m_protocol = protocol;
		m_backLogSize = backLogSize;
	}

	virtual ~CBaseSocket() {}

private :
	int m_addressFamily{ INVALID_VALUE };
	int m_type{ INVALID_VALUE };
	int m_protocol{ INVALID_VALUE };
	int m_portNumber{ INVALID_VALUE };
	int m_backLogSize{ INVALID_VALUE };
	std::string m_ipAddress{};
	SOCKET m_socket{};

	void CheckConsistency()
	{
		if (INVALID_VALUE == m_portNumber || INVALID_VALUE == m_addressFamily || INVALID_VALUE == m_type
			|| INVALID_VALUE == m_protocol || INVALID_VALUE == m_backLogSize)
		{
			throw std::exception("Inavlid parameters to create socket ...");
		}
	}
};