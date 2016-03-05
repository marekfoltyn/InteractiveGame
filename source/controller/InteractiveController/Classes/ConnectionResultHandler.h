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

/**
 * Handler processing connection results (success, fail)
 */
class ConnectionResultHandler: public BoxHandler{
public:

    ConnectionResultHandler(MainMenuScene * scene);
    
    /**
     * process the connection result
     * success - show select team scene
     * fail - tell the MainMenuScene
     */
    virtual bool execute( GameNet::Box * box );
    
private:
  
    Director * director;
    MainMenuScene * scene;
    
};

#endif /* ConnectionResult_h */
