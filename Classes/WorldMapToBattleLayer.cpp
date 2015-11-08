//
//  WorldMapToBattleLayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/7.
//
//

#include "WorldMapToBattleLayer.hpp"
#include "ToolFunction.hpp"

USING_NS_CC;

WorldMapToBattleLayer *WorldMapToBattleLayer::create(const std::string &stage){
    WorldMapToBattleLayer *pRet = new (std::nothrow) WorldMapToBattleLayer(stage);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool WorldMapToBattleLayer::init(){

    if (!Layer::init()){
        return false;
    }
    
    this->layoutUI();
    
    return true;
}

void WorldMapToBattleLayer::onEnter(){
    Layer::onEnter();
}

void WorldMapToBattleLayer::onExit(){
    Layer::onExit();
}

void WorldMapToBattleLayer::layoutUI(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size backgroundWoodSize = Sprite::createWithSpriteFrameName("worldmap_tobattle_background_wood.png")->getContentSize();
    int numberOfNeedWoodX = visibleSize.width / backgroundWoodSize.width + 1;
    int numberOfNeedWoodY = visibleSize.height / backgroundWoodSize.height + 1;
    
    for (int indexX = 0; indexX < numberOfNeedWoodX; ++indexX){
        for (int indexY = 0; indexY < numberOfNeedWoodY; ++indexY){
            Sprite *wood = Sprite::createWithSpriteFrameName("worldmap_tobattle_background_wood.png");
            wood->setAnchorPoint(Vec2(0, 0));
            wood->setPosition(backgroundWoodSize.width * indexX - indexX, backgroundWoodSize.height * indexY - indexY);
            this->addChild(wood, 0);
        }
    }
    
    _background = Sprite::createWithSpriteFrameName("worldmap_tobattle_background.png");
    _background->setAnchorPoint(Vec2(0, 1));
    _background->setPosition(0, visibleSize.height);
    this->addChild(_background, 1);
    
    _perViewBackground = Sprite::createWithSpriteFrameName("worldmap_tobattle_ preview.png");
    _perViewBackground->setAnchorPoint(Vec2(0, 1));
    _perViewBackground->setPosition(-30, _background->getContentSize().height);
    _background->addChild(_perViewBackground, 5);
    
    _closeButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_tobattle_button_close.png",
                                                                 "worldmap_tobattle_button_close_on.png",
                                                                 "worldmap_tobattle_button_close.png",
                                                                 [](Ref *sender){
                                                                     CCLOG("To Battle Close Button");
                                                                 });
    _closeButton->setPosition(visibleSize.width - 140, visibleSize.height - 70);
    this->addChild(_closeButton, 1);
    
    _toBattleButton = createMenuWithSpriteByThreeTextureAndCallback("worldmap_tobattle_button_tobattle.png",
                                                                    "worldmap_tobattle_button_tobattle_on.png",
                                                                    "worldmap_tobattle_button_tobattle.png",
                                                                    [&](Ref *sender){
                                                                        CCLOG("TO Battle ToBattle Button : %s", _battleStage.c_str());
                                                                    });
    _toBattleButton->setPosition(visibleSize.width - 200, 90);
    this->addChild(_toBattleButton, 1);
    
    
}
