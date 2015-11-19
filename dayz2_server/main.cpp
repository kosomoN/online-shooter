#include <iostream>
#include <enet/enet.h>

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

	server = enet_host_create(&address, 32, 1, 0, 0);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}

	bool shouldClose = false;

	ENetEvent event;
	while (!shouldClose)
	{
		while (enet_host_service(server, &event, 1000))
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
			{
				printf("A new client connected from %x:%u.\n",
					event.peer->address.host,
					event.peer->address.port);

				ENetPacket* packet = enet_packet_create("packet",
					strlen("packet") + 1,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(event.peer, 0, packet);
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