#ifndef  _NewPlayerHandler_H_
#define  _NewPlayerHandler_H_

#include "cocos2d.h"
#include "Connector.h"
#include "Box.h"
#include "BoxHandler.h"
#include "Game.h"

#include <string>

// TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TADY

class NewPlayerHandler: public BoxHandler{
public:
    
    NewPlayerHandler(Game * game){
        this->game = game;
    }
    
    void execute(GameNet::Box * box){
        
        CCLOG("New player: %s", box->getData().c_str() );
        // game->addPlayer(
    }
    
private:
    
    Game * game;
};

#endif // _NewPlayerHandler_H_