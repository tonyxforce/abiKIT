#ifndef NETWORK_H
#define NETWORK_H
#include "credentials.h"
#include <WiFi.h>
#include <WiFiUdp.h>

extern WiFiUDP udp;
extern const unsigned int localUdpPort;  // Local UDP port for listening
extern char incomingPacket[255];  // Buffer for incoming packets
extern IPAddress clientIP;

void networkSetup();

#endif