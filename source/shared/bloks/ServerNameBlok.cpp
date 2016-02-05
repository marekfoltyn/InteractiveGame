//
//  ServerNameBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "ServerNameBlok.h"



std::string ServerNameBlok::parseServerName(Blok * blok)
{
    return std::string( blok->getData()+sizeof(RakNet::TimeMS) ); // skip ping timestamp
}