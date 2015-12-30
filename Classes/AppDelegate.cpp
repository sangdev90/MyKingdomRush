#include "AppDelegate.h"
#include "MainMenu.hpp"

#include "ToolFunction.hpp"
#include "ResourcesPath.h"
#include "WorldMapToBattleLayer.hpp"

#include "BattleScene.hpp"
#include "GameData.hpp"

USING_NS_CC;

void AppDelegate::testCode(){
    
//    GameData::getInstance()->loadMonsterData();
//    Scene *testScene = Scene::create();
//    Director::getInstance()->runWithScene(testScene);
    
    //战场
    prepareBattle();
    BattleScene *testBattleScene = BattleScene::create("stage_1");
    Director::getInstance()->runWithScene(testBattleScene);
    return;
    
    //世界地图
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLDMAP_UI_PLIST);
    Scene *testScene = Scene::create();
    WorldMapToBattleLayer *testLayer = WorldMapToBattleLayer::create("stage_1");
    testScene->addChild(testLayer);
    Director::getInstance()->runWithScene(testScene);
    return;//TODO:
}

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
        glview = GLViewImpl::createWithRect("KingdomRush", Rect(0, 0, 1136, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // Test
    this->testCode();
    return true;
    
    auto scene = MainMenu::createScene(true);
    director->runWithScene(scene);

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
