#ifndef  _ServerNameMessage_H_
#define  _ServerNameMessage_H_

#include "Message.h"
#include <string>

namespace GameNet {

/**
 * class representing Game ping response
 * it sends timestamp (not needed) and server name
 */
class ServerNameMessage: Message {
public:
    
    /**
     * implement Message interface
     * not used - RakNet creates the message automatically
     */
    virtual std::string serialize();

    /**
     * implement Message interface
     */
    virtual bool deserialize(std::string str);

    /**
     * StringMessage-specific
     */
    std::string getServerName();
    
private:
    
    std::string str;
    
};    
}

#endif // _StringMessage_H_