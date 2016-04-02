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
#include "Controller.h"

class ControlScene;

/**
 * Processing admin attaching
 */
class AdminHandler: public BoxHandler{
public:

    AdminHandler(Node * scene);
    
    /**
     * set this player as the admin
     */
    virtual bool execute( GameNet::Box * box );
    
private:
  
    Director * director;
    Controller * controller;
    Node * scene;
    
};

#endif /* Admin_h */
