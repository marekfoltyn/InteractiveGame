#ifndef  _LogHandler_H_
#define  _LogHandler_H_

#include "cocos2d.h"
#include "Box.h"
#include "BoxHandler.h"

#include <string>

class LogHandler: public BoxHandler{
public:
    
    void execute(GameNet::Box * box)
    {
        switch ( box->getType() )
        {
            case P_PING:
            {
                CCLOG("Client %s has pinged.", box->getAddress().ToString() );
                break;
            }
                
            case P_NEW_CONNECTION:
            {
                CCLOG("%s connected.", box->getAddress().ToString() );
                break;
            }
            case P_CONNECTION_LOST:
            case P_DISCONNECTED:
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
    }

};

#endif // _LogHandler_H_