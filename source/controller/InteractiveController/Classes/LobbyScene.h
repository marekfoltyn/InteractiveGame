#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "Connector.h"

class LobbyScene : public cocos2d::Layer
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene * createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LobbyScene);
    
    // load and set up cocos nodes and graphics
    void initGraphics();
    
    // send information to server
    void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);
    
    /**
     * receive Block processing loop
     * receives until RakNet returns 0 (empty packet queue)
     */
    void receiveAllBlocks();
    
    void onConnectionLost(Blok * block);
    
private:
    
    cocos2d::Label * lblX;
    cocos2d::Label * lblY;
    cocos2d::Label * lblZ;
    
    cocos2d::RepeatForever * receivePacketAction;

};

#endif // __LOBBY_SCENE_H__
