#include <iostream>
#include <enet/enet.h>
#include "Player.h"
#include "Client.h"
#include <chrono>
#include "dayz2/NetworkConstants.h"
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

#define TICK_RATE 20

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
	
	std::vector<ServerClient> clientList;

	uint32_t nextEntID = 0;

	bool shouldClose = false;
	
	ENetEvent event;
	auto lastTime = Clock::now();
	while (!shouldClose)
	{
		lastTime = Clock::now();



		long timeToWait = 1000.0 / TICK_RATE - std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastTime).count();
		
		if (timeToWait < 0)
		{
			timeToWait = 0;
			std::cout << "Server overloaded" << std::endl;
		}

		while (enet_host_service(server, &event, timeToWait))
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
			{
				printf("A new client connected from %x:%u.\n",
					event.peer->address.host,
					event.peer->address.port);

				ServerClient newClient;
				newClient.m_pPeer = event.peer;
				uint32_t ID = nextEntID++;
				newClient.m_pEntity = new Player(ID);
				clientList.push_back(newClient);

				uint8_t packetData[1 + sizeof(ID)];
				packetData[0] = PacketTypes::CONNECTION_ACCEPTED;
				memcpy(packetData + 1, &ID, sizeof(ID));

				ENetPacket* packet = enet_packet_create(packetData, sizeof(packetData), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(event.peer, COMMAND_CHANNEL, packet);
			}
			break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.channelID);
				enet_packet_destroy(event.packet);

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", event.peer->data);
			}
		}
		

	}

	enet_host_destroy(server);
	enet_deinitialize();
}