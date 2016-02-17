//
//  AdminBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "AdminBox.h"

using namespace GameNet;

Box * AdminBox::create()
{
    Box * box = Box::create(nullptr, 0); // empty data
    box->setType(P_ADMIN);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    return box;
}