#pragma once

#include "CBaseSocket.h"


class CClientSocket : public CBaseSocket
{
public:
	CClientSocket(const int portNumber, const int addressFamily, const int socketType,
		const int protocol, const std::string& serverIp) :
		CBaseSocket(portNumber, addressFamily, socketType, protocol, 0),
		m_serverIp(serverIp)
	{}

	CClientSocket() = default;

	std::string GetServerIp()
	{
		return m_serverIp;
	}

	void Init(const int portNumber, const int addressFamily, const int socketType,
		const int protocol, const std::string& serverIp);

	virtual void Connect();
	virtual void SendBlocking();

	virtual ~CClientSocket() {}

private:
	std::string m_serverIp;

};