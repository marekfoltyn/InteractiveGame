#include "NewPlayerHandler.h"

#include "Game.h"
#include "Player.h"
#include "PlayerCollisionHandler.h"
#include "GameplayDefinitions.h"


NewPlayerHandler::NewPlayerHandler(Game * game, Director * director)
{
    this->game = game;
    this->director = director;
}



bool NewPlayerHandler::execute(GameNet::Box * box)
{
    Player * player = Player::create(box->getAddress(), box->getData());
    auto stadium = game->getStadium();
    auto sprite = player->getSprite();
    auto visibleSize = director->getVisibleSize();
    auto origin = director->getVisibleOrigin();
    
    CCLOG("New player: %s", box->getData().c_str() );
    
 
    game->addPlayer(player);
    
    // add to the stadium (but hidden, show after team select)
    sprite->setPosition( POSITION_CENTER );
    sprite->setVisible(false);
    sprite->getPhysicsBody()->setEnabled(false);
    stadium->addChild( player->getSprite() );
    
    // check if this player should be the admin
    if( game->playersCount() == 1 ) // only this player is in the stadium
    {
        game->setAsAdmin(player);
    }
    
    return false;
}