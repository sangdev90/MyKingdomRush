//
//  BattleUILayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include "BattleUILayer.hpp"
#include "ToolFunction.hpp"
#include "BattleDisplayBoardSprite.hpp"

USING_NS_CC;

BattleUILayer *BattleUILayer::create(){
    BattleUILayer *pRet = new (std::nothrow) BattleUILayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BattleUILayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    this->layoutUI();
    
    return true;
}

void BattleUILayer::layoutUI(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _displayBoardSprite = BattleDisplayBoardSprite::createWithInformationAndSpriteFrameName(20, 500, 1, 10, "battle_ui_displayboard.png");
    _displayBoardSprite->setAnchorPoint(Vec2(0, 1));
    _displayBoardSprite->setPosition(20, visibleSize.height - 20);
    this->addChild(_displayBoardSprite, 1);
    
    
    
}
