#ifndef  _ExitGameHandler_H_
#define  _ExitGameHandler_H_

#include "AbstractHandlers.h"
class Game;

class ExitGameHandler: public VoidHandler{
public:
    
    ExitGameHandler();
    
    virtual void execute();
    
private:
    Game * game;
};


#endif // _ExitGameHandler_H_