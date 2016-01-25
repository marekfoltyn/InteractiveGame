#ifndef  _DEFINITIONS_H_
#define  _DEFINITIONS_H_

#include "MessageIdentifiers.h"

// time (ms) during when reliable packet was not able to be received -> connection lost
#define CONNECTION_LOST_TIMEOUT 10000

// logging function
#define LOG(...) printf(__VA_ARGS__)

// port used for all communication
#define SERVER_PORT 54027

// client port used for all communication
#define CLIENT_PORT 54023

// maximum players connected to server
#define MAX_PLAYERS 8

// sleep time between receiving packets
#define RAKNET_SLEEP 30

// find servers repeat time (in seconds)
#define FIND_SERVER_REPEAT_TIME 0.5

// server lifetime - time to disappear from menu after not responsing to ping (in seconds)
#define SERVER_MENU_LIFETIME 3

// how often to run packet receive loop (in seconds)
#define RECEIVE_TIMEOUT 0.03

/////////////////// Message types  ///////////////////

#define P_PING                        ID_UNCONNECTED_PING_OPEN_CONNECTIONS
#define P_SERVER_NAME                 ID_UNCONNECTED_PONG
#define P_NEW_CONNECTION              ID_NEW_INCOMING_CONNECTION
#define P_CONNECTED                   ID_CONNECTION_REQUEST_ACCEPTED
#define P_CONNECTION_LOST             ID_CONNECTION_LOST

//#define PACKET_CUSTOM                      ID_USER_PACKET_ENUM+1 // +2, +3 and so on

#endif // _DEFINITIONS_H_
