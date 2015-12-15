#pragma once

#include <cstdint>

#define COMMAND_CHANNEL 0
#define SNAPSHOT_CHANNEL 1
#define EFFECTS_CHANNEL 2
#define MAX_CHANNELS 3

#define UP_KEY    0
#define DOWN_KEY  1
#define LEFT_KEY  2
#define RIGHT_KEY 3

struct PacketTypes
{
	static const uint8_t CONNECTION_ACCEPTED = 0x01;
	static const uint8_t REQUEST_TIME = 0x05;

	static const uint8_t ENTITY_CREATE = 0x10;
	static const uint8_t ENTITY_UPDATE = 0x11;
	static const uint8_t ENTITY_DELETE = 0x12;

	static const uint8_t INPUT_UPDATE = 0x20;
	static const uint8_t PLAYER_SHOOT = 0x21;

	static const uint8_t PLAYER_HIT = 0x30;
};

struct EntityTypes
{
	static const uint8_t PLAYER = 0x00;
	static const uint8_t ZOMBIE = 0x01;
};
