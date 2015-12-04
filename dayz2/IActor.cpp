#include "IActor.h"

#include "ByteDecoder.h"
#include "GlobalSystem.h"

void IActor::parsePacket(uint8_t* data, unsigned int length, double time)
{
	if (length == 12)
	{
		m_pos.addValue(readFloat(data), readFloat(data + 4), time);
		m_angle = readFloat(data + 8);
		printf("%f \n", m_angle);
	}
}