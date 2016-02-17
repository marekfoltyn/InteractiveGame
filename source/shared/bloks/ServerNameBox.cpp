//
//  ServerNameBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "ServerNameBox.h"

using namespace GameNet;

std::string ServerNameBox::parseServerName(Box * box)
{
    return std::string( box->getData()+sizeof(RakNet::TimeMS) ); // skip ping timestamp
}