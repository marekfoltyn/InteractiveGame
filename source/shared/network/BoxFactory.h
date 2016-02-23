#ifndef __BOXFACTORY_H__
#define __BOXFACTORY_H__

#include "MessageIdentifiers.h"
#include "Box.h"

namespace GameNet {

/**
 * class responsible for proper Box objects creation
 * every Box (except RakNet's internal packets) sould be created via BoxFactory
 */
class BoxFactory{
public:
    
    /**
     * accelerometer data
     * using AccelerationMessage
     */
    static Box * acceleration(double x, double y, double z);
    
    /**
     * setting as the admin
     *
     * address - RakNet::SystemAddress of the player to be the admin
     */
    static Box * admin(RakNet::SystemAddress address);
  
    /**
     * simple collision information
     */
    static Box * collision(RakNet::SystemAddress address);
    
    /**
     * reset game score
     */
    static Box * resetScore();
    
    /**
     * ball kick
     * intensity is the kick force from interval [0..255]
     */
    static Box * kick(unsigned char intensity);
    
    /**
     * tackle (small kick)
     */
    static Box * tackle();
    
    /**
     * player name info
     */
    static Box * playerName(std::string name);
    
};
}

#endif // __BOXFACTORY_H__
