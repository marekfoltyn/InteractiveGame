//
//  StartHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "StartHandler.h"

StartHandler::StartHandler()
{
    game = Game::getInstance();
    director = Director::getInstance();
}



void StartHandler::execute()
{
    bool result = game->startNetworking();
    if( result == false )
    {
        //IDEA: game->getWindowManager->noNetworkingDialog();
        return;
    }
    
    game->run();
}
