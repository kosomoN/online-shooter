#include "PacketProcessor.h"

#include <string>
#include "GlobalSystem.h"
#include "ByteDecoder.h"
#include "Player.h"

void CPacketProcessor::packetReceived(ENetEvent & event)
{
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
					IEntity* entity = gSys->pEntitySystem->getEntity(entityID);
					if (entity == nullptr)
					{
						gSys->log("Entity does not exist");
						return;
					}

					entity->parsePacket((event.packet->data + index), payloadSize);
					index += payloadSize;
				}
				else
				{
					reachedEnd = true;
				}
			}
		}
		break;
		case PacketTypes::ENTITY_CREATE:
		{
			unsigned int index = 1;
			uint32_t id = readUint32(event.packet->data + index);

			//Player is already created
			if (id == gSys->pPlayer->getID())
				return;

			index += sizeof(id);
			IEntity* entity;
			switch (*(event.packet->data + index))
			{
			case EntityTypes::PLAYER:
				entity = new CPlayer(id);
				break;
			}
			
			uint16_t payloadSize = readUint16(event.packet->data + index);
			index += sizeof(payloadSize);
			entity->parsePacket(event.packet->data + index, payloadSize);
		}
		break;
		default:
			fprintf(stderr, "Unknown packet type: %u", *(event.packet->data));
			break;
		}
	}
}
