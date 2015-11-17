#include "PacketProcessor.h"

#include <iostream>

void CPacketProcessor::packetReceived(ENetEvent & event)
{
	printf("A packet of length %u containing %s was received on channel %u.\n",
		event.packet->dataLength,
		event.packet->data,
		event.channelID);
}
