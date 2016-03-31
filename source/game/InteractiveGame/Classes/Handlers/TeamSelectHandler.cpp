#include "TeamSelectHandler.h"

#include "Game.h"
#include "Player.h"
#include "PlayerCollisionHandler.h"
#include "GameplayDefinitions.h"

bool TeamSelectHandler::execute(GameNet::Box * box)
{
    CCLOG("TEAM_SELECT: %s", box->getData().c_str());
    
    int id = box->getId();
    std::string team = box->getData();
    auto player = game->getPlayer(id);
    
    // auto assign
    if(team.compare(TEAM_AUTO) == 0)
    {
        team = game->getAutoTeam();
    }
    
    if(player != nullptr)
    {
        player->setTeam(team);

        // show player in the game
        player->getSprite()->setVisible(true);
        player->getSprite()->getPhysicsBody()->setEnabled(true);
    }
    return false;
}