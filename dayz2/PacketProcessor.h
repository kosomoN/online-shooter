#pragma once

#include <enet/enet.h>

class CPacketProcessor
{
public:
	CPacketProcessor() {}
	~CPacketProcessor() {}

	void packetReceived(ENetEvent& event);
};

