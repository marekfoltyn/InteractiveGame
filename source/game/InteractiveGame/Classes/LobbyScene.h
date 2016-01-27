#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "RakPeerInterface.h"

class LobbyScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LobbyScene);
    
    void processBlock();
    
    void onAccelerationBlock(Block * block);
    
private:
    
    cocos2d::Sprite * point;
    
    // start the server stuff
    void initServer();
    
    // start the graphics stuff
    void initGUI();
    
    void setDebugOutputEnabled(bool enabled);
};

#endif // __LOBBY_SCENE_H__
