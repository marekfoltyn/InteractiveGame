//
//  ConnectedHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ConnectionResult_hpp
#define ConnectionResult_hpp

#include "AbstractHandlers.h"

class ConnectionResultHandler: public BoxHandler{
public:

    ConnectionResultHandler();
    
    virtual void execute( GameNet::Box * box );
    
private:
    
};

#endif /* ConnectionResult_h */
