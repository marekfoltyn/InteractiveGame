#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#include "RakPeerInterface.h"
#include "Box.h"
#include "Game.h"
#include "Player.h"

using namespace GameNet;

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
    
    void onAccelerationBox(Box * box);
    
    void onPlayerKick(Box * box);
    
    void onPlayerTackle(Box * box);
    
    /**
     * Exit game
     */
    void btnExitClicked(Ref * sender);

    
private:
    
    Game * game;
    
    cocos2d::PhysicsWorld * sceneWorld;
    
    std::map<int, Player * > players;
    
    cocos2d::Sprite * point;

    void setPhysicsWorld(cocos2d::PhysicsWorld * world){ sceneWorld = world; }
    
    // start the server stuff
    void initServer();
    
    // start the graphics stuff
    void initGUI();
    
    void setDebugOutputEnabled(bool enabled);
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    
    cocos2d::Vec2 prevForce;
};

#endif // __LOBBY_SCENE_H__
