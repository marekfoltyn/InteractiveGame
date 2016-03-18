//
//  WindowManager.h
//  InteractiveController
//
//  Created by Marek Foltýn on 10.03.16.
//
//

#ifndef WindowManager_h
#define WindowManager_h

#include "cocos2d.h"
#include "MainMenuScene.h"

USING_NS_CC;

/**
 * helper class showind popup windows
 */
class WindowManager{
public:
   
    static const int FONT_SIZE_DEFAULT = 70;
    
    /**
     * show "connection lost" dialog
     */
    static void showConnectionLostDialog(MainMenuScene * scene);
    
};

#endif /* WindowManager_h */
