//
//  EmptyUniversalHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#include "EmptyUniversalHandler.h"

void EmptyUniversalHandler::execute()
{
    CCLOG("VoidHandler");
}



void EmptyUniversalHandler::execute( GameNet::Box * box )
{
    CCLOG("BoxHandler");
}



void EmptyUniversalHandler::execute( Ref * sender )
{
    CCLOG("ClickHandler");
}



void EmptyUniversalHandler::execute( Ref * sender, ui::Widget::TouchEventType type )
{
    CCLOG("TouchHandler");
}



void EmptyUniversalHandler::execute( Acceleration* acc, Event * unused_event )
{
    CCLOG("AccelerationHandler");
}



void EmptyUniversalHandler::execute(PhysicsBody * first, PhysicsBody * second)
{
    CCLOG("CollisionHandler");
}
