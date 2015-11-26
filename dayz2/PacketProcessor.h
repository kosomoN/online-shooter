#pragma once

#include <enet/enet.h>
#include <cstdint>

class CPacketProcessor
{
public:
	CPacketProcessor() {}
	~CPacketProcessor() {}

	void packetReceived(ENetEvent& event);
};
