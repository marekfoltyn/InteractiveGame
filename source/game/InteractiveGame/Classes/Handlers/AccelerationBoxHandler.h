#ifndef  _AccelerationHandler_H_
#define  _AccelerationHandler_H_

#include "Box.h"
#include "AbstractHandlers.h"
#include <string>
class Game; // avoid circular dependency

class AccelerationBoxHandler: public BoxHandler{
public:
    
    AccelerationBoxHandler(Game * game)
    {
        this->game = game;
    }
    
    void execute(GameNet::Box * box);
    
private:
    
    Game * game;
};

#endif // _AccelerationHandler_H_