//
//  StringBox.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "StringBox.h"

using namespace GameNet;

std::string StringBox::parseString(Box * box)
{
    return std::string( box->getData() );
}


Box * StringBox::create(std::string str)
{
    return Box::create(str);
}