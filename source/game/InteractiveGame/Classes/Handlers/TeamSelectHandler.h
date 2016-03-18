#ifndef  _TeamSelectHandler_H_
#define  _TeamSelectHandler_H_

#include "Box.h"
#include "AbstractHandlers.h"
#include <string>
class Game;

class TeamSelectHandler: public BoxHandler{
public:
    
    TeamSelectHandler(Game * game)
    {
        this->game = game;
    }
    
    bool execute(GameNet::Box * box);
    
private:
    
    Game * game;
};

#endif // _TeamSelectHandler_H_