//
//  StringBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef StringBox_h
#define StringBox_h

#include <string>
#include "Connector.h"

using namespace GameNet;

class StringBox{
public:
    
    /**
     * parse the string
     */
    static std::string parseString(Box * box);
    
    /**
     * create StringBox from string
     */
    static Box * create(std::string str);
    
};


#endif /* StringBox_h */
