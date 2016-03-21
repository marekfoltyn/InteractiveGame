//
//  CollisionBoxHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef CollisionBoxHandler_hpp
#define CollisionBoxHandler_hpp

#include "AbstractHandlers.h"
#include "Controller.h"

/**
 * General collision event - just vibrate
 */
class CollisionBoxHandler: public BoxHandler{
public:

    CollisionBoxHandler();
    
    /**
     * just vibrate
     */
    virtual bool execute( GameNet::Box * box );
    
private:
  
    Controller * controller;
};

#endif /* CollisionBoxHandler_h */
