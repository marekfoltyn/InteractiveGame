//
//  KickBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "KickBox.h"

using namespace GameNet;

Box * KickBox::create()
{
    Box * box = Box::create(nullptr, 0); // empty data
    box->setType(P_KICK);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::HIGH_PRIORITY);
    return box;
}