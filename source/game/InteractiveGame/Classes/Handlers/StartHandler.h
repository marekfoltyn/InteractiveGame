//
//  StartHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef StartHandler_h
#define StartHandler_h

#include "Game.h"
#include "AbstractHandlers.h"

/**
 * First handler responsible for the application initialization,
 * network start and game setup
 */
class StartHandler: public VoidHandler{
public:
    
    StartHandler(Game * game, Director * director);
    
    /**
     * start networking and the Game
     */
    void execute();
    
private:
    
    Game * game;
    Director * director;
    
};

#endif /* StartHandler_h */
