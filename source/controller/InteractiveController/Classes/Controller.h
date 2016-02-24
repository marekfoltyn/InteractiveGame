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
#include "BoxHandler.h"

class Controller{
public:
    static Controller * getInstance();
    
    void run();
    
    void runMainMenu();
    
    //end();
    
    //void switchScene(SceneEnum scene)
    
    //
    
private:
    static Controller * instance;
    cocos2d::Director * director;
    GameNet::Connector * connector;
    
    std::map<int, BoxHandler *> boxHandlerMap;
    
    Controller();
    
    bool startNetworking();
    
    void registerHandlers();
    
    void receiveBoxes();

};

#endif /* Controller_hpp */
