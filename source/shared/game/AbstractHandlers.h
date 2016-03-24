#ifndef  _AbstractHandlers_H_
#define  _AbstractHandlers_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box.h"
#include <string>

USING_NS_CC;

/**
 * Base handler class - a lot of game events are controlled
 * by handlers - small classes interacting with scenes, controller, connector and so on
 * Handlers have several types, but every Handler derives from BaseHandler
 */
class BaseHandler{
public:
    virtual ~BaseHandler(){}
};


/**
 * The simplest handler - does something, bud it does not accept
 * any arguments when called (for example - start game, exit game)
 */
class VoidHandler: public BaseHandler{
public:
    virtual void execute() = 0;
};


/**
 * Handler that processes a received Box
 *
 * @return true if the active scene should stop Box receiving (before scene replace)
 * - keep received boxes in a queue to receive by next scene
 */
class BoxHandler: public BaseHandler{
public:
    virtual bool execute( GameNet::Box * box ) = 0;
};


/**
 * Handler that processes a button click
 */
class ClickHandler: public BaseHandler{
public:
    virtual void execute( Ref * sender ) = 0;
};


/**
 * Handler that processes a widget touch
 */
class TouchHandler: public BaseHandler{
public:
    virtual void execute( Ref * sender, ui::Widget::TouchEventType type ) = 0;
};


/** 
 * Handler that processes values received from accelerometer
 */
class AccelerationHandler: public BaseHandler{
public:
    virtual void execute( Acceleration* acc, Event * unused_event ) = 0;
};


/**
 * Handler that processes physical collisions in a scene
 */
class CollisionHandler: public BaseHandler{
public:
    virtual void execute(PhysicsBody * first, PhysicsBody * second) = 0;
};


/**
 * Handler that process the string parameter (for example text field update)
 */
class StringHandler: public BaseHandler{
public:
    virtual void execute(std::string) = 0;
};



#endif // _AbstractHandlers_H_