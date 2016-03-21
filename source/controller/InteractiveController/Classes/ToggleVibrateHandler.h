//
//  ToggleVibrateHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ToggleVibrateHandler_hpp
#define ToggleVibrateHandler_hpp

#include "AbstractHandlers.h"
#include "Controller.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

/**
 * Class that processes user's vibrate button click
 */
class ToggleVibrateHandler: public TouchHandler{
public:

    ToggleVibrateHandler();
    
    /**
     * toggle vibrate settings
     */
    virtual void execute(Ref * sender, ui::Widget::TouchEventType type);
    
private:
    
    Controller * controller;
};

#endif /* ConnectionLost_h */
