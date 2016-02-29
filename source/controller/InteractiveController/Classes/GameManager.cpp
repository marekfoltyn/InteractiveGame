//
//  GameManager.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#include "GameManager.h"

GameManager * GameManager::instance = nullptr;

GameManager * GameManager::getInstance()
{
    if(instance == nullptr)
    {
        return new GameManager();
    }
    else
    {
        return instance;
    }
}



GameManager::GameManager()
{

}
