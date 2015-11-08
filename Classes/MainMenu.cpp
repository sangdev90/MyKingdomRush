//
//  MainMenu.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/10/30.
//
//

#include "MainMenu.hpp"

#include "ToolFunction.hpp"
#include "ResourcesPath.h"

#include "WaitLoad.hpp"
#include "Credits.hpp"
#include "WorldMapScene.hpp"

USING_NS_CC;

Scene *MainMenu::createScene(bool is){
    
    Scene *scene = Scene::create();
    MainMenu *layer = MainMenu::create(is);
    scene->addChild(layer);
    return scene;
    
}

MainMenu *MainMenu::create(bool is){
    MainMenu *pRet = new (std::nothrow) MainMenu(is);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool MainMenu::init(){
    if (!Layer::init()){
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MAINMENU_UI_PLIST);
    
    Sprite *background = Sprite::create("res/image/mainmenu/mainmenu_background.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background, 0);
    
    return true;
}

void MainMenu::onEnter(){
    Layer::onEnter();
    
    if (!isGameStart){
        CCLOG("是从其它场景转入，需要显示 WaitLoad");
        this->addChild(WaitLoad::getInstance());
        WaitLoad::getInstance()->open();
    }
    
    Sprite *logo = Sprite::createWithSpriteFrameName("mainmenu_logo.png");
    logo->setPosition(visibleSize.width / 2, visibleSize.height / 3 * 2);
    logo->setScale(0.3, 0.3);
    this->addChild(logo, 3);
    
    logo->runAction(Sequence::create(ScaleTo::create(0.3, 1),
                                     CallFunc::create([&](){
        
        Menu *startButton = createMenuWithSpriteByThreeTextureAndCallback("mainmenu_button_start.png",
                                                                          "mainmenu_button_start_on.png",
                                                                          "mainmenu_button_start.png",
                                                                          [&](Ref *sender){
                                                                              
                                                                              CCLOG("Start Button");
                                                                              
                                                                              WorldMapScene *worldMapScene = WorldMapScene::create();
                                                                              Director::getInstance()->replaceScene(worldMapScene);
                                                                          
                                                                          });
        
        startButton->setPosition(visibleSize.width / 2, visibleSize.height / 3 * 2);
        this->addChild(startButton, 2);
        
        startButton->runAction(Sequence::create(EaseElasticOut::create(MoveBy::create(0.5, Vec2(0, -180)), 2),
                                                CallFuncN::create([&](Node *target){
            
            Vec2 startButtonPosition = target->getPosition();
            
            Menu *creditsButton = createMenuWithSpriteByThreeTextureAndCallback("mainmenu_button_crdits.png",
                                                                               "mainmenu_button_crdits_on.png",
                                                                               "mainmenu_button_crdits.png",
                                                                               [&](Ref *sender){
                                                                                   CCLOG("Cridits Button");
                                                                                   WaitLoad *waitLoadLayer = WaitLoad::getInstance();
                                                                                   
                                                                                   this->addChild(waitLoadLayer, 100);
                                                                                   waitLoadLayer->close([&](){
                                                                                       
                                                                                       Scene *creditsScene = Credits::createScene();
                                                                                       Director::getInstance()->replaceScene(creditsScene);
                                                                                       
                                                                                   });
                                                                                   
                                                                               });
            this->addChild(creditsButton, 1);
            creditsButton->setPosition(startButtonPosition.x, startButtonPosition.y - 50);
            creditsButton->runAction(Sequence::create(EaseElasticOut::create(MoveBy::create(0.3, Vec2(0, -100)), 2), NULL));
        }), NULL));
        
        
        
        
    }), NULL));
    
}
