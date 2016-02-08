//
//  AccelerationBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "AccelerationBlok.h"

Blok * AccelerationBlok::Create(cocos2d::Acceleration * acc)
{
    AccStruct str;
    str.x = acc->x;
    str.y = acc->y;
    str.z = acc->z;
    
    Blok * blok = Blok::create( (const char *) &str, sizeof(AccStruct) );
    blok->setType(P_ACCELERATION);
    blok->setPriority(PacketPriority::HIGH_PRIORITY);
    blok->setReliability(PacketReliability::UNRELIABLE);
    
    return blok;
}



cocos2d::Acceleration * AccelerationBlok::Parse(Blok * blok)
{
    double * x = (double *) blok->getData();
    double * y = (double *) ( blok->getData() + sizeof(double) );
    double * z = (double *) ( blok->getData() + 2 * sizeof(double) );
    
    cocos2d::Acceleration * acc = new cocos2d::Acceleration();
    acc->x = *x;
    acc->y = *y;
    acc->z = *z;
    return acc;
}