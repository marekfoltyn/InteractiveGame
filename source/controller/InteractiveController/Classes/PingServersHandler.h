//
//  PingServersHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef PingServersHandler_h
#define PingServersHandler_h

#include "Controller.h"
#include "AbstractHandlers.h"

class PingServersHandler: public VoidHandler{
public:
    
    PingServersHandler();
    
    void execute();
    
private:
    
    Controller * controller;
    Director * director;
    
};

#endif /* PingServersHandler_h */
