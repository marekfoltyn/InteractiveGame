#ifndef __CONTROLLER_DEFINITIONS_H__
#define __CONTROLLER_DEFINITIONS_H__

class Definitions{
public:
    
    // delay when the click is considered successful (in seconds)
    constexpr static const float TIME_DELAY_CLICK = 0.6;
    
    // action tag (delay, button animation and after ACCIDENT_CLICK_DELAY seconds call click handler)
    static const int TAG_DELAY_CLICK = 1;
    
    // time needed to hold the kick button to maximum kick force
    constexpr static const float TIME_KICK_FORCE_MAX = 1.0;
    
};

#endif // __CONTROLLER_DEFINITIONS_H__
