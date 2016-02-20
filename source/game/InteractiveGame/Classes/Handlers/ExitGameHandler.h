#ifndef  _ExitGameHandler_H_
#define  _ExitGameHandler_H_

#include "VoidHandler.h"
class Game; // forward declaration - avoiding circular dependency

class ExitGameHandler: public VoidHandler{
public:
    
    ExitGameHandler(Game * game){
        this->game = game;
    };
    
    virtual void execute(void * data = nullptr);
    
private:
    Game * game;
};


#endif // _ExitGameHandler_H_