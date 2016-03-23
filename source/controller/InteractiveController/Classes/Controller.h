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
#include "GameState.pb.h"

/**
 * singleton class controlling base processes in the application
 * - networking setup
 * - getting running scene
 * - options
 * - ...
 */
class Controller{
public:
    
    static Controller * getInstance();
    
    /**
     * start RakNet interface
     * returns false if there is a network error
     */
    bool startNetworking();
    
    /**
     * receive boxes and executes handlers from the handlerMap
     */
    void receiveBoxes(HandlerMap * handlerMap);
    
    /**
     * saves vibrate options
     */
    void setVibrate(bool set);
    
    /**
     * returns true if there is vibration enabled in user options
     * false otherwise
     */
    bool isVibrateEnabled();
    
    /**
     * template method
     * returns true if the running class is an instance of type T
     */
    template<class T>
    bool isRunning()
    {
        return getScene<T>() != nullptr;
    }
    
    /**
     * template method
     * returns the running class (if it is an instance of T)
     * if it is not instance of T, returns nullptr
     */
    template<class T>
    T * getScene()
    {
            return director->getRunningScene()->getChildByTag<T*>(T::SCENE_TAG);
    }
    
    /**
     * when admin box received, set this controller as an admin
     */
    void setAdmin(bool admin);
    
    /**
     * check if this player is an admin
     */
    bool isAdmin(){return admin;}
    
    GameState gameState;
    
private:
    
    static Controller * instance;
    cocos2d::Director * director;
    GameNet::Connector * connector;
    bool admin;
    
    
    
    /**
     * singleton - private constructor
     */
    Controller();

};

#endif /* Controller_hpp */
