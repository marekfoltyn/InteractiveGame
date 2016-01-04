#ifndef  _DEFINITIONS_H_
#define  _DEFINITIONS_H_

#include "MessageIdentifiers.h"

// time (ms) during when reliable packet was not able to be received -> connection lost
#define CONNECTION_LOST_TIMEOUT 5000

// logging function
#define LOG(...) printf(__VA_ARGS__)

// password needed for connection
#define INCOMING_PASSWORD "ahojkamo"

// server port used for all communication
#define SERVER_PORT 54027

// client port used for all communication
#define CLIENT_PORT 54023

// sleep time between receiving packets
#define RAKNET_SLEEP 30



/////////////////// Message types  ///////////////////

#define PACKET_PING                        ID_UNCONNECTED_PING
#define PACKET_PING_REPLY                  ID_UNCONNECTED_PONG

#endif // _DEFINITIONS_H_