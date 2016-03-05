#ifndef  _LogHandler_H_
#define  _LogHandler_H_

#include "cocos2d.h"
#include "Box.h"
#include "AbstractHandlers.h"
#include "GameplayDefinitions.h"

#include <string>

class LogHandler: public BoxHandler{
public:
    
    bool execute(GameNet::Box * box)
    {
        switch ( box->getType() )
        {
            case BOX_PING:
            {
                CCLOG("Client %s has pinged.", box->getAddress().ToString() );
                break;
            }
                
            case BOX_NEW_CONNECTION:
            {
                CCLOG("%s connected.", box->getAddress().ToString() );
                break;
            }
            case BOX_CONNECTION_LOST:
            case BOX_DISCONNECTED:
            {
                CCLOG("%s disconnected.", box->getAddress().ToString());
                break;
            }
                
            default:
            {
                CCLOG("Packet type %d was ignored.", box->getType());
                break;
            }
       }
        return false;
    }
};

#endif // _LogHandler_H_