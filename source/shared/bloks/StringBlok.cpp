//
//  StringBlok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "StringBlok.h"



std::string StringBlok::parseString(Blok * blok)
{
    return std::string( blok->getData() );
}

Blok * StringBlok::create(std::string str)
{
    auto blok = Blok::create(str.c_str(), (unsigned int) str.length() );
    return blok;
}