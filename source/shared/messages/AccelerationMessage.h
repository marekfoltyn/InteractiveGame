#ifndef  _AccelerationMessage_H_
#define  _AccelerationMessage_H_

#include "Message.h"

namespace GameNet {

class AccelerationMessage: Message {
public:
    
    /**
     * implement Message interface
     */
    virtual std::string serialize();

    /**
     * implement Message interface
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