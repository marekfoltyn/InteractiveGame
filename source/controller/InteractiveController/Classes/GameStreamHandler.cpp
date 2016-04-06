//
//  GameStreamHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "BoxFactory.h"
#include "ControlScene.h"
#include "StadiumScene.h"

#include "GameStreamHandler.h"
#include "GameStreamConnectionLostHandler.h"
#include "AdminHandler.h"
#include "AdminDialogHandler.h"
#include "CollisionBoxHandler.h"
#include "StopGameHandler.h"

GameStreamHandler::GameStreamHandler(ControlScene * scene)
{
    director = Director::getInstance();
    controller = Controller::getInstance();
    handlerMap = HandlerMap::create();
    playerMap = std::map<unsigned long, Player *>();
    timer = Util::Timer();
    scoreSet = false;
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
        updateActive(stream);
        stop = true;
    }
    
    // update score
    if( stream.has_scoreleft() && stream.has_scoreright() )
    {
        updateScore(StadiumScene::SIDE_LEFT, stream.scoreleft() );
        updateScore(StadiumScene::SIDE_RIGHT, stream.scoreright() );
        scoreSet = true;
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



void GameStreamHandler::updateActive(PBGameStream stream)
{
    if(stream.active())
    {
        // it the game stream begins it has to send
        // pitch size (we need to know proportions)
        if( !stream.has_height() || !stream.has_width() || !stream.has_playerid())
        {
            CCLOG("FATAL ERROR - server did not send pitch size or player ID!");
            return;
        }
        
        myId = stream.playerid();
        pitchSize = cocos2d::Size( stream.width(), stream.height() );
        
        controller->pushStadium();
        prepareStadium(pitchSize);
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
    // scoreSet - score was at least once updated (at first)
    if( stadium->getScore(side) < score && scoreSet )
    {
        stadium->goalAnimation();
    }
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
        if( playerMap.count( playerState.id() ) == 0)
        {
            // not found, need to add new
            // but only if he has a team (skip otherwise
            if(!playerState.has_team())
            {
                // player has not selected a team yet, nothing to render
                continue;
            }
            else
            {
                player = Player::create( playerState.name() );
                playerMap[playerState.id()] = player;
                
                std::string team = (playerState.team() == PBTeam::RED) ? TEAM_RED : TEAM_BLUE;
                player->setTeam(team);
                player->getSprite()->setPosition(Vec2( pitchSize.width/2, pitchSize.height/2 ));
                
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
            Vec2 delta = newPosition - Vec2(player->getSprite()->getPositionX(), player->getSprite()->getPositionY());
  
            auto move = EaseInOut::create(MoveBy::create(0.05, delta), 2);
            player->getSprite()->runAction(move);
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
    handlerMap->add(BOX_ADMIN, new AdminHandler(nullptr));
    handlerMap->add(BOX_COLLISION, new CollisionBoxHandler());
    handlerMap->add(VOID_ADMIN_DIALOG, new AdminDialogHandler(handlerMap));
    handlerMap->add(VOID_STOP_GAME, new StopGameHandler());
    
    
    
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



void GameStreamHandler::prepareStadium(cocos2d::Size pitchSize)
{
    //REFACTOR: compute origin that the pitch will be in center
    //          and size that corresponds to server size
    auto origin = Vec2( (DESIGN_WIDTH - pitchSize.width)/2, (DESIGN_HEIGHT - pitchSize.height)/2 );
    auto size = pitchSize;
    
    stadium = controller->getStadium();
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
    
    // schedule pitch movement with player
    stadium->schedule([&, pitchSize, origin](float dt)
    {
        if( playerMap.count(myId) == 0 )
        {
            // nothing to compute movement from
            CCLOG("movePitch: player not found");
            return;
        }
        
        // move the pitch according to player
        auto player = playerMap[myId];
        auto realOrigin = director->getVisibleOrigin();
        auto visibleSize = director->getVisibleSize();
        auto center = Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
        auto pitchPosition = center - player->getSprite()->getPosition();
        
        // correct the pitch position
        // if the pitch width is bigger than visible width of the phone screen
        // we must move the pitch when player moves (in order to see the rest)
        if( pitchSize.width > visibleSize.width)
        {
            // player is too left -> we do not want to see what is right of the pitch
            if( pitchPosition.x > realOrigin.x )
            {
                pitchPosition.x = realOrigin.x;
            }
            // player is too right - similar as above
            else if( pitchPosition.x < realOrigin.x + visibleSize.width - pitchSize.width)
            {
                pitchPosition.x = realOrigin.x + visibleSize.width - pitchSize.width;
            }
            
            stadium->setPositionX( pitchPosition.x );
        }
        
        // the same as width
        if( pitchSize.height > visibleSize.height)
        {
            // player is too bottom
            if( pitchPosition.y > realOrigin.y )
            {
                pitchPosition.y = realOrigin.y;
            }
            // player is too up
            else if( pitchPosition.y < realOrigin.y + visibleSize.height - pitchSize.height)
            {
                pitchPosition.y = realOrigin.y + visibleSize.height - pitchSize.height;
            }
            
            stadium->setPositionY( pitchPosition.y );
        }
        
    }
    , 1.0/60, "pitchMovement");
    
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










