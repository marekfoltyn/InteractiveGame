#ifndef  _Handler_H_
#define  _Handler_H_

#include "cocos2d.h"
#include "Connector.h"
#include "Box.h"
#include "BoxHandler.h"
#include "Game.h"

#include <string>

class Handler{
public:
    
    void execute() = 0;
    
};

#endif // _Handler_H_