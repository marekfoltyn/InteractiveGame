//
//  LobbyManager.h
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#ifndef LobbyManager_h
#define LobbyManager_h

#include "cocos2d.h"
#include "HandlerMap.h"
#include "LobbyScene.h"

class LobbyManager{
public:
    
    static LobbyManager * getInstance();
    
    void runLobby();
    bool isLobbyRunning();
    LobbyScene * getLobbyScene();

    
private:
    
    static LobbyManager * instance;
    LobbyManager();
    
    cocos2d::Director * director;
    HandlerMap * handlerMap;
    
    LobbyScene * lobbyScene;
};

#endif /* LobbyManager_h */
