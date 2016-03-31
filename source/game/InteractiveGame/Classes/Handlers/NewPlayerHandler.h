#ifndef  _NewPlayerHandler_H_
#define  _NewPlayerHandler_H_

#include "Box.h"
#include "AbstractHandlers.h"
#include <string>
class Game; // avoid circular dependency

class NewPlayerHandler: public BoxHandler{
public:
    
    NewPlayerHandler();
    
    bool execute(GameNet::Box * box);
    
private:
    
    Director * director;
    Game * game;
};

#endif // _NewPlayerHandler_H_