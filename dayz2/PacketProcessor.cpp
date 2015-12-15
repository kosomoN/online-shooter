#include "PacketProcessor.h"

#include <string>
#include "GlobalSystem.h"
#include "ByteDecoder.h"
#include "Player.h"
#include "Zombie.h"

void CPacketProcessor::packetReceived(ENetEvent & event)
{
	if (event.packet->dataLength > 0) {
		//First byte is the packet type
		switch (*(event.packet->data))
		{
		case PacketTypes::ENTITY_UPDATE:
		{
			double timeStamp = 0;
			memcpy(&timeStamp, event.packet->data + 1, sizeof(double));
			//Current position in data
			unsigned int index = 9;

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

					entity->parsePacket((event.packet->data + index), payloadSize, timeStamp);
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
			case EntityTypes::ZOMBIE:
				entity = new CZombie(id);
				break;
			}



			uint16_t payloadSize = readUint16(event.packet->data + index);
			index += sizeof(payloadSize);
			//TODO TIMESTAMP CREATE PACKETS
			entity->parsePacket(event.packet->data + index, payloadSize, 0);
		}
		break;
		case PacketTypes::ENTITY_DELETE:
		{
			if(IEntity* pEntity = gSys->pEntitySystem->getEntity(readUint32(event.packet->data + 1)))
			{
				gSys->pEntitySystem->deleteEntity(pEntity);
			}
		}
		break;
		case PacketTypes::PLAYER_SHOOT:
		{
			uint32_t playerID = readUint32(event.packet->data + 1);
			
			if (CPlayer* pPlayer = static_cast<CPlayer*>(gSys->pEntitySystem->getEntity(readUint32(event.packet->data + 1))))
			{
				pPlayer->fire(readFloat(event.packet->data + 5));
			}
		}
		break;
		case PacketTypes::REQUEST_TIME:
		{
			double serverTime = 0;
			memcpy(&serverTime, event.packet->data + 1, sizeof(double));

			//Add half of round-trip
			//serverTime += (glfwGetTime() - gSys->lastTimeRequest) / 2;

			gSys->pGame->serverTimeDelta = serverTime - glfwGetTime();
		}
		break;
		default:
			fprintf(stderr, "Unknown packet type: %u", *(event.packet->data));
			break;
		}
	}
}
