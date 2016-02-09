//
//  ResetScoreBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "ResetScoreBlok.h"



Blok * ResetScoreBlok::create()
{
    Blok * blok = Blok::create(nullptr, 0); // empty data
    blok->setType(P_RESET_SCORE);
    blok->setReliability(PacketReliability::RELIABLE);
    blok->setPriority(PacketPriority::LOW_PRIORITY);
    blok->setAddress( Connector::getInstance()->getServer() );
    return blok;
}