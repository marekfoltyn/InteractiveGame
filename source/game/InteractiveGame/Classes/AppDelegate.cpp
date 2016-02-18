#include "AppDelegate.h"
#include "Game.h"

USING_NS_CC;

AppDelegate::AppDelegate(){}
AppDelegate::~AppDelegate(){}

// toggle debug
#define DEBUG

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}



bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        
        #ifdef DEBUG
            glview = GLViewImpl::createWithRect("InteractiveGame", cocos2d::Rect(0, 0, 1024, 576));
            //glview = GLViewImpl::createWithRect("InteractiveGame", cocos2d::Rect(0, 0, 1024, 768));
            //glview = GLViewImpl::createWithRect("InteractiveGame", cocos2d::Rect(0, 0, 1400, 900));
        #else
            glview = GLViewImpl::createWithFullScreen("InteractiveGame");
        #endif
        
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1680, 1050, ResolutionPolicy::NO_BORDER);

#ifdef DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#endif
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");
//    FileUtils::getInstance()->addSearchPath("../../../shared/resources");


    // run the game
    Game::getInstance()->run();

    return true;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
