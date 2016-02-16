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
    std::string s = str;
    auto blok = Blok::create(s.c_str(), static_cast<unsigned int>(s.length() + 1) ); // empty char
    return blok;
}