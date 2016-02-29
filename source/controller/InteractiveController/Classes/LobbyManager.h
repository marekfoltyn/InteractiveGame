//
//  LobbyManager.h
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#ifndef LobbyManager_h
#define LobbyManager_h

class LobbyManager{
public:
    
    LobbyManager * getInstance();
    
    
private:
    
    static LobbyManager * instance;
    LobbyManager();
    
};

#endif /* LobbyManager_h */
