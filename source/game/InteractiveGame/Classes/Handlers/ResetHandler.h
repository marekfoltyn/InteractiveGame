#ifndef  _ResetHandler_H_
#define  _ResetHandler_H_

#include "AbstractHandlers.h"
class Game; // forward declaration - avoiding circular dependency

class ResetHandler: public BoxHandler{
public:
    
    ResetHandler(Game * game){
        this->game = game;
    };
    
    virtual bool execute(GameNet::Box * box);
    
private:
    Game * game;
};


#endif // _ResetHandler_H_