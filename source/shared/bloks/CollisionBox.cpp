//
//  ServerNameBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "CollisionBox.h"

using namespace GameNet;

Box * CollisionBox::create()
{
    Box * box = Box::createEmpty();
    box->setType(P_COLLISION);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::HIGH_PRIORITY);
    return box;
}