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
	void disconnect();
	void init();

	ENetHost* client = nullptr;
	ENetPeer* peer = nullptr;
private:
	CPacketProcessor packetProcessor;

};

