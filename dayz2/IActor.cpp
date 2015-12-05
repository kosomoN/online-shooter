#include "IActor.h"

#include "ByteDecoder.h"
#include "GlobalSystem.h"

void IActor::parsePacket(uint8_t* data, unsigned int length, double time)
{
	if (length >= 8)
	{
		m_pos.addValue(readFloat(data), readFloat(data + 4), time);
		if(length == 12)
			m_angle.addValue(readFloat(data + 8), time);
	}
}