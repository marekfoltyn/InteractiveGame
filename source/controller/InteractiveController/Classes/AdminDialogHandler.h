//
//  AdminDialogHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef AdminDialogHandler_hpp
#define AdminDialogHandler_hpp

#include "AbstractHandlers.h"
#include "cocos2d.h"
#include "Connector.h"
#include "Controller.h"
#include "HandlerMap.h"

/**
 * Class that show admin dialog
 */
class AdminDialogHandler: public VoidHandler{
public:

    AdminDialogHandler(HandlerMap * handlerMap);
    
    /**
     * return to the main menu
     */
    virtual void execute();
    
private:
    
    cocos2d::Director * director;
    GameNet::Connector * connector;
    Controller * controller;
    HandlerMap * handlerMap;
};

#endif /* ConnectionLost_h */
