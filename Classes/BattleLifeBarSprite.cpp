//
//  BattleLifeBarSprite.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/12/27.
//
//

#include "BattleLifeBarSprite.hpp"

USING_NS_CC;

#pragma mark - Public Method

BattleLifeBarSprite *BattleLifeBarSprite::createBattleLifeBarSprite(int state, int fullLiftPoint){
    if (state > battle_life_bar_medBig){
        CCLOG("血条 state 不对，改成默认 big");
        state = 0;
    }
    
    BattleLifeBarSprite *lifeBar = new (std::nothrow) BattleLifeBarSprite(state, fullLiftPoint);
    if (lifeBar && lifeBar->init()){
        lifeBar->autorelease();
        return lifeBar;
    }
    
    delete lifeBar;
    lifeBar = nullptr;
    return nullptr;
}

bool BattleLifeBarSprite::init(){
    if (!Sprite::init()){
        return false;
    }
    
    _fullLifeBar = Sprite::createWithSpriteFrameName(_getLifeBarSpriteFrameName("background"));
    _currentLifeBar = Sprite::createWithSpriteFrameName(_getLifeBarSpriteFrameName("normal"));
    
    _currentLifeBar->setAnchorPoint(Vec2(0, 0.5));
    _currentLifeBar->setPosition(-_currentLifeBar->getContentSize().width / 2, 0);
    
    this->addChild(_fullLifeBar, 0);
    this->addChild(_currentLifeBar, 0);
    
    
    return true;
}

void BattleLifeBarSprite::updateLife(int targetValue){
    if (targetValue > _fullLifePoint){
        targetValue = _fullLifePoint;
    }
    if (targetValue < 0){
        targetValue = 0;
    }
    float percent= static_cast<float>(targetValue) / static_cast<float>(_fullLifePoint);
    //TODO:这里是不是要加个动画？
    _currentLifeBar->setScaleX(percent);
}

#pragma mark - Private Method

std::string BattleLifeBarSprite::_getLifeBarSpriteFrameName(const std::string &which){
    std::string state;
    
    switch (_state){
        case battle_life_bar_big:{
            state = "big";
            break;
        }
            
        case battle_life_bar_med:{
            state = "med";
            break;
        }
            
        case battle_life_bar_small:{
            state = "small";
            break;
        }
            
        case battle_life_bar_medBig:{
            state = "medBig";
            break;
        }
            
        default:{
            state = "big";
            break;
        }
    }
    
    if (which == "background"){
        std::string frameName = std::string("battle_basic_lifebar_bg_") + state + ".png";
        return frameName;
    }else if (which == "normal"){
        std::string frameName = std::string("battle_basic_lifebar_") + state + ".png";
        return frameName;
    }else {
        CCLOG("血条的 which 不对，改成默认 background");
        std::string frameName = std::string("battle_basic_lifebar_bg_") + state + ".png";
        return frameName;
    }
}