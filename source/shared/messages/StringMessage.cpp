//
//  StringMessage.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 18.02.16.
//

#include "StringMessage.h"

using namespace GameNet;

std::string StringMessage::serialize()
{
    return getString();
}

bool StringMessage::deserialize(std::string str)
{
    this->str = std::string(str);
    return true;
}

std::string StringMessage::getString()
{
    return str;
}