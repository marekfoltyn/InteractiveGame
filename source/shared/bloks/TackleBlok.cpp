//
//  TackleBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "TackleBlok.h"



Blok * TackleBlok::create()
{
    Blok * blok = Blok::create(nullptr, 0); // empty data
    blok->setType(P_TACKLE);
    blok->setReliability(PacketReliability::RELIABLE);
    blok->setPriority(PacketPriority::HIGH_PRIORITY);
    return blok;
}