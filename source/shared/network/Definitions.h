#ifndef  _DEFINITIONS_H_
#define  _DEFINITIONS_H_

#include "MessageIdentifiers.h" // packet types
#include "cocos2d.h" // CCLOG

/**
 * constants used in GameNet module
 */

// time (ms) during when reliable packet was not able to be received -> connection lost
#define CONNECTION_LOST_TIMEOUT 5000

// logging function - now used with cocos2d
#define LOG(...) CCLOG(__VA_ARGS__)

// port used for all communication
// Warning: the system uses PORT_RANGE ports (SERVER_PORT, SERVER_PORT+1, ..., SERVER_PORT+PORT_RANGE-1)
#define SERVER_PORT 54027

// client port used for all communication
// Warning: the system uses PORT_RANGE ports (CLIENT_PORT, CLIENT_PORT+1, ..., CLIENT_PORT+PORT_RANGE-1)
#define CLIENT_PORT 53027

// maximum players connected to server
#define MAX_PLAYERS 8

// sleep time between receiving packets (ms)
#define RAKNET_SLEEP 30

// find servers repeat time (in seconds)
#define FIND_SERVER_REPEAT_TIME 0.5

// server lifetime - time to disappear from menu after not responsing to ping (in seconds)
#define SERVER_MENU_LIFETIME 5

// how often to run packet receive loop (in seconds)
#define RECEIVE_TIMEOUT 0.015

// scene transition speed (in seconds)
#define TIME_SCENE_TRANSITION 0.2

// connection password (no need to change)
#define RAKNET_PASSWORD "abc"

#define PORT_RANGE 10

/////////////////// Message types ///////////////////

/**
 * #define PACKET_CUSTOM              ID_USER_PACKET_ENUM+1 // +2, +3 and so on
 */

// moved to GameplayEvents.h


#endif // _DEFINITIONS_H_
