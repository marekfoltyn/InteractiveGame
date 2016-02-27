//
//  MenuManager.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#include "MenuManager.h"

MenuManager * MenuManager::instance = nullptr;

MenuManager * MenuManager::getInstance()
{
    if(instance == nullptr)
    {
        return new MenuManager();
    }
    else
    {
        return instance;
    }
}



MenuManager::MenuManager()
{

}
