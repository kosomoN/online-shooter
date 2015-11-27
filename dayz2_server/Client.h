#pragma once

#include <enet/enet.h>
struct Player;

struct ServerClient
{
	ENetPeer* m_pPeer = 0;
	Player* m_pEntity = 0;
	uint8_t keyStates = 0;
};