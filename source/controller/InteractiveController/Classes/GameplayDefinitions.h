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
    constexpr static const float TIME_DELAY_CLICK = 0.4;
    
    // action tag (delay, button animation and after ACCIDENT_CLICK_DELAY seconds call click handler)
    static const int TAG_DELAY_CLICK = 1;
    
    // time needed to hold the kick button to maximum kick force
    constexpr static const float TIME_KICK_FORCE_MAX = 1.0;
    
    static const int LEFT  = 0;
    static const int RIGHT = 1;
    
    // fade out duration when a dialog is canceled (in seconds)
    constexpr static const float DIALOG_FADEOUT_DURATION = 0.25;
    
    constexpr static const float TIME_COLLISION_VIBRATION = 0.05;
    constexpr static const float TIME_VIBRATION_ENABLED = 0.20;
    
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
    
    static const int FONT_SIZE_GOAL_ANIMATION = 100;
};

#define SERVER_NAME_DEFAULT "ConnectHere"

#define DESIGN_WIDTH 1680
#define DESIGN_HEIGHT 1050

#define TIME_GOAL_ANIMATION 1
#define TIME_BALL_RESET_DELAY 4.0
#define TIME_BALL_CENTER 0.5

#define TIME_BONUS_GENERATION_MIN  5.0
#define TIME_BONUS_GENERATION_MAX 50.0
#define TIME_BLINK 0.1

#define PROBABILITY_BONUS 0.10  

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

#define BONUS_KICK "KickBonus"
#define BONUS_SPEED "SpeedBonus"
#define BONUS_INVISIBILITY "InvisibilityBonus"

#define SETTINGS_VIBRATE "vibrate"

#define BITMASK_SOLID             1 // 0000000 1
#define BITMASK_BALL              2 // 000000 1 0
#define BITMASK_PLAYER            4 // 00000 1 00
#define BITMASK_SCORE             8 // 0000 1 000
#define BITMASK_BALL_BOUNDARY    16 // 000 1 0000
#define BITMASK_BONUS            32 // 00 1 00000
#define BITMASK_INVISIBLE_PLAYER 64 // 0 1 000000

#define BITMASK_ALL    0xFFFFFFFF

#define PLAYER_COLLIDES_WITH               BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER
#define PLAYER_INVISIBLE_COLLIDES_WITH     BITMASK_SOLID | BITMASK_BALL

#define BALL_CONTACTS                      BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER | BITMASK_BALL_BOUNDARY | BITMASK_SCORE
#define BALL_CONTACTS_WITHOUT_GOAL         BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER | BITMASK_BALL_BOUNDARY
#define BALL_CONTACTS_AFTER_SCORE          BITMASK_SOLID | BITMASK_BALL | BITMASK_BALL_BOUNDARY

//#define COLOR_FONT_TRANSPARENT cocos2d::Color4B(255,255,255,44)
#define COLOR_FONT_TRANSPARENT cocos2d::Color4B(255,255,255,255)
#define NODE_BALL "sprBall"
#define BALL_DAMPING 0.7
#define BORDER 20
#define SCALE_GOAL 0.8
#define SCALE_BALL 0.8
#define MATERIAL_SOLID cocos2d::PhysicsMaterial(0.5, 1, 0.5)
#define MATERIAL_BALL cocos2d::PhysicsMaterial(0.5, 0.5, 0.5)
#define MATERIAL_PLAYER cocos2d::PhysicsMaterial(0.5, 0.5   , 0.5)
#define LABEL_SCORE_LEFT "lblScoreLeft"
#define LABEL_SCORE_RIGHT "lblScoreRight"
#define LABEL_ADMIN "lblAdminName"
#define LABEL_SERVER_NAME "lblServerName"
#define LABEL_TIME "lblTime"
#define LABEL_GOAL_ANIMATION "lblGoalAnimation"
#define LABEL_BONUS "lblBonus"
#define BUTTON_ADMIN "btnAdmin"

#define SCHEDULE_KICK_SLOWING "kickSlowing"
#define SCHEDULE_GENERATE_BONUS "generateBonus"
#define SCHEDULE_COUNTDOWN "countdown"

#define FONT_DEFAULT "Vanilla.ttf"

#define POSITION_CENTER Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2)

#define BORDER_DEFAULT 50

#endif // __GAMEPLAY_DEFINITIONS_H__
