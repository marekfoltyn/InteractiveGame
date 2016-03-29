//
//  StartGameHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef StartGameHandler_h
#define StartGameHandler_h

#include "AbstractHandlers.h"
#include "Connector.h"
#include "Controller.h"

using namespace GameNet;

/**
 * Class that processes user's attempt to start the game
 */
class StartGameHandler: public VoidHandler{
public:

    StartGameHandler();
    
    /**
     * begin the game
     */
    virtual void execute();
    
private:

    Connector * connector;
    Controller * controller;
};

#endif /* ConnectionLost_h */
