//
//  CollisionBoxHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "CollisionBoxHandler.h"

CollisionBoxHandler::CollisionBoxHandler()
{
    controller = Controller::getInstance();
}

bool CollisionBoxHandler::execute( GameNet::Box * box )
{
    
// iOS ignores vibrate duration - too long vibrations
// so we can't use collision vibrations in iOS
    
#if ( CC_TARGET_PLATFORM != CC_PLATFORM_IOS )
    
    if( controller->isVibrateEnabled() )
    {
        Device::vibrate(Definitions::TIME_COLLISION_VIBRATION);
    }

#endif

    return false;
}