#include <string>

#include "StadiumScene.h"

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "Definitions.h"
#include "GameplayDefinitions.h"
#include "Connector.h"
#include "Box.h"
#include "BoxFactory.h"
#include "AccelerationMessage.h"

#include "GameplayDefinitions.h"



Scene * StadiumScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // no gravity - top view
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);

    // toggle between fullscreen and debug windowed screen
#ifdef DEBUG
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
#else
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_NONE );
#endif
    
    // 'layer' is an autorelease object
    auto layer = StadiumScene::create();
    layer->setTag(SCENE_TAG);
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
} 



bool StadiumScene::init()
{
    //  super init first
    if(!Layer::init())
    {
        return false;
    }
    
    // collision listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(StadiumScene::collision, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    CCLOG("GameScene initialized.");
    return true;
}



void StadiumScene::initPitch(Vec2 newOrigin, cocos2d::Size newVisibleSize)
{
    origin = newOrigin;
    visibleSize = newVisibleSize;
    
    this->removeAllChildren();
    
    // background color
    auto background = Sprite::create("grass.png");
    background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(background);
    
    // center circle
    auto line = Sprite::create("center.png");
    line->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(line);
    
    //  compute scale based on visibleSize
    float scaleX = visibleSize.width  / 100.0 - 2.0*BORDER/100.0;
    float scaleY = visibleSize.height / 100.0 - 2.0*BORDER/100.0;
    
    // center line
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(line);
    
    // top line
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height - BORDER));
    this->addChild(line);
    
    // bottom line
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,0));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + BORDER));
    this->addChild(line);
    
    // left line
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,0));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height - BORDER));
    this->addChild(line);
    
    // right line
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER, origin.y + visibleSize.height - BORDER ));
    this->addChild(line);
    
    // line.jpg is 100px wide
    scaleX = visibleSize.width/800;
    scaleY *= 0.5;
    
    // left lines near the goal
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height/2 - scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER + scaleX*100, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    
    // right lines near the goal
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER - scaleX*100, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER - scaleX*100, origin.y + visibleSize.height/2 - scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,0));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER - scaleX*100, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    
    // left goal
    auto goal = Sprite::create("goal.png");
    goal->setScale(SCALE_GOAL);
    goal->setAnchorPoint(Vec2(0,0.5));
    goal->setPosition(Vec2( origin.x, origin.y + visibleSize.height/2));
    this->addChild(goal, 2);
    
    // right goal
    goal = Sprite::create("goal.png");
    goal->setRotation(180);
    goal->setAnchorPoint(Vec2(0,0.5));
    goal->setScale(SCALE_GOAL);
    goal->setPosition(Vec2( origin.x + visibleSize.width, origin.y + visibleSize.height/2));
    this->addChild(goal, 2);
    
    // goal physics
    // 4 horizontal lines (each goal has two lines - top and down)
    for(int i=0; i<4; i++)
    {
        auto top = Node::create();
        auto body = PhysicsBody::createBox(cocos2d::Size( SCALE_GOAL*goal->getContentSize().width, 10), MATERIAL_SOLID);
        body->setDynamic(false);
        body->setCategoryBitmask(BITMASK_SOLID);
        body->setCollisionBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER);
        body->setContactTestBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER);
        top->setPhysicsBody(body);
        
        // compute line positions based on i (topleft, bottomleft, topright, bottomright)
        top->setPosition(Vec2(
            origin.x + (i>1)*(visibleSize.width) + (1-(i>1)*2)*0.5*SCALE_GOAL*goal->getContentSize().width,
            origin.y + visibleSize.height/2 + (1 - 2*(i%2)) * SCALE_GOAL*(goal->getContentSize().height/2
        )));
        this->addChild(top);
    }
    
    // score point detectors
    for(int i=0; i<2; i++)
    {
        auto size = cocos2d::Size(
            SCALE_GOAL*goal->getContentSize().width - Sprite::create("ball.png")->getContentSize().width*SCALE_BALL,
            SCALE_GOAL*goal->getContentSize().height - Sprite::create("ball.png")->getContentSize().width*SCALE_BALL
        );
        auto top = Node::create();
        auto body = PhysicsBody::createBox(size);
        body->setDynamic(false);
        body->setCategoryBitmask(BITMASK_SCORE);
        body->setCollisionBitmask(0);
        body->setContactTestBitmask(BITMASK_BALL);
        top->setAnchorPoint(Vec2( 0.5, 0.5 ));
        top->setPhysicsBody(body);
        top->setTag(i); // LEFT and RIGHT (#defined)
        top->setPosition(Vec2(
            origin.x + size.width/2 * (1-2*i) + i*(visibleSize.width),
            origin.y + visibleSize.height/2
        ));
        this->addChild(top);
    }
    
    // physics boundary
    auto edgeBody = PhysicsBody::createEdgeBox(cocos2d::Size(visibleSize.width + 4*BORDER, visibleSize.height + 4*BORDER), MATERIAL_SOLID, BORDER);
    edgeBody->setDynamic(false);
    edgeBody->setCategoryBitmask(BITMASK_SOLID);
    edgeBody->setCollisionBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER);
    edgeBody->setContactTestBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    // ball-only physics boundary
    edgeBody = PhysicsBody::createEdgeBox(cocos2d::Size(visibleSize.width, visibleSize.height), MATERIAL_SOLID, BORDER);
    edgeBody->setDynamic(false);
    edgeBody->setCategoryBitmask(BITMASK_BALL_BOUNDARY);
    edgeBody->setCollisionBitmask(BITMASK_BALL);
    edgeBody->setContactTestBitmask(BITMASK_BALL);
    edgeNode = Node::create();
    edgeNode->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    // 4 anti-corner boxes
    for(int i=0; i<4; i++)
    {
        auto box = PhysicsBody::createBox(cocos2d::Size( 90, 90 ));
        box->setDynamic(false);
        box->setCategoryBitmask(BITMASK_BALL_BOUNDARY);
        box->setCollisionBitmask(BITMASK_BALL);
        box->setContactTestBitmask(BITMASK_BALL);
        edgeNode = Node::create();
        edgeNode->setPosition(Vec2( origin.x + (i%2) * visibleSize.width, origin.y + (i>=2) * visibleSize.height ));
        edgeNode->setPhysicsBody(box);
        edgeNode->setRotation(45);
        this->addChild(edgeNode);
    }
    
    // 4 anti corner boxes near goals
    for(int i=0; i<4; i++)
    {
        auto box = PhysicsBody::createBox(cocos2d::Size( 70, 70 ));
        box->setDynamic(false);
        box->setCategoryBitmask(BITMASK_BALL_BOUNDARY);
        box->setCollisionBitmask(BITMASK_BALL);
        box->setContactTestBitmask(BITMASK_BALL);
        edgeNode = Node::create();
        edgeNode->setPosition(Vec2( origin.x + (i%2) * visibleSize.width, origin.y + visibleSize.height/2 + (((i>=2)*2)-1) * goal->getContentSize().height*SCALE_GOAL/2 ));
        edgeNode->setPhysicsBody(box);
        edgeNode->setRotation(45);
        this->addChild(edgeNode);
    }
    
    // score labels
    leftScore = Label::createWithTTF("0", "Vanilla.ttf", 100);
    float circle = Sprite::create("center.png")->getContentSize().width/4;
    leftScore->setPosition(Vec2( - circle + origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    leftScore->setTextColor(COLOR_FONT_TRANSPARENT);
    leftScore->setName(LABEL_SCORE_LEFT);
    this->addChild(leftScore);
    rightScore = Label::createWithTTF("0", "Vanilla.ttf", 100);
    rightScore->setPosition(Vec2( circle + origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    rightScore->setTextColor(COLOR_FONT_TRANSPARENT);
    rightScore->setName(LABEL_SCORE_RIGHT);
    this->addChild(rightScore);
    
    // admin
    lblAdmin = Label::createWithTTF("Admin:", "Vanilla.ttf", 30);
    lblAdmin->setAlignment(TextHAlignment::CENTER);
    lblAdmin->setTextColor(COLOR_FONT_TRANSPARENT);
    lblAdmin->setAnchorPoint(Vec2(0.5, 0));
    lblAdmin->setPosition(Vec2( origin.x + visibleSize.width/2 - circle, origin.y + 2*BORDER ));
    lblAdmin->setVisible(false); // default hidden - toggled by setAdminName()
    this->addChild(lblAdmin,0);
    
    // admin name
    lblAdminName = Label::createWithTTF("", "Vanilla.ttf", 30);
    lblAdminName->setName(LABEL_ADMIN);
    lblAdminName->setAlignment(TextHAlignment::LEFT);
    lblAdminName->setTextColor(COLOR_FONT_TRANSPARENT);
    lblAdminName->setAnchorPoint(Vec2(0, 0));
    lblAdminName->setPosition(Vec2( origin.x + visibleSize.width/2 + BORDER, origin.y + 2*BORDER ));
    this->addChild(lblAdminName,0);
    
    // server name
    lblServerName = Label::createWithTTF("", "Vanilla.ttf", 40);
    lblServerName->setName(LABEL_SERVER_NAME);
    lblServerName->setAlignment(TextHAlignment::LEFT);
    lblServerName->setTextColor(COLOR_FONT_TRANSPARENT);
    lblServerName->setAnchorPoint(Vec2(0, 1));
    lblServerName->setPosition(Vec2( origin.x + 2*BORDER, origin.y + visibleSize.height - 2*BORDER ));
    this->addChild(lblServerName,0);
    
    // ball sprite
    sprBall = Sprite::create("ball.png");
    sprBall->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    sprBall->setScale(SCALE_BALL);
    sprBall->setName(NODE_BALL);
    sprBall->setVisible(false);
    auto spriteBody = PhysicsBody::createCircle( sprBall->getContentSize().width/2, MATERIAL_BALL );
    spriteBody->setCategoryBitmask(BITMASK_BALL);
    spriteBody->setCollisionBitmask(BALL_CONTACTS_WITHOUT_GOAL);
    spriteBody->setContactTestBitmask(BALL_CONTACTS);
    spriteBody->setLinearDamping(BALL_DAMPING);
    spriteBody->setAngularDamping(BALL_DAMPING);
    spriteBody->setTag(StadiumScene::BALL_NORMAL);
    spriteBody->setRotationEnable(true);
    spriteBody->setEnabled(false);
    sprBall->setPhysicsBody(spriteBody);
    this->addChild(sprBall);
    
    // countdown time
    lblTime = Label::createWithTTF("", "Vanilla.ttf", 40);
    lblTime->setName(LABEL_TIME);
    lblTime->setAlignment(TextHAlignment::LEFT);
    lblTime->setTextColor(COLOR_FONT_TRANSPARENT);
    lblTime->setAnchorPoint(Vec2(0, 1));
    lblTime->setPosition(Vec2( origin.x + visibleSize.width/2 + BORDER, origin.y + visibleSize.height - 2*BORDER ));
    this->addChild(lblTime,0);
    
    // GOAAAL label
    lblGoal = Label::createWithTTF("Goal!", "Vanilla.ttf", Definitions::FONT_SIZE_GOAL_ANIMATION);
    lblGoal->setAnchorPoint(Vec2(0.5, 0.5));
    lblGoal->setPosition(POSITION_CENTER);
    lblGoal->setName(LABEL_GOAL_ANIMATION);
    lblGoal->setOpacity(0);
    this->addChild(lblGoal);
    
    // exit button
    // not complete - the rest in showExitButton(...);
    btnExit = ui::Button::create();
    btnExit->setAnchorPoint(Vec2(0.5, 1));
    btnExit->setPosition(Vec2( origin.x + visibleSize.width - 2*BORDER_DEFAULT, origin.y + visibleSize.height - 2*BORDER ));
    btnExit->setTitleText("Exit");
    btnExit->setTitleFontName("Vanilla.ttf");
    btnExit->setTitleFontSize(40);
    btnExit->getTitleRenderer()->setTextColor(COLOR_FONT_TRANSPARENT);
    btnExit->setVisible(false);
    this->addChild(btnExit);
}



void StadiumScene::setMatchMode(bool match, bool animate)
{
    GLubyte opacity = match ? OPACITY_LABELS : 255;
    
    if(!animate)
    {
        leftScore->setOpacity(opacity);
        rightScore->setOpacity(opacity);
        lblAdmin->setOpacity(opacity);
        lblAdminName->setOpacity(opacity);
        lblServerName->setOpacity(opacity);
        lblTime->setOpacity(opacity);
        btnExit->setOpacity(opacity);
        return;
    }
    
    Action * action = FadeTo::create(Definitions::TIME_LABEL_FADE, opacity);
    
    leftScore->runAction(action);
    rightScore->runAction(action->clone());
    lblAdmin->runAction(action->clone());
    lblAdminName->runAction(action->clone());
    lblServerName->runAction(action->clone());
    lblTime->runAction(action->clone());
    btnExit->runAction(action->clone());
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
    CCLOG("Collision.");
    
    return true;
}



void StadiumScene::setAdminName(std::string name)
{
    lblAdminName->setString(name);
    lblAdmin->setVisible( name.length() > 0 );
}



void StadiumScene::setServerName(std::string name)
{
    lblServerName->setString(name);
}



void StadiumScene::resetScore()
{
    leftScore->setString("0");
    rightScore->setString("0");
}



void StadiumScene::addScore(Side side)
{
    Label * label = (side==SIDE_LEFT) ? leftScore : rightScore;
    int score = __String::create( label->getString() )->intValue();
    score++;
    label->setString( __String::createWithFormat("%d", score)->getCString() );
}



void StadiumScene::setScore(Side side, int score)
{
    Label * label = (side==SIDE_LEFT) ? leftScore : rightScore;
    label->setString( __String::createWithFormat("%d", score)->getCString() );
}



int StadiumScene::getScore(Side side)
{
    Label * label = (side==SIDE_LEFT) ? leftScore : rightScore;
    int score = __String::create( label->getString() )->intValue();
    return score;
}



void StadiumScene::goalAnimation()
{
    // GOAAAL label
    lblGoal->setOpacity(255);
    lblGoal->setScale(1);
    
    // animate the label
    auto scale = ScaleTo::create(TIME_GOAL_ANIMATION, 4);
    auto fade = FadeOut::create(TIME_GOAL_ANIMATION);
    auto spawn = Spawn::create(scale, fade, nullptr);
    lblGoal->runAction(spawn);
}



void StadiumScene::setSecondsLeft(int left)
{
    this->secondsLeft = left;
    int minutes = secondsLeft / 60;
    int seconds = secondsLeft % 60;
    std::string text = __String::createWithFormat("%02d:%02d", minutes, seconds)->getCString();
    lblTime->setString(text);
}



int StadiumScene::getSecondsLeft()
{
    return secondsLeft;
}



void StadiumScene::showExitButton(VoidHandler * exitHandler)
{
    btnExit->setVisible(true);
    btnExit->addTouchEventListener([exitHandler](Ref * sender, ui::Widget::TouchEventType type)
    {
        exitHandler->execute();
    });
}



void StadiumScene::setBallKickable(bool kickable)
{
    auto ball = getBall();
    
    if(kickable)
    {
        ball->getPhysicsBody()->setContactTestBitmask(BALL_CONTACTS);
        ball->getPhysicsBody()->setCollisionBitmask(BALL_CONTACTS_WITHOUT_GOAL);
        ball->getPhysicsBody()->setTag(StadiumScene::BALL_NORMAL);
    }
    else
    {
        ball->getPhysicsBody()->setContactTestBitmask(BALL_CONTACTS_AFTER_SCORE);
        ball->getPhysicsBody()->setCollisionBitmask(BALL_CONTACTS_AFTER_SCORE);
        ball->getPhysicsBody()->setTag(StadiumScene::BALL_NON_KICKABLE);
    }
}



void StadiumScene::setBallInGame(bool visible)
{
    sprBall->getPhysicsBody()->setRotationEnable(visible);
    sprBall->getPhysicsBody()->setEnabled(visible);
    sprBall->setVisible(visible);
    
    if(visible)
    {
        sprBall->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
        sprBall->getPhysicsBody()->setVelocity(Vec2::ZERO);
        sprBall->getPhysicsBody()->setAngularVelocity(0);
    }
}













