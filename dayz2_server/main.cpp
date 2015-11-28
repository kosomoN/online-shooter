#include <iostream>
#include <enet/enet.h>
#include "Player.h"
#include "Client.h"
#include <chrono>
#include "dayz2/NetworkConstants.h"
#include <vector>
#include <algorithm>


typedef std::chrono::high_resolution_clock Clock;

#define TICK_LENGTH (1.0 / 20.0)

int main(void)
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	ENetAddress address;
	ENetHost* server;

	address.host = ENET_HOST_ANY;
	address.port = 12321;

	server = enet_host_create(&address, 32, MAX_CHANNELS, 0, 0);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
	
	std::vector<ServerClient*> clientList;
	std::vector<IEntity*> entityList;

	uint32_t nextEntID = 0;

	bool shouldClose = false;
	
	uint8_t packetBuffer[2048];
	ENetEvent event;
	auto startTime = Clock::now();
	double gameTime, lastGameTime = 0, dt, accumulatedTicks = 0;
	while (!shouldClose)
	{
		gameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - startTime).count() / 1000000000.0;
		dt = gameTime - lastGameTime;
		lastGameTime = gameTime;

		accumulatedTicks += dt / TICK_LENGTH;
		if (accumulatedTicks >= 1)
		{
			for (IEntity* ent : entityList)
			{
				if (ent != nullptr)
					ent->update(TICK_LENGTH);
			}
			accumulatedTicks--;

			packetBuffer[0] = PacketTypes::ENTITY_UPDATE;
			int packetIndex = 1;
			for (IEntity* ent : entityList)
			{
				if (ent != nullptr)
				{
					//TODO RESTRICT PACKET SIZE!!
					memcpy((packetBuffer + packetIndex), &ent->m_id, sizeof(ent->m_id));
					packetIndex += sizeof(ent->m_id);
					uint16_t serializedSize = ent->serializedSize();
					memcpy((packetBuffer + packetIndex), &serializedSize, sizeof(serializedSize));
					packetIndex += sizeof(serializedSize);
					ent->serialize(packetBuffer + packetIndex);
					packetIndex += serializedSize;
				}
			}
			ENetPacket* packet = enet_packet_create(packetBuffer, packetIndex, ENET_PACKET_FLAG_UNSEQUENCED);
			enet_host_broadcast(server, SNAPSHOT_CHANNEL, packet);
		}
		if (accumulatedTicks >= 1)
			std::cout << "Server overloaded" << std::endl;

		while (enet_host_service(server, &event, 0))
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
			{
				printf("A new client connected from %x:%u.\n",
					event.peer->address.host,
					event.peer->address.port);

				ServerClient* newClient = new ServerClient;
				newClient->m_pPeer = event.peer;
				uint32_t ID = nextEntID++;
				Player* pPlayer = new Player(ID);
				newClient->m_pEntity = pPlayer;
				pPlayer->client = newClient;
				clientList.push_back(newClient);
				entityList.push_back(pPlayer);
				event.peer->data = newClient;

				uint8_t packetData[1 + sizeof(ID)];
				packetData[0] = PacketTypes::CONNECTION_ACCEPTED;
				memcpy(packetData + 1, &ID, sizeof(ID));

				ENetPacket* packet = enet_packet_create(packetData, sizeof(packetData), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(event.peer, COMMAND_CHANNEL, packet);

				//Send old entities
				for (IEntity* ent : entityList)
				{
					if (ent != nullptr)
					{
						int packetIndex = 1;
						packetBuffer[0] = PacketTypes::ENTITY_CREATE;
						memcpy(packetBuffer + packetIndex, &ent->m_id, sizeof(ent->m_id));
						packetIndex += sizeof(ent->m_id);

						packetBuffer[packetIndex++] = ent->m_type;

						uint16_t serializedSize = ent->serializedSize();
						memcpy(packetBuffer + packetIndex, &serializedSize, sizeof(serializedSize));
						packetIndex += sizeof(serializedSize);

						ent->serialize(packetBuffer + packetIndex);
						packetIndex += serializedSize;

						packet = enet_packet_create(packetBuffer, packetIndex, ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(newClient->m_pPeer, COMMAND_CHANNEL, packet);
					}
				}

				//Broadcast new player entity
				int packetIndex = 1;
				packetBuffer[0] = PacketTypes::ENTITY_CREATE;
				memcpy(packetBuffer + packetIndex, &pPlayer->m_id, sizeof(pPlayer->m_id));
				packetIndex += sizeof(pPlayer->m_id);

				packetBuffer[packetIndex++] = EntityTypes::PLAYER;

				uint16_t serializedSize = pPlayer->serializedSize();
				memcpy(packetBuffer + packetIndex, &serializedSize, sizeof(serializedSize));
				packetIndex += sizeof(serializedSize);

				pPlayer->serialize(packetBuffer + packetIndex);
				packetIndex += serializedSize;

				packet = enet_packet_create(packetBuffer, packetIndex, ENET_PACKET_FLAG_RELIABLE);
				enet_host_broadcast(server, COMMAND_CHANNEL, packet);
			}
			break;
			case ENET_EVENT_TYPE_RECEIVE:

				if (event.packet->dataLength > 0)
				{
					switch (*event.packet->data)
					{
					case PacketTypes::INPUT_UPDATE:
						if (event.packet->dataLength >= 2)
							reinterpret_cast<ServerClient*>(event.peer->data)->keyStates = *(event.packet->data + 1);
						break;
					}
				}

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "Client disconnected\n";
				ENetPacket* packet;

				ServerClient* serverClient = static_cast<ServerClient*>(event.peer->data);
				Player* pPlayer = serverClient->m_pEntity;

				uint32_t entId = pPlayer->m_id;

				uint8_t packetData[1 + sizeof(entId)];
				packetData[0] = PacketTypes::ENTITY_DELETE;
				memcpy(packetData + 1, &entId, sizeof(entId));

				packet = enet_packet_create(packetData, sizeof(packetData), ENET_PACKET_FLAG_RELIABLE);

				delete static_cast<IEntity*>(pPlayer);
				delete serverClient;
				entityList.erase(std::remove(entityList.begin(), entityList.end(), static_cast<IEntity*>(pPlayer)));
				clientList.erase(std::remove(clientList.begin(), clientList.end(), serverClient));

				enet_host_broadcast(server, COMMAND_CHANNEL, packet);
			}
		}


	}

	enet_host_destroy(server);
	enet_deinitialize();
}