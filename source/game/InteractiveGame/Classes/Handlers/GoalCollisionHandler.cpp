#include "GoalCollisionHandler.h"
#include "GameplayDefinitions.h"
#include "Connector.h"
#include "BoxFactory.h"

USING_NS_CC;

GoalCollisionHandler::GoalCollisionHandler()
{
    game = Game::getInstance();
    director = Director::getInstance();
}

void GoalCollisionHandler::execute(cocos2d::PhysicsBody * first, cocos2d::PhysicsBody * second)
{
    // physics bodies
    goal = first;
    ball = second;
    
    // score detection
    if( ball->getCategoryBitmask() & BITMASK_BALL ) // the ball is in the goal
    {
        int goalSide = goal->getNode()->getTag();
        CCLOG("GOOAAAALLL to %s", (goalSide==Definitions::LEFT) ?  "left" : "right" );
        
        // add points
        Label * lbl = static_cast<Label*>( game->getStadium()->getChildByName( (goalSide == Definitions::LEFT) ? LABEL_SCORE_RIGHT : LABEL_SCORE_LEFT ) );
        int score = __String::create( lbl->getString() )->intValue();
        score++;
        lbl->setString( __String::createWithFormat("%d", score)->getCString() );
        
        // score animation and ball position reset
        scoreSequence(goalSide);
    }
}



void GoalCollisionHandler::scoreSequence(int side)
{
    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();
    
    // disable collision with goal
    // players can't interact with the ball until it is moved to center
    game->getStadium()->setBallKickable(false);
    
    // GOAAAL label
    auto lblGoal = game->getStadium()->getChildByName<Label*>(LABEL_GOAL_ANIMATION);
    lblGoal->setAnchorPoint(Vec2(0.5, 0.5));
    lblGoal->setPosition(POSITION_CENTER);
    lblGoal->setOpacity(255);
    lblGoal->setScale(1);
    game->getStadium()->addChild(lblGoal);
    
    // animate the label
    auto scale = ScaleTo::create(TIME_GOAL_ANIMATION, 4);
    auto fade = FadeOut::create(TIME_GOAL_ANIMATION);
    auto spawn = Spawn::create(scale, fade, nullptr);
    lblGoal->runAction(spawn);
    
    // reset the ball
    auto disablePhysics = CallFunc::create([&]()
    {
        ball->setVelocity(Vec2::ZERO);
        ball->setAngularVelocity(0);
    });
    auto enable = CallFunc::create([&]()
    {
        game->getStadium()->setBallKickable(true);
    });
    auto delay = DelayTime::create(TIME_BALL_RESET_DELAY);
    auto center = MoveTo::create(TIME_BALL_CENTER, POSITION_CENTER);
    auto ease = EaseInOut::create(center, 2);
    auto sequence = Sequence::create(delay, disablePhysics, ease, enable, nullptr);
    ball->getNode()->runAction(sequence);
    
}