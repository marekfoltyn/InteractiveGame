#ifndef __SERVERLIST_SCENE_H__
#define __SERVERLIST_SCENE_H__

#include <map>
#include <atomic>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Connector.h"

struct ServerMapEntry{
    RakNet::SystemAddress * address;
    std::atomic<int> inactiveSeconds;
};

class ServerListScene : public cocos2d::Layer
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene * createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ServerListScene);
    
    // load and set up cocos nodes and graphics
    void initGraphics();
    
    // process packet with server name
    void serverFound(Block * block);
    
    // send broadcast packet to find servers
    void findServers();
    
    // connect to server
    void btnServerClicked(Ref * pSender);
    
    // Succesfully connected to a server
    void onConnected(Block * block);
    
    void exitGame(Ref * pSender);
    
    void searchLabelNoDot();
    void searchLabelOneDot();
    void searchLabelTwoDots();
    void searchLabelThreeDots();
    
    // start receiving packets
    void startPacketAction();
    
    // stop receiving packets
    void stopPacketAction();
    
    // receive packet processing loop
    void packetAction();
    
    // acceleration event
    void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);
    
private:
    cocos2d::Label * lblSearching;
    cocos2d::Label * lblX;
    cocos2d::Label * lblY;
    cocos2d::Label * lblZ;
    cocos2d::Menu * menu;
    cocos2d::Menu * serverMenu;
    cocos2d::RepeatForever * searchServersAction;
    cocos2d::RepeatForever * receivePacketAction;
    cocos2d::RepeatForever * searchTextLoop;
    
    // map of available servers
    // key - hash of the system address
    std::map<int, ServerMapEntry*> serverMap;
    
    // periodically send broadcast ping to find servers
    void startPing();
    
    // one ping send
    void ping();
    
    // stop pinging action
    void stopPing();
    
    // add new menu item to scroll view, updates if exists
    void addOrUpdateServer(cocos2d::__String * serverName, RakNet::SystemAddress address);
    
    // every "server search" decreases servers lifetimes (when not responding -> delete from menu)
    void decreaseServerLifetimes();
};

#endif // __SERVERLIST_SCENE_H__
