//
//  ServerNameHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ServerNameHandler_h
#define ServerNameHandler_h

#include "AbstractHandlers.h"
#include "Controller.h"

class ServerNameHandler: public BoxHandler{
public:

    ServerNameHandler();
    
    virtual void execute( GameNet::Box * box );
    
private:
    
    Controller * controller;
    
};

#endif /* ServerNameHandler_h */
