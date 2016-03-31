//
//  GameStreamHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "GameStreamHandler.h"
#include "GameStreamConnectionLostHandler.h"
#include "BoxFactory.h"
#include "ControlScene.h"
#include "StadiumScene.h"

GameStreamHandler::GameStreamHandler(ControlScene * scene)
{
    director = Director::getInstance();
    controller = Controller::getInstance();
    handlerMap = HandlerMap::create();
    playerMap = std::map<int, Player *>();
    timer = Util::Timer();
}

bool GameStreamHandler::execute( GameNet::Box * box )
{
    bool stop = false;
    auto stream = PBGameStream();
    auto message = box->getData();
    stream.ParseFromString(message);
    
    CCLOG("Game stream:");
    CCLOG("===========");
    CCLOG("%s", stream.DebugString().c_str());
    
    // toggle bonus - always changes the scene!
    if( stream.has_active() )
    {
        updateActive(stream.active());
        stop = true;
    }
    
    // update score
    if( stream.has_scoreleft() )
    {
        updateScore(StadiumScene::SIDE_LEFT, stream.scoreleft() );
    }
    if( stream.has_scoreright() )
    {
        updateScore(StadiumScene::SIDE_RIGHT, stream.scoreright() );
    }

    
    // update ball parameters
    if( stream.has_ball() )
    {
        updateBall(stream.ball());
    }
    
    // players sprites
    if( stream.player_size() > 0)
    {
        updatePlayers(stream);
    }
    
    return stop;
}



void GameStreamHandler::updateActive(bool isActive)
{
    if(isActive)
    {
        controller->pushStadium();
        prepareStadium();
        playerMap.clear();
        startNetworking();
    }
    else
    {
        stopNetworking();
        controller->popStadium();
    }
}



void GameStreamHandler::updateScore(StadiumScene::Side side, int score)
{
    auto stadium = controller->getStadium();
    stadium->setScore(side, score);
}



void GameStreamHandler::updateBall(PBBall ballState)
{
    auto stadium = controller->getStadium();
    auto ball = stadium->getBall();
    
    // process position delta
    if(ballState.has_position())
    {
        Vec2 newPosition = Vec2( ballState.position().x(), ballState.position().y());
        Vec2 delta = newPosition - ball->getPosition();
        
        ball->setPosition(newPosition);
    }

    if( ballState.has_playerenabled())
    {
        stadium->setBallKickable( ballState.playerenabled() );
    }
    
    if( ballState.has_velocity())
    {
        ball->getPhysicsBody()->setVelocity(Vec2( ballState.velocity().x(), ballState.velocity().y() ));
    }
}



void GameStreamHandler::updatePlayers(PBGameStream stream)
{
    auto stadium = controller->getStadium();
    
    for(int i=0; i<stream.player_size(); i++)
    {
        auto playerState = stream.player(i);
        Player * player;

        // try to find already existing player
        if( playerMap.find( playerState.id() ) == playerMap.end())
        {
            // not found, need to add new
            // but only if he has a team
            if(playerState.has_team())
            {
                player = Player::create( playerState.name() );
                playerMap[playerState.id()] = player;
                
                std::string team = (playerState.team() == PBTeam::RED) ? TEAM_RED : TEAM_BLUE;
                player->setTeam(team);
                player->getSprite()->setPosition(Vec2( playerState.position().x(), playerState.position().y() ));
                
                stadium->addChild(player->getSprite());
            }
        }
        else
        {
            player = playerMap[ playerState.id() ];
        }
        
        // apply force (same way as in server)
        if(playerState.has_force())
        {
            auto force = Vec2( playerState.force().x(), playerState.force().y() );
            player->applyForce(force);
        }
                
        // process position delta - smoothly move
        if(playerState.has_position())
        {
            Vec2 newPosition = Vec2( playerState.position().x(), playerState.position().y());
            Vec2 delta = newPosition - player->getSprite()->getPosition();
  
            //auto move = EaseInOut::create(MoveBy::create(0.1, delta), 2);
            //player->getSprite()->runAction(move);
            player->getSprite()->setPosition(newPosition);
        }
        
        // speedscale - during kick force loading
        if(playerState.has_speedscale())
        {
            player->setSpeedScale( playerState.speedscale() );
        }
        
        // kick multiplier - bonus
        // TODO? - maybe not necessary - ball force is controlled precisely enough
        
        // speed multiplier - bonus
        if(playerState.has_speedmultiplier())
        {
            player->setSpeedMultiplier( playerState.speedmultiplier() );
        }

    }
}



void GameStreamHandler::startNetworking()
{
    auto stadium = controller->getStadium();
    
    // register handlers
    handlerMap->add(BOX_GAME_STREAM, this);
    handlerMap->add(BOX_CONNECTION_LOST, new GameStreamConnectionLostHandler(stadium));
    
    
    director->getScheduler()->schedule([&](float dt)
    {
        controller->receiveBoxes(handlerMap);
    },
    stadium, RECEIVE_TIMEOUT, CC_REPEAT_FOREVER, 0.0f, false, SCHEDULE_NETWORKING);

    CCLOG("Activated invisibility bonus networking mode.");
}



void GameStreamHandler::stopNetworking()
{
    director->getScheduler()->unschedule(SCHEDULE_NETWORKING, this);
}



void GameStreamHandler::prepareStadium()
{
    //REFACTOR: compute origin that the pitch will be in center
    //          and size that corresponds to server size
    auto origin = director->getVisibleOrigin();
    auto size = director->getVisibleSize();
    
    auto stadium = controller->getStadium();
    stadium->initPitch(origin, size);
    stadium->setMatchMode(true, false);
    stadium->setBallInGame(true);
    
    // init accelerometer
    auto listener = EventListenerAcceleration::create([](Acceleration * acc, Event * ignore)
    {
        GameNet::BoxFactory::acceleration(acc->x, acc->y, acc->z)->send();
    });
    Device::setAccelerometerEnabled(true);
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, stadium);
    
    // touch wherever to kick
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameStreamHandler::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameStreamHandler::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameStreamHandler::onTouchEnded, this);
    stadium->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, stadium);

    // add kickforce-loading image
    auto force = Sprite::create("line.png");
    force->setName(NODE_FORCE);
    force->setScale(1,0);
    force->setAnchorPoint(Vec2(0.5, 0.5));
    force->setOpacity(FORCEBAR_OPACITY);
    force->setVisible(false);
    stadium->addChild(force, 90);
}



bool GameStreamHandler::onTouchBegan(Touch * touch, Event * event)
{
    
    // send kick loading info (needed for player slowing)
    BoxFactory::kickPressed()->send();
    
    // start time measuring
    timer.reset();
    
    // run animation effect
    auto forceBar = dynamic_cast<Sprite*>( controller->getStadium()->getChildByName(NODE_FORCE) );
    
    float scaleY = 500/5.0;     // 500px
    forceBar->runAction(ScaleTo::create(Definitions::TIME_KICK_FORCE_MAX, forceBar->getScaleX(), scaleY));
    forceBar->setVisible(true);
    
    // when touched on the left half,
    // show the bar on the right side
    // (the same with the other side)
    int halfSign = (touch->getLocation().x < DESIGN_WIDTH/2) ? 1 : -1;
    auto offset = halfSign * STADIUM_LOADBAR_OFFSET;
    forceBar->setPosition(Vec2( touch->getLocation().x + offset, touch->getLocation().y ));
    
    return true;
}



bool GameStreamHandler::onTouchMoved(Touch * touch, Event * event)
{
    // reposition the bar
    auto forceBar = dynamic_cast<Sprite*>( controller->getStadium()->getChildByName(NODE_FORCE) );
    int halfSign = (touch->getLocation().x < DESIGN_WIDTH/2) ? 1 : -1;
    auto offset = halfSign * STADIUM_LOADBAR_OFFSET;
    forceBar->setPosition(Vec2( touch->getLocation().x + offset, touch->getLocation().y ));
    
    return true;
}



bool GameStreamHandler::onTouchEnded(Touch * touch, Event * event)
{
    // calculate kick force
    unsigned long long int ms = timer.elapsed().count();
    if( ms >= Definitions::TIME_KICK_FORCE_MAX * 1000){
        ms = Definitions::TIME_KICK_FORCE_MAX * 1000;
    }
    unsigned int force = (ms / (Definitions::TIME_KICK_FORCE_MAX * 1000.0)) * 255.0;
    
    // send to server
    BoxFactory::kickReleased(force)->send();

    // stop animation
    auto forceBar = dynamic_cast<Sprite*>( controller->getStadium()->getChildByName(NODE_FORCE) );
    forceBar->stopAllActions();
    forceBar->setScaleY(0);
    forceBar->setVisible(false);
    
    return true;
}










