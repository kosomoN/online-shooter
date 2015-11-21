#include "PacketProcessor.h"

#include <string>
#include "GlobalSystem.h"

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
		default:
			fprintf(stderr, "Unknown packet type: %u", *(event.packet->data));
			break;
		}
	}
}
