#pragma once
#include <vector>
#include "IEntity.h"
#include "Client.h"

class CZSpawner;

class CMain
{
public:
	CMain() { main(); };
	~CMain();

	void main();

	std::vector<IEntity*> entityList;
	std::vector<ServerClient*> clientList;

private:
	CZSpawner* pZSpawner;
};

extern CMain* gMain;