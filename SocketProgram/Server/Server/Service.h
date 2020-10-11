#pragma once

#include "CBaseSocket.h"
#include <memory>
#include "ServerSocket.h"
#include <iostream>

class CServiceBase
{
private :
	
	int m_addressFamily{};
	int m_type{};
	int m_protocol{};
	int m_portNumber{};
	int m_backLogSiz{};
public :
	CServiceBase(CServerSocketBase& serverSocket) : m_listeningSocket(serverSocket){};
	virtual void Init() = 0;
	virtual void ReadConfig() = 0;
	virtual void Start() = 0;
	virtual void DeInit() = 0;
	virtual void StartConnectionMonitor() = 0;
	virtual void ConnectionMonitorThread() = 0;
	virtual void RequestProcessingThread(ServerBaseSocketPtr clientSocket) = 0;
	// todo : join connection monitor thread using promise future
	//virtual void JoinMonitorThread() = 0;

	virtual void ServerLoop()
	{
		std::cout << "Server entering inifinite loop ... \n";
		while (true)
		{
			Sleep(1000);
		}
	}

protected : 
	CServerSocketBase& m_listeningSocket;
};



class CWinService : public CServiceBase
{
public :
	CWinService(CServerSocketBase& serverSocket) : CServiceBase(serverSocket) {};
	void Init() override;
	void ReadConfig() override;
	void Start() override;
	void DeInit() override;
	void StartConnectionMonitor() override;
	void ConnectionMonitorThread() override;
	void RequestProcessingThread(ServerBaseSocketPtr clientSocket) override;
	~CWinService();
private :
	bool m_wsaCleanUpDone{};
};