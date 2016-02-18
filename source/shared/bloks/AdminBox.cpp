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
    Box * box = Box::createEmpty(); 
    box->setType(P_ADMIN);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    return box;
}