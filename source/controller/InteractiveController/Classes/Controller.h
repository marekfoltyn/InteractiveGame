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
#include "StadiumScene.h"

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
    
    /**
     * returns server name, if it is known,
     * "" otherwise
     */
    std::string getServerName();
    
    /**
     * set the server name received from server
     */
    void setServerName(std::string name);
    
    /**
     * stadium scene getter
     */
    StadiumScene * getStadium(){ return stadium; }
    
    /**
     * show stadium scene
     * using cocos2d scene stack
     * and pushes the StadiumScene on top
     */
    void pushStadium();
    
    /**
     * hide stadium scene
     * before this call, pushStadium() must be called!
     * removes the StadiumScene from the scene stack
     */
    void popStadium();
    
    /**
     * protobuf game state
     */
    GameState gameState;
    
    void setTeam(std::string team){ this->team = team; }
    std::string getTeam(){return team; }
    
    /**
     * speed scale getter / setter
     */
    float getSpeedScale(){return speedScale;}
    void setSpeedScale(float scale);
    
private:
    
    /**
     * singleton instance
     */
    static Controller * instance;
    
    /**
     * cocos2d game director
     */
    cocos2d::Director * director;
    
    /**
     * gamenet director
     */
    GameNet::Connector * connector;
    
    /**
     * stadium instance for invisibility bonus
     */
    StadiumScene * stadium;
    
    /**
     * stadium scene required for scene replace
     * by cocos2d::Director
     */
    Scene * directorStadium;
    
    /**
     * indicator if this player is the game admin
     */
    bool admin;
    
    /**
     * team of this phone
     */
    std::string team;
    
    /**
     * speed scale factor
     * - used when loading a kick
     */
    float speedScale;
    
    /**
     * singleton - private constructor
     */
    Controller();

};

#endif /* Controller_hpp */
