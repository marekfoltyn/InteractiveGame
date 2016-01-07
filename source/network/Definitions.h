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

// find servers repeat time (in seconds)
#define FIND_SERVER_REPEAT_TIME 1


/////////////////// Message types  ///////////////////

#define P_FIND_SERVER                 ID_UNCONNECTED_PING
#define P_SERVER_NAME                 ID_UNCONNECTED_PONG
#define P_NEW_INCOMING_CONNECTION     ID_NEW_INCOMING_CONNECTION

//#define PACKET_CUSTOM                      ID_USER_PACKET_ENUM+1 // +2, +3 and so on

#endif // _DEFINITIONS_H_
