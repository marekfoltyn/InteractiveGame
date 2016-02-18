//
//  TackleBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "TackleBox.h"

using namespace GameNet;

Box * TackleBox::create()
{
    Box * box = Box::createEmpty(); // empty data
    box->setType(P_TACKLE);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::HIGH_PRIORITY);
    return box;
}