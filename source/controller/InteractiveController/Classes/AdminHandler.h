//
//  ConnectedHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef Admin_hpp
#define Admin_hpp

#include "AbstractHandlers.h"

class LobbyScene;

/**
 * Processing admin attaching
 */
class AdminHandler: public BoxHandler{
public:

    AdminHandler(LobbyScene * scene);
    
    /**
     * set this player as the admin
     */
    virtual bool execute( GameNet::Box * box );
    
private:
  
    Director * director;
    LobbyScene * scene;
    
};

#endif /* Admin_h */
