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
#include "Connector.h"     // #include into WindowManager.cpp makes "Point reference is ambigous" in MacTypes.h !!!
#include "GameState.pb.h"
#include "HandlerMap.h"

USING_NS_CC;

/**
 * helper class showing popup windows
 */
class WindowManager{
public:
   
    static const int FONT_SIZE_DEFAULT = 70;
    
    /**
     * show "connection lost" dialog
     */
    static void showConnectionLostDialog(Layer * scene);
    
    /**
     * show a dialog with admin settings
     * (match duration, pitch size, ...)
     */
    static void showAdminSettings(Node * scene, GameState gameState, HandlerMap * handlerMap);
    
};

#endif /* WindowManager_h */
