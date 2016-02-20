#ifndef  _ExitGameHandler_H_
#define  _ExitGameHandler_H_

#include "Handler.h"
class Game; // forward declaration - avoiding circular dependency

class ExitGameHandler: public Handler{
public:
    
    ExitGameHandler(Game * game){
        this->game = game;
    };
    
    virtual void execute();
    
private:
    Game * game;
};


#endif // _ExitGameHandler_H_