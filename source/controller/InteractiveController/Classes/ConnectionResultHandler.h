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

class MainMenuScene;

class ConnectionResultHandler: public BoxHandler{
public:

    ConnectionResultHandler(MainMenuScene * scene);
    
    virtual bool execute( GameNet::Box * box );
    
private:
  
    Director * director;
    MainMenuScene * scene;
    
};

#endif /* ConnectionResult_h */
