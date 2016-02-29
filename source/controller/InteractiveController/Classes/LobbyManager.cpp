//
//  LobbyManager.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#include "LobbyManager.h"

LobbyManager * LobbyManager::instance = nullptr;

LobbyManager * LobbyManager::getInstance()
{
    if(instance == nullptr)
    {
        return new LobbyManager();
    }
    else
    {
        return instance;
    }
}



LobbyManager::LobbyManager()
{

}
