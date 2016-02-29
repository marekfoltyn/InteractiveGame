//
//  EmptyUniversalHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#ifndef EmptyUniversalHandler_h
#define EmptyUniversalHandler_h

#include "AbstractHandlers.h"

class EmptyUniversalHandler:
    public VoidHandler,
    public BoxHandler,
    public TouchHandler,
    public AccelerationHandler,
    public CollisionHandler
{
    virtual void execute();
    virtual void execute( GameNet::Box * box );
    virtual void execute( Ref * sender );
    virtual void execute( Ref * sender, ui::Widget::TouchEventType type );
    virtual void execute( Acceleration* acc, Event * unused_event );
    virtual void execute(PhysicsBody * first, PhysicsBody * second);
};


#endif /* EmptyUniversalHandler_h */
