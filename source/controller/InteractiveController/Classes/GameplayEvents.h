//
//  GameplayEvents.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef GameplayEvents_h
#define GameplayEvents_h

/**
 * Gameplay events - all "things" that could happen in the game and requires some processing
 * for example: click, packet receive, score point, collision and so on...
 * Each event has own code. Some codes  are based on RakNet packet numbering, but it is not
 * necessary (it is only easier - Box and Event numbering are the same)
 *
 * This file is shared with both the Game and the Controller
 */

#define BOX_PING                        ID_UNCONNECTED_PING_OPEN_CONNECTIONS
#define BOX_SERVER_NAME                 ID_UNCONNECTED_PONG
#define BOX_NEW_CONNECTION              ID_NEW_INCOMING_CONNECTION
#define BOX_CONNECTED                   ID_CONNECTION_REQUEST_ACCEPTED
#define BOX_DISCONNECTED                ID_DISCONNECTION_NOTIFICATION
#define BOX_CONNECTION_FAILED           ID_CONNECTION_ATTEMPT_FAILED
#define BOX_CONNECTION_LOST             ID_CONNECTION_LOST

#define BOX_ACCELERATION                ID_USER_PACKET_ENUM+1
#define BOX_COLLISION                   ID_USER_PACKET_ENUM+2 // 136
#define BOX_PLAYER_NAME                 ID_USER_PACKET_ENUM+3
#define BOX_KICK                        ID_USER_PACKET_ENUM+4
#define BOX_ADMIN                       ID_USER_PACKET_ENUM+5
#define BOX_RESET_SCORE                 ID_USER_PACKET_ENUM+6
#define BOX_TEAM_SELECT                 ID_USER_PACKET_ENUM+7
#define BOX_GAME_STREAM                 ID_USER_PACKET_ENUM+8

// Box type has range 0 - 255, so it is better that non-Box events have bigger numbers

#define VOID_PING_SERVERS               ID_USER_PACKET_ENUM+1000
#define VOID_GENERATE_BONUS             ID_USER_PACKET_ENUM+1001
#define VOID_DISCONNECT                 ID_USER_PACKET_ENUM+1002
#define VOID_ADMIN_DIALOG               ID_USER_PACKET_ENUM+1003
#define VOID_START_GAME                 ID_USER_PACKET_ENUM+1004
#define VOID_STOP_GAME                  ID_USER_PACKET_ENUM+1005
#define VOID_COUNTDOWN_FINISHED         ID_USER_PACKET_ENUM+1006

#define TOUCH_TEAM_SELECT               ID_USER_PACKET_ENUM+2000
#define TOUCH_TOGGLE_VIBRATE            ID_USER_PACKET_ENUM+2001

#define CLICK_CONNECT_TO_SERVER         ID_USER_PACKET_ENUM+3000

#define STRING_SERVER_NAME_UPDATE       ID_USER_PACKET_ENUM+4000
#define STRING_SERVER_DURATION_UPDATE   ID_USER_PACKET_ENUM+4001
#define STRING_SERVER_SIZE_UPDATE       ID_USER_PACKET_ENUM+4002

#endif /* GameplayEvents_h */
