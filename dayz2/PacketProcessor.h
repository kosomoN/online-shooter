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

struct PacketTypes
{
	static const uint8_t ENTITY_UPDATE = 0x11;

	static const uint8_t INPUT_UPDATE = 0x20;
};

