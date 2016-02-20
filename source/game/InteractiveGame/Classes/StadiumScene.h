#ifndef __STADIUM_SCENE_H__
#define __STADIUM_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#include "RakPeerInterface.h"
#include "Box.h"
#include "Player.h"

#include "CollisionHandler.h"

class StadiumScene : public cocos2d::Layer
{
public:
    
    static const int SCENE_TAG = 1;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(StadiumScene);
    
    void addCollisionHandler(int bitmask, CollisionHandler * handler);
    
private:
    
    cocos2d::PhysicsWorld * sceneWorld;
    
    std::map<int, Player * > players;
    std::map<int, CollisionHandler * > collisions;
    
    cocos2d::Sprite * point;

    void setPhysicsWorld(cocos2d::PhysicsWorld * world){ sceneWorld = world; }
    
    bool collision( cocos2d::PhysicsContact &contact );
};

#endif // __LOBBY_SCENE_H__
