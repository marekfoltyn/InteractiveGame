#ifndef  _KickHandler_H_
#define  _KickHandler_H_

#include "Box.h"
#include "AbstractHandlers.h"
#include <string>
class Game; // avoid circular dependency

class KickHandler: public BoxHandler{
public:
    
    KickHandler(Game * game)
    {
        this->game = game;
    }
    
    bool execute(GameNet::Box * box);
    
private:
    
    Game * game;
};

#endif // _KickHandler_H_