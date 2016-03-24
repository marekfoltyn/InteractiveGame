//
//  WindowManager.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 10.03.16.
//
//

#include "WindowManager.h"
#include "GameplayDefinitions.h"
#include "ui/CocosGUI.h"
#include "Controller.h"

void WindowManager::showConnectionLostDialog(Layer * scene)
{
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    auto origin = director->getVisibleOrigin();
    
    // background
    auto bg = ui::Button::create("line_black.png");
    bg->setScale(16.8, 20*10.5);
    bg->setOpacity(100);
    bg->setCascadeOpacityEnabled(true);
    bg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    scene->addChild(bg);

    // dialog box
    auto box = Sprite::create("line.png");
    box->setScale(10, 20*6);
    box->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    scene->addChild(box);
    
    
    // text
    auto text = Label::createWithTTF("Connection lost.", "Vanilla.ttf", FONT_SIZE_DEFAULT);
    text->setTextColor(COLOR_GREEN);
    text->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + (box->getContentSize().height*box->getScaleY())/4 ));
    scene->addChild(text);
    
    auto ok = ui::Button::create();
    ok->setTitleText("Ok");
    ok->getTitleRenderer()->setTTFConfig(TTFConfig("Vanilla.ttf",FONT_SIZE_DEFAULT*2));
    ok->getTitleRenderer()->setTextColor(COLOR_GREEN);
    ok->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - (box->getContentSize().height*box->getScaleY())/4 ));
    scene->addChild(ok);
    
    // disappear after click
    // [&]()[] is not working... [ok](){} works
    ok->addTouchEventListener([scene,ok,text,bg,box](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type == ui::Widget::TouchEventType::BEGAN)
        {
            CCLOG("ok has label '%s'", ok->getTitleRenderer()->getString().c_str());
            ok->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));
            text->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));
            bg->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));
            box->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));

            // remove from scene
            scene->scheduleOnce([scene,ok,text,bg,box](float dt){
                scene->removeChild(ok);
                scene->removeChild(text);
                scene->removeChild(bg);
                scene->removeChild(box);
                CCLOG("dialog children removed.");
            }, Definitions::DIALOG_FADEOUT_DURATION, "dialogHide");     // "dialogHide" must not be "" !!! otherwise repeats forever!
            
        }
    });
}



void WindowManager::showAdminSettings(cocos2d::Node * scene, GameState gameState, HandlerMap * handlerMap)
{
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    auto origin = director->getVisibleOrigin();
    
    // background
    auto bg = ui::Button::create("line_black.png");
    bg->setScale(16.8, 20*10.5);
    bg->setOpacity(100);
    bg->setCascadeOpacityEnabled(true);
    bg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    scene->addChild(bg);
    
    // dialog box
    auto box = Sprite::create("dialogBox.png");
    box->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    box->setCascadeOpacityEnabled(true);
    scene->addChild(box);
    
    auto boxSize = box->getContentSize();

    // Stadium:
    auto lblStadium = Label::createWithTTF("Stadium:", FONT_DEFAULT, FONT_SIZE_DEFAULT);
    lblStadium->setTextColor(COLOR_GREEN_SEMI_TRANSPARENT);
    lblStadium->setAnchorPoint(Vec2(0,1));
    lblStadium->setPosition(Vec2( BORDER_DEFAULT, boxSize.height - BORDER_DEFAULT ));
    box->addChild(lblStadium);
    
    // stadium name - text field
    auto txtName = ui::TextField::create("<stadium name>", FONT_DEFAULT, FONT_SIZE_DEFAULT);
    txtName->setString( gameState.name() );
    txtName->setMaxLength(16);
    txtName->setMaxLengthEnabled(true);
    txtName->setAnchorPoint(Vec2(1,1));
    txtName->setPosition(Vec2( boxSize.width - BORDER_DEFAULT, boxSize.height - BORDER_DEFAULT ));
    txtName->setTextColor(COLOR_GREEN);
    txtName->setPlaceHolderColor(Color4B(255, 255, 255, 124));
    txtName->addEventListener([handlerMap](Ref * sender, ui::TextField::EventType type)
    {
        ui::TextField * txtField = dynamic_cast<ui::TextField *>( sender );
        
        switch (type)
        {
            case ui::TextField::EventType::ATTACH_WITH_IME:
            {
                break;
            }
                
            case ui::TextField::EventType::INSERT_TEXT:
            case ui::TextField::EventType::DELETE_BACKWARD:
            case ui::TextField::EventType::DETACH_WITH_IME:
            {
                // update server name
                handlerMap->getStringHandler(STRING_SERVER_NAME_UPDATE)->execute( txtField->getString() );
            }
        }
    });
    box->addChild(txtName);

    // Duration:
    auto lblDuration = Label::createWithTTF("Duration:", FONT_DEFAULT, FONT_SIZE_DEFAULT);
    lblDuration->setTextColor(COLOR_GREEN_SEMI_TRANSPARENT);
    lblDuration->setAnchorPoint(Vec2(0,1));
    lblDuration->setPosition(Vec2( BORDER_DEFAULT, boxSize.height - lblStadium->getContentSize().height - 2*BORDER_DEFAULT));
    box->addChild(lblDuration);

    // Size:
    auto lblSize = Label::createWithTTF("Size:", FONT_DEFAULT, FONT_SIZE_DEFAULT);
    lblSize->setTextColor(COLOR_GREEN_SEMI_TRANSPARENT);
    lblSize->setAnchorPoint(Vec2(0,1));
    lblSize->setPosition(Vec2( BORDER_DEFAULT, boxSize.height - 2*lblStadium->getContentSize().height - 3*BORDER_DEFAULT));
    box->addChild(lblSize);
    
    // Bots:
    auto lblBots = Label::createWithTTF("Bots:", FONT_DEFAULT, FONT_SIZE_DEFAULT);
    lblBots->setTextColor(COLOR_GREEN_SEMI_TRANSPARENT);
    lblBots->setAnchorPoint(Vec2(0,1));
    lblBots->setPosition(Vec2( BORDER_DEFAULT, boxSize.height - 3*lblStadium->getContentSize().height - 4*BORDER_DEFAULT));
    //box->addChild(lblBots);

    
    // Start button
    auto ok = ui::Button::create();
    ok->setTitleText("Start");
    ok->setAnchorPoint(Vec2(1,0));
    ok->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT,1.5*FONT_SIZE_DEFAULT));
    ok->getTitleRenderer()->setTextColor(COLOR_GREEN);
    ok->setPosition(Vec2( boxSize.width - BORDER_DEFAULT, BORDER_DEFAULT ));
    box->addChild(ok);

    // Cancel button
    auto btnCancel = ui::Button::create();
    btnCancel->setTitleText("Back");
    btnCancel->setAnchorPoint(Vec2(0,0));
    btnCancel->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT,1.5*FONT_SIZE_DEFAULT));
    btnCancel->getTitleRenderer()->setTextColor(COLOR_GREEN);
    btnCancel->setPosition(Vec2( BORDER_DEFAULT, BORDER_DEFAULT ));
    box->addChild(btnCancel);
    
    // disappear after click
    // [&]()[] is not working... [scene,...](){} works
    ok->addTouchEventListener([scene,box,bg,handlerMap](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type == ui::Widget::TouchEventType::BEGAN)
        {
            box->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));
            bg->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));
            
            // remove from scene
            scene->scheduleOnce([scene,box,bg](float dt){
                scene->removeChild(box);
                scene->removeChild(bg);
                CCLOG("dialog children removed.");
            }, Definitions::DIALOG_FADEOUT_DURATION, "dialogHide");     // "dialogHide" must not be "" !!! otherwise repeats forever!
            
            //handlerMap->getVoidHandler(VOID_START_GAME)->execute();
        }
    });
    
    // disappear after click
    // [&]()[] is not working... [scene,...](){} works
    btnCancel->addTouchEventListener([scene,box,bg](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type == ui::Widget::TouchEventType::BEGAN)
        {
            box->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));
            bg->runAction(FadeOut::create(Definitions::DIALOG_FADEOUT_DURATION));
            
            // remove from scene
            scene->scheduleOnce([scene,box,bg](float dt){
            scene->removeChild(box);
            scene->removeChild(bg);
            CCLOG("dialog children removed.");
        }, Definitions::DIALOG_FADEOUT_DURATION, "dialogHide");     // "dialogHide" must not be "" !!! otherwise repeats forever!
      }
  });
    

    
}
