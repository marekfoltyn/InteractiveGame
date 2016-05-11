
#include "TestDelegate.h"
#include "TestScene.h"
#include "GameplayDefinitions.h"
#include "StartHandler.h"

#define CATCH_CONFIG_RUNNER
#include "Catch.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate()
{
}

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
        glview = GLViewImpl::createWithRect("InteractiveController", cocos2d::Rect(0, 0, DESIGN_WIDTH, DESIGN_HEIGHT));
        director->setOpenGLView(glview);
    }
    
    director->getOpenGLView()->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, ResolutionPolicy::NO_BORDER);
    
    // gitturn on display FPS
    //director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    FileUtils::getInstance()->addSearchPath("res");
    
    // create a scene. it's an autorelease object
    auto scene = TestScene::createScene();
    
    // run
    director->runWithScene(scene);
    
    // start testing session
    Catch::Session session;
    session.run();

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

///////////////////////// UNIT TESTING /////////////////////////

#include "NetworkingTests.hpp"

#include "HandlerTests.hpp"

