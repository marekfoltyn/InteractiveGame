//
//  StopGameHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef StopGameHandler_h
#define StopGameHandler_h

#include "AbstractHandlers.h"
#include "Connector.h"
#include "Controller.h"

using namespace GameNet;

/**
 * Class that processes user's attempt to stop the game
 */
class StopGameHandler: public VoidHandler{
public:

    StopGameHandler();
    
    /**
     * begin the game
     */
    virtual void execute();
    
private:

    Connector * connector;
    Controller * controller;
};

#endif /* ConnectionLost_h */
