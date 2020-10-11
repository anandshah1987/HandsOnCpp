#pragma once
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <memory>
#include <system_error>


class CBaseSocket
{
public :
	CBaseSocket(const int portNumber, const int addressFamily, const int type, const int protocol)
		: m_addressFamily(addressFamily), m_type(type), m_protocol(protocol), m_portNumber(portNumber) {}

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

	const SOCKET GetSocket() const
	{
		return m_socket;
	}

	void Create()
	{
		m_socket = socket(GetAddressFamily(), GetType(), GetProtocol());
		if (INVALID_SOCKET == m_socket)
		{
			throw std::exception("Failed to create new socket \n");
		}
	}

private :
	int m_addressFamily{};
	int m_type{};
	int m_protocol{};
	int m_portNumber{};
	SOCKET m_socket{};
};


class IServerSocket
{
public :
	virtual void Create() = 0;
	virtual void Bind() = 0;
	virtual void Listen() = 0;
};

class CServerSocket : public CBaseSocket, public IServerSocket
{
private :
	int m_backLogSize{};
public :
	CServerSocket(const int portNumber, const int addressFamily, const int socketType,
		const int protocol, const int backLogSize) :
		CBaseSocket(portNumber, addressFamily, socketType, protocol),
		m_backLogSize(backLogSize) {}

	void Create()
	{
		CBaseSocket::Create();
	}

	void Bind()
	{
		sockaddr_in socketAddr{};
		socketAddr.sin_family = GetAddressFamily();
		socketAddr.sin_port = GetPortNumber();
		// todo : this should be configured from outside (at least for IPV6).
		socketAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		if (SOCKET_ERROR == (bind(GetSocket(), reinterpret_cast<sockaddr *>(&socketAddr), sizeof(sockaddr_in))))
		{
			throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to bind socket.");
		}
	}

	void Listen()
	{
		if (SOCKET_ERROR == (listen(GetSocket(), m_backLogSize)))
		{
			throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Failed to listen on socket.");
		}
	}
};