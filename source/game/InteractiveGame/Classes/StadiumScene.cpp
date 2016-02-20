#include <string>

#include "StadiumScene.h"

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "Definitions.h"
#include "GameDefinitions.h"
#include "Connector.h"
#include "Box.h"
#include "BoxFactory.h"
#include "AccelerationMessage.h"

#include "GameDefinitions.h"

using namespace cocos2d;

Scene * StadiumScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

#ifdef DEBUG
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
#else
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_NONE );
#endif
    
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    
    // 'layer' is an autorelease object
    auto layer = StadiumScene::create();
    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    layer->setTag(SCENE_TAG);
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StadiumScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);

    // collision listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(StadiumScene::collision, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void StadiumScene::addCollisionHandler(int bitmask, CollisionHandler * handler)
{
    collisions[bitmask] = handler;
}



bool StadiumScene::collision( cocos2d::PhysicsContact &contact )
{
    PhysicsBody * a[2];
    a[0] = contact.getShapeA()->getBody();
    a[1] = contact.getShapeB()->getBody();
    
    for(int i=0; i<2; i++)
    {
        int bitmask = a[i]->getCategoryBitmask();
        auto iterator = collisions.find(bitmask);
        if(iterator != collisions.end())
        {
            iterator->second->execute( a[i], a[ (i+1)%2 ] ); // i==0 -> 1, i==1 -> 0
        }
        
    }
        
    // score detection
    for(int i=0; i<2; i++)
    {
        if( a[i]->getCategoryBitmask() & BITMASK_SCORE ) // the ball in the goal
        {
            int goalSide = a[i]->getNode()->getTag();
            CCLOG("GOOAAAALLL to %s", (goalSide==GameDefinitions::LEFT) ?  "left" : "right" );
            
            // add points
            Label * lbl = static_cast<Label*>( this->getChildByName( (goalSide == GameDefinitions::LEFT) ? LABEL_SCORE_RIGHT : LABEL_SCORE_LEFT ) );
            int score = __String::create( lbl->getString() )->intValue();
            score++;
            lbl->setString( __String::createWithFormat("%d", score)->getCString() );
        }
    }
    
    return true;
}
