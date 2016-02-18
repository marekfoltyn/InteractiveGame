#ifndef  _StringMessage_H_
#define  _StringMessage_H_

#include "Message.h"
#include <string>

namespace GameNet {

class StringMessage: Message {
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
     * StringMessage-specific
     */
    std::string getString();
    
    /**
     * implicit constructor
     */
    StringMessage(){}
    
private:
    
    std::string str;
};
    
}

#endif // _StringMessage_H_