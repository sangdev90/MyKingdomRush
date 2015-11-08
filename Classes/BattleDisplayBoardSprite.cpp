//
//  BattleDisplayBoardSprite.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include "BattleDisplayBoardSprite.hpp"

USING_NS_CC;

BattleDisplayBoardSprite *BattleDisplayBoardSprite::createWithInformationAndSpriteFrameName(int numberOfHP, int numberOfCoin, int numberOfWave, int numberOfTotalWave, const std::string &spriteFrameName){
    
    BattleDisplayBoardSprite *pRet = new (std::nothrow) BattleDisplayBoardSprite(numberOfHP, numberOfCoin, numberOfWave, numberOfTotalWave);
    if (pRet && pRet->initWithSpriteFrameName("battle_ui_displayboard.png")){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

void BattleDisplayBoardSprite::onEnter(){
    Sprite::onEnter();
    
//    _labelOfHP = Label::createWithSystemFont(std::string(_numberOfHP), "Arial", 20);
    
}
