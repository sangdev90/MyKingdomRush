//
//  WorldMapUILayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/4.
//
//

#include "WorldMapUILayer.hpp"
#include "ToolFunction.hpp"

USING_NS_CC;

WorldMapUILayer *WorldMapUILayer::create(){
    WorldMapUILayer *pRet = new (std::nothrow) WorldMapUILayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool WorldMapUILayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    this->layoutUI();
    
    return true;
}

void WorldMapUILayer::layoutUI(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _starLabel = Sprite::createWithSpriteFrameName("worldmap_ui_starlabel.png");
    _starLabel->setPosition(visibleSize.width - 100, visibleSize.height - 50);
    this->addChild(_starLabel, 1);
    
    _diamondLabel = Sprite::createWithSpriteFrameName("worldmap_ui_diamondlabel.png");
    _diamondLabel->setPosition(visibleSize.width - _starLabel->getContentSize().width - 100, visibleSize.height - 50);
    this->addChild(_diamondLabel, 1);
    
    int offsetX = 160;
    
    _shopButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_ui_button_shop.png",
                                                                "worldmap_ui_button_shop_on.png",
                                                                "worldmap_ui_button_shop.png",
                                                                [](Ref *sender){
                                                                    CCLOG("Shop Button");
                                                                });
    _shopButton->setPosition(visibleSize.width / 2, 80);
    this->addChild(_shopButton, 1);
    
    _heroRoomButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_ui_button_heroroom.png",
                                                                    "worldmap_ui_button_heroroom_on.png",
                                                                    "worldmap_ui_button_heroroom.png",
                                                                    [](Ref *sender){
                                                                        CCLOG("Hero Room Button");
                                                                    });
    _heroRoomButton->setPosition(visibleSize.width / 2 + offsetX, 80);
    this->addChild(_heroRoomButton, 1);
    
    _upgradesButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_ui_button_upgrades.png",
                                                                    "worldmap_ui_button_upgrades_on.png",
                                                                    "worldmap_ui_button_upgrades.png",
                                                                    [](Ref *sender){
                                                                        CCLOG("Upgrades Button");
                                                                    });
    _upgradesButton->setPosition(visibleSize.width / 2 + 2 * offsetX, 80);
    this->addChild(_upgradesButton, 1);
    
    _encyclopediaButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_ui_button_encyclopedia.png",
                                                                        "worldmap_ui_button_encyclopedia_on.png",
                                                                        "worldmap_ui_button_encyclopedia.png",
                                                                        [](Ref *sender){
                                                                            CCLOG("Encyclopedia Button");
                                                                        });
    _encyclopediaButton->setPosition(visibleSize.width / 2 + 3 * offsetX, 80);
    this->addChild(_encyclopediaButton, 1);
    
    _oprationButton = Menu::create(MenuItemToggle::createWithCallback([&](Ref *sender){
                                                                        CCLOG("Opration Button");
                                                                        _oprationButtonBackground->isVisible() ? _oprationButtonBackground->setVisible(false) : _oprationButtonBackground->setVisible(true);},
                                                                      MenuItemSprite::create(Sprite::createWithSpriteFrameName("worldmap_ui_button_opration.png"),
                                                                                             Sprite::createWithSpriteFrameName("worldmap_ui_button_opration_on.png")),
                                                                      NULL),
                                   NULL);
    _oprationButton->setPosition(50, 50);
    this->addChild(_oprationButton, 1);
    
    _achievementButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_ui_button_achievement.png",
                                                                       "worldmap_ui_button_achievement_on.png",
                                                                       "worldmap_ui_button_achievement.png",
                                                                       [](Ref *ender){
                                                                           CCLOG("Achievement Button");
                                                                       });
    _achievementButton->setPosition(150, 50);
    this->addChild(_achievementButton, 1);
    
    _oprationButtonBackground = Sprite::createWithSpriteFrameName("worldmap_ui_buttonbackground.png");
    _oprationButtonBackground->setAnchorPoint(Vec2(0.5, 0));
    _oprationButtonBackground->setPosition(50, 50);
    _oprationButtonBackground->setVisible(false);
    this->addChild(_oprationButtonBackground, 0);
    
    Size buttonBackgroundVisible = _oprationButtonBackground->getContentSize();
    int offsetY = 80;
    _homeButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_ui_button_home.png",
                                                                "worldmap_ui_button_home_on.png",
                                                                "worldmap_ui_button_home.png",
                                                                [](Ref *sender){
                                                                    CCLOG("Home Button");
                                                                });
    _homeButton->setPosition(buttonBackgroundVisible.width / 2, buttonBackgroundVisible.height - 20);
    _oprationButtonBackground->addChild(_homeButton, 1);
    
    _soundButton = Menu::create(MenuItemToggle::createWithCallback([](Ref *sender){
        CCLOG("Sound Button");
    }, MenuItemSprite::create(Sprite::createWithSpriteFrameName("worldmap_ui_button_sound.png"), Sprite::createWithSpriteFrameName("worldmap_ui_button_sound.png")), MenuItemSprite::create(Sprite::createWithSpriteFrameName("worldmap_ui_button_sound_no.png"), Sprite::createWithSpriteFrameName("worldmap_ui_button_sound_no.png")), NULL), NULL);
    _soundButton->setPosition(buttonBackgroundVisible.width / 2, buttonBackgroundVisible.height - offsetY - 20);
    _oprationButtonBackground->addChild(_soundButton, 1);
    
    _musicButton = Menu::create(MenuItemToggle::createWithCallback([](Ref *sender){
        CCLOG("Music Button");
    }, MenuItemSprite::create(Sprite::createWithSpriteFrameName("worldmap_ui_button_music.png"), Sprite::createWithSpriteFrameName("worldmap_ui_button_music.png")), MenuItemSprite::create(Sprite::createWithSpriteFrameName("worldmap_ui_button_music_no.png"), Sprite::createWithSpriteFrameName("worldmap_ui_button_music_no.png")), NULL), NULL);
    _musicButton->setPosition(buttonBackgroundVisible.width / 2, buttonBackgroundVisible.height - offsetY * 2 - 20);
    _oprationButtonBackground->addChild(_musicButton, 1);
    
}
