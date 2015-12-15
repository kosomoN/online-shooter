#include <iostream>
#include <enet/enet.h>
#include "Player.h"
#include "Client.h"
#include <chrono>
#include "dayz2/NetworkConstants.h"
#include <vector>
#include <algorithm>
#include "Zombie.h"
#include "main.h"
#include "ZSpawner.h"
#include <string>
#include "dayz2/ByteDecoder.h"
#include <Box2D/Box2D.h>

CMain* gMain;

typedef std::chrono::high_resolution_clock Clock;

#define TICK_LENGTH (1.0 / 20.0)

DWORD WINAPI ConsoleListeningThread(void* arguments)
{
	while (true)
	{
		std::string line;
		std::getline(std::cin, line);

		if (line == "spawnz")
			gMain->pZSpawner->spawn(100, gMain->nextEntID);

	}
}

void CMain::main()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return;
	}

	ENetAddress address;

	address.host = ENET_HOST_ANY;
	address.port = 12321;

	server = enet_host_create(&address, 32, MAX_CHANNELS, 0, 0);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}

	thread = CreateThread(nullptr, 0, ConsoleListeningThread, 0, 0, nullptr);

	gMain = this;
	
	pWorld = new b2World(b2Vec2(0, 0));

	nextEntID = 0;

	bool shouldClose = false;

	pZSpawner = new CZSpawner;

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

			pWorld->Step(TICK_LENGTH, 6, 2);

			accumulatedTicks--;

			packetBuffer[0] = PacketTypes::ENTITY_UPDATE;
			memcpy(packetBuffer + 1, &gameTime, sizeof(gameTime));
			int packetIndex = 9;
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
			ENetPacket* packet = enet_packet_create(packetBuffer, packetIndex, 0);
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

				auto zid = nextEntID++;

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
			}
			break;
			case ENET_EVENT_TYPE_RECEIVE:

				if (event.packet->dataLength > 0)
				{
					switch (*event.packet->data)
					{
					case PacketTypes::INPUT_UPDATE:
						if (event.packet->dataLength == 6)
						{
							static_cast<ServerClient*>(event.peer->data)->keyStates = *(event.packet->data + 1);
							static_cast<ServerClient*>(event.peer->data)->m_pEntity->m_angle = readFloat((event.packet->data + 2));
						}
					break;
					case PacketTypes::PLAYER_SHOOT:
						if (event.packet->dataLength == 5)
						{
							Player* pPlayer = static_cast<ServerClient*>(event.peer->data)->m_pEntity;
							float angle = 0;
							memcpy(&angle, event.packet->data + 1, sizeof(angle));
							shootingHandler.fire(pPlayer, angle);

							uint8_t packetData[9];
							packetData[0] = PacketTypes::PLAYER_SHOOT;
							memcpy(packetData + 1, &pPlayer->m_id, sizeof(uint32_t));
							memcpy(packetData + 5, &angle, sizeof(float));
							ENetPacket* packet = enet_packet_create(packetData, sizeof(packetData), 0);
							enet_host_broadcast(server, EFFECTS_CHANNEL, packet);
						}
					case PacketTypes::REQUEST_TIME:
					{
						uint8_t packetData[9];
						packetData[0] = PacketTypes::REQUEST_TIME;
						memcpy(packetData + 1, &gameTime, sizeof(double));
						ENetPacket* returnPacket = enet_packet_create(packetData, sizeof(packetData), 0);
						enet_peer_send(event.peer, COMMAND_CHANNEL, returnPacket);
					}
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

				entityList.erase(std::remove(entityList.begin(), entityList.end(), static_cast<IEntity*>(pPlayer)));
				clientList.erase(std::remove(clientList.begin(), clientList.end(), serverClient));
				delete static_cast<IEntity*>(pPlayer);
				delete serverClient;

				enet_host_broadcast(server, COMMAND_CHANNEL, packet);
			}
		}
	}
	enet_host_destroy(server);
	enet_deinitialize();
}

void CMain::initializeEntityOnClients(IEntity* pEnt) 
{
	int packetIndex = 1;
	packetBuffer[0] = PacketTypes::ENTITY_CREATE;
	memcpy(packetBuffer + packetIndex, &pEnt->m_id, sizeof(pEnt->m_id));
	packetIndex += sizeof(pEnt->m_id);

	packetBuffer[packetIndex++] = pEnt->m_type;

	uint16_t serializedSize = pEnt->serializedSize();
	memcpy(packetBuffer + packetIndex, &serializedSize, sizeof(serializedSize));
	packetIndex += sizeof(serializedSize);

	pEnt->serialize(packetBuffer + packetIndex);
	packetIndex += serializedSize;

	ENetPacket* packet = enet_packet_create(packetBuffer, packetIndex, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(server, COMMAND_CHANNEL, packet);
}	

CMain::~CMain()
{
	CloseHandle(thread);
	delete pZSpawner;
	delete pWorld;
}

int main(void)
{
	CMain();
}
