//
//  ServerNameHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ServerNameHandler_hpp
#define ServerNameHandler_hpp

#include "AbstractHandlers.h"
#include "MenuManager.h"

class ServerNameHandler: public BoxHandler{
public:

    ServerNameHandler(MenuManager * manager);
    
    virtual void execute( GameNet::Box * box );
    
private:
    
    MenuManager * menuManager;
};

#endif /* ServerNameHandler_hpp */
