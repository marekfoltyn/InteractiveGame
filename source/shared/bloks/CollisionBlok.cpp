//
//  ServerNameBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "CollisionBlok.h"



Blok * CollisionBlok::create()
{
    Blok * blok = Blok::create(nullptr, 0);
    blok->setType(P_COLLISION);
    blok->setReliability(PacketReliability::RELIABLE);
    blok->setPriority(PacketPriority::HIGH_PRIORITY);
    return blok;
}