//
//  Controller.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 24.02.16.
//
//

#ifndef Controller_hpp
#define Controller_hpp

#include "Connector.h"
#include "HandlerMap.h"
#include "MenuManager.h"

class Controller{
public:
    static Controller * getInstance();
    
    void run();
        
    //end();
    
private:
    static Controller * instance;
    cocos2d::Director * director;
    GameNet::Connector * connector;
    
    HandlerMap * handlerMap;
    
    MenuManager * menuManager;
    //LobbyManager * lobbyManager;
    //GameManager * gameManager;
    
    Controller();
    
    bool startNetworking();
    
    void registerHandlers();
    
    void receiveBoxes();

};

#endif /* Controller_hpp */
