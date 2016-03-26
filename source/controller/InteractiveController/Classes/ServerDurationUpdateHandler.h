//
//  ServerDurationUpdateHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ServerDurationUpdateHandler_h
#define ServerDurationUpdateHandler_h

#include "AbstractHandlers.h"
#include "Connector.h"
#include "Controller.h"

using namespace GameNet;

/**
 * Class that processes user's attempt to ServerDurationUpdate from the server
 */
class ServerDurationUpdateHandler: public StringHandler{
public:

    ServerDurationUpdateHandler();
    
    /**
     * return to the main menu
     */
    virtual void execute(std::string duration);
    
private:

    Connector * connector;
    Controller * controller;
    
    GameState_MatchDuration stringToDuration(std::string strDuration);
};

#endif /* ConnectionLost_h */
