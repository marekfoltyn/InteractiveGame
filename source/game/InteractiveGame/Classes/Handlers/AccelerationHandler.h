#ifndef  _AccelerationHandler_H_
#define  _AccelerationHandler_H_

#include "Box.h"
#include "BoxHandler.h"
#include <string>
class Game; // avoid circular dependency

class AccelerationHandler: public BoxHandler{
public:
    
    AccelerationHandler(Game * game)
    {
        this->game = game;
    }
    
    void execute(GameNet::Box * box);
    
private:
    
    Game * game;
};

#endif // _AccelerationHandler_H_