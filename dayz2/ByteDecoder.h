#pragma once

#include <cstdint>
#include <string>

inline uint32_t readUint32(uint8_t* bytes)
{
	return (bytes[0]) | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
}

inline int32_t readInt32(uint8_t* bytes)
{
	return (bytes[0]) | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
}

inline float readFloat(uint8_t* bytes)
{
	float f;
	memcpy(&f, bytes, sizeof(f));
	return f;
}

inline uint16_t readUint16(uint8_t* bytes)
{
	return (bytes[0]) | (bytes[1] << 8);
}

