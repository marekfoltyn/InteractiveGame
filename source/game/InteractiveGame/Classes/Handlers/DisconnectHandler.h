#ifndef  _DisconnectHandler_H_
#define  _DisconnectHandler_H_

#include "Box.h"
#include "AbstractHandlers.h"
#include <string>
class Game; // avoid circular dependency

class DisconnectHandler: public BoxHandler{
public:
    
    DisconnectHandler(Game * game)
    {
        this->game = game;
    }
    
    bool execute(GameNet::Box * box);
    
private:
    
    Game * game;
};

#endif // _DisconnectHandler_H_