#pragma once

#include <enet/enet.h>
#include "PacketProcessor.h"

#define UPDATE_CHANNEL 0
#define INPUT_CHANNEL 1
#define MAX_CHANNELS 2

class CClient
{
public:
	CClient();
	~CClient();

	void update();
	bool connect(ENetAddress& address);
	void init();

	ENetHost* client = nullptr;
	ENetPeer* peer = nullptr;
private:
	CPacketProcessor packetProcessor;

};

