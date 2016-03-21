//
//  HandlerMap.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#include "HandlerMap.h"

HandlerMap * HandlerMap::create()
{
    return new HandlerMap();
}



HandlerMap::HandlerMap()
{
    handlerMap = std::map<int, BaseHandler*>();
    emptyHandler = new EmptyUniversalHandler();
    CCLOG("HandlerMap()");
}

HandlerMap::~HandlerMap()
{
    std::set<BaseHandler*> deleted = std::set<BaseHandler*>();
    
    for(auto it=handlerMap.begin(); it!=handlerMap.end(); ++it)
    {
        if(deleted.count(it->second) > 0)
        {
            // already deleted
            continue;
        }
        
        deleted.insert(it->second);
        delete it->second;
    }
    
    delete emptyHandler;
    deleted.clear();
    clear();
    CCLOG("~HandlerMap()");
}



void HandlerMap::add(int eventType, BaseHandler * handler)
{
    if(handler == nullptr) return;
    handlerMap[eventType] = handler;
}



void HandlerMap::remove(int eventType)
{
    if(handlerMap.count(eventType) == 0)
    {
        //delete handlerMap[eventType];
        handlerMap.erase(eventType);
    }
}



void HandlerMap::clear()
{
    /*for(auto it=handlerMap.begin(); it!=handlerMap.end(); it++){
        delete it->second;
    }*/

    handlerMap.clear();
}



template<class T>
T HandlerMap::get(int eventType)
{
    // handler not found
    if(handlerMap.count(eventType) == 0)
    {
        CCLOG("Handler not found:");
        return emptyHandler;
    }
    
    T handler = dynamic_cast<T>(handlerMap[eventType]);
    
    // bad cast
    if(handler == nullptr)
    {
        CCLOG("Bad handler cast:");
        return emptyHandler;
    }
    
    return handler;
}



VoidHandler * HandlerMap::getVoidHandler(int eventType)
{
    return get<VoidHandler*>(eventType);
}

BoxHandler * HandlerMap::getBoxHandler(int eventType)
{
    return get<BoxHandler*>(eventType);
}

ClickHandler * HandlerMap::getClickHandler(int eventType)
{
    return get<ClickHandler*>(eventType);
}

TouchHandler * HandlerMap::getTouchHandler(int eventType)
{
    return get<TouchHandler*>(eventType);
}

AccelerationHandler * HandlerMap::getAccHandler(int eventType)
{
    return get<AccelerationHandler*>(eventType);
}

CollisionHandler * HandlerMap::getCollisionHandler(int eventType)
{
    return get<CollisionHandler*>(eventType);
}
