#ifndef __GAMEPLAY_DEFINITIONS_H__
#define __GAMEPLAY_DEFINITIONS_H__

#include "GameplayEvents.h"

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

};


// toggle debug
#define DEBUG

#define SETTINGS_VIBRATE "vibrate"

#define BITMASK_SOLID            1 // 0000 0001
#define BITMASK_BALL             2 // 0000 0010
#define BITMASK_PLAYER           4 // 0000 0100
#define BITMASK_SCORE            8 // 0000 1000
#define BITMASK_BALL_BOUNDARY   16 // 0001 0000

#define BITMASK_ALL    0xFFFFFFFF

#define PLAYER_COLLIDES_WITH    BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER



#define COLOR_FONT_TRANSPARENT cocos2d::Color4B(255,255,255,44)
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


#define SCHEDULE_KICK_SLOWING "kickSlowing"


#define BORDER_DEFAULT 50

#endif // __GAMEPLAY_DEFINITIONS_H__
