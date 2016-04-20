//
//  CountdownHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef CountdownHandler_h
#define CountdownHandler_h

#include "AbstractHandlers.h"
class Game;

/**
 * coundown finish processing
 */
class CountdownHandler: public VoidHandler{
public:
    
    CountdownHandler(Game *);
    
    /**
     * Match countdown finished
     */
    void execute();
    
private:
    
    Game * game;
    
};

#endif /* CountdownHandler_h */
