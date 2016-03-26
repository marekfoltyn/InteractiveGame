//
//  ServerSizeUpdateHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ServerSizeUpdateHandler_h
#define ServerSizeUpdateHandler_h

#include "AbstractHandlers.h"
#include "Connector.h"
#include "Controller.h"

using namespace GameNet;

/**
 * Class that processes user's attempt to ServerSizeUpdate from the server
 */
class ServerSizeUpdateHandler: public StringHandler{
public:

    ServerSizeUpdateHandler();
    
    /**
     * return to the main menu
     */
    virtual void execute(std::string name);
    
private:

    Connector * connector;
    Controller * controller;
    
    GameState_PitchSize stringToSize(std::string strSize);
};

#endif /* ConnectionLost_h */
