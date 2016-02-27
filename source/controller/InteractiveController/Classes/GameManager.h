//
//  MenuManager.h
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#ifndef MenuManager_h
#define MenuManager_h

class MenuManager{
public:
    
    MenuManager * getInstance();
    
    
private:
    
    static MenuManager * instance;
    MenuManager();
    
};

#endif /* MenuManager_h */
