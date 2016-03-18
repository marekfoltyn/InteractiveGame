#include "TeamSelectHandler.h"

#include "Game.h"
#include "Player.h"
#include "PlayerCollisionHandler.h"
#include "GameplayDefinitions.h"

bool TeamSelectHandler::execute(GameNet::Box * box)
{
    //GameNet::TeamSelectMessage msg = GameNet::TeamSelectMessage();
    //bool res = msg.deserialize( box->getData() );
    
    CCLOG("TEAM_SELECT: %s", box->getData().c_str());
    
    int id = box->getId();
    std::string team = box->getData();
    
    if(team.compare(TEAM_AUTO) == 0)
    {
        team = game->getAutoTeam();
    }
    
    auto player = game->getPlayer(id);
    if(player != nullptr)
    {
        player->setTeam(team);
    }
    
    return false;
}