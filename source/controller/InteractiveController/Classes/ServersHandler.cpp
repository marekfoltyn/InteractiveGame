//
//  ServersHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ServersHandler.h"
#include "MainMenuScene.h"
#include "ServerNameMessage.h"
#include "GameplayDefinitions.h"

ServersHandler::ServersHandler(MainMenuScene * scene)
{
    connector = GameNet::Connector::getInstance();
    controller = Controller::getInstance();
    director = Director::getInstance();
    this->scene = scene;
    menuView = (ui::ScrollView *) scene->getChildByName(MainMenuScene::NODE_SERVERS);
    
    serverMap = std::map<int, ServerMapEntry*>();
}


ServersHandler::~ServersHandler()
{
    for(auto it=serverMap.begin(); it!=serverMap.end(); it++)
    {
        deleteServer(it->first);
    }
}

void ServersHandler::execute()
{
    connector->ping();
    decreaseServersLifetime(); // refresh actually found servers
}



bool ServersHandler::execute(GameNet::Box * box)
{
    if( !controller->isRunning<MainMenuScene>() )
    {
        CCLOG("MainMenu is not running, ServerName ignored.");
        return false;
    }
    
    auto message = ServerNameMessage();
    message.deserialize(box->getData());
    auto name = message.getServerName();
    CCLOG("Server ping: %s", name.c_str());
    
    addOrUpdateServer(name, box->getAddress());
    
    return false;
}



void ServersHandler::execute(Ref * pSender)
{
    auto btn = (cocos2d::ui::Button *) pSender;
    int tag = btn->getTag(); // tag value is the key in serverMap
    
    if(tag == -1)
    {
        CCLOG("Tag not found. Can't connect.");
        return;
    }
    
    RakNet::SystemAddress address = *(serverMap[tag]->address);
    connector->connect(address);
    scene->setLoadingAnimation(true);
    
    CCLOG("[MainMenuScene] Connecting to %s", address.ToString());
}



void ServersHandler::addOrUpdateServer(std::string serverName, RakNet::SystemAddress address)
{
    auto origin = director->getVisibleOrigin();
    int hash = (int) RakNet::SystemAddress::ToInteger( address );
    
    if( serverMap.count( hash ) != 1 || serverMap[hash] == nullptr ) // when deleted, set to nullptr (node is not deleted, bad memory acces during map loop)
    {
        // create new entry
        ServerMapEntry * s = new ServerMapEntry();
        s->inactiveSeconds = 0;
        s->address = new RakNet::SystemAddress(address); // copy adress (packet will be deallocated)
        serverMap[hash] = s;
        
        CCLOG("%s added (hash: %d).", serverName.c_str(), hash);
        std::string name(serverName.c_str());
        
        // add to the menu (img, background, label)
        s->button = ui::Button::create(/*"servername_bg.png", "servername_bg.png"*/);
        s->button->setTag(hash);
        s->button->setAnchorPoint(Vec2(0.5, 1));
        s->button->setTitleText(name);
        s->button->setTitleFontName("Vanilla.ttf");
        s->button->setTitleFontSize(MainMenuScene::FONT_SIZE_DEFAULT);
        s->button->setTitleColor(Color3B::WHITE);
        s->button->addClickEventListener(CC_CALLBACK_1(MainMenuScene::btnServerClicked, scene));
        menuView->addChild(s->button);
        
        repositionServers();
    }
    else
    {
        // server already exists - refresh server lifetime
        auto s = serverMap[hash];
        s->inactiveSeconds = 0;
    }
}



void ServersHandler::decreaseServersLifetime()
{
    for(auto i=serverMap.begin(); i!=serverMap.end(); i++)
    {
        i->second->inactiveSeconds++;
        CCLOG("%s lifetime set to %d", i->second->address->ToString(), (int) i->second->inactiveSeconds);
    }
    
    auto i = serverMap.begin();
    while( i != serverMap.end() )
    {
        if( i->second->inactiveSeconds >= SERVER_MENU_LIFETIME)
        {
            deleteServer(i->first);
            i=serverMap.begin(); // we don't know the next iterator, need to start over
            repositionServers();
        }
        else
        {
            i++; // next iterator
        }
    }
}



void ServersHandler::deleteServer(int hash)
{
    std::string address = serverMap[hash]->address->ToString();
    CCLOG("%s removed for inactivity.",address.c_str());
    
    delete serverMap[hash]->address;
    delete serverMap[hash];
    
    auto btn = (ui::Button * ) menuView->getChildByTag(hash);
    menuView->removeChild(btn);
    serverMap.erase(hash);

}



void ServersHandler::repositionServers()
{
    int serverCount = static_cast<int>(serverMap.size());
    menuView->setInnerContainerSize(cocos2d::Size( menuView->getInnerContainerSize().width, (serverCount+1) * (1.5 * MainMenuScene::FONT_SIZE_DEFAULT + BORDER_DEFAULT )));
    
    int i=0;
    for(auto it=serverMap.begin(); it!=serverMap.end(); it++)
    {
        it->second->button->setPosition(Vec2(menuView->getInnerContainerSize().width/2,menuView->getInnerContainerSize().height - i * (1.5 * MainMenuScene::FONT_SIZE_DEFAULT + BORDER_DEFAULT) - BORDER_DEFAULT));
        i++;
    }
}



/*IDEA:

 ServerMenuScene
 =========================
 - addServerItem(...)
 - removeServerItem(...)
 
 PingServersHandler
 =========================
 - pingServers()
 - decreaseLifetimes()
 - addOrRefreshServer(...)
 
*/
