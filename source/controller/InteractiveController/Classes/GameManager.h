//
//  GameManager.h
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#ifndef GameManager_h
#define GameManager_h

class GameManager{
public:
    
    GameManager * getInstance();
    
    
private:
    
    static GameManager * instance;
    GameManager();
    
};

#endif /* GameManager_h */
