#include "InvisibilityBonus.h"
#include "Game.h"
#include "GameplayDefinitions.h"
#include "GameStream.pb.h"
#include "BoxFactory.h"

InvisibilityBonus * InvisibilityBonus::create()
{
    return new InvisibilityBonus();
}

InvisibilityBonus::InvisibilityBonus() : BonusInterface()
{
    name = BONUS_INVISIBILITY;
    
    game = Game::getInstance();
    director = Director::getInstance();
    
    durationMin = INVISIBILITY_MIN;
    durationMax = INVISIBILITY_MAX;

    sprite = Sprite::create("bonus_invisibility.png");
    sprite->setScale(0.5);
    sprite->setName(LABEL_BONUS);
    sprite->setUserData(this);    
    
    auto body = cocos2d::PhysicsBody::createCircle( sprite->getContentSize().width/2, MATERIAL_PLAYER);
    body->setCategoryBitmask(BITMASK_BONUS);
    body->setContactTestBitmask(BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER);
    sprite->setPhysicsBody(body);
    
    // 1 ... first time send with position
    playerCountdown = 1;
    ballCountdown = 1;
}


void InvisibilityBonus::activate(int playerId)
{
    this->playerId = playerId;
    Player * player = game->getPlayer(playerId);

    // player already disconnected
    if(player == nullptr){ return; }
    
    // hide player (physics body works normally)
    player->getSprite()->setVisible(false);
    player->getSprite()->getPhysicsBody()->setCategoryBitmask(BITMASK_INVISIBLE_PLAYER);
    player->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_INVISIBLE_COLLIDES_WITH);
    
    // send initial data
    sendInitialGameStream(player);
    player->getSprite()->schedule([&, player](float dt)
    {
        sendGameStreamDelta(player);
    },
    TIME_GAMESTREAM_DELAY, SCHEDULE_GAMESTREAM);
}



void InvisibilityBonus::deactivate()
{
    Player * player = game->getPlayer(playerId);
    
    if(player != nullptr)
    {
        player->getSprite()->setVisible(true);
        player->getSprite()->getPhysicsBody()->setCategoryBitmask(BITMASK_PLAYER);
        player->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLIDES_WITH);
        player->getSprite()->unschedule(SCHEDULE_GAMESTREAM);
        sendLastGameStream(player);
    }
    else
    {
        CCLOG("%s not deactivated - player not found!", name.c_str());
    }
}



void InvisibilityBonus::sendInitialGameStream(Player * player)
{
    PBGameStream stream = PBGameStream();
    
    stream.set_active(true);
    stream.set_playerid(player->getId());
    stream.set_width( director->getVisibleSize().width );
    stream.set_height( director->getVisibleSize().height );
    stream.set_duration( getDuration() );
    
    GameNet::BoxFactory::gameStreamReliable(player->getAddress(), stream)->send();
}



void InvisibilityBonus::sendGameStreamDelta(Player * player)
{
    CCLOG("Preparing game delta...");
    auto stadium = game->getStadium();
    PBGameStream delta = PBGameStream();
 
    // first condition - if the game has already finished, just tell it
    // and don't send anything else
    if(!game->isPlaying())
    {
        delta.set_active(false);
        GameNet::BoxFactory::gameStream(player->getAddress(), delta)->send();
        player->getSprite()->unschedule(SCHEDULE_GAMESTREAM);
        return;
    }
    
    ////////////////
    // game state //
    ////////////////
    
    delta.set_scoreleft( stadium->getScore(StadiumScene::SIDE_LEFT) );
    delta.set_scoreright( stadium->getScore(StadiumScene::SIDE_RIGHT) );
    
    //////////////////////////////
    // send ball state - always //
    //////////////////////////////
    
    auto ball = stadium->getBall();
    auto ballState = new PBBall();
    auto ballVelocity = new PBVec2();
    
    bool enabled = (ball->getPhysicsBody()->getTag() == StadiumScene::BALL_NORMAL); // parentheses!!!
    ballVelocity->set_x( ball->getPhysicsBody()->getVelocity().x );
    ballVelocity->set_y( ball->getPhysicsBody()->getVelocity().y );
    
    ballState->set_playerenabled(enabled);
    ballState->set_allocated_velocity(ballVelocity);
    delta.set_allocated_ball(ballState);
    
    // position (after every BALL_COUNTDOWN box sending (without position))
    // if ball is player-disabled (after scoring), send always (return animation)
    if( --ballCountdown == 0 || !enabled)
    {
        ballCountdown = BALL_COUNTDOWN;
        auto ballPosition = new PBVec2();
        ballPosition->set_x( ball->getPositionX() );
        ballPosition->set_y( ball->getPositionY() );
        ballState->set_allocated_position(ballPosition);
    }

    
    ////////////////////////////////
    // send player state - always //
    ////////////////////////////////
    
    for(auto it=game->players.begin(); it != game->players.end(); it++)
    {
        auto playerIter = it->second;
        
        // skip the player, if it is invisible enemy
        if( !playerIter->getSprite()->isVisible() && playerIter->getTeam().compare( player->getTeam() ) != 0 )
        {
            continue;
        }

        auto playerState = delta.add_player();
        auto force = new PBVec2();
        
        force->set_x( playerIter->getPreviousForceVector().x );
        force->set_y( playerIter->getPreviousForceVector().y );
        
        if(playerIter->getTeam() != TEAM_AUTO)
        {
            PBTeam team;
            if(playerIter->getTeam() == TEAM_BLUE) team = PBTeam::BLUE;
            if(playerIter->getTeam() == TEAM_RED) team = PBTeam::RED;
            playerState->set_team( team );
        }
        
        playerState->set_id( playerIter->getId() );
        playerState->set_name( playerIter->getName() );
        playerState->set_allocated_force(force);
        playerState->set_speedscale( playerIter->getSpeedScale() );
        playerState->set_kickmultiplier( playerIter->getKickMultiplier() );
        playerState->set_speedmultiplier( playerIter->getSpeedMultiplier() );
        playerState->set_visible( playerIter->getSprite()->isVisible() );
        
        // position (after every PLAYER_COUNTDOWN box sent without position)
        if( --playerCountdown == 0)
        {
            playerCountdown = PLAYER_COUNTDOWN;
            auto position = new PBVec2();
            position->set_x( playerIter->getSprite()->getPositionX() );
            position->set_y( playerIter->getSprite()->getPositionY() );
            playerState->set_allocated_position(position);
        }
    }
    
    /////////////////////////////////
    // send bonuses state - always //
    /////////////////////////////////
    
    auto nodes = stadium->getChildren();
    for(Node * node : nodes)
    {
        if( node->getName().compare(LABEL_BONUS) == 0)
        {
            auto bonus = dynamic_cast<BonusInterface*>((BonusInterface*)node->getUserData());
            if(bonus == nullptr)
            {
                CCLOG("LABEL_BONUS, but it is not BonusInterface * !!!");
                continue;
            }
            
            auto bonusState = delta.add_bonus();
            auto position = new PBVec2();
            position->set_x(bonus->getSprite()->getPositionX());
            position->set_y(bonus->getSprite()->getPositionY());
            bonusState->set_allocated_position(position);
            bonusState->set_id( bonus->id() );
            bonusState->set_name(bonus->getName());
        }
    }
    
    GameNet::BoxFactory::gameStream(player->getAddress(), delta)->send();
}



void InvisibilityBonus::sendLastGameStream(Player * player)
{
    PBGameStream stream;
    stream.set_active(false);
    
    GameNet::BoxFactory::gameStream(player->getAddress(), stream)->send();
    
}