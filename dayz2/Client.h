#pragma once

#include <enet/enet.h>
#include "PacketProcessor.h"

class CClient
{
public:
	CClient();
	~CClient();

	void update();
	bool connect(ENetAddress& address);
	void init();

private:
	ENetHost* client = nullptr;
	ENetPeer* peer = nullptr;
	CPacketProcessor packetProcessor;

};

