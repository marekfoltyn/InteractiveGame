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

class StartHandler: public VoidHandler{
public:
    
    StartHandler();
    
    void execute();
    
private:
    
    Controller * controller;
    Director * director;
    
    void showMainMenu();
};

#endif /* StartHandler_h */
