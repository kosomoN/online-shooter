#include "Client.h"

#include <iostream>
#include "GlobalSystem.h"
#include "ByteDecoder.h"
#include "Player.h"

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
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			gSys->log("Disconnected from host");
			//TODO Add proper shutdown
			exit(1);
			break;
		} 
	} 
}

bool CClient::connect(ENetAddress& address)
{
	if (client == nullptr)
	{
		client = enet_host_create(nullptr, 1, MAX_CHANNELS, 0, 0);

		if (client == nullptr)
		{
			fprintf(stderr,
				"An error occurred while trying to create an ENet client host.\n");
			exit(EXIT_FAILURE);
		}
	}

	peer = enet_host_connect(client, &address, MAX_CHANNELS, 0);

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
		while (enet_host_service(client, &event, 1000))
		{
			switch(event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				if (event.packet->dataLength >= 5 && *(event.packet->data) == PacketTypes::CONNECTION_ACCEPTED)
				{
					gSys->pPlayer = new CPlayer(readUint32(event.packet->data + 1));

					uint8_t packetType = PacketTypes::REQUEST_TIME;
					ENetPacket* packet = enet_packet_create(&packetType, sizeof(packetType), 0);
					gSys->lastTimeRequest = glfwGetTime();
					enet_peer_send(peer, COMMAND_CHANNEL, packet);
					return true;
				}
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				return false;
				break;
			}
		}
	}

	enet_peer_reset(peer);
	return false;
}

void CClient::disconnect()
{
	enet_peer_disconnect(peer, 0);

	ENetEvent event;
	while (enet_host_service(client, &event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			puts("Disconnection succeeded.");
			return;
		}
	}

	enet_peer_reset(peer);
}

void CClient::init()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
}

