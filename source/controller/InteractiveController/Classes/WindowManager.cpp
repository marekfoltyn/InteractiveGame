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
    lblStadium->setTextColor(COLOR_GRAY);
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
    lblDuration->setTextColor(COLOR_GRAY);
    lblDuration->setAnchorPoint(Vec2(0,1));
    lblDuration->setPosition(Vec2( BORDER_DEFAULT, boxSize.height - lblStadium->getContentSize().height - 2*BORDER_DEFAULT));
    box->addChild(lblDuration);

    auto btn3min = ui::Button::create();
    auto btn5min = ui::Button::create();
    auto btn7min = ui::Button::create();
    
    // 7min
    btn7min->setTitleText("7min");
    btn7min->setAnchorPoint(Vec2(1,1));
    btn7min->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT, FONT_SIZE_DEFAULT));
    btn7min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
    btn7min->setPosition(Vec2( boxSize.width - BORDER_DEFAULT, boxSize.height - lblStadium->getContentSize().height - 2*BORDER_DEFAULT));
    box->addChild(btn7min);
    btn7min->addTouchEventListener([handlerMap, btn3min, btn5min, btn7min](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type != ui::Widget::TouchEventType::BEGAN) return;
        btn3min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btn5min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btn7min->getTitleRenderer()->setTextColor(COLOR_GREEN);
        handlerMap->getStringHandler(STRING_SERVER_DURATION_UPDATE)->execute(STRING_DURATION_LONG);
    });
    
    // 5min
    btn5min->setTitleText("5min");
    btn5min->setAnchorPoint(Vec2(1,1));
    btn5min->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT, FONT_SIZE_DEFAULT));
    btn5min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
    btn5min->setPosition(Vec2( boxSize.width - btn7min->getTitleRenderer()->getContentSize().width - 2*BORDER_DEFAULT, boxSize.height - lblStadium->getContentSize().height - 2*BORDER_DEFAULT));
    box->addChild(btn5min);
    btn5min->addTouchEventListener([handlerMap, btn3min, btn5min, btn7min](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type != ui::Widget::TouchEventType::BEGAN) return;
        btn3min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btn5min->getTitleRenderer()->setTextColor(COLOR_GREEN);
        btn7min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        handlerMap->getStringHandler(STRING_SERVER_DURATION_UPDATE)->execute(STRING_DURATION_MEDIUM);
    });
    
    
    // 3min
    btn3min->setTitleText("3min");
    btn3min->setAnchorPoint(Vec2(1,1));
    btn3min->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT, FONT_SIZE_DEFAULT));
    btn3min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
    btn3min->setPosition(Vec2( boxSize.width - 2 * btn5min->getTitleRenderer()->getContentSize().width - 3*BORDER_DEFAULT, boxSize.height - lblStadium->getContentSize().height - 2*BORDER_DEFAULT));
    box->addChild(btn3min);
    btn3min->addTouchEventListener([handlerMap, btn3min, btn5min, btn7min](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type != ui::Widget::TouchEventType::BEGAN) return;
        btn3min->getTitleRenderer()->setTextColor(COLOR_GREEN);
        btn5min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btn7min->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        handlerMap->getStringHandler(STRING_SERVER_DURATION_UPDATE)->execute(STRING_DURATION_SHORT);
    });
    
    
    // set active duration
    switch ( gameState.duration() ) {
        case GameState_MatchDuration_DURATION_SHORT:
            btn3min->getTitleRenderer()->setTextColor(COLOR_GREEN);
        break;
        case GameState_MatchDuration_DURATION_MEDIUM:
            btn5min->getTitleRenderer()->setTextColor(COLOR_GREEN);
        break;
        case GameState_MatchDuration_DURATION_LONG:
            btn7min->getTitleRenderer()->setTextColor(COLOR_GREEN);
        break;
            
        default:
            break;
    }

    // Size:
    auto lblSize = Label::createWithTTF("Size:", FONT_DEFAULT, FONT_SIZE_DEFAULT);
    lblSize->setTextColor(COLOR_GRAY);
    lblSize->setAnchorPoint(Vec2(0,1));
    lblSize->setPosition(Vec2( BORDER_DEFAULT, boxSize.height - 2*lblStadium->getContentSize().height - 3*BORDER_DEFAULT));
    box->addChild(lblSize);

    auto btnSizeBig = ui::Button::create();
    auto btnSizeMedium = ui::Button::create();
    auto btnSizeSmall = ui::Button::create();
    
    // big
    btnSizeBig->setTitleText("big");
    btnSizeBig->setAnchorPoint(Vec2(1,1));
    btnSizeBig->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT, FONT_SIZE_DEFAULT));
    btnSizeBig->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
    btnSizeBig->setPosition(Vec2( boxSize.width - BORDER_DEFAULT, boxSize.height - 2*lblStadium->getContentSize().height - 3*BORDER_DEFAULT));
    box->addChild(btnSizeBig);
    btnSizeBig->addTouchEventListener([handlerMap, btnSizeSmall, btnSizeMedium, btnSizeBig](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type != ui::Widget::TouchEventType::BEGAN) return;
        btnSizeSmall->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btnSizeMedium->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btnSizeBig->getTitleRenderer()->setTextColor(COLOR_GREEN);
        handlerMap->getStringHandler(STRING_SERVER_SIZE_UPDATE)->execute(STRING_SIZE_BIG);
    });
    
    // medium
    btnSizeMedium->setTitleText("medium");
    btnSizeMedium->setAnchorPoint(Vec2(1,1));
    btnSizeMedium->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT, FONT_SIZE_DEFAULT));
    btnSizeMedium->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
    btnSizeMedium->setPosition(Vec2( boxSize.width - btnSizeBig->getTitleRenderer()->getContentSize().width - 2*BORDER_DEFAULT, boxSize.height - 2*lblStadium->getContentSize().height - 3*BORDER_DEFAULT));
    box->addChild(btnSizeMedium);
    btnSizeMedium->addTouchEventListener([handlerMap, btnSizeSmall, btnSizeMedium, btnSizeBig](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type != ui::Widget::TouchEventType::BEGAN) return;
        btnSizeSmall->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btnSizeMedium->getTitleRenderer()->setTextColor(COLOR_GREEN);
        btnSizeBig->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        handlerMap->getStringHandler(STRING_SERVER_SIZE_UPDATE)->execute(STRING_SIZE_MEDIUM);
    });
    
    // small
    btnSizeSmall->setTitleText("small");
    btnSizeSmall->setAnchorPoint(Vec2(1,1));
    btnSizeSmall->getTitleRenderer()->setTTFConfig(TTFConfig(FONT_DEFAULT, FONT_SIZE_DEFAULT));
    btnSizeSmall->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
    btnSizeSmall->setPosition(Vec2( boxSize.width - btnSizeMedium->getTitleRenderer()->getContentSize().width - btnSizeBig->getTitleRenderer()->getContentSize().width - 3*BORDER_DEFAULT, boxSize.height - 2*lblStadium->getContentSize().height - 3*BORDER_DEFAULT));
    box->addChild(btnSizeSmall);
    btnSizeSmall->addTouchEventListener([handlerMap, btnSizeSmall, btnSizeMedium, btnSizeBig](Ref * sender, ui::Widget::TouchEventType type)
    {
        if(type != ui::Widget::TouchEventType::BEGAN) return;
        btnSizeSmall->getTitleRenderer()->setTextColor(COLOR_GREEN);
        btnSizeMedium->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        btnSizeBig->getTitleRenderer()->setTextColor(COLOR_GREEN_ALMOST_TRANSPARENT);
        handlerMap->getStringHandler(STRING_SERVER_SIZE_UPDATE)->execute(STRING_SIZE_SMALL);
    });

    
    // set active size
    switch ( gameState.pitchsize() ) {
        case GameState_PitchSize_SIZE_SMALL:
            btnSizeSmall->getTitleRenderer()->setTextColor(COLOR_GREEN);
            break;
        case GameState_PitchSize_SIZE_MEDIUM:
            btnSizeMedium->getTitleRenderer()->setTextColor(COLOR_GREEN);
            break;
        case GameState_PitchSize_SIZE_BIG:
            btnSizeBig->getTitleRenderer()->setTextColor(COLOR_GREEN);
            break;
            
        default:
            break;
    }
    
    
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
