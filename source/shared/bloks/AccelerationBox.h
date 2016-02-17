//
//  AccelerationBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef AccelerationBox_h
#define AccelerationBox_h

#include "cocos2d.h"
#include "Connector.h"

using namespace GameNet;

/**
 
 Box with x, y, z values of the phone accelerometer

 Type:
 ==============================================
 P_ACCELERATION
 
 Format:
 ==============================================
 x (double)
 y (double)
 z (double)
 
*/
class AccelerationBox{
public:

    /**
     * Create Box from acceleration object
     */
    static Box * Create(cocos2d::Acceleration * acc);
    
    /**
     * Parse to the cocos2d acc object
     */
    static cocos2d::Acceleration Parse(Box * box);
    
private:
    
    struct AccStruct{
        double x;
        double y;
        double z;
    };
};

#endif /* AccelerationBox_h */
