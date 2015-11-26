#pragma once

#include <cstdint>

#define COMMAND_CHANNEL 0
#define SNAPSHOT_CHANNEL 1
#define MAX_CHANNELS 2

struct PacketTypes
{
	static const uint8_t CONNECTION_ACCEPTED = 0x01;

	static const uint8_t ENTITY_CREATE = 0x10;
	static const uint8_t ENTITY_UPDATE = 0x11;

	static const uint8_t INPUT_UPDATE = 0x20;
};
