//
//  KickBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "KickBlok.h"



Blok * KickBlok::create()
{
    Blok * blok = Blok::create(nullptr, 0); // empty data
    blok->setType(P_KICK);
    blok->setReliability(PacketReliability::RELIABLE);
    blok->setPriority(PacketPriority::HIGH_PRIORITY);
    return blok;
}