#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include <map>
#include <atomic>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Connector.h"
#include "Controller.h"

#include "HandlerMap.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace GameNet;


/**
 * First scene - showing the main menu with the list of servers in LAN
 */
class MainMenuScene : public cocos2d::Layer
{
public:
    
    static const int SCENE_TAG = 1;
    static const int FONT_SIZE_DEFAULT = 70;
    
    static const std::string NODE_SERVERS;
    static const std::string NODE_LOGO;
    
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
    CREATE_FUNC(MainMenuScene);
    
    /**
     * load and set up cocos nodes and graphics in init()
     */
    void initGraphics();
    
    /**
     * start Box receiving
     */
    void scheduleBoxReceive();
    
    /**
     * This method is called when user interacts with the player name textfield
     */
    void txtNameEvent(Ref * sender, ui::TextField::EventType type);
    
    /**
     * try to connect to server
     */
    void btnServerClicked(Ref * pSender);
    
    /**
     * show that the Controller is connecting to a server
     */
    void setLoadingAnimation(bool set);
    
    /**
     * Exit game
     */
    void btnLeaveClicked(Ref * pSender);
    
private:
    
    /**
     * Controller instance
     */
    Controller * controller;
    
    /**
     * map of event handlers interacting with this scene
     */
    std::shared_ptr<HandlerMap> handlerMap;
    
    /**
     * registering handlers
     */
    void registerHandlers();
    
    /**
     * periodically send broadcast ping to find servers
     */
    void startFindServers();
    
    /**
     * send a ping broadcast message to find servers
     */
    void pingServers();
    
};

#endif // __MainMenu_SCENE_H__
