//
//  ServerNameUpdateHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ServerNameUpdateHandler_h
#define ServerNameUpdateHandler_h

#include "AbstractHandlers.h"
#include "Connector.h"
#include "Controller.h"

using namespace GameNet;

/**
 * Class that processes user's attempt to ServerNameUpdate from the server
 */
class ServerNameUpdateHandler: public StringHandler{
public:

    ServerNameUpdateHandler();
    
    /**
     * return to the main menu
     */
    virtual void execute(std::string name);
    
private:

    Connector * connector;
    Controller * controller;
};

#endif /* ConnectionLost_h */
