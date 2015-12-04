#pragma once
#include <vector>
#include "IEntity.h"
#include "Client.h"
#include <Windows.h>

class CZSpawner;

class CMain
{
public:
	CMain() { main(); };
	~CMain();

	void main();

	std::vector<IEntity*> entityList;
	std::vector<ServerClient*> clientList;
	void initializeEntityOnClients(IEntity* pEnt);
	CZSpawner* pZSpawner;
	uint32_t nextEntID = 0;

private:
	uint8_t packetBuffer[204800];
	HANDLE thread;
};

extern CMain* gMain;