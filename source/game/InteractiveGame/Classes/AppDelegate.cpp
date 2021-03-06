#include "AppDelegate.h"
#include "GameplayDefinitions.h"
#include "StartHandler.h"

AppDelegate::AppDelegate(){}
AppDelegate::~AppDelegate(){}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}



bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        
        #ifdef DEBUG
            glview = cocos2d::GLViewImpl::createWithRect("InteractiveGame", cocos2d::Rect(0, 0, 1024, 576));
            //glview = GLViewImpl::createWithRect("InteractiveGame", cocos2d::Rect(0, 0, 1024, 768));
            //glview = GLViewImpl::createWithRect("InteractiveGame", cocos2d::Rect(0, 0, 1400, 900));
        #else
            glview = cocos2d::GLViewImpl::createWithFullScreen("InteractiveGame");
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

    cocos2d::FileUtils::getInstance()->addSearchPath("res");

    // run the game
    auto game = Game::getInstance();
    StartHandler(game, director).execute();

    return true;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    
    cocos2d::Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    cocos2d::Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
