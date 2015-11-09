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
    
//    std::string hp = int2string(_numberOfHP);
//    CCLOG("%s", hp.c_str());
    
    _labelOfHP = Label::createWithSystemFont(int2string(_numberOfHP), "Arial", 25);
    _labelOfHP->setPosition(64, 64);
    this->addChild(_labelOfHP, 1);
    
    _labelOfCoin = Label::createWithSystemFont(int2string(_numberOfCoin), "Arial", 25);
    _labelOfCoin->setPosition(185, 64);
    this->addChild(_labelOfCoin, 1);
    
    std::string waveString = std::string("WAVE ") + int2string(_numberOfWave) + " / " + int2string(_numberOfTotalWave);
    CCLOG("%s", waveString.c_str());
    _labelOfWave = Label::createWithSystemFont(waveString, "Arial", 23);
    _labelOfWave->setPosition(140, 24);
    this->addChild(_labelOfWave, 1);
    
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
