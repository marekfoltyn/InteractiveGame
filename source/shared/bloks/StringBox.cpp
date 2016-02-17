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
    std::string s = str;
    auto box = Box::create(s.c_str(), static_cast<unsigned int>(s.length() + 1) ); // empty char
    return box;
}