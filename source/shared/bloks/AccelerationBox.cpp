//
//  AccelerationBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "AccelerationBox.h"

using namespace GameNet;

Box * AccelerationBox::Create(cocos2d::Acceleration * acc)
{
    AccStruct str;
    str.x = acc->x;
    str.y = acc->y;
    str.z = acc->z;
    
    Box * box = Box::create( (const char *) &str, sizeof(AccStruct) );
    box->setType(P_ACCELERATION);
    box->setPriority(PacketPriority::HIGH_PRIORITY);
    box->setReliability(PacketReliability::UNRELIABLE);
    
    return box;
}



cocos2d::Acceleration AccelerationBox::Parse(Box * box)
{
    double * x = (double *) box->getData();
    double * y = (double *) ( box->getData() + sizeof(double) );
    double * z = (double *) ( box->getData() + 2 * sizeof(double) );
    
    cocos2d::Acceleration acc = cocos2d::Acceleration();
    acc.x = *x;
    acc.y = *y;
    acc.z = *z;
    return acc;
}