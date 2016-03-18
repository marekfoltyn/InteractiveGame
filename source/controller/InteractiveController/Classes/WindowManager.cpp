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

void WindowManager::showConnectionLostDialog(MainMenuScene * scene)
{
    Layer * s = scene;
    
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    auto origin = director->getVisibleOrigin();
    
    // background
    auto bg = ui::Button::create("line_green.png");
    bg->setScale(16.8, 20*10.5);
    bg->setOpacity(200);
    bg->setCascadeOpacityEnabled(true);
    bg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    s->addChild(bg);

    // dialog box
    auto box = Sprite::create("line.png");
    box->setScale(10, 20*6);
    box->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    s->addChild(box);
    
    
    // text
    auto text = Label::createWithTTF("Connection lost.", "Vanilla.ttf", FONT_SIZE_DEFAULT);
    text->setTextColor(COLOR_GREEN);
    text->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + (box->getContentSize().height*box->getScaleY())/4 ));
    s->addChild(text);
    
    auto ok = ui::Button::create();
    ok->setTitleText("Ok");
    ok->getTitleRenderer()->setTTFConfig(TTFConfig("Vanilla.ttf",FONT_SIZE_DEFAULT*2));
    ok->getTitleRenderer()->setTextColor(COLOR_GREEN);
    ok->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - (box->getContentSize().height*box->getScaleY())/4 ));
    s->addChild(ok);
    
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
            scene->schedule([scene,ok,text,bg,box](float dt){
                scene->removeChild(ok);
                scene->removeChild(text);
                scene->removeChild(bg);
                scene->removeChild(box);
            }, 0, 1, Definitions::DIALOG_FADEOUT_DURATION, "");
            
        }
    });
    
    CCLOG("dialog...");
    
    //TODO
}
