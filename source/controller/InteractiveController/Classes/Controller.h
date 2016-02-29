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

class Controller{
public:
    
    static Controller * getInstance();
    
    bool startNetworking();
    
private:
    
    static Controller * instance;
    cocos2d::Director * director;
    GameNet::Connector * connector;
    HandlerMap * handlerMap;
    
    Controller();
    
    void receiveBoxes();

};

#endif /* Controller_hpp */
