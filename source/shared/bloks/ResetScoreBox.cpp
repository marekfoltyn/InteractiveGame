//
//  ResetScoreBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "ResetScoreBox.h"

using namespace GameNet;

Box * ResetScoreBox::create()
{
    Box * box = Box::createEmpty();
    box->setType(P_RESET_SCORE);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    box->setAddress( Connector::getInstance()->getServer() );
    return box;
}