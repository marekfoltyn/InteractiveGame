//
//  ServerNameBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef ServerNameBox_h
#define ServerNameBox_h

#include <string>
#include "Connector.h"

using namespace GameNet;

class ServerNameBox{
public:
    
    /**
     * parse the string
     */
    static std::string parseServerName(Box * box);
        
};


#endif /* ServerNameBox_h */
