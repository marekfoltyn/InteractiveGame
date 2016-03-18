//
//  ConnectedHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef TeamSelectHandler_hpp
#define TeamSelectHandler_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Connector.h"
#include "AbstractHandlers.h"

/**
 * Class that processes user's team selection
 */
class TeamSelectHandler: public TouchHandler{
public:

    TeamSelectHandler();
    
    /**
     * return to the main menu
     */
    virtual void execute(Ref * sender, ui::Widget::TouchEventType type);
    
private:
    
    cocos2d::Director * director;
    GameNet::Connector * connector;
};

#endif /* ConnectionLost_h */
