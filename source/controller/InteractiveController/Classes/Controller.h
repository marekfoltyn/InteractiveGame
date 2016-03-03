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
#include "cocos2d.h"

class Controller{
public:
    
    static Controller * getInstance();
    
    bool startNetworking();
    void receiveBoxes(std::shared_ptr<HandlerMap> handlerMap);
    
    void setVibrate(bool set);
    bool isVibrateEnabled();
    
    template<class T>
    bool isRunning()
    {
        return getScene<T>() != nullptr;
    }
    
    template<class T>
    T * getScene()
    {
            return director->getRunningScene()->getChildByTag<T*>(T::SCENE_TAG);
    }
    
private:
    
    static Controller * instance;
    cocos2d::Director * director;
    GameNet::Connector * connector;
    
    Controller();

};

#endif /* Controller_hpp */
