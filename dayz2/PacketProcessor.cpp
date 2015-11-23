#include "PacketProcessor.h"

#include <string>
#include "GlobalSystem.h"
#include "ByteDecoder.h"

void CPacketProcessor::packetReceived(ENetEvent & event)
{
	printf("A packet of length %u containing %s was received on channel %u.\n",
		event.packet->dataLength,
		event.packet->data,
		event.channelID);

	if (event.packet->dataLength > 0) {
		//First byte is the packet type
		switch (*(event.packet->data))
		{
		case PacketTypes::ENTITY_UPDATE:
		{
			//Current position in data
			unsigned int index = 1;

			//Process all entity updates
			bool reachedEnd = false;
			while (!reachedEnd)
			{
				//Check to see if there is enough data for entity ID and payload length
				if (event.packet->dataLength - index >= 6)
				{
					uint32_t entityID = readUint32((event.packet->data + index));
					index += 4;
					uint16_t payloadSize = readUint16((event.packet->data + index));
					index += 2;

					gSys->pEntitySystem->getEntity(entityID)
						->parsePacket((event.packet->data + index), payloadSize);
					index += payloadSize;
				}
				else
				{
					reachedEnd = true;
				}
			}
		}
		break;
		default:
			fprintf(stderr, "Unknown packet type: %u", *(event.packet->data));
			break;
		}
	}
}
