//
//  AdminBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "AdminBlok.h"



Blok * AdminBlok::create()
{
    Blok * blok = Blok::create(nullptr, 0); // empty data
    blok->setType(P_ADMIN);
    blok->setReliability(PacketReliability::RELIABLE);
    blok->setPriority(PacketPriority::LOW_PRIORITY);
    return blok;
}