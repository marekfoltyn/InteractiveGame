//
//  ServerDurationUpdateHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ServerDurationUpdateHandler.h"
#include "GameplayDefinitions.h"
#include "BoxFactory.h"
#include "GameState.pb.h"

ServerDurationUpdateHandler::ServerDurationUpdateHandler()
{
    connector = Connector::getInstance();
    controller = Controller::getInstance();
}



void ServerDurationUpdateHandler::execute(std::string strDuration)
{
    GameState_MatchDuration duration = stringToDuration(strDuration);
    
    // gameState difference
    GameState stateChange = GameState();
    stateChange.set_duration(duration);
    
    // update local game state object
    controller->gameState.set_duration(duration);
    
    // send to server
    BoxFactory::admin( connector->getServer(), stateChange)->send();
}


GameState_MatchDuration ServerDurationUpdateHandler::stringToDuration(std::string strDuration)
{
    if( strDuration.compare(STRING_DURATION_SHORT) == 0)
    {
        return GameState_MatchDuration_DURATION_SHORT;
    }

    if( strDuration.compare(STRING_DURATION_MEDIUM) == 0)
    {
        return GameState_MatchDuration_DURATION_MEDIUM;
    }
    
    if( strDuration.compare(STRING_DURATION_LONG) == 0)
    {
        return GameState_MatchDuration_DURATION_LONG;
    }

    return GameState_MatchDuration_DURATION_MEDIUM;
}