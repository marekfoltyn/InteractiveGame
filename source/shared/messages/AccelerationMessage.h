#ifndef  _AccelerationMessage_H_
#define  _AccelerationMessage_H_

#include "BoxMessage.h"

namespace GameNet {

/**
 * Message representing the x,y,z coordinates of the
 * accelerometer
 */
class AccelerationMessage: BoxMessage {
public:
    
    /**
     * implementation of the Message interface
     * convert AccelerationMessage to string
     */
    virtual std::string serialize();

    /**
     * implementation of the Message interface
     * set values of AccelerationMessage from the string
     */
    virtual bool deserialize(std::string str);

    /**
     * get X coord
     */
    double getX();

    /**
     * get Y coord
     */
    double getY();

    /**
     * get Z coord
     */
    double getZ();

    /**
     * implicit constructor
     */
    AccelerationMessage();
    
    /**
     * constructor with data
     */
    AccelerationMessage(double x, double y, double z);
    
private:
    
    struct AccStruct{
        double x;
        double y;
        double z;
    };
    
    AccStruct acc;
    
};
}

#endif // _StringMessage_H_