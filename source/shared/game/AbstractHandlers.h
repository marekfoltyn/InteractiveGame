#ifndef  _AbstractHandlers_H_
#define  _AbstractHandlers_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box.h"

USING_NS_CC;

class BaseHandler{
public:
    virtual ~BaseHandler(){}
};



class VoidHandler: public BaseHandler{
public:
    virtual void execute() = 0;
};



class BoxHandler: public BaseHandler{
public:
    virtual void execute( GameNet::Box * box ) = 0;
};



class ClickHandler: public BaseHandler{
public:
    virtual void execute( Ref * sender ) = 0;
};



class TouchHandler: public BaseHandler{
public:
    virtual void execute( Ref * sender, ui::Widget::TouchEventType type ) = 0;
};



class AccelerationHandler: public BaseHandler{
public:
    virtual void execute( Acceleration* acc, Event * unused_event ) = 0;
};



class CollisionHandler: public BaseHandler{
public:
    virtual void execute(PhysicsBody * first, PhysicsBody * second) = 0;
};





#endif // _AbstractHandlers_H_