#ifndef  _BoxHandler_H_
#define  _BoxHandler_H_

#include "Box.h"

/**
 * An abstract class
 */
class BoxHandler {
public:

    virtual void execute( GameNet::Box * box ) = 0;
    
    ~BoxHandler(){}
};

#endif // _Message_H_