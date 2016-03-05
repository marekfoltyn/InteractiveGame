//
//  ServersHandler.h
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef ServersHandler_h
#define ServersHandler_h

#include "Connector.h"
#include "Controller.h"
#include "AbstractHandlers.h"

class MainMenuScene;
struct ServerMapEntry;

/**
 * Handler responsible for proper server search and displaying
 * including adding/deleting server entries
 */
class ServersHandler: public VoidHandler, public BoxHandler, public ClickHandler{
public:
    
    ServersHandler(MainMenuScene * scene);
    ~ServersHandler();
    
    /**
     * decrease lifetime of found servers and find more servers
     * this method is called periodically
     */
    void execute();
    
    /**
     * received ping from a server
     */
    bool execute(GameNet::Box * box);
    
    /**
     * click on a server menu item
     */
    void execute(Ref * pSender);
    
private:
    
    GameNet::Connector * connector;
    Controller * controller;
    Director * director;
    MainMenuScene * scene;
    cocos2d::ui::ScrollView * menuView;
    
    /**
     * map of available servers
     * key - hash of the system address
     */
    std::map<int, ServerMapEntry*> serverMap;
    
    /**
     * every "server search" decreases servers lifetimes (when not responding -> delete from menu)
     */
    void decreaseServersLifetime();

    /**
     * add new menu item to scroll view or updates if exists
     */
    void addOrUpdateServer(std::string serverName, RakNet::SystemAddress address);
    
    /**
     * remove server entry from the scene
     */
    void deleteServer(int hash);
    
    /**
     * set positions to servers in scrollView
     */
    void repositionServers();
};





/**
 * Simple helper structure for storing information about servers in LAN
 */
struct ServerMapEntry{
    
    /**
     * server address (IP and port)
     */
    RakNet::SystemAddress * address;
    
    /**
     * how many second the server did not responed
     * after SERVER_MENU_LIFETIME seconds the server entry
     * will be deleted
     */
    int inactiveSeconds;
        
    cocos2d::ui::Button * button;
    
};





#endif /* ServersHandler_h */
