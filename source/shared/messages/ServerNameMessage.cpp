//
//  ServerNameMessage.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 18.02.16.
//

#include "ServerNameMessage.h"

using namespace GameNet;

std::string ServerNameMessage::serialize()
{
    std::string s = "\0\0\0\0"; // empty timestamp
    return s + getServerName();
}

bool ServerNameMessage::deserialize(std::string str)
{
    if(str.length() < 4){
        return false;
    }
    
    // exclude 4 bytes (RakNet timestamp)
    this->str = std::string(str);
    this->str.erase(0,4);
    
    return true;
}

std::string ServerNameMessage::getServerName()
{
    return this->str;
}