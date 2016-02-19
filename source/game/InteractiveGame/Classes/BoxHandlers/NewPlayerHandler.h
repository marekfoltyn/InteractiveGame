#ifndef  _ExitGameHandler_H_
#define  _ExitGameHandler_H_

#include "cocos2d.h"
#include "Connector.h"
#include "Box.h"
#include "BoxHandler.h"
#include "Game.h"

#include <string>

class ExitGameHandler: public Handler{
public:
    
    ExitGameHandler(Game * game){
        this->game = game;
    }
    
    void execute(){
        game->end();
    }
    
private:
    
    Game * game;
};

#endif // _ExitGameHandler_H_