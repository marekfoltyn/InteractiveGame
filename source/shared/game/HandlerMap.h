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

class HandlerMap{
public:
    
    HandlerMap();
    ~HandlerMap();
    
    static std::shared_ptr<HandlerMap> create();
    
    void add(int eventType, BaseHandler * handler);
    void remove(int eventType);
    void clear();
    
    VoidHandler         * getVoidHandler      (int eventType);
    BoxHandler          * getBoxHandler       (int eventType);
    ClickHandler        * getClickHandler     (int eventType);
    TouchHandler        * getTouchHandler     (int eventType);
    AccelerationHandler * getAccHandler       (int eventType);
    CollisionHandler    * getCollisionHandler (int eventType);

    
    
private:
    
    static HandlerMap * instance;
    
    std::map<int, BaseHandler *> handlerMap;
    
    EmptyUniversalHandler * emptyHandler;
    
    template<class T>
    T get(int eventType);
};

#endif /* HandlerMap_h */
