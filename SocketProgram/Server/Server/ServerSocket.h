#pragma once

#include "CBaseSocket.h"

class CServerSocketBase : public CBaseSocket
{
public:

	CServerSocketBase(const int portNumber, const int addressFamily, const int socketType, const int protocol,
		const int backLogSize) :
		CBaseSocket(portNumber, addressFamily, socketType, protocol, backLogSize) {}
	CServerSocketBase() = default;

	virtual void Create() = 0;
	virtual void Bind() = 0;
	virtual void Listen() = 0;
	virtual ServerBaseSocketPtr Accept() = 0;
	virtual int Recv(char* data, int bytesToRead) = 0;

	virtual ~CServerSocketBase() {}
};

class CServerSocket : public CServerSocketBase
{
public:
	CServerSocket(const int portNumber, const int addressFamily, const int socketType,
		const int protocol, const int backLogSize) :
		CServerSocketBase(portNumber, addressFamily, socketType, protocol, backLogSize)
	{}

	CServerSocket() = default;

	void Create() override;
	void Bind() override;
	void Listen() override;
	ServerBaseSocketPtr Accept() override;
	int Recv(char* data, int bytesToRead) override;
};
