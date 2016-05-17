#ifndef __BOXFACTORY_H__
#define __BOXFACTORY_H__

#include "MessageIdentifiers.h"
#include "Box.h"

#include "GameState.pb.h"
#include "GameStream.pb.h"

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
    static Box * admin(RakNet::SystemAddress address, GameState gameState);
  
    /**
     * simple collision information
     */
    static Box * collision(RakNet::SystemAddress address);
    
    /**
     * ball kick
     * intensity is the kick force from interval [0..255]
     */
    static Box * kick(unsigned int intensity);
    
    /**
     * player name info
     */
    static Box * playerName(std::string name);
    
    /**
     * player's team selection
     */
    static Box * teamSelection(std::string team);
    
    /**
     * game stream step information
     */
    static Box * gameStream(RakNet::SystemAddress player, PBGameStream & stream);
    static Box * gameStreamReliable(RakNet::SystemAddress player, PBGameStream & stream);
};
}

#endif // __BOXFACTORY_H__
