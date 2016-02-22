#ifndef __CONTROLLER_DEFINITIONS_H__
#define __CONTROLLER_DEFINITIONS_H__

class Definitions{
public:
    
    // delay when the click is considered successful (in seconds)
    static const int TIME_DELAY_CLICK = 1;
    
    // action tag (delay, button animation and after ACCIDENT_CLICK_DELAY seconds call click handler)
    static const int TAG_DELAY_CLICK = 1;
    
};

#endif // __CONTROLLER_DEFINITIONS_H__
