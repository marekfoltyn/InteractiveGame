#ifndef  _TackleHandler_H_
#define  _TackleHandler_H_

#include "Box.h"
#include "BoxHandler.h"
#include <string>
class Game; // avoid circular dependency

class TackleHandler: public BoxHandler{
public:
    
    TackleHandler(Game * game)
    {
        this->game = game;
    }
    
    void execute(GameNet::Box * box);
    
private:
    
    Game * game;
};

#endif // _TackleHandler_H_