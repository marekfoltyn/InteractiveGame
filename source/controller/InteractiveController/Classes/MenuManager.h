//
//  MenuManager.h
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#ifndef MenuManager_h
#define MenuManager_h

#include "cocos2d.h"
#include "ServerListScene.h"
#include "HandlerMap.h"

class MenuManager{
public:
    
    static MenuManager * getInstance();

    void startWithMainMenu();
    
    void runMainMenu();
    
    bool isMainMenuRunning();
    ServerListScene * getMainMenuScene();

    
private:
    
    static MenuManager * instance;
    MenuManager();
    
    cocos2d::Director * director;
    
    ServerListScene * mainMenuScene;
    HandlerMap * handlerMap;
};

#endif /* MenuManager_h */
