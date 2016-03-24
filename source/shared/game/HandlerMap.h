//
//  HandlerMap.h
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#ifndef HandlerMap_h
#define HandlerMap_h

#include "AbstractHandlers.h"
#include "EmptyUniversalHandler.h"

#include <map>
#include <set>

/**
 * map of handlers
 * key is the event type defined in GameplayEvents.h
 * and value is the Handler
 */
class HandlerMap{
public:
    
    /**
     * handlerMap creation
     */
    static HandlerMap * create();
    
    /**
     * constructor - it is better ot call HandlerMap::create()
     */
    HandlerMap();
    
    /**
     * destructor - deletes all handler pointers including
     * the handler data
     */
    ~HandlerMap();
    
    /**
     * add a handler (does not matter what type)
     */
    void add(int eventType, BaseHandler * handler);
    
    /**
     * remove a handler defined via eventType
     */
    void remove(int eventType);
    
    /**
     * deletes all handler pointers including
     * the handler data
     */
    void clear();
    
    /**
     * get handler
     * if not found, returns EmptyUniversalHandler, that does nothing
     * but the log the event
     */
    
    VoidHandler         * getVoidHandler      (int eventType);
    BoxHandler          * getBoxHandler       (int eventType);
    ClickHandler        * getClickHandler     (int eventType);
    TouchHandler        * getTouchHandler     (int eventType);
    AccelerationHandler * getAccHandler       (int eventType);
    CollisionHandler    * getCollisionHandler (int eventType);
    StringHandler       * getStringHandler    (int eventType);

    
    
private:
    
    std::map<int, BaseHandler *> handlerMap;
    
    EmptyUniversalHandler * emptyHandler;
    
    template<class T>
    T get(int eventType);
};

#endif /* HandlerMap_h */
