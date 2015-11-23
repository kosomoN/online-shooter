#include "IActor.h"

#include "ByteDecoder.h"

void IActor::parsePacket(uint8_t* data, unsigned int length)
{
	if (length == 8)
	{
		m_pos.x = readFloat(data);
		m_pos.y = readFloat((data + 4));
	}
}