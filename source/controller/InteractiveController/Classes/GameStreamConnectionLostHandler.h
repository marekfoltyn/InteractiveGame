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
#include "StadiumScene.h"

/**
 * Class that responds when the connection is lost
 * returns to the main menu and shows the dialog
 * "Connection lost."
 */
class GameStreamConnectionLostHandler: public BoxHandler{
public:

    GameStreamConnectionLostHandler(StadiumScene * stadium);
    
    /**
     * return to the main menu and show the dialog
     * "Connection lost."
     */
    virtual bool execute( GameNet::Box * box );
    
private:
    
    cocos2d::Director * director;
    StadiumScene * stadium;
};

#endif /* ConnectionLost_h */
