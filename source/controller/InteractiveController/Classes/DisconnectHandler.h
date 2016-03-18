//
//  ConnectedHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef DisconnectHandler_hpp
#define DisconnectHandler_hpp

#include "cocos2d.h"
#include "Connector.h"
#include "AbstractHandlers.h"

/**
 * Class that processes user's attempt to disconnect from the server
 */
class DisconnectHandler: public VoidHandler{
public:

    DisconnectHandler();
    
    /**
     * return to the main menu
     */
    virtual void execute();
    
private:
    
    cocos2d::Director * director;
    GameNet::Connector * connector;
};

#endif /* ConnectionLost_h */
