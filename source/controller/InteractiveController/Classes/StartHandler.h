//
//  StartHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef StartHandler_h
#define StartHandler_h

#include "Controller.h"
#include "AbstractHandlers.h"

/**
 * First handler responsible for the application initialization,
 * network start and first scene setup
 */
class StartHandler: public VoidHandler{
public:
    
    StartHandler();
    
    /**
     * start networking and show the first scene
     */
    void execute();
    
private:
    
    Controller * controller;
    Director * director;
    
    void showMainMenu();
};

#endif /* StartHandler_h */
