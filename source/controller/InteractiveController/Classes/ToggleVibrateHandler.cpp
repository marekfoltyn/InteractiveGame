//
//  ToggleVibrateHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ToggleVibrateHandler.h"
#include "GameplayDefinitions.h"

ToggleVibrateHandler::ToggleVibrateHandler()
{
    controller = Controller::getInstance();
}

void ToggleVibrateHandler::execute(Ref * sender, ui::Widget::TouchEventType type)
{
    if(type != ui::Widget::TouchEventType::ENDED){
        return;
    }
    
    auto button = dynamic_cast<ui::Button*>(sender);
    if(button == nullptr){
        CCLOG("Bad cast!!!");
        return;
    }

    if(controller->isVibrateEnabled())
    {
        controller->setVibrate(false);
        button->setOpacity(Definitions::OPACITY_HALF);
    }
    else
    {
        controller->setVibrate(true);
        button->setOpacity(Definitions::OPACITY_FULL);
    }
}