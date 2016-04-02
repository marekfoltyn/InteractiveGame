#include "InvisibilityBonus.h"
#include "GameplayDefinitions.h"
#include "GameStream.pb.h"
#include "BoxFactory.h"

InvisibilityBonus * InvisibilityBonus::create()
{
    return new InvisibilityBonus();
}

InvisibilityBonus::InvisibilityBonus()
{
    game = Game::getInstance();
    
    durationMin = INVISIBILITY_MIN;
    durationMax = INVISIBILITY_MAX;

    sprite = Sprite::create("bonus_invisibility.png");
    sprite->setScale(0.5);
    sprite->setName(LABEL_BONUS);
    
    auto body = cocos2d::PhysicsBody::createCircle( sprite->getContentSize().width/2, MATERIAL_PLAYER);
    body->setCategoryBitmask(BITMASK_BONUS);
    body->setContactTestBitmask(BITMASK_PLAYER);
    sprite->setPhysicsBody(body);
    
    // 1 ... firstly send with position
    playerCountdown = 1;
    ballCountdown = 1;
}


void InvisibilityBonus::activateEffect(Player * player)
{
    // avoid duplicate invisibility
    if(!player->getSprite()->isVisible())
    {
        return;
    }
    
    // hide player (physics body works normally)
    player->getSprite()->setVisible(false);
    
    // send initial data
    sendInitialGameStream(player);
    player->getSprite()->schedule([&, player](float dt)
    {
        sendGameStreamDelta(player);
    },
    TIME_GAMESTREAM_DELAY, SCHEDULE_GAMESTREAM);
}



void InvisibilityBonus::deactivateEffect(Player * player)
{
    // duplicate activation
    if(player->getSprite()->isVisible())
    {
        return;
    }
    
    player->getSprite()->setVisible(true);
    player->getSprite()->unschedule(SCHEDULE_GAMESTREAM);
    sendLastGameStream(player);
}



void InvisibilityBonus::sendInitialGameStream(Player * player)
{
    PBGameStream stream = PBGameStream();
    
    stream.set_active(true);
    stream.set_width( game->getStadium()->getContentSize().width );
    stream.set_height( game->getStadium()->getContentSize().height );
    
    GameNet::BoxFactory::gameStreamReliable(player->getAddress(), stream)->send();
}



void InvisibilityBonus::sendGameStreamDelta(Player * player)
{
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
        auto player = it->second;
        auto playerState = delta.add_player();
        auto force = new PBVec2();
        
        force->set_x( player->getPreviousForceVector().x );
        force->set_y( player->getPreviousForceVector().y );
        
        if(player->getTeam() != TEAM_AUTO)
        {
            PBTeam team;
            if(player->getTeam() == TEAM_BLUE) team = PBTeam::BLUE;
            if(player->getTeam() == TEAM_RED) team = PBTeam::RED;
            playerState->set_team( team );
        }
        
        playerState->set_id( player->getId() );
        playerState->set_name( player->getName() );
        playerState->set_allocated_force(force);
        playerState->set_speedscale( player->getSpeedScale() );
        playerState->set_kickmultiplier( player->getKickMultiplier() );
        playerState->set_speedmultiplier( player->getSpeedMultiplier() );
        
        // position (after every PLAYER_COUNTDOWN box sent without position)
        if( --playerCountdown == 0)
        {
            playerCountdown = PLAYER_COUNTDOWN;
            auto position = new PBVec2();
            position->set_x( player->getSprite()->getPositionX() );
            position->set_y( player->getSprite()->getPositionY() );
            playerState->set_allocated_position(position);
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