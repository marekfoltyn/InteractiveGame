#ifndef __SERVERLIST_SCENE_H__
#define __SERVERLIST_SCENE_H__

#include <map>
#include <atomic>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Connector.h"

/**
 * Simple structure for storing information about servers in LAN
 */
struct ServerMapEntry{
    RakNet::SystemAddress * address;
    std::atomic<int> inactiveSeconds;
};

/**
 * First scene - showing the main menu with the list of servers in LAN
 */
class ServerListScene : public cocos2d::Layer
{
public:
    
    /**
     * Cocos2d-x:
     * there's no 'id' in cpp, so we recommend returning the class instance pointer
     */
    static cocos2d::Scene * createScene();

    /**
     * Cocos2d-x:
     * Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
     */
    virtual bool init();

    /**
     * Cocos2d-x:
     * implement the "static create()" method manually
     */
    CREATE_FUNC(ServerListScene);
    
    /**
     * load and set up cocos nodes and graphics in init()
     */
    void initGraphics();

    /**
     * receive Block processing loop
     * receives until RakNet returns 0 (empty packet queue)
     */
    void receiveAllBlocks();
    
    /**
     * decrease lifetime of found servers and find more servers
     */
    void findServersStep();
    
    /**
     * connect to server
     */
    void btnServerClicked(Ref * pSender);
    
    /**
     * a server has responded to the ping
     * if the controller knows about it, resfresh its lifetime
     * if not, add this server to the server list
     */
    void refreshServer(Blok * blok);
    
    /**
     * Succesfully connected to a server (go to lobby)
     */
    void onConnected(Blok * blok);
    
    /**
     * Exit game
     */
    void btnLeaveClicked(Ref * pSender);
    
    
private:
    cocos2d::Label * lblSearching;
    cocos2d::Label * lblX;
    cocos2d::Label * lblY;
    cocos2d::Label * lblZ;
    cocos2d::Menu * menu;
    cocos2d::Menu * serverMenu;
    cocos2d::RepeatForever * findServersAction;
    cocos2d::RepeatForever * receivePacketAction;
    cocos2d::RepeatForever * searchTextLoop;
    
    // map of available servers
    // key - hash of the system address
    std::map<int, ServerMapEntry*> serverMap;
    
    /**
     * start receiving bloks
     */
    void startReceiveBlocks();
    
    /**
     * stop receiving packets
     */
    void stopReceiveBlocks();

    
    // periodically send broadcast ping to find servers
    void startFindServers();
    
    /**
     * send a ping broadcast message to find servers
     */
    void pingServers();
    
    // stop server action
    void stopFindServers();
    
    // add new menu item to scroll view, updates if exists
    void addOrUpdateServer(cocos2d::__String * serverName, RakNet::SystemAddress address);
    
    // every "server search" decreases servers lifetimes (when not responding -> delete from menu)
    void decreaseServerLifetimes();
};

#endif // __SERVERLIST_SCENE_H__
