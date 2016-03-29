#ifndef __GAMEPLAY_DEFINITIONS_H__
#define __GAMEPLAY_DEFINITIONS_H__

#include "GameplayEvents.h"

// toggle debug
#define DEBUG

/**
 * static constants and values used in both Controller and Game
 */
class Definitions{
public:
    
    // delay when the click is considered successful (in seconds)
    constexpr static const float TIME_DELAY_CLICK = 0.6;
    
    // action tag (delay, button animation and after ACCIDENT_CLICK_DELAY seconds call click handler)
    static const int TAG_DELAY_CLICK = 1;
    
    // time needed to hold the kick button to maximum kick force
    constexpr static const float TIME_KICK_FORCE_MAX = 1.0;
    
    static const int LEFT  = 0;
    static const int RIGHT = 1;
    
    // fade out duration when a dialog is canceled (in seconds)
    constexpr static const float DIALOG_FADEOUT_DURATION = 0.25;
    
    constexpr static const float TIME_COLLISION_VIBRATION = 0.05;
    
    static const int OPACITY_FULL = 255;
    static const int OPACITY_HALF = 123;
    
    constexpr static const float TIME_KICKBONUS_MIN = 5.0;
    constexpr static const float TIME_KICKBONUS_MAX = 20.0;
    constexpr static const float KICKBONUS_MULTIPLIER = 2.0;
    
    static const unsigned int TIME_MATCH_SHORT  = 180;     // 3 min
    static const unsigned int TIME_MATCH_MEDIUM = 300;     // 5 min
    static const unsigned int TIME_MATCH_LONG   = 420;     // 7 min

    constexpr static const float TIME_GENERATE_BONUS_MIN = 5.0;
    constexpr static const float TIME_GENERATE_BONUS_MAX = 60.0;
    
    constexpr static const float TIME_LABEL_FADE = 0.5;
    
};

#define SERVER_NAME_DEFAULT "ConnectHere"

#define COLOR_GRAY                      Color4B(1, 52, 4, 120)
#define COLOR_GREEN                     Color4B(11, 112, 14, 255)
#define COLOR_GREEN_SEMI_TRANSPARENT    Color4B(11, 112, 14, 155)
#define COLOR_GREEN_ALMOST_TRANSPARENT  Color4B(11, 112, 14, 77)
#define COLOR_RED   Color4B(209, 119, 45, 255)

#define OPACITY_LABELS 44

#define TEAM_BLUE "blue"
#define TEAM_RED  "red"
#define TEAM_AUTO "auto"

#define STRING_DURATION_SHORT "3min"
#define STRING_DURATION_MEDIUM "5min"
#define STRING_DURATION_LONG "7min"

#define STRING_SIZE_SMALL  "small"
#define STRING_SIZE_MEDIUM "medium"
#define STRING_SIZE_BIG    "big"


#define SETTINGS_VIBRATE "vibrate"

#define BITMASK_SOLID            1 // 0000 0001
#define BITMASK_BALL             2 // 0000 0010
#define BITMASK_PLAYER           4 // 0000 0100
#define BITMASK_SCORE            8 // 0000 1000
#define BITMASK_BALL_BOUNDARY   16 // 0001 0000

#define BITMASK_ALL    0xFFFFFFFF

#define PLAYER_COLLIDES_WITH    BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER

//#define COLOR_FONT_TRANSPARENT cocos2d::Color4B(255,255,255,44)
#define COLOR_FONT_TRANSPARENT cocos2d::Color4B(255,255,255,255)
#define NODE_BALL "sprBall"
#define BALL_DAMPING 0.7
#define BORDER 20
#define SCALE_GOAL 0.8
#define SCALE_BALL 0.8
#define MATERIAL_SOLID cocos2d::PhysicsMaterial(0.5, 1, 0.5)
#define MATERIAL_BALL cocos2d::PhysicsMaterial(0.5, 0.5, 0.5)
#define MATERIAL_PLAYER cocos2d::PhysicsMaterial(0.5, 0, 0.5)
#define LABEL_SCORE_LEFT "lblScoreLeft"
#define LABEL_SCORE_RIGHT "lblScoreRight"
#define LABEL_ADMIN "lblAdminName"
#define LABEL_SERVER_NAME "lblServerName"
#define LABEL_TIME "lblTime"


#define SCHEDULE_KICK_SLOWING "kickSlowing"
#define SCHEDULE_GENERATE_BONUS "generateBonus"
#define SCHEDULE_COUNTDOWN "countdown"

#define FONT_DEFAULT "Vanilla.ttf"


#define BORDER_DEFAULT 50

#endif // __GAMEPLAY_DEFINITIONS_H__
