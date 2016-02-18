//
//  Game
//  InteractiveGame
//
//  Created by Marek Foltýn on 18.02.16.
//
//

#include "Game.h"
#include "LobbyScene.h"

Game * Game::instance = nullptr;

Game::Game()
{
    // empty constructor
}



Game * Game::getInstance()
{
    if(instance == nullptr)
    {
        return new Game();
    }
    else
    {
        return instance;
    }
}



void Game::run()
{
    auto scene = LobbyScene::createScene();
    Director::getInstance()->runWithScene(scene);
}


void Game::end()
{
    Connector::getInstance()->stop();
    Director::getInstance()->end();
    exit(0);
}