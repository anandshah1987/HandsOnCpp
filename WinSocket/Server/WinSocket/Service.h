#pragma once

#include "CBaseSocket.h"
#include <memory>

class CServiceBase
{
private :
	CServerSocket* m_serverSocket{};
	int m_addressFamily{};
	int m_type{};
	int m_protocol{};
	int m_portNumber{};
public :
	CServiceBase() {};
	virtual void Init() = 0;
	virtual void ReadConfig() = 0;
	virtual void Start() = 0;
	virtual void DeInit() = 0;
};



class CWinService : public CServiceBase
{
public :
	CWinService() {};
	void Init() override;
	void ReadConfig() override;
	void Start() override;
	void DeInit() override;

private :

};