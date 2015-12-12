#pragma once
#include <vector>
#include "IEntity.h"
#include "Client.h"
#include "ShootingHandler.h"

class CZSpawner;
class b2World;

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
	b2World* pWorld;

private:
	CShootingHandler shootingHandler;
	uint8_t packetBuffer[204800];
	HANDLE thread;
	ENetHost* server;
};

extern CMain* gMain;