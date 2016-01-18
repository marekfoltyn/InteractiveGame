#ifndef __SERVERLIST_SCENE_H__
#define __SERVERLIST_SCENE_H__

#include <map>
#include <atomic>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "RakPeerInterface.h"

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
    void serverFound(RakNet::Packet*);
    
    // send broadcast packet to find servers
    void findServers();
    
    // connect to server
    void btnServerClicked(Ref * pSender);
    
    void exitGame(Ref * pSender);
    
    void searchLabelNoDot();
    void searchLabelOneDot();
    void searchLabelTwoDots();
    void searchLabelThreeDots();
    
private:
    cocos2d::Label * lblSearching;
    cocos2d::ui::ScrollView * serversView;
    
    // map of available servers
    // key - hash of the system address
    std::map<int, ServerMapEntry*> serverMap;
    
    // add new menu item to scroll view, updates if exists
    void addOrUpdateServer(cocos2d::__String serverName, RakNet::SystemAddress * address);
    
    
};

#endif // __SERVERLIST_SCENE_H__
