//
//  AccelerationBlock.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "AccelerationBlock.h"

Block * AccelerationBlock::Create(cocos2d::Acceleration * acc)
{
    AccStruct str;
    str.x = acc->x;
    str.y = acc->y;
    str.z = acc->z;
    
    Block * block = Block::create( (const char *) &str, sizeof(AccStruct) );
    block->setType(P_ACCELERATION);
    block->setPriority(HIGH_PRIORITY);
    block->setReliability(PacketReliability::UNRELIABLE);
    block->setAddress( Connector::getInstance()->getServer() );
    
    return block;
}

cocos2d::Acceleration * AccelerationBlock::Parse(Block * block)
{
    double * x = (double *) block->getData();
    double * y = (double *) ( block->getData() + sizeof(double) );
    double * z = (double *) ( block->getData() + 2 * sizeof(double) );
    
    cocos2d::Acceleration * acc = new cocos2d::Acceleration();
    acc->x = *x;
    acc->y = *y;
    acc->z = *z;
    return acc;
}