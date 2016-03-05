//
//  ConnectedHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ConnectionLost_hpp
#define ConnectionLost_hpp

#include "AbstractHandlers.h"

class ConnectionLostHandler: public BoxHandler{
public:

    ConnectionLostHandler();
    
    virtual bool execute( GameNet::Box * box );
    
private:
    
};

#endif /* ConnectionLost_h */
