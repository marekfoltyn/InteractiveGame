//
//  StringBlok.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef StringBlok_h
#define StringBlok_h

#include <string>
#include "Connector.h"


class StringBlok{
public:
    
    /**
     * parse the string
     */
    static std::string parseString(Blok * blok);
    
    /**
     * create StringBlok from string
     */
    static Blok * create(std::string str);
    
};


#endif /* StringBlock_h */
