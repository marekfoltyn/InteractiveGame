//
//  StringMessage.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 18.02.16.
//

#include "AccelerationMessage.h"

using namespace GameNet;

AccelerationMessage::AccelerationMessage()
{
    acc.x = acc.y = acc.z = 0;
}

AccelerationMessage::AccelerationMessage(double x, double y, double z){
    acc.x = x;
    acc.y = y;
    acc.z = z;
}

std::string AccelerationMessage::serialize()
{
    return std::string( (const char *) &acc, sizeof(AccStruct) );
}

bool AccelerationMessage::deserialize(std::string str)
{
    if(str.length() < 3*sizeof(double)){
        // invalid string size
        return false;
    }
    
    const char * data = str.c_str();
    
    acc.x = * (double *) data;
    acc.y = * (double *) ( data + sizeof(double) );
    acc.z = * (double *) ( data + 2 * sizeof(double) );
    
    return true;
}

double AccelerationMessage::getX()
{
    return acc.x;
}

double AccelerationMessage::getY()
{
    return acc.y;
}

double AccelerationMessage::getZ()
{
    return acc.z;
}
