//
//  ServerSizeUpdateHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ServerSizeUpdateHandler.h"
#include "GameplayDefinitions.h"
#include "BoxFactory.h"
#include "GameState.pb.h"

ServerSizeUpdateHandler::ServerSizeUpdateHandler()
{
    connector = Connector::getInstance();
    controller = Controller::getInstance();
}

void ServerSizeUpdateHandler::execute(std::string strSize)
{
    GameState_PitchSize size = stringToSize(strSize);
    
    // gameState difference
    GameState stateChange = GameState();
    stateChange.set_pitchsize(size);
    
    // update local game state object
    controller->gameState.set_pitchsize(size);
    
    // send to server
    BoxFactory::admin( connector->getServer(), stateChange)->send();
}



GameState_PitchSize ServerSizeUpdateHandler::stringToSize(std::string strSize)
{
    if( strSize.compare(STRING_SIZE_SMALL) == 0)
    {
        return GameState_PitchSize_SIZE_SMALL;
    }
    
    if( strSize.compare(STRING_SIZE_MEDIUM) == 0)
    {
        return GameState_PitchSize_SIZE_MEDIUM;
    }
    
    if( strSize.compare(STRING_SIZE_BIG) == 0)
    {
        return GameState_PitchSize_SIZE_BIG;
    }
    
    return GameState_PitchSize_SIZE_SMALL;
}