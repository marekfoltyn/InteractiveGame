//
//  GameStateHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef GameState_h
#define GameState_h

#include "AbstractHandlers.h"
#include "Game.h"

/**
 * Processing GameState changes
 */
class GameStateHandler: public BoxHandler{
public:

    GameStateHandler();
    
    /**
     * process game state changes
     */
    virtual bool execute( GameNet::Box * box );
    
private:
  
    Director * director;
    Game * game;
    GameState state;
    
    void updateName();
};

#endif /* GameState_h */
