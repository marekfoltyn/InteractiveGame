//
//  BlockInterface.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//
#ifndef DummyBlock_h
#define DummyBlock_h

#include "Connector.h"

/**
 * Example of how to use Block for different types
 * Methods are dependent on Block type (doesn't have to be static)
 * There could be more method, custom private variables, and so on...
 */
class DummyBlock{ // : Block ... is also possible
public:
    
    /**
     * Creates a Block from Dummy (some game thing)
     */
    static Block * create( char userID, int health ){
        
        int len = 1 + sizeof(int); // userID + health
        char * dumm = new char[len];
        memcpy(dumm, &userID, 1);
        memcpy(dumm+1, &health, sizeof(int) );
        
        return Block::create( dumm, len);
    }
    
    // custom methods (dependent on Block type)
    
    static char UserID(Block * block)
    {
        // if( block->getType() == P_DUMMY && block->getLength() == 1
        char id = block->getData()[0];
        return id;
    }
    
    static int Health(Block * block)
    {
        return (int) * (block->getData()+1);
    }
    
};







#endif /* DummyBlock_h */
