#include "Client.h"

#include <iostream>
#include "GlobalSystem.h"

CClient::CClient()
{
}


CClient::~CClient()
{
	enet_deinitialize();
}

void CClient::update()
{
	ENetEvent event;
	
	while (enet_host_service(client, &event, 0))
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			packetProcessor.packetReceived(event);
			enet_packet_destroy(event.packet);
		case ENET_EVENT_TYPE_DISCONNECT:
			gSys->log("Disconnected from host");
			//TODO Add proper shutdown
			exit(1);
		} 
	} 
}

bool CClient::connect(ENetAddress& address)
{
	if (client == nullptr)
	{
		client = enet_host_create(nullptr, 1, 1, 0, 0);

		if (client == nullptr)
		{
			fprintf(stderr,
				"An error occurred while trying to create an ENet client host.\n");
			exit(EXIT_FAILURE);
		}
	}

	peer = enet_host_connect(client, &address, 1, 0);

	if (peer == nullptr)
	{
		fprintf(stderr,
			"No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}

	ENetEvent event;
	if (enet_host_service(client, &event, 1000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		gSys->log("Connected to server");
		return true;
	}

	enet_peer_reset(peer);
	return false;
}

void CClient::init()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
}

