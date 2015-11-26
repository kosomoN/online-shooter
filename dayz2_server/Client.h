#pragma once

#include <enet/enet.h>
#include "Player.h"

struct ServerClient
{
	ENetPeer* m_pPeer = 0;
	Player* m_pEntity = 0;
};