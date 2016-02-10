//
//  AccelerationBlok.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef AccelerationBlok_h
#define AccelerationBlok_h

#include "cocos2d.h"
#include "Connector.h"

/**
 
 Block with x, y, z values of the phone accelerometer

 Type:
 ==============================================
 P_ACCELERATION
 
 Format:
 ==============================================
 x (double)
 y (double)
 z (double)
 
*/
class AccelerationBlok{
public:

    /**
     * Create Block from acceleration object
     */
    static Blok * Create(cocos2d::Acceleration * acc);
    
    /**
     * Parse to the cocos2d acc object
     */
    static cocos2d::Acceleration Parse(Blok * block);
    
private:
    
    struct AccStruct{
        double x;
        double y;
        double z;
    };
};

#endif /* AccelerationBlock_h */
