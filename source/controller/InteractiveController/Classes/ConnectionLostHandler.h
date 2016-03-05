//
//  ConnectedHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ConnectionLost_hpp
#define ConnectionLost_hpp

#include "cocos2d.h"
#include "AbstractHandlers.h"

/**
 * Class that responds when the connection is lost
 * returns to the main menu and shows the dialog
 * "Connection lost."
 */
class ConnectionLostHandler: public BoxHandler{
public:

    ConnectionLostHandler();
    
    /**
     * return to the main menu and show the dialog
     * "Connection lost."
     */
    virtual bool execute( GameNet::Box * box );
    
private:
    
    cocos2d::Director * director;
};

#endif /* ConnectionLost_h */
