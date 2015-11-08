//
//  BattleDisplayBoardSprite.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include "BattleDisplayBoardSprite.hpp"
#include "ToolFunction.hpp"

USING_NS_CC;

BattleDisplayBoardSprite *BattleDisplayBoardSprite::createWithInformationAndSpriteFrameName(int numberOfHP, int numberOfCoin, int numberOfWave, int numberOfTotalWave, const std::string &spriteFrameName){
    
    BattleDisplayBoardSprite *pRet = new (std::nothrow) BattleDisplayBoardSprite(numberOfHP, numberOfCoin, numberOfWave, numberOfTotalWave);
    if (pRet && pRet->initWithSpriteFrameName(spriteFrameName)){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

void BattleDisplayBoardSprite::onEnter(){
    Sprite::onEnter();
    
    _labelOfHP = Label::createWithSystemFont(int2string(_numberOfHP), "Arial", 20);
    _labelOfHP->setPosition(64, 64);
    this->addChild(_labelOfHP, 1);
    
    _labelOfCoin = Label::createWithSystemFont(int2string(_numberOfCoin), "Arial", 20);
    _labelOfCoin->setPosition(185, 64);
    this->addChild(_labelOfCoin, 1);
    
    std::string waveString = std::string("WAVE") + int2string(_numberOfWave) + "/" + int2string(_numberOfTotalWave);
    _labelOfWave = Label::createWithSystemFont(waveString, "Arial", 20);
    _labelOfWave->setPosition(24, 160);
    
}

void BattleDisplayBoardSprite::updateHP(int numberOfHP){
    _numberOfHP = numberOfHP;
    _labelOfHP->setString(int2string(_numberOfHP));
}

void BattleDisplayBoardSprite::updateCoin(int numberOfCoin){
    _numberOfCoin = numberOfCoin;
    _labelOfCoin->setString(int2string(_numberOfCoin));
}

void BattleDisplayBoardSprite::updateWave(int numberOfWave){
    _numberOfWave = numberOfWave;
    std::string waveString = std::string("WAVE") + int2string(_numberOfWave) + "/" + int2string(_numberOfTotalWave);
    _labelOfWave->setString(waveString);
}
