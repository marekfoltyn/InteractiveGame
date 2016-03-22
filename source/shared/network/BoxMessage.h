#ifndef  _BoxMessage_H_
#define  _BoxMessage_H_

#include <string>

namespace GameNet {

/**
 * An "interface" representing custom binary data
 * that will be sent in a GameNet::Box
 * Message has two functions - serialize and deserialize data
 */
class BoxMessage {
public:
    
    /**
     * serialization to binary data
     *
     */
    virtual std::string serialize() = 0;
    
    /**
     * deserialization
     * usage:
     *
     * MyMessage msg = MyMessage();
     * bool res = msg.deserialize( box->getData() );
     *
     * returns false if deserialization failed
     */
     virtual bool deserialize(std::string) = 0;
    
    
    /**
     * virtual destructor - necessary ( http://stackoverflow.com/questions/318064 )
     */
    virtual ~BoxMessage(){}
    
    /**
     * implicit constructor
     */
    BoxMessage(){}
};
    
}

#endif // _Message_H_