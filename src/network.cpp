#include "network.h"
WiFiUDP udp;
const unsigned int localUdpPort = 4210;  // Local UDP port for listening
char incomingPacket[255];  // Buffer for incoming packets
IPAddress clientIP;

void networkSetup(){
	WiFi.softAP(ssid, password);
	udp.begin(localUdpPort);
}